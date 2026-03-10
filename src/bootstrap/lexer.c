#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include "ext.h"

typedef struct StructDef StructDef;
typedef struct EnumDef EnumDef;
typedef struct FunctionDef FunctionDef;
typedef struct Dynamic Dynamic;
typedef struct Range Range;
typedef struct Map Map;
typedef struct Set Set;
typedef struct Vec Vec;
typedef enum {
    TokenType_TAG_Eof,
    TokenType_TAG_LParen,
    TokenType_TAG_RParen,
    TokenType_TAG_LBrace,
    TokenType_TAG_RBrace,
    TokenType_TAG_LBracket,
    TokenType_TAG_RBracket,
    TokenType_TAG_Comma,
    TokenType_TAG_Colon,
    TokenType_TAG_Question,
    TokenType_TAG_Bang,
    TokenType_TAG_Minus,
    TokenType_TAG_Plus,
    TokenType_TAG_Star,
    TokenType_TAG_Slash,
    TokenType_TAG_Dot,
    TokenType_TAG_DotDot,
    TokenType_TAG_Eq,
    TokenType_TAG_EqEq,
    TokenType_TAG_Neq,
    TokenType_TAG_Lt,
    TokenType_TAG_LtEq,
    TokenType_TAG_Gt,
    TokenType_TAG_GtEq,
    TokenType_TAG_ColonEq,
    TokenType_TAG_Ident,
    TokenType_TAG_StringTok,
    TokenType_TAG_Number,
    TokenType_TAG_Char,
    TokenType_TAG_KwMode,
    TokenType_TAG_KwMut,
    TokenType_TAG_KwOwn,
    TokenType_TAG_KwRef,
    TokenType_TAG_KwStruct,
    TokenType_TAG_KwExtStruct,
    TokenType_TAG_KwEnum,
    TokenType_TAG_KwNamespace,
    TokenType_TAG_KwFunc,
    TokenType_TAG_KwProc,
    TokenType_TAG_KwTest,
    TokenType_TAG_KwMacro,
    TokenType_TAG_KwExtFunc,
    TokenType_TAG_KwExtProc,
    TokenType_TAG_KwReturns,
    TokenType_TAG_KwThrows,
    TokenType_TAG_KwIf,
    TokenType_TAG_KwElse,
    TokenType_TAG_KwWhile,
    TokenType_TAG_KwFor,
    TokenType_TAG_KwIn,
    TokenType_TAG_KwSwitch,
    TokenType_TAG_KwMatch,
    TokenType_TAG_KwCase,
    TokenType_TAG_KwDefault,
    TokenType_TAG_KwReturn,
    TokenType_TAG_KwThrow,
    TokenType_TAG_KwCatch,
    TokenType_TAG_KwBreak,
    TokenType_TAG_KwContinue,
    TokenType_TAG_KwDefer,
    TokenType_TAG_KwTrue,
    TokenType_TAG_KwFalse,
    TokenType_TAG_Error
} TokenType_tag;
typedef struct TokenType TokenType;
typedef struct Token Token;


static Str *Str_lit(const char *s, unsigned long long len);
static void print_single(Str *s);
static void print_flush();

EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool * call_free);
U64 * EnumDef_size(void);
static __attribute__((unused)) Str * U8_to_str(U8 * val);
static __attribute__((unused)) U8 * U8_from_i64(I64 * val);
static __attribute__((unused)) U64 * U8_size(void);
static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b);
static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b);
static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b);
static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b);
static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b);
static __attribute__((unused)) Str * I16_to_str(I16 * val);
static __attribute__((unused)) I16 * I16_from_i64(I64 * val);
static __attribute__((unused)) I16 * I16_neg(I16 * a);
static __attribute__((unused)) I16 * I16_abs(I16 * a);
static __attribute__((unused)) U64 * I16_size(void);
static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b);
static __attribute__((unused)) Str * I32_to_str(I32 * val);
static __attribute__((unused)) I32 * I32_from_i64(I64 * val);
static __attribute__((unused)) I32 * I32_neg(I32 * a);
static __attribute__((unused)) I32 * I32_abs(I32 * a);
static __attribute__((unused)) U64 * I32_size(void);
static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b);
static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b);
static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b);
static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b);
static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b);
static __attribute__((unused)) F32 * F32_from_i64(I64 * val);
static __attribute__((unused)) U64 * F32_size(void);
static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b);
static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b);
static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b);
static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b);
static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b);
static __attribute__((unused)) Str * U32_to_str(U32 * val);
static __attribute__((unused)) U32 * U32_from_i64(I64 * val);
static __attribute__((unused)) U64 * U32_size(void);
static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b);
Str * U64_to_str(U64 val);
static __attribute__((unused)) U64 * U64_from_i64(I64 * val);
static __attribute__((unused)) U64 * U64_size(void);
static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b);
static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b);
static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b);
static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b);
static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b);
static __attribute__((unused)) Str * I64_to_str(I64 * val);
static __attribute__((unused)) I64 * I64_neg(I64 * a);
static __attribute__((unused)) I64 * I64_abs(I64 * a);
static __attribute__((unused)) U64 * I64_size(void);
static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b);
static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b);
static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b);
static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b);
static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
static __attribute__((unused)) Str * Bool_to_str(Bool * b);
static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b);
static __attribute__((unused)) U64 * Bool_size(void);
static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b);
static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b);
static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b);
static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b);
static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b);
void println(Array * parts);
void print(Array * parts);
Str * format(Array * parts);
I64 * wait_cmd(I64 * pid);
I64 * run_cmd(Str * output, Array * args);
void panic(Str * loc_str, Array * parts);
void TODO(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
Bool * assertm(Str * loc_str, Bool * cond, Array * parts);
Bool * assert(Str * loc_str, Bool * cond);
void test_expect(Str * loc_str, Bool * cond, Array * parts);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap);
U64 * Array_len(Array * self);
void * Array_get(Array * self, U64 * i);
void Array_set(Array * self, U64 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U64 * Array_size(void);
Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size);
U64 * Map_len(Map * self);
Bool * Map_has(Map * self, void * key);
void * Map_get(Map * self, void * key);
void Map_set(Map * self, void * key, void * val);
void Map_delete(Map * self, Bool * call_free);
Map * Map_clone(Map * self);
U64 * Map_size(void);
Set * Set_new(Str * elem_type, U64 * elem_size);
U64 * Set_len(Set * self);
Bool * Set_has(Set * self, void * val);
void Set_add(Set * self, void * val);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U64 * Set_size(void);
U64 * Str_len(Str * self);
U8 * Str_get(Str * self, U64 * i);
I64 * Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_with_capacity(U64 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_to_str(Str * val);
Str * Str_substr(Str * s, U64 * start, U64 * n);
Bool * Str_contains(Str * a, Str * b);
Bool * Str_starts_with(Str * a, Str * b);
Bool * Str_ends_with(Str * a, Str * b);
Bool * Str_is_empty(Str * self);
I64 * Str_find(Str * self, Str * needle);
I64 * Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
Str * Str_get_char(Str * self, U64 * i);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 * byte);
I64 * Str_to_i64(Str * self);
U64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
Bool * Str_lt(Str * a, Str * b);
Bool * Str_gt(Str * a, Str * b);
Bool * Str_neq(Str * a, Str * b);
Bool * Str_lte(Str * a, Str * b);
Bool * Str_gte(Str * a, Str * b);
Vec * Vec_new(Str * elem_type, U64 * elem_size);
U64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, U64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U64 * Vec_size(void);
Vec * split(Str * s, Str * delim);
Str * join(Vec * parts, Str * sep);
Bool * TokenType_is_Eof(TokenType * self);
Bool * TokenType_is_LParen(TokenType * self);
Bool * TokenType_is_RParen(TokenType * self);
Bool * TokenType_is_LBrace(TokenType * self);
Bool * TokenType_is_RBrace(TokenType * self);
Bool * TokenType_is_LBracket(TokenType * self);
Bool * TokenType_is_RBracket(TokenType * self);
Bool * TokenType_is_Comma(TokenType * self);
Bool * TokenType_is_Colon(TokenType * self);
Bool * TokenType_is_Question(TokenType * self);
Bool * TokenType_is_Bang(TokenType * self);
Bool * TokenType_is_Minus(TokenType * self);
Bool * TokenType_is_Plus(TokenType * self);
Bool * TokenType_is_Star(TokenType * self);
Bool * TokenType_is_Slash(TokenType * self);
Bool * TokenType_is_Dot(TokenType * self);
Bool * TokenType_is_DotDot(TokenType * self);
Bool * TokenType_is_Eq(TokenType * self);
Bool * TokenType_is_EqEq(TokenType * self);
Bool * TokenType_is_Neq(TokenType * self);
Bool * TokenType_is_Lt(TokenType * self);
Bool * TokenType_is_LtEq(TokenType * self);
Bool * TokenType_is_Gt(TokenType * self);
Bool * TokenType_is_GtEq(TokenType * self);
Bool * TokenType_is_ColonEq(TokenType * self);
Bool * TokenType_is_Ident(TokenType * self);
Bool * TokenType_is_StringTok(TokenType * self);
Bool * TokenType_is_Number(TokenType * self);
Bool * TokenType_is_Char(TokenType * self);
Bool * TokenType_is_KwMode(TokenType * self);
Bool * TokenType_is_KwMut(TokenType * self);
Bool * TokenType_is_KwOwn(TokenType * self);
Bool * TokenType_is_KwRef(TokenType * self);
Bool * TokenType_is_KwStruct(TokenType * self);
Bool * TokenType_is_KwExtStruct(TokenType * self);
Bool * TokenType_is_KwEnum(TokenType * self);
Bool * TokenType_is_KwNamespace(TokenType * self);
Bool * TokenType_is_KwFunc(TokenType * self);
Bool * TokenType_is_KwProc(TokenType * self);
Bool * TokenType_is_KwTest(TokenType * self);
Bool * TokenType_is_KwMacro(TokenType * self);
Bool * TokenType_is_KwExtFunc(TokenType * self);
Bool * TokenType_is_KwExtProc(TokenType * self);
Bool * TokenType_is_KwReturns(TokenType * self);
Bool * TokenType_is_KwThrows(TokenType * self);
Bool * TokenType_is_KwIf(TokenType * self);
Bool * TokenType_is_KwElse(TokenType * self);
Bool * TokenType_is_KwWhile(TokenType * self);
Bool * TokenType_is_KwFor(TokenType * self);
Bool * TokenType_is_KwIn(TokenType * self);
Bool * TokenType_is_KwSwitch(TokenType * self);
Bool * TokenType_is_KwMatch(TokenType * self);
Bool * TokenType_is_KwCase(TokenType * self);
Bool * TokenType_is_KwDefault(TokenType * self);
Bool * TokenType_is_KwReturn(TokenType * self);
Bool * TokenType_is_KwThrow(TokenType * self);
Bool * TokenType_is_KwCatch(TokenType * self);
Bool * TokenType_is_KwBreak(TokenType * self);
Bool * TokenType_is_KwContinue(TokenType * self);
Bool * TokenType_is_KwDefer(TokenType * self);
Bool * TokenType_is_KwTrue(TokenType * self);
Bool * TokenType_is_KwFalse(TokenType * self);
Bool * TokenType_is_Error(TokenType * self);
Bool * TokenType_eq(TokenType * self, TokenType * other);
TokenType * TokenType_clone(TokenType * self);
void TokenType_delete(TokenType * self, Bool * call_free);
Str * TokenType_to_str(TokenType * self);
U64 * TokenType_size(void);
Token * Token_clone(Token * self);
void Token_delete(Token * self, Bool * call_free);
U64 * Token_size(void);
Bool * is_digit(U8 * c);
Bool * is_alpha(U8 * c);
Bool * is_alnum(U8 * c);
Str * tok_name(TokenType * type);
TokenType * lookup_keyword(Str * word);
Vec * tokenize(Str * source, Str * path);
Bool *TokenType_eq(TokenType *, TokenType *);
TokenType *TokenType_Eof();
TokenType *TokenType_LParen();
TokenType *TokenType_RParen();
TokenType *TokenType_LBrace();
TokenType *TokenType_RBrace();
TokenType *TokenType_LBracket();
TokenType *TokenType_RBracket();
TokenType *TokenType_Comma();
TokenType *TokenType_Colon();
TokenType *TokenType_Question();
TokenType *TokenType_Bang();
TokenType *TokenType_Minus();
TokenType *TokenType_Plus();
TokenType *TokenType_Star();
TokenType *TokenType_Slash();
TokenType *TokenType_Dot();
TokenType *TokenType_DotDot();
TokenType *TokenType_Eq();
TokenType *TokenType_EqEq();
TokenType *TokenType_Neq();
TokenType *TokenType_Lt();
TokenType *TokenType_LtEq();
TokenType *TokenType_Gt();
TokenType *TokenType_GtEq();
TokenType *TokenType_ColonEq();
TokenType *TokenType_Ident();
TokenType *TokenType_StringTok();
TokenType *TokenType_Number();
TokenType *TokenType_Char();
TokenType *TokenType_KwMode();
TokenType *TokenType_KwMut();
TokenType *TokenType_KwOwn();
TokenType *TokenType_KwRef();
TokenType *TokenType_KwStruct();
TokenType *TokenType_KwExtStruct();
TokenType *TokenType_KwEnum();
TokenType *TokenType_KwNamespace();
TokenType *TokenType_KwFunc();
TokenType *TokenType_KwProc();
TokenType *TokenType_KwTest();
TokenType *TokenType_KwMacro();
TokenType *TokenType_KwExtFunc();
TokenType *TokenType_KwExtProc();
TokenType *TokenType_KwReturns();
TokenType *TokenType_KwThrows();
TokenType *TokenType_KwIf();
TokenType *TokenType_KwElse();
TokenType *TokenType_KwWhile();
TokenType *TokenType_KwFor();
TokenType *TokenType_KwIn();
TokenType *TokenType_KwSwitch();
TokenType *TokenType_KwMatch();
TokenType *TokenType_KwCase();
TokenType *TokenType_KwDefault();
TokenType *TokenType_KwReturn();
TokenType *TokenType_KwThrow();
TokenType *TokenType_KwCatch();
TokenType *TokenType_KwBreak();
TokenType *TokenType_KwContinue();
TokenType *TokenType_KwDefer();
TokenType *TokenType_KwTrue();
TokenType *TokenType_KwFalse();
TokenType *TokenType_Error();

void dyn_call_delete(Str *type_name, void *val, void *arg2);
void *dyn_call_clone(Str *type_name, void *val);
void *dyn_call_cmp(Str *type_name, void *val, void *arg2);

Bool *dyn_has_cmp(Str *type_name);

typedef struct StructDef {
    char _;
} StructDef;


typedef struct EnumDef {
    char _;
} EnumDef;


typedef struct FunctionDef {
    char _;
} FunctionDef;


typedef struct Dynamic {
    char _;
} Dynamic;









typedef struct Range {
    U64 start;
    U64 end;
} Range;




typedef struct Map {
    U8 *key_data;
    U8 *val_data;
    U64 count;
    U64 cap;
    U64 key_size;
    Str key_type;
    U64 val_size;
    Str val_type;
} Map;


typedef struct Set {
    U8 *data;
    U64 count;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Set;



typedef struct Vec {
    U8 *data;
    U64 count;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Vec;


struct TokenType {
    TokenType_tag tag;
};

typedef struct Token {
    TokenType type;
    Str text;
    I64 line;
    I64 col;
} Token;


#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
__attribute__((unused))
#define TIL_CAP_LIT ULLONG_MAX
static Str *Str_lit(const char *s, unsigned long long len) {
    Str *r = malloc(sizeof(Str));
    r->c_str = (U8 *)s;
    r->count = len;
    r->cap = TIL_CAP_LIT;
    return r;
}
__attribute__((unused))
static void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
__attribute__((unused))
static void print_flush() {
    putchar('\n');
}

static I64 *_t2002;
static I64 *_t2003;
static I64 *_t2004;
static U64 *CAP_LIT;
static I64 *_t2005;
static I64 *_t2006;
static I64 *_t2007;
static U64 *CAP_VIEW;

EnumDef * EnumDef_clone(EnumDef * self) {
    (void)self;
    EnumDef *_t0 = malloc(sizeof(EnumDef));
    return _t0;
}

void EnumDef_delete(EnumDef * self, Bool * call_free) {
    (void)self;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *EnumDef_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(EnumDef);
    return r;
}

static __attribute__((unused)) Str * U8_to_str(U8 * val) {
    I64 *_t2 = malloc(sizeof(I64)); *_t2 = U8_to_i64(DEREF(val));
    Str *_t3 = I64_to_str(_t2);
    I64_delete(_t2, &(Bool){1});
    return _t3;
}

static __attribute__((unused)) U8 * U8_from_i64(I64 * val) {
    I64 *_t10 = malloc(sizeof(I64));
    *_t10 = 0;
    I64 *_t11 = malloc(sizeof(I64));
    *_t11 = 255;
    Bool *_t12 = I64_lt(val, _t10);
    I64_delete(_t10, &(Bool){1});
    Bool *_t13 = I64_gt(val, _t11);
    I64_delete(_t11, &(Bool){1});
    Bool *_t14 = malloc(sizeof(Bool)); *_t14 = Bool_or(DEREF(_t12), DEREF(_t13));
    Bool_delete(_t12, &(Bool){1});
    Bool_delete(_t13, &(Bool){1});
    if (DEREF(_t14)) {
        Str *_t4 = Str_lit("Str", 3ULL);
        U64 *_t5 = Str_size();
        U64 *_t6 = malloc(sizeof(U64));
        *_t6 = 1;
        Array *_va0 = Array_new(_t4, _t5, _t6);
        Str_delete(_t4, &(Bool){1});
        U64_delete(_t5, &(Bool){1});
        U64_delete(_t6, &(Bool){1});
        U64 *_t7 = malloc(sizeof(U64));
        *_t7 = 0;
        Str *_t8 = Str_lit("value out of range (0-255)", 26ULL);
        Array_set(_va0, _t7, _t8);
        U64_delete(_t7, &(Bool){1});
        Str *_t9 = Str_lit("U8.from_i64", 11ULL);
        panic(_t9, _va0);
        Str_delete(_t9, &(Bool){1});
        Array_delete(_va0, &(Bool){1});
    }
    Bool_delete(_t14, &(Bool){1});
    /* TODO: nested func U8_from_i64_ext */
    U8 *_t15 = U8_from_i64_ext(val);
    return _t15;
}

static U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b) {
    I64 *_t17 = malloc(sizeof(I64));
    *_t17 = 0;
    I64 *_t18 = malloc(sizeof(I64));
    *_t18 = 1;
    I64 *_t19 = malloc(sizeof(I64)); *_t19 = U8_cmp(DEREF(a), DEREF(b));
    I64 *_t20 = malloc(sizeof(I64)); *_t20 = I64_sub(DEREF(_t17), DEREF(_t18));
    I64_delete(_t17, &(Bool){1});
    I64_delete(_t18, &(Bool){1});
    Bool *_t21 = malloc(sizeof(Bool)); *_t21 = I64_eq(DEREF(_t19), DEREF(_t20));
    I64_delete(_t19, &(Bool){1});
    I64_delete(_t20, &(Bool){1});
    return _t21;
}

static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b) {
    I64 *_t22 = malloc(sizeof(I64)); *_t22 = U8_cmp(DEREF(a), DEREF(b));
    I64 *_t23 = malloc(sizeof(I64));
    *_t23 = 1;
    Bool *_t24 = malloc(sizeof(Bool)); *_t24 = I64_eq(DEREF(_t22), DEREF(_t23));
    I64_delete(_t22, &(Bool){1});
    I64_delete(_t23, &(Bool){1});
    return _t24;
}

static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b) {
    Bool *_t25 = malloc(sizeof(Bool)); *_t25 = U8_eq(DEREF(a), DEREF(b));
    Bool *_t26 = malloc(sizeof(Bool)); *_t26 = Bool_not(DEREF(_t25));
    Bool_delete(_t25, &(Bool){1});
    return _t26;
}

static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b) {
    Bool *_t27 = U8_gt(a, b);
    Bool *_t28 = malloc(sizeof(Bool)); *_t28 = Bool_not(DEREF(_t27));
    Bool_delete(_t27, &(Bool){1});
    return _t28;
}

static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b) {
    Bool *_t29 = U8_lt(a, b);
    Bool *_t30 = malloc(sizeof(Bool)); *_t30 = Bool_not(DEREF(_t29));
    Bool_delete(_t29, &(Bool){1});
    return _t30;
}

static __attribute__((unused)) Str * I16_to_str(I16 * val) {
    I64 *_t31 = malloc(sizeof(I64)); *_t31 = I16_to_i64(DEREF(val));
    Str *_t32 = I64_to_str(_t31);
    I64_delete(_t31, &(Bool){1});
    return _t32;
}

static __attribute__((unused)) I16 * I16_from_i64(I64 * val) {
    I64 *_t39 = malloc(sizeof(I64));
    *_t39 = 32768;
    I64 *_t40 = I64_neg(_t39);
    I64_delete(_t39, &(Bool){1});
    I64 *_t41 = malloc(sizeof(I64));
    *_t41 = 32767;
    Bool *_t42 = I64_lt(val, _t40);
    I64_delete(_t40, &(Bool){1});
    Bool *_t43 = I64_gt(val, _t41);
    I64_delete(_t41, &(Bool){1});
    Bool *_t44 = malloc(sizeof(Bool)); *_t44 = Bool_or(DEREF(_t42), DEREF(_t43));
    Bool_delete(_t42, &(Bool){1});
    Bool_delete(_t43, &(Bool){1});
    if (DEREF(_t44)) {
        Str *_t33 = Str_lit("Str", 3ULL);
        U64 *_t34 = Str_size();
        U64 *_t35 = malloc(sizeof(U64));
        *_t35 = 1;
        Array *_va1 = Array_new(_t33, _t34, _t35);
        Str_delete(_t33, &(Bool){1});
        U64_delete(_t34, &(Bool){1});
        U64_delete(_t35, &(Bool){1});
        U64 *_t36 = malloc(sizeof(U64));
        *_t36 = 0;
        Str *_t37 = Str_lit("value out of range (-32768 to 32767)", 36ULL);
        Array_set(_va1, _t36, _t37);
        U64_delete(_t36, &(Bool){1});
        Str *_t38 = Str_lit("I16.from_i64", 12ULL);
        panic(_t38, _va1);
        Str_delete(_t38, &(Bool){1});
        Array_delete(_va1, &(Bool){1});
    }
    Bool_delete(_t44, &(Bool){1});
    /* TODO: nested func I16_from_i64_ext */
    I16 *_t45 = I16_from_i64_ext(val);
    return _t45;
}

static __attribute__((unused)) I16 * I16_neg(I16 * a) {
    I64 *_t46 = malloc(sizeof(I64));
    *_t46 = 0;
    I64 *_t47 = malloc(sizeof(I64)); *_t47 = I16_to_i64(DEREF(a));
    I64 *_t48 = malloc(sizeof(I64)); *_t48 = I64_sub(DEREF(_t46), DEREF(_t47));
    I64_delete(_t46, &(Bool){1});
    I64_delete(_t47, &(Bool){1});
    I16 *_t49 = I16_from_i64(_t48);
    I64_delete(_t48, &(Bool){1});
    return _t49;
}

static __attribute__((unused)) I16 * I16_abs(I16 * a) {
    I64 *_t54 = malloc(sizeof(I64)); *_t54 = I16_to_i64(DEREF(a));
    I64 *_t55 = malloc(sizeof(I64));
    *_t55 = 0;
    Bool *_t56 = I64_lt(_t54, _t55);
    I64_delete(_t54, &(Bool){1});
    I64_delete(_t55, &(Bool){1});
    if (DEREF(_t56)) {
        I64 *_t50 = malloc(sizeof(I64));
        *_t50 = 0;
        I64 *_t51 = malloc(sizeof(I64)); *_t51 = I16_to_i64(DEREF(a));
        I64 *_t52 = malloc(sizeof(I64)); *_t52 = I64_sub(DEREF(_t50), DEREF(_t51));
        I64_delete(_t50, &(Bool){1});
        I64_delete(_t51, &(Bool){1});
        I16 *_t53 = I16_from_i64(_t52);
        I64_delete(_t52, &(Bool){1});
        Bool_delete(_t56, &(Bool){1});
        return _t53;
    }
    Bool_delete(_t56, &(Bool){1});
    I16 *_t57 = I16_clone(a);
    return _t57;
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b) {
    I64 *_t59 = malloc(sizeof(I64));
    *_t59 = 0;
    I64 *_t60 = malloc(sizeof(I64));
    *_t60 = 1;
    I64 *_t61 = malloc(sizeof(I64)); *_t61 = I16_cmp(DEREF(a), DEREF(b));
    I64 *_t62 = malloc(sizeof(I64)); *_t62 = I64_sub(DEREF(_t59), DEREF(_t60));
    I64_delete(_t59, &(Bool){1});
    I64_delete(_t60, &(Bool){1});
    Bool *_t63 = malloc(sizeof(Bool)); *_t63 = I64_eq(DEREF(_t61), DEREF(_t62));
    I64_delete(_t61, &(Bool){1});
    I64_delete(_t62, &(Bool){1});
    return _t63;
}

static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b) {
    I64 *_t64 = malloc(sizeof(I64)); *_t64 = I16_cmp(DEREF(a), DEREF(b));
    I64 *_t65 = malloc(sizeof(I64));
    *_t65 = 1;
    Bool *_t66 = malloc(sizeof(Bool)); *_t66 = I64_eq(DEREF(_t64), DEREF(_t65));
    I64_delete(_t64, &(Bool){1});
    I64_delete(_t65, &(Bool){1});
    return _t66;
}

static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b) {
    Bool *_t67 = malloc(sizeof(Bool)); *_t67 = I16_eq(DEREF(a), DEREF(b));
    Bool *_t68 = malloc(sizeof(Bool)); *_t68 = Bool_not(DEREF(_t67));
    Bool_delete(_t67, &(Bool){1});
    return _t68;
}

static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b) {
    Bool *_t69 = I16_gt(a, b);
    Bool *_t70 = malloc(sizeof(Bool)); *_t70 = Bool_not(DEREF(_t69));
    Bool_delete(_t69, &(Bool){1});
    return _t70;
}

static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b) {
    Bool *_t71 = I16_lt(a, b);
    Bool *_t72 = malloc(sizeof(Bool)); *_t72 = Bool_not(DEREF(_t71));
    Bool_delete(_t71, &(Bool){1});
    return _t72;
}

static __attribute__((unused)) Str * I32_to_str(I32 * val) {
    I64 *_t73 = malloc(sizeof(I64)); *_t73 = I32_to_i64(DEREF(val));
    Str *_t74 = I64_to_str(_t73);
    I64_delete(_t73, &(Bool){1});
    return _t74;
}

static __attribute__((unused)) I32 * I32_from_i64(I64 * val) {
    I64 *_t81 = malloc(sizeof(I64));
    *_t81 = 2147483648;
    I64 *_t82 = I64_neg(_t81);
    I64_delete(_t81, &(Bool){1});
    I64 *_t83 = malloc(sizeof(I64));
    *_t83 = 2147483647;
    Bool *_t84 = I64_lt(val, _t82);
    I64_delete(_t82, &(Bool){1});
    Bool *_t85 = I64_gt(val, _t83);
    I64_delete(_t83, &(Bool){1});
    Bool *_t86 = malloc(sizeof(Bool)); *_t86 = Bool_or(DEREF(_t84), DEREF(_t85));
    Bool_delete(_t84, &(Bool){1});
    Bool_delete(_t85, &(Bool){1});
    if (DEREF(_t86)) {
        Str *_t75 = Str_lit("Str", 3ULL);
        U64 *_t76 = Str_size();
        U64 *_t77 = malloc(sizeof(U64));
        *_t77 = 1;
        Array *_va2 = Array_new(_t75, _t76, _t77);
        Str_delete(_t75, &(Bool){1});
        U64_delete(_t76, &(Bool){1});
        U64_delete(_t77, &(Bool){1});
        U64 *_t78 = malloc(sizeof(U64));
        *_t78 = 0;
        Str *_t79 = Str_lit("value out of range (-2147483648 to 2147483647)", 46ULL);
        Array_set(_va2, _t78, _t79);
        U64_delete(_t78, &(Bool){1});
        Str *_t80 = Str_lit("I32.from_i64", 12ULL);
        panic(_t80, _va2);
        Str_delete(_t80, &(Bool){1});
        Array_delete(_va2, &(Bool){1});
    }
    Bool_delete(_t86, &(Bool){1});
    /* TODO: nested func I32_from_i64_ext */
    I32 *_t87 = I32_from_i64_ext(val);
    return _t87;
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    I64 *_t88 = malloc(sizeof(I64));
    *_t88 = 0;
    I64 *_t89 = malloc(sizeof(I64)); *_t89 = I32_to_i64(DEREF(a));
    I64 *_t90 = malloc(sizeof(I64)); *_t90 = I64_sub(DEREF(_t88), DEREF(_t89));
    I64_delete(_t88, &(Bool){1});
    I64_delete(_t89, &(Bool){1});
    I32 *_t91 = I32_from_i64(_t90);
    I64_delete(_t90, &(Bool){1});
    return _t91;
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    I64 *_t96 = malloc(sizeof(I64)); *_t96 = I32_to_i64(DEREF(a));
    I64 *_t97 = malloc(sizeof(I64));
    *_t97 = 0;
    Bool *_t98 = I64_lt(_t96, _t97);
    I64_delete(_t96, &(Bool){1});
    I64_delete(_t97, &(Bool){1});
    if (DEREF(_t98)) {
        I64 *_t92 = malloc(sizeof(I64));
        *_t92 = 0;
        I64 *_t93 = malloc(sizeof(I64)); *_t93 = I32_to_i64(DEREF(a));
        I64 *_t94 = malloc(sizeof(I64)); *_t94 = I64_sub(DEREF(_t92), DEREF(_t93));
        I64_delete(_t92, &(Bool){1});
        I64_delete(_t93, &(Bool){1});
        I32 *_t95 = I32_from_i64(_t94);
        I64_delete(_t94, &(Bool){1});
        Bool_delete(_t98, &(Bool){1});
        return _t95;
    }
    Bool_delete(_t98, &(Bool){1});
    I32 *_t99 = I32_clone(a);
    return _t99;
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    I64 *_t101 = malloc(sizeof(I64));
    *_t101 = 0;
    I64 *_t102 = malloc(sizeof(I64));
    *_t102 = 1;
    I64 *_t103 = malloc(sizeof(I64)); *_t103 = I32_cmp(DEREF(a), DEREF(b));
    I64 *_t104 = malloc(sizeof(I64)); *_t104 = I64_sub(DEREF(_t101), DEREF(_t102));
    I64_delete(_t101, &(Bool){1});
    I64_delete(_t102, &(Bool){1});
    Bool *_t105 = malloc(sizeof(Bool)); *_t105 = I64_eq(DEREF(_t103), DEREF(_t104));
    I64_delete(_t103, &(Bool){1});
    I64_delete(_t104, &(Bool){1});
    return _t105;
}

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    I64 *_t106 = malloc(sizeof(I64)); *_t106 = I32_cmp(DEREF(a), DEREF(b));
    I64 *_t107 = malloc(sizeof(I64));
    *_t107 = 1;
    Bool *_t108 = malloc(sizeof(Bool)); *_t108 = I64_eq(DEREF(_t106), DEREF(_t107));
    I64_delete(_t106, &(Bool){1});
    I64_delete(_t107, &(Bool){1});
    return _t108;
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    Bool *_t109 = malloc(sizeof(Bool)); *_t109 = I32_eq(DEREF(a), DEREF(b));
    Bool *_t110 = malloc(sizeof(Bool)); *_t110 = Bool_not(DEREF(_t109));
    Bool_delete(_t109, &(Bool){1});
    return _t110;
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    Bool *_t111 = I32_gt(a, b);
    Bool *_t112 = malloc(sizeof(Bool)); *_t112 = Bool_not(DEREF(_t111));
    Bool_delete(_t111, &(Bool){1});
    return _t112;
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    Bool *_t113 = I32_lt(a, b);
    Bool *_t114 = malloc(sizeof(Bool)); *_t114 = Bool_not(DEREF(_t113));
    Bool_delete(_t113, &(Bool){1});
    return _t114;
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 *_t115 = F32_from_i64_ext(val);
    return _t115;
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    I64 *_t117 = malloc(sizeof(I64));
    *_t117 = 0;
    I64 *_t118 = malloc(sizeof(I64));
    *_t118 = 1;
    I64 *_t119 = malloc(sizeof(I64)); *_t119 = F32_cmp(DEREF(a), DEREF(b));
    I64 *_t120 = malloc(sizeof(I64)); *_t120 = I64_sub(DEREF(_t117), DEREF(_t118));
    I64_delete(_t117, &(Bool){1});
    I64_delete(_t118, &(Bool){1});
    Bool *_t121 = malloc(sizeof(Bool)); *_t121 = I64_eq(DEREF(_t119), DEREF(_t120));
    I64_delete(_t119, &(Bool){1});
    I64_delete(_t120, &(Bool){1});
    return _t121;
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    I64 *_t122 = malloc(sizeof(I64)); *_t122 = F32_cmp(DEREF(a), DEREF(b));
    I64 *_t123 = malloc(sizeof(I64));
    *_t123 = 1;
    Bool *_t124 = malloc(sizeof(Bool)); *_t124 = I64_eq(DEREF(_t122), DEREF(_t123));
    I64_delete(_t122, &(Bool){1});
    I64_delete(_t123, &(Bool){1});
    return _t124;
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    Bool *_t125 = malloc(sizeof(Bool)); *_t125 = F32_eq(DEREF(a), DEREF(b));
    Bool *_t126 = malloc(sizeof(Bool)); *_t126 = Bool_not(DEREF(_t125));
    Bool_delete(_t125, &(Bool){1});
    return _t126;
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    Bool *_t127 = F32_gt(a, b);
    Bool *_t128 = malloc(sizeof(Bool)); *_t128 = Bool_not(DEREF(_t127));
    Bool_delete(_t127, &(Bool){1});
    return _t128;
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    Bool *_t129 = F32_lt(a, b);
    Bool *_t130 = malloc(sizeof(Bool)); *_t130 = Bool_not(DEREF(_t129));
    Bool_delete(_t129, &(Bool){1});
    return _t130;
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    I64 *_t131 = malloc(sizeof(I64)); *_t131 = U32_to_i64(DEREF(val));
    Str *_t132 = I64_to_str(_t131);
    I64_delete(_t131, &(Bool){1});
    return _t132;
}

static __attribute__((unused)) U32 * U32_from_i64(I64 * val) {
    I64 *_t139 = malloc(sizeof(I64));
    *_t139 = 0;
    I64 *_t140 = malloc(sizeof(I64));
    *_t140 = 4294967295;
    Bool *_t141 = I64_lt(val, _t139);
    I64_delete(_t139, &(Bool){1});
    Bool *_t142 = I64_gt(val, _t140);
    I64_delete(_t140, &(Bool){1});
    Bool *_t143 = malloc(sizeof(Bool)); *_t143 = Bool_or(DEREF(_t141), DEREF(_t142));
    Bool_delete(_t141, &(Bool){1});
    Bool_delete(_t142, &(Bool){1});
    if (DEREF(_t143)) {
        Str *_t133 = Str_lit("Str", 3ULL);
        U64 *_t134 = Str_size();
        U64 *_t135 = malloc(sizeof(U64));
        *_t135 = 1;
        Array *_va3 = Array_new(_t133, _t134, _t135);
        Str_delete(_t133, &(Bool){1});
        U64_delete(_t134, &(Bool){1});
        U64_delete(_t135, &(Bool){1});
        U64 *_t136 = malloc(sizeof(U64));
        *_t136 = 0;
        Str *_t137 = Str_lit("value out of range (0-4294967295)", 33ULL);
        Array_set(_va3, _t136, _t137);
        U64_delete(_t136, &(Bool){1});
        Str *_t138 = Str_lit("U32.from_i64", 12ULL);
        panic(_t138, _va3);
        Str_delete(_t138, &(Bool){1});
        Array_delete(_va3, &(Bool){1});
    }
    Bool_delete(_t143, &(Bool){1});
    /* TODO: nested func U32_from_i64_ext */
    U32 *_t144 = U32_from_i64_ext(val);
    return _t144;
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    I64 *_t146 = malloc(sizeof(I64));
    *_t146 = 0;
    I64 *_t147 = malloc(sizeof(I64));
    *_t147 = 1;
    I64 *_t148 = malloc(sizeof(I64)); *_t148 = U32_cmp(DEREF(a), DEREF(b));
    I64 *_t149 = malloc(sizeof(I64)); *_t149 = I64_sub(DEREF(_t146), DEREF(_t147));
    I64_delete(_t146, &(Bool){1});
    I64_delete(_t147, &(Bool){1});
    Bool *_t150 = malloc(sizeof(Bool)); *_t150 = I64_eq(DEREF(_t148), DEREF(_t149));
    I64_delete(_t148, &(Bool){1});
    I64_delete(_t149, &(Bool){1});
    return _t150;
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    I64 *_t151 = malloc(sizeof(I64)); *_t151 = U32_cmp(DEREF(a), DEREF(b));
    I64 *_t152 = malloc(sizeof(I64));
    *_t152 = 1;
    Bool *_t153 = malloc(sizeof(Bool)); *_t153 = I64_eq(DEREF(_t151), DEREF(_t152));
    I64_delete(_t151, &(Bool){1});
    I64_delete(_t152, &(Bool){1});
    return _t153;
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    Bool *_t154 = malloc(sizeof(Bool)); *_t154 = U32_eq(DEREF(a), DEREF(b));
    Bool *_t155 = malloc(sizeof(Bool)); *_t155 = Bool_not(DEREF(_t154));
    Bool_delete(_t154, &(Bool){1});
    return _t155;
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    Bool *_t156 = U32_gt(a, b);
    Bool *_t157 = malloc(sizeof(Bool)); *_t157 = Bool_not(DEREF(_t156));
    Bool_delete(_t156, &(Bool){1});
    return _t157;
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    Bool *_t158 = U32_lt(a, b);
    Bool *_t159 = malloc(sizeof(Bool)); *_t159 = Bool_not(DEREF(_t158));
    Bool_delete(_t158, &(Bool){1});
    return _t159;
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t160 = U64_to_str_ext(&(U64){val});
    return _t160;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 *_t161 = U64_from_i64_ext(val);
    return _t161;
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    I64 *_t163 = malloc(sizeof(I64));
    *_t163 = 0;
    I64 *_t164 = malloc(sizeof(I64));
    *_t164 = 1;
    I64 *_t165 = malloc(sizeof(I64)); *_t165 = U64_cmp(DEREF(a), DEREF(b));
    I64 *_t166 = malloc(sizeof(I64)); *_t166 = I64_sub(DEREF(_t163), DEREF(_t164));
    I64_delete(_t163, &(Bool){1});
    I64_delete(_t164, &(Bool){1});
    Bool *_t167 = malloc(sizeof(Bool)); *_t167 = I64_eq(DEREF(_t165), DEREF(_t166));
    I64_delete(_t165, &(Bool){1});
    I64_delete(_t166, &(Bool){1});
    return _t167;
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    I64 *_t168 = malloc(sizeof(I64)); *_t168 = U64_cmp(DEREF(a), DEREF(b));
    I64 *_t169 = malloc(sizeof(I64));
    *_t169 = 1;
    Bool *_t170 = malloc(sizeof(Bool)); *_t170 = I64_eq(DEREF(_t168), DEREF(_t169));
    I64_delete(_t168, &(Bool){1});
    I64_delete(_t169, &(Bool){1});
    return _t170;
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    Bool *_t171 = malloc(sizeof(Bool)); *_t171 = U64_eq(DEREF(a), DEREF(b));
    Bool *_t172 = malloc(sizeof(Bool)); *_t172 = Bool_not(DEREF(_t171));
    Bool_delete(_t171, &(Bool){1});
    return _t172;
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    Bool *_t173 = U64_gt(a, b);
    Bool *_t174 = malloc(sizeof(Bool)); *_t174 = Bool_not(DEREF(_t173));
    Bool_delete(_t173, &(Bool){1});
    return _t174;
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    Bool *_t175 = U64_lt(a, b);
    Bool *_t176 = malloc(sizeof(Bool)); *_t176 = Bool_not(DEREF(_t175));
    Bool_delete(_t175, &(Bool){1});
    return _t176;
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    I64 *_t216 = malloc(sizeof(I64));
    *_t216 = 0;
    Bool *_t217 = malloc(sizeof(Bool)); *_t217 = I64_eq(DEREF(val), DEREF(_t216));
    I64_delete(_t216, &(Bool){1});
    if (DEREF(_t217)) {
        U64 *_t177 = malloc(sizeof(U64));
        *_t177 = 2;
        U8 *buf = malloc(DEREF(_t177));
        U64_delete(_t177, &(Bool){1});
        I64 *_t178 = malloc(sizeof(I64));
        *_t178 = 48;
        U8 *_t179 = U8_from_i64(_t178);
        I64_delete(_t178, &(Bool){1});
        U64 *_t180 = malloc(sizeof(U64));
        *_t180 = 1;
        memcpy(buf, _t179, DEREF(_t180));
        U8_delete(_t179, &(Bool){1});
        U64_delete(_t180, &(Bool){1});
        U64 *_t181 = malloc(sizeof(U64));
        *_t181 = 1;
        I64 *_t182 = malloc(sizeof(I64));
        *_t182 = 0;
        void *_t183 = ptr_add(buf, DEREF(_t181));
        U8 *_t184 = U8_from_i64(_t182);
        I64_delete(_t182, &(Bool){1});
        U64 *_t185 = malloc(sizeof(U64));
        *_t185 = 1;
        memcpy(_t183, _t184, DEREF(_t185));
        U64_delete(_t181, &(Bool){1});
        U8_delete(_t184, &(Bool){1});
        U64_delete(_t185, &(Bool){1});
        I64 *_t186 = malloc(sizeof(I64));
        *_t186 = 1;
        I64 *_t187 = malloc(sizeof(I64));
        *_t187 = 1;
        Str *_t188 = malloc(sizeof(Str));
        _t188->c_str = buf;
        _t188->count = DEREF(_t186);
        _t188->cap = DEREF(_t187);
        I64_delete(_t186, &(Bool){1});
        I64_delete(_t187, &(Bool){1});
        Bool_delete(_t217, &(Bool){1});
        return _t188;
    }
    Bool_delete(_t217, &(Bool){1});
    Bool *is_neg = malloc(sizeof(Bool));
    *is_neg = 0;
    I64 *v = I64_clone(val);
    I64 *_t218 = malloc(sizeof(I64));
    *_t218 = 0;
    Bool *_t219 = I64_lt(val, _t218);
    I64_delete(_t218, &(Bool){1});
    if (DEREF(_t219)) {
        Bool *_t189 = malloc(sizeof(Bool));
        *_t189 = 1;
        *is_neg = DEREF(_t189);
        Bool_delete(_t189, &(Bool){1});
        I64 *_t190 = malloc(sizeof(I64));
        *_t190 = 0;
        I64 *_t191 = malloc(sizeof(I64)); *_t191 = I64_sub(DEREF(_t190), DEREF(val));
        I64_delete(_t190, &(Bool){1});
        *v = DEREF(_t191);
        I64_delete(_t191, &(Bool){1});
    }
    Bool_delete(_t219, &(Bool){1});
    U64 *ndigits = malloc(sizeof(U64));
    *ndigits = 0;
    I64 *tmp = I64_clone(v);
    while (1) {
        I64 *_t193 = malloc(sizeof(I64));
        *_t193 = 0;
        Bool *_wcond192 = I64_gt(tmp, _t193);
        I64_delete(_t193, &(Bool){1});
        if (DEREF(_wcond192)) {
        } else {
            Bool_delete(_wcond192, &(Bool){1});
            break;
        }
        Bool_delete(_wcond192, &(Bool){1});
        U64 *_t194 = malloc(sizeof(U64));
        *_t194 = 1;
        U64 *_t195 = malloc(sizeof(U64)); *_t195 = U64_add(DEREF(ndigits), DEREF(_t194));
        U64_delete(_t194, &(Bool){1});
        *ndigits = DEREF(_t195);
        U64_delete(_t195, &(Bool){1});
        I64 *_t196 = malloc(sizeof(I64));
        *_t196 = 10;
        I64 *_t197 = malloc(sizeof(I64)); *_t197 = I64_div(DEREF(tmp), DEREF(_t196));
        I64_delete(_t196, &(Bool){1});
        *tmp = DEREF(_t197);
        I64_delete(_t197, &(Bool){1});
    }
    I64_delete(tmp, &(Bool){1});
    U64 *total = U64_clone(ndigits);
    U64_delete(ndigits, &(Bool){1});
    if (DEREF(is_neg)) {
        U64 *_t198 = malloc(sizeof(U64));
        *_t198 = 1;
        U64 *_t199 = malloc(sizeof(U64)); *_t199 = U64_add(DEREF(total), DEREF(_t198));
        U64_delete(_t198, &(Bool){1});
        *total = DEREF(_t199);
        U64_delete(_t199, &(Bool){1});
    }
    U64 *_t220 = malloc(sizeof(U64));
    *_t220 = 1;
    U64 *_t221 = malloc(sizeof(U64)); *_t221 = U64_add(DEREF(total), DEREF(_t220));
    U64_delete(_t220, &(Bool){1});
    U8 *buf = malloc(DEREF(_t221));
    U64_delete(_t221, &(Bool){1});
    if (DEREF(is_neg)) {
        I64 *_t200 = malloc(sizeof(I64));
        *_t200 = 45;
        U8 *_t201 = U8_from_i64(_t200);
        I64_delete(_t200, &(Bool){1});
        U64 *_t202 = malloc(sizeof(U64));
        *_t202 = 1;
        memcpy(buf, _t201, DEREF(_t202));
        U8_delete(_t201, &(Bool){1});
        U64_delete(_t202, &(Bool){1});
    }
    Bool_delete(is_neg, &(Bool){1});
    U64 *_t222 = malloc(sizeof(U64));
    *_t222 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), DEREF(_t222));
    U64_delete(_t222, &(Bool){1});
    while (1) {
        I64 *_t204 = malloc(sizeof(I64));
        *_t204 = 0;
        Bool *_wcond203 = I64_gt(v, _t204);
        I64_delete(_t204, &(Bool){1});
        if (DEREF(_wcond203)) {
        } else {
            Bool_delete(_wcond203, &(Bool){1});
            break;
        }
        Bool_delete(_wcond203, &(Bool){1});
        I64 *_t205 = malloc(sizeof(I64));
        *_t205 = 10;
        I64 *_t206 = malloc(sizeof(I64)); *_t206 = I64_mod(DEREF(v), DEREF(_t205));
        I64_delete(_t205, &(Bool){1});
        I64 *_t207 = malloc(sizeof(I64));
        *_t207 = 48;
        I64 *_t208 = malloc(sizeof(I64)); *_t208 = I64_add(DEREF(_t206), DEREF(_t207));
        I64_delete(_t206, &(Bool){1});
        I64_delete(_t207, &(Bool){1});
        void *_t209 = ptr_add(buf, DEREF(i));
        U8 *_t210 = U8_from_i64(_t208);
        I64_delete(_t208, &(Bool){1});
        U64 *_t211 = malloc(sizeof(U64));
        *_t211 = 1;
        memcpy(_t209, _t210, DEREF(_t211));
        U8_delete(_t210, &(Bool){1});
        U64_delete(_t211, &(Bool){1});
        I64 *_t212 = malloc(sizeof(I64));
        *_t212 = 10;
        I64 *_t213 = malloc(sizeof(I64)); *_t213 = I64_div(DEREF(v), DEREF(_t212));
        I64_delete(_t212, &(Bool){1});
        *v = DEREF(_t213);
        I64_delete(_t213, &(Bool){1});
        U64 *_t214 = malloc(sizeof(U64));
        *_t214 = 1;
        U64 *_t215 = malloc(sizeof(U64)); *_t215 = U64_sub(DEREF(i), DEREF(_t214));
        U64_delete(_t214, &(Bool){1});
        *i = DEREF(_t215);
        U64_delete(_t215, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    I64_delete(v, &(Bool){1});
    I64 *_t223 = malloc(sizeof(I64));
    *_t223 = 0;
    void *_t224 = ptr_add(buf, DEREF(total));
    U8 *_t225 = U8_from_i64(_t223);
    I64_delete(_t223, &(Bool){1});
    U64 *_t226 = malloc(sizeof(U64));
    *_t226 = 1;
    memcpy(_t224, _t225, DEREF(_t226));
    U8_delete(_t225, &(Bool){1});
    U64_delete(_t226, &(Bool){1});
    U64 *_t227 = U64_clone(total);
    U64 *_t228 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t229 = malloc(sizeof(Str));
    _t229->c_str = buf;
    _t229->count = DEREF(_t227);
    _t229->cap = DEREF(_t228);
    U64_delete(_t227, &(Bool){1});
    U64_delete(_t228, &(Bool){1});
    return _t229;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    I64 *_t230 = malloc(sizeof(I64));
    *_t230 = 0;
    I64 *_t231 = malloc(sizeof(I64)); *_t231 = I64_sub(DEREF(_t230), DEREF(a));
    I64_delete(_t230, &(Bool){1});
    return _t231;
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    I64 *_t234 = malloc(sizeof(I64));
    *_t234 = 0;
    Bool *_t235 = I64_lt(a, _t234);
    I64_delete(_t234, &(Bool){1});
    if (DEREF(_t235)) {
        I64 *_t232 = malloc(sizeof(I64));
        *_t232 = 0;
        I64 *_t233 = malloc(sizeof(I64)); *_t233 = I64_sub(DEREF(_t232), DEREF(a));
        I64_delete(_t232, &(Bool){1});
        Bool_delete(_t235, &(Bool){1});
        return _t233;
    }
    Bool_delete(_t235, &(Bool){1});
    I64 *_t236 = I64_clone(a);
    return _t236;
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    I64 *_t238 = malloc(sizeof(I64));
    *_t238 = 0;
    I64 *_t239 = malloc(sizeof(I64));
    *_t239 = 1;
    I64 *_t240 = malloc(sizeof(I64)); *_t240 = I64_cmp(DEREF(a), DEREF(b));
    I64 *_t241 = malloc(sizeof(I64)); *_t241 = I64_sub(DEREF(_t238), DEREF(_t239));
    I64_delete(_t238, &(Bool){1});
    I64_delete(_t239, &(Bool){1});
    Bool *_t242 = malloc(sizeof(Bool)); *_t242 = I64_eq(DEREF(_t240), DEREF(_t241));
    I64_delete(_t240, &(Bool){1});
    I64_delete(_t241, &(Bool){1});
    return _t242;
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    I64 *_t243 = malloc(sizeof(I64)); *_t243 = I64_cmp(DEREF(a), DEREF(b));
    I64 *_t244 = malloc(sizeof(I64));
    *_t244 = 1;
    Bool *_t245 = malloc(sizeof(Bool)); *_t245 = I64_eq(DEREF(_t243), DEREF(_t244));
    I64_delete(_t243, &(Bool){1});
    I64_delete(_t244, &(Bool){1});
    return _t245;
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    Bool *_t246 = malloc(sizeof(Bool)); *_t246 = I64_eq(DEREF(a), DEREF(b));
    Bool *_t247 = malloc(sizeof(Bool)); *_t247 = Bool_not(DEREF(_t246));
    Bool_delete(_t246, &(Bool){1});
    return _t247;
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    Bool *_t248 = I64_gt(a, b);
    Bool *_t249 = malloc(sizeof(Bool)); *_t249 = Bool_not(DEREF(_t248));
    Bool_delete(_t248, &(Bool){1});
    return _t249;
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    Bool *_t250 = I64_lt(a, b);
    Bool *_t251 = malloc(sizeof(Bool)); *_t251 = Bool_not(DEREF(_t250));
    Bool_delete(_t250, &(Bool){1});
    return _t251;
}

Range * Range_new(U64 start, U64 end) {
    U64 *_t252 = U64_clone(&(U64){start});
    U64 *_t253 = U64_clone(&(U64){end});
    Range *_t254 = malloc(sizeof(Range));
    _t254->start = DEREF(_t252);
    _t254->end = DEREF(_t253);
    U64_delete(_t252, &(Bool){1});
    U64_delete(_t253, &(Bool){1});
    return _t254;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool *_t256 = U64_lte(&self->start, &self->end);
    if (DEREF(_t256)) {
        U64 *_t255 = malloc(sizeof(U64)); *_t255 = U64_sub(self->end, self->start);
        Bool_delete(_t256, &(Bool){1});
        return _t255;
    }
    Bool_delete(_t256, &(Bool){1});
    U64 *_t257 = malloc(sizeof(U64)); *_t257 = U64_sub(self->start, self->end);
    return _t257;
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    Bool *_t259 = U64_lte(&self->start, &self->end);
    if (DEREF(_t259)) {
        U64 *_t258 = malloc(sizeof(U64)); *_t258 = U64_add(self->start, i);
        Bool_delete(_t259, &(Bool){1});
        return _t258;
    }
    Bool_delete(_t259, &(Bool){1});
    U64 *_t260 = malloc(sizeof(U64)); *_t260 = U64_sub(self->start, i);
    return _t260;
}

Range * Range_clone(Range * val) {
    Range *_t261 = malloc(sizeof(Range));
    _t261->start = val->start;
    _t261->end = val->end;
    return _t261;
}

void Range_delete(Range * self, Bool * call_free) {
    (void)self;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Range_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Range);
    return r;
}

static __attribute__((unused)) Str * Bool_to_str(Bool * b) {
    if (DEREF(b)) {
        Str *_t263 = Str_lit("true", 4ULL);
        return _t263;
    } else {
        Str *_t264 = Str_lit("false", 5ULL);
        return _t264;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool *_t269 = malloc(sizeof(Bool)); *_t269 = Bool_eq(DEREF(a), DEREF(b));
    if (DEREF(_t269)) {
        I64 *_t265 = malloc(sizeof(I64));
        *_t265 = 0;
        Bool_delete(_t269, &(Bool){1});
        return _t265;
    }
    Bool_delete(_t269, &(Bool){1});
    if (DEREF(b)) {
        I64 *_t266 = malloc(sizeof(I64));
        *_t266 = 0;
        I64 *_t267 = malloc(sizeof(I64));
        *_t267 = 1;
        I64 *_t268 = malloc(sizeof(I64)); *_t268 = I64_sub(DEREF(_t266), DEREF(_t267));
        I64_delete(_t266, &(Bool){1});
        I64_delete(_t267, &(Bool){1});
        return _t268;
    }
    I64 *_t270 = malloc(sizeof(I64));
    *_t270 = 1;
    return _t270;
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    I64 *_t272 = malloc(sizeof(I64));
    *_t272 = 0;
    I64 *_t273 = malloc(sizeof(I64));
    *_t273 = 1;
    I64 *_t274 = Bool_cmp(a, b);
    I64 *_t275 = malloc(sizeof(I64)); *_t275 = I64_sub(DEREF(_t272), DEREF(_t273));
    I64_delete(_t272, &(Bool){1});
    I64_delete(_t273, &(Bool){1});
    Bool *_t276 = malloc(sizeof(Bool)); *_t276 = I64_eq(DEREF(_t274), DEREF(_t275));
    I64_delete(_t274, &(Bool){1});
    I64_delete(_t275, &(Bool){1});
    return _t276;
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    I64 *_t277 = Bool_cmp(a, b);
    I64 *_t278 = malloc(sizeof(I64));
    *_t278 = 1;
    Bool *_t279 = malloc(sizeof(Bool)); *_t279 = I64_eq(DEREF(_t277), DEREF(_t278));
    I64_delete(_t277, &(Bool){1});
    I64_delete(_t278, &(Bool){1});
    return _t279;
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    Bool *_t280 = malloc(sizeof(Bool)); *_t280 = Bool_eq(DEREF(a), DEREF(b));
    Bool *_t281 = malloc(sizeof(Bool)); *_t281 = Bool_not(DEREF(_t280));
    Bool_delete(_t280, &(Bool){1});
    return _t281;
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    Bool *_t282 = Bool_gt(a, b);
    Bool *_t283 = malloc(sizeof(Bool)); *_t283 = Bool_not(DEREF(_t282));
    Bool_delete(_t282, &(Bool){1});
    return _t283;
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    Bool *_t284 = Bool_lt(a, b);
    Bool *_t285 = malloc(sizeof(Bool)); *_t285 = Bool_not(DEREF(_t284));
    Bool_delete(_t284, &(Bool){1});
    return _t285;
}

void println(Array * parts) {
    {
        U64 *_fi286 = malloc(sizeof(U64));
        *_fi286 = 0;
        while (1) {
            U64 *_t288 = Array_len(parts);
            Bool *_wcond287 = U64_lt(_fi286, _t288);
            U64_delete(_t288, &(Bool){1});
            if (DEREF(_wcond287)) {
            } else {
                Bool_delete(_wcond287, &(Bool){1});
                break;
            }
            Bool_delete(_wcond287, &(Bool){1});
            Str *s = Array_get(parts, _fi286);
            U64 *_t289 = malloc(sizeof(U64));
            *_t289 = 1;
            U64 *_t290 = malloc(sizeof(U64)); *_t290 = U64_add(DEREF(_fi286), DEREF(_t289));
            U64_delete(_t289, &(Bool){1});
            *_fi286 = DEREF(_t290);
            U64_delete(_t290, &(Bool){1});
            print_single(s);
        }
        U64_delete(_fi286, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        U64 *_fi291 = malloc(sizeof(U64));
        *_fi291 = 0;
        while (1) {
            U64 *_t293 = Array_len(parts);
            Bool *_wcond292 = U64_lt(_fi291, _t293);
            U64_delete(_t293, &(Bool){1});
            if (DEREF(_wcond292)) {
            } else {
                Bool_delete(_wcond292, &(Bool){1});
                break;
            }
            Bool_delete(_wcond292, &(Bool){1});
            Str *s = Array_get(parts, _fi291);
            U64 *_t294 = malloc(sizeof(U64));
            *_t294 = 1;
            U64 *_t295 = malloc(sizeof(U64)); *_t295 = U64_add(DEREF(_fi291), DEREF(_t294));
            U64_delete(_t294, &(Bool){1});
            *_fi291 = DEREF(_t295);
            U64_delete(_t295, &(Bool){1});
            print_single(s);
        }
        U64_delete(_fi291, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 *total = malloc(sizeof(U64));
    *total = 0;
    {
        U64 *_fi296 = malloc(sizeof(U64));
        *_fi296 = 0;
        while (1) {
            U64 *_t298 = Array_len(parts);
            Bool *_wcond297 = U64_lt(_fi296, _t298);
            U64_delete(_t298, &(Bool){1});
            if (DEREF(_wcond297)) {
            } else {
                Bool_delete(_wcond297, &(Bool){1});
                break;
            }
            Bool_delete(_wcond297, &(Bool){1});
            Str *s = Array_get(parts, _fi296);
            U64 *_t299 = malloc(sizeof(U64));
            *_t299 = 1;
            U64 *_t300 = malloc(sizeof(U64)); *_t300 = U64_add(DEREF(_fi296), DEREF(_t299));
            U64_delete(_t299, &(Bool){1});
            *_fi296 = DEREF(_t300);
            U64_delete(_t300, &(Bool){1});
            U64 *_t301 = Str_len(s);
            U64 *_t302 = malloc(sizeof(U64)); *_t302 = U64_add(DEREF(total), DEREF(_t301));
            U64_delete(_t301, &(Bool){1});
            *total = DEREF(_t302);
            U64_delete(_t302, &(Bool){1});
        }
        U64_delete(_fi296, &(Bool){1});
    }
    U8 *buf = malloc(DEREF(total));
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi303 = malloc(sizeof(U64));
        *_fi303 = 0;
        while (1) {
            U64 *_t305 = Array_len(parts);
            Bool *_wcond304 = U64_lt(_fi303, _t305);
            U64_delete(_t305, &(Bool){1});
            if (DEREF(_wcond304)) {
            } else {
                Bool_delete(_wcond304, &(Bool){1});
                break;
            }
            Bool_delete(_wcond304, &(Bool){1});
            Str *s = Array_get(parts, _fi303);
            U64 *_t306 = malloc(sizeof(U64));
            *_t306 = 1;
            U64 *_t307 = malloc(sizeof(U64)); *_t307 = U64_add(DEREF(_fi303), DEREF(_t306));
            U64_delete(_t306, &(Bool){1});
            *_fi303 = DEREF(_t307);
            U64_delete(_t307, &(Bool){1});
            void *_t308 = ptr_add(buf, DEREF(offset));
            U64 *_t309 = Str_len(s);
            memcpy(_t308, s->c_str, DEREF(_t309));
            U64_delete(_t309, &(Bool){1});
            U64 *_t310 = Str_len(s);
            U64 *_t311 = malloc(sizeof(U64)); *_t311 = U64_add(DEREF(offset), DEREF(_t310));
            U64_delete(_t310, &(Bool){1});
            *offset = DEREF(_t311);
            U64_delete(_t311, &(Bool){1});
        }
        U64_delete(_fi303, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 *_t312 = U64_clone(total);
    U64 *_t313 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t314 = malloc(sizeof(Str));
    _t314->c_str = buf;
    _t314->count = DEREF(_t312);
    _t314->cap = DEREF(_t313);
    U64_delete(_t312, &(Bool){1});
    U64_delete(_t313, &(Bool){1});
    return _t314;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 *status = check_cmd_status(DEREF(pid));
        I64 *_t315 = malloc(sizeof(I64));
        *_t315 = 0;
        I64 *_t316 = malloc(sizeof(I64));
        *_t316 = 1;
        I64 *_t317 = malloc(sizeof(I64)); *_t317 = I64_sub(DEREF(_t315), DEREF(_t316));
        I64_delete(_t315, &(Bool){1});
        I64_delete(_t316, &(Bool){1});
        Bool *_t318 = I64_neq(status, _t317);
        I64_delete(_t317, &(Bool){1});
        if (DEREF(_t318)) {
            Bool_delete(_t318, &(Bool){1});
            return status;
        }
        Bool_delete(_t318, &(Bool){1});
        I64_delete(status, &(Bool){1});
        I64 *_t319 = malloc(sizeof(I64));
        *_t319 = 50;
        sleep_ms(DEREF(_t319));
        I64_delete(_t319, &(Bool){1});
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t325 = Array_len(args);
        Bool *_wcond320 = U64_lt(i, _t325);
        U64_delete(_t325, &(Bool){1});
        if (DEREF(_wcond320)) {
        } else {
            Bool_delete(_wcond320, &(Bool){1});
            break;
        }
        Bool_delete(_wcond320, &(Bool){1});
        Str *arg = Array_get(args, i);
        U64 *_t326 = malloc(sizeof(U64));
        *_t326 = 0;
        Bool *_t327 = U64_gt(i, _t326);
        U64_delete(_t326, &(Bool){1});
        if (DEREF(_t327)) {
            Str *_t321 = Str_lit(" '", 2ULL);
            Str *_t322 = Str_concat(cmd, _t321);
            Str_delete(_t321, &(Bool){1});
            Str *_t323 = Str_concat(_t322, arg);
            Str_delete(_t322, &(Bool){1});
            Str *_t324 = Str_lit("'", 1ULL);
            cmd = Str_concat(_t323, _t324);
            Str_delete(_t323, &(Bool){1});
            Str_delete(_t324, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        Bool_delete(_t327, &(Bool){1});
        U64 *_t328 = malloc(sizeof(U64));
        *_t328 = 1;
        U64 *_t329 = malloc(sizeof(U64)); *_t329 = U64_add(DEREF(i), DEREF(_t328));
        U64_delete(_t328, &(Bool){1});
        *i = DEREF(_t329);
        U64_delete(_t329, &(Bool){1});
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    Str *_t330 = Str_lit(" > ", 3ULL);
    Str *_t331 = Str_concat(cmd, _t330);
    Str_delete(_t330, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t332 = Str_concat(_t331, tmpf);
    Str_delete(_t331, &(Bool){1});
    Str *_t333 = Str_lit(" 2>&1", 5ULL);
    Str *_t334 = Str_concat(_t332, _t333);
    Str_delete(_t332, &(Bool){1});
    Str_delete(_t333, &(Bool){1});
    I64 *pid = spawn_cmd(_t334);
    Str_delete(_t334, &(Bool){1});
    I64 *ec = wait_cmd(pid);
    I64_delete(pid, &(Bool){1});
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 *_t335 = Str_size();
    memcpy(output, content, DEREF(_t335));
    U64_delete(_t335, &(Bool){1});
    free(content);
    return ec;
}

void panic(Str * loc_str, Array * parts) {
    Str *_t336 = Str_lit("Str", 3ULL);
    U64 *_t337 = Str_size();
    U64 *_t338 = malloc(sizeof(U64));
    *_t338 = 3;
    Array *_va4 = Array_new(_t336, _t337, _t338);
    Str_delete(_t336, &(Bool){1});
    U64_delete(_t337, &(Bool){1});
    U64_delete(_t338, &(Bool){1});
    U64 *_t339 = malloc(sizeof(U64));
    *_t339 = 0;
    Str *_t340 = Str_clone(loc_str);
    Array_set(_va4, _t339, _t340);
    U64_delete(_t339, &(Bool){1});
    U64 *_t341 = malloc(sizeof(U64));
    *_t341 = 1;
    Str *_t342 = Str_lit(": panic: ", 9ULL);
    Array_set(_va4, _t341, _t342);
    U64_delete(_t341, &(Bool){1});
    U64 *_t343 = malloc(sizeof(U64));
    *_t343 = 2;
    Str *_t344 = format(parts);
    Array_set(_va4, _t343, _t344);
    U64_delete(_t343, &(Bool){1});
    println(_va4);
    I64 *_t345 = malloc(sizeof(I64));
    *_t345 = 1;
    exit(DEREF(_t345));
    I64_delete(_t345, &(Bool){1});
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t346 = Str_lit("Str", 3ULL);
    U64 *_t347 = Str_size();
    U64 *_t348 = malloc(sizeof(U64));
    *_t348 = 2;
    Array *_va5 = Array_new(_t346, _t347, _t348);
    Str_delete(_t346, &(Bool){1});
    U64_delete(_t347, &(Bool){1});
    U64_delete(_t348, &(Bool){1});
    U64 *_t349 = malloc(sizeof(U64));
    *_t349 = 0;
    Str *_t350 = Str_lit("TODO: ", 6ULL);
    Array_set(_va5, _t349, _t350);
    U64_delete(_t349, &(Bool){1});
    U64 *_t351 = malloc(sizeof(U64));
    *_t351 = 1;
    Str *_t352 = format(parts);
    Array_set(_va5, _t351, _t352);
    U64_delete(_t351, &(Bool){1});
    panic(loc_str, _va5);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t353 = Str_lit("Str", 3ULL);
    U64 *_t354 = Str_size();
    U64 *_t355 = malloc(sizeof(U64));
    *_t355 = 1;
    Array *_va6 = Array_new(_t353, _t354, _t355);
    Str_delete(_t353, &(Bool){1});
    U64_delete(_t354, &(Bool){1});
    U64_delete(_t355, &(Bool){1});
    U64 *_t356 = malloc(sizeof(U64));
    *_t356 = 0;
    Str *_t357 = Str_lit("unreachable", 11ULL);
    Array_set(_va6, _t356, _t357);
    U64_delete(_t356, &(Bool){1});
    panic(loc_str, _va6);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool *_t365 = malloc(sizeof(Bool)); *_t365 = Bool_not(DEREF(cond));
    if (DEREF(_t365)) {
        Str *_t358 = Str_lit("Str", 3ULL);
        U64 *_t359 = Str_size();
        U64 *_t360 = malloc(sizeof(U64));
        *_t360 = 2;
        Array *_va7 = Array_new(_t358, _t359, _t360);
        Str_delete(_t358, &(Bool){1});
        U64_delete(_t359, &(Bool){1});
        U64_delete(_t360, &(Bool){1});
        U64 *_t361 = malloc(sizeof(U64));
        *_t361 = 0;
        Str *_t362 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va7, _t361, _t362);
        U64_delete(_t361, &(Bool){1});
        U64 *_t363 = malloc(sizeof(U64));
        *_t363 = 1;
        Str *_t364 = format(parts);
        Array_set(_va7, _t363, _t364);
        U64_delete(_t363, &(Bool){1});
        panic(loc_str, _va7);
    }
    Bool_delete(_t365, &(Bool){1});
    Bool *_t366 = malloc(sizeof(Bool));
    *_t366 = 1;
    return _t366;
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t367 = Str_lit("Str", 3ULL);
    U64 *_t368 = Str_size();
    U64 *_t369 = malloc(sizeof(U64));
    *_t369 = 0;
    Array *_va8 = Array_new(_t367, _t368, _t369);
    Str_delete(_t367, &(Bool){1});
    U64_delete(_t368, &(Bool){1});
    U64_delete(_t369, &(Bool){1});
    Bool *_t370 = assertm(loc_str, cond, _va8);
    return _t370;
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t371 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool *_t372 = assertm(loc_str, cond, _t371);
    Bool_delete(_t372, &(Bool){1});
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool *_t386 = I64_neq(a, b);
    if (DEREF(_t386)) {
        Str *_t373 = Str_lit("Str", 3ULL);
        U64 *_t374 = Str_size();
        U64 *_t375 = malloc(sizeof(U64));
        *_t375 = 5;
        Array *_va9 = Array_new(_t373, _t374, _t375);
        Str_delete(_t373, &(Bool){1});
        U64_delete(_t374, &(Bool){1});
        U64_delete(_t375, &(Bool){1});
        U64 *_t376 = malloc(sizeof(U64));
        *_t376 = 0;
        Str *_t377 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va9, _t376, _t377);
        U64_delete(_t376, &(Bool){1});
        U64 *_t378 = malloc(sizeof(U64));
        *_t378 = 1;
        Str *_t379 = I64_to_str(a);
        Array_set(_va9, _t378, _t379);
        U64_delete(_t378, &(Bool){1});
        U64 *_t380 = malloc(sizeof(U64));
        *_t380 = 2;
        Str *_t381 = Str_lit("', found '", 10ULL);
        Array_set(_va9, _t380, _t381);
        U64_delete(_t380, &(Bool){1});
        U64 *_t382 = malloc(sizeof(U64));
        *_t382 = 3;
        Str *_t383 = I64_to_str(b);
        Array_set(_va9, _t382, _t383);
        U64_delete(_t382, &(Bool){1});
        U64 *_t384 = malloc(sizeof(U64));
        *_t384 = 4;
        Str *_t385 = Str_lit("'", 1ULL);
        Array_set(_va9, _t384, _t385);
        U64_delete(_t384, &(Bool){1});
        panic(loc_str, _va9);
    }
    Bool_delete(_t386, &(Bool){1});
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool *_t400 = Str_eq(a, b);
    Bool *_t401 = malloc(sizeof(Bool)); *_t401 = Bool_not(DEREF(_t400));
    Bool_delete(_t400, &(Bool){1});
    if (DEREF(_t401)) {
        Str *_t387 = Str_lit("Str", 3ULL);
        U64 *_t388 = Str_size();
        U64 *_t389 = malloc(sizeof(U64));
        *_t389 = 5;
        Array *_va10 = Array_new(_t387, _t388, _t389);
        Str_delete(_t387, &(Bool){1});
        U64_delete(_t388, &(Bool){1});
        U64_delete(_t389, &(Bool){1});
        U64 *_t390 = malloc(sizeof(U64));
        *_t390 = 0;
        Str *_t391 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va10, _t390, _t391);
        U64_delete(_t390, &(Bool){1});
        U64 *_t392 = malloc(sizeof(U64));
        *_t392 = 1;
        Str *_t393 = Str_clone(a);
        Array_set(_va10, _t392, _t393);
        U64_delete(_t392, &(Bool){1});
        U64 *_t394 = malloc(sizeof(U64));
        *_t394 = 2;
        Str *_t395 = Str_lit("', found '", 10ULL);
        Array_set(_va10, _t394, _t395);
        U64_delete(_t394, &(Bool){1});
        U64 *_t396 = malloc(sizeof(U64));
        *_t396 = 3;
        Str *_t397 = Str_clone(b);
        Array_set(_va10, _t396, _t397);
        U64_delete(_t396, &(Bool){1});
        U64 *_t398 = malloc(sizeof(U64));
        *_t398 = 4;
        Str *_t399 = Str_lit("'", 1ULL);
        Array_set(_va10, _t398, _t399);
        U64_delete(_t398, &(Bool){1});
        panic(loc_str, _va10);
    }
    Bool_delete(_t401, &(Bool){1});
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    void *_t402 = calloc(DEREF(cap), DEREF(elem_size));
    U64 *_t403 = U64_clone(cap);
    U64 *_t404 = U64_clone(elem_size);
    Array *_t405 = malloc(sizeof(Array));
    _t405->data = _t402;
    _t405->cap = DEREF(_t403);
    _t405->elem_size = DEREF(_t404);
    { Str *_ca = Str_clone(elem_type); _t405->elem_type = *_ca; free(_ca); }
    U64_delete(_t403, &(Bool){1});
    U64_delete(_t404, &(Bool){1});
    return _t405;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    Bool *_t420 = U64_gte(i, &self->cap);
    if (DEREF(_t420)) {
        Str *_t406 = Str_lit("Str", 3ULL);
        U64 *_t407 = Str_size();
        U64 *_t408 = malloc(sizeof(U64));
        *_t408 = 5;
        Array *_va11 = Array_new(_t406, _t407, _t408);
        Str_delete(_t406, &(Bool){1});
        U64_delete(_t407, &(Bool){1});
        U64_delete(_t408, &(Bool){1});
        U64 *_t409 = malloc(sizeof(U64));
        *_t409 = 0;
        Str *_t410 = Str_lit("index ", 6ULL);
        Array_set(_va11, _t409, _t410);
        U64_delete(_t409, &(Bool){1});
        U64 *_t411 = malloc(sizeof(U64));
        *_t411 = 1;
        Str *_t412 = U64_to_str(DEREF(i));
        Array_set(_va11, _t411, _t412);
        U64_delete(_t411, &(Bool){1});
        U64 *_t413 = malloc(sizeof(U64));
        *_t413 = 2;
        Str *_t414 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va11, _t413, _t414);
        U64_delete(_t413, &(Bool){1});
        U64 *_t415 = malloc(sizeof(U64));
        *_t415 = 3;
        Str *_t416 = U64_to_str(self->cap);
        Array_set(_va11, _t415, _t416);
        U64_delete(_t415, &(Bool){1});
        U64 *_t417 = malloc(sizeof(U64));
        *_t417 = 4;
        Str *_t418 = Str_lit(")", 1ULL);
        Array_set(_va11, _t417, _t418);
        U64_delete(_t417, &(Bool){1});
        Str *_t419 = Str_lit("Array.get", 9ULL);
        panic(_t419, _va11);
        Str_delete(_t419, &(Bool){1});
    }
    Bool_delete(_t420, &(Bool){1});
    U64 *_t421 = malloc(sizeof(U64)); *_t421 = U64_mul(DEREF(i), self->elem_size);
    void *_t422 = ptr_add(self->data, DEREF(_t421));
    U64_delete(_t421, &(Bool){1});
    return _t422;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    Bool *_t437 = U64_gte(i, &self->cap);
    if (DEREF(_t437)) {
        Str *_t423 = Str_lit("Str", 3ULL);
        U64 *_t424 = Str_size();
        U64 *_t425 = malloc(sizeof(U64));
        *_t425 = 5;
        Array *_va12 = Array_new(_t423, _t424, _t425);
        Str_delete(_t423, &(Bool){1});
        U64_delete(_t424, &(Bool){1});
        U64_delete(_t425, &(Bool){1});
        U64 *_t426 = malloc(sizeof(U64));
        *_t426 = 0;
        Str *_t427 = Str_lit("index ", 6ULL);
        Array_set(_va12, _t426, _t427);
        U64_delete(_t426, &(Bool){1});
        U64 *_t428 = malloc(sizeof(U64));
        *_t428 = 1;
        Str *_t429 = U64_to_str(DEREF(i));
        Array_set(_va12, _t428, _t429);
        U64_delete(_t428, &(Bool){1});
        U64 *_t430 = malloc(sizeof(U64));
        *_t430 = 2;
        Str *_t431 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va12, _t430, _t431);
        U64_delete(_t430, &(Bool){1});
        U64 *_t432 = malloc(sizeof(U64));
        *_t432 = 3;
        Str *_t433 = U64_to_str(self->cap);
        Array_set(_va12, _t432, _t433);
        U64_delete(_t432, &(Bool){1});
        U64 *_t434 = malloc(sizeof(U64));
        *_t434 = 4;
        Str *_t435 = Str_lit(")", 1ULL);
        Array_set(_va12, _t434, _t435);
        U64_delete(_t434, &(Bool){1});
        Str *_t436 = Str_lit("Array.set", 9ULL);
        panic(_t436, _va12);
        Str_delete(_t436, &(Bool){1});
    }
    Bool_delete(_t437, &(Bool){1});
    U64 *_t438 = malloc(sizeof(U64)); *_t438 = U64_mul(DEREF(i), self->elem_size);
    void *_t439 = ptr_add(self->data, DEREF(_t438));
    Bool *_t440 = malloc(sizeof(Bool));
    *_t440 = 0;
    dyn_call_delete(&self->elem_type, _t439, _t440);
    U64_delete(_t438, &(Bool){1});
    Bool_delete(_t440, &(Bool){1});
    U64 *_t441 = malloc(sizeof(U64)); *_t441 = U64_mul(DEREF(i), self->elem_size);
    void *_t442 = ptr_add(self->data, DEREF(_t441));
    memcpy(_t442, val, self->elem_size);
    U64_delete(_t441, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    {
        U64 *_fi443 = malloc(sizeof(U64));
        *_fi443 = 0;
        while (1) {
            U64 *_t445 = malloc(sizeof(U64));
            *_t445 = 0;
            Range *_t446 = Range_new(DEREF(_t445), self->cap);
            U64_delete(_t445, &(Bool){1});
            U64 *_t447 = Range_len(_t446);
            Range_delete(_t446, &(Bool){1});
            Bool *_wcond444 = U64_lt(_fi443, _t447);
            U64_delete(_t447, &(Bool){1});
            if (DEREF(_wcond444)) {
            } else {
                Bool_delete(_wcond444, &(Bool){1});
                break;
            }
            Bool_delete(_wcond444, &(Bool){1});
            U64 *_t448 = malloc(sizeof(U64));
            *_t448 = 0;
            Range *_t449 = Range_new(DEREF(_t448), self->cap);
            U64_delete(_t448, &(Bool){1});
            U64 *i = Range_get(_t449, DEREF(_fi443));
            Range_delete(_t449, &(Bool){1});
            U64 *_t450 = malloc(sizeof(U64));
            *_t450 = 1;
            U64 *_t451 = malloc(sizeof(U64)); *_t451 = U64_add(DEREF(_fi443), DEREF(_t450));
            U64_delete(_t450, &(Bool){1});
            *_fi443 = DEREF(_t451);
            U64_delete(_t451, &(Bool){1});
            U64 *_t452 = malloc(sizeof(U64)); *_t452 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t453 = ptr_add(self->data, DEREF(_t452));
            Bool *_t454 = malloc(sizeof(Bool));
            *_t454 = 0;
            dyn_call_delete(&self->elem_type, _t453, _t454);
            U64_delete(_t452, &(Bool){1});
            Bool_delete(_t454, &(Bool){1});
        }
        U64_delete(_fi443, &(Bool){1});
    }
    free(self->data);
    Bool *_t455 = malloc(sizeof(Bool));
    *_t455 = 0;
    Str_delete(&self->elem_type, _t455);
    Bool_delete(_t455, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 *_t469 = malloc(sizeof(U64)); *_t469 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t469));
    U64_delete(_t469, &(Bool){1});
    {
        U64 *_fi456 = malloc(sizeof(U64));
        *_fi456 = 0;
        while (1) {
            U64 *_t458 = malloc(sizeof(U64));
            *_t458 = 0;
            Range *_t459 = Range_new(DEREF(_t458), self->cap);
            U64_delete(_t458, &(Bool){1});
            U64 *_t460 = Range_len(_t459);
            Range_delete(_t459, &(Bool){1});
            Bool *_wcond457 = U64_lt(_fi456, _t460);
            U64_delete(_t460, &(Bool){1});
            if (DEREF(_wcond457)) {
            } else {
                Bool_delete(_wcond457, &(Bool){1});
                break;
            }
            Bool_delete(_wcond457, &(Bool){1});
            U64 *_t461 = malloc(sizeof(U64));
            *_t461 = 0;
            Range *_t462 = Range_new(DEREF(_t461), self->cap);
            U64_delete(_t461, &(Bool){1});
            U64 *i = Range_get(_t462, DEREF(_fi456));
            Range_delete(_t462, &(Bool){1});
            U64 *_t463 = malloc(sizeof(U64));
            *_t463 = 1;
            U64 *_t464 = malloc(sizeof(U64)); *_t464 = U64_add(DEREF(_fi456), DEREF(_t463));
            U64_delete(_t463, &(Bool){1});
            *_fi456 = DEREF(_t464);
            U64_delete(_t464, &(Bool){1});
            U64 *_t465 = malloc(sizeof(U64)); *_t465 = U64_mul(DEREF(i), self->elem_size);
            void *_t466 = ptr_add(self->data, DEREF(_t465));
            void *cloned = dyn_call_clone(&self->elem_type, _t466);
            U64_delete(_t465, &(Bool){1});
            U64 *_t467 = malloc(sizeof(U64)); *_t467 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t468 = ptr_add(new_data, DEREF(_t467));
            memcpy(_t468, cloned, self->elem_size);
            U64_delete(_t467, &(Bool){1});
            free(cloned);
        }
        U64_delete(_fi456, &(Bool){1});
    }
    Array *_t470 = malloc(sizeof(Array));
    _t470->data = new_data;
    _t470->cap = self->cap;
    _t470->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t470->elem_type = *_ca; free(_ca); }
    return _t470;
}

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    Bool *_t484 = Str_is_empty(key_type);
    Bool *_t485 = malloc(sizeof(Bool)); *_t485 = Bool_not(DEREF(_t484));
    Bool_delete(_t484, &(Bool){1});
    if (DEREF(_t485)) {
        Bool *_t482 = dyn_has_cmp(key_type);
        Bool *_t483 = malloc(sizeof(Bool)); *_t483 = Bool_not(DEREF(_t482));
        Bool_delete(_t482, &(Bool){1});
        if (DEREF(_t483)) {
            Str *_t472 = Str_lit("Str", 3ULL);
            U64 *_t473 = Str_size();
            U64 *_t474 = malloc(sizeof(U64));
            *_t474 = 3;
            Array *_va13 = Array_new(_t472, _t473, _t474);
            Str_delete(_t472, &(Bool){1});
            U64_delete(_t473, &(Bool){1});
            U64_delete(_t474, &(Bool){1});
            U64 *_t475 = malloc(sizeof(U64));
            *_t475 = 0;
            Str *_t476 = Str_lit("type ", 5ULL);
            Array_set(_va13, _t475, _t476);
            U64_delete(_t475, &(Bool){1});
            U64 *_t477 = malloc(sizeof(U64));
            *_t477 = 1;
            Str *_t478 = Str_clone(key_type);
            Array_set(_va13, _t477, _t478);
            U64_delete(_t477, &(Bool){1});
            U64 *_t479 = malloc(sizeof(U64));
            *_t479 = 2;
            Str *_t480 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va13, _t479, _t480);
            U64_delete(_t479, &(Bool){1});
            Str *_t481 = Str_lit("Map.new", 7ULL);
            panic(_t481, _va13);
            Str_delete(_t481, &(Bool){1});
        }
        Bool_delete(_t483, &(Bool){1});
    }
    Bool_delete(_t485, &(Bool){1});
    void *_t486 = malloc(DEREF(key_size));
    void *_t487 = malloc(DEREF(val_size));
    U64 *_t488 = malloc(sizeof(U64));
    *_t488 = 0;
    I64 *_t489 = malloc(sizeof(I64));
    *_t489 = 1;
    U64 *_t490 = U64_clone(key_size);
    U64 *_t491 = U64_clone(val_size);
    Map *_t492 = malloc(sizeof(Map));
    _t492->key_data = _t486;
    _t492->val_data = _t487;
    _t492->count = DEREF(_t488);
    _t492->cap = DEREF(_t489);
    _t492->key_size = DEREF(_t490);
    { Str *_ca = Str_clone(key_type); _t492->key_type = *_ca; free(_ca); }
    _t492->val_size = DEREF(_t491);
    { Str *_ca = Str_clone(val_type); _t492->val_type = *_ca; free(_ca); }
    U64_delete(_t488, &(Bool){1});
    I64_delete(_t489, &(Bool){1});
    U64_delete(_t490, &(Bool){1});
    U64_delete(_t491, &(Bool){1});
    return _t492;
}

U64 * Map_len(Map * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Map_has(Map * self, void * key) {
    (void)self;
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    while (1) {
        Bool *_wcond493 = U64_lt(lo, hi);
        if (DEREF(_wcond493)) {
        } else {
            Bool_delete(_wcond493, &(Bool){1});
            break;
        }
        Bool_delete(_wcond493, &(Bool){1});
        U64 *_t500 = malloc(sizeof(U64)); *_t500 = U64_sub(DEREF(hi), DEREF(lo));
        U64 *_t501 = malloc(sizeof(U64));
        *_t501 = 2;
        U64 *_t502 = malloc(sizeof(U64)); *_t502 = U64_div(DEREF(_t500), DEREF(_t501));
        U64_delete(_t500, &(Bool){1});
        U64_delete(_t501, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t502));
        U64_delete(_t502, &(Bool){1});
        U64 *_t503 = malloc(sizeof(U64)); *_t503 = U64_mul(DEREF(mid), self->key_size);
        void *_t504 = ptr_add(self->key_data, DEREF(_t503));
        I64 *c = dyn_call_cmp(&self->key_type, _t504, key);
        U64_delete(_t503, &(Bool){1});
        I64 *_t505 = malloc(sizeof(I64));
        *_t505 = 0;
        Bool *_t506 = I64_lt(c, _t505);
        I64_delete(_t505, &(Bool){1});
        if (DEREF(_t506)) {
            U64 *_t494 = malloc(sizeof(U64));
            *_t494 = 1;
            U64 *_t495 = malloc(sizeof(U64)); *_t495 = U64_add(DEREF(mid), DEREF(_t494));
            U64_delete(_t494, &(Bool){1});
            *lo = DEREF(_t495);
            U64_delete(_t495, &(Bool){1});
        } else {
            I64 *_t498 = malloc(sizeof(I64));
            *_t498 = 0;
            Bool *_t499 = I64_gt(c, _t498);
            I64_delete(_t498, &(Bool){1});
            if (DEREF(_t499)) {
                U64 *_t496 = U64_clone(mid);
                *hi = DEREF(_t496);
                U64_delete(_t496, &(Bool){1});
            } else {
                Bool *_t497 = malloc(sizeof(Bool));
                *_t497 = 1;
                Bool_delete(_t499, &(Bool){1});
                Bool_delete(_t506, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t497;
            }
            Bool_delete(_t499, &(Bool){1});
        }
        Bool_delete(_t506, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Bool *_t507 = malloc(sizeof(Bool));
    *_t507 = 0;
    return _t507;
}

void * Map_get(Map * self, void * key) {
    (void)self;
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    while (1) {
        Bool *_wcond508 = U64_lt(lo, hi);
        if (DEREF(_wcond508)) {
        } else {
            Bool_delete(_wcond508, &(Bool){1});
            break;
        }
        Bool_delete(_wcond508, &(Bool){1});
        U64 *_t516 = malloc(sizeof(U64)); *_t516 = U64_sub(DEREF(hi), DEREF(lo));
        U64 *_t517 = malloc(sizeof(U64));
        *_t517 = 2;
        U64 *_t518 = malloc(sizeof(U64)); *_t518 = U64_div(DEREF(_t516), DEREF(_t517));
        U64_delete(_t516, &(Bool){1});
        U64_delete(_t517, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t518));
        U64_delete(_t518, &(Bool){1});
        U64 *_t519 = malloc(sizeof(U64)); *_t519 = U64_mul(DEREF(mid), self->key_size);
        void *_t520 = ptr_add(self->key_data, DEREF(_t519));
        I64 *c = dyn_call_cmp(&self->key_type, _t520, key);
        U64_delete(_t519, &(Bool){1});
        I64 *_t521 = malloc(sizeof(I64));
        *_t521 = 0;
        Bool *_t522 = I64_lt(c, _t521);
        I64_delete(_t521, &(Bool){1});
        if (DEREF(_t522)) {
            U64 *_t509 = malloc(sizeof(U64));
            *_t509 = 1;
            U64 *_t510 = malloc(sizeof(U64)); *_t510 = U64_add(DEREF(mid), DEREF(_t509));
            U64_delete(_t509, &(Bool){1});
            *lo = DEREF(_t510);
            U64_delete(_t510, &(Bool){1});
        } else {
            I64 *_t514 = malloc(sizeof(I64));
            *_t514 = 0;
            Bool *_t515 = I64_gt(c, _t514);
            I64_delete(_t514, &(Bool){1});
            if (DEREF(_t515)) {
                U64 *_t511 = U64_clone(mid);
                *hi = DEREF(_t511);
                U64_delete(_t511, &(Bool){1});
            } else {
                U64 *_t512 = malloc(sizeof(U64)); *_t512 = U64_mul(DEREF(mid), self->val_size);
                void *_t513 = ptr_add(self->val_data, DEREF(_t512));
                U64_delete(_t512, &(Bool){1});
                Bool_delete(_t515, &(Bool){1});
                Bool_delete(_t522, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t513;
            }
            Bool_delete(_t515, &(Bool){1});
        }
        Bool_delete(_t522, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Str *_t523 = Str_lit("Str", 3ULL);
    U64 *_t524 = Str_size();
    U64 *_t525 = malloc(sizeof(U64));
    *_t525 = 1;
    Array *_va14 = Array_new(_t523, _t524, _t525);
    Str_delete(_t523, &(Bool){1});
    U64_delete(_t524, &(Bool){1});
    U64_delete(_t525, &(Bool){1});
    U64 *_t526 = malloc(sizeof(U64));
    *_t526 = 0;
    Str *_t527 = Str_lit("key not found", 13ULL);
    Array_set(_va14, _t526, _t527);
    U64_delete(_t526, &(Bool){1});
    Str *_t528 = Str_lit("Map.get", 7ULL);
    panic(_t528, _va14);
    Str_delete(_t528, &(Bool){1});
    U64 *_t529 = malloc(sizeof(U64));
    *_t529 = 0;
    void *_t530 = ptr_add(self->val_data, DEREF(_t529));
    U64_delete(_t529, &(Bool){1});
    return _t530;
}

void Map_set(Map * self, void * key, void * val) {
    (void)self;
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    Bool *found = malloc(sizeof(Bool));
    *found = 0;
    while (1) {
        Bool *_wcond531 = U64_lt(lo, hi);
        if (DEREF(_wcond531)) {
        } else {
            Bool_delete(_wcond531, &(Bool){1});
            break;
        }
        Bool_delete(_wcond531, &(Bool){1});
        U64 *_t540 = malloc(sizeof(U64)); *_t540 = U64_sub(DEREF(hi), DEREF(lo));
        U64 *_t541 = malloc(sizeof(U64));
        *_t541 = 2;
        U64 *_t542 = malloc(sizeof(U64)); *_t542 = U64_div(DEREF(_t540), DEREF(_t541));
        U64_delete(_t540, &(Bool){1});
        U64_delete(_t541, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t542));
        U64_delete(_t542, &(Bool){1});
        U64 *_t543 = malloc(sizeof(U64)); *_t543 = U64_mul(DEREF(mid), self->key_size);
        void *_t544 = ptr_add(self->key_data, DEREF(_t543));
        I64 *c = dyn_call_cmp(&self->key_type, _t544, key);
        U64_delete(_t543, &(Bool){1});
        I64 *_t545 = malloc(sizeof(I64));
        *_t545 = 0;
        Bool *_t546 = I64_lt(c, _t545);
        I64_delete(_t545, &(Bool){1});
        if (DEREF(_t546)) {
            U64 *_t532 = malloc(sizeof(U64));
            *_t532 = 1;
            U64 *_t533 = malloc(sizeof(U64)); *_t533 = U64_add(DEREF(mid), DEREF(_t532));
            U64_delete(_t532, &(Bool){1});
            *lo = DEREF(_t533);
            U64_delete(_t533, &(Bool){1});
        } else {
            I64 *_t538 = malloc(sizeof(I64));
            *_t538 = 0;
            Bool *_t539 = I64_gt(c, _t538);
            I64_delete(_t538, &(Bool){1});
            if (DEREF(_t539)) {
                U64 *_t534 = U64_clone(mid);
                *hi = DEREF(_t534);
                U64_delete(_t534, &(Bool){1});
            } else {
                Bool *_t535 = malloc(sizeof(Bool));
                *_t535 = 1;
                *found = DEREF(_t535);
                Bool_delete(_t535, &(Bool){1});
                U64 *_t536 = U64_clone(mid);
                *lo = DEREF(_t536);
                U64_delete(_t536, &(Bool){1});
                U64 *_t537 = U64_clone(mid);
                *hi = DEREF(_t537);
                U64_delete(_t537, &(Bool){1});
            }
            Bool_delete(_t539, &(Bool){1});
        }
        Bool_delete(_t546, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    if (DEREF(found)) {
        Bool *_t551 = Str_is_empty(&self->key_type);
        Bool *_t552 = malloc(sizeof(Bool)); *_t552 = Bool_not(DEREF(_t551));
        Bool_delete(_t551, &(Bool){1});
        if (DEREF(_t552)) {
            Bool *_t547 = malloc(sizeof(Bool));
            *_t547 = 0;
            dyn_call_delete(&self->key_type, key, _t547);
            Bool_delete(_t547, &(Bool){1});
        }
        Bool_delete(_t552, &(Bool){1});
        free(key);
        Bool *_t553 = Str_is_empty(&self->val_type);
        Bool *_t554 = malloc(sizeof(Bool)); *_t554 = Bool_not(DEREF(_t553));
        Bool_delete(_t553, &(Bool){1});
        if (DEREF(_t554)) {
            U64 *_t548 = malloc(sizeof(U64)); *_t548 = U64_mul(DEREF(lo), self->val_size);
            void *_t549 = ptr_add(self->val_data, DEREF(_t548));
            Bool *_t550 = malloc(sizeof(Bool));
            *_t550 = 0;
            dyn_call_delete(&self->val_type, _t549, _t550);
            U64_delete(_t548, &(Bool){1});
            Bool_delete(_t550, &(Bool){1});
        }
        Bool_delete(_t554, &(Bool){1});
        U64 *_t555 = malloc(sizeof(U64)); *_t555 = U64_mul(DEREF(lo), self->val_size);
        void *_t556 = ptr_add(self->val_data, DEREF(_t555));
        memcpy(_t556, val, self->val_size);
        U64_delete(_t555, &(Bool){1});
        free(val);
    } else {
        Bool *_t563 = malloc(sizeof(Bool)); *_t563 = U64_eq(self->count, self->cap);
        if (DEREF(_t563)) {
            U64 *_t557 = malloc(sizeof(U64));
            *_t557 = 2;
            U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t557));
            U64_delete(_t557, &(Bool){1});
            U64 *_t558 = malloc(sizeof(U64)); *_t558 = U64_mul(DEREF(new_cap), self->key_size);
            void *_t559 = realloc(self->key_data, DEREF(_t558));
            U64_delete(_t558, &(Bool){1});
            self->key_data = _t559;
            U64 *_t560 = malloc(sizeof(U64)); *_t560 = U64_mul(DEREF(new_cap), self->val_size);
            void *_t561 = realloc(self->val_data, DEREF(_t560));
            U64_delete(_t560, &(Bool){1});
            self->val_data = _t561;
            U64 *_t562 = U64_clone(new_cap);
            U64_delete(new_cap, &(Bool){1});
            self->cap = DEREF(_t562);
            U64_delete(_t562, &(Bool){1});
        }
        Bool_delete(_t563, &(Bool){1});
        U64 *_t564 = malloc(sizeof(U64));
        *_t564 = 1;
        U64 *_t565 = malloc(sizeof(U64)); *_t565 = U64_add(DEREF(lo), DEREF(_t564));
        U64_delete(_t564, &(Bool){1});
        U64 *_t566 = malloc(sizeof(U64)); *_t566 = U64_mul(DEREF(_t565), self->key_size);
        U64_delete(_t565, &(Bool){1});
        U64 *_t567 = malloc(sizeof(U64)); *_t567 = U64_mul(DEREF(lo), self->key_size);
        U64 *_t568 = malloc(sizeof(U64)); *_t568 = U64_sub(self->count, DEREF(lo));
        void *_t569 = ptr_add(self->key_data, DEREF(_t566));
        void *_t570 = ptr_add(self->key_data, DEREF(_t567));
        U64 *_t571 = malloc(sizeof(U64)); *_t571 = U64_mul(DEREF(_t568), self->key_size);
        U64_delete(_t568, &(Bool){1});
        memmove(_t569, _t570, DEREF(_t571));
        U64_delete(_t566, &(Bool){1});
        U64_delete(_t567, &(Bool){1});
        U64_delete(_t571, &(Bool){1});
        U64 *_t572 = malloc(sizeof(U64));
        *_t572 = 1;
        U64 *_t573 = malloc(sizeof(U64)); *_t573 = U64_add(DEREF(lo), DEREF(_t572));
        U64_delete(_t572, &(Bool){1});
        U64 *_t574 = malloc(sizeof(U64)); *_t574 = U64_mul(DEREF(_t573), self->val_size);
        U64_delete(_t573, &(Bool){1});
        U64 *_t575 = malloc(sizeof(U64)); *_t575 = U64_mul(DEREF(lo), self->val_size);
        U64 *_t576 = malloc(sizeof(U64)); *_t576 = U64_sub(self->count, DEREF(lo));
        void *_t577 = ptr_add(self->val_data, DEREF(_t574));
        void *_t578 = ptr_add(self->val_data, DEREF(_t575));
        U64 *_t579 = malloc(sizeof(U64)); *_t579 = U64_mul(DEREF(_t576), self->val_size);
        U64_delete(_t576, &(Bool){1});
        memmove(_t577, _t578, DEREF(_t579));
        U64_delete(_t574, &(Bool){1});
        U64_delete(_t575, &(Bool){1});
        U64_delete(_t579, &(Bool){1});
        U64 *_t580 = malloc(sizeof(U64)); *_t580 = U64_mul(DEREF(lo), self->key_size);
        void *_t581 = ptr_add(self->key_data, DEREF(_t580));
        memcpy(_t581, key, self->key_size);
        U64_delete(_t580, &(Bool){1});
        U64 *_t582 = malloc(sizeof(U64)); *_t582 = U64_mul(DEREF(lo), self->val_size);
        void *_t583 = ptr_add(self->val_data, DEREF(_t582));
        memcpy(_t583, val, self->val_size);
        U64_delete(_t582, &(Bool){1});
        free(key);
        free(val);
        U64 *_t584 = malloc(sizeof(U64));
        *_t584 = 1;
        U64 *_t585 = malloc(sizeof(U64)); *_t585 = U64_add(self->count, DEREF(_t584));
        U64_delete(_t584, &(Bool){1});
        self->count = DEREF(_t585);
        U64_delete(_t585, &(Bool){1});
    }
    Bool_delete(found, &(Bool){1});
    U64_delete(lo, &(Bool){1});
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    Bool *_t612 = Str_is_empty(&self->key_type);
    Bool *_t613 = malloc(sizeof(Bool)); *_t613 = Bool_not(DEREF(_t612));
    Bool_delete(_t612, &(Bool){1});
    if (DEREF(_t613)) {
        {
            U64 *_fi586 = malloc(sizeof(U64));
            *_fi586 = 0;
            while (1) {
                U64 *_t588 = malloc(sizeof(U64));
                *_t588 = 0;
                Range *_t589 = Range_new(DEREF(_t588), self->count);
                U64_delete(_t588, &(Bool){1});
                U64 *_t590 = Range_len(_t589);
                Range_delete(_t589, &(Bool){1});
                Bool *_wcond587 = U64_lt(_fi586, _t590);
                U64_delete(_t590, &(Bool){1});
                if (DEREF(_wcond587)) {
                } else {
                    Bool_delete(_wcond587, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond587, &(Bool){1});
                U64 *_t591 = malloc(sizeof(U64));
                *_t591 = 0;
                Range *_t592 = Range_new(DEREF(_t591), self->count);
                U64_delete(_t591, &(Bool){1});
                U64 *i = Range_get(_t592, DEREF(_fi586));
                Range_delete(_t592, &(Bool){1});
                U64 *_t593 = malloc(sizeof(U64));
                *_t593 = 1;
                U64 *_t594 = malloc(sizeof(U64)); *_t594 = U64_add(DEREF(_fi586), DEREF(_t593));
                U64_delete(_t593, &(Bool){1});
                *_fi586 = DEREF(_t594);
                U64_delete(_t594, &(Bool){1});
                U64 *_t595 = malloc(sizeof(U64)); *_t595 = U64_mul(DEREF(i), self->key_size);
                U64_delete(i, &(Bool){1});
                void *_t596 = ptr_add(self->key_data, DEREF(_t595));
                Bool *_t597 = malloc(sizeof(Bool));
                *_t597 = 0;
                dyn_call_delete(&self->key_type, _t596, _t597);
                U64_delete(_t595, &(Bool){1});
                Bool_delete(_t597, &(Bool){1});
            }
            U64_delete(_fi586, &(Bool){1});
        }
    }
    Bool_delete(_t613, &(Bool){1});
    Bool *_t614 = Str_is_empty(&self->val_type);
    Bool *_t615 = malloc(sizeof(Bool)); *_t615 = Bool_not(DEREF(_t614));
    Bool_delete(_t614, &(Bool){1});
    if (DEREF(_t615)) {
        {
            U64 *_fi598 = malloc(sizeof(U64));
            *_fi598 = 0;
            while (1) {
                U64 *_t600 = malloc(sizeof(U64));
                *_t600 = 0;
                Range *_t601 = Range_new(DEREF(_t600), self->count);
                U64_delete(_t600, &(Bool){1});
                U64 *_t602 = Range_len(_t601);
                Range_delete(_t601, &(Bool){1});
                Bool *_wcond599 = U64_lt(_fi598, _t602);
                U64_delete(_t602, &(Bool){1});
                if (DEREF(_wcond599)) {
                } else {
                    Bool_delete(_wcond599, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond599, &(Bool){1});
                U64 *_t603 = malloc(sizeof(U64));
                *_t603 = 0;
                Range *_t604 = Range_new(DEREF(_t603), self->count);
                U64_delete(_t603, &(Bool){1});
                U64 *i = Range_get(_t604, DEREF(_fi598));
                Range_delete(_t604, &(Bool){1});
                U64 *_t605 = malloc(sizeof(U64));
                *_t605 = 1;
                U64 *_t606 = malloc(sizeof(U64)); *_t606 = U64_add(DEREF(_fi598), DEREF(_t605));
                U64_delete(_t605, &(Bool){1});
                *_fi598 = DEREF(_t606);
                U64_delete(_t606, &(Bool){1});
                U64 *_t607 = malloc(sizeof(U64)); *_t607 = U64_mul(DEREF(i), self->val_size);
                U64_delete(i, &(Bool){1});
                void *_t608 = ptr_add(self->val_data, DEREF(_t607));
                Bool *_t609 = malloc(sizeof(Bool));
                *_t609 = 0;
                dyn_call_delete(&self->val_type, _t608, _t609);
                U64_delete(_t607, &(Bool){1});
                Bool_delete(_t609, &(Bool){1});
            }
            U64_delete(_fi598, &(Bool){1});
        }
    }
    Bool_delete(_t615, &(Bool){1});
    free(self->key_data);
    free(self->val_data);
    Bool *_t616 = Str_is_empty(&self->key_type);
    Bool *_t617 = malloc(sizeof(Bool)); *_t617 = Bool_not(DEREF(_t616));
    Bool_delete(_t616, &(Bool){1});
    if (DEREF(_t617)) {
        Bool *_t610 = malloc(sizeof(Bool));
        *_t610 = 0;
        Str_delete(&self->key_type, _t610);
        Bool_delete(_t610, &(Bool){1});
    }
    Bool_delete(_t617, &(Bool){1});
    Bool *_t618 = Str_is_empty(&self->val_type);
    Bool *_t619 = malloc(sizeof(Bool)); *_t619 = Bool_not(DEREF(_t618));
    Bool_delete(_t618, &(Bool){1});
    if (DEREF(_t619)) {
        Bool *_t611 = malloc(sizeof(Bool));
        *_t611 = 0;
        Str_delete(&self->val_type, _t611);
        Bool_delete(_t611, &(Bool){1});
    }
    Bool_delete(_t619, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 *_t637 = malloc(sizeof(U64)); *_t637 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(DEREF(_t637));
    U64_delete(_t637, &(Bool){1});
    U64 *_t638 = malloc(sizeof(U64)); *_t638 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(DEREF(_t638));
    U64_delete(_t638, &(Bool){1});
    {
        U64 *_fi620 = malloc(sizeof(U64));
        *_fi620 = 0;
        while (1) {
            U64 *_t622 = malloc(sizeof(U64));
            *_t622 = 0;
            Range *_t623 = Range_new(DEREF(_t622), self->count);
            U64_delete(_t622, &(Bool){1});
            U64 *_t624 = Range_len(_t623);
            Range_delete(_t623, &(Bool){1});
            Bool *_wcond621 = U64_lt(_fi620, _t624);
            U64_delete(_t624, &(Bool){1});
            if (DEREF(_wcond621)) {
            } else {
                Bool_delete(_wcond621, &(Bool){1});
                break;
            }
            Bool_delete(_wcond621, &(Bool){1});
            U64 *_t625 = malloc(sizeof(U64));
            *_t625 = 0;
            Range *_t626 = Range_new(DEREF(_t625), self->count);
            U64_delete(_t625, &(Bool){1});
            U64 *i = Range_get(_t626, DEREF(_fi620));
            Range_delete(_t626, &(Bool){1});
            U64 *_t627 = malloc(sizeof(U64));
            *_t627 = 1;
            U64 *_t628 = malloc(sizeof(U64)); *_t628 = U64_add(DEREF(_fi620), DEREF(_t627));
            U64_delete(_t627, &(Bool){1});
            *_fi620 = DEREF(_t628);
            U64_delete(_t628, &(Bool){1});
            U64 *_t629 = malloc(sizeof(U64)); *_t629 = U64_mul(DEREF(i), self->key_size);
            void *_t630 = ptr_add(self->key_data, DEREF(_t629));
            void *ck = dyn_call_clone(&self->key_type, _t630);
            U64_delete(_t629, &(Bool){1});
            U64 *_t631 = malloc(sizeof(U64)); *_t631 = U64_mul(DEREF(i), self->key_size);
            void *_t632 = ptr_add(new_keys, DEREF(_t631));
            memcpy(_t632, ck, self->key_size);
            U64_delete(_t631, &(Bool){1});
            free(ck);
            U64 *_t633 = malloc(sizeof(U64)); *_t633 = U64_mul(DEREF(i), self->val_size);
            void *_t634 = ptr_add(self->val_data, DEREF(_t633));
            void *cv = dyn_call_clone(&self->val_type, _t634);
            U64_delete(_t633, &(Bool){1});
            U64 *_t635 = malloc(sizeof(U64)); *_t635 = U64_mul(DEREF(i), self->val_size);
            U64_delete(i, &(Bool){1});
            void *_t636 = ptr_add(new_vals, DEREF(_t635));
            memcpy(_t636, cv, self->val_size);
            U64_delete(_t635, &(Bool){1});
            free(cv);
        }
        U64_delete(_fi620, &(Bool){1});
    }
    Map *_t639 = malloc(sizeof(Map));
    _t639->key_data = new_keys;
    _t639->val_data = new_vals;
    _t639->count = self->count;
    _t639->cap = self->cap;
    _t639->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t639->key_type = *_ca; free(_ca); }
    _t639->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t639->val_type = *_ca; free(_ca); }
    return _t639;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    Bool *_t653 = Str_is_empty(elem_type);
    Bool *_t654 = malloc(sizeof(Bool)); *_t654 = Bool_not(DEREF(_t653));
    Bool_delete(_t653, &(Bool){1});
    if (DEREF(_t654)) {
        Bool *_t651 = dyn_has_cmp(elem_type);
        Bool *_t652 = malloc(sizeof(Bool)); *_t652 = Bool_not(DEREF(_t651));
        Bool_delete(_t651, &(Bool){1});
        if (DEREF(_t652)) {
            Str *_t641 = Str_lit("Str", 3ULL);
            U64 *_t642 = Str_size();
            U64 *_t643 = malloc(sizeof(U64));
            *_t643 = 3;
            Array *_va15 = Array_new(_t641, _t642, _t643);
            Str_delete(_t641, &(Bool){1});
            U64_delete(_t642, &(Bool){1});
            U64_delete(_t643, &(Bool){1});
            U64 *_t644 = malloc(sizeof(U64));
            *_t644 = 0;
            Str *_t645 = Str_lit("type ", 5ULL);
            Array_set(_va15, _t644, _t645);
            U64_delete(_t644, &(Bool){1});
            U64 *_t646 = malloc(sizeof(U64));
            *_t646 = 1;
            Str *_t647 = Str_clone(elem_type);
            Array_set(_va15, _t646, _t647);
            U64_delete(_t646, &(Bool){1});
            U64 *_t648 = malloc(sizeof(U64));
            *_t648 = 2;
            Str *_t649 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va15, _t648, _t649);
            U64_delete(_t648, &(Bool){1});
            Str *_t650 = Str_lit("Set.new", 7ULL);
            panic(_t650, _va15);
            Str_delete(_t650, &(Bool){1});
        }
        Bool_delete(_t652, &(Bool){1});
    }
    Bool_delete(_t654, &(Bool){1});
    void *_t655 = malloc(DEREF(elem_size));
    U64 *_t656 = malloc(sizeof(U64));
    *_t656 = 0;
    I64 *_t657 = malloc(sizeof(I64));
    *_t657 = 1;
    U64 *_t658 = U64_clone(elem_size);
    Set *_t659 = malloc(sizeof(Set));
    _t659->data = _t655;
    _t659->count = DEREF(_t656);
    _t659->cap = DEREF(_t657);
    _t659->elem_size = DEREF(_t658);
    { Str *_ca = Str_clone(elem_type); _t659->elem_type = *_ca; free(_ca); }
    U64_delete(_t656, &(Bool){1});
    I64_delete(_t657, &(Bool){1});
    U64_delete(_t658, &(Bool){1});
    return _t659;
}

U64 * Set_len(Set * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Set_has(Set * self, void * val) {
    (void)self;
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    while (1) {
        Bool *_wcond660 = U64_lt(lo, hi);
        if (DEREF(_wcond660)) {
        } else {
            Bool_delete(_wcond660, &(Bool){1});
            break;
        }
        Bool_delete(_wcond660, &(Bool){1});
        U64 *_t667 = malloc(sizeof(U64)); *_t667 = U64_sub(DEREF(hi), DEREF(lo));
        U64 *_t668 = malloc(sizeof(U64));
        *_t668 = 2;
        U64 *_t669 = malloc(sizeof(U64)); *_t669 = U64_div(DEREF(_t667), DEREF(_t668));
        U64_delete(_t667, &(Bool){1});
        U64_delete(_t668, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t669));
        U64_delete(_t669, &(Bool){1});
        U64 *_t670 = malloc(sizeof(U64)); *_t670 = U64_mul(DEREF(mid), self->elem_size);
        void *_t671 = ptr_add(self->data, DEREF(_t670));
        I64 *c = dyn_call_cmp(&self->elem_type, _t671, val);
        U64_delete(_t670, &(Bool){1});
        I64 *_t672 = malloc(sizeof(I64));
        *_t672 = 0;
        Bool *_t673 = I64_lt(c, _t672);
        I64_delete(_t672, &(Bool){1});
        if (DEREF(_t673)) {
            U64 *_t661 = malloc(sizeof(U64));
            *_t661 = 1;
            U64 *_t662 = malloc(sizeof(U64)); *_t662 = U64_add(DEREF(mid), DEREF(_t661));
            U64_delete(_t661, &(Bool){1});
            *lo = DEREF(_t662);
            U64_delete(_t662, &(Bool){1});
        } else {
            I64 *_t665 = malloc(sizeof(I64));
            *_t665 = 0;
            Bool *_t666 = I64_gt(c, _t665);
            I64_delete(_t665, &(Bool){1});
            if (DEREF(_t666)) {
                U64 *_t663 = U64_clone(mid);
                *hi = DEREF(_t663);
                U64_delete(_t663, &(Bool){1});
            } else {
                Bool *_t664 = malloc(sizeof(Bool));
                *_t664 = 1;
                Bool_delete(_t666, &(Bool){1});
                Bool_delete(_t673, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t664;
            }
            Bool_delete(_t666, &(Bool){1});
        }
        Bool_delete(_t673, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Bool *_t674 = malloc(sizeof(Bool));
    *_t674 = 0;
    return _t674;
}

void Set_add(Set * self, void * val) {
    (void)self;
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    Bool *found = malloc(sizeof(Bool));
    *found = 0;
    while (1) {
        Bool *_wcond675 = U64_lt(lo, hi);
        if (DEREF(_wcond675)) {
        } else {
            Bool_delete(_wcond675, &(Bool){1});
            break;
        }
        Bool_delete(_wcond675, &(Bool){1});
        U64 *_t684 = malloc(sizeof(U64)); *_t684 = U64_sub(DEREF(hi), DEREF(lo));
        U64 *_t685 = malloc(sizeof(U64));
        *_t685 = 2;
        U64 *_t686 = malloc(sizeof(U64)); *_t686 = U64_div(DEREF(_t684), DEREF(_t685));
        U64_delete(_t684, &(Bool){1});
        U64_delete(_t685, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t686));
        U64_delete(_t686, &(Bool){1});
        U64 *_t687 = malloc(sizeof(U64)); *_t687 = U64_mul(DEREF(mid), self->elem_size);
        void *_t688 = ptr_add(self->data, DEREF(_t687));
        I64 *c = dyn_call_cmp(&self->elem_type, _t688, val);
        U64_delete(_t687, &(Bool){1});
        I64 *_t689 = malloc(sizeof(I64));
        *_t689 = 0;
        Bool *_t690 = I64_lt(c, _t689);
        I64_delete(_t689, &(Bool){1});
        if (DEREF(_t690)) {
            U64 *_t676 = malloc(sizeof(U64));
            *_t676 = 1;
            U64 *_t677 = malloc(sizeof(U64)); *_t677 = U64_add(DEREF(mid), DEREF(_t676));
            U64_delete(_t676, &(Bool){1});
            *lo = DEREF(_t677);
            U64_delete(_t677, &(Bool){1});
        } else {
            I64 *_t682 = malloc(sizeof(I64));
            *_t682 = 0;
            Bool *_t683 = I64_gt(c, _t682);
            I64_delete(_t682, &(Bool){1});
            if (DEREF(_t683)) {
                U64 *_t678 = U64_clone(mid);
                *hi = DEREF(_t678);
                U64_delete(_t678, &(Bool){1});
            } else {
                Bool *_t679 = malloc(sizeof(Bool));
                *_t679 = 1;
                *found = DEREF(_t679);
                Bool_delete(_t679, &(Bool){1});
                U64 *_t680 = U64_clone(mid);
                *lo = DEREF(_t680);
                U64_delete(_t680, &(Bool){1});
                U64 *_t681 = U64_clone(mid);
                *hi = DEREF(_t681);
                U64_delete(_t681, &(Bool){1});
            }
            Bool_delete(_t683, &(Bool){1});
        }
        Bool_delete(_t690, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    if (DEREF(found)) {
        Bool *_t692 = Str_is_empty(&self->elem_type);
        Bool *_t693 = malloc(sizeof(Bool)); *_t693 = Bool_not(DEREF(_t692));
        Bool_delete(_t692, &(Bool){1});
        if (DEREF(_t693)) {
            Bool *_t691 = malloc(sizeof(Bool));
            *_t691 = 0;
            dyn_call_delete(&self->elem_type, val, _t691);
            Bool_delete(_t691, &(Bool){1});
        }
        Bool_delete(_t693, &(Bool){1});
        free(val);
    } else {
        Bool *_t698 = malloc(sizeof(Bool)); *_t698 = U64_eq(self->count, self->cap);
        if (DEREF(_t698)) {
            U64 *_t694 = malloc(sizeof(U64));
            *_t694 = 2;
            U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t694));
            U64_delete(_t694, &(Bool){1});
            U64 *_t695 = malloc(sizeof(U64)); *_t695 = U64_mul(DEREF(new_cap), self->elem_size);
            void *_t696 = realloc(self->data, DEREF(_t695));
            U64_delete(_t695, &(Bool){1});
            self->data = _t696;
            U64 *_t697 = U64_clone(new_cap);
            U64_delete(new_cap, &(Bool){1});
            self->cap = DEREF(_t697);
            U64_delete(_t697, &(Bool){1});
        }
        Bool_delete(_t698, &(Bool){1});
        U64 *_t699 = malloc(sizeof(U64));
        *_t699 = 1;
        U64 *_t700 = malloc(sizeof(U64)); *_t700 = U64_add(DEREF(lo), DEREF(_t699));
        U64_delete(_t699, &(Bool){1});
        U64 *_t701 = malloc(sizeof(U64)); *_t701 = U64_mul(DEREF(_t700), self->elem_size);
        U64_delete(_t700, &(Bool){1});
        U64 *_t702 = malloc(sizeof(U64)); *_t702 = U64_mul(DEREF(lo), self->elem_size);
        U64 *_t703 = malloc(sizeof(U64)); *_t703 = U64_sub(self->count, DEREF(lo));
        void *_t704 = ptr_add(self->data, DEREF(_t701));
        void *_t705 = ptr_add(self->data, DEREF(_t702));
        U64 *_t706 = malloc(sizeof(U64)); *_t706 = U64_mul(DEREF(_t703), self->elem_size);
        U64_delete(_t703, &(Bool){1});
        memmove(_t704, _t705, DEREF(_t706));
        U64_delete(_t701, &(Bool){1});
        U64_delete(_t702, &(Bool){1});
        U64_delete(_t706, &(Bool){1});
        U64 *_t707 = malloc(sizeof(U64)); *_t707 = U64_mul(DEREF(lo), self->elem_size);
        void *_t708 = ptr_add(self->data, DEREF(_t707));
        memcpy(_t708, val, self->elem_size);
        U64_delete(_t707, &(Bool){1});
        free(val);
        U64 *_t709 = malloc(sizeof(U64));
        *_t709 = 1;
        U64 *_t710 = malloc(sizeof(U64)); *_t710 = U64_add(self->count, DEREF(_t709));
        U64_delete(_t709, &(Bool){1});
        self->count = DEREF(_t710);
        U64_delete(_t710, &(Bool){1});
    }
    Bool_delete(found, &(Bool){1});
    U64_delete(lo, &(Bool){1});
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    Bool *_t724 = Str_is_empty(&self->elem_type);
    Bool *_t725 = malloc(sizeof(Bool)); *_t725 = Bool_not(DEREF(_t724));
    Bool_delete(_t724, &(Bool){1});
    if (DEREF(_t725)) {
        {
            U64 *_fi711 = malloc(sizeof(U64));
            *_fi711 = 0;
            while (1) {
                U64 *_t713 = malloc(sizeof(U64));
                *_t713 = 0;
                Range *_t714 = Range_new(DEREF(_t713), self->count);
                U64_delete(_t713, &(Bool){1});
                U64 *_t715 = Range_len(_t714);
                Range_delete(_t714, &(Bool){1});
                Bool *_wcond712 = U64_lt(_fi711, _t715);
                U64_delete(_t715, &(Bool){1});
                if (DEREF(_wcond712)) {
                } else {
                    Bool_delete(_wcond712, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond712, &(Bool){1});
                U64 *_t716 = malloc(sizeof(U64));
                *_t716 = 0;
                Range *_t717 = Range_new(DEREF(_t716), self->count);
                U64_delete(_t716, &(Bool){1});
                U64 *i = Range_get(_t717, DEREF(_fi711));
                Range_delete(_t717, &(Bool){1});
                U64 *_t718 = malloc(sizeof(U64));
                *_t718 = 1;
                U64 *_t719 = malloc(sizeof(U64)); *_t719 = U64_add(DEREF(_fi711), DEREF(_t718));
                U64_delete(_t718, &(Bool){1});
                *_fi711 = DEREF(_t719);
                U64_delete(_t719, &(Bool){1});
                U64 *_t720 = malloc(sizeof(U64)); *_t720 = U64_mul(DEREF(i), self->elem_size);
                U64_delete(i, &(Bool){1});
                void *_t721 = ptr_add(self->data, DEREF(_t720));
                Bool *_t722 = malloc(sizeof(Bool));
                *_t722 = 0;
                dyn_call_delete(&self->elem_type, _t721, _t722);
                U64_delete(_t720, &(Bool){1});
                Bool_delete(_t722, &(Bool){1});
            }
            U64_delete(_fi711, &(Bool){1});
        }
    }
    Bool_delete(_t725, &(Bool){1});
    free(self->data);
    Bool *_t726 = Str_is_empty(&self->elem_type);
    Bool *_t727 = malloc(sizeof(Bool)); *_t727 = Bool_not(DEREF(_t726));
    Bool_delete(_t726, &(Bool){1});
    if (DEREF(_t727)) {
        Bool *_t723 = malloc(sizeof(Bool));
        *_t723 = 0;
        Str_delete(&self->elem_type, _t723);
        Bool_delete(_t723, &(Bool){1});
    }
    Bool_delete(_t727, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 *_t741 = malloc(sizeof(U64)); *_t741 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t741));
    U64_delete(_t741, &(Bool){1});
    {
        U64 *_fi728 = malloc(sizeof(U64));
        *_fi728 = 0;
        while (1) {
            U64 *_t730 = malloc(sizeof(U64));
            *_t730 = 0;
            Range *_t731 = Range_new(DEREF(_t730), self->count);
            U64_delete(_t730, &(Bool){1});
            U64 *_t732 = Range_len(_t731);
            Range_delete(_t731, &(Bool){1});
            Bool *_wcond729 = U64_lt(_fi728, _t732);
            U64_delete(_t732, &(Bool){1});
            if (DEREF(_wcond729)) {
            } else {
                Bool_delete(_wcond729, &(Bool){1});
                break;
            }
            Bool_delete(_wcond729, &(Bool){1});
            U64 *_t733 = malloc(sizeof(U64));
            *_t733 = 0;
            Range *_t734 = Range_new(DEREF(_t733), self->count);
            U64_delete(_t733, &(Bool){1});
            U64 *i = Range_get(_t734, DEREF(_fi728));
            Range_delete(_t734, &(Bool){1});
            U64 *_t735 = malloc(sizeof(U64));
            *_t735 = 1;
            U64 *_t736 = malloc(sizeof(U64)); *_t736 = U64_add(DEREF(_fi728), DEREF(_t735));
            U64_delete(_t735, &(Bool){1});
            *_fi728 = DEREF(_t736);
            U64_delete(_t736, &(Bool){1});
            U64 *_t737 = malloc(sizeof(U64)); *_t737 = U64_mul(DEREF(i), self->elem_size);
            void *_t738 = ptr_add(self->data, DEREF(_t737));
            void *cloned = dyn_call_clone(&self->elem_type, _t738);
            U64_delete(_t737, &(Bool){1});
            U64 *_t739 = malloc(sizeof(U64)); *_t739 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t740 = ptr_add(new_data, DEREF(_t739));
            memcpy(_t740, cloned, self->elem_size);
            U64_delete(_t739, &(Bool){1});
            free(cloned);
        }
        U64_delete(_fi728, &(Bool){1});
    }
    Set *_t742 = malloc(sizeof(Set));
    _t742->data = new_data;
    _t742->count = self->count;
    _t742->cap = self->cap;
    _t742->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t742->elem_type = *_ca; free(_ca); }
    return _t742;
}

U64 *Set_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Set);
    return r;
}

U64 * Str_len(Str * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, U64 * i) {
    (void)self;
    Bool *_t750 = U64_gte(i, &self->count);
    if (DEREF(_t750)) {
        Str *_t744 = Str_lit("Str", 3ULL);
        U64 *_t745 = Str_size();
        U64 *_t746 = malloc(sizeof(U64));
        *_t746 = 1;
        Array *_va16 = Array_new(_t744, _t745, _t746);
        Str_delete(_t744, &(Bool){1});
        U64_delete(_t745, &(Bool){1});
        U64_delete(_t746, &(Bool){1});
        U64 *_t747 = malloc(sizeof(U64));
        *_t747 = 0;
        Str *_t748 = Str_lit("index out of bounds", 19ULL);
        Array_set(_va16, _t747, _t748);
        U64_delete(_t747, &(Bool){1});
        Str *_t749 = Str_lit("Str.get", 7ULL);
        panic(_t749, _va16);
        Str_delete(_t749, &(Bool){1});
    }
    Bool_delete(_t750, &(Bool){1});
    void *_t751 = ptr_add(self->c_str, DEREF(i));
    return _t751;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 *min_len = malloc(sizeof(U64));
    *min_len = a->count;
    Bool *_t757 = U64_lt(&b->count, &a->count);
    if (DEREF(_t757)) {
        *min_len = b->count;
    }
    Bool_delete(_t757, &(Bool){1});
    while (1) {
        Bool *_wcond752 = U64_lt(i, min_len);
        if (DEREF(_wcond752)) {
        } else {
            Bool_delete(_wcond752, &(Bool){1});
            break;
        }
        Bool_delete(_wcond752, &(Bool){1});
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 *_t753 = malloc(sizeof(I64));
        *_t753 = 0;
        Bool *_t754 = I64_neq(c, _t753);
        I64_delete(_t753, &(Bool){1});
        if (DEREF(_t754)) {
            Bool_delete(_t754, &(Bool){1});
            U64_delete(i, &(Bool){1});
            U64_delete(min_len, &(Bool){1});
            return c;
        }
        Bool_delete(_t754, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64 *_t755 = malloc(sizeof(U64));
        *_t755 = 1;
        U64 *_t756 = malloc(sizeof(U64)); *_t756 = U64_add(DEREF(i), DEREF(_t755));
        U64_delete(_t755, &(Bool){1});
        *i = DEREF(_t756);
        U64_delete(_t756, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    U64_delete(min_len, &(Bool){1});
    I64 *_t758 = malloc(sizeof(I64)); *_t758 = U64_cmp(a->count, b->count);
    return _t758;
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    U64 *_t759 = malloc(sizeof(U64));
    *_t759 = 1;
    U64 *_t760 = malloc(sizeof(U64)); *_t760 = U64_add(DEREF(new_len), DEREF(_t759));
    U64_delete(_t759, &(Bool){1});
    U8 *new_data = malloc(DEREF(_t760));
    U64_delete(_t760, &(Bool){1});
    memcpy(new_data, a->c_str, a->count);
    void *_t761 = ptr_add(new_data, a->count);
    memcpy(_t761, b->c_str, b->count);
    I64 *_t762 = malloc(sizeof(I64));
    *_t762 = 0;
    void *_t763 = ptr_add(new_data, DEREF(new_len));
    U8 *_t764 = U8_from_i64(_t762);
    I64_delete(_t762, &(Bool){1});
    U64 *_t765 = malloc(sizeof(U64));
    *_t765 = 1;
    memcpy(_t763, _t764, DEREF(_t765));
    U8_delete(_t764, &(Bool){1});
    U64_delete(_t765, &(Bool){1});
    U64 *_t766 = U64_clone(new_len);
    U64 *_t767 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t768 = malloc(sizeof(Str));
    _t768->c_str = new_data;
    _t768->count = DEREF(_t766);
    _t768->cap = DEREF(_t767);
    U64_delete(_t766, &(Bool){1});
    U64_delete(_t767, &(Bool){1});
    return _t768;
}

Str * Str_with_capacity(U64 * n) {
    U64 *_t769 = malloc(sizeof(U64));
    *_t769 = 1;
    U64 *_t770 = malloc(sizeof(U64)); *_t770 = U64_add(DEREF(n), DEREF(_t769));
    U64_delete(_t769, &(Bool){1});
    U8 *buf = malloc(DEREF(_t770));
    U64_delete(_t770, &(Bool){1});
    I64 *_t771 = malloc(sizeof(I64));
    *_t771 = 0;
    U8 *_t772 = U8_from_i64(_t771);
    I64_delete(_t771, &(Bool){1});
    U64 *_t773 = malloc(sizeof(U64));
    *_t773 = 1;
    memcpy(buf, _t772, DEREF(_t773));
    U8_delete(_t772, &(Bool){1});
    U64_delete(_t773, &(Bool){1});
    I64 *_t774 = malloc(sizeof(I64));
    *_t774 = 0;
    U64 *_t775 = U64_clone(n);
    Str *_t776 = malloc(sizeof(Str));
    _t776->c_str = buf;
    _t776->count = DEREF(_t774);
    _t776->cap = DEREF(_t775);
    I64_delete(_t774, &(Bool){1});
    U64_delete(_t775, &(Bool){1});
    return _t776;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    Bool *_t789 = U64_gte(&self->cap, CAP_VIEW);
    if (DEREF(_t789)) {
        Str *_t777 = Str_lit("Str", 3ULL);
        U64 *_t778 = Str_size();
        U64 *_t779 = malloc(sizeof(U64));
        *_t779 = 1;
        Array *_va17 = Array_new(_t777, _t778, _t779);
        Str_delete(_t777, &(Bool){1});
        U64_delete(_t778, &(Bool){1});
        U64_delete(_t779, &(Bool){1});
        U64 *_t780 = malloc(sizeof(U64));
        *_t780 = 0;
        Str *_t781 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va17, _t780, _t781);
        U64_delete(_t780, &(Bool){1});
        Str *_t782 = Str_lit("Str.push_str", 12ULL);
        panic(_t782, _va17);
        Str_delete(_t782, &(Bool){1});
    }
    Bool_delete(_t789, &(Bool){1});
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool *_t790 = U64_gt(new_len, &self->cap);
    if (DEREF(_t790)) {
        Str *_t783 = Str_lit("Str", 3ULL);
        U64 *_t784 = Str_size();
        U64 *_t785 = malloc(sizeof(U64));
        *_t785 = 1;
        Array *_va18 = Array_new(_t783, _t784, _t785);
        Str_delete(_t783, &(Bool){1});
        U64_delete(_t784, &(Bool){1});
        U64_delete(_t785, &(Bool){1});
        U64 *_t786 = malloc(sizeof(U64));
        *_t786 = 0;
        Str *_t787 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va18, _t786, _t787);
        U64_delete(_t786, &(Bool){1});
        Str *_t788 = Str_lit("Str.push_str", 12ULL);
        panic(_t788, _va18);
        Str_delete(_t788, &(Bool){1});
    }
    Bool_delete(_t790, &(Bool){1});
    void *_t791 = ptr_add(self->c_str, self->count);
    memcpy(_t791, s->c_str, s->count);
    U64 *_t792 = U64_clone(new_len);
    self->count = DEREF(_t792);
    U64_delete(_t792, &(Bool){1});
    I64 *_t793 = malloc(sizeof(I64));
    *_t793 = 0;
    void *_t794 = ptr_add(self->c_str, DEREF(new_len));
    U8 *_t795 = U8_from_i64(_t793);
    I64_delete(_t793, &(Bool){1});
    U64 *_t796 = malloc(sizeof(U64));
    *_t796 = 1;
    memcpy(_t794, _t795, DEREF(_t796));
    U8_delete(_t795, &(Bool){1});
    U64_delete(_t796, &(Bool){1});
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    U64 *_t797 = malloc(sizeof(U64));
    *_t797 = 1;
    U64 *_t798 = malloc(sizeof(U64)); *_t798 = U64_add(val->count, DEREF(_t797));
    U64_delete(_t797, &(Bool){1});
    U8 *new_data = malloc(DEREF(_t798));
    U64_delete(_t798, &(Bool){1});
    memcpy(new_data, val->c_str, val->count);
    I64 *_t799 = malloc(sizeof(I64));
    *_t799 = 0;
    void *_t800 = ptr_add(new_data, val->count);
    U8 *_t801 = U8_from_i64(_t799);
    I64_delete(_t799, &(Bool){1});
    U64 *_t802 = malloc(sizeof(U64));
    *_t802 = 1;
    memcpy(_t800, _t801, DEREF(_t802));
    U8_delete(_t801, &(Bool){1});
    U64_delete(_t802, &(Bool){1});
    Str *_t803 = malloc(sizeof(Str));
    _t803->c_str = new_data;
    _t803->count = val->count;
    _t803->cap = val->count;
    return _t803;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    Bool *_t804 = U64_lt(&self->cap, CAP_VIEW);
    if (DEREF(_t804)) {
        free(self->c_str);
    }
    Bool_delete(_t804, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t805 = Str_clone(val);
    return _t805;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = U64_clone(start);
    U64 *ln = U64_clone(n);
    Bool *_t807 = U64_gt(st, &s->count);
    if (DEREF(_t807)) {
        *st = s->count;
    }
    Bool_delete(_t807, &(Bool){1});
    U64 *_t808 = malloc(sizeof(U64)); *_t808 = U64_add(DEREF(st), DEREF(ln));
    Bool *_t809 = U64_gt(_t808, &s->count);
    U64_delete(_t808, &(Bool){1});
    if (DEREF(_t809)) {
        U64 *_t806 = malloc(sizeof(U64)); *_t806 = U64_sub(s->count, DEREF(st));
        *ln = DEREF(_t806);
        U64_delete(_t806, &(Bool){1});
    }
    Bool_delete(_t809, &(Bool){1});
    void *_t810 = ptr_add(s->c_str, DEREF(st));
    U64 *_t811 = U64_clone(ln);
    U64_delete(ln, &(Bool){1});
    U64 *_t812 = U64_clone(CAP_VIEW);
    Str *_t813 = malloc(sizeof(Str));
    _t813->c_str = _t810;
    _t813->count = DEREF(_t811);
    _t813->cap = DEREF(_t812);
    U64_delete(_t811, &(Bool){1});
    U64_delete(_t812, &(Bool){1});
    U64_delete(st, &(Bool){1});
    return _t813;
}

Bool * Str_contains(Str * a, Str * b) {
    U64 *_t827 = malloc(sizeof(U64));
    *_t827 = 0;
    Bool *_t828 = malloc(sizeof(Bool)); *_t828 = U64_eq(b->count, DEREF(_t827));
    U64_delete(_t827, &(Bool){1});
    if (DEREF(_t828)) {
        Bool *_t814 = malloc(sizeof(Bool));
        *_t814 = 1;
        Bool_delete(_t828, &(Bool){1});
        return _t814;
    }
    Bool_delete(_t828, &(Bool){1});
    Bool *_t829 = U64_gt(&b->count, &a->count);
    if (DEREF(_t829)) {
        Bool *_t815 = malloc(sizeof(Bool));
        *_t815 = 0;
        Bool_delete(_t829, &(Bool){1});
        return _t815;
    }
    Bool_delete(_t829, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t824 = malloc(sizeof(U64)); *_t824 = U64_sub(a->count, b->count);
        Bool *_wcond816 = U64_lte(i, _t824);
        U64_delete(_t824, &(Bool){1});
        if (DEREF(_wcond816)) {
        } else {
            Bool_delete(_wcond816, &(Bool){1});
            break;
        }
        Bool_delete(_wcond816, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond817 = U64_lt(j, &b->count);
            if (DEREF(_wcond817)) {
            } else {
                Bool_delete(_wcond817, &(Bool){1});
                break;
            }
            Bool_delete(_wcond817, &(Bool){1});
            U64 *_t819 = malloc(sizeof(U64)); *_t819 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(a, _t819);
            U8 *bc = Str_get(b, j);
            Bool *_t820 = U8_neq(ac, bc);
            U64_delete(_t819, &(Bool){1});
            if (DEREF(_t820)) {
                Bool *_t818 = malloc(sizeof(Bool));
                *_t818 = 0;
                *found = DEREF(_t818);
                Bool_delete(_t818, &(Bool){1});
            }
            Bool_delete(_t820, &(Bool){1});
            U64 *_t821 = malloc(sizeof(U64));
            *_t821 = 1;
            U64 *_t822 = malloc(sizeof(U64)); *_t822 = U64_add(DEREF(j), DEREF(_t821));
            U64_delete(_t821, &(Bool){1});
            *j = DEREF(_t822);
            U64_delete(_t822, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            Bool *_t823 = malloc(sizeof(Bool));
            *_t823 = 1;
            Bool_delete(found, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t823;
        }
        Bool_delete(found, &(Bool){1});
        U64 *_t825 = malloc(sizeof(U64));
        *_t825 = 1;
        U64 *_t826 = malloc(sizeof(U64)); *_t826 = U64_add(DEREF(i), DEREF(_t825));
        U64_delete(_t825, &(Bool){1});
        *i = DEREF(_t826);
        U64_delete(_t826, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    Bool *_t830 = malloc(sizeof(Bool));
    *_t830 = 0;
    return _t830;
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool *_t837 = U64_gt(&b->count, &a->count);
    if (DEREF(_t837)) {
        Bool *_t831 = malloc(sizeof(Bool));
        *_t831 = 0;
        Bool_delete(_t837, &(Bool){1});
        return _t831;
    }
    Bool_delete(_t837, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool *_wcond832 = U64_lt(i, &b->count);
        if (DEREF(_wcond832)) {
        } else {
            Bool_delete(_wcond832, &(Bool){1});
            break;
        }
        Bool_delete(_wcond832, &(Bool){1});
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool *_t834 = U8_neq(ac, bc);
        if (DEREF(_t834)) {
            Bool *_t833 = malloc(sizeof(Bool));
            *_t833 = 0;
            Bool_delete(_t834, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t833;
        }
        Bool_delete(_t834, &(Bool){1});
        U64 *_t835 = malloc(sizeof(U64));
        *_t835 = 1;
        U64 *_t836 = malloc(sizeof(U64)); *_t836 = U64_add(DEREF(i), DEREF(_t835));
        U64_delete(_t835, &(Bool){1});
        *i = DEREF(_t836);
        U64_delete(_t836, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    Bool *_t838 = malloc(sizeof(Bool));
    *_t838 = 1;
    return _t838;
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool *_t846 = U64_gt(&b->count, &a->count);
    if (DEREF(_t846)) {
        Bool *_t839 = malloc(sizeof(Bool));
        *_t839 = 0;
        Bool_delete(_t846, &(Bool){1});
        return _t839;
    }
    Bool_delete(_t846, &(Bool){1});
    U64 *offset = malloc(sizeof(U64)); *offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool *_wcond840 = U64_lt(i, &b->count);
        if (DEREF(_wcond840)) {
        } else {
            Bool_delete(_wcond840, &(Bool){1});
            break;
        }
        Bool_delete(_wcond840, &(Bool){1});
        U64 *_t842 = malloc(sizeof(U64)); *_t842 = U64_add(DEREF(offset), DEREF(i));
        U8 *ac = Str_get(a, _t842);
        U8 *bc = Str_get(b, i);
        Bool *_t843 = U8_neq(ac, bc);
        U64_delete(_t842, &(Bool){1});
        if (DEREF(_t843)) {
            Bool *_t841 = malloc(sizeof(Bool));
            *_t841 = 0;
            Bool_delete(_t843, &(Bool){1});
            U64_delete(i, &(Bool){1});
            U64_delete(offset, &(Bool){1});
            return _t841;
        }
        Bool_delete(_t843, &(Bool){1});
        U64 *_t844 = malloc(sizeof(U64));
        *_t844 = 1;
        U64 *_t845 = malloc(sizeof(U64)); *_t845 = U64_add(DEREF(i), DEREF(_t844));
        U64_delete(_t844, &(Bool){1});
        *i = DEREF(_t845);
        U64_delete(_t845, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    Bool *_t847 = malloc(sizeof(Bool));
    *_t847 = 1;
    return _t847;
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 *_t848 = malloc(sizeof(U64));
    *_t848 = 0;
    Bool *_t849 = malloc(sizeof(Bool)); *_t849 = U64_eq(self->count, DEREF(_t848));
    U64_delete(_t848, &(Bool){1});
    return _t849;
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    U64 *_t867 = malloc(sizeof(U64));
    *_t867 = 0;
    Bool *_t868 = malloc(sizeof(Bool)); *_t868 = U64_eq(needle->count, DEREF(_t867));
    U64_delete(_t867, &(Bool){1});
    if (DEREF(_t868)) {
        I64 *_t850 = malloc(sizeof(I64));
        *_t850 = 0;
        I64 *_t851 = malloc(sizeof(I64));
        *_t851 = 1;
        I64 *_t852 = malloc(sizeof(I64)); *_t852 = I64_sub(DEREF(_t850), DEREF(_t851));
        I64_delete(_t850, &(Bool){1});
        I64_delete(_t851, &(Bool){1});
        Bool_delete(_t868, &(Bool){1});
        return _t852;
    }
    Bool_delete(_t868, &(Bool){1});
    Bool *_t869 = U64_gt(&needle->count, &self->count);
    if (DEREF(_t869)) {
        I64 *_t853 = malloc(sizeof(I64));
        *_t853 = 0;
        I64 *_t854 = malloc(sizeof(I64));
        *_t854 = 1;
        I64 *_t855 = malloc(sizeof(I64)); *_t855 = I64_sub(DEREF(_t853), DEREF(_t854));
        I64_delete(_t853, &(Bool){1});
        I64_delete(_t854, &(Bool){1});
        Bool_delete(_t869, &(Bool){1});
        return _t855;
    }
    Bool_delete(_t869, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t864 = malloc(sizeof(U64)); *_t864 = U64_sub(self->count, needle->count);
        Bool *_wcond856 = U64_lte(i, _t864);
        U64_delete(_t864, &(Bool){1});
        if (DEREF(_wcond856)) {
        } else {
            Bool_delete(_wcond856, &(Bool){1});
            break;
        }
        Bool_delete(_wcond856, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond857 = U64_lt(j, &needle->count);
            if (DEREF(_wcond857)) {
            } else {
                Bool_delete(_wcond857, &(Bool){1});
                break;
            }
            Bool_delete(_wcond857, &(Bool){1});
            U64 *_t859 = malloc(sizeof(U64)); *_t859 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(self, _t859);
            U8 *bc = Str_get(needle, j);
            Bool *_t860 = U8_neq(ac, bc);
            U64_delete(_t859, &(Bool){1});
            if (DEREF(_t860)) {
                Bool *_t858 = malloc(sizeof(Bool));
                *_t858 = 0;
                *found = DEREF(_t858);
                Bool_delete(_t858, &(Bool){1});
            }
            Bool_delete(_t860, &(Bool){1});
            U64 *_t861 = malloc(sizeof(U64));
            *_t861 = 1;
            U64 *_t862 = malloc(sizeof(U64)); *_t862 = U64_add(DEREF(j), DEREF(_t861));
            U64_delete(_t861, &(Bool){1});
            *j = DEREF(_t862);
            U64_delete(_t862, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            I64 *_t863 = malloc(sizeof(I64)); *_t863 = U64_to_i64(DEREF(i));
            Bool_delete(found, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t863;
        }
        Bool_delete(found, &(Bool){1});
        U64 *_t865 = malloc(sizeof(U64));
        *_t865 = 1;
        U64 *_t866 = malloc(sizeof(U64)); *_t866 = U64_add(DEREF(i), DEREF(_t865));
        U64_delete(_t865, &(Bool){1});
        *i = DEREF(_t866);
        U64_delete(_t866, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    I64 *_t870 = malloc(sizeof(I64));
    *_t870 = 0;
    I64 *_t871 = malloc(sizeof(I64));
    *_t871 = 1;
    I64 *_t872 = malloc(sizeof(I64)); *_t872 = I64_sub(DEREF(_t870), DEREF(_t871));
    I64_delete(_t870, &(Bool){1});
    I64_delete(_t871, &(Bool){1});
    return _t872;
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    U64 *_t890 = malloc(sizeof(U64));
    *_t890 = 0;
    Bool *_t891 = malloc(sizeof(Bool)); *_t891 = U64_eq(needle->count, DEREF(_t890));
    U64_delete(_t890, &(Bool){1});
    if (DEREF(_t891)) {
        I64 *_t873 = malloc(sizeof(I64));
        *_t873 = 0;
        I64 *_t874 = malloc(sizeof(I64));
        *_t874 = 1;
        I64 *_t875 = malloc(sizeof(I64)); *_t875 = I64_sub(DEREF(_t873), DEREF(_t874));
        I64_delete(_t873, &(Bool){1});
        I64_delete(_t874, &(Bool){1});
        Bool_delete(_t891, &(Bool){1});
        return _t875;
    }
    Bool_delete(_t891, &(Bool){1});
    Bool *_t892 = U64_gt(&needle->count, &self->count);
    if (DEREF(_t892)) {
        I64 *_t876 = malloc(sizeof(I64));
        *_t876 = 0;
        I64 *_t877 = malloc(sizeof(I64));
        *_t877 = 1;
        I64 *_t878 = malloc(sizeof(I64)); *_t878 = I64_sub(DEREF(_t876), DEREF(_t877));
        I64_delete(_t876, &(Bool){1});
        I64_delete(_t877, &(Bool){1});
        Bool_delete(_t892, &(Bool){1});
        return _t878;
    }
    Bool_delete(_t892, &(Bool){1});
    I64 *_t893 = malloc(sizeof(I64));
    *_t893 = 0;
    I64 *_t894 = malloc(sizeof(I64));
    *_t894 = 1;
    I64 *last = malloc(sizeof(I64)); *last = I64_sub(DEREF(_t893), DEREF(_t894));
    I64_delete(_t893, &(Bool){1});
    I64_delete(_t894, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t887 = malloc(sizeof(U64)); *_t887 = U64_sub(self->count, needle->count);
        Bool *_wcond879 = U64_lte(i, _t887);
        U64_delete(_t887, &(Bool){1});
        if (DEREF(_wcond879)) {
        } else {
            Bool_delete(_wcond879, &(Bool){1});
            break;
        }
        Bool_delete(_wcond879, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond880 = U64_lt(j, &needle->count);
            if (DEREF(_wcond880)) {
            } else {
                Bool_delete(_wcond880, &(Bool){1});
                break;
            }
            Bool_delete(_wcond880, &(Bool){1});
            U64 *_t882 = malloc(sizeof(U64)); *_t882 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(self, _t882);
            U8 *bc = Str_get(needle, j);
            Bool *_t883 = U8_neq(ac, bc);
            U64_delete(_t882, &(Bool){1});
            if (DEREF(_t883)) {
                Bool *_t881 = malloc(sizeof(Bool));
                *_t881 = 0;
                *found = DEREF(_t881);
                Bool_delete(_t881, &(Bool){1});
            }
            Bool_delete(_t883, &(Bool){1});
            U64 *_t884 = malloc(sizeof(U64));
            *_t884 = 1;
            U64 *_t885 = malloc(sizeof(U64)); *_t885 = U64_add(DEREF(j), DEREF(_t884));
            U64_delete(_t884, &(Bool){1});
            *j = DEREF(_t885);
            U64_delete(_t885, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            I64 *_t886 = malloc(sizeof(I64)); *_t886 = U64_to_i64(DEREF(i));
            *last = DEREF(_t886);
            I64_delete(_t886, &(Bool){1});
        }
        Bool_delete(found, &(Bool){1});
        U64 *_t888 = malloc(sizeof(U64));
        *_t888 = 1;
        U64 *_t889 = malloc(sizeof(U64)); *_t889 = U64_add(DEREF(i), DEREF(_t888));
        U64_delete(_t888, &(Bool){1});
        *i = DEREF(_t889);
        U64_delete(_t889, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    return last;
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    U64 *_t910 = malloc(sizeof(U64));
    *_t910 = 0;
    Bool *_t911 = malloc(sizeof(Bool)); *_t911 = U64_eq(from->count, DEREF(_t910));
    U64_delete(_t910, &(Bool){1});
    if (DEREF(_t911)) {
        Str *_t895 = Str_clone(self);
        Bool_delete(_t911, &(Bool){1});
        return _t895;
    }
    Bool_delete(_t911, &(Bool){1});
    Str *result = Str_lit("", 0ULL);
    U64 *start = malloc(sizeof(U64));
    *start = 0;
    while (1) {
        U64 *_t897 = malloc(sizeof(U64)); *_t897 = U64_sub(self->count, from->count);
        Bool *_wcond896 = U64_lte(start, _t897);
        U64_delete(_t897, &(Bool){1});
        if (DEREF(_wcond896)) {
        } else {
            Bool_delete(_wcond896, &(Bool){1});
            break;
        }
        Bool_delete(_wcond896, &(Bool){1});
        U64 *_t898 = malloc(sizeof(U64)); *_t898 = U64_sub(self->count, DEREF(start));
        Str *rest = Str_substr(self, start, _t898);
        U64_delete(_t898, &(Bool){1});
        I64 *pos = Str_find(rest, from);
        I64 *_t899 = malloc(sizeof(I64));
        *_t899 = 0;
        I64 *_t900 = malloc(sizeof(I64));
        *_t900 = 1;
        I64 *_t901 = malloc(sizeof(I64)); *_t901 = I64_sub(DEREF(_t899), DEREF(_t900));
        I64_delete(_t899, &(Bool){1});
        I64_delete(_t900, &(Bool){1});
        Bool *_t902 = malloc(sizeof(Bool)); *_t902 = I64_eq(DEREF(pos), DEREF(_t901));
        I64_delete(_t901, &(Bool){1});
        if (DEREF(_t902)) {
            result = Str_concat(result, rest);
            Bool_delete(_t902, &(Bool){1});
            I64_delete(pos, &(Bool){1});
            Str_delete(rest, &(Bool){1});
            U64_delete(start, &(Bool){1});
            return result;
        }
        Bool_delete(_t902, &(Bool){1});
        Str_delete(rest, &(Bool){1});
        U64 *_t903 = U64_from_i64(pos);
        Str *_t904 = Str_substr(self, start, _t903);
        U64_delete(_t903, &(Bool){1});
        result = Str_concat(result, _t904);
        Str_delete(_t904, &(Bool){1});
        result = Str_concat(result, to);
        U64 *_t905 = U64_from_i64(pos);
        I64_delete(pos, &(Bool){1});
        U64 *_t906 = malloc(sizeof(U64)); *_t906 = U64_add(DEREF(start), DEREF(_t905));
        U64_delete(_t905, &(Bool){1});
        U64 *_t907 = malloc(sizeof(U64)); *_t907 = U64_add(DEREF(_t906), from->count);
        U64_delete(_t906, &(Bool){1});
        *start = DEREF(_t907);
        U64_delete(_t907, &(Bool){1});
    }
    Bool *_t912 = U64_lt(start, &self->count);
    if (DEREF(_t912)) {
        U64 *_t908 = malloc(sizeof(U64)); *_t908 = U64_sub(self->count, DEREF(start));
        Str *_t909 = Str_substr(self, start, _t908);
        U64_delete(_t908, &(Bool){1});
        result = Str_concat(result, _t909);
        Str_delete(_t909, &(Bool){1});
    }
    Bool_delete(_t912, &(Bool){1});
    U64_delete(start, &(Bool){1});
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    U64 *_t913 = malloc(sizeof(U64));
    *_t913 = 1;
    Str *_t914 = Str_substr(self, i, _t913);
    U64_delete(_t913, &(Bool){1});
    return _t914;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    Bool *_t917 = Str_starts_with(self, prefix);
    if (DEREF(_t917)) {
        U64 *_t915 = malloc(sizeof(U64)); *_t915 = U64_sub(self->count, prefix->count);
        Str *_t916 = Str_substr(self, &prefix->count, _t915);
        U64_delete(_t915, &(Bool){1});
        Bool_delete(_t917, &(Bool){1});
        return _t916;
    }
    Bool_delete(_t917, &(Bool){1});
    Str *_t918 = Str_clone(self);
    return _t918;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    Bool *_t922 = Str_ends_with(self, suffix);
    if (DEREF(_t922)) {
        U64 *_t919 = malloc(sizeof(U64));
        *_t919 = 0;
        U64 *_t920 = malloc(sizeof(U64)); *_t920 = U64_sub(self->count, suffix->count);
        Str *_t921 = Str_substr(self, _t919, _t920);
        U64_delete(_t919, &(Bool){1});
        U64_delete(_t920, &(Bool){1});
        Bool_delete(_t922, &(Bool){1});
        return _t921;
    }
    Bool_delete(_t922, &(Bool){1});
    Str *_t923 = Str_clone(self);
    return _t923;
}

Str * Str_from_byte(U8 * byte) {
    U64 *_t924 = malloc(sizeof(U64));
    *_t924 = 2;
    U8 *buf = malloc(DEREF(_t924));
    U64_delete(_t924, &(Bool){1});
    U64 *_t925 = malloc(sizeof(U64));
    *_t925 = 1;
    memcpy(buf, byte, DEREF(_t925));
    U64_delete(_t925, &(Bool){1});
    U64 *_t926 = malloc(sizeof(U64));
    *_t926 = 1;
    I64 *_t927 = malloc(sizeof(I64));
    *_t927 = 0;
    void *_t928 = ptr_add(buf, DEREF(_t926));
    U8 *_t929 = U8_from_i64(_t927);
    I64_delete(_t927, &(Bool){1});
    U64 *_t930 = malloc(sizeof(U64));
    *_t930 = 1;
    memcpy(_t928, _t929, DEREF(_t930));
    U64_delete(_t926, &(Bool){1});
    U8_delete(_t929, &(Bool){1});
    U64_delete(_t930, &(Bool){1});
    I64 *_t931 = malloc(sizeof(I64));
    *_t931 = 1;
    I64 *_t932 = malloc(sizeof(I64));
    *_t932 = 1;
    Str *_t933 = malloc(sizeof(Str));
    _t933->c_str = buf;
    _t933->count = DEREF(_t931);
    _t933->cap = DEREF(_t932);
    I64_delete(_t931, &(Bool){1});
    I64_delete(_t932, &(Bool){1});
    return _t933;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 *_t974 = malloc(sizeof(U64));
    *_t974 = 0;
    Bool *_t975 = malloc(sizeof(Bool)); *_t975 = U64_eq(self->count, DEREF(_t974));
    U64_delete(_t974, &(Bool){1});
    if (DEREF(_t975)) {
        Str *_t934 = Str_lit("Str", 3ULL);
        U64 *_t935 = Str_size();
        U64 *_t936 = malloc(sizeof(U64));
        *_t936 = 1;
        Array *_va19 = Array_new(_t934, _t935, _t936);
        Str_delete(_t934, &(Bool){1});
        U64_delete(_t935, &(Bool){1});
        U64_delete(_t936, &(Bool){1});
        U64 *_t937 = malloc(sizeof(U64));
        *_t937 = 0;
        Str *_t938 = Str_lit("empty string", 12ULL);
        Array_set(_va19, _t937, _t938);
        U64_delete(_t937, &(Bool){1});
        Str *_t939 = Str_lit("Str.to_i64", 10ULL);
        panic(_t939, _va19);
        Str_delete(_t939, &(Bool){1});
    }
    Bool_delete(_t975, &(Bool){1});
    I64 *result = malloc(sizeof(I64));
    *result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool *neg = malloc(sizeof(Bool));
    *neg = 0;
    U64 *_t976 = malloc(sizeof(U64));
    *_t976 = 0;
    U8 *first = Str_get(self, _t976);
    I64 *_t977 = malloc(sizeof(I64));
    *_t977 = 45;
    U8 *_t978 = U8_from_i64(_t977);
    I64_delete(_t977, &(Bool){1});
    Bool *_t979 = malloc(sizeof(Bool)); *_t979 = U8_eq(DEREF(first), DEREF(_t978));
    U64_delete(_t976, &(Bool){1});
    U8_delete(_t978, &(Bool){1});
    if (DEREF(_t979)) {
        Bool *_t940 = malloc(sizeof(Bool));
        *_t940 = 1;
        *neg = DEREF(_t940);
        Bool_delete(_t940, &(Bool){1});
        I64 *_t941 = malloc(sizeof(I64));
        *_t941 = 1;
        U64 *_t942 = U64_from_i64(_t941);
        I64_delete(_t941, &(Bool){1});
        *i = DEREF(_t942);
        U64_delete(_t942, &(Bool){1});
    }
    Bool_delete(_t979, &(Bool){1});
    Bool *_t980 = malloc(sizeof(Bool)); *_t980 = U64_eq(DEREF(i), self->count);
    if (DEREF(_t980)) {
        Str *_t943 = Str_lit("Str", 3ULL);
        U64 *_t944 = Str_size();
        U64 *_t945 = malloc(sizeof(U64));
        *_t945 = 1;
        Array *_va20 = Array_new(_t943, _t944, _t945);
        Str_delete(_t943, &(Bool){1});
        U64_delete(_t944, &(Bool){1});
        U64_delete(_t945, &(Bool){1});
        U64 *_t946 = malloc(sizeof(U64));
        *_t946 = 0;
        Str *_t947 = Str_lit("no digits", 9ULL);
        Array_set(_va20, _t946, _t947);
        U64_delete(_t946, &(Bool){1});
        Str *_t948 = Str_lit("Str.to_i64", 10ULL);
        panic(_t948, _va20);
        Str_delete(_t948, &(Bool){1});
    }
    Bool_delete(_t980, &(Bool){1});
    while (1) {
        Bool *_wcond949 = U64_lt(i, &self->count);
        if (DEREF(_wcond949)) {
        } else {
            Bool_delete(_wcond949, &(Bool){1});
            break;
        }
        Bool_delete(_wcond949, &(Bool){1});
        U8 *ch = Str_get(self, i);
        I64 *_t960 = malloc(sizeof(I64)); *_t960 = U8_to_i64(DEREF(ch));
        I64 *_t961 = malloc(sizeof(I64));
        *_t961 = 48;
        I64 *d = malloc(sizeof(I64)); *d = I64_sub(DEREF(_t960), DEREF(_t961));
        I64_delete(_t960, &(Bool){1});
        I64_delete(_t961, &(Bool){1});
        I64 *_t962 = malloc(sizeof(I64));
        *_t962 = 0;
        I64 *_t963 = malloc(sizeof(I64));
        *_t963 = 9;
        Bool *_t964 = I64_lt(d, _t962);
        I64_delete(_t962, &(Bool){1});
        Bool *_t965 = I64_gt(d, _t963);
        I64_delete(_t963, &(Bool){1});
        Bool *_t966 = malloc(sizeof(Bool)); *_t966 = Bool_or(DEREF(_t964), DEREF(_t965));
        Bool_delete(_t964, &(Bool){1});
        Bool_delete(_t965, &(Bool){1});
        if (DEREF(_t966)) {
            Str *_t950 = Str_lit("Str", 3ULL);
            U64 *_t951 = Str_size();
            U64 *_t952 = malloc(sizeof(U64));
            *_t952 = 3;
            Array *_va21 = Array_new(_t950, _t951, _t952);
            Str_delete(_t950, &(Bool){1});
            U64_delete(_t951, &(Bool){1});
            U64_delete(_t952, &(Bool){1});
            U64 *_t953 = malloc(sizeof(U64));
            *_t953 = 0;
            Str *_t954 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va21, _t953, _t954);
            U64_delete(_t953, &(Bool){1});
            U64 *_t955 = malloc(sizeof(U64));
            *_t955 = 1;
            Str *_t956 = Str_clone(self);
            Array_set(_va21, _t955, _t956);
            U64_delete(_t955, &(Bool){1});
            U64 *_t957 = malloc(sizeof(U64));
            *_t957 = 2;
            Str *_t958 = Str_lit("'", 1ULL);
            Array_set(_va21, _t957, _t958);
            U64_delete(_t957, &(Bool){1});
            Str *_t959 = Str_lit("Str.to_i64", 10ULL);
            panic(_t959, _va21);
            Str_delete(_t959, &(Bool){1});
        }
        Bool_delete(_t966, &(Bool){1});
        I64 *_t967 = malloc(sizeof(I64));
        *_t967 = 10;
        I64 *_t968 = malloc(sizeof(I64)); *_t968 = I64_mul(DEREF(result), DEREF(_t967));
        I64_delete(_t967, &(Bool){1});
        I64 *_t969 = malloc(sizeof(I64)); *_t969 = I64_add(DEREF(_t968), DEREF(d));
        I64_delete(_t968, &(Bool){1});
        I64_delete(d, &(Bool){1});
        *result = DEREF(_t969);
        I64_delete(_t969, &(Bool){1});
        U64 *_t970 = malloc(sizeof(U64));
        *_t970 = 1;
        U64 *_t971 = malloc(sizeof(U64)); *_t971 = U64_add(DEREF(i), DEREF(_t970));
        U64_delete(_t970, &(Bool){1});
        *i = DEREF(_t971);
        U64_delete(_t971, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    if (DEREF(neg)) {
        I64 *_t972 = malloc(sizeof(I64));
        *_t972 = 0;
        I64 *_t973 = malloc(sizeof(I64)); *_t973 = I64_sub(DEREF(_t972), DEREF(result));
        I64_delete(_t972, &(Bool){1});
        Bool_delete(neg, &(Bool){1});
        I64_delete(result, &(Bool){1});
        return _t973;
    }
    Bool_delete(neg, &(Bool){1});
    return result;
}

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    I64 *_t982 = Str_cmp(a, b);
    I64 *_t983 = malloc(sizeof(I64));
    *_t983 = 0;
    Bool *_t984 = malloc(sizeof(Bool)); *_t984 = I64_eq(DEREF(_t982), DEREF(_t983));
    I64_delete(_t982, &(Bool){1});
    I64_delete(_t983, &(Bool){1});
    return _t984;
}

Bool * Str_lt(Str * a, Str * b) {
    I64 *_t985 = malloc(sizeof(I64));
    *_t985 = 0;
    I64 *_t986 = malloc(sizeof(I64));
    *_t986 = 1;
    I64 *_t987 = Str_cmp(a, b);
    I64 *_t988 = malloc(sizeof(I64)); *_t988 = I64_sub(DEREF(_t985), DEREF(_t986));
    I64_delete(_t985, &(Bool){1});
    I64_delete(_t986, &(Bool){1});
    Bool *_t989 = malloc(sizeof(Bool)); *_t989 = I64_eq(DEREF(_t987), DEREF(_t988));
    I64_delete(_t987, &(Bool){1});
    I64_delete(_t988, &(Bool){1});
    return _t989;
}

Bool * Str_gt(Str * a, Str * b) {
    I64 *_t990 = Str_cmp(a, b);
    I64 *_t991 = malloc(sizeof(I64));
    *_t991 = 1;
    Bool *_t992 = malloc(sizeof(Bool)); *_t992 = I64_eq(DEREF(_t990), DEREF(_t991));
    I64_delete(_t990, &(Bool){1});
    I64_delete(_t991, &(Bool){1});
    return _t992;
}

Bool * Str_neq(Str * a, Str * b) {
    Bool *_t993 = Str_eq(a, b);
    Bool *_t994 = malloc(sizeof(Bool)); *_t994 = Bool_not(DEREF(_t993));
    Bool_delete(_t993, &(Bool){1});
    return _t994;
}

Bool * Str_lte(Str * a, Str * b) {
    Bool *_t995 = Str_gt(a, b);
    Bool *_t996 = malloc(sizeof(Bool)); *_t996 = Bool_not(DEREF(_t995));
    Bool_delete(_t995, &(Bool){1});
    return _t996;
}

Bool * Str_gte(Str * a, Str * b) {
    Bool *_t997 = Str_lt(a, b);
    Bool *_t998 = malloc(sizeof(Bool)); *_t998 = Bool_not(DEREF(_t997));
    Bool_delete(_t997, &(Bool){1});
    return _t998;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t999 = malloc(DEREF(elem_size));
    U64 *_t1000 = malloc(sizeof(U64));
    *_t1000 = 0;
    I64 *_t1001 = malloc(sizeof(I64));
    *_t1001 = 1;
    U64 *_t1002 = U64_clone(elem_size);
    Vec *_t1003 = malloc(sizeof(Vec));
    _t1003->data = _t999;
    _t1003->count = DEREF(_t1000);
    _t1003->cap = DEREF(_t1001);
    _t1003->elem_size = DEREF(_t1002);
    { Str *_ca = Str_clone(elem_type); _t1003->elem_type = *_ca; free(_ca); }
    U64_delete(_t1000, &(Bool){1});
    I64_delete(_t1001, &(Bool){1});
    U64_delete(_t1002, &(Bool){1});
    return _t1003;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    Bool *_t1008 = malloc(sizeof(Bool)); *_t1008 = U64_eq(self->count, self->cap);
    if (DEREF(_t1008)) {
        U64 *_t1004 = malloc(sizeof(U64));
        *_t1004 = 2;
        U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t1004));
        U64_delete(_t1004, &(Bool){1});
        U64 *_t1005 = malloc(sizeof(U64)); *_t1005 = U64_mul(DEREF(new_cap), self->elem_size);
        void *_t1006 = realloc(self->data, DEREF(_t1005));
        U64_delete(_t1005, &(Bool){1});
        self->data = _t1006;
        U64 *_t1007 = U64_clone(new_cap);
        U64_delete(new_cap, &(Bool){1});
        self->cap = DEREF(_t1007);
        U64_delete(_t1007, &(Bool){1});
    }
    Bool_delete(_t1008, &(Bool){1});
    U64 *_t1009 = malloc(sizeof(U64)); *_t1009 = U64_mul(self->count, self->elem_size);
    void *_t1010 = ptr_add(self->data, DEREF(_t1009));
    memcpy(_t1010, val, self->elem_size);
    U64_delete(_t1009, &(Bool){1});
    free(val);
    U64 *_t1011 = malloc(sizeof(U64));
    *_t1011 = 1;
    U64 *_t1012 = malloc(sizeof(U64)); *_t1012 = U64_add(self->count, DEREF(_t1011));
    U64_delete(_t1011, &(Bool){1});
    self->count = DEREF(_t1012);
    U64_delete(_t1012, &(Bool){1});
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    Bool *_t1027 = U64_gte(i, &self->count);
    if (DEREF(_t1027)) {
        Str *_t1013 = Str_lit("Str", 3ULL);
        U64 *_t1014 = Str_size();
        U64 *_t1015 = malloc(sizeof(U64));
        *_t1015 = 5;
        Array *_va22 = Array_new(_t1013, _t1014, _t1015);
        Str_delete(_t1013, &(Bool){1});
        U64_delete(_t1014, &(Bool){1});
        U64_delete(_t1015, &(Bool){1});
        U64 *_t1016 = malloc(sizeof(U64));
        *_t1016 = 0;
        Str *_t1017 = Str_lit("index ", 6ULL);
        Array_set(_va22, _t1016, _t1017);
        U64_delete(_t1016, &(Bool){1});
        U64 *_t1018 = malloc(sizeof(U64));
        *_t1018 = 1;
        Str *_t1019 = U64_to_str(DEREF(i));
        Array_set(_va22, _t1018, _t1019);
        U64_delete(_t1018, &(Bool){1});
        U64 *_t1020 = malloc(sizeof(U64));
        *_t1020 = 2;
        Str *_t1021 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va22, _t1020, _t1021);
        U64_delete(_t1020, &(Bool){1});
        U64 *_t1022 = malloc(sizeof(U64));
        *_t1022 = 3;
        Str *_t1023 = U64_to_str(self->count);
        Array_set(_va22, _t1022, _t1023);
        U64_delete(_t1022, &(Bool){1});
        U64 *_t1024 = malloc(sizeof(U64));
        *_t1024 = 4;
        Str *_t1025 = Str_lit(")", 1ULL);
        Array_set(_va22, _t1024, _t1025);
        U64_delete(_t1024, &(Bool){1});
        Str *_t1026 = Str_lit("Vec.get", 7ULL);
        panic(_t1026, _va22);
        Str_delete(_t1026, &(Bool){1});
    }
    Bool_delete(_t1027, &(Bool){1});
    U64 *_t1028 = malloc(sizeof(U64)); *_t1028 = U64_mul(DEREF(i), self->elem_size);
    void *_t1029 = ptr_add(self->data, DEREF(_t1028));
    U64_delete(_t1028, &(Bool){1});
    return _t1029;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    Bool *_t1043 = Str_is_empty(&self->elem_type);
    Bool *_t1044 = malloc(sizeof(Bool)); *_t1044 = Bool_not(DEREF(_t1043));
    Bool_delete(_t1043, &(Bool){1});
    if (DEREF(_t1044)) {
        {
            U64 *_fi1030 = malloc(sizeof(U64));
            *_fi1030 = 0;
            while (1) {
                U64 *_t1032 = malloc(sizeof(U64));
                *_t1032 = 0;
                Range *_t1033 = Range_new(DEREF(_t1032), self->count);
                U64_delete(_t1032, &(Bool){1});
                U64 *_t1034 = Range_len(_t1033);
                Range_delete(_t1033, &(Bool){1});
                Bool *_wcond1031 = U64_lt(_fi1030, _t1034);
                U64_delete(_t1034, &(Bool){1});
                if (DEREF(_wcond1031)) {
                } else {
                    Bool_delete(_wcond1031, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond1031, &(Bool){1});
                U64 *_t1035 = malloc(sizeof(U64));
                *_t1035 = 0;
                Range *_t1036 = Range_new(DEREF(_t1035), self->count);
                U64_delete(_t1035, &(Bool){1});
                U64 *i = Range_get(_t1036, DEREF(_fi1030));
                Range_delete(_t1036, &(Bool){1});
                U64 *_t1037 = malloc(sizeof(U64));
                *_t1037 = 1;
                U64 *_t1038 = malloc(sizeof(U64)); *_t1038 = U64_add(DEREF(_fi1030), DEREF(_t1037));
                U64_delete(_t1037, &(Bool){1});
                *_fi1030 = DEREF(_t1038);
                U64_delete(_t1038, &(Bool){1});
                U64 *_t1039 = malloc(sizeof(U64)); *_t1039 = U64_mul(DEREF(i), self->elem_size);
                U64_delete(i, &(Bool){1});
                void *_t1040 = ptr_add(self->data, DEREF(_t1039));
                Bool *_t1041 = malloc(sizeof(Bool));
                *_t1041 = 0;
                dyn_call_delete(&self->elem_type, _t1040, _t1041);
                U64_delete(_t1039, &(Bool){1});
                Bool_delete(_t1041, &(Bool){1});
            }
            U64_delete(_fi1030, &(Bool){1});
        }
    }
    Bool_delete(_t1044, &(Bool){1});
    free(self->data);
    Bool *_t1045 = Str_is_empty(&self->elem_type);
    Bool *_t1046 = malloc(sizeof(Bool)); *_t1046 = Bool_not(DEREF(_t1045));
    Bool_delete(_t1045, &(Bool){1});
    if (DEREF(_t1046)) {
        Bool *_t1042 = malloc(sizeof(Bool));
        *_t1042 = 0;
        Str_delete(&self->elem_type, _t1042);
        Bool_delete(_t1042, &(Bool){1});
    }
    Bool_delete(_t1046, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 *_t1060 = malloc(sizeof(U64)); *_t1060 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t1060));
    U64_delete(_t1060, &(Bool){1});
    {
        U64 *_fi1047 = malloc(sizeof(U64));
        *_fi1047 = 0;
        while (1) {
            U64 *_t1049 = malloc(sizeof(U64));
            *_t1049 = 0;
            Range *_t1050 = Range_new(DEREF(_t1049), self->count);
            U64_delete(_t1049, &(Bool){1});
            U64 *_t1051 = Range_len(_t1050);
            Range_delete(_t1050, &(Bool){1});
            Bool *_wcond1048 = U64_lt(_fi1047, _t1051);
            U64_delete(_t1051, &(Bool){1});
            if (DEREF(_wcond1048)) {
            } else {
                Bool_delete(_wcond1048, &(Bool){1});
                break;
            }
            Bool_delete(_wcond1048, &(Bool){1});
            U64 *_t1052 = malloc(sizeof(U64));
            *_t1052 = 0;
            Range *_t1053 = Range_new(DEREF(_t1052), self->count);
            U64_delete(_t1052, &(Bool){1});
            U64 *i = Range_get(_t1053, DEREF(_fi1047));
            Range_delete(_t1053, &(Bool){1});
            U64 *_t1054 = malloc(sizeof(U64));
            *_t1054 = 1;
            U64 *_t1055 = malloc(sizeof(U64)); *_t1055 = U64_add(DEREF(_fi1047), DEREF(_t1054));
            U64_delete(_t1054, &(Bool){1});
            *_fi1047 = DEREF(_t1055);
            U64_delete(_t1055, &(Bool){1});
            U64 *_t1056 = malloc(sizeof(U64)); *_t1056 = U64_mul(DEREF(i), self->elem_size);
            void *_t1057 = ptr_add(self->data, DEREF(_t1056));
            void *cloned = dyn_call_clone(&self->elem_type, _t1057);
            U64_delete(_t1056, &(Bool){1});
            U64 *_t1058 = malloc(sizeof(U64)); *_t1058 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t1059 = ptr_add(new_data, DEREF(_t1058));
            memcpy(_t1059, cloned, self->elem_size);
            U64_delete(_t1058, &(Bool){1});
            free(cloned);
        }
        U64_delete(_fi1047, &(Bool){1});
    }
    Vec *_t1061 = malloc(sizeof(Vec));
    _t1061->data = new_data;
    _t1061->count = self->count;
    _t1061->cap = self->cap;
    _t1061->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1061->elem_type = *_ca; free(_ca); }
    return _t1061;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t1079 = Str_lit("Str", 3ULL);
    U64 *_t1080 = Str_size();
    Vec *parts = Vec_new(_t1079, _t1080);
    Str_delete(_t1079, &(Bool){1});
    U64_delete(_t1080, &(Bool){1});
    U64 *_t1081 = Str_len(delim);
    U64 *_t1082 = malloc(sizeof(U64));
    *_t1082 = 0;
    Bool *_t1083 = malloc(sizeof(Bool)); *_t1083 = U64_eq(DEREF(_t1081), DEREF(_t1082));
    U64_delete(_t1081, &(Bool){1});
    U64_delete(_t1082, &(Bool){1});
    if (DEREF(_t1083)) {
        Str *_t1063 = Str_clone(s);
        Vec_push(parts, _t1063);
        Bool_delete(_t1083, &(Bool){1});
        return parts;
    }
    Bool_delete(_t1083, &(Bool){1});
    U64 *start = malloc(sizeof(U64));
    *start = 0;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    while (1) {
        U64 *_t1073 = Str_len(s);
        U64 *_t1074 = Str_len(delim);
        U64 *_t1075 = malloc(sizeof(U64)); *_t1075 = U64_sub(DEREF(_t1073), DEREF(_t1074));
        U64_delete(_t1073, &(Bool){1});
        U64_delete(_t1074, &(Bool){1});
        Bool *_wcond1064 = U64_lte(pos, _t1075);
        U64_delete(_t1075, &(Bool){1});
        if (DEREF(_wcond1064)) {
        } else {
            Bool_delete(_wcond1064, &(Bool){1});
            break;
        }
        Bool_delete(_wcond1064, &(Bool){1});
        U64 *_t1076 = Str_len(delim);
        Str *_t1077 = Str_substr(s, pos, _t1076);
        U64_delete(_t1076, &(Bool){1});
        Bool *_t1078 = Str_eq(_t1077, delim);
        Str_delete(_t1077, &(Bool){1});
        if (DEREF(_t1078)) {
            U64 *_t1065 = malloc(sizeof(U64)); *_t1065 = U64_sub(DEREF(pos), DEREF(start));
            Str *_t1066 = Str_substr(s, start, _t1065);
            U64_delete(_t1065, &(Bool){1});
            Str *_t1067 = Str_clone(_t1066);
            Str_delete(_t1066, &(Bool){1});
            Vec_push(parts, _t1067);
            U64 *_t1068 = Str_len(delim);
            U64 *_t1069 = malloc(sizeof(U64)); *_t1069 = U64_add(DEREF(pos), DEREF(_t1068));
            U64_delete(_t1068, &(Bool){1});
            *start = DEREF(_t1069);
            U64_delete(_t1069, &(Bool){1});
            U64 *_t1070 = U64_clone(start);
            *pos = DEREF(_t1070);
            U64_delete(_t1070, &(Bool){1});
        } else {
            U64 *_t1071 = malloc(sizeof(U64));
            *_t1071 = 1;
            U64 *_t1072 = malloc(sizeof(U64)); *_t1072 = U64_add(DEREF(pos), DEREF(_t1071));
            U64_delete(_t1071, &(Bool){1});
            *pos = DEREF(_t1072);
            U64_delete(_t1072, &(Bool){1});
        }
        Bool_delete(_t1078, &(Bool){1});
    }
    U64_delete(pos, &(Bool){1});
    U64 *_t1084 = Str_len(s);
    U64 *_t1085 = malloc(sizeof(U64)); *_t1085 = U64_sub(DEREF(_t1084), DEREF(start));
    U64_delete(_t1084, &(Bool){1});
    Str *_t1086 = Str_substr(s, start, _t1085);
    U64_delete(_t1085, &(Bool){1});
    U64_delete(start, &(Bool){1});
    Str *_t1087 = Str_clone(_t1086);
    Str_delete(_t1086, &(Bool){1});
    Vec_push(parts, _t1087);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 *_t1095 = Vec_len(parts);
    U64 *_t1096 = malloc(sizeof(U64));
    *_t1096 = 0;
    Bool *_t1097 = malloc(sizeof(Bool)); *_t1097 = U64_eq(DEREF(_t1095), DEREF(_t1096));
    U64_delete(_t1095, &(Bool){1});
    U64_delete(_t1096, &(Bool){1});
    if (DEREF(_t1097)) {
        Str *_t1088 = Str_lit("", 0ULL);
        Bool_delete(_t1097, &(Bool){1});
        return _t1088;
    }
    Bool_delete(_t1097, &(Bool){1});
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t1090 = Vec_len(parts);
        Bool *_wcond1089 = U64_lt(i, _t1090);
        U64_delete(_t1090, &(Bool){1});
        if (DEREF(_wcond1089)) {
        } else {
            Bool_delete(_wcond1089, &(Bool){1});
            break;
        }
        Bool_delete(_wcond1089, &(Bool){1});
        U64 *_t1091 = malloc(sizeof(U64));
        *_t1091 = 0;
        Bool *_t1092 = U64_gt(i, _t1091);
        U64_delete(_t1091, &(Bool){1});
        if (DEREF(_t1092)) {
            result = Str_concat(result, sep);
        }
        Bool_delete(_t1092, &(Bool){1});
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        U64 *_t1093 = malloc(sizeof(U64));
        *_t1093 = 1;
        U64 *_t1094 = malloc(sizeof(U64)); *_t1094 = U64_add(DEREF(i), DEREF(_t1093));
        U64_delete(_t1093, &(Bool){1});
        *i = DEREF(_t1094);
        U64_delete(_t1094, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    return result;
}

TokenType *TokenType_Eof() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Eof };
    return r;
}
TokenType *TokenType_LParen() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_LParen };
    return r;
}
TokenType *TokenType_RParen() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_RParen };
    return r;
}
TokenType *TokenType_LBrace() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_LBrace };
    return r;
}
TokenType *TokenType_RBrace() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_RBrace };
    return r;
}
TokenType *TokenType_LBracket() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_LBracket };
    return r;
}
TokenType *TokenType_RBracket() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_RBracket };
    return r;
}
TokenType *TokenType_Comma() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Comma };
    return r;
}
TokenType *TokenType_Colon() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Colon };
    return r;
}
TokenType *TokenType_Question() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Question };
    return r;
}
TokenType *TokenType_Bang() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Bang };
    return r;
}
TokenType *TokenType_Minus() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Minus };
    return r;
}
TokenType *TokenType_Plus() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Plus };
    return r;
}
TokenType *TokenType_Star() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Star };
    return r;
}
TokenType *TokenType_Slash() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Slash };
    return r;
}
TokenType *TokenType_Dot() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Dot };
    return r;
}
TokenType *TokenType_DotDot() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_DotDot };
    return r;
}
TokenType *TokenType_Eq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Eq };
    return r;
}
TokenType *TokenType_EqEq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_EqEq };
    return r;
}
TokenType *TokenType_Neq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Neq };
    return r;
}
TokenType *TokenType_Lt() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Lt };
    return r;
}
TokenType *TokenType_LtEq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_LtEq };
    return r;
}
TokenType *TokenType_Gt() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Gt };
    return r;
}
TokenType *TokenType_GtEq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_GtEq };
    return r;
}
TokenType *TokenType_ColonEq() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_ColonEq };
    return r;
}
TokenType *TokenType_Ident() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Ident };
    return r;
}
TokenType *TokenType_StringTok() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_StringTok };
    return r;
}
TokenType *TokenType_Number() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Number };
    return r;
}
TokenType *TokenType_Char() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Char };
    return r;
}
TokenType *TokenType_KwMode() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwMode };
    return r;
}
TokenType *TokenType_KwMut() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwMut };
    return r;
}
TokenType *TokenType_KwOwn() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwOwn };
    return r;
}
TokenType *TokenType_KwRef() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwRef };
    return r;
}
TokenType *TokenType_KwStruct() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwStruct };
    return r;
}
TokenType *TokenType_KwExtStruct() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwExtStruct };
    return r;
}
TokenType *TokenType_KwEnum() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwEnum };
    return r;
}
TokenType *TokenType_KwNamespace() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwNamespace };
    return r;
}
TokenType *TokenType_KwFunc() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwFunc };
    return r;
}
TokenType *TokenType_KwProc() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwProc };
    return r;
}
TokenType *TokenType_KwTest() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwTest };
    return r;
}
TokenType *TokenType_KwMacro() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwMacro };
    return r;
}
TokenType *TokenType_KwExtFunc() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwExtFunc };
    return r;
}
TokenType *TokenType_KwExtProc() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwExtProc };
    return r;
}
TokenType *TokenType_KwReturns() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwReturns };
    return r;
}
TokenType *TokenType_KwThrows() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwThrows };
    return r;
}
TokenType *TokenType_KwIf() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwIf };
    return r;
}
TokenType *TokenType_KwElse() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwElse };
    return r;
}
TokenType *TokenType_KwWhile() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwWhile };
    return r;
}
TokenType *TokenType_KwFor() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwFor };
    return r;
}
TokenType *TokenType_KwIn() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwIn };
    return r;
}
TokenType *TokenType_KwSwitch() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwSwitch };
    return r;
}
TokenType *TokenType_KwMatch() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwMatch };
    return r;
}
TokenType *TokenType_KwCase() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwCase };
    return r;
}
TokenType *TokenType_KwDefault() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwDefault };
    return r;
}
TokenType *TokenType_KwReturn() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwReturn };
    return r;
}
TokenType *TokenType_KwThrow() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwThrow };
    return r;
}
TokenType *TokenType_KwCatch() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwCatch };
    return r;
}
TokenType *TokenType_KwBreak() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwBreak };
    return r;
}
TokenType *TokenType_KwContinue() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwContinue };
    return r;
}
TokenType *TokenType_KwDefer() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwDefer };
    return r;
}
TokenType *TokenType_KwTrue() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwTrue };
    return r;
}
TokenType *TokenType_KwFalse() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwFalse };
    return r;
}
TokenType *TokenType_Error() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_Error };
    return r;
}
Bool *TokenType_is_Eof(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Eof);
    return r;
}
Bool *TokenType_is_LParen(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_LParen);
    return r;
}
Bool *TokenType_is_RParen(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_RParen);
    return r;
}
Bool *TokenType_is_LBrace(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_LBrace);
    return r;
}
Bool *TokenType_is_RBrace(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_RBrace);
    return r;
}
Bool *TokenType_is_LBracket(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_LBracket);
    return r;
}
Bool *TokenType_is_RBracket(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_RBracket);
    return r;
}
Bool *TokenType_is_Comma(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Comma);
    return r;
}
Bool *TokenType_is_Colon(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Colon);
    return r;
}
Bool *TokenType_is_Question(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Question);
    return r;
}
Bool *TokenType_is_Bang(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Bang);
    return r;
}
Bool *TokenType_is_Minus(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Minus);
    return r;
}
Bool *TokenType_is_Plus(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Plus);
    return r;
}
Bool *TokenType_is_Star(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Star);
    return r;
}
Bool *TokenType_is_Slash(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Slash);
    return r;
}
Bool *TokenType_is_Dot(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Dot);
    return r;
}
Bool *TokenType_is_DotDot(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_DotDot);
    return r;
}
Bool *TokenType_is_Eq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Eq);
    return r;
}
Bool *TokenType_is_EqEq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_EqEq);
    return r;
}
Bool *TokenType_is_Neq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Neq);
    return r;
}
Bool *TokenType_is_Lt(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Lt);
    return r;
}
Bool *TokenType_is_LtEq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_LtEq);
    return r;
}
Bool *TokenType_is_Gt(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Gt);
    return r;
}
Bool *TokenType_is_GtEq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_GtEq);
    return r;
}
Bool *TokenType_is_ColonEq(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_ColonEq);
    return r;
}
Bool *TokenType_is_Ident(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Ident);
    return r;
}
Bool *TokenType_is_StringTok(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_StringTok);
    return r;
}
Bool *TokenType_is_Number(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Number);
    return r;
}
Bool *TokenType_is_Char(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Char);
    return r;
}
Bool *TokenType_is_KwMode(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwMode);
    return r;
}
Bool *TokenType_is_KwMut(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwMut);
    return r;
}
Bool *TokenType_is_KwOwn(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwOwn);
    return r;
}
Bool *TokenType_is_KwRef(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwRef);
    return r;
}
Bool *TokenType_is_KwStruct(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwStruct);
    return r;
}
Bool *TokenType_is_KwExtStruct(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwExtStruct);
    return r;
}
Bool *TokenType_is_KwEnum(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwEnum);
    return r;
}
Bool *TokenType_is_KwNamespace(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwNamespace);
    return r;
}
Bool *TokenType_is_KwFunc(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwFunc);
    return r;
}
Bool *TokenType_is_KwProc(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwProc);
    return r;
}
Bool *TokenType_is_KwTest(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwTest);
    return r;
}
Bool *TokenType_is_KwMacro(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwMacro);
    return r;
}
Bool *TokenType_is_KwExtFunc(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwExtFunc);
    return r;
}
Bool *TokenType_is_KwExtProc(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwExtProc);
    return r;
}
Bool *TokenType_is_KwReturns(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwReturns);
    return r;
}
Bool *TokenType_is_KwThrows(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwThrows);
    return r;
}
Bool *TokenType_is_KwIf(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwIf);
    return r;
}
Bool *TokenType_is_KwElse(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwElse);
    return r;
}
Bool *TokenType_is_KwWhile(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwWhile);
    return r;
}
Bool *TokenType_is_KwFor(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwFor);
    return r;
}
Bool *TokenType_is_KwIn(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwIn);
    return r;
}
Bool *TokenType_is_KwSwitch(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwSwitch);
    return r;
}
Bool *TokenType_is_KwMatch(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwMatch);
    return r;
}
Bool *TokenType_is_KwCase(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwCase);
    return r;
}
Bool *TokenType_is_KwDefault(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwDefault);
    return r;
}
Bool *TokenType_is_KwReturn(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwReturn);
    return r;
}
Bool *TokenType_is_KwThrow(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwThrow);
    return r;
}
Bool *TokenType_is_KwCatch(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwCatch);
    return r;
}
Bool *TokenType_is_KwBreak(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwBreak);
    return r;
}
Bool *TokenType_is_KwContinue(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwContinue);
    return r;
}
Bool *TokenType_is_KwDefer(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwDefer);
    return r;
}
Bool *TokenType_is_KwTrue(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwTrue);
    return r;
}
Bool *TokenType_is_KwFalse(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwFalse);
    return r;
}
Bool *TokenType_is_Error(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Error);
    return r;
}
Bool * TokenType_eq(TokenType * self, TokenType * other) {
    (void)self;
    Bool *_t1161 = TokenType_is_Eof(self);
    if (DEREF(_t1161)) {
        Bool *_t1098 = TokenType_is_Eof(other);
        Bool_delete(_t1161, &(Bool){1});
        return _t1098;
    }
    Bool_delete(_t1161, &(Bool){1});
    Bool *_t1162 = TokenType_is_LParen(self);
    if (DEREF(_t1162)) {
        Bool *_t1099 = TokenType_is_LParen(other);
        Bool_delete(_t1162, &(Bool){1});
        return _t1099;
    }
    Bool_delete(_t1162, &(Bool){1});
    Bool *_t1163 = TokenType_is_RParen(self);
    if (DEREF(_t1163)) {
        Bool *_t1100 = TokenType_is_RParen(other);
        Bool_delete(_t1163, &(Bool){1});
        return _t1100;
    }
    Bool_delete(_t1163, &(Bool){1});
    Bool *_t1164 = TokenType_is_LBrace(self);
    if (DEREF(_t1164)) {
        Bool *_t1101 = TokenType_is_LBrace(other);
        Bool_delete(_t1164, &(Bool){1});
        return _t1101;
    }
    Bool_delete(_t1164, &(Bool){1});
    Bool *_t1165 = TokenType_is_RBrace(self);
    if (DEREF(_t1165)) {
        Bool *_t1102 = TokenType_is_RBrace(other);
        Bool_delete(_t1165, &(Bool){1});
        return _t1102;
    }
    Bool_delete(_t1165, &(Bool){1});
    Bool *_t1166 = TokenType_is_LBracket(self);
    if (DEREF(_t1166)) {
        Bool *_t1103 = TokenType_is_LBracket(other);
        Bool_delete(_t1166, &(Bool){1});
        return _t1103;
    }
    Bool_delete(_t1166, &(Bool){1});
    Bool *_t1167 = TokenType_is_RBracket(self);
    if (DEREF(_t1167)) {
        Bool *_t1104 = TokenType_is_RBracket(other);
        Bool_delete(_t1167, &(Bool){1});
        return _t1104;
    }
    Bool_delete(_t1167, &(Bool){1});
    Bool *_t1168 = TokenType_is_Comma(self);
    if (DEREF(_t1168)) {
        Bool *_t1105 = TokenType_is_Comma(other);
        Bool_delete(_t1168, &(Bool){1});
        return _t1105;
    }
    Bool_delete(_t1168, &(Bool){1});
    Bool *_t1169 = TokenType_is_Colon(self);
    if (DEREF(_t1169)) {
        Bool *_t1106 = TokenType_is_Colon(other);
        Bool_delete(_t1169, &(Bool){1});
        return _t1106;
    }
    Bool_delete(_t1169, &(Bool){1});
    Bool *_t1170 = TokenType_is_Question(self);
    if (DEREF(_t1170)) {
        Bool *_t1107 = TokenType_is_Question(other);
        Bool_delete(_t1170, &(Bool){1});
        return _t1107;
    }
    Bool_delete(_t1170, &(Bool){1});
    Bool *_t1171 = TokenType_is_Bang(self);
    if (DEREF(_t1171)) {
        Bool *_t1108 = TokenType_is_Bang(other);
        Bool_delete(_t1171, &(Bool){1});
        return _t1108;
    }
    Bool_delete(_t1171, &(Bool){1});
    Bool *_t1172 = TokenType_is_Minus(self);
    if (DEREF(_t1172)) {
        Bool *_t1109 = TokenType_is_Minus(other);
        Bool_delete(_t1172, &(Bool){1});
        return _t1109;
    }
    Bool_delete(_t1172, &(Bool){1});
    Bool *_t1173 = TokenType_is_Plus(self);
    if (DEREF(_t1173)) {
        Bool *_t1110 = TokenType_is_Plus(other);
        Bool_delete(_t1173, &(Bool){1});
        return _t1110;
    }
    Bool_delete(_t1173, &(Bool){1});
    Bool *_t1174 = TokenType_is_Star(self);
    if (DEREF(_t1174)) {
        Bool *_t1111 = TokenType_is_Star(other);
        Bool_delete(_t1174, &(Bool){1});
        return _t1111;
    }
    Bool_delete(_t1174, &(Bool){1});
    Bool *_t1175 = TokenType_is_Slash(self);
    if (DEREF(_t1175)) {
        Bool *_t1112 = TokenType_is_Slash(other);
        Bool_delete(_t1175, &(Bool){1});
        return _t1112;
    }
    Bool_delete(_t1175, &(Bool){1});
    Bool *_t1176 = TokenType_is_Dot(self);
    if (DEREF(_t1176)) {
        Bool *_t1113 = TokenType_is_Dot(other);
        Bool_delete(_t1176, &(Bool){1});
        return _t1113;
    }
    Bool_delete(_t1176, &(Bool){1});
    Bool *_t1177 = TokenType_is_DotDot(self);
    if (DEREF(_t1177)) {
        Bool *_t1114 = TokenType_is_DotDot(other);
        Bool_delete(_t1177, &(Bool){1});
        return _t1114;
    }
    Bool_delete(_t1177, &(Bool){1});
    Bool *_t1178 = TokenType_is_Eq(self);
    if (DEREF(_t1178)) {
        Bool *_t1115 = TokenType_is_Eq(other);
        Bool_delete(_t1178, &(Bool){1});
        return _t1115;
    }
    Bool_delete(_t1178, &(Bool){1});
    Bool *_t1179 = TokenType_is_EqEq(self);
    if (DEREF(_t1179)) {
        Bool *_t1116 = TokenType_is_EqEq(other);
        Bool_delete(_t1179, &(Bool){1});
        return _t1116;
    }
    Bool_delete(_t1179, &(Bool){1});
    Bool *_t1180 = TokenType_is_Neq(self);
    if (DEREF(_t1180)) {
        Bool *_t1117 = TokenType_is_Neq(other);
        Bool_delete(_t1180, &(Bool){1});
        return _t1117;
    }
    Bool_delete(_t1180, &(Bool){1});
    Bool *_t1181 = TokenType_is_Lt(self);
    if (DEREF(_t1181)) {
        Bool *_t1118 = TokenType_is_Lt(other);
        Bool_delete(_t1181, &(Bool){1});
        return _t1118;
    }
    Bool_delete(_t1181, &(Bool){1});
    Bool *_t1182 = TokenType_is_LtEq(self);
    if (DEREF(_t1182)) {
        Bool *_t1119 = TokenType_is_LtEq(other);
        Bool_delete(_t1182, &(Bool){1});
        return _t1119;
    }
    Bool_delete(_t1182, &(Bool){1});
    Bool *_t1183 = TokenType_is_Gt(self);
    if (DEREF(_t1183)) {
        Bool *_t1120 = TokenType_is_Gt(other);
        Bool_delete(_t1183, &(Bool){1});
        return _t1120;
    }
    Bool_delete(_t1183, &(Bool){1});
    Bool *_t1184 = TokenType_is_GtEq(self);
    if (DEREF(_t1184)) {
        Bool *_t1121 = TokenType_is_GtEq(other);
        Bool_delete(_t1184, &(Bool){1});
        return _t1121;
    }
    Bool_delete(_t1184, &(Bool){1});
    Bool *_t1185 = TokenType_is_ColonEq(self);
    if (DEREF(_t1185)) {
        Bool *_t1122 = TokenType_is_ColonEq(other);
        Bool_delete(_t1185, &(Bool){1});
        return _t1122;
    }
    Bool_delete(_t1185, &(Bool){1});
    Bool *_t1186 = TokenType_is_Ident(self);
    if (DEREF(_t1186)) {
        Bool *_t1123 = TokenType_is_Ident(other);
        Bool_delete(_t1186, &(Bool){1});
        return _t1123;
    }
    Bool_delete(_t1186, &(Bool){1});
    Bool *_t1187 = TokenType_is_StringTok(self);
    if (DEREF(_t1187)) {
        Bool *_t1124 = TokenType_is_StringTok(other);
        Bool_delete(_t1187, &(Bool){1});
        return _t1124;
    }
    Bool_delete(_t1187, &(Bool){1});
    Bool *_t1188 = TokenType_is_Number(self);
    if (DEREF(_t1188)) {
        Bool *_t1125 = TokenType_is_Number(other);
        Bool_delete(_t1188, &(Bool){1});
        return _t1125;
    }
    Bool_delete(_t1188, &(Bool){1});
    Bool *_t1189 = TokenType_is_Char(self);
    if (DEREF(_t1189)) {
        Bool *_t1126 = TokenType_is_Char(other);
        Bool_delete(_t1189, &(Bool){1});
        return _t1126;
    }
    Bool_delete(_t1189, &(Bool){1});
    Bool *_t1190 = TokenType_is_KwMode(self);
    if (DEREF(_t1190)) {
        Bool *_t1127 = TokenType_is_KwMode(other);
        Bool_delete(_t1190, &(Bool){1});
        return _t1127;
    }
    Bool_delete(_t1190, &(Bool){1});
    Bool *_t1191 = TokenType_is_KwMut(self);
    if (DEREF(_t1191)) {
        Bool *_t1128 = TokenType_is_KwMut(other);
        Bool_delete(_t1191, &(Bool){1});
        return _t1128;
    }
    Bool_delete(_t1191, &(Bool){1});
    Bool *_t1192 = TokenType_is_KwOwn(self);
    if (DEREF(_t1192)) {
        Bool *_t1129 = TokenType_is_KwOwn(other);
        Bool_delete(_t1192, &(Bool){1});
        return _t1129;
    }
    Bool_delete(_t1192, &(Bool){1});
    Bool *_t1193 = TokenType_is_KwRef(self);
    if (DEREF(_t1193)) {
        Bool *_t1130 = TokenType_is_KwRef(other);
        Bool_delete(_t1193, &(Bool){1});
        return _t1130;
    }
    Bool_delete(_t1193, &(Bool){1});
    Bool *_t1194 = TokenType_is_KwStruct(self);
    if (DEREF(_t1194)) {
        Bool *_t1131 = TokenType_is_KwStruct(other);
        Bool_delete(_t1194, &(Bool){1});
        return _t1131;
    }
    Bool_delete(_t1194, &(Bool){1});
    Bool *_t1195 = TokenType_is_KwExtStruct(self);
    if (DEREF(_t1195)) {
        Bool *_t1132 = TokenType_is_KwExtStruct(other);
        Bool_delete(_t1195, &(Bool){1});
        return _t1132;
    }
    Bool_delete(_t1195, &(Bool){1});
    Bool *_t1196 = TokenType_is_KwEnum(self);
    if (DEREF(_t1196)) {
        Bool *_t1133 = TokenType_is_KwEnum(other);
        Bool_delete(_t1196, &(Bool){1});
        return _t1133;
    }
    Bool_delete(_t1196, &(Bool){1});
    Bool *_t1197 = TokenType_is_KwNamespace(self);
    if (DEREF(_t1197)) {
        Bool *_t1134 = TokenType_is_KwNamespace(other);
        Bool_delete(_t1197, &(Bool){1});
        return _t1134;
    }
    Bool_delete(_t1197, &(Bool){1});
    Bool *_t1198 = TokenType_is_KwFunc(self);
    if (DEREF(_t1198)) {
        Bool *_t1135 = TokenType_is_KwFunc(other);
        Bool_delete(_t1198, &(Bool){1});
        return _t1135;
    }
    Bool_delete(_t1198, &(Bool){1});
    Bool *_t1199 = TokenType_is_KwProc(self);
    if (DEREF(_t1199)) {
        Bool *_t1136 = TokenType_is_KwProc(other);
        Bool_delete(_t1199, &(Bool){1});
        return _t1136;
    }
    Bool_delete(_t1199, &(Bool){1});
    Bool *_t1200 = TokenType_is_KwTest(self);
    if (DEREF(_t1200)) {
        Bool *_t1137 = TokenType_is_KwTest(other);
        Bool_delete(_t1200, &(Bool){1});
        return _t1137;
    }
    Bool_delete(_t1200, &(Bool){1});
    Bool *_t1201 = TokenType_is_KwMacro(self);
    if (DEREF(_t1201)) {
        Bool *_t1138 = TokenType_is_KwMacro(other);
        Bool_delete(_t1201, &(Bool){1});
        return _t1138;
    }
    Bool_delete(_t1201, &(Bool){1});
    Bool *_t1202 = TokenType_is_KwExtFunc(self);
    if (DEREF(_t1202)) {
        Bool *_t1139 = TokenType_is_KwExtFunc(other);
        Bool_delete(_t1202, &(Bool){1});
        return _t1139;
    }
    Bool_delete(_t1202, &(Bool){1});
    Bool *_t1203 = TokenType_is_KwExtProc(self);
    if (DEREF(_t1203)) {
        Bool *_t1140 = TokenType_is_KwExtProc(other);
        Bool_delete(_t1203, &(Bool){1});
        return _t1140;
    }
    Bool_delete(_t1203, &(Bool){1});
    Bool *_t1204 = TokenType_is_KwReturns(self);
    if (DEREF(_t1204)) {
        Bool *_t1141 = TokenType_is_KwReturns(other);
        Bool_delete(_t1204, &(Bool){1});
        return _t1141;
    }
    Bool_delete(_t1204, &(Bool){1});
    Bool *_t1205 = TokenType_is_KwThrows(self);
    if (DEREF(_t1205)) {
        Bool *_t1142 = TokenType_is_KwThrows(other);
        Bool_delete(_t1205, &(Bool){1});
        return _t1142;
    }
    Bool_delete(_t1205, &(Bool){1});
    Bool *_t1206 = TokenType_is_KwIf(self);
    if (DEREF(_t1206)) {
        Bool *_t1143 = TokenType_is_KwIf(other);
        Bool_delete(_t1206, &(Bool){1});
        return _t1143;
    }
    Bool_delete(_t1206, &(Bool){1});
    Bool *_t1207 = TokenType_is_KwElse(self);
    if (DEREF(_t1207)) {
        Bool *_t1144 = TokenType_is_KwElse(other);
        Bool_delete(_t1207, &(Bool){1});
        return _t1144;
    }
    Bool_delete(_t1207, &(Bool){1});
    Bool *_t1208 = TokenType_is_KwWhile(self);
    if (DEREF(_t1208)) {
        Bool *_t1145 = TokenType_is_KwWhile(other);
        Bool_delete(_t1208, &(Bool){1});
        return _t1145;
    }
    Bool_delete(_t1208, &(Bool){1});
    Bool *_t1209 = TokenType_is_KwFor(self);
    if (DEREF(_t1209)) {
        Bool *_t1146 = TokenType_is_KwFor(other);
        Bool_delete(_t1209, &(Bool){1});
        return _t1146;
    }
    Bool_delete(_t1209, &(Bool){1});
    Bool *_t1210 = TokenType_is_KwIn(self);
    if (DEREF(_t1210)) {
        Bool *_t1147 = TokenType_is_KwIn(other);
        Bool_delete(_t1210, &(Bool){1});
        return _t1147;
    }
    Bool_delete(_t1210, &(Bool){1});
    Bool *_t1211 = TokenType_is_KwSwitch(self);
    if (DEREF(_t1211)) {
        Bool *_t1148 = TokenType_is_KwSwitch(other);
        Bool_delete(_t1211, &(Bool){1});
        return _t1148;
    }
    Bool_delete(_t1211, &(Bool){1});
    Bool *_t1212 = TokenType_is_KwMatch(self);
    if (DEREF(_t1212)) {
        Bool *_t1149 = TokenType_is_KwMatch(other);
        Bool_delete(_t1212, &(Bool){1});
        return _t1149;
    }
    Bool_delete(_t1212, &(Bool){1});
    Bool *_t1213 = TokenType_is_KwCase(self);
    if (DEREF(_t1213)) {
        Bool *_t1150 = TokenType_is_KwCase(other);
        Bool_delete(_t1213, &(Bool){1});
        return _t1150;
    }
    Bool_delete(_t1213, &(Bool){1});
    Bool *_t1214 = TokenType_is_KwDefault(self);
    if (DEREF(_t1214)) {
        Bool *_t1151 = TokenType_is_KwDefault(other);
        Bool_delete(_t1214, &(Bool){1});
        return _t1151;
    }
    Bool_delete(_t1214, &(Bool){1});
    Bool *_t1215 = TokenType_is_KwReturn(self);
    if (DEREF(_t1215)) {
        Bool *_t1152 = TokenType_is_KwReturn(other);
        Bool_delete(_t1215, &(Bool){1});
        return _t1152;
    }
    Bool_delete(_t1215, &(Bool){1});
    Bool *_t1216 = TokenType_is_KwThrow(self);
    if (DEREF(_t1216)) {
        Bool *_t1153 = TokenType_is_KwThrow(other);
        Bool_delete(_t1216, &(Bool){1});
        return _t1153;
    }
    Bool_delete(_t1216, &(Bool){1});
    Bool *_t1217 = TokenType_is_KwCatch(self);
    if (DEREF(_t1217)) {
        Bool *_t1154 = TokenType_is_KwCatch(other);
        Bool_delete(_t1217, &(Bool){1});
        return _t1154;
    }
    Bool_delete(_t1217, &(Bool){1});
    Bool *_t1218 = TokenType_is_KwBreak(self);
    if (DEREF(_t1218)) {
        Bool *_t1155 = TokenType_is_KwBreak(other);
        Bool_delete(_t1218, &(Bool){1});
        return _t1155;
    }
    Bool_delete(_t1218, &(Bool){1});
    Bool *_t1219 = TokenType_is_KwContinue(self);
    if (DEREF(_t1219)) {
        Bool *_t1156 = TokenType_is_KwContinue(other);
        Bool_delete(_t1219, &(Bool){1});
        return _t1156;
    }
    Bool_delete(_t1219, &(Bool){1});
    Bool *_t1220 = TokenType_is_KwDefer(self);
    if (DEREF(_t1220)) {
        Bool *_t1157 = TokenType_is_KwDefer(other);
        Bool_delete(_t1220, &(Bool){1});
        return _t1157;
    }
    Bool_delete(_t1220, &(Bool){1});
    Bool *_t1221 = TokenType_is_KwTrue(self);
    if (DEREF(_t1221)) {
        Bool *_t1158 = TokenType_is_KwTrue(other);
        Bool_delete(_t1221, &(Bool){1});
        return _t1158;
    }
    Bool_delete(_t1221, &(Bool){1});
    Bool *_t1222 = TokenType_is_KwFalse(self);
    if (DEREF(_t1222)) {
        Bool *_t1159 = TokenType_is_KwFalse(other);
        Bool_delete(_t1222, &(Bool){1});
        return _t1159;
    }
    Bool_delete(_t1222, &(Bool){1});
    Bool *_t1223 = TokenType_is_Error(self);
    if (DEREF(_t1223)) {
        Bool *_t1160 = TokenType_is_Error(other);
        Bool_delete(_t1223, &(Bool){1});
        return _t1160;
    }
    Bool_delete(_t1223, &(Bool){1});
    Bool *_t1224 = malloc(sizeof(Bool));
    *_t1224 = 0;
    return _t1224;
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool *_t1225 = TokenType_eq(self, TokenType_Eof());
    if (DEREF(_t1225)) {
        Bool_delete(_t1225, &(Bool){1});
        return TokenType_Eof();
    }
    Bool_delete(_t1225, &(Bool){1});
    Bool *_t1226 = TokenType_eq(self, TokenType_LParen());
    if (DEREF(_t1226)) {
        Bool_delete(_t1226, &(Bool){1});
        return TokenType_LParen();
    }
    Bool_delete(_t1226, &(Bool){1});
    Bool *_t1227 = TokenType_eq(self, TokenType_RParen());
    if (DEREF(_t1227)) {
        Bool_delete(_t1227, &(Bool){1});
        return TokenType_RParen();
    }
    Bool_delete(_t1227, &(Bool){1});
    Bool *_t1228 = TokenType_eq(self, TokenType_LBrace());
    if (DEREF(_t1228)) {
        Bool_delete(_t1228, &(Bool){1});
        return TokenType_LBrace();
    }
    Bool_delete(_t1228, &(Bool){1});
    Bool *_t1229 = TokenType_eq(self, TokenType_RBrace());
    if (DEREF(_t1229)) {
        Bool_delete(_t1229, &(Bool){1});
        return TokenType_RBrace();
    }
    Bool_delete(_t1229, &(Bool){1});
    Bool *_t1230 = TokenType_eq(self, TokenType_LBracket());
    if (DEREF(_t1230)) {
        Bool_delete(_t1230, &(Bool){1});
        return TokenType_LBracket();
    }
    Bool_delete(_t1230, &(Bool){1});
    Bool *_t1231 = TokenType_eq(self, TokenType_RBracket());
    if (DEREF(_t1231)) {
        Bool_delete(_t1231, &(Bool){1});
        return TokenType_RBracket();
    }
    Bool_delete(_t1231, &(Bool){1});
    Bool *_t1232 = TokenType_eq(self, TokenType_Comma());
    if (DEREF(_t1232)) {
        Bool_delete(_t1232, &(Bool){1});
        return TokenType_Comma();
    }
    Bool_delete(_t1232, &(Bool){1});
    Bool *_t1233 = TokenType_eq(self, TokenType_Colon());
    if (DEREF(_t1233)) {
        Bool_delete(_t1233, &(Bool){1});
        return TokenType_Colon();
    }
    Bool_delete(_t1233, &(Bool){1});
    Bool *_t1234 = TokenType_eq(self, TokenType_Question());
    if (DEREF(_t1234)) {
        Bool_delete(_t1234, &(Bool){1});
        return TokenType_Question();
    }
    Bool_delete(_t1234, &(Bool){1});
    Bool *_t1235 = TokenType_eq(self, TokenType_Bang());
    if (DEREF(_t1235)) {
        Bool_delete(_t1235, &(Bool){1});
        return TokenType_Bang();
    }
    Bool_delete(_t1235, &(Bool){1});
    Bool *_t1236 = TokenType_eq(self, TokenType_Minus());
    if (DEREF(_t1236)) {
        Bool_delete(_t1236, &(Bool){1});
        return TokenType_Minus();
    }
    Bool_delete(_t1236, &(Bool){1});
    Bool *_t1237 = TokenType_eq(self, TokenType_Plus());
    if (DEREF(_t1237)) {
        Bool_delete(_t1237, &(Bool){1});
        return TokenType_Plus();
    }
    Bool_delete(_t1237, &(Bool){1});
    Bool *_t1238 = TokenType_eq(self, TokenType_Star());
    if (DEREF(_t1238)) {
        Bool_delete(_t1238, &(Bool){1});
        return TokenType_Star();
    }
    Bool_delete(_t1238, &(Bool){1});
    Bool *_t1239 = TokenType_eq(self, TokenType_Slash());
    if (DEREF(_t1239)) {
        Bool_delete(_t1239, &(Bool){1});
        return TokenType_Slash();
    }
    Bool_delete(_t1239, &(Bool){1});
    Bool *_t1240 = TokenType_eq(self, TokenType_Dot());
    if (DEREF(_t1240)) {
        Bool_delete(_t1240, &(Bool){1});
        return TokenType_Dot();
    }
    Bool_delete(_t1240, &(Bool){1});
    Bool *_t1241 = TokenType_eq(self, TokenType_DotDot());
    if (DEREF(_t1241)) {
        Bool_delete(_t1241, &(Bool){1});
        return TokenType_DotDot();
    }
    Bool_delete(_t1241, &(Bool){1});
    Bool *_t1242 = TokenType_eq(self, TokenType_Eq());
    if (DEREF(_t1242)) {
        Bool_delete(_t1242, &(Bool){1});
        return TokenType_Eq();
    }
    Bool_delete(_t1242, &(Bool){1});
    Bool *_t1243 = TokenType_eq(self, TokenType_EqEq());
    if (DEREF(_t1243)) {
        Bool_delete(_t1243, &(Bool){1});
        return TokenType_EqEq();
    }
    Bool_delete(_t1243, &(Bool){1});
    Bool *_t1244 = TokenType_eq(self, TokenType_Neq());
    if (DEREF(_t1244)) {
        Bool_delete(_t1244, &(Bool){1});
        return TokenType_Neq();
    }
    Bool_delete(_t1244, &(Bool){1});
    Bool *_t1245 = TokenType_eq(self, TokenType_Lt());
    if (DEREF(_t1245)) {
        Bool_delete(_t1245, &(Bool){1});
        return TokenType_Lt();
    }
    Bool_delete(_t1245, &(Bool){1});
    Bool *_t1246 = TokenType_eq(self, TokenType_LtEq());
    if (DEREF(_t1246)) {
        Bool_delete(_t1246, &(Bool){1});
        return TokenType_LtEq();
    }
    Bool_delete(_t1246, &(Bool){1});
    Bool *_t1247 = TokenType_eq(self, TokenType_Gt());
    if (DEREF(_t1247)) {
        Bool_delete(_t1247, &(Bool){1});
        return TokenType_Gt();
    }
    Bool_delete(_t1247, &(Bool){1});
    Bool *_t1248 = TokenType_eq(self, TokenType_GtEq());
    if (DEREF(_t1248)) {
        Bool_delete(_t1248, &(Bool){1});
        return TokenType_GtEq();
    }
    Bool_delete(_t1248, &(Bool){1});
    Bool *_t1249 = TokenType_eq(self, TokenType_ColonEq());
    if (DEREF(_t1249)) {
        Bool_delete(_t1249, &(Bool){1});
        return TokenType_ColonEq();
    }
    Bool_delete(_t1249, &(Bool){1});
    Bool *_t1250 = TokenType_eq(self, TokenType_Ident());
    if (DEREF(_t1250)) {
        Bool_delete(_t1250, &(Bool){1});
        return TokenType_Ident();
    }
    Bool_delete(_t1250, &(Bool){1});
    Bool *_t1251 = TokenType_eq(self, TokenType_StringTok());
    if (DEREF(_t1251)) {
        Bool_delete(_t1251, &(Bool){1});
        return TokenType_StringTok();
    }
    Bool_delete(_t1251, &(Bool){1});
    Bool *_t1252 = TokenType_eq(self, TokenType_Number());
    if (DEREF(_t1252)) {
        Bool_delete(_t1252, &(Bool){1});
        return TokenType_Number();
    }
    Bool_delete(_t1252, &(Bool){1});
    Bool *_t1253 = TokenType_eq(self, TokenType_Char());
    if (DEREF(_t1253)) {
        Bool_delete(_t1253, &(Bool){1});
        return TokenType_Char();
    }
    Bool_delete(_t1253, &(Bool){1});
    Bool *_t1254 = TokenType_eq(self, TokenType_KwMode());
    if (DEREF(_t1254)) {
        Bool_delete(_t1254, &(Bool){1});
        return TokenType_KwMode();
    }
    Bool_delete(_t1254, &(Bool){1});
    Bool *_t1255 = TokenType_eq(self, TokenType_KwMut());
    if (DEREF(_t1255)) {
        Bool_delete(_t1255, &(Bool){1});
        return TokenType_KwMut();
    }
    Bool_delete(_t1255, &(Bool){1});
    Bool *_t1256 = TokenType_eq(self, TokenType_KwOwn());
    if (DEREF(_t1256)) {
        Bool_delete(_t1256, &(Bool){1});
        return TokenType_KwOwn();
    }
    Bool_delete(_t1256, &(Bool){1});
    Bool *_t1257 = TokenType_eq(self, TokenType_KwRef());
    if (DEREF(_t1257)) {
        Bool_delete(_t1257, &(Bool){1});
        return TokenType_KwRef();
    }
    Bool_delete(_t1257, &(Bool){1});
    Bool *_t1258 = TokenType_eq(self, TokenType_KwStruct());
    if (DEREF(_t1258)) {
        Bool_delete(_t1258, &(Bool){1});
        return TokenType_KwStruct();
    }
    Bool_delete(_t1258, &(Bool){1});
    Bool *_t1259 = TokenType_eq(self, TokenType_KwExtStruct());
    if (DEREF(_t1259)) {
        Bool_delete(_t1259, &(Bool){1});
        return TokenType_KwExtStruct();
    }
    Bool_delete(_t1259, &(Bool){1});
    Bool *_t1260 = TokenType_eq(self, TokenType_KwEnum());
    if (DEREF(_t1260)) {
        Bool_delete(_t1260, &(Bool){1});
        return TokenType_KwEnum();
    }
    Bool_delete(_t1260, &(Bool){1});
    Bool *_t1261 = TokenType_eq(self, TokenType_KwNamespace());
    if (DEREF(_t1261)) {
        Bool_delete(_t1261, &(Bool){1});
        return TokenType_KwNamespace();
    }
    Bool_delete(_t1261, &(Bool){1});
    Bool *_t1262 = TokenType_eq(self, TokenType_KwFunc());
    if (DEREF(_t1262)) {
        Bool_delete(_t1262, &(Bool){1});
        return TokenType_KwFunc();
    }
    Bool_delete(_t1262, &(Bool){1});
    Bool *_t1263 = TokenType_eq(self, TokenType_KwProc());
    if (DEREF(_t1263)) {
        Bool_delete(_t1263, &(Bool){1});
        return TokenType_KwProc();
    }
    Bool_delete(_t1263, &(Bool){1});
    Bool *_t1264 = TokenType_eq(self, TokenType_KwTest());
    if (DEREF(_t1264)) {
        Bool_delete(_t1264, &(Bool){1});
        return TokenType_KwTest();
    }
    Bool_delete(_t1264, &(Bool){1});
    Bool *_t1265 = TokenType_eq(self, TokenType_KwMacro());
    if (DEREF(_t1265)) {
        Bool_delete(_t1265, &(Bool){1});
        return TokenType_KwMacro();
    }
    Bool_delete(_t1265, &(Bool){1});
    Bool *_t1266 = TokenType_eq(self, TokenType_KwExtFunc());
    if (DEREF(_t1266)) {
        Bool_delete(_t1266, &(Bool){1});
        return TokenType_KwExtFunc();
    }
    Bool_delete(_t1266, &(Bool){1});
    Bool *_t1267 = TokenType_eq(self, TokenType_KwExtProc());
    if (DEREF(_t1267)) {
        Bool_delete(_t1267, &(Bool){1});
        return TokenType_KwExtProc();
    }
    Bool_delete(_t1267, &(Bool){1});
    Bool *_t1268 = TokenType_eq(self, TokenType_KwReturns());
    if (DEREF(_t1268)) {
        Bool_delete(_t1268, &(Bool){1});
        return TokenType_KwReturns();
    }
    Bool_delete(_t1268, &(Bool){1});
    Bool *_t1269 = TokenType_eq(self, TokenType_KwThrows());
    if (DEREF(_t1269)) {
        Bool_delete(_t1269, &(Bool){1});
        return TokenType_KwThrows();
    }
    Bool_delete(_t1269, &(Bool){1});
    Bool *_t1270 = TokenType_eq(self, TokenType_KwIf());
    if (DEREF(_t1270)) {
        Bool_delete(_t1270, &(Bool){1});
        return TokenType_KwIf();
    }
    Bool_delete(_t1270, &(Bool){1});
    Bool *_t1271 = TokenType_eq(self, TokenType_KwElse());
    if (DEREF(_t1271)) {
        Bool_delete(_t1271, &(Bool){1});
        return TokenType_KwElse();
    }
    Bool_delete(_t1271, &(Bool){1});
    Bool *_t1272 = TokenType_eq(self, TokenType_KwWhile());
    if (DEREF(_t1272)) {
        Bool_delete(_t1272, &(Bool){1});
        return TokenType_KwWhile();
    }
    Bool_delete(_t1272, &(Bool){1});
    Bool *_t1273 = TokenType_eq(self, TokenType_KwFor());
    if (DEREF(_t1273)) {
        Bool_delete(_t1273, &(Bool){1});
        return TokenType_KwFor();
    }
    Bool_delete(_t1273, &(Bool){1});
    Bool *_t1274 = TokenType_eq(self, TokenType_KwIn());
    if (DEREF(_t1274)) {
        Bool_delete(_t1274, &(Bool){1});
        return TokenType_KwIn();
    }
    Bool_delete(_t1274, &(Bool){1});
    Bool *_t1275 = TokenType_eq(self, TokenType_KwSwitch());
    if (DEREF(_t1275)) {
        Bool_delete(_t1275, &(Bool){1});
        return TokenType_KwSwitch();
    }
    Bool_delete(_t1275, &(Bool){1});
    Bool *_t1276 = TokenType_eq(self, TokenType_KwMatch());
    if (DEREF(_t1276)) {
        Bool_delete(_t1276, &(Bool){1});
        return TokenType_KwMatch();
    }
    Bool_delete(_t1276, &(Bool){1});
    Bool *_t1277 = TokenType_eq(self, TokenType_KwCase());
    if (DEREF(_t1277)) {
        Bool_delete(_t1277, &(Bool){1});
        return TokenType_KwCase();
    }
    Bool_delete(_t1277, &(Bool){1});
    Bool *_t1278 = TokenType_eq(self, TokenType_KwDefault());
    if (DEREF(_t1278)) {
        Bool_delete(_t1278, &(Bool){1});
        return TokenType_KwDefault();
    }
    Bool_delete(_t1278, &(Bool){1});
    Bool *_t1279 = TokenType_eq(self, TokenType_KwReturn());
    if (DEREF(_t1279)) {
        Bool_delete(_t1279, &(Bool){1});
        return TokenType_KwReturn();
    }
    Bool_delete(_t1279, &(Bool){1});
    Bool *_t1280 = TokenType_eq(self, TokenType_KwThrow());
    if (DEREF(_t1280)) {
        Bool_delete(_t1280, &(Bool){1});
        return TokenType_KwThrow();
    }
    Bool_delete(_t1280, &(Bool){1});
    Bool *_t1281 = TokenType_eq(self, TokenType_KwCatch());
    if (DEREF(_t1281)) {
        Bool_delete(_t1281, &(Bool){1});
        return TokenType_KwCatch();
    }
    Bool_delete(_t1281, &(Bool){1});
    Bool *_t1282 = TokenType_eq(self, TokenType_KwBreak());
    if (DEREF(_t1282)) {
        Bool_delete(_t1282, &(Bool){1});
        return TokenType_KwBreak();
    }
    Bool_delete(_t1282, &(Bool){1});
    Bool *_t1283 = TokenType_eq(self, TokenType_KwContinue());
    if (DEREF(_t1283)) {
        Bool_delete(_t1283, &(Bool){1});
        return TokenType_KwContinue();
    }
    Bool_delete(_t1283, &(Bool){1});
    Bool *_t1284 = TokenType_eq(self, TokenType_KwDefer());
    if (DEREF(_t1284)) {
        Bool_delete(_t1284, &(Bool){1});
        return TokenType_KwDefer();
    }
    Bool_delete(_t1284, &(Bool){1});
    Bool *_t1285 = TokenType_eq(self, TokenType_KwTrue());
    if (DEREF(_t1285)) {
        Bool_delete(_t1285, &(Bool){1});
        return TokenType_KwTrue();
    }
    Bool_delete(_t1285, &(Bool){1});
    Bool *_t1286 = TokenType_eq(self, TokenType_KwFalse());
    if (DEREF(_t1286)) {
        Bool_delete(_t1286, &(Bool){1});
        return TokenType_KwFalse();
    }
    Bool_delete(_t1286, &(Bool){1});
    return TokenType_Error();
}

void TokenType_delete(TokenType * self, Bool * call_free) {
    (void)self;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * TokenType_to_str(TokenType * self) {
    (void)self;
    Bool *_t1350 = TokenType_eq(self, TokenType_Eof());
    if (DEREF(_t1350)) {
        Str *_t1287 = Str_lit("Eof", 3ULL);
        Bool_delete(_t1350, &(Bool){1});
        return _t1287;
    }
    Bool_delete(_t1350, &(Bool){1});
    Bool *_t1351 = TokenType_eq(self, TokenType_LParen());
    if (DEREF(_t1351)) {
        Str *_t1288 = Str_lit("LParen", 6ULL);
        Bool_delete(_t1351, &(Bool){1});
        return _t1288;
    }
    Bool_delete(_t1351, &(Bool){1});
    Bool *_t1352 = TokenType_eq(self, TokenType_RParen());
    if (DEREF(_t1352)) {
        Str *_t1289 = Str_lit("RParen", 6ULL);
        Bool_delete(_t1352, &(Bool){1});
        return _t1289;
    }
    Bool_delete(_t1352, &(Bool){1});
    Bool *_t1353 = TokenType_eq(self, TokenType_LBrace());
    if (DEREF(_t1353)) {
        Str *_t1290 = Str_lit("LBrace", 6ULL);
        Bool_delete(_t1353, &(Bool){1});
        return _t1290;
    }
    Bool_delete(_t1353, &(Bool){1});
    Bool *_t1354 = TokenType_eq(self, TokenType_RBrace());
    if (DEREF(_t1354)) {
        Str *_t1291 = Str_lit("RBrace", 6ULL);
        Bool_delete(_t1354, &(Bool){1});
        return _t1291;
    }
    Bool_delete(_t1354, &(Bool){1});
    Bool *_t1355 = TokenType_eq(self, TokenType_LBracket());
    if (DEREF(_t1355)) {
        Str *_t1292 = Str_lit("LBracket", 8ULL);
        Bool_delete(_t1355, &(Bool){1});
        return _t1292;
    }
    Bool_delete(_t1355, &(Bool){1});
    Bool *_t1356 = TokenType_eq(self, TokenType_RBracket());
    if (DEREF(_t1356)) {
        Str *_t1293 = Str_lit("RBracket", 8ULL);
        Bool_delete(_t1356, &(Bool){1});
        return _t1293;
    }
    Bool_delete(_t1356, &(Bool){1});
    Bool *_t1357 = TokenType_eq(self, TokenType_Comma());
    if (DEREF(_t1357)) {
        Str *_t1294 = Str_lit("Comma", 5ULL);
        Bool_delete(_t1357, &(Bool){1});
        return _t1294;
    }
    Bool_delete(_t1357, &(Bool){1});
    Bool *_t1358 = TokenType_eq(self, TokenType_Colon());
    if (DEREF(_t1358)) {
        Str *_t1295 = Str_lit("Colon", 5ULL);
        Bool_delete(_t1358, &(Bool){1});
        return _t1295;
    }
    Bool_delete(_t1358, &(Bool){1});
    Bool *_t1359 = TokenType_eq(self, TokenType_Question());
    if (DEREF(_t1359)) {
        Str *_t1296 = Str_lit("Question", 8ULL);
        Bool_delete(_t1359, &(Bool){1});
        return _t1296;
    }
    Bool_delete(_t1359, &(Bool){1});
    Bool *_t1360 = TokenType_eq(self, TokenType_Bang());
    if (DEREF(_t1360)) {
        Str *_t1297 = Str_lit("Bang", 4ULL);
        Bool_delete(_t1360, &(Bool){1});
        return _t1297;
    }
    Bool_delete(_t1360, &(Bool){1});
    Bool *_t1361 = TokenType_eq(self, TokenType_Minus());
    if (DEREF(_t1361)) {
        Str *_t1298 = Str_lit("Minus", 5ULL);
        Bool_delete(_t1361, &(Bool){1});
        return _t1298;
    }
    Bool_delete(_t1361, &(Bool){1});
    Bool *_t1362 = TokenType_eq(self, TokenType_Plus());
    if (DEREF(_t1362)) {
        Str *_t1299 = Str_lit("Plus", 4ULL);
        Bool_delete(_t1362, &(Bool){1});
        return _t1299;
    }
    Bool_delete(_t1362, &(Bool){1});
    Bool *_t1363 = TokenType_eq(self, TokenType_Star());
    if (DEREF(_t1363)) {
        Str *_t1300 = Str_lit("Star", 4ULL);
        Bool_delete(_t1363, &(Bool){1});
        return _t1300;
    }
    Bool_delete(_t1363, &(Bool){1});
    Bool *_t1364 = TokenType_eq(self, TokenType_Slash());
    if (DEREF(_t1364)) {
        Str *_t1301 = Str_lit("Slash", 5ULL);
        Bool_delete(_t1364, &(Bool){1});
        return _t1301;
    }
    Bool_delete(_t1364, &(Bool){1});
    Bool *_t1365 = TokenType_eq(self, TokenType_Dot());
    if (DEREF(_t1365)) {
        Str *_t1302 = Str_lit("Dot", 3ULL);
        Bool_delete(_t1365, &(Bool){1});
        return _t1302;
    }
    Bool_delete(_t1365, &(Bool){1});
    Bool *_t1366 = TokenType_eq(self, TokenType_DotDot());
    if (DEREF(_t1366)) {
        Str *_t1303 = Str_lit("DotDot", 6ULL);
        Bool_delete(_t1366, &(Bool){1});
        return _t1303;
    }
    Bool_delete(_t1366, &(Bool){1});
    Bool *_t1367 = TokenType_eq(self, TokenType_Eq());
    if (DEREF(_t1367)) {
        Str *_t1304 = Str_lit("Eq", 2ULL);
        Bool_delete(_t1367, &(Bool){1});
        return _t1304;
    }
    Bool_delete(_t1367, &(Bool){1});
    Bool *_t1368 = TokenType_eq(self, TokenType_EqEq());
    if (DEREF(_t1368)) {
        Str *_t1305 = Str_lit("EqEq", 4ULL);
        Bool_delete(_t1368, &(Bool){1});
        return _t1305;
    }
    Bool_delete(_t1368, &(Bool){1});
    Bool *_t1369 = TokenType_eq(self, TokenType_Neq());
    if (DEREF(_t1369)) {
        Str *_t1306 = Str_lit("Neq", 3ULL);
        Bool_delete(_t1369, &(Bool){1});
        return _t1306;
    }
    Bool_delete(_t1369, &(Bool){1});
    Bool *_t1370 = TokenType_eq(self, TokenType_Lt());
    if (DEREF(_t1370)) {
        Str *_t1307 = Str_lit("Lt", 2ULL);
        Bool_delete(_t1370, &(Bool){1});
        return _t1307;
    }
    Bool_delete(_t1370, &(Bool){1});
    Bool *_t1371 = TokenType_eq(self, TokenType_LtEq());
    if (DEREF(_t1371)) {
        Str *_t1308 = Str_lit("LtEq", 4ULL);
        Bool_delete(_t1371, &(Bool){1});
        return _t1308;
    }
    Bool_delete(_t1371, &(Bool){1});
    Bool *_t1372 = TokenType_eq(self, TokenType_Gt());
    if (DEREF(_t1372)) {
        Str *_t1309 = Str_lit("Gt", 2ULL);
        Bool_delete(_t1372, &(Bool){1});
        return _t1309;
    }
    Bool_delete(_t1372, &(Bool){1});
    Bool *_t1373 = TokenType_eq(self, TokenType_GtEq());
    if (DEREF(_t1373)) {
        Str *_t1310 = Str_lit("GtEq", 4ULL);
        Bool_delete(_t1373, &(Bool){1});
        return _t1310;
    }
    Bool_delete(_t1373, &(Bool){1});
    Bool *_t1374 = TokenType_eq(self, TokenType_ColonEq());
    if (DEREF(_t1374)) {
        Str *_t1311 = Str_lit("ColonEq", 7ULL);
        Bool_delete(_t1374, &(Bool){1});
        return _t1311;
    }
    Bool_delete(_t1374, &(Bool){1});
    Bool *_t1375 = TokenType_eq(self, TokenType_Ident());
    if (DEREF(_t1375)) {
        Str *_t1312 = Str_lit("Ident", 5ULL);
        Bool_delete(_t1375, &(Bool){1});
        return _t1312;
    }
    Bool_delete(_t1375, &(Bool){1});
    Bool *_t1376 = TokenType_eq(self, TokenType_StringTok());
    if (DEREF(_t1376)) {
        Str *_t1313 = Str_lit("StringTok", 9ULL);
        Bool_delete(_t1376, &(Bool){1});
        return _t1313;
    }
    Bool_delete(_t1376, &(Bool){1});
    Bool *_t1377 = TokenType_eq(self, TokenType_Number());
    if (DEREF(_t1377)) {
        Str *_t1314 = Str_lit("Number", 6ULL);
        Bool_delete(_t1377, &(Bool){1});
        return _t1314;
    }
    Bool_delete(_t1377, &(Bool){1});
    Bool *_t1378 = TokenType_eq(self, TokenType_Char());
    if (DEREF(_t1378)) {
        Str *_t1315 = Str_lit("Char", 4ULL);
        Bool_delete(_t1378, &(Bool){1});
        return _t1315;
    }
    Bool_delete(_t1378, &(Bool){1});
    Bool *_t1379 = TokenType_eq(self, TokenType_KwMode());
    if (DEREF(_t1379)) {
        Str *_t1316 = Str_lit("KwMode", 6ULL);
        Bool_delete(_t1379, &(Bool){1});
        return _t1316;
    }
    Bool_delete(_t1379, &(Bool){1});
    Bool *_t1380 = TokenType_eq(self, TokenType_KwMut());
    if (DEREF(_t1380)) {
        Str *_t1317 = Str_lit("KwMut", 5ULL);
        Bool_delete(_t1380, &(Bool){1});
        return _t1317;
    }
    Bool_delete(_t1380, &(Bool){1});
    Bool *_t1381 = TokenType_eq(self, TokenType_KwOwn());
    if (DEREF(_t1381)) {
        Str *_t1318 = Str_lit("KwOwn", 5ULL);
        Bool_delete(_t1381, &(Bool){1});
        return _t1318;
    }
    Bool_delete(_t1381, &(Bool){1});
    Bool *_t1382 = TokenType_eq(self, TokenType_KwRef());
    if (DEREF(_t1382)) {
        Str *_t1319 = Str_lit("KwRef", 5ULL);
        Bool_delete(_t1382, &(Bool){1});
        return _t1319;
    }
    Bool_delete(_t1382, &(Bool){1});
    Bool *_t1383 = TokenType_eq(self, TokenType_KwStruct());
    if (DEREF(_t1383)) {
        Str *_t1320 = Str_lit("KwStruct", 8ULL);
        Bool_delete(_t1383, &(Bool){1});
        return _t1320;
    }
    Bool_delete(_t1383, &(Bool){1});
    Bool *_t1384 = TokenType_eq(self, TokenType_KwExtStruct());
    if (DEREF(_t1384)) {
        Str *_t1321 = Str_lit("KwExtStruct", 11ULL);
        Bool_delete(_t1384, &(Bool){1});
        return _t1321;
    }
    Bool_delete(_t1384, &(Bool){1});
    Bool *_t1385 = TokenType_eq(self, TokenType_KwEnum());
    if (DEREF(_t1385)) {
        Str *_t1322 = Str_lit("KwEnum", 6ULL);
        Bool_delete(_t1385, &(Bool){1});
        return _t1322;
    }
    Bool_delete(_t1385, &(Bool){1});
    Bool *_t1386 = TokenType_eq(self, TokenType_KwNamespace());
    if (DEREF(_t1386)) {
        Str *_t1323 = Str_lit("KwNamespace", 11ULL);
        Bool_delete(_t1386, &(Bool){1});
        return _t1323;
    }
    Bool_delete(_t1386, &(Bool){1});
    Bool *_t1387 = TokenType_eq(self, TokenType_KwFunc());
    if (DEREF(_t1387)) {
        Str *_t1324 = Str_lit("KwFunc", 6ULL);
        Bool_delete(_t1387, &(Bool){1});
        return _t1324;
    }
    Bool_delete(_t1387, &(Bool){1});
    Bool *_t1388 = TokenType_eq(self, TokenType_KwProc());
    if (DEREF(_t1388)) {
        Str *_t1325 = Str_lit("KwProc", 6ULL);
        Bool_delete(_t1388, &(Bool){1});
        return _t1325;
    }
    Bool_delete(_t1388, &(Bool){1});
    Bool *_t1389 = TokenType_eq(self, TokenType_KwTest());
    if (DEREF(_t1389)) {
        Str *_t1326 = Str_lit("KwTest", 6ULL);
        Bool_delete(_t1389, &(Bool){1});
        return _t1326;
    }
    Bool_delete(_t1389, &(Bool){1});
    Bool *_t1390 = TokenType_eq(self, TokenType_KwMacro());
    if (DEREF(_t1390)) {
        Str *_t1327 = Str_lit("KwMacro", 7ULL);
        Bool_delete(_t1390, &(Bool){1});
        return _t1327;
    }
    Bool_delete(_t1390, &(Bool){1});
    Bool *_t1391 = TokenType_eq(self, TokenType_KwExtFunc());
    if (DEREF(_t1391)) {
        Str *_t1328 = Str_lit("KwExtFunc", 9ULL);
        Bool_delete(_t1391, &(Bool){1});
        return _t1328;
    }
    Bool_delete(_t1391, &(Bool){1});
    Bool *_t1392 = TokenType_eq(self, TokenType_KwExtProc());
    if (DEREF(_t1392)) {
        Str *_t1329 = Str_lit("KwExtProc", 9ULL);
        Bool_delete(_t1392, &(Bool){1});
        return _t1329;
    }
    Bool_delete(_t1392, &(Bool){1});
    Bool *_t1393 = TokenType_eq(self, TokenType_KwReturns());
    if (DEREF(_t1393)) {
        Str *_t1330 = Str_lit("KwReturns", 9ULL);
        Bool_delete(_t1393, &(Bool){1});
        return _t1330;
    }
    Bool_delete(_t1393, &(Bool){1});
    Bool *_t1394 = TokenType_eq(self, TokenType_KwThrows());
    if (DEREF(_t1394)) {
        Str *_t1331 = Str_lit("KwThrows", 8ULL);
        Bool_delete(_t1394, &(Bool){1});
        return _t1331;
    }
    Bool_delete(_t1394, &(Bool){1});
    Bool *_t1395 = TokenType_eq(self, TokenType_KwIf());
    if (DEREF(_t1395)) {
        Str *_t1332 = Str_lit("KwIf", 4ULL);
        Bool_delete(_t1395, &(Bool){1});
        return _t1332;
    }
    Bool_delete(_t1395, &(Bool){1});
    Bool *_t1396 = TokenType_eq(self, TokenType_KwElse());
    if (DEREF(_t1396)) {
        Str *_t1333 = Str_lit("KwElse", 6ULL);
        Bool_delete(_t1396, &(Bool){1});
        return _t1333;
    }
    Bool_delete(_t1396, &(Bool){1});
    Bool *_t1397 = TokenType_eq(self, TokenType_KwWhile());
    if (DEREF(_t1397)) {
        Str *_t1334 = Str_lit("KwWhile", 7ULL);
        Bool_delete(_t1397, &(Bool){1});
        return _t1334;
    }
    Bool_delete(_t1397, &(Bool){1});
    Bool *_t1398 = TokenType_eq(self, TokenType_KwFor());
    if (DEREF(_t1398)) {
        Str *_t1335 = Str_lit("KwFor", 5ULL);
        Bool_delete(_t1398, &(Bool){1});
        return _t1335;
    }
    Bool_delete(_t1398, &(Bool){1});
    Bool *_t1399 = TokenType_eq(self, TokenType_KwIn());
    if (DEREF(_t1399)) {
        Str *_t1336 = Str_lit("KwIn", 4ULL);
        Bool_delete(_t1399, &(Bool){1});
        return _t1336;
    }
    Bool_delete(_t1399, &(Bool){1});
    Bool *_t1400 = TokenType_eq(self, TokenType_KwSwitch());
    if (DEREF(_t1400)) {
        Str *_t1337 = Str_lit("KwSwitch", 8ULL);
        Bool_delete(_t1400, &(Bool){1});
        return _t1337;
    }
    Bool_delete(_t1400, &(Bool){1});
    Bool *_t1401 = TokenType_eq(self, TokenType_KwMatch());
    if (DEREF(_t1401)) {
        Str *_t1338 = Str_lit("KwMatch", 7ULL);
        Bool_delete(_t1401, &(Bool){1});
        return _t1338;
    }
    Bool_delete(_t1401, &(Bool){1});
    Bool *_t1402 = TokenType_eq(self, TokenType_KwCase());
    if (DEREF(_t1402)) {
        Str *_t1339 = Str_lit("KwCase", 6ULL);
        Bool_delete(_t1402, &(Bool){1});
        return _t1339;
    }
    Bool_delete(_t1402, &(Bool){1});
    Bool *_t1403 = TokenType_eq(self, TokenType_KwDefault());
    if (DEREF(_t1403)) {
        Str *_t1340 = Str_lit("KwDefault", 9ULL);
        Bool_delete(_t1403, &(Bool){1});
        return _t1340;
    }
    Bool_delete(_t1403, &(Bool){1});
    Bool *_t1404 = TokenType_eq(self, TokenType_KwReturn());
    if (DEREF(_t1404)) {
        Str *_t1341 = Str_lit("KwReturn", 8ULL);
        Bool_delete(_t1404, &(Bool){1});
        return _t1341;
    }
    Bool_delete(_t1404, &(Bool){1});
    Bool *_t1405 = TokenType_eq(self, TokenType_KwThrow());
    if (DEREF(_t1405)) {
        Str *_t1342 = Str_lit("KwThrow", 7ULL);
        Bool_delete(_t1405, &(Bool){1});
        return _t1342;
    }
    Bool_delete(_t1405, &(Bool){1});
    Bool *_t1406 = TokenType_eq(self, TokenType_KwCatch());
    if (DEREF(_t1406)) {
        Str *_t1343 = Str_lit("KwCatch", 7ULL);
        Bool_delete(_t1406, &(Bool){1});
        return _t1343;
    }
    Bool_delete(_t1406, &(Bool){1});
    Bool *_t1407 = TokenType_eq(self, TokenType_KwBreak());
    if (DEREF(_t1407)) {
        Str *_t1344 = Str_lit("KwBreak", 7ULL);
        Bool_delete(_t1407, &(Bool){1});
        return _t1344;
    }
    Bool_delete(_t1407, &(Bool){1});
    Bool *_t1408 = TokenType_eq(self, TokenType_KwContinue());
    if (DEREF(_t1408)) {
        Str *_t1345 = Str_lit("KwContinue", 10ULL);
        Bool_delete(_t1408, &(Bool){1});
        return _t1345;
    }
    Bool_delete(_t1408, &(Bool){1});
    Bool *_t1409 = TokenType_eq(self, TokenType_KwDefer());
    if (DEREF(_t1409)) {
        Str *_t1346 = Str_lit("KwDefer", 7ULL);
        Bool_delete(_t1409, &(Bool){1});
        return _t1346;
    }
    Bool_delete(_t1409, &(Bool){1});
    Bool *_t1410 = TokenType_eq(self, TokenType_KwTrue());
    if (DEREF(_t1410)) {
        Str *_t1347 = Str_lit("KwTrue", 6ULL);
        Bool_delete(_t1410, &(Bool){1});
        return _t1347;
    }
    Bool_delete(_t1410, &(Bool){1});
    Bool *_t1411 = TokenType_eq(self, TokenType_KwFalse());
    if (DEREF(_t1411)) {
        Str *_t1348 = Str_lit("KwFalse", 7ULL);
        Bool_delete(_t1411, &(Bool){1});
        return _t1348;
    }
    Bool_delete(_t1411, &(Bool){1});
    Bool *_t1412 = TokenType_eq(self, TokenType_Error());
    if (DEREF(_t1412)) {
        Str *_t1349 = Str_lit("Error", 5ULL);
        Bool_delete(_t1412, &(Bool){1});
        return _t1349;
    }
    Bool_delete(_t1412, &(Bool){1});
    Str *_t1413 = Str_lit("unknown", 7ULL);
    return _t1413;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 *_t1415 = I64_clone(&self->line);
    I64 *_t1416 = I64_clone(&self->col);
    Token *_t1417 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1417->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1417->text = *_ca; free(_ca); }
    _t1417->line = DEREF(_t1415);
    _t1417->col = DEREF(_t1416);
    I64_delete(_t1415, &(Bool){1});
    I64_delete(_t1416, &(Bool){1});
    return _t1417;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    Bool *_t1418 = malloc(sizeof(Bool));
    *_t1418 = 0;
    TokenType_delete(&self->type, _t1418);
    Bool_delete(_t1418, &(Bool){1});
    Bool *_t1419 = malloc(sizeof(Bool));
    *_t1419 = 0;
    Str_delete(&self->text, _t1419);
    Bool_delete(_t1419, &(Bool){1});
    Bool *_t1420 = malloc(sizeof(Bool));
    *_t1420 = 0;
    I64_delete(&self->line, _t1420);
    Bool_delete(_t1420, &(Bool){1});
    Bool *_t1421 = malloc(sizeof(Bool));
    *_t1421 = 0;
    I64_delete(&self->col, _t1421);
    Bool_delete(_t1421, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Token_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Token);
    return r;
}

Bool * is_digit(U8 * c) {
    U8 *_t1423 = malloc(sizeof(U8));
    *_t1423 = 48;
    U8 *_t1424 = malloc(sizeof(U8));
    *_t1424 = 57;
    Bool *_t1425 = U8_gte(c, _t1423);
    U8_delete(_t1423, &(Bool){1});
    Bool *_t1426 = U8_lte(c, _t1424);
    U8_delete(_t1424, &(Bool){1});
    Bool *_t1427 = malloc(sizeof(Bool)); *_t1427 = Bool_and(DEREF(_t1425), DEREF(_t1426));
    Bool_delete(_t1425, &(Bool){1});
    Bool_delete(_t1426, &(Bool){1});
    return _t1427;
}

Bool * is_alpha(U8 * c) {
    U8 *_t1428 = malloc(sizeof(U8));
    *_t1428 = 97;
    U8 *_t1429 = malloc(sizeof(U8));
    *_t1429 = 122;
    Bool *_t1430 = U8_gte(c, _t1428);
    U8_delete(_t1428, &(Bool){1});
    Bool *_t1431 = U8_lte(c, _t1429);
    U8_delete(_t1429, &(Bool){1});
    U8 *_t1432 = malloc(sizeof(U8));
    *_t1432 = 65;
    U8 *_t1433 = malloc(sizeof(U8));
    *_t1433 = 90;
    Bool *_t1434 = U8_gte(c, _t1432);
    U8_delete(_t1432, &(Bool){1});
    Bool *_t1435 = U8_lte(c, _t1433);
    U8_delete(_t1433, &(Bool){1});
    Bool *_t1436 = malloc(sizeof(Bool)); *_t1436 = Bool_and(DEREF(_t1430), DEREF(_t1431));
    Bool_delete(_t1430, &(Bool){1});
    Bool_delete(_t1431, &(Bool){1});
    Bool *_t1437 = malloc(sizeof(Bool)); *_t1437 = Bool_and(DEREF(_t1434), DEREF(_t1435));
    Bool_delete(_t1434, &(Bool){1});
    Bool_delete(_t1435, &(Bool){1});
    U8 *_t1438 = malloc(sizeof(U8));
    *_t1438 = 95;
    Bool *_t1439 = malloc(sizeof(Bool)); *_t1439 = Bool_or(DEREF(_t1436), DEREF(_t1437));
    Bool_delete(_t1436, &(Bool){1});
    Bool_delete(_t1437, &(Bool){1});
    Bool *_t1440 = malloc(sizeof(Bool)); *_t1440 = U8_eq(DEREF(c), DEREF(_t1438));
    U8_delete(_t1438, &(Bool){1});
    Bool *_t1441 = malloc(sizeof(Bool)); *_t1441 = Bool_or(DEREF(_t1439), DEREF(_t1440));
    Bool_delete(_t1439, &(Bool){1});
    Bool_delete(_t1440, &(Bool){1});
    return _t1441;
}

Bool * is_alnum(U8 * c) {
    Bool *_t1442 = is_alpha(c);
    Bool *_t1443 = is_digit(c);
    Bool *_t1444 = malloc(sizeof(Bool)); *_t1444 = Bool_or(DEREF(_t1442), DEREF(_t1443));
    Bool_delete(_t1442, &(Bool){1});
    Bool_delete(_t1443, &(Bool){1});
    return _t1444;
}

Str * tok_name(TokenType * type) {
    {
        TokenType *_sw1445 = TokenType_clone(type);
        Bool *_t1572 = TokenType_eq(_sw1445, TokenType_Eof());
        if (DEREF(_t1572)) {
            Str *_t1446 = Str_lit("eof", 3ULL);
            TokenType_delete(_sw1445, &(Bool){1});
            Bool_delete(_t1572, &(Bool){1});
            return _t1446;
        } else {
            Bool *_t1571 = TokenType_eq(_sw1445, TokenType_LParen());
            if (DEREF(_t1571)) {
                Str *_t1447 = Str_lit("(", 1ULL);
                Bool_delete(_t1571, &(Bool){1});
                TokenType_delete(_sw1445, &(Bool){1});
                Bool_delete(_t1572, &(Bool){1});
                return _t1447;
            } else {
                Bool *_t1570 = TokenType_eq(_sw1445, TokenType_RParen());
                if (DEREF(_t1570)) {
                    Str *_t1448 = Str_lit(")", 1ULL);
                    Bool_delete(_t1570, &(Bool){1});
                    Bool_delete(_t1571, &(Bool){1});
                    TokenType_delete(_sw1445, &(Bool){1});
                    Bool_delete(_t1572, &(Bool){1});
                    return _t1448;
                } else {
                    Bool *_t1569 = TokenType_eq(_sw1445, TokenType_LBrace());
                    if (DEREF(_t1569)) {
                        Str *_t1449 = Str_lit("{", 1ULL);
                        Bool_delete(_t1569, &(Bool){1});
                        Bool_delete(_t1570, &(Bool){1});
                        Bool_delete(_t1571, &(Bool){1});
                        TokenType_delete(_sw1445, &(Bool){1});
                        Bool_delete(_t1572, &(Bool){1});
                        return _t1449;
                    } else {
                        Bool *_t1568 = TokenType_eq(_sw1445, TokenType_RBrace());
                        if (DEREF(_t1568)) {
                            Str *_t1450 = Str_lit("}", 1ULL);
                            Bool_delete(_t1568, &(Bool){1});
                            Bool_delete(_t1569, &(Bool){1});
                            Bool_delete(_t1570, &(Bool){1});
                            Bool_delete(_t1571, &(Bool){1});
                            TokenType_delete(_sw1445, &(Bool){1});
                            Bool_delete(_t1572, &(Bool){1});
                            return _t1450;
                        } else {
                            Bool *_t1567 = TokenType_eq(_sw1445, TokenType_LBracket());
                            if (DEREF(_t1567)) {
                                Str *_t1451 = Str_lit("[", 1ULL);
                                Bool_delete(_t1567, &(Bool){1});
                                Bool_delete(_t1568, &(Bool){1});
                                Bool_delete(_t1569, &(Bool){1});
                                Bool_delete(_t1570, &(Bool){1});
                                Bool_delete(_t1571, &(Bool){1});
                                TokenType_delete(_sw1445, &(Bool){1});
                                Bool_delete(_t1572, &(Bool){1});
                                return _t1451;
                            } else {
                                Bool *_t1566 = TokenType_eq(_sw1445, TokenType_RBracket());
                                if (DEREF(_t1566)) {
                                    Str *_t1452 = Str_lit("]", 1ULL);
                                    Bool_delete(_t1566, &(Bool){1});
                                    Bool_delete(_t1567, &(Bool){1});
                                    Bool_delete(_t1568, &(Bool){1});
                                    Bool_delete(_t1569, &(Bool){1});
                                    Bool_delete(_t1570, &(Bool){1});
                                    Bool_delete(_t1571, &(Bool){1});
                                    TokenType_delete(_sw1445, &(Bool){1});
                                    Bool_delete(_t1572, &(Bool){1});
                                    return _t1452;
                                } else {
                                    Bool *_t1565 = TokenType_eq(_sw1445, TokenType_Comma());
                                    if (DEREF(_t1565)) {
                                        Str *_t1453 = Str_lit(",", 1ULL);
                                        Bool_delete(_t1565, &(Bool){1});
                                        Bool_delete(_t1566, &(Bool){1});
                                        Bool_delete(_t1567, &(Bool){1});
                                        Bool_delete(_t1568, &(Bool){1});
                                        Bool_delete(_t1569, &(Bool){1});
                                        Bool_delete(_t1570, &(Bool){1});
                                        Bool_delete(_t1571, &(Bool){1});
                                        TokenType_delete(_sw1445, &(Bool){1});
                                        Bool_delete(_t1572, &(Bool){1});
                                        return _t1453;
                                    } else {
                                        Bool *_t1564 = TokenType_eq(_sw1445, TokenType_Colon());
                                        if (DEREF(_t1564)) {
                                            Str *_t1454 = Str_lit(":", 1ULL);
                                            Bool_delete(_t1564, &(Bool){1});
                                            Bool_delete(_t1565, &(Bool){1});
                                            Bool_delete(_t1566, &(Bool){1});
                                            Bool_delete(_t1567, &(Bool){1});
                                            Bool_delete(_t1568, &(Bool){1});
                                            Bool_delete(_t1569, &(Bool){1});
                                            Bool_delete(_t1570, &(Bool){1});
                                            Bool_delete(_t1571, &(Bool){1});
                                            TokenType_delete(_sw1445, &(Bool){1});
                                            Bool_delete(_t1572, &(Bool){1});
                                            return _t1454;
                                        } else {
                                            Bool *_t1563 = TokenType_eq(_sw1445, TokenType_Question());
                                            if (DEREF(_t1563)) {
                                                Str *_t1455 = Str_lit("?", 1ULL);
                                                Bool_delete(_t1563, &(Bool){1});
                                                Bool_delete(_t1564, &(Bool){1});
                                                Bool_delete(_t1565, &(Bool){1});
                                                Bool_delete(_t1566, &(Bool){1});
                                                Bool_delete(_t1567, &(Bool){1});
                                                Bool_delete(_t1568, &(Bool){1});
                                                Bool_delete(_t1569, &(Bool){1});
                                                Bool_delete(_t1570, &(Bool){1});
                                                Bool_delete(_t1571, &(Bool){1});
                                                TokenType_delete(_sw1445, &(Bool){1});
                                                Bool_delete(_t1572, &(Bool){1});
                                                return _t1455;
                                            } else {
                                                Bool *_t1562 = TokenType_eq(_sw1445, TokenType_Bang());
                                                if (DEREF(_t1562)) {
                                                    Str *_t1456 = Str_lit("!", 1ULL);
                                                    Bool_delete(_t1562, &(Bool){1});
                                                    Bool_delete(_t1563, &(Bool){1});
                                                    Bool_delete(_t1564, &(Bool){1});
                                                    Bool_delete(_t1565, &(Bool){1});
                                                    Bool_delete(_t1566, &(Bool){1});
                                                    Bool_delete(_t1567, &(Bool){1});
                                                    Bool_delete(_t1568, &(Bool){1});
                                                    Bool_delete(_t1569, &(Bool){1});
                                                    Bool_delete(_t1570, &(Bool){1});
                                                    Bool_delete(_t1571, &(Bool){1});
                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                    Bool_delete(_t1572, &(Bool){1});
                                                    return _t1456;
                                                } else {
                                                    Bool *_t1561 = TokenType_eq(_sw1445, TokenType_Minus());
                                                    if (DEREF(_t1561)) {
                                                        Str *_t1457 = Str_lit("-", 1ULL);
                                                        Bool_delete(_t1561, &(Bool){1});
                                                        Bool_delete(_t1562, &(Bool){1});
                                                        Bool_delete(_t1563, &(Bool){1});
                                                        Bool_delete(_t1564, &(Bool){1});
                                                        Bool_delete(_t1565, &(Bool){1});
                                                        Bool_delete(_t1566, &(Bool){1});
                                                        Bool_delete(_t1567, &(Bool){1});
                                                        Bool_delete(_t1568, &(Bool){1});
                                                        Bool_delete(_t1569, &(Bool){1});
                                                        Bool_delete(_t1570, &(Bool){1});
                                                        Bool_delete(_t1571, &(Bool){1});
                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                        Bool_delete(_t1572, &(Bool){1});
                                                        return _t1457;
                                                    } else {
                                                        Bool *_t1560 = TokenType_eq(_sw1445, TokenType_Plus());
                                                        if (DEREF(_t1560)) {
                                                            Str *_t1458 = Str_lit("+", 1ULL);
                                                            Bool_delete(_t1560, &(Bool){1});
                                                            Bool_delete(_t1561, &(Bool){1});
                                                            Bool_delete(_t1562, &(Bool){1});
                                                            Bool_delete(_t1563, &(Bool){1});
                                                            Bool_delete(_t1564, &(Bool){1});
                                                            Bool_delete(_t1565, &(Bool){1});
                                                            Bool_delete(_t1566, &(Bool){1});
                                                            Bool_delete(_t1567, &(Bool){1});
                                                            Bool_delete(_t1568, &(Bool){1});
                                                            Bool_delete(_t1569, &(Bool){1});
                                                            Bool_delete(_t1570, &(Bool){1});
                                                            Bool_delete(_t1571, &(Bool){1});
                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                            Bool_delete(_t1572, &(Bool){1});
                                                            return _t1458;
                                                        } else {
                                                            Bool *_t1559 = TokenType_eq(_sw1445, TokenType_Star());
                                                            if (DEREF(_t1559)) {
                                                                Str *_t1459 = Str_lit("*", 1ULL);
                                                                Bool_delete(_t1559, &(Bool){1});
                                                                Bool_delete(_t1560, &(Bool){1});
                                                                Bool_delete(_t1561, &(Bool){1});
                                                                Bool_delete(_t1562, &(Bool){1});
                                                                Bool_delete(_t1563, &(Bool){1});
                                                                Bool_delete(_t1564, &(Bool){1});
                                                                Bool_delete(_t1565, &(Bool){1});
                                                                Bool_delete(_t1566, &(Bool){1});
                                                                Bool_delete(_t1567, &(Bool){1});
                                                                Bool_delete(_t1568, &(Bool){1});
                                                                Bool_delete(_t1569, &(Bool){1});
                                                                Bool_delete(_t1570, &(Bool){1});
                                                                Bool_delete(_t1571, &(Bool){1});
                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                Bool_delete(_t1572, &(Bool){1});
                                                                return _t1459;
                                                            } else {
                                                                Bool *_t1558 = TokenType_eq(_sw1445, TokenType_Slash());
                                                                if (DEREF(_t1558)) {
                                                                    Str *_t1460 = Str_lit("/", 1ULL);
                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                    return _t1460;
                                                                } else {
                                                                    Bool *_t1557 = TokenType_eq(_sw1445, TokenType_Dot());
                                                                    if (DEREF(_t1557)) {
                                                                        Str *_t1461 = Str_lit(".", 1ULL);
                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                        return _t1461;
                                                                    } else {
                                                                        Bool *_t1556 = TokenType_eq(_sw1445, TokenType_DotDot());
                                                                        if (DEREF(_t1556)) {
                                                                            Str *_t1462 = Str_lit("..", 2ULL);
                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                            return _t1462;
                                                                        } else {
                                                                            Bool *_t1555 = TokenType_eq(_sw1445, TokenType_Eq());
                                                                            if (DEREF(_t1555)) {
                                                                                Str *_t1463 = Str_lit("=", 1ULL);
                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                return _t1463;
                                                                            } else {
                                                                                Bool *_t1554 = TokenType_eq(_sw1445, TokenType_EqEq());
                                                                                if (DEREF(_t1554)) {
                                                                                    Str *_t1464 = Str_lit("==", 2ULL);
                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                    return _t1464;
                                                                                } else {
                                                                                    Bool *_t1553 = TokenType_eq(_sw1445, TokenType_Neq());
                                                                                    if (DEREF(_t1553)) {
                                                                                        Str *_t1465 = Str_lit("!=", 2ULL);
                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                        return _t1465;
                                                                                    } else {
                                                                                        Bool *_t1552 = TokenType_eq(_sw1445, TokenType_Lt());
                                                                                        if (DEREF(_t1552)) {
                                                                                            Str *_t1466 = Str_lit("<", 1ULL);
                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                            return _t1466;
                                                                                        } else {
                                                                                            Bool *_t1551 = TokenType_eq(_sw1445, TokenType_LtEq());
                                                                                            if (DEREF(_t1551)) {
                                                                                                Str *_t1467 = Str_lit("<=", 2ULL);
                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                return _t1467;
                                                                                            } else {
                                                                                                Bool *_t1550 = TokenType_eq(_sw1445, TokenType_Gt());
                                                                                                if (DEREF(_t1550)) {
                                                                                                    Str *_t1468 = Str_lit(">", 1ULL);
                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                    return _t1468;
                                                                                                } else {
                                                                                                    Bool *_t1549 = TokenType_eq(_sw1445, TokenType_GtEq());
                                                                                                    if (DEREF(_t1549)) {
                                                                                                        Str *_t1469 = Str_lit(">=", 2ULL);
                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                        return _t1469;
                                                                                                    } else {
                                                                                                        Bool *_t1548 = TokenType_eq(_sw1445, TokenType_ColonEq());
                                                                                                        if (DEREF(_t1548)) {
                                                                                                            Str *_t1470 = Str_lit(":=", 2ULL);
                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                            return _t1470;
                                                                                                        } else {
                                                                                                            Bool *_t1547 = TokenType_eq(_sw1445, TokenType_Ident());
                                                                                                            if (DEREF(_t1547)) {
                                                                                                                Str *_t1471 = Str_lit("identifier", 10ULL);
                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                return _t1471;
                                                                                                            } else {
                                                                                                                Bool *_t1546 = TokenType_eq(_sw1445, TokenType_StringTok());
                                                                                                                if (DEREF(_t1546)) {
                                                                                                                    Str *_t1472 = Str_lit("string", 6ULL);
                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                    return _t1472;
                                                                                                                } else {
                                                                                                                    Bool *_t1545 = TokenType_eq(_sw1445, TokenType_Number());
                                                                                                                    if (DEREF(_t1545)) {
                                                                                                                        Str *_t1473 = Str_lit("number", 6ULL);
                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                        return _t1473;
                                                                                                                    } else {
                                                                                                                        Bool *_t1544 = TokenType_eq(_sw1445, TokenType_Char());
                                                                                                                        if (DEREF(_t1544)) {
                                                                                                                            Str *_t1474 = Str_lit("char", 4ULL);
                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                            return _t1474;
                                                                                                                        } else {
                                                                                                                            Bool *_t1543 = TokenType_eq(_sw1445, TokenType_KwMode());
                                                                                                                            if (DEREF(_t1543)) {
                                                                                                                                Str *_t1475 = Str_lit("mode", 4ULL);
                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                return _t1475;
                                                                                                                            } else {
                                                                                                                                Bool *_t1542 = TokenType_eq(_sw1445, TokenType_KwMut());
                                                                                                                                if (DEREF(_t1542)) {
                                                                                                                                    Str *_t1476 = Str_lit("mut", 3ULL);
                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                    return _t1476;
                                                                                                                                } else {
                                                                                                                                    Bool *_t1541 = TokenType_eq(_sw1445, TokenType_KwOwn());
                                                                                                                                    if (DEREF(_t1541)) {
                                                                                                                                        Str *_t1477 = Str_lit("own", 3ULL);
                                                                                                                                        Bool_delete(_t1541, &(Bool){1});
                                                                                                                                        Bool_delete(_t1542, &(Bool){1});
                                                                                                                                        Bool_delete(_t1543, &(Bool){1});
                                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                                        return _t1477;
                                                                                                                                    } else {
                                                                                                                                        Bool *_t1540 = TokenType_eq(_sw1445, TokenType_KwRef());
                                                                                                                                        if (DEREF(_t1540)) {
                                                                                                                                            Str *_t1478 = Str_lit("ref", 3ULL);
                                                                                                                                            Bool_delete(_t1540, &(Bool){1});
                                                                                                                                            Bool_delete(_t1541, &(Bool){1});
                                                                                                                                            Bool_delete(_t1542, &(Bool){1});
                                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                                            return _t1478;
                                                                                                                                        } else {
                                                                                                                                            Bool *_t1539 = TokenType_eq(_sw1445, TokenType_KwStruct());
                                                                                                                                            if (DEREF(_t1539)) {
                                                                                                                                                Str *_t1479 = Str_lit("struct", 6ULL);
                                                                                                                                                Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                return _t1479;
                                                                                                                                            } else {
                                                                                                                                                Bool *_t1538 = TokenType_eq(_sw1445, TokenType_KwExtStruct());
                                                                                                                                                if (DEREF(_t1538)) {
                                                                                                                                                    Str *_t1480 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                    return _t1480;
                                                                                                                                                } else {
                                                                                                                                                    Bool *_t1537 = TokenType_eq(_sw1445, TokenType_KwEnum());
                                                                                                                                                    if (DEREF(_t1537)) {
                                                                                                                                                        Str *_t1481 = Str_lit("enum", 4ULL);
                                                                                                                                                        Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                        return _t1481;
                                                                                                                                                    } else {
                                                                                                                                                        Bool *_t1536 = TokenType_eq(_sw1445, TokenType_KwNamespace());
                                                                                                                                                        if (DEREF(_t1536)) {
                                                                                                                                                            Str *_t1482 = Str_lit("namespace", 9ULL);
                                                                                                                                                            Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                            return _t1482;
                                                                                                                                                        } else {
                                                                                                                                                            Bool *_t1535 = TokenType_eq(_sw1445, TokenType_KwFunc());
                                                                                                                                                            if (DEREF(_t1535)) {
                                                                                                                                                                Str *_t1483 = Str_lit("func", 4ULL);
                                                                                                                                                                Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                return _t1483;
                                                                                                                                                            } else {
                                                                                                                                                                Bool *_t1534 = TokenType_eq(_sw1445, TokenType_KwProc());
                                                                                                                                                                if (DEREF(_t1534)) {
                                                                                                                                                                    Str *_t1484 = Str_lit("proc", 4ULL);
                                                                                                                                                                    Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                    return _t1484;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool *_t1533 = TokenType_eq(_sw1445, TokenType_KwTest());
                                                                                                                                                                    if (DEREF(_t1533)) {
                                                                                                                                                                        Str *_t1485 = Str_lit("test", 4ULL);
                                                                                                                                                                        Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                        return _t1485;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool *_t1532 = TokenType_eq(_sw1445, TokenType_KwMacro());
                                                                                                                                                                        if (DEREF(_t1532)) {
                                                                                                                                                                            Str *_t1486 = Str_lit("macro", 5ULL);
                                                                                                                                                                            Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                            return _t1486;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool *_t1531 = TokenType_eq(_sw1445, TokenType_KwExtFunc());
                                                                                                                                                                            if (DEREF(_t1531)) {
                                                                                                                                                                                Str *_t1487 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                return _t1487;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool *_t1530 = TokenType_eq(_sw1445, TokenType_KwExtProc());
                                                                                                                                                                                if (DEREF(_t1530)) {
                                                                                                                                                                                    Str *_t1488 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                    Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                    return _t1488;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool *_t1529 = TokenType_eq(_sw1445, TokenType_KwReturns());
                                                                                                                                                                                    if (DEREF(_t1529)) {
                                                                                                                                                                                        Str *_t1489 = Str_lit("returns", 7ULL);
                                                                                                                                                                                        Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                        return _t1489;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool *_t1528 = TokenType_eq(_sw1445, TokenType_KwThrows());
                                                                                                                                                                                        if (DEREF(_t1528)) {
                                                                                                                                                                                            Str *_t1490 = Str_lit("throws", 6ULL);
                                                                                                                                                                                            Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                            return _t1490;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool *_t1527 = TokenType_eq(_sw1445, TokenType_KwIf());
                                                                                                                                                                                            if (DEREF(_t1527)) {
                                                                                                                                                                                                Str *_t1491 = Str_lit("if", 2ULL);
                                                                                                                                                                                                Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                return _t1491;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool *_t1526 = TokenType_eq(_sw1445, TokenType_KwElse());
                                                                                                                                                                                                if (DEREF(_t1526)) {
                                                                                                                                                                                                    Str *_t1492 = Str_lit("else", 4ULL);
                                                                                                                                                                                                    Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                    return _t1492;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool *_t1525 = TokenType_eq(_sw1445, TokenType_KwWhile());
                                                                                                                                                                                                    if (DEREF(_t1525)) {
                                                                                                                                                                                                        Str *_t1493 = Str_lit("while", 5ULL);
                                                                                                                                                                                                        Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                        return _t1493;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool *_t1524 = TokenType_eq(_sw1445, TokenType_KwFor());
                                                                                                                                                                                                        if (DEREF(_t1524)) {
                                                                                                                                                                                                            Str *_t1494 = Str_lit("for", 3ULL);
                                                                                                                                                                                                            Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                            return _t1494;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool *_t1523 = TokenType_eq(_sw1445, TokenType_KwIn());
                                                                                                                                                                                                            if (DEREF(_t1523)) {
                                                                                                                                                                                                                Str *_t1495 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                return _t1495;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool *_t1522 = TokenType_eq(_sw1445, TokenType_KwSwitch());
                                                                                                                                                                                                                if (DEREF(_t1522)) {
                                                                                                                                                                                                                    Str *_t1496 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                    Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                    return _t1496;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool *_t1521 = TokenType_eq(_sw1445, TokenType_KwMatch());
                                                                                                                                                                                                                    if (DEREF(_t1521)) {
                                                                                                                                                                                                                        Str *_t1497 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                        Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                        return _t1497;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool *_t1520 = TokenType_eq(_sw1445, TokenType_KwCase());
                                                                                                                                                                                                                        if (DEREF(_t1520)) {
                                                                                                                                                                                                                            Str *_t1498 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                            Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                            return _t1498;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool *_t1519 = TokenType_eq(_sw1445, TokenType_KwDefault());
                                                                                                                                                                                                                            if (DEREF(_t1519)) {
                                                                                                                                                                                                                                Str *_t1499 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                return _t1499;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool *_t1518 = TokenType_eq(_sw1445, TokenType_KwReturn());
                                                                                                                                                                                                                                if (DEREF(_t1518)) {
                                                                                                                                                                                                                                    Str *_t1500 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                    Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                    return _t1500;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool *_t1517 = TokenType_eq(_sw1445, TokenType_KwThrow());
                                                                                                                                                                                                                                    if (DEREF(_t1517)) {
                                                                                                                                                                                                                                        Str *_t1501 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                        Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                        return _t1501;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool *_t1516 = TokenType_eq(_sw1445, TokenType_KwCatch());
                                                                                                                                                                                                                                        if (DEREF(_t1516)) {
                                                                                                                                                                                                                                            Str *_t1502 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                            Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                            return _t1502;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool *_t1515 = TokenType_eq(_sw1445, TokenType_KwBreak());
                                                                                                                                                                                                                                            if (DEREF(_t1515)) {
                                                                                                                                                                                                                                                Str *_t1503 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                Bool_delete(_t1515, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                                return _t1503;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool *_t1514 = TokenType_eq(_sw1445, TokenType_KwContinue());
                                                                                                                                                                                                                                                if (DEREF(_t1514)) {
                                                                                                                                                                                                                                                    Str *_t1504 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                    Bool_delete(_t1514, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1515, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                                    return _t1504;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool *_t1513 = TokenType_eq(_sw1445, TokenType_KwDefer());
                                                                                                                                                                                                                                                    if (DEREF(_t1513)) {
                                                                                                                                                                                                                                                        Str *_t1505 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                        Bool_delete(_t1513, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1514, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1515, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                        Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                                        return _t1505;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool *_t1512 = TokenType_eq(_sw1445, TokenType_KwTrue());
                                                                                                                                                                                                                                                        if (DEREF(_t1512)) {
                                                                                                                                                                                                                                                            Str *_t1506 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                            Bool_delete(_t1512, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1513, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1514, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1515, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                            Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                                            return _t1506;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool *_t1511 = TokenType_eq(_sw1445, TokenType_KwFalse());
                                                                                                                                                                                                                                                            if (DEREF(_t1511)) {
                                                                                                                                                                                                                                                                Str *_t1507 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                Bool_delete(_t1511, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1512, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1513, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1514, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1515, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                                Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                                                return _t1507;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool *_t1510 = TokenType_eq(_sw1445, TokenType_Error());
                                                                                                                                                                                                                                                                if (DEREF(_t1510)) {
                                                                                                                                                                                                                                                                    Str *_t1508 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                    Bool_delete(_t1510, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1511, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1512, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1513, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1514, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1515, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                                                    return _t1508;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Str *_t1509 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                    Bool_delete(_t1510, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1511, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1512, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1513, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1514, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1515, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1538, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1539, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1540, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1542, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1543, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1544, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1546, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1547, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1548, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1550, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1551, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1552, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1554, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1555, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1556, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1558, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1559, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1560, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1561, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1562, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1563, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1564, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1565, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1566, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1567, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1568, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1569, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1570, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1571, &(Bool){1});
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                                    Bool_delete(_t1572, &(Bool){1});
                                                                                                                                                                                                                                                                    return _t1509;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                Bool_delete(_t1510, &(Bool){1});
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            Bool_delete(_t1511, &(Bool){1});
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        Bool_delete(_t1512, &(Bool){1});
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    Bool_delete(_t1513, &(Bool){1});
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                Bool_delete(_t1514, &(Bool){1});
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            Bool_delete(_t1515, &(Bool){1});
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        Bool_delete(_t1516, &(Bool){1});
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    Bool_delete(_t1517, &(Bool){1});
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                Bool_delete(_t1518, &(Bool){1});
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            Bool_delete(_t1519, &(Bool){1});
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        Bool_delete(_t1520, &(Bool){1});
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    Bool_delete(_t1521, &(Bool){1});
                                                                                                                                                                                                                }
                                                                                                                                                                                                                Bool_delete(_t1522, &(Bool){1});
                                                                                                                                                                                                            }
                                                                                                                                                                                                            Bool_delete(_t1523, &(Bool){1});
                                                                                                                                                                                                        }
                                                                                                                                                                                                        Bool_delete(_t1524, &(Bool){1});
                                                                                                                                                                                                    }
                                                                                                                                                                                                    Bool_delete(_t1525, &(Bool){1});
                                                                                                                                                                                                }
                                                                                                                                                                                                Bool_delete(_t1526, &(Bool){1});
                                                                                                                                                                                            }
                                                                                                                                                                                            Bool_delete(_t1527, &(Bool){1});
                                                                                                                                                                                        }
                                                                                                                                                                                        Bool_delete(_t1528, &(Bool){1});
                                                                                                                                                                                    }
                                                                                                                                                                                    Bool_delete(_t1529, &(Bool){1});
                                                                                                                                                                                }
                                                                                                                                                                                Bool_delete(_t1530, &(Bool){1});
                                                                                                                                                                            }
                                                                                                                                                                            Bool_delete(_t1531, &(Bool){1});
                                                                                                                                                                        }
                                                                                                                                                                        Bool_delete(_t1532, &(Bool){1});
                                                                                                                                                                    }
                                                                                                                                                                    Bool_delete(_t1533, &(Bool){1});
                                                                                                                                                                }
                                                                                                                                                                Bool_delete(_t1534, &(Bool){1});
                                                                                                                                                            }
                                                                                                                                                            Bool_delete(_t1535, &(Bool){1});
                                                                                                                                                        }
                                                                                                                                                        Bool_delete(_t1536, &(Bool){1});
                                                                                                                                                    }
                                                                                                                                                    Bool_delete(_t1537, &(Bool){1});
                                                                                                                                                }
                                                                                                                                                Bool_delete(_t1538, &(Bool){1});
                                                                                                                                            }
                                                                                                                                            Bool_delete(_t1539, &(Bool){1});
                                                                                                                                        }
                                                                                                                                        Bool_delete(_t1540, &(Bool){1});
                                                                                                                                    }
                                                                                                                                    Bool_delete(_t1541, &(Bool){1});
                                                                                                                                }
                                                                                                                                Bool_delete(_t1542, &(Bool){1});
                                                                                                                            }
                                                                                                                            Bool_delete(_t1543, &(Bool){1});
                                                                                                                        }
                                                                                                                        Bool_delete(_t1544, &(Bool){1});
                                                                                                                    }
                                                                                                                    Bool_delete(_t1545, &(Bool){1});
                                                                                                                }
                                                                                                                Bool_delete(_t1546, &(Bool){1});
                                                                                                            }
                                                                                                            Bool_delete(_t1547, &(Bool){1});
                                                                                                        }
                                                                                                        Bool_delete(_t1548, &(Bool){1});
                                                                                                    }
                                                                                                    Bool_delete(_t1549, &(Bool){1});
                                                                                                }
                                                                                                Bool_delete(_t1550, &(Bool){1});
                                                                                            }
                                                                                            Bool_delete(_t1551, &(Bool){1});
                                                                                        }
                                                                                        Bool_delete(_t1552, &(Bool){1});
                                                                                    }
                                                                                    Bool_delete(_t1553, &(Bool){1});
                                                                                }
                                                                                Bool_delete(_t1554, &(Bool){1});
                                                                            }
                                                                            Bool_delete(_t1555, &(Bool){1});
                                                                        }
                                                                        Bool_delete(_t1556, &(Bool){1});
                                                                    }
                                                                    Bool_delete(_t1557, &(Bool){1});
                                                                }
                                                                Bool_delete(_t1558, &(Bool){1});
                                                            }
                                                            Bool_delete(_t1559, &(Bool){1});
                                                        }
                                                        Bool_delete(_t1560, &(Bool){1});
                                                    }
                                                    Bool_delete(_t1561, &(Bool){1});
                                                }
                                                Bool_delete(_t1562, &(Bool){1});
                                            }
                                            Bool_delete(_t1563, &(Bool){1});
                                        }
                                        Bool_delete(_t1564, &(Bool){1});
                                    }
                                    Bool_delete(_t1565, &(Bool){1});
                                }
                                Bool_delete(_t1566, &(Bool){1});
                            }
                            Bool_delete(_t1567, &(Bool){1});
                        }
                        Bool_delete(_t1568, &(Bool){1});
                    }
                    Bool_delete(_t1569, &(Bool){1});
                }
                Bool_delete(_t1570, &(Bool){1});
            }
            Bool_delete(_t1571, &(Bool){1});
        }
        TokenType_delete(_sw1445, &(Bool){1});
        Bool_delete(_t1572, &(Bool){1});
    }
}

TokenType * lookup_keyword(Str * word) {
    {
        Str *_sw1573 = Str_clone(word);
        Str *_t1638 = Str_lit("mode", 4ULL);
        Bool *_t1639 = Str_eq(_sw1573, _t1638);
        Str_delete(_t1638, &(Bool){1});
        if (DEREF(_t1639)) {
            Str_delete(_sw1573, &(Bool){1});
            Bool_delete(_t1639, &(Bool){1});
            return TokenType_KwMode();
        } else {
            Str *_t1636 = Str_lit("mut", 3ULL);
            Bool *_t1637 = Str_eq(_sw1573, _t1636);
            Str_delete(_t1636, &(Bool){1});
            if (DEREF(_t1637)) {
                Bool_delete(_t1637, &(Bool){1});
                Str_delete(_sw1573, &(Bool){1});
                Bool_delete(_t1639, &(Bool){1});
                return TokenType_KwMut();
            } else {
                Str *_t1634 = Str_lit("own", 3ULL);
                Bool *_t1635 = Str_eq(_sw1573, _t1634);
                Str_delete(_t1634, &(Bool){1});
                if (DEREF(_t1635)) {
                    Bool_delete(_t1635, &(Bool){1});
                    Bool_delete(_t1637, &(Bool){1});
                    Str_delete(_sw1573, &(Bool){1});
                    Bool_delete(_t1639, &(Bool){1});
                    return TokenType_KwOwn();
                } else {
                    Str *_t1632 = Str_lit("ref", 3ULL);
                    Bool *_t1633 = Str_eq(_sw1573, _t1632);
                    Str_delete(_t1632, &(Bool){1});
                    if (DEREF(_t1633)) {
                        Bool_delete(_t1633, &(Bool){1});
                        Bool_delete(_t1635, &(Bool){1});
                        Bool_delete(_t1637, &(Bool){1});
                        Str_delete(_sw1573, &(Bool){1});
                        Bool_delete(_t1639, &(Bool){1});
                        return TokenType_KwRef();
                    } else {
                        Str *_t1630 = Str_lit("struct", 6ULL);
                        Bool *_t1631 = Str_eq(_sw1573, _t1630);
                        Str_delete(_t1630, &(Bool){1});
                        if (DEREF(_t1631)) {
                            Bool_delete(_t1631, &(Bool){1});
                            Bool_delete(_t1633, &(Bool){1});
                            Bool_delete(_t1635, &(Bool){1});
                            Bool_delete(_t1637, &(Bool){1});
                            Str_delete(_sw1573, &(Bool){1});
                            Bool_delete(_t1639, &(Bool){1});
                            return TokenType_KwStruct();
                        } else {
                            Str *_t1628 = Str_lit("ext_struct", 10ULL);
                            Bool *_t1629 = Str_eq(_sw1573, _t1628);
                            Str_delete(_t1628, &(Bool){1});
                            if (DEREF(_t1629)) {
                                Bool_delete(_t1629, &(Bool){1});
                                Bool_delete(_t1631, &(Bool){1});
                                Bool_delete(_t1633, &(Bool){1});
                                Bool_delete(_t1635, &(Bool){1});
                                Bool_delete(_t1637, &(Bool){1});
                                Str_delete(_sw1573, &(Bool){1});
                                Bool_delete(_t1639, &(Bool){1});
                                return TokenType_KwExtStruct();
                            } else {
                                Str *_t1626 = Str_lit("enum", 4ULL);
                                Bool *_t1627 = Str_eq(_sw1573, _t1626);
                                Str_delete(_t1626, &(Bool){1});
                                if (DEREF(_t1627)) {
                                    Bool_delete(_t1627, &(Bool){1});
                                    Bool_delete(_t1629, &(Bool){1});
                                    Bool_delete(_t1631, &(Bool){1});
                                    Bool_delete(_t1633, &(Bool){1});
                                    Bool_delete(_t1635, &(Bool){1});
                                    Bool_delete(_t1637, &(Bool){1});
                                    Str_delete(_sw1573, &(Bool){1});
                                    Bool_delete(_t1639, &(Bool){1});
                                    return TokenType_KwEnum();
                                } else {
                                    Str *_t1624 = Str_lit("namespace", 9ULL);
                                    Bool *_t1625 = Str_eq(_sw1573, _t1624);
                                    Str_delete(_t1624, &(Bool){1});
                                    if (DEREF(_t1625)) {
                                        Bool_delete(_t1625, &(Bool){1});
                                        Bool_delete(_t1627, &(Bool){1});
                                        Bool_delete(_t1629, &(Bool){1});
                                        Bool_delete(_t1631, &(Bool){1});
                                        Bool_delete(_t1633, &(Bool){1});
                                        Bool_delete(_t1635, &(Bool){1});
                                        Bool_delete(_t1637, &(Bool){1});
                                        Str_delete(_sw1573, &(Bool){1});
                                        Bool_delete(_t1639, &(Bool){1});
                                        return TokenType_KwNamespace();
                                    } else {
                                        Str *_t1622 = Str_lit("func", 4ULL);
                                        Bool *_t1623 = Str_eq(_sw1573, _t1622);
                                        Str_delete(_t1622, &(Bool){1});
                                        if (DEREF(_t1623)) {
                                            Bool_delete(_t1623, &(Bool){1});
                                            Bool_delete(_t1625, &(Bool){1});
                                            Bool_delete(_t1627, &(Bool){1});
                                            Bool_delete(_t1629, &(Bool){1});
                                            Bool_delete(_t1631, &(Bool){1});
                                            Bool_delete(_t1633, &(Bool){1});
                                            Bool_delete(_t1635, &(Bool){1});
                                            Bool_delete(_t1637, &(Bool){1});
                                            Str_delete(_sw1573, &(Bool){1});
                                            Bool_delete(_t1639, &(Bool){1});
                                            return TokenType_KwFunc();
                                        } else {
                                            Str *_t1620 = Str_lit("proc", 4ULL);
                                            Bool *_t1621 = Str_eq(_sw1573, _t1620);
                                            Str_delete(_t1620, &(Bool){1});
                                            if (DEREF(_t1621)) {
                                                Bool_delete(_t1621, &(Bool){1});
                                                Bool_delete(_t1623, &(Bool){1});
                                                Bool_delete(_t1625, &(Bool){1});
                                                Bool_delete(_t1627, &(Bool){1});
                                                Bool_delete(_t1629, &(Bool){1});
                                                Bool_delete(_t1631, &(Bool){1});
                                                Bool_delete(_t1633, &(Bool){1});
                                                Bool_delete(_t1635, &(Bool){1});
                                                Bool_delete(_t1637, &(Bool){1});
                                                Str_delete(_sw1573, &(Bool){1});
                                                Bool_delete(_t1639, &(Bool){1});
                                                return TokenType_KwProc();
                                            } else {
                                                Str *_t1618 = Str_lit("test", 4ULL);
                                                Bool *_t1619 = Str_eq(_sw1573, _t1618);
                                                Str_delete(_t1618, &(Bool){1});
                                                if (DEREF(_t1619)) {
                                                    Bool_delete(_t1619, &(Bool){1});
                                                    Bool_delete(_t1621, &(Bool){1});
                                                    Bool_delete(_t1623, &(Bool){1});
                                                    Bool_delete(_t1625, &(Bool){1});
                                                    Bool_delete(_t1627, &(Bool){1});
                                                    Bool_delete(_t1629, &(Bool){1});
                                                    Bool_delete(_t1631, &(Bool){1});
                                                    Bool_delete(_t1633, &(Bool){1});
                                                    Bool_delete(_t1635, &(Bool){1});
                                                    Bool_delete(_t1637, &(Bool){1});
                                                    Str_delete(_sw1573, &(Bool){1});
                                                    Bool_delete(_t1639, &(Bool){1});
                                                    return TokenType_KwTest();
                                                } else {
                                                    Str *_t1616 = Str_lit("macro", 5ULL);
                                                    Bool *_t1617 = Str_eq(_sw1573, _t1616);
                                                    Str_delete(_t1616, &(Bool){1});
                                                    if (DEREF(_t1617)) {
                                                        Bool_delete(_t1617, &(Bool){1});
                                                        Bool_delete(_t1619, &(Bool){1});
                                                        Bool_delete(_t1621, &(Bool){1});
                                                        Bool_delete(_t1623, &(Bool){1});
                                                        Bool_delete(_t1625, &(Bool){1});
                                                        Bool_delete(_t1627, &(Bool){1});
                                                        Bool_delete(_t1629, &(Bool){1});
                                                        Bool_delete(_t1631, &(Bool){1});
                                                        Bool_delete(_t1633, &(Bool){1});
                                                        Bool_delete(_t1635, &(Bool){1});
                                                        Bool_delete(_t1637, &(Bool){1});
                                                        Str_delete(_sw1573, &(Bool){1});
                                                        Bool_delete(_t1639, &(Bool){1});
                                                        return TokenType_KwMacro();
                                                    } else {
                                                        Str *_t1614 = Str_lit("ext_func", 8ULL);
                                                        Bool *_t1615 = Str_eq(_sw1573, _t1614);
                                                        Str_delete(_t1614, &(Bool){1});
                                                        if (DEREF(_t1615)) {
                                                            Bool_delete(_t1615, &(Bool){1});
                                                            Bool_delete(_t1617, &(Bool){1});
                                                            Bool_delete(_t1619, &(Bool){1});
                                                            Bool_delete(_t1621, &(Bool){1});
                                                            Bool_delete(_t1623, &(Bool){1});
                                                            Bool_delete(_t1625, &(Bool){1});
                                                            Bool_delete(_t1627, &(Bool){1});
                                                            Bool_delete(_t1629, &(Bool){1});
                                                            Bool_delete(_t1631, &(Bool){1});
                                                            Bool_delete(_t1633, &(Bool){1});
                                                            Bool_delete(_t1635, &(Bool){1});
                                                            Bool_delete(_t1637, &(Bool){1});
                                                            Str_delete(_sw1573, &(Bool){1});
                                                            Bool_delete(_t1639, &(Bool){1});
                                                            return TokenType_KwExtFunc();
                                                        } else {
                                                            Str *_t1612 = Str_lit("ext_proc", 8ULL);
                                                            Bool *_t1613 = Str_eq(_sw1573, _t1612);
                                                            Str_delete(_t1612, &(Bool){1});
                                                            if (DEREF(_t1613)) {
                                                                Bool_delete(_t1613, &(Bool){1});
                                                                Bool_delete(_t1615, &(Bool){1});
                                                                Bool_delete(_t1617, &(Bool){1});
                                                                Bool_delete(_t1619, &(Bool){1});
                                                                Bool_delete(_t1621, &(Bool){1});
                                                                Bool_delete(_t1623, &(Bool){1});
                                                                Bool_delete(_t1625, &(Bool){1});
                                                                Bool_delete(_t1627, &(Bool){1});
                                                                Bool_delete(_t1629, &(Bool){1});
                                                                Bool_delete(_t1631, &(Bool){1});
                                                                Bool_delete(_t1633, &(Bool){1});
                                                                Bool_delete(_t1635, &(Bool){1});
                                                                Bool_delete(_t1637, &(Bool){1});
                                                                Str_delete(_sw1573, &(Bool){1});
                                                                Bool_delete(_t1639, &(Bool){1});
                                                                return TokenType_KwExtProc();
                                                            } else {
                                                                Str *_t1610 = Str_lit("returns", 7ULL);
                                                                Bool *_t1611 = Str_eq(_sw1573, _t1610);
                                                                Str_delete(_t1610, &(Bool){1});
                                                                if (DEREF(_t1611)) {
                                                                    Bool_delete(_t1611, &(Bool){1});
                                                                    Bool_delete(_t1613, &(Bool){1});
                                                                    Bool_delete(_t1615, &(Bool){1});
                                                                    Bool_delete(_t1617, &(Bool){1});
                                                                    Bool_delete(_t1619, &(Bool){1});
                                                                    Bool_delete(_t1621, &(Bool){1});
                                                                    Bool_delete(_t1623, &(Bool){1});
                                                                    Bool_delete(_t1625, &(Bool){1});
                                                                    Bool_delete(_t1627, &(Bool){1});
                                                                    Bool_delete(_t1629, &(Bool){1});
                                                                    Bool_delete(_t1631, &(Bool){1});
                                                                    Bool_delete(_t1633, &(Bool){1});
                                                                    Bool_delete(_t1635, &(Bool){1});
                                                                    Bool_delete(_t1637, &(Bool){1});
                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                    Bool_delete(_t1639, &(Bool){1});
                                                                    return TokenType_KwReturns();
                                                                } else {
                                                                    Str *_t1608 = Str_lit("throws", 6ULL);
                                                                    Bool *_t1609 = Str_eq(_sw1573, _t1608);
                                                                    Str_delete(_t1608, &(Bool){1});
                                                                    if (DEREF(_t1609)) {
                                                                        Bool_delete(_t1609, &(Bool){1});
                                                                        Bool_delete(_t1611, &(Bool){1});
                                                                        Bool_delete(_t1613, &(Bool){1});
                                                                        Bool_delete(_t1615, &(Bool){1});
                                                                        Bool_delete(_t1617, &(Bool){1});
                                                                        Bool_delete(_t1619, &(Bool){1});
                                                                        Bool_delete(_t1621, &(Bool){1});
                                                                        Bool_delete(_t1623, &(Bool){1});
                                                                        Bool_delete(_t1625, &(Bool){1});
                                                                        Bool_delete(_t1627, &(Bool){1});
                                                                        Bool_delete(_t1629, &(Bool){1});
                                                                        Bool_delete(_t1631, &(Bool){1});
                                                                        Bool_delete(_t1633, &(Bool){1});
                                                                        Bool_delete(_t1635, &(Bool){1});
                                                                        Bool_delete(_t1637, &(Bool){1});
                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                        Bool_delete(_t1639, &(Bool){1});
                                                                        return TokenType_KwThrows();
                                                                    } else {
                                                                        Str *_t1606 = Str_lit("if", 2ULL);
                                                                        Bool *_t1607 = Str_eq(_sw1573, _t1606);
                                                                        Str_delete(_t1606, &(Bool){1});
                                                                        if (DEREF(_t1607)) {
                                                                            Bool_delete(_t1607, &(Bool){1});
                                                                            Bool_delete(_t1609, &(Bool){1});
                                                                            Bool_delete(_t1611, &(Bool){1});
                                                                            Bool_delete(_t1613, &(Bool){1});
                                                                            Bool_delete(_t1615, &(Bool){1});
                                                                            Bool_delete(_t1617, &(Bool){1});
                                                                            Bool_delete(_t1619, &(Bool){1});
                                                                            Bool_delete(_t1621, &(Bool){1});
                                                                            Bool_delete(_t1623, &(Bool){1});
                                                                            Bool_delete(_t1625, &(Bool){1});
                                                                            Bool_delete(_t1627, &(Bool){1});
                                                                            Bool_delete(_t1629, &(Bool){1});
                                                                            Bool_delete(_t1631, &(Bool){1});
                                                                            Bool_delete(_t1633, &(Bool){1});
                                                                            Bool_delete(_t1635, &(Bool){1});
                                                                            Bool_delete(_t1637, &(Bool){1});
                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                            Bool_delete(_t1639, &(Bool){1});
                                                                            return TokenType_KwIf();
                                                                        } else {
                                                                            Str *_t1604 = Str_lit("else", 4ULL);
                                                                            Bool *_t1605 = Str_eq(_sw1573, _t1604);
                                                                            Str_delete(_t1604, &(Bool){1});
                                                                            if (DEREF(_t1605)) {
                                                                                Bool_delete(_t1605, &(Bool){1});
                                                                                Bool_delete(_t1607, &(Bool){1});
                                                                                Bool_delete(_t1609, &(Bool){1});
                                                                                Bool_delete(_t1611, &(Bool){1});
                                                                                Bool_delete(_t1613, &(Bool){1});
                                                                                Bool_delete(_t1615, &(Bool){1});
                                                                                Bool_delete(_t1617, &(Bool){1});
                                                                                Bool_delete(_t1619, &(Bool){1});
                                                                                Bool_delete(_t1621, &(Bool){1});
                                                                                Bool_delete(_t1623, &(Bool){1});
                                                                                Bool_delete(_t1625, &(Bool){1});
                                                                                Bool_delete(_t1627, &(Bool){1});
                                                                                Bool_delete(_t1629, &(Bool){1});
                                                                                Bool_delete(_t1631, &(Bool){1});
                                                                                Bool_delete(_t1633, &(Bool){1});
                                                                                Bool_delete(_t1635, &(Bool){1});
                                                                                Bool_delete(_t1637, &(Bool){1});
                                                                                Str_delete(_sw1573, &(Bool){1});
                                                                                Bool_delete(_t1639, &(Bool){1});
                                                                                return TokenType_KwElse();
                                                                            } else {
                                                                                Str *_t1602 = Str_lit("while", 5ULL);
                                                                                Bool *_t1603 = Str_eq(_sw1573, _t1602);
                                                                                Str_delete(_t1602, &(Bool){1});
                                                                                if (DEREF(_t1603)) {
                                                                                    Bool_delete(_t1603, &(Bool){1});
                                                                                    Bool_delete(_t1605, &(Bool){1});
                                                                                    Bool_delete(_t1607, &(Bool){1});
                                                                                    Bool_delete(_t1609, &(Bool){1});
                                                                                    Bool_delete(_t1611, &(Bool){1});
                                                                                    Bool_delete(_t1613, &(Bool){1});
                                                                                    Bool_delete(_t1615, &(Bool){1});
                                                                                    Bool_delete(_t1617, &(Bool){1});
                                                                                    Bool_delete(_t1619, &(Bool){1});
                                                                                    Bool_delete(_t1621, &(Bool){1});
                                                                                    Bool_delete(_t1623, &(Bool){1});
                                                                                    Bool_delete(_t1625, &(Bool){1});
                                                                                    Bool_delete(_t1627, &(Bool){1});
                                                                                    Bool_delete(_t1629, &(Bool){1});
                                                                                    Bool_delete(_t1631, &(Bool){1});
                                                                                    Bool_delete(_t1633, &(Bool){1});
                                                                                    Bool_delete(_t1635, &(Bool){1});
                                                                                    Bool_delete(_t1637, &(Bool){1});
                                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                                    Bool_delete(_t1639, &(Bool){1});
                                                                                    return TokenType_KwWhile();
                                                                                } else {
                                                                                    Str *_t1600 = Str_lit("for", 3ULL);
                                                                                    Bool *_t1601 = Str_eq(_sw1573, _t1600);
                                                                                    Str_delete(_t1600, &(Bool){1});
                                                                                    if (DEREF(_t1601)) {
                                                                                        Bool_delete(_t1601, &(Bool){1});
                                                                                        Bool_delete(_t1603, &(Bool){1});
                                                                                        Bool_delete(_t1605, &(Bool){1});
                                                                                        Bool_delete(_t1607, &(Bool){1});
                                                                                        Bool_delete(_t1609, &(Bool){1});
                                                                                        Bool_delete(_t1611, &(Bool){1});
                                                                                        Bool_delete(_t1613, &(Bool){1});
                                                                                        Bool_delete(_t1615, &(Bool){1});
                                                                                        Bool_delete(_t1617, &(Bool){1});
                                                                                        Bool_delete(_t1619, &(Bool){1});
                                                                                        Bool_delete(_t1621, &(Bool){1});
                                                                                        Bool_delete(_t1623, &(Bool){1});
                                                                                        Bool_delete(_t1625, &(Bool){1});
                                                                                        Bool_delete(_t1627, &(Bool){1});
                                                                                        Bool_delete(_t1629, &(Bool){1});
                                                                                        Bool_delete(_t1631, &(Bool){1});
                                                                                        Bool_delete(_t1633, &(Bool){1});
                                                                                        Bool_delete(_t1635, &(Bool){1});
                                                                                        Bool_delete(_t1637, &(Bool){1});
                                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                                        Bool_delete(_t1639, &(Bool){1});
                                                                                        return TokenType_KwFor();
                                                                                    } else {
                                                                                        Str *_t1598 = Str_lit("in", 2ULL);
                                                                                        Bool *_t1599 = Str_eq(_sw1573, _t1598);
                                                                                        Str_delete(_t1598, &(Bool){1});
                                                                                        if (DEREF(_t1599)) {
                                                                                            Bool_delete(_t1599, &(Bool){1});
                                                                                            Bool_delete(_t1601, &(Bool){1});
                                                                                            Bool_delete(_t1603, &(Bool){1});
                                                                                            Bool_delete(_t1605, &(Bool){1});
                                                                                            Bool_delete(_t1607, &(Bool){1});
                                                                                            Bool_delete(_t1609, &(Bool){1});
                                                                                            Bool_delete(_t1611, &(Bool){1});
                                                                                            Bool_delete(_t1613, &(Bool){1});
                                                                                            Bool_delete(_t1615, &(Bool){1});
                                                                                            Bool_delete(_t1617, &(Bool){1});
                                                                                            Bool_delete(_t1619, &(Bool){1});
                                                                                            Bool_delete(_t1621, &(Bool){1});
                                                                                            Bool_delete(_t1623, &(Bool){1});
                                                                                            Bool_delete(_t1625, &(Bool){1});
                                                                                            Bool_delete(_t1627, &(Bool){1});
                                                                                            Bool_delete(_t1629, &(Bool){1});
                                                                                            Bool_delete(_t1631, &(Bool){1});
                                                                                            Bool_delete(_t1633, &(Bool){1});
                                                                                            Bool_delete(_t1635, &(Bool){1});
                                                                                            Bool_delete(_t1637, &(Bool){1});
                                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                                            Bool_delete(_t1639, &(Bool){1});
                                                                                            return TokenType_KwIn();
                                                                                        } else {
                                                                                            Str *_t1596 = Str_lit("switch", 6ULL);
                                                                                            Bool *_t1597 = Str_eq(_sw1573, _t1596);
                                                                                            Str_delete(_t1596, &(Bool){1});
                                                                                            if (DEREF(_t1597)) {
                                                                                                Bool_delete(_t1597, &(Bool){1});
                                                                                                Bool_delete(_t1599, &(Bool){1});
                                                                                                Bool_delete(_t1601, &(Bool){1});
                                                                                                Bool_delete(_t1603, &(Bool){1});
                                                                                                Bool_delete(_t1605, &(Bool){1});
                                                                                                Bool_delete(_t1607, &(Bool){1});
                                                                                                Bool_delete(_t1609, &(Bool){1});
                                                                                                Bool_delete(_t1611, &(Bool){1});
                                                                                                Bool_delete(_t1613, &(Bool){1});
                                                                                                Bool_delete(_t1615, &(Bool){1});
                                                                                                Bool_delete(_t1617, &(Bool){1});
                                                                                                Bool_delete(_t1619, &(Bool){1});
                                                                                                Bool_delete(_t1621, &(Bool){1});
                                                                                                Bool_delete(_t1623, &(Bool){1});
                                                                                                Bool_delete(_t1625, &(Bool){1});
                                                                                                Bool_delete(_t1627, &(Bool){1});
                                                                                                Bool_delete(_t1629, &(Bool){1});
                                                                                                Bool_delete(_t1631, &(Bool){1});
                                                                                                Bool_delete(_t1633, &(Bool){1});
                                                                                                Bool_delete(_t1635, &(Bool){1});
                                                                                                Bool_delete(_t1637, &(Bool){1});
                                                                                                Str_delete(_sw1573, &(Bool){1});
                                                                                                Bool_delete(_t1639, &(Bool){1});
                                                                                                return TokenType_KwSwitch();
                                                                                            } else {
                                                                                                Str *_t1594 = Str_lit("match", 5ULL);
                                                                                                Bool *_t1595 = Str_eq(_sw1573, _t1594);
                                                                                                Str_delete(_t1594, &(Bool){1});
                                                                                                if (DEREF(_t1595)) {
                                                                                                    Bool_delete(_t1595, &(Bool){1});
                                                                                                    Bool_delete(_t1597, &(Bool){1});
                                                                                                    Bool_delete(_t1599, &(Bool){1});
                                                                                                    Bool_delete(_t1601, &(Bool){1});
                                                                                                    Bool_delete(_t1603, &(Bool){1});
                                                                                                    Bool_delete(_t1605, &(Bool){1});
                                                                                                    Bool_delete(_t1607, &(Bool){1});
                                                                                                    Bool_delete(_t1609, &(Bool){1});
                                                                                                    Bool_delete(_t1611, &(Bool){1});
                                                                                                    Bool_delete(_t1613, &(Bool){1});
                                                                                                    Bool_delete(_t1615, &(Bool){1});
                                                                                                    Bool_delete(_t1617, &(Bool){1});
                                                                                                    Bool_delete(_t1619, &(Bool){1});
                                                                                                    Bool_delete(_t1621, &(Bool){1});
                                                                                                    Bool_delete(_t1623, &(Bool){1});
                                                                                                    Bool_delete(_t1625, &(Bool){1});
                                                                                                    Bool_delete(_t1627, &(Bool){1});
                                                                                                    Bool_delete(_t1629, &(Bool){1});
                                                                                                    Bool_delete(_t1631, &(Bool){1});
                                                                                                    Bool_delete(_t1633, &(Bool){1});
                                                                                                    Bool_delete(_t1635, &(Bool){1});
                                                                                                    Bool_delete(_t1637, &(Bool){1});
                                                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                                                    Bool_delete(_t1639, &(Bool){1});
                                                                                                    return TokenType_KwMatch();
                                                                                                } else {
                                                                                                    Str *_t1592 = Str_lit("case", 4ULL);
                                                                                                    Bool *_t1593 = Str_eq(_sw1573, _t1592);
                                                                                                    Str_delete(_t1592, &(Bool){1});
                                                                                                    if (DEREF(_t1593)) {
                                                                                                        Bool_delete(_t1593, &(Bool){1});
                                                                                                        Bool_delete(_t1595, &(Bool){1});
                                                                                                        Bool_delete(_t1597, &(Bool){1});
                                                                                                        Bool_delete(_t1599, &(Bool){1});
                                                                                                        Bool_delete(_t1601, &(Bool){1});
                                                                                                        Bool_delete(_t1603, &(Bool){1});
                                                                                                        Bool_delete(_t1605, &(Bool){1});
                                                                                                        Bool_delete(_t1607, &(Bool){1});
                                                                                                        Bool_delete(_t1609, &(Bool){1});
                                                                                                        Bool_delete(_t1611, &(Bool){1});
                                                                                                        Bool_delete(_t1613, &(Bool){1});
                                                                                                        Bool_delete(_t1615, &(Bool){1});
                                                                                                        Bool_delete(_t1617, &(Bool){1});
                                                                                                        Bool_delete(_t1619, &(Bool){1});
                                                                                                        Bool_delete(_t1621, &(Bool){1});
                                                                                                        Bool_delete(_t1623, &(Bool){1});
                                                                                                        Bool_delete(_t1625, &(Bool){1});
                                                                                                        Bool_delete(_t1627, &(Bool){1});
                                                                                                        Bool_delete(_t1629, &(Bool){1});
                                                                                                        Bool_delete(_t1631, &(Bool){1});
                                                                                                        Bool_delete(_t1633, &(Bool){1});
                                                                                                        Bool_delete(_t1635, &(Bool){1});
                                                                                                        Bool_delete(_t1637, &(Bool){1});
                                                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                                                        Bool_delete(_t1639, &(Bool){1});
                                                                                                        return TokenType_KwCase();
                                                                                                    } else {
                                                                                                        Str *_t1590 = Str_lit("default", 7ULL);
                                                                                                        Bool *_t1591 = Str_eq(_sw1573, _t1590);
                                                                                                        Str_delete(_t1590, &(Bool){1});
                                                                                                        if (DEREF(_t1591)) {
                                                                                                            Bool_delete(_t1591, &(Bool){1});
                                                                                                            Bool_delete(_t1593, &(Bool){1});
                                                                                                            Bool_delete(_t1595, &(Bool){1});
                                                                                                            Bool_delete(_t1597, &(Bool){1});
                                                                                                            Bool_delete(_t1599, &(Bool){1});
                                                                                                            Bool_delete(_t1601, &(Bool){1});
                                                                                                            Bool_delete(_t1603, &(Bool){1});
                                                                                                            Bool_delete(_t1605, &(Bool){1});
                                                                                                            Bool_delete(_t1607, &(Bool){1});
                                                                                                            Bool_delete(_t1609, &(Bool){1});
                                                                                                            Bool_delete(_t1611, &(Bool){1});
                                                                                                            Bool_delete(_t1613, &(Bool){1});
                                                                                                            Bool_delete(_t1615, &(Bool){1});
                                                                                                            Bool_delete(_t1617, &(Bool){1});
                                                                                                            Bool_delete(_t1619, &(Bool){1});
                                                                                                            Bool_delete(_t1621, &(Bool){1});
                                                                                                            Bool_delete(_t1623, &(Bool){1});
                                                                                                            Bool_delete(_t1625, &(Bool){1});
                                                                                                            Bool_delete(_t1627, &(Bool){1});
                                                                                                            Bool_delete(_t1629, &(Bool){1});
                                                                                                            Bool_delete(_t1631, &(Bool){1});
                                                                                                            Bool_delete(_t1633, &(Bool){1});
                                                                                                            Bool_delete(_t1635, &(Bool){1});
                                                                                                            Bool_delete(_t1637, &(Bool){1});
                                                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                                                            Bool_delete(_t1639, &(Bool){1});
                                                                                                            return TokenType_KwDefault();
                                                                                                        } else {
                                                                                                            Str *_t1588 = Str_lit("return", 6ULL);
                                                                                                            Bool *_t1589 = Str_eq(_sw1573, _t1588);
                                                                                                            Str_delete(_t1588, &(Bool){1});
                                                                                                            if (DEREF(_t1589)) {
                                                                                                                Bool_delete(_t1589, &(Bool){1});
                                                                                                                Bool_delete(_t1591, &(Bool){1});
                                                                                                                Bool_delete(_t1593, &(Bool){1});
                                                                                                                Bool_delete(_t1595, &(Bool){1});
                                                                                                                Bool_delete(_t1597, &(Bool){1});
                                                                                                                Bool_delete(_t1599, &(Bool){1});
                                                                                                                Bool_delete(_t1601, &(Bool){1});
                                                                                                                Bool_delete(_t1603, &(Bool){1});
                                                                                                                Bool_delete(_t1605, &(Bool){1});
                                                                                                                Bool_delete(_t1607, &(Bool){1});
                                                                                                                Bool_delete(_t1609, &(Bool){1});
                                                                                                                Bool_delete(_t1611, &(Bool){1});
                                                                                                                Bool_delete(_t1613, &(Bool){1});
                                                                                                                Bool_delete(_t1615, &(Bool){1});
                                                                                                                Bool_delete(_t1617, &(Bool){1});
                                                                                                                Bool_delete(_t1619, &(Bool){1});
                                                                                                                Bool_delete(_t1621, &(Bool){1});
                                                                                                                Bool_delete(_t1623, &(Bool){1});
                                                                                                                Bool_delete(_t1625, &(Bool){1});
                                                                                                                Bool_delete(_t1627, &(Bool){1});
                                                                                                                Bool_delete(_t1629, &(Bool){1});
                                                                                                                Bool_delete(_t1631, &(Bool){1});
                                                                                                                Bool_delete(_t1633, &(Bool){1});
                                                                                                                Bool_delete(_t1635, &(Bool){1});
                                                                                                                Bool_delete(_t1637, &(Bool){1});
                                                                                                                Str_delete(_sw1573, &(Bool){1});
                                                                                                                Bool_delete(_t1639, &(Bool){1});
                                                                                                                return TokenType_KwReturn();
                                                                                                            } else {
                                                                                                                Str *_t1586 = Str_lit("throw", 5ULL);
                                                                                                                Bool *_t1587 = Str_eq(_sw1573, _t1586);
                                                                                                                Str_delete(_t1586, &(Bool){1});
                                                                                                                if (DEREF(_t1587)) {
                                                                                                                    Bool_delete(_t1587, &(Bool){1});
                                                                                                                    Bool_delete(_t1589, &(Bool){1});
                                                                                                                    Bool_delete(_t1591, &(Bool){1});
                                                                                                                    Bool_delete(_t1593, &(Bool){1});
                                                                                                                    Bool_delete(_t1595, &(Bool){1});
                                                                                                                    Bool_delete(_t1597, &(Bool){1});
                                                                                                                    Bool_delete(_t1599, &(Bool){1});
                                                                                                                    Bool_delete(_t1601, &(Bool){1});
                                                                                                                    Bool_delete(_t1603, &(Bool){1});
                                                                                                                    Bool_delete(_t1605, &(Bool){1});
                                                                                                                    Bool_delete(_t1607, &(Bool){1});
                                                                                                                    Bool_delete(_t1609, &(Bool){1});
                                                                                                                    Bool_delete(_t1611, &(Bool){1});
                                                                                                                    Bool_delete(_t1613, &(Bool){1});
                                                                                                                    Bool_delete(_t1615, &(Bool){1});
                                                                                                                    Bool_delete(_t1617, &(Bool){1});
                                                                                                                    Bool_delete(_t1619, &(Bool){1});
                                                                                                                    Bool_delete(_t1621, &(Bool){1});
                                                                                                                    Bool_delete(_t1623, &(Bool){1});
                                                                                                                    Bool_delete(_t1625, &(Bool){1});
                                                                                                                    Bool_delete(_t1627, &(Bool){1});
                                                                                                                    Bool_delete(_t1629, &(Bool){1});
                                                                                                                    Bool_delete(_t1631, &(Bool){1});
                                                                                                                    Bool_delete(_t1633, &(Bool){1});
                                                                                                                    Bool_delete(_t1635, &(Bool){1});
                                                                                                                    Bool_delete(_t1637, &(Bool){1});
                                                                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                                                                    Bool_delete(_t1639, &(Bool){1});
                                                                                                                    return TokenType_KwThrow();
                                                                                                                } else {
                                                                                                                    Str *_t1584 = Str_lit("catch", 5ULL);
                                                                                                                    Bool *_t1585 = Str_eq(_sw1573, _t1584);
                                                                                                                    Str_delete(_t1584, &(Bool){1});
                                                                                                                    if (DEREF(_t1585)) {
                                                                                                                        Bool_delete(_t1585, &(Bool){1});
                                                                                                                        Bool_delete(_t1587, &(Bool){1});
                                                                                                                        Bool_delete(_t1589, &(Bool){1});
                                                                                                                        Bool_delete(_t1591, &(Bool){1});
                                                                                                                        Bool_delete(_t1593, &(Bool){1});
                                                                                                                        Bool_delete(_t1595, &(Bool){1});
                                                                                                                        Bool_delete(_t1597, &(Bool){1});
                                                                                                                        Bool_delete(_t1599, &(Bool){1});
                                                                                                                        Bool_delete(_t1601, &(Bool){1});
                                                                                                                        Bool_delete(_t1603, &(Bool){1});
                                                                                                                        Bool_delete(_t1605, &(Bool){1});
                                                                                                                        Bool_delete(_t1607, &(Bool){1});
                                                                                                                        Bool_delete(_t1609, &(Bool){1});
                                                                                                                        Bool_delete(_t1611, &(Bool){1});
                                                                                                                        Bool_delete(_t1613, &(Bool){1});
                                                                                                                        Bool_delete(_t1615, &(Bool){1});
                                                                                                                        Bool_delete(_t1617, &(Bool){1});
                                                                                                                        Bool_delete(_t1619, &(Bool){1});
                                                                                                                        Bool_delete(_t1621, &(Bool){1});
                                                                                                                        Bool_delete(_t1623, &(Bool){1});
                                                                                                                        Bool_delete(_t1625, &(Bool){1});
                                                                                                                        Bool_delete(_t1627, &(Bool){1});
                                                                                                                        Bool_delete(_t1629, &(Bool){1});
                                                                                                                        Bool_delete(_t1631, &(Bool){1});
                                                                                                                        Bool_delete(_t1633, &(Bool){1});
                                                                                                                        Bool_delete(_t1635, &(Bool){1});
                                                                                                                        Bool_delete(_t1637, &(Bool){1});
                                                                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                                                                        Bool_delete(_t1639, &(Bool){1});
                                                                                                                        return TokenType_KwCatch();
                                                                                                                    } else {
                                                                                                                        Str *_t1582 = Str_lit("break", 5ULL);
                                                                                                                        Bool *_t1583 = Str_eq(_sw1573, _t1582);
                                                                                                                        Str_delete(_t1582, &(Bool){1});
                                                                                                                        if (DEREF(_t1583)) {
                                                                                                                            Bool_delete(_t1583, &(Bool){1});
                                                                                                                            Bool_delete(_t1585, &(Bool){1});
                                                                                                                            Bool_delete(_t1587, &(Bool){1});
                                                                                                                            Bool_delete(_t1589, &(Bool){1});
                                                                                                                            Bool_delete(_t1591, &(Bool){1});
                                                                                                                            Bool_delete(_t1593, &(Bool){1});
                                                                                                                            Bool_delete(_t1595, &(Bool){1});
                                                                                                                            Bool_delete(_t1597, &(Bool){1});
                                                                                                                            Bool_delete(_t1599, &(Bool){1});
                                                                                                                            Bool_delete(_t1601, &(Bool){1});
                                                                                                                            Bool_delete(_t1603, &(Bool){1});
                                                                                                                            Bool_delete(_t1605, &(Bool){1});
                                                                                                                            Bool_delete(_t1607, &(Bool){1});
                                                                                                                            Bool_delete(_t1609, &(Bool){1});
                                                                                                                            Bool_delete(_t1611, &(Bool){1});
                                                                                                                            Bool_delete(_t1613, &(Bool){1});
                                                                                                                            Bool_delete(_t1615, &(Bool){1});
                                                                                                                            Bool_delete(_t1617, &(Bool){1});
                                                                                                                            Bool_delete(_t1619, &(Bool){1});
                                                                                                                            Bool_delete(_t1621, &(Bool){1});
                                                                                                                            Bool_delete(_t1623, &(Bool){1});
                                                                                                                            Bool_delete(_t1625, &(Bool){1});
                                                                                                                            Bool_delete(_t1627, &(Bool){1});
                                                                                                                            Bool_delete(_t1629, &(Bool){1});
                                                                                                                            Bool_delete(_t1631, &(Bool){1});
                                                                                                                            Bool_delete(_t1633, &(Bool){1});
                                                                                                                            Bool_delete(_t1635, &(Bool){1});
                                                                                                                            Bool_delete(_t1637, &(Bool){1});
                                                                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                                                                            Bool_delete(_t1639, &(Bool){1});
                                                                                                                            return TokenType_KwBreak();
                                                                                                                        } else {
                                                                                                                            Str *_t1580 = Str_lit("continue", 8ULL);
                                                                                                                            Bool *_t1581 = Str_eq(_sw1573, _t1580);
                                                                                                                            Str_delete(_t1580, &(Bool){1});
                                                                                                                            if (DEREF(_t1581)) {
                                                                                                                                Bool_delete(_t1581, &(Bool){1});
                                                                                                                                Bool_delete(_t1583, &(Bool){1});
                                                                                                                                Bool_delete(_t1585, &(Bool){1});
                                                                                                                                Bool_delete(_t1587, &(Bool){1});
                                                                                                                                Bool_delete(_t1589, &(Bool){1});
                                                                                                                                Bool_delete(_t1591, &(Bool){1});
                                                                                                                                Bool_delete(_t1593, &(Bool){1});
                                                                                                                                Bool_delete(_t1595, &(Bool){1});
                                                                                                                                Bool_delete(_t1597, &(Bool){1});
                                                                                                                                Bool_delete(_t1599, &(Bool){1});
                                                                                                                                Bool_delete(_t1601, &(Bool){1});
                                                                                                                                Bool_delete(_t1603, &(Bool){1});
                                                                                                                                Bool_delete(_t1605, &(Bool){1});
                                                                                                                                Bool_delete(_t1607, &(Bool){1});
                                                                                                                                Bool_delete(_t1609, &(Bool){1});
                                                                                                                                Bool_delete(_t1611, &(Bool){1});
                                                                                                                                Bool_delete(_t1613, &(Bool){1});
                                                                                                                                Bool_delete(_t1615, &(Bool){1});
                                                                                                                                Bool_delete(_t1617, &(Bool){1});
                                                                                                                                Bool_delete(_t1619, &(Bool){1});
                                                                                                                                Bool_delete(_t1621, &(Bool){1});
                                                                                                                                Bool_delete(_t1623, &(Bool){1});
                                                                                                                                Bool_delete(_t1625, &(Bool){1});
                                                                                                                                Bool_delete(_t1627, &(Bool){1});
                                                                                                                                Bool_delete(_t1629, &(Bool){1});
                                                                                                                                Bool_delete(_t1631, &(Bool){1});
                                                                                                                                Bool_delete(_t1633, &(Bool){1});
                                                                                                                                Bool_delete(_t1635, &(Bool){1});
                                                                                                                                Bool_delete(_t1637, &(Bool){1});
                                                                                                                                Str_delete(_sw1573, &(Bool){1});
                                                                                                                                Bool_delete(_t1639, &(Bool){1});
                                                                                                                                return TokenType_KwContinue();
                                                                                                                            } else {
                                                                                                                                Str *_t1578 = Str_lit("defer", 5ULL);
                                                                                                                                Bool *_t1579 = Str_eq(_sw1573, _t1578);
                                                                                                                                Str_delete(_t1578, &(Bool){1});
                                                                                                                                if (DEREF(_t1579)) {
                                                                                                                                    Bool_delete(_t1579, &(Bool){1});
                                                                                                                                    Bool_delete(_t1581, &(Bool){1});
                                                                                                                                    Bool_delete(_t1583, &(Bool){1});
                                                                                                                                    Bool_delete(_t1585, &(Bool){1});
                                                                                                                                    Bool_delete(_t1587, &(Bool){1});
                                                                                                                                    Bool_delete(_t1589, &(Bool){1});
                                                                                                                                    Bool_delete(_t1591, &(Bool){1});
                                                                                                                                    Bool_delete(_t1593, &(Bool){1});
                                                                                                                                    Bool_delete(_t1595, &(Bool){1});
                                                                                                                                    Bool_delete(_t1597, &(Bool){1});
                                                                                                                                    Bool_delete(_t1599, &(Bool){1});
                                                                                                                                    Bool_delete(_t1601, &(Bool){1});
                                                                                                                                    Bool_delete(_t1603, &(Bool){1});
                                                                                                                                    Bool_delete(_t1605, &(Bool){1});
                                                                                                                                    Bool_delete(_t1607, &(Bool){1});
                                                                                                                                    Bool_delete(_t1609, &(Bool){1});
                                                                                                                                    Bool_delete(_t1611, &(Bool){1});
                                                                                                                                    Bool_delete(_t1613, &(Bool){1});
                                                                                                                                    Bool_delete(_t1615, &(Bool){1});
                                                                                                                                    Bool_delete(_t1617, &(Bool){1});
                                                                                                                                    Bool_delete(_t1619, &(Bool){1});
                                                                                                                                    Bool_delete(_t1621, &(Bool){1});
                                                                                                                                    Bool_delete(_t1623, &(Bool){1});
                                                                                                                                    Bool_delete(_t1625, &(Bool){1});
                                                                                                                                    Bool_delete(_t1627, &(Bool){1});
                                                                                                                                    Bool_delete(_t1629, &(Bool){1});
                                                                                                                                    Bool_delete(_t1631, &(Bool){1});
                                                                                                                                    Bool_delete(_t1633, &(Bool){1});
                                                                                                                                    Bool_delete(_t1635, &(Bool){1});
                                                                                                                                    Bool_delete(_t1637, &(Bool){1});
                                                                                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                                                                                    Bool_delete(_t1639, &(Bool){1});
                                                                                                                                    return TokenType_KwDefer();
                                                                                                                                } else {
                                                                                                                                    Str *_t1576 = Str_lit("true", 4ULL);
                                                                                                                                    Bool *_t1577 = Str_eq(_sw1573, _t1576);
                                                                                                                                    Str_delete(_t1576, &(Bool){1});
                                                                                                                                    if (DEREF(_t1577)) {
                                                                                                                                        Bool_delete(_t1577, &(Bool){1});
                                                                                                                                        Bool_delete(_t1579, &(Bool){1});
                                                                                                                                        Bool_delete(_t1581, &(Bool){1});
                                                                                                                                        Bool_delete(_t1583, &(Bool){1});
                                                                                                                                        Bool_delete(_t1585, &(Bool){1});
                                                                                                                                        Bool_delete(_t1587, &(Bool){1});
                                                                                                                                        Bool_delete(_t1589, &(Bool){1});
                                                                                                                                        Bool_delete(_t1591, &(Bool){1});
                                                                                                                                        Bool_delete(_t1593, &(Bool){1});
                                                                                                                                        Bool_delete(_t1595, &(Bool){1});
                                                                                                                                        Bool_delete(_t1597, &(Bool){1});
                                                                                                                                        Bool_delete(_t1599, &(Bool){1});
                                                                                                                                        Bool_delete(_t1601, &(Bool){1});
                                                                                                                                        Bool_delete(_t1603, &(Bool){1});
                                                                                                                                        Bool_delete(_t1605, &(Bool){1});
                                                                                                                                        Bool_delete(_t1607, &(Bool){1});
                                                                                                                                        Bool_delete(_t1609, &(Bool){1});
                                                                                                                                        Bool_delete(_t1611, &(Bool){1});
                                                                                                                                        Bool_delete(_t1613, &(Bool){1});
                                                                                                                                        Bool_delete(_t1615, &(Bool){1});
                                                                                                                                        Bool_delete(_t1617, &(Bool){1});
                                                                                                                                        Bool_delete(_t1619, &(Bool){1});
                                                                                                                                        Bool_delete(_t1621, &(Bool){1});
                                                                                                                                        Bool_delete(_t1623, &(Bool){1});
                                                                                                                                        Bool_delete(_t1625, &(Bool){1});
                                                                                                                                        Bool_delete(_t1627, &(Bool){1});
                                                                                                                                        Bool_delete(_t1629, &(Bool){1});
                                                                                                                                        Bool_delete(_t1631, &(Bool){1});
                                                                                                                                        Bool_delete(_t1633, &(Bool){1});
                                                                                                                                        Bool_delete(_t1635, &(Bool){1});
                                                                                                                                        Bool_delete(_t1637, &(Bool){1});
                                                                                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                                                                                        Bool_delete(_t1639, &(Bool){1});
                                                                                                                                        return TokenType_KwTrue();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1574 = Str_lit("false", 5ULL);
                                                                                                                                        Bool *_t1575 = Str_eq(_sw1573, _t1574);
                                                                                                                                        Str_delete(_t1574, &(Bool){1});
                                                                                                                                        if (DEREF(_t1575)) {
                                                                                                                                            Bool_delete(_t1575, &(Bool){1});
                                                                                                                                            Bool_delete(_t1577, &(Bool){1});
                                                                                                                                            Bool_delete(_t1579, &(Bool){1});
                                                                                                                                            Bool_delete(_t1581, &(Bool){1});
                                                                                                                                            Bool_delete(_t1583, &(Bool){1});
                                                                                                                                            Bool_delete(_t1585, &(Bool){1});
                                                                                                                                            Bool_delete(_t1587, &(Bool){1});
                                                                                                                                            Bool_delete(_t1589, &(Bool){1});
                                                                                                                                            Bool_delete(_t1591, &(Bool){1});
                                                                                                                                            Bool_delete(_t1593, &(Bool){1});
                                                                                                                                            Bool_delete(_t1595, &(Bool){1});
                                                                                                                                            Bool_delete(_t1597, &(Bool){1});
                                                                                                                                            Bool_delete(_t1599, &(Bool){1});
                                                                                                                                            Bool_delete(_t1601, &(Bool){1});
                                                                                                                                            Bool_delete(_t1603, &(Bool){1});
                                                                                                                                            Bool_delete(_t1605, &(Bool){1});
                                                                                                                                            Bool_delete(_t1607, &(Bool){1});
                                                                                                                                            Bool_delete(_t1609, &(Bool){1});
                                                                                                                                            Bool_delete(_t1611, &(Bool){1});
                                                                                                                                            Bool_delete(_t1613, &(Bool){1});
                                                                                                                                            Bool_delete(_t1615, &(Bool){1});
                                                                                                                                            Bool_delete(_t1617, &(Bool){1});
                                                                                                                                            Bool_delete(_t1619, &(Bool){1});
                                                                                                                                            Bool_delete(_t1621, &(Bool){1});
                                                                                                                                            Bool_delete(_t1623, &(Bool){1});
                                                                                                                                            Bool_delete(_t1625, &(Bool){1});
                                                                                                                                            Bool_delete(_t1627, &(Bool){1});
                                                                                                                                            Bool_delete(_t1629, &(Bool){1});
                                                                                                                                            Bool_delete(_t1631, &(Bool){1});
                                                                                                                                            Bool_delete(_t1633, &(Bool){1});
                                                                                                                                            Bool_delete(_t1635, &(Bool){1});
                                                                                                                                            Bool_delete(_t1637, &(Bool){1});
                                                                                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                                                                                            Bool_delete(_t1639, &(Bool){1});
                                                                                                                                            return TokenType_KwFalse();
                                                                                                                                        } else {
                                                                                                                                            Bool_delete(_t1575, &(Bool){1});
                                                                                                                                            Bool_delete(_t1577, &(Bool){1});
                                                                                                                                            Bool_delete(_t1579, &(Bool){1});
                                                                                                                                            Bool_delete(_t1581, &(Bool){1});
                                                                                                                                            Bool_delete(_t1583, &(Bool){1});
                                                                                                                                            Bool_delete(_t1585, &(Bool){1});
                                                                                                                                            Bool_delete(_t1587, &(Bool){1});
                                                                                                                                            Bool_delete(_t1589, &(Bool){1});
                                                                                                                                            Bool_delete(_t1591, &(Bool){1});
                                                                                                                                            Bool_delete(_t1593, &(Bool){1});
                                                                                                                                            Bool_delete(_t1595, &(Bool){1});
                                                                                                                                            Bool_delete(_t1597, &(Bool){1});
                                                                                                                                            Bool_delete(_t1599, &(Bool){1});
                                                                                                                                            Bool_delete(_t1601, &(Bool){1});
                                                                                                                                            Bool_delete(_t1603, &(Bool){1});
                                                                                                                                            Bool_delete(_t1605, &(Bool){1});
                                                                                                                                            Bool_delete(_t1607, &(Bool){1});
                                                                                                                                            Bool_delete(_t1609, &(Bool){1});
                                                                                                                                            Bool_delete(_t1611, &(Bool){1});
                                                                                                                                            Bool_delete(_t1613, &(Bool){1});
                                                                                                                                            Bool_delete(_t1615, &(Bool){1});
                                                                                                                                            Bool_delete(_t1617, &(Bool){1});
                                                                                                                                            Bool_delete(_t1619, &(Bool){1});
                                                                                                                                            Bool_delete(_t1621, &(Bool){1});
                                                                                                                                            Bool_delete(_t1623, &(Bool){1});
                                                                                                                                            Bool_delete(_t1625, &(Bool){1});
                                                                                                                                            Bool_delete(_t1627, &(Bool){1});
                                                                                                                                            Bool_delete(_t1629, &(Bool){1});
                                                                                                                                            Bool_delete(_t1631, &(Bool){1});
                                                                                                                                            Bool_delete(_t1633, &(Bool){1});
                                                                                                                                            Bool_delete(_t1635, &(Bool){1});
                                                                                                                                            Bool_delete(_t1637, &(Bool){1});
                                                                                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                                                                                            Bool_delete(_t1639, &(Bool){1});
                                                                                                                                            return TokenType_Ident();
                                                                                                                                        }
                                                                                                                                        Bool_delete(_t1575, &(Bool){1});
                                                                                                                                    }
                                                                                                                                    Bool_delete(_t1577, &(Bool){1});
                                                                                                                                }
                                                                                                                                Bool_delete(_t1579, &(Bool){1});
                                                                                                                            }
                                                                                                                            Bool_delete(_t1581, &(Bool){1});
                                                                                                                        }
                                                                                                                        Bool_delete(_t1583, &(Bool){1});
                                                                                                                    }
                                                                                                                    Bool_delete(_t1585, &(Bool){1});
                                                                                                                }
                                                                                                                Bool_delete(_t1587, &(Bool){1});
                                                                                                            }
                                                                                                            Bool_delete(_t1589, &(Bool){1});
                                                                                                        }
                                                                                                        Bool_delete(_t1591, &(Bool){1});
                                                                                                    }
                                                                                                    Bool_delete(_t1593, &(Bool){1});
                                                                                                }
                                                                                                Bool_delete(_t1595, &(Bool){1});
                                                                                            }
                                                                                            Bool_delete(_t1597, &(Bool){1});
                                                                                        }
                                                                                        Bool_delete(_t1599, &(Bool){1});
                                                                                    }
                                                                                    Bool_delete(_t1601, &(Bool){1});
                                                                                }
                                                                                Bool_delete(_t1603, &(Bool){1});
                                                                            }
                                                                            Bool_delete(_t1605, &(Bool){1});
                                                                        }
                                                                        Bool_delete(_t1607, &(Bool){1});
                                                                    }
                                                                    Bool_delete(_t1609, &(Bool){1});
                                                                }
                                                                Bool_delete(_t1611, &(Bool){1});
                                                            }
                                                            Bool_delete(_t1613, &(Bool){1});
                                                        }
                                                        Bool_delete(_t1615, &(Bool){1});
                                                    }
                                                    Bool_delete(_t1617, &(Bool){1});
                                                }
                                                Bool_delete(_t1619, &(Bool){1});
                                            }
                                            Bool_delete(_t1621, &(Bool){1});
                                        }
                                        Bool_delete(_t1623, &(Bool){1});
                                    }
                                    Bool_delete(_t1625, &(Bool){1});
                                }
                                Bool_delete(_t1627, &(Bool){1});
                            }
                            Bool_delete(_t1629, &(Bool){1});
                        }
                        Bool_delete(_t1631, &(Bool){1});
                    }
                    Bool_delete(_t1633, &(Bool){1});
                }
                Bool_delete(_t1635, &(Bool){1});
            }
            Bool_delete(_t1637, &(Bool){1});
        }
        Str_delete(_sw1573, &(Bool){1});
        Bool_delete(_t1639, &(Bool){1});
    }
}

Vec * tokenize(Str * source, Str * path) {
    Str *_t1995 = Str_lit("Token", 5ULL);
    U64 *_t1996 = Token_size();
    Vec *tokens = Vec_new(_t1995, _t1996);
    Str_delete(_t1995, &(Bool){1});
    U64_delete(_t1996, &(Bool){1});
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    I64 *line = malloc(sizeof(I64));
    *line = 1;
    U64 *line_start = malloc(sizeof(U64));
    *line_start = 0;
    U64 *src_len = Str_len(source);
    while (1) {
        Bool *_wcond1640 = U64_lt(pos, src_len);
        if (DEREF(_wcond1640)) {
        } else {
            Bool_delete(_wcond1640, &(Bool){1});
            break;
        }
        Bool_delete(_wcond1640, &(Bool){1});
        U8 *c = Str_get(source, pos);
        U8 *_t1940 = malloc(sizeof(U8));
        *_t1940 = 32;
        U8 *_t1941 = malloc(sizeof(U8));
        *_t1941 = 9;
        Bool *_t1942 = malloc(sizeof(Bool)); *_t1942 = U8_eq(DEREF(c), DEREF(_t1940));
        U8_delete(_t1940, &(Bool){1});
        Bool *_t1943 = malloc(sizeof(Bool)); *_t1943 = U8_eq(DEREF(c), DEREF(_t1941));
        U8_delete(_t1941, &(Bool){1});
        U8 *_t1944 = malloc(sizeof(U8));
        *_t1944 = 13;
        Bool *_t1945 = malloc(sizeof(Bool)); *_t1945 = Bool_or(DEREF(_t1942), DEREF(_t1943));
        Bool_delete(_t1942, &(Bool){1});
        Bool_delete(_t1943, &(Bool){1});
        Bool *_t1946 = malloc(sizeof(Bool)); *_t1946 = U8_eq(DEREF(c), DEREF(_t1944));
        U8_delete(_t1944, &(Bool){1});
        U8 *_t1947 = malloc(sizeof(U8));
        *_t1947 = 59;
        Bool *_t1948 = malloc(sizeof(Bool)); *_t1948 = Bool_or(DEREF(_t1945), DEREF(_t1946));
        Bool_delete(_t1945, &(Bool){1});
        Bool_delete(_t1946, &(Bool){1});
        Bool *_t1949 = malloc(sizeof(Bool)); *_t1949 = U8_eq(DEREF(c), DEREF(_t1947));
        U8_delete(_t1947, &(Bool){1});
        Bool *_t1950 = malloc(sizeof(Bool)); *_t1950 = Bool_or(DEREF(_t1948), DEREF(_t1949));
        Bool_delete(_t1948, &(Bool){1});
        Bool_delete(_t1949, &(Bool){1});
        if (DEREF(_t1950)) {
            U64 *_t1641 = malloc(sizeof(U64));
            *_t1641 = 1;
            U64 *_t1642 = malloc(sizeof(U64)); *_t1642 = U64_add(DEREF(pos), DEREF(_t1641));
            U64_delete(_t1641, &(Bool){1});
            *pos = DEREF(_t1642);
            U64_delete(_t1642, &(Bool){1});
            Bool_delete(_t1950, &(Bool){1});
            continue;
        }
        Bool_delete(_t1950, &(Bool){1});
        U8 *_t1951 = malloc(sizeof(U8));
        *_t1951 = 10;
        Bool *_t1952 = malloc(sizeof(Bool)); *_t1952 = U8_eq(DEREF(c), DEREF(_t1951));
        U8_delete(_t1951, &(Bool){1});
        if (DEREF(_t1952)) {
            U64 *_t1643 = malloc(sizeof(U64));
            *_t1643 = 1;
            U64 *_t1644 = malloc(sizeof(U64)); *_t1644 = U64_add(DEREF(pos), DEREF(_t1643));
            U64_delete(_t1643, &(Bool){1});
            *pos = DEREF(_t1644);
            U64_delete(_t1644, &(Bool){1});
            I64 *_t1645 = malloc(sizeof(I64));
            *_t1645 = 1;
            I64 *_t1646 = malloc(sizeof(I64)); *_t1646 = I64_add(DEREF(line), DEREF(_t1645));
            I64_delete(_t1645, &(Bool){1});
            *line = DEREF(_t1646);
            I64_delete(_t1646, &(Bool){1});
            U64 *_t1647 = U64_clone(pos);
            *line_start = DEREF(_t1647);
            U64_delete(_t1647, &(Bool){1});
            Bool_delete(_t1952, &(Bool){1});
            continue;
        }
        Bool_delete(_t1952, &(Bool){1});
        U64 *_t1953 = malloc(sizeof(U64)); *_t1953 = U64_sub(DEREF(pos), DEREF(line_start));
        U64 *_t1954 = malloc(sizeof(U64));
        *_t1954 = 1;
        U64 *_t1955 = malloc(sizeof(U64)); *_t1955 = U64_add(DEREF(_t1953), DEREF(_t1954));
        U64_delete(_t1953, &(Bool){1});
        U64_delete(_t1954, &(Bool){1});
        I64 *col = malloc(sizeof(I64)); *col = U64_to_i64(DEREF(_t1955));
        U64_delete(_t1955, &(Bool){1});
        U64 *start = U64_clone(pos);
        U8 *_t1956 = malloc(sizeof(U8));
        *_t1956 = 35;
        Bool *_t1957 = malloc(sizeof(Bool)); *_t1957 = U8_eq(DEREF(c), DEREF(_t1956));
        U8_delete(_t1956, &(Bool){1});
        if (DEREF(_t1957)) {
            while (1) {
                Bool *_wcond1648 = U64_lt(pos, src_len);
                if (DEREF(_wcond1648)) {
                } else {
                    Bool_delete(_wcond1648, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond1648, &(Bool){1});
                U8 *_t1649 = Str_get(source, pos);
                U8 *_t1650 = malloc(sizeof(U8));
                *_t1650 = 10;
                Bool *_t1651 = malloc(sizeof(Bool)); *_t1651 = U8_eq(DEREF(_t1649), DEREF(_t1650));
                U8_delete(_t1650, &(Bool){1});
                if (DEREF(_t1651)) {
                    Bool_delete(_t1651, &(Bool){1});
                    break;
                }
                Bool_delete(_t1651, &(Bool){1});
                U64 *_t1652 = malloc(sizeof(U64));
                *_t1652 = 1;
                U64 *_t1653 = malloc(sizeof(U64)); *_t1653 = U64_add(DEREF(pos), DEREF(_t1652));
                U64_delete(_t1652, &(Bool){1});
                *pos = DEREF(_t1653);
                U64_delete(_t1653, &(Bool){1});
            }
            Bool_delete(_t1957, &(Bool){1});
            I64_delete(col, &(Bool){1});
            U64_delete(start, &(Bool){1});
            continue;
        }
        Bool_delete(_t1957, &(Bool){1});
        U8 *_t1958 = malloc(sizeof(U8));
        *_t1958 = 47;
        U64 *_t1959 = malloc(sizeof(U64));
        *_t1959 = 1;
        U64 *_t1960 = malloc(sizeof(U64)); *_t1960 = U64_add(DEREF(pos), DEREF(_t1959));
        U64_delete(_t1959, &(Bool){1});
        Bool *_t1961 = malloc(sizeof(Bool)); *_t1961 = U8_eq(DEREF(c), DEREF(_t1958));
        U8_delete(_t1958, &(Bool){1});
        Bool *_t1962 = U64_lt(_t1960, src_len);
        U64_delete(_t1960, &(Bool){1});
        Bool *_t1963 = malloc(sizeof(Bool)); *_t1963 = Bool_and(DEREF(_t1961), DEREF(_t1962));
        Bool_delete(_t1961, &(Bool){1});
        Bool_delete(_t1962, &(Bool){1});
        if (DEREF(_t1963)) {
            U64 *_t1714 = malloc(sizeof(U64));
            *_t1714 = 1;
            U64 *_t1715 = malloc(sizeof(U64)); *_t1715 = U64_add(DEREF(pos), DEREF(_t1714));
            U64_delete(_t1714, &(Bool){1});
            U8 *c2 = Str_get(source, _t1715);
            U8 *_t1716 = malloc(sizeof(U8));
            *_t1716 = 47;
            Bool *_t1717 = malloc(sizeof(Bool)); *_t1717 = U8_eq(DEREF(c2), DEREF(_t1716));
            U8_delete(_t1716, &(Bool){1});
            if (DEREF(_t1717)) {
                while (1) {
                    Bool *_wcond1654 = U64_lt(pos, src_len);
                    if (DEREF(_wcond1654)) {
                    } else {
                        Bool_delete(_wcond1654, &(Bool){1});
                        break;
                    }
                    Bool_delete(_wcond1654, &(Bool){1});
                    U8 *_t1655 = Str_get(source, pos);
                    U8 *_t1656 = malloc(sizeof(U8));
                    *_t1656 = 10;
                    Bool *_t1657 = malloc(sizeof(Bool)); *_t1657 = U8_eq(DEREF(_t1655), DEREF(_t1656));
                    U8_delete(_t1656, &(Bool){1});
                    if (DEREF(_t1657)) {
                        Bool_delete(_t1657, &(Bool){1});
                        break;
                    }
                    Bool_delete(_t1657, &(Bool){1});
                    U64 *_t1658 = malloc(sizeof(U64));
                    *_t1658 = 1;
                    U64 *_t1659 = malloc(sizeof(U64)); *_t1659 = U64_add(DEREF(pos), DEREF(_t1658));
                    U64_delete(_t1658, &(Bool){1});
                    *pos = DEREF(_t1659);
                    U64_delete(_t1659, &(Bool){1});
                }
                U64_delete(_t1715, &(Bool){1});
                Bool_delete(_t1717, &(Bool){1});
                Bool_delete(_t1963, &(Bool){1});
                I64_delete(col, &(Bool){1});
                U64_delete(start, &(Bool){1});
                continue;
            }
            Bool_delete(_t1717, &(Bool){1});
            U8 *_t1718 = malloc(sizeof(U8));
            *_t1718 = 42;
            Bool *_t1719 = malloc(sizeof(Bool)); *_t1719 = U8_eq(DEREF(c2), DEREF(_t1718));
            U64_delete(_t1715, &(Bool){1});
            U8_delete(_t1718, &(Bool){1});
            if (DEREF(_t1719)) {
                U64 *_t1710 = malloc(sizeof(U64));
                *_t1710 = 2;
                U64 *_t1711 = malloc(sizeof(U64)); *_t1711 = U64_add(DEREF(pos), DEREF(_t1710));
                U64_delete(_t1710, &(Bool){1});
                *pos = DEREF(_t1711);
                U64_delete(_t1711, &(Bool){1});
                I64 *depth = malloc(sizeof(I64));
                *depth = 1;
                while (1) {
                    Bool *_wcond1660 = U64_lt(pos, src_len);
                    if (DEREF(_wcond1660)) {
                    } else {
                        Bool_delete(_wcond1660, &(Bool){1});
                        break;
                    }
                    Bool_delete(_wcond1660, &(Bool){1});
                    I64 *_t1685 = malloc(sizeof(I64));
                    *_t1685 = 0;
                    Bool *_t1686 = I64_lte(depth, _t1685);
                    I64_delete(_t1685, &(Bool){1});
                    if (DEREF(_t1686)) {
                        Bool_delete(_t1686, &(Bool){1});
                        break;
                    }
                    Bool_delete(_t1686, &(Bool){1});
                    U64 *_t1687 = malloc(sizeof(U64));
                    *_t1687 = 1;
                    U64 *_t1688 = malloc(sizeof(U64)); *_t1688 = U64_add(DEREF(pos), DEREF(_t1687));
                    U64_delete(_t1687, &(Bool){1});
                    Bool *_t1689 = U64_lt(_t1688, src_len);
                    U64_delete(_t1688, &(Bool){1});
                    if (DEREF(_t1689)) {
                        U8 *b1 = Str_get(source, pos);
                        U64 *_t1669 = malloc(sizeof(U64));
                        *_t1669 = 1;
                        U64 *_t1670 = malloc(sizeof(U64)); *_t1670 = U64_add(DEREF(pos), DEREF(_t1669));
                        U64_delete(_t1669, &(Bool){1});
                        U8 *b2 = Str_get(source, _t1670);
                        U8 *_t1671 = malloc(sizeof(U8));
                        *_t1671 = 47;
                        U8 *_t1672 = malloc(sizeof(U8));
                        *_t1672 = 42;
                        Bool *_t1673 = malloc(sizeof(Bool)); *_t1673 = U8_eq(DEREF(b1), DEREF(_t1671));
                        U8_delete(_t1671, &(Bool){1});
                        Bool *_t1674 = malloc(sizeof(Bool)); *_t1674 = U8_eq(DEREF(b2), DEREF(_t1672));
                        U8_delete(_t1672, &(Bool){1});
                        Bool *_t1675 = malloc(sizeof(Bool)); *_t1675 = Bool_and(DEREF(_t1673), DEREF(_t1674));
                        Bool_delete(_t1673, &(Bool){1});
                        Bool_delete(_t1674, &(Bool){1});
                        if (DEREF(_t1675)) {
                            I64 *_t1661 = malloc(sizeof(I64));
                            *_t1661 = 1;
                            I64 *_t1662 = malloc(sizeof(I64)); *_t1662 = I64_add(DEREF(depth), DEREF(_t1661));
                            I64_delete(_t1661, &(Bool){1});
                            *depth = DEREF(_t1662);
                            I64_delete(_t1662, &(Bool){1});
                            U64 *_t1663 = malloc(sizeof(U64));
                            *_t1663 = 2;
                            U64 *_t1664 = malloc(sizeof(U64)); *_t1664 = U64_add(DEREF(pos), DEREF(_t1663));
                            U64_delete(_t1663, &(Bool){1});
                            *pos = DEREF(_t1664);
                            U64_delete(_t1664, &(Bool){1});
                            U64_delete(_t1670, &(Bool){1});
                            Bool_delete(_t1675, &(Bool){1});
                            Bool_delete(_t1689, &(Bool){1});
                            continue;
                        }
                        Bool_delete(_t1675, &(Bool){1});
                        U8 *_t1676 = malloc(sizeof(U8));
                        *_t1676 = 42;
                        U8 *_t1677 = malloc(sizeof(U8));
                        *_t1677 = 47;
                        Bool *_t1678 = malloc(sizeof(Bool)); *_t1678 = U8_eq(DEREF(b1), DEREF(_t1676));
                        U8_delete(_t1676, &(Bool){1});
                        Bool *_t1679 = malloc(sizeof(Bool)); *_t1679 = U8_eq(DEREF(b2), DEREF(_t1677));
                        U64_delete(_t1670, &(Bool){1});
                        U8_delete(_t1677, &(Bool){1});
                        Bool *_t1680 = malloc(sizeof(Bool)); *_t1680 = Bool_and(DEREF(_t1678), DEREF(_t1679));
                        Bool_delete(_t1678, &(Bool){1});
                        Bool_delete(_t1679, &(Bool){1});
                        if (DEREF(_t1680)) {
                            I64 *_t1665 = malloc(sizeof(I64));
                            *_t1665 = 1;
                            I64 *_t1666 = malloc(sizeof(I64)); *_t1666 = I64_sub(DEREF(depth), DEREF(_t1665));
                            I64_delete(_t1665, &(Bool){1});
                            *depth = DEREF(_t1666);
                            I64_delete(_t1666, &(Bool){1});
                            U64 *_t1667 = malloc(sizeof(U64));
                            *_t1667 = 2;
                            U64 *_t1668 = malloc(sizeof(U64)); *_t1668 = U64_add(DEREF(pos), DEREF(_t1667));
                            U64_delete(_t1667, &(Bool){1});
                            *pos = DEREF(_t1668);
                            U64_delete(_t1668, &(Bool){1});
                            Bool_delete(_t1680, &(Bool){1});
                            Bool_delete(_t1689, &(Bool){1});
                            continue;
                        }
                        Bool_delete(_t1680, &(Bool){1});
                    }
                    Bool_delete(_t1689, &(Bool){1});
                    U8 *_t1690 = Str_get(source, pos);
                    U8 *_t1691 = malloc(sizeof(U8));
                    *_t1691 = 10;
                    Bool *_t1692 = malloc(sizeof(Bool)); *_t1692 = U8_eq(DEREF(_t1690), DEREF(_t1691));
                    U8_delete(_t1691, &(Bool){1});
                    if (DEREF(_t1692)) {
                        I64 *_t1681 = malloc(sizeof(I64));
                        *_t1681 = 1;
                        I64 *_t1682 = malloc(sizeof(I64)); *_t1682 = I64_add(DEREF(line), DEREF(_t1681));
                        I64_delete(_t1681, &(Bool){1});
                        *line = DEREF(_t1682);
                        I64_delete(_t1682, &(Bool){1});
                        U64 *_t1683 = malloc(sizeof(U64));
                        *_t1683 = 1;
                        U64 *_t1684 = malloc(sizeof(U64)); *_t1684 = U64_add(DEREF(pos), DEREF(_t1683));
                        U64_delete(_t1683, &(Bool){1});
                        *line_start = DEREF(_t1684);
                        U64_delete(_t1684, &(Bool){1});
                    }
                    Bool_delete(_t1692, &(Bool){1});
                    U64 *_t1693 = malloc(sizeof(U64));
                    *_t1693 = 1;
                    U64 *_t1694 = malloc(sizeof(U64)); *_t1694 = U64_add(DEREF(pos), DEREF(_t1693));
                    U64_delete(_t1693, &(Bool){1});
                    *pos = DEREF(_t1694);
                    U64_delete(_t1694, &(Bool){1});
                }
                I64 *_t1712 = malloc(sizeof(I64));
                *_t1712 = 0;
                Bool *_t1713 = I64_gt(depth, _t1712);
                I64_delete(_t1712, &(Bool){1});
                I64_delete(depth, &(Bool){1});
                if (DEREF(_t1713)) {
                    Str *_t1695 = Str_lit("Str", 3ULL);
                    U64 *_t1696 = Str_size();
                    U64 *_t1697 = malloc(sizeof(U64));
                    *_t1697 = 6;
                    Array *_va23 = Array_new(_t1695, _t1696, _t1697);
                    Str_delete(_t1695, &(Bool){1});
                    U64_delete(_t1696, &(Bool){1});
                    U64_delete(_t1697, &(Bool){1});
                    U64 *_t1698 = malloc(sizeof(U64));
                    *_t1698 = 0;
                    Str *_t1699 = Str_clone(path);
                    Array_set(_va23, _t1698, _t1699);
                    U64_delete(_t1698, &(Bool){1});
                    U64 *_t1700 = malloc(sizeof(U64));
                    *_t1700 = 1;
                    Str *_t1701 = Str_lit(":", 1ULL);
                    Array_set(_va23, _t1700, _t1701);
                    U64_delete(_t1700, &(Bool){1});
                    U64 *_t1702 = malloc(sizeof(U64));
                    *_t1702 = 2;
                    Str *_t1703 = I64_to_str(line);
                    Array_set(_va23, _t1702, _t1703);
                    U64_delete(_t1702, &(Bool){1});
                    U64 *_t1704 = malloc(sizeof(U64));
                    *_t1704 = 3;
                    Str *_t1705 = Str_lit(":", 1ULL);
                    Array_set(_va23, _t1704, _t1705);
                    U64_delete(_t1704, &(Bool){1});
                    U64 *_t1706 = malloc(sizeof(U64));
                    *_t1706 = 4;
                    Str *_t1707 = I64_to_str(col);
                    Array_set(_va23, _t1706, _t1707);
                    U64_delete(_t1706, &(Bool){1});
                    U64 *_t1708 = malloc(sizeof(U64));
                    *_t1708 = 5;
                    Str *_t1709 = Str_lit(": error: unterminated comment", 29ULL);
                    Array_set(_va23, _t1708, _t1709);
                    U64_delete(_t1708, &(Bool){1});
                    println(_va23);
                }
                Bool_delete(_t1713, &(Bool){1});
                Bool_delete(_t1719, &(Bool){1});
                Bool_delete(_t1963, &(Bool){1});
                I64_delete(col, &(Bool){1});
                U64_delete(start, &(Bool){1});
                continue;
            }
            Bool_delete(_t1719, &(Bool){1});
        }
        Bool_delete(_t1963, &(Bool){1});
        Bool *_t1964 = is_digit(c);
        if (DEREF(_t1964)) {
            while (1) {
                Bool *_wcond1720 = U64_lt(pos, src_len);
                if (DEREF(_wcond1720)) {
                } else {
                    Bool_delete(_wcond1720, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond1720, &(Bool){1});
                U8 *_t1721 = Str_get(source, pos);
                Bool *_t1722 = is_digit(_t1721);
                Bool *_t1723 = malloc(sizeof(Bool)); *_t1723 = Bool_not(DEREF(_t1722));
                Bool_delete(_t1722, &(Bool){1});
                if (DEREF(_t1723)) {
                    Bool_delete(_t1723, &(Bool){1});
                    break;
                }
                Bool_delete(_t1723, &(Bool){1});
                U64 *_t1724 = malloc(sizeof(U64));
                *_t1724 = 1;
                U64 *_t1725 = malloc(sizeof(U64)); *_t1725 = U64_add(DEREF(pos), DEREF(_t1724));
                U64_delete(_t1724, &(Bool){1});
                *pos = DEREF(_t1725);
                U64_delete(_t1725, &(Bool){1});
            }
            U64 *_t1742 = malloc(sizeof(U64));
            *_t1742 = 1;
            U64 *_t1743 = malloc(sizeof(U64)); *_t1743 = U64_add(DEREF(pos), DEREF(_t1742));
            U64_delete(_t1742, &(Bool){1});
            Bool *_t1744 = U64_lt(_t1743, src_len);
            U64_delete(_t1743, &(Bool){1});
            if (DEREF(_t1744)) {
                U8 *_t1734 = Str_get(source, pos);
                U8 *_t1735 = malloc(sizeof(U8));
                *_t1735 = 46;
                U64 *_t1736 = malloc(sizeof(U64));
                *_t1736 = 1;
                U64 *_t1737 = malloc(sizeof(U64)); *_t1737 = U64_add(DEREF(pos), DEREF(_t1736));
                U64_delete(_t1736, &(Bool){1});
                U8 *_t1738 = Str_get(source, _t1737);
                Bool *_t1739 = malloc(sizeof(Bool)); *_t1739 = U8_eq(DEREF(_t1734), DEREF(_t1735));
                U8_delete(_t1735, &(Bool){1});
                Bool *_t1740 = is_digit(_t1738);
                U64_delete(_t1737, &(Bool){1});
                Bool *_t1741 = malloc(sizeof(Bool)); *_t1741 = Bool_and(DEREF(_t1739), DEREF(_t1740));
                Bool_delete(_t1739, &(Bool){1});
                Bool_delete(_t1740, &(Bool){1});
                if (DEREF(_t1741)) {
                    U64 *_t1732 = malloc(sizeof(U64));
                    *_t1732 = 1;
                    U64 *_t1733 = malloc(sizeof(U64)); *_t1733 = U64_add(DEREF(pos), DEREF(_t1732));
                    U64_delete(_t1732, &(Bool){1});
                    *pos = DEREF(_t1733);
                    U64_delete(_t1733, &(Bool){1});
                    while (1) {
                        Bool *_wcond1726 = U64_lt(pos, src_len);
                        if (DEREF(_wcond1726)) {
                        } else {
                            Bool_delete(_wcond1726, &(Bool){1});
                            break;
                        }
                        Bool_delete(_wcond1726, &(Bool){1});
                        U8 *_t1727 = Str_get(source, pos);
                        Bool *_t1728 = is_digit(_t1727);
                        Bool *_t1729 = malloc(sizeof(Bool)); *_t1729 = Bool_not(DEREF(_t1728));
                        Bool_delete(_t1728, &(Bool){1});
                        if (DEREF(_t1729)) {
                            Bool_delete(_t1729, &(Bool){1});
                            break;
                        }
                        Bool_delete(_t1729, &(Bool){1});
                        U64 *_t1730 = malloc(sizeof(U64));
                        *_t1730 = 1;
                        U64 *_t1731 = malloc(sizeof(U64)); *_t1731 = U64_add(DEREF(pos), DEREF(_t1730));
                        U64_delete(_t1730, &(Bool){1});
                        *pos = DEREF(_t1731);
                        U64_delete(_t1731, &(Bool){1});
                    }
                }
                Bool_delete(_t1741, &(Bool){1});
            }
            Bool_delete(_t1744, &(Bool){1});
            U64 *_t1745 = malloc(sizeof(U64)); *_t1745 = U64_sub(DEREF(pos), DEREF(start));
            I64 *_t1746 = I64_clone(col);
            Token *_t1747 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1747->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, start, _t1745); _t1747->text = *_ca; free(_ca); }
            { I64 *_ca = I64_clone(line); _t1747->line = *_ca; free(_ca); }
            _t1747->col = DEREF(_t1746);
            U64_delete(_t1745, &(Bool){1});
            I64_delete(_t1746, &(Bool){1});
            Vec_push(tokens, _t1747);
            Bool_delete(_t1964, &(Bool){1});
            I64_delete(col, &(Bool){1});
            U64_delete(start, &(Bool){1});
            continue;
        }
        Bool_delete(_t1964, &(Bool){1});
        Bool *_t1965 = is_alpha(c);
        if (DEREF(_t1965)) {
            while (1) {
                Bool *_wcond1748 = U64_lt(pos, src_len);
                if (DEREF(_wcond1748)) {
                } else {
                    Bool_delete(_wcond1748, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond1748, &(Bool){1});
                U8 *_t1749 = Str_get(source, pos);
                Bool *_t1750 = is_alnum(_t1749);
                Bool *_t1751 = malloc(sizeof(Bool)); *_t1751 = Bool_not(DEREF(_t1750));
                Bool_delete(_t1750, &(Bool){1});
                if (DEREF(_t1751)) {
                    Bool_delete(_t1751, &(Bool){1});
                    break;
                }
                Bool_delete(_t1751, &(Bool){1});
                U64 *_t1752 = malloc(sizeof(U64));
                *_t1752 = 1;
                U64 *_t1753 = malloc(sizeof(U64)); *_t1753 = U64_add(DEREF(pos), DEREF(_t1752));
                U64_delete(_t1752, &(Bool){1});
                *pos = DEREF(_t1753);
                U64_delete(_t1753, &(Bool){1});
            }
            U64 *_t1754 = malloc(sizeof(U64)); *_t1754 = U64_sub(DEREF(pos), DEREF(start));
            Str *word = Str_substr(source, start, _t1754);
            U64_delete(_t1754, &(Bool){1});
            TokenType *type = lookup_keyword(word);
            I64 *_t1755 = I64_clone(line);
            I64 *_t1756 = I64_clone(col);
            Token *_t1757 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1757->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1757->text = *_ca; free(_ca); }
            _t1757->line = DEREF(_t1755);
            _t1757->col = DEREF(_t1756);
            I64_delete(_t1755, &(Bool){1});
            I64_delete(_t1756, &(Bool){1});
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1757);
            Bool_delete(_t1965, &(Bool){1});
            I64_delete(col, &(Bool){1});
            U64_delete(start, &(Bool){1});
            continue;
        }
        Bool_delete(_t1965, &(Bool){1});
        U8 *_t1966 = malloc(sizeof(U8));
        *_t1966 = 34;
        Bool *_t1967 = malloc(sizeof(Bool)); *_t1967 = U8_eq(DEREF(c), DEREF(_t1966));
        U8_delete(_t1966, &(Bool){1});
        if (DEREF(_t1967)) {
            U64 *_t1807 = malloc(sizeof(U64));
            *_t1807 = 1;
            U64 *_t1808 = malloc(sizeof(U64)); *_t1808 = U64_add(DEREF(pos), DEREF(_t1807));
            U64_delete(_t1807, &(Bool){1});
            *pos = DEREF(_t1808);
            U64_delete(_t1808, &(Bool){1});
            while (1) {
                Bool *_wcond1758 = U64_lt(pos, src_len);
                if (DEREF(_wcond1758)) {
                } else {
                    Bool_delete(_wcond1758, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond1758, &(Bool){1});
                U8 *_t1765 = Str_get(source, pos);
                U8 *_t1766 = malloc(sizeof(U8));
                *_t1766 = 34;
                Bool *_t1767 = malloc(sizeof(Bool)); *_t1767 = U8_eq(DEREF(_t1765), DEREF(_t1766));
                U8_delete(_t1766, &(Bool){1});
                if (DEREF(_t1767)) {
                    Bool_delete(_t1767, &(Bool){1});
                    break;
                }
                Bool_delete(_t1767, &(Bool){1});
                U8 *_t1768 = Str_get(source, pos);
                U8 *_t1769 = malloc(sizeof(U8));
                *_t1769 = 92;
                U64 *_t1770 = malloc(sizeof(U64));
                *_t1770 = 1;
                U64 *_t1771 = malloc(sizeof(U64)); *_t1771 = U64_add(DEREF(pos), DEREF(_t1770));
                U64_delete(_t1770, &(Bool){1});
                Bool *_t1772 = malloc(sizeof(Bool)); *_t1772 = U8_eq(DEREF(_t1768), DEREF(_t1769));
                U8_delete(_t1769, &(Bool){1});
                Bool *_t1773 = U64_lt(_t1771, src_len);
                U64_delete(_t1771, &(Bool){1});
                Bool *_t1774 = malloc(sizeof(Bool)); *_t1774 = Bool_and(DEREF(_t1772), DEREF(_t1773));
                Bool_delete(_t1772, &(Bool){1});
                Bool_delete(_t1773, &(Bool){1});
                if (DEREF(_t1774)) {
                    U64 *_t1759 = malloc(sizeof(U64));
                    *_t1759 = 1;
                    U64 *_t1760 = malloc(sizeof(U64)); *_t1760 = U64_add(DEREF(pos), DEREF(_t1759));
                    U64_delete(_t1759, &(Bool){1});
                    *pos = DEREF(_t1760);
                    U64_delete(_t1760, &(Bool){1});
                }
                Bool_delete(_t1774, &(Bool){1});
                U8 *_t1775 = Str_get(source, pos);
                U8 *_t1776 = malloc(sizeof(U8));
                *_t1776 = 10;
                Bool *_t1777 = malloc(sizeof(Bool)); *_t1777 = U8_eq(DEREF(_t1775), DEREF(_t1776));
                U8_delete(_t1776, &(Bool){1});
                if (DEREF(_t1777)) {
                    I64 *_t1761 = malloc(sizeof(I64));
                    *_t1761 = 1;
                    I64 *_t1762 = malloc(sizeof(I64)); *_t1762 = I64_add(DEREF(line), DEREF(_t1761));
                    I64_delete(_t1761, &(Bool){1});
                    *line = DEREF(_t1762);
                    I64_delete(_t1762, &(Bool){1});
                    U64 *_t1763 = malloc(sizeof(U64));
                    *_t1763 = 1;
                    U64 *_t1764 = malloc(sizeof(U64)); *_t1764 = U64_add(DEREF(pos), DEREF(_t1763));
                    U64_delete(_t1763, &(Bool){1});
                    *line_start = DEREF(_t1764);
                    U64_delete(_t1764, &(Bool){1});
                }
                Bool_delete(_t1777, &(Bool){1});
                U64 *_t1778 = malloc(sizeof(U64));
                *_t1778 = 1;
                U64 *_t1779 = malloc(sizeof(U64)); *_t1779 = U64_add(DEREF(pos), DEREF(_t1778));
                U64_delete(_t1778, &(Bool){1});
                *pos = DEREF(_t1779);
                U64_delete(_t1779, &(Bool){1});
            }
            U8 *_t1809 = Str_get(source, pos);
            U8 *_t1810 = malloc(sizeof(U8));
            *_t1810 = 34;
            Bool *_t1811 = U64_lt(pos, src_len);
            Bool *_t1812 = malloc(sizeof(Bool)); *_t1812 = U8_eq(DEREF(_t1809), DEREF(_t1810));
            U8_delete(_t1810, &(Bool){1});
            Bool *_t1813 = malloc(sizeof(Bool)); *_t1813 = Bool_and(DEREF(_t1811), DEREF(_t1812));
            Bool_delete(_t1811, &(Bool){1});
            Bool_delete(_t1812, &(Bool){1});
            if (DEREF(_t1813)) {
                U64 *_t1780 = malloc(sizeof(U64));
                *_t1780 = 1;
                U64 *_t1781 = malloc(sizeof(U64)); *_t1781 = U64_add(DEREF(pos), DEREF(_t1780));
                U64_delete(_t1780, &(Bool){1});
                *pos = DEREF(_t1781);
                U64_delete(_t1781, &(Bool){1});
                U64 *_t1782 = malloc(sizeof(U64));
                *_t1782 = 1;
                U64 *_t1783 = malloc(sizeof(U64)); *_t1783 = U64_sub(DEREF(pos), DEREF(start));
                U64 *_t1784 = malloc(sizeof(U64));
                *_t1784 = 2;
                U64 *_t1785 = malloc(sizeof(U64)); *_t1785 = U64_add(DEREF(start), DEREF(_t1782));
                U64_delete(_t1782, &(Bool){1});
                U64 *_t1786 = malloc(sizeof(U64)); *_t1786 = U64_sub(DEREF(_t1783), DEREF(_t1784));
                U64_delete(_t1783, &(Bool){1});
                U64_delete(_t1784, &(Bool){1});
                I64 *_t1787 = I64_clone(col);
                Token *_t1788 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1788->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, _t1785, _t1786); _t1788->text = *_ca; free(_ca); }
                { I64 *_ca = I64_clone(line); _t1788->line = *_ca; free(_ca); }
                _t1788->col = DEREF(_t1787);
                U64_delete(_t1785, &(Bool){1});
                U64_delete(_t1786, &(Bool){1});
                I64_delete(_t1787, &(Bool){1});
                Vec_push(tokens, _t1788);
            } else {
                Str *_t1789 = Str_lit("Str", 3ULL);
                U64 *_t1790 = Str_size();
                U64 *_t1791 = malloc(sizeof(U64));
                *_t1791 = 6;
                Array *_va24 = Array_new(_t1789, _t1790, _t1791);
                Str_delete(_t1789, &(Bool){1});
                U64_delete(_t1790, &(Bool){1});
                U64_delete(_t1791, &(Bool){1});
                U64 *_t1792 = malloc(sizeof(U64));
                *_t1792 = 0;
                Str *_t1793 = Str_clone(path);
                Array_set(_va24, _t1792, _t1793);
                U64_delete(_t1792, &(Bool){1});
                U64 *_t1794 = malloc(sizeof(U64));
                *_t1794 = 1;
                Str *_t1795 = Str_lit(":", 1ULL);
                Array_set(_va24, _t1794, _t1795);
                U64_delete(_t1794, &(Bool){1});
                U64 *_t1796 = malloc(sizeof(U64));
                *_t1796 = 2;
                Str *_t1797 = I64_to_str(line);
                Array_set(_va24, _t1796, _t1797);
                U64_delete(_t1796, &(Bool){1});
                U64 *_t1798 = malloc(sizeof(U64));
                *_t1798 = 3;
                Str *_t1799 = Str_lit(":", 1ULL);
                Array_set(_va24, _t1798, _t1799);
                U64_delete(_t1798, &(Bool){1});
                U64 *_t1800 = malloc(sizeof(U64));
                *_t1800 = 4;
                Str *_t1801 = I64_to_str(col);
                Array_set(_va24, _t1800, _t1801);
                U64_delete(_t1800, &(Bool){1});
                U64 *_t1802 = malloc(sizeof(U64));
                *_t1802 = 5;
                Str *_t1803 = Str_lit(": error: unterminated string", 28ULL);
                Array_set(_va24, _t1802, _t1803);
                U64_delete(_t1802, &(Bool){1});
                println(_va24);
                U64 *_t1804 = malloc(sizeof(U64)); *_t1804 = U64_sub(DEREF(pos), DEREF(start));
                I64 *_t1805 = I64_clone(col);
                Token *_t1806 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1806->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, start, _t1804); _t1806->text = *_ca; free(_ca); }
                { I64 *_ca = I64_clone(line); _t1806->line = *_ca; free(_ca); }
                _t1806->col = DEREF(_t1805);
                U64_delete(_t1804, &(Bool){1});
                I64_delete(_t1805, &(Bool){1});
                Vec_push(tokens, _t1806);
            }
            Bool_delete(_t1813, &(Bool){1});
            Bool_delete(_t1967, &(Bool){1});
            I64_delete(col, &(Bool){1});
            U64_delete(start, &(Bool){1});
            continue;
        }
        Bool_delete(_t1967, &(Bool){1});
        U8 *_t1968 = malloc(sizeof(U8));
        *_t1968 = 39;
        Bool *_t1969 = malloc(sizeof(Bool)); *_t1969 = U8_eq(DEREF(c), DEREF(_t1968));
        U8_delete(_t1968, &(Bool){1});
        if (DEREF(_t1969)) {
            U64 *_t1839 = malloc(sizeof(U64));
            *_t1839 = 1;
            U64 *_t1840 = malloc(sizeof(U64)); *_t1840 = U64_add(DEREF(pos), DEREF(_t1839));
            U64_delete(_t1839, &(Bool){1});
            *pos = DEREF(_t1840);
            U64_delete(_t1840, &(Bool){1});
            U64 *ch_start = U64_clone(pos);
            U8 *_t1841 = Str_get(source, pos);
            U8 *_t1842 = malloc(sizeof(U8));
            *_t1842 = 92;
            U64 *_t1843 = malloc(sizeof(U64));
            *_t1843 = 1;
            U64 *_t1844 = malloc(sizeof(U64)); *_t1844 = U64_add(DEREF(pos), DEREF(_t1843));
            U64_delete(_t1843, &(Bool){1});
            Bool *_t1845 = malloc(sizeof(Bool)); *_t1845 = U8_eq(DEREF(_t1841), DEREF(_t1842));
            U8_delete(_t1842, &(Bool){1});
            Bool *_t1846 = U64_lt(_t1844, src_len);
            U64_delete(_t1844, &(Bool){1});
            Bool *_t1847 = U64_lt(pos, src_len);
            Bool *_t1848 = malloc(sizeof(Bool)); *_t1848 = Bool_and(DEREF(_t1845), DEREF(_t1846));
            Bool_delete(_t1845, &(Bool){1});
            Bool_delete(_t1846, &(Bool){1});
            Bool *_t1849 = malloc(sizeof(Bool)); *_t1849 = Bool_and(DEREF(_t1847), DEREF(_t1848));
            Bool_delete(_t1847, &(Bool){1});
            Bool_delete(_t1848, &(Bool){1});
            if (DEREF(_t1849)) {
                U64 *_t1814 = malloc(sizeof(U64));
                *_t1814 = 1;
                U64 *_t1815 = malloc(sizeof(U64)); *_t1815 = U64_add(DEREF(pos), DEREF(_t1814));
                U64_delete(_t1814, &(Bool){1});
                *pos = DEREF(_t1815);
                U64_delete(_t1815, &(Bool){1});
            }
            Bool_delete(_t1849, &(Bool){1});
            U64 *_t1850 = malloc(sizeof(U64));
            *_t1850 = 1;
            U64 *_t1851 = malloc(sizeof(U64)); *_t1851 = U64_add(DEREF(pos), DEREF(_t1850));
            U64_delete(_t1850, &(Bool){1});
            *pos = DEREF(_t1851);
            U64_delete(_t1851, &(Bool){1});
            U8 *_t1852 = Str_get(source, pos);
            U8 *_t1853 = malloc(sizeof(U8));
            *_t1853 = 39;
            Bool *_t1854 = U64_lt(pos, src_len);
            Bool *_t1855 = malloc(sizeof(Bool)); *_t1855 = U8_eq(DEREF(_t1852), DEREF(_t1853));
            U8_delete(_t1853, &(Bool){1});
            Bool *_t1856 = malloc(sizeof(Bool)); *_t1856 = Bool_and(DEREF(_t1854), DEREF(_t1855));
            Bool_delete(_t1854, &(Bool){1});
            Bool_delete(_t1855, &(Bool){1});
            if (DEREF(_t1856)) {
                U64 *_t1816 = malloc(sizeof(U64)); *_t1816 = U64_sub(DEREF(pos), DEREF(ch_start));
                I64 *_t1817 = I64_clone(col);
                Token *_t1818 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1818->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, ch_start, _t1816); _t1818->text = *_ca; free(_ca); }
                { I64 *_ca = I64_clone(line); _t1818->line = *_ca; free(_ca); }
                _t1818->col = DEREF(_t1817);
                U64_delete(_t1816, &(Bool){1});
                I64_delete(_t1817, &(Bool){1});
                Vec_push(tokens, _t1818);
                U64 *_t1819 = malloc(sizeof(U64));
                *_t1819 = 1;
                U64 *_t1820 = malloc(sizeof(U64)); *_t1820 = U64_add(DEREF(pos), DEREF(_t1819));
                U64_delete(_t1819, &(Bool){1});
                *pos = DEREF(_t1820);
                U64_delete(_t1820, &(Bool){1});
            } else {
                Str *_t1821 = Str_lit("Str", 3ULL);
                U64 *_t1822 = Str_size();
                U64 *_t1823 = malloc(sizeof(U64));
                *_t1823 = 6;
                Array *_va25 = Array_new(_t1821, _t1822, _t1823);
                Str_delete(_t1821, &(Bool){1});
                U64_delete(_t1822, &(Bool){1});
                U64_delete(_t1823, &(Bool){1});
                U64 *_t1824 = malloc(sizeof(U64));
                *_t1824 = 0;
                Str *_t1825 = Str_clone(path);
                Array_set(_va25, _t1824, _t1825);
                U64_delete(_t1824, &(Bool){1});
                U64 *_t1826 = malloc(sizeof(U64));
                *_t1826 = 1;
                Str *_t1827 = Str_lit(":", 1ULL);
                Array_set(_va25, _t1826, _t1827);
                U64_delete(_t1826, &(Bool){1});
                U64 *_t1828 = malloc(sizeof(U64));
                *_t1828 = 2;
                Str *_t1829 = I64_to_str(line);
                Array_set(_va25, _t1828, _t1829);
                U64_delete(_t1828, &(Bool){1});
                U64 *_t1830 = malloc(sizeof(U64));
                *_t1830 = 3;
                Str *_t1831 = Str_lit(":", 1ULL);
                Array_set(_va25, _t1830, _t1831);
                U64_delete(_t1830, &(Bool){1});
                U64 *_t1832 = malloc(sizeof(U64));
                *_t1832 = 4;
                Str *_t1833 = I64_to_str(col);
                Array_set(_va25, _t1832, _t1833);
                U64_delete(_t1832, &(Bool){1});
                U64 *_t1834 = malloc(sizeof(U64));
                *_t1834 = 5;
                Str *_t1835 = Str_lit(": error: unterminated character literal", 39ULL);
                Array_set(_va25, _t1834, _t1835);
                U64_delete(_t1834, &(Bool){1});
                println(_va25);
                U64 *_t1836 = malloc(sizeof(U64)); *_t1836 = U64_sub(DEREF(pos), DEREF(start));
                I64 *_t1837 = I64_clone(col);
                Token *_t1838 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1838->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, start, _t1836); _t1838->text = *_ca; free(_ca); }
                { I64 *_ca = I64_clone(line); _t1838->line = *_ca; free(_ca); }
                _t1838->col = DEREF(_t1837);
                U64_delete(_t1836, &(Bool){1});
                I64_delete(_t1837, &(Bool){1});
                Vec_push(tokens, _t1838);
            }
            Bool_delete(_t1856, &(Bool){1});
            U64_delete(ch_start, &(Bool){1});
            Bool_delete(_t1969, &(Bool){1});
            I64_delete(col, &(Bool){1});
            U64_delete(start, &(Bool){1});
            continue;
        }
        Bool_delete(_t1969, &(Bool){1});
        U64 *_t1970 = malloc(sizeof(U64));
        *_t1970 = 1;
        U64 *_t1971 = malloc(sizeof(U64)); *_t1971 = U64_add(DEREF(pos), DEREF(_t1970));
        U64_delete(_t1970, &(Bool){1});
        Bool *_t1972 = U64_lt(_t1971, src_len);
        U64_delete(_t1971, &(Bool){1});
        if (DEREF(_t1972)) {
            U64 *_t1863 = malloc(sizeof(U64));
            *_t1863 = 1;
            U64 *_t1864 = malloc(sizeof(U64)); *_t1864 = U64_add(DEREF(pos), DEREF(_t1863));
            U64_delete(_t1863, &(Bool){1});
            U8 *c2 = Str_get(source, _t1864);
            TokenType *two = TokenType_clone(TokenType_Eof());
            U8 *_t1865 = malloc(sizeof(U8));
            *_t1865 = 58;
            U8 *_t1866 = malloc(sizeof(U8));
            *_t1866 = 61;
            Bool *_t1867 = malloc(sizeof(Bool)); *_t1867 = U8_eq(DEREF(c), DEREF(_t1865));
            U8_delete(_t1865, &(Bool){1});
            Bool *_t1868 = malloc(sizeof(Bool)); *_t1868 = U8_eq(DEREF(c2), DEREF(_t1866));
            U8_delete(_t1866, &(Bool){1});
            Bool *_t1869 = malloc(sizeof(Bool)); *_t1869 = Bool_and(DEREF(_t1867), DEREF(_t1868));
            Bool_delete(_t1867, &(Bool){1});
            Bool_delete(_t1868, &(Bool){1});
            if (DEREF(_t1869)) {
                two = TokenType_clone(TokenType_ColonEq());
            }
            Bool_delete(_t1869, &(Bool){1});
            U8 *_t1870 = malloc(sizeof(U8));
            *_t1870 = 61;
            U8 *_t1871 = malloc(sizeof(U8));
            *_t1871 = 61;
            Bool *_t1872 = malloc(sizeof(Bool)); *_t1872 = U8_eq(DEREF(c), DEREF(_t1870));
            U8_delete(_t1870, &(Bool){1});
            Bool *_t1873 = malloc(sizeof(Bool)); *_t1873 = U8_eq(DEREF(c2), DEREF(_t1871));
            U8_delete(_t1871, &(Bool){1});
            Bool *_t1874 = malloc(sizeof(Bool)); *_t1874 = Bool_and(DEREF(_t1872), DEREF(_t1873));
            Bool_delete(_t1872, &(Bool){1});
            Bool_delete(_t1873, &(Bool){1});
            if (DEREF(_t1874)) {
                two = TokenType_clone(TokenType_EqEq());
            }
            Bool_delete(_t1874, &(Bool){1});
            U8 *_t1875 = malloc(sizeof(U8));
            *_t1875 = 33;
            U8 *_t1876 = malloc(sizeof(U8));
            *_t1876 = 61;
            Bool *_t1877 = malloc(sizeof(Bool)); *_t1877 = U8_eq(DEREF(c), DEREF(_t1875));
            U8_delete(_t1875, &(Bool){1});
            Bool *_t1878 = malloc(sizeof(Bool)); *_t1878 = U8_eq(DEREF(c2), DEREF(_t1876));
            U8_delete(_t1876, &(Bool){1});
            Bool *_t1879 = malloc(sizeof(Bool)); *_t1879 = Bool_and(DEREF(_t1877), DEREF(_t1878));
            Bool_delete(_t1877, &(Bool){1});
            Bool_delete(_t1878, &(Bool){1});
            if (DEREF(_t1879)) {
                two = TokenType_clone(TokenType_Neq());
            }
            Bool_delete(_t1879, &(Bool){1});
            U8 *_t1880 = malloc(sizeof(U8));
            *_t1880 = 60;
            U8 *_t1881 = malloc(sizeof(U8));
            *_t1881 = 61;
            Bool *_t1882 = malloc(sizeof(Bool)); *_t1882 = U8_eq(DEREF(c), DEREF(_t1880));
            U8_delete(_t1880, &(Bool){1});
            Bool *_t1883 = malloc(sizeof(Bool)); *_t1883 = U8_eq(DEREF(c2), DEREF(_t1881));
            U8_delete(_t1881, &(Bool){1});
            Bool *_t1884 = malloc(sizeof(Bool)); *_t1884 = Bool_and(DEREF(_t1882), DEREF(_t1883));
            Bool_delete(_t1882, &(Bool){1});
            Bool_delete(_t1883, &(Bool){1});
            if (DEREF(_t1884)) {
                two = TokenType_clone(TokenType_LtEq());
            }
            Bool_delete(_t1884, &(Bool){1});
            U8 *_t1885 = malloc(sizeof(U8));
            *_t1885 = 62;
            U8 *_t1886 = malloc(sizeof(U8));
            *_t1886 = 61;
            Bool *_t1887 = malloc(sizeof(Bool)); *_t1887 = U8_eq(DEREF(c), DEREF(_t1885));
            U8_delete(_t1885, &(Bool){1});
            Bool *_t1888 = malloc(sizeof(Bool)); *_t1888 = U8_eq(DEREF(c2), DEREF(_t1886));
            U8_delete(_t1886, &(Bool){1});
            Bool *_t1889 = malloc(sizeof(Bool)); *_t1889 = Bool_and(DEREF(_t1887), DEREF(_t1888));
            Bool_delete(_t1887, &(Bool){1});
            Bool_delete(_t1888, &(Bool){1});
            if (DEREF(_t1889)) {
                two = TokenType_clone(TokenType_GtEq());
            }
            Bool_delete(_t1889, &(Bool){1});
            U8 *_t1890 = malloc(sizeof(U8));
            *_t1890 = 46;
            U8 *_t1891 = malloc(sizeof(U8));
            *_t1891 = 46;
            Bool *_t1892 = malloc(sizeof(Bool)); *_t1892 = U8_eq(DEREF(c), DEREF(_t1890));
            U8_delete(_t1890, &(Bool){1});
            Bool *_t1893 = malloc(sizeof(Bool)); *_t1893 = U8_eq(DEREF(c2), DEREF(_t1891));
            U64_delete(_t1864, &(Bool){1});
            U8_delete(_t1891, &(Bool){1});
            Bool *_t1894 = malloc(sizeof(Bool)); *_t1894 = Bool_and(DEREF(_t1892), DEREF(_t1893));
            Bool_delete(_t1892, &(Bool){1});
            Bool_delete(_t1893, &(Bool){1});
            if (DEREF(_t1894)) {
                two = TokenType_clone(TokenType_DotDot());
            }
            Bool_delete(_t1894, &(Bool){1});
            Bool *_t1895 = TokenType_eq(two, TokenType_Eof());
            Bool *_t1896 = malloc(sizeof(Bool)); *_t1896 = Bool_not(DEREF(_t1895));
            Bool_delete(_t1895, &(Bool){1});
            if (DEREF(_t1896)) {
                U64 *_t1857 = malloc(sizeof(U64));
                *_t1857 = 2;
                I64 *_t1858 = I64_clone(line);
                I64 *_t1859 = I64_clone(col);
                Token *_t1860 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1860->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, start, _t1857); _t1860->text = *_ca; free(_ca); }
                _t1860->line = DEREF(_t1858);
                _t1860->col = DEREF(_t1859);
                U64_delete(_t1857, &(Bool){1});
                I64_delete(_t1858, &(Bool){1});
                I64_delete(_t1859, &(Bool){1});
                Vec_push(tokens, _t1860);
                U64 *_t1861 = malloc(sizeof(U64));
                *_t1861 = 2;
                U64 *_t1862 = malloc(sizeof(U64)); *_t1862 = U64_add(DEREF(pos), DEREF(_t1861));
                U64_delete(_t1861, &(Bool){1});
                *pos = DEREF(_t1862);
                U64_delete(_t1862, &(Bool){1});
                Bool_delete(_t1896, &(Bool){1});
                TokenType_delete(two, &(Bool){1});
                Bool_delete(_t1972, &(Bool){1});
                I64_delete(col, &(Bool){1});
                U64_delete(start, &(Bool){1});
                continue;
            }
            Bool_delete(_t1896, &(Bool){1});
            TokenType_delete(two, &(Bool){1});
        }
        Bool_delete(_t1972, &(Bool){1});
        TokenType *single = TokenType_clone(TokenType_Eof());
        {
            U8 *_sw1897 = U8_clone(c);
            U8 *_t1932 = malloc(sizeof(U8));
            *_t1932 = 40;
            Bool *_t1933 = malloc(sizeof(Bool)); *_t1933 = U8_eq(DEREF(_sw1897), DEREF(_t1932));
            U8_delete(_t1932, &(Bool){1});
            if (DEREF(_t1933)) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 *_t1930 = malloc(sizeof(U8));
                *_t1930 = 41;
                Bool *_t1931 = malloc(sizeof(Bool)); *_t1931 = U8_eq(DEREF(_sw1897), DEREF(_t1930));
                U8_delete(_t1930, &(Bool){1});
                if (DEREF(_t1931)) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 *_t1928 = malloc(sizeof(U8));
                    *_t1928 = 123;
                    Bool *_t1929 = malloc(sizeof(Bool)); *_t1929 = U8_eq(DEREF(_sw1897), DEREF(_t1928));
                    U8_delete(_t1928, &(Bool){1});
                    if (DEREF(_t1929)) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 *_t1926 = malloc(sizeof(U8));
                        *_t1926 = 125;
                        Bool *_t1927 = malloc(sizeof(Bool)); *_t1927 = U8_eq(DEREF(_sw1897), DEREF(_t1926));
                        U8_delete(_t1926, &(Bool){1});
                        if (DEREF(_t1927)) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 *_t1924 = malloc(sizeof(U8));
                            *_t1924 = 91;
                            Bool *_t1925 = malloc(sizeof(Bool)); *_t1925 = U8_eq(DEREF(_sw1897), DEREF(_t1924));
                            U8_delete(_t1924, &(Bool){1});
                            if (DEREF(_t1925)) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 *_t1922 = malloc(sizeof(U8));
                                *_t1922 = 93;
                                Bool *_t1923 = malloc(sizeof(Bool)); *_t1923 = U8_eq(DEREF(_sw1897), DEREF(_t1922));
                                U8_delete(_t1922, &(Bool){1});
                                if (DEREF(_t1923)) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 *_t1920 = malloc(sizeof(U8));
                                    *_t1920 = 44;
                                    Bool *_t1921 = malloc(sizeof(Bool)); *_t1921 = U8_eq(DEREF(_sw1897), DEREF(_t1920));
                                    U8_delete(_t1920, &(Bool){1});
                                    if (DEREF(_t1921)) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 *_t1918 = malloc(sizeof(U8));
                                        *_t1918 = 58;
                                        Bool *_t1919 = malloc(sizeof(Bool)); *_t1919 = U8_eq(DEREF(_sw1897), DEREF(_t1918));
                                        U8_delete(_t1918, &(Bool){1});
                                        if (DEREF(_t1919)) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 *_t1916 = malloc(sizeof(U8));
                                            *_t1916 = 46;
                                            Bool *_t1917 = malloc(sizeof(Bool)); *_t1917 = U8_eq(DEREF(_sw1897), DEREF(_t1916));
                                            U8_delete(_t1916, &(Bool){1});
                                            if (DEREF(_t1917)) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 *_t1914 = malloc(sizeof(U8));
                                                *_t1914 = 63;
                                                Bool *_t1915 = malloc(sizeof(Bool)); *_t1915 = U8_eq(DEREF(_sw1897), DEREF(_t1914));
                                                U8_delete(_t1914, &(Bool){1});
                                                if (DEREF(_t1915)) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 *_t1912 = malloc(sizeof(U8));
                                                    *_t1912 = 33;
                                                    Bool *_t1913 = malloc(sizeof(Bool)); *_t1913 = U8_eq(DEREF(_sw1897), DEREF(_t1912));
                                                    U8_delete(_t1912, &(Bool){1});
                                                    if (DEREF(_t1913)) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 *_t1910 = malloc(sizeof(U8));
                                                        *_t1910 = 43;
                                                        Bool *_t1911 = malloc(sizeof(Bool)); *_t1911 = U8_eq(DEREF(_sw1897), DEREF(_t1910));
                                                        U8_delete(_t1910, &(Bool){1});
                                                        if (DEREF(_t1911)) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 *_t1908 = malloc(sizeof(U8));
                                                            *_t1908 = 45;
                                                            Bool *_t1909 = malloc(sizeof(Bool)); *_t1909 = U8_eq(DEREF(_sw1897), DEREF(_t1908));
                                                            U8_delete(_t1908, &(Bool){1});
                                                            if (DEREF(_t1909)) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 *_t1906 = malloc(sizeof(U8));
                                                                *_t1906 = 42;
                                                                Bool *_t1907 = malloc(sizeof(Bool)); *_t1907 = U8_eq(DEREF(_sw1897), DEREF(_t1906));
                                                                U8_delete(_t1906, &(Bool){1});
                                                                if (DEREF(_t1907)) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 *_t1904 = malloc(sizeof(U8));
                                                                    *_t1904 = 47;
                                                                    Bool *_t1905 = malloc(sizeof(Bool)); *_t1905 = U8_eq(DEREF(_sw1897), DEREF(_t1904));
                                                                    U8_delete(_t1904, &(Bool){1});
                                                                    if (DEREF(_t1905)) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 *_t1902 = malloc(sizeof(U8));
                                                                        *_t1902 = 61;
                                                                        Bool *_t1903 = malloc(sizeof(Bool)); *_t1903 = U8_eq(DEREF(_sw1897), DEREF(_t1902));
                                                                        U8_delete(_t1902, &(Bool){1});
                                                                        if (DEREF(_t1903)) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 *_t1900 = malloc(sizeof(U8));
                                                                            *_t1900 = 60;
                                                                            Bool *_t1901 = malloc(sizeof(Bool)); *_t1901 = U8_eq(DEREF(_sw1897), DEREF(_t1900));
                                                                            U8_delete(_t1900, &(Bool){1});
                                                                            if (DEREF(_t1901)) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 *_t1898 = malloc(sizeof(U8));
                                                                                *_t1898 = 62;
                                                                                Bool *_t1899 = malloc(sizeof(Bool)); *_t1899 = U8_eq(DEREF(_sw1897), DEREF(_t1898));
                                                                                U8_delete(_t1898, &(Bool){1});
                                                                                if (DEREF(_t1899)) {
                                                                                    single = TokenType_clone(TokenType_Gt());
                                                                                }
                                                                                Bool_delete(_t1899, &(Bool){1});
                                                                            }
                                                                            Bool_delete(_t1901, &(Bool){1});
                                                                        }
                                                                        Bool_delete(_t1903, &(Bool){1});
                                                                    }
                                                                    Bool_delete(_t1905, &(Bool){1});
                                                                }
                                                                Bool_delete(_t1907, &(Bool){1});
                                                            }
                                                            Bool_delete(_t1909, &(Bool){1});
                                                        }
                                                        Bool_delete(_t1911, &(Bool){1});
                                                    }
                                                    Bool_delete(_t1913, &(Bool){1});
                                                }
                                                Bool_delete(_t1915, &(Bool){1});
                                            }
                                            Bool_delete(_t1917, &(Bool){1});
                                        }
                                        Bool_delete(_t1919, &(Bool){1});
                                    }
                                    Bool_delete(_t1921, &(Bool){1});
                                }
                                Bool_delete(_t1923, &(Bool){1});
                            }
                            Bool_delete(_t1925, &(Bool){1});
                        }
                        Bool_delete(_t1927, &(Bool){1});
                    }
                    Bool_delete(_t1929, &(Bool){1});
                }
                Bool_delete(_t1931, &(Bool){1});
            }
            U8_delete(_sw1897, &(Bool){1});
            Bool_delete(_t1933, &(Bool){1});
        }
        Bool *_t1973 = TokenType_eq(single, TokenType_Eof());
        Bool *_t1974 = malloc(sizeof(Bool)); *_t1974 = Bool_not(DEREF(_t1973));
        Bool_delete(_t1973, &(Bool){1});
        if (DEREF(_t1974)) {
            U64 *_t1934 = malloc(sizeof(U64));
            *_t1934 = 1;
            I64 *_t1935 = I64_clone(line);
            I64 *_t1936 = I64_clone(col);
            Token *_t1937 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1937->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, start, _t1934); _t1937->text = *_ca; free(_ca); }
            _t1937->line = DEREF(_t1935);
            _t1937->col = DEREF(_t1936);
            U64_delete(_t1934, &(Bool){1});
            I64_delete(_t1935, &(Bool){1});
            I64_delete(_t1936, &(Bool){1});
            Vec_push(tokens, _t1937);
            U64 *_t1938 = malloc(sizeof(U64));
            *_t1938 = 1;
            U64 *_t1939 = malloc(sizeof(U64)); *_t1939 = U64_add(DEREF(pos), DEREF(_t1938));
            U64_delete(_t1938, &(Bool){1});
            *pos = DEREF(_t1939);
            U64_delete(_t1939, &(Bool){1});
            Bool_delete(_t1974, &(Bool){1});
            I64_delete(col, &(Bool){1});
            TokenType_delete(single, &(Bool){1});
            U64_delete(start, &(Bool){1});
            continue;
        }
        Bool_delete(_t1974, &(Bool){1});
        TokenType_delete(single, &(Bool){1});
        Str *_t1975 = Str_lit("Str", 3ULL);
        U64 *_t1976 = Str_size();
        U64 *_t1977 = malloc(sizeof(U64));
        *_t1977 = 6;
        Array *_va26 = Array_new(_t1975, _t1976, _t1977);
        Str_delete(_t1975, &(Bool){1});
        U64_delete(_t1976, &(Bool){1});
        U64_delete(_t1977, &(Bool){1});
        U64 *_t1978 = malloc(sizeof(U64));
        *_t1978 = 0;
        Str *_t1979 = Str_clone(path);
        Array_set(_va26, _t1978, _t1979);
        U64_delete(_t1978, &(Bool){1});
        U64 *_t1980 = malloc(sizeof(U64));
        *_t1980 = 1;
        Str *_t1981 = Str_lit(":", 1ULL);
        Array_set(_va26, _t1980, _t1981);
        U64_delete(_t1980, &(Bool){1});
        U64 *_t1982 = malloc(sizeof(U64));
        *_t1982 = 2;
        Str *_t1983 = I64_to_str(line);
        Array_set(_va26, _t1982, _t1983);
        U64_delete(_t1982, &(Bool){1});
        U64 *_t1984 = malloc(sizeof(U64));
        *_t1984 = 3;
        Str *_t1985 = Str_lit(":", 1ULL);
        Array_set(_va26, _t1984, _t1985);
        U64_delete(_t1984, &(Bool){1});
        U64 *_t1986 = malloc(sizeof(U64));
        *_t1986 = 4;
        Str *_t1987 = I64_to_str(col);
        Array_set(_va26, _t1986, _t1987);
        U64_delete(_t1986, &(Bool){1});
        U64 *_t1988 = malloc(sizeof(U64));
        *_t1988 = 5;
        Str *_t1989 = Str_lit(": error: unexpected character", 29ULL);
        Array_set(_va26, _t1988, _t1989);
        U64_delete(_t1988, &(Bool){1});
        println(_va26);
        U64 *_t1990 = malloc(sizeof(U64));
        *_t1990 = 1;
        I64 *_t1991 = I64_clone(col);
        I64_delete(col, &(Bool){1});
        Token *_t1992 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1992->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(source, start, _t1990); _t1992->text = *_ca; free(_ca); }
        { I64 *_ca = I64_clone(line); _t1992->line = *_ca; free(_ca); }
        _t1992->col = DEREF(_t1991);
        U64_delete(_t1990, &(Bool){1});
        I64_delete(_t1991, &(Bool){1});
        U64_delete(start, &(Bool){1});
        Vec_push(tokens, _t1992);
        U64 *_t1993 = malloc(sizeof(U64));
        *_t1993 = 1;
        U64 *_t1994 = malloc(sizeof(U64)); *_t1994 = U64_add(DEREF(pos), DEREF(_t1993));
        U64_delete(_t1993, &(Bool){1});
        *pos = DEREF(_t1994);
        U64_delete(_t1994, &(Bool){1});
    }
    U64_delete(src_len, &(Bool){1});
    U64 *_t1997 = malloc(sizeof(U64)); *_t1997 = U64_sub(DEREF(pos), DEREF(line_start));
    U64_delete(line_start, &(Bool){1});
    U64_delete(pos, &(Bool){1});
    U64 *_t1998 = malloc(sizeof(U64));
    *_t1998 = 1;
    U64 *_t1999 = malloc(sizeof(U64)); *_t1999 = U64_add(DEREF(_t1997), DEREF(_t1998));
    U64_delete(_t1997, &(Bool){1});
    U64_delete(_t1998, &(Bool){1});
    I64 *col = malloc(sizeof(I64)); *col = U64_to_i64(DEREF(_t1999));
    U64_delete(_t1999, &(Bool){1});
    I64 *_t2000 = I64_clone(col);
    I64_delete(col, &(Bool){1});
    Token *_t2001 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2001->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2001->text = *_ca; free(_ca); }
    { I64 *_ca = I64_clone(line); _t2001->line = *_ca; free(_ca); }
    _t2001->col = DEREF(_t2000);
    I64_delete(_t2000, &(Bool){1});
    I64_delete(line, &(Bool){1});
    Vec_push(tokens, _t2001);
    return tokens;
}

void dyn_call_delete(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) { EnumDef_delete(val, arg2); return; }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { U8_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) { I16_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) { F32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { U32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { U64_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) { Range_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) { Array_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) { Map_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) { Set_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) { Str_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) { Vec_delete(val, arg2); return; }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0) { TokenType_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) { Token_delete(val, arg2); return; }
    fprintf(stderr, "dyn_call: unknown type for delete\n");
    exit(1);
}

void *dyn_call_clone(Str *type_name, void *val) {
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) return (void *)EnumDef_clone(val);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return (void *)U8_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) return (void *)I16_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return (void *)I32_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return (void *)F32_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return (void *)U32_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return (void *)U64_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return (void *)I64_clone(val);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return (void *)Range_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return (void *)Bool_clone(val);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return (void *)Array_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) return (void *)Map_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) return (void *)Set_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void *)Str_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) return (void *)Vec_clone(val);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "TokenType", 9ULL) == 0) return (void *)TokenType_clone(val);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) return (void *)Token_clone(val);
    fprintf(stderr, "dyn_call: unknown type for clone\n");
    exit(1);
}

void *dyn_call_cmp(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = U8_cmp(*(U8 *)val, *(U8 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I16_cmp(*(I16 *)val, *(I16 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I32_cmp(*(I32 *)val, *(I32 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = F32_cmp(*(F32 *)val, *(F32 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = U32_cmp(*(U32 *)val, *(U32 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = U64_cmp(*(U64 *)val, *(U64 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I64_cmp(*(I64 *)val, *(I64 *)arg2); return _r; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return (void *)Bool_cmp(val, arg2);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void *)Str_cmp(val, arg2);
    fprintf(stderr, "dyn_call: unknown type for cmp\n");
    exit(1);
}

Bool *dyn_has_cmp(Str *type_name) {
    (void)type_name;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    Bool *r = malloc(sizeof(Bool)); *r = 0; return r;
}

__attribute__((constructor))
static void _til_lib_init(void) {
    _t2002 = malloc(sizeof(I64));
    *_t2002 = 0;
    _t2003 = malloc(sizeof(I64));
    *_t2003 = 1;
    _t2004 = malloc(sizeof(I64)); *_t2004 = I64_sub(DEREF(_t2002), DEREF(_t2003));
    CAP_LIT = U64_from_i64(_t2004);
    _t2005 = malloc(sizeof(I64));
    *_t2005 = 0;
    _t2006 = malloc(sizeof(I64));
    *_t2006 = 2;
    _t2007 = malloc(sizeof(I64)); *_t2007 = I64_sub(DEREF(_t2005), DEREF(_t2006));
    CAP_VIEW = U64_from_i64(_t2007);
}

