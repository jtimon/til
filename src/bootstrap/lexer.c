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
Bool * TokenType_eq(TokenType *, TokenType *);
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

Bool dyn_has_cmp(Str *type_name);

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

static I64 *_t1980;
static I64 *_t1981;
static I64 *_t1982;
static U64 *CAP_LIT;
static I64 *_t1983;
static I64 *_t1984;
static I64 *_t1985;
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
    I64 _t2 = U8_to_i64(DEREF(val));
    Str *_t3 = I64_to_str(&(I64){_t2});
    ;
    return _t3;
}

static U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b) {
    I64 _t5 = 0;
    I64 _t6 = 1;
    I64 _t7 = U8_cmp(DEREF(a), DEREF(b));
    I64 _t8 = I64_sub(_t5, _t6);
    ;
    ;
    Bool _t9 = I64_eq(_t7, _t8);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t9; return _r; }
}

static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b) {
    I64 _t10 = U8_cmp(DEREF(a), DEREF(b));
    I64 _t11 = 1;
    Bool _t12 = I64_eq(_t10, _t11);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t12; return _r; }
}

static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b) {
    Bool _t13 = U8_eq(DEREF(a), DEREF(b));
    Bool _t14 = Bool_not(_t13);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t14; return _r; }
}

static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b) {
    Bool _t15; { Bool *_hp = U8_gt(a, b); _t15 = *_hp; free(_hp); }
    Bool _t16 = Bool_not(_t15);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t16; return _r; }
}

static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b) {
    Bool _t17; { Bool *_hp = U8_lt(a, b); _t17 = *_hp; free(_hp); }
    Bool _t18 = Bool_not(_t17);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t18; return _r; }
}

static __attribute__((unused)) Str * I16_to_str(I16 * val) {
    I64 _t19 = I16_to_i64(DEREF(val));
    Str *_t20 = I64_to_str(&(I64){_t19});
    ;
    return _t20;
}

static __attribute__((unused)) I16 * I16_from_i64(I64 * val) {
    I64 _t27 = 32768;
    I64 _t28; { I64 *_hp = I64_neg(&(I64){_t27}); _t28 = *_hp; free(_hp); }
    ;
    I64 _t29 = 32767;
    Bool _t30; { Bool *_hp = I64_lt(val, &(I64){_t28}); _t30 = *_hp; free(_hp); }
    ;
    Bool _t31; { Bool *_hp = I64_gt(val, &(I64){_t29}); _t31 = *_hp; free(_hp); }
    ;
    Bool _t32 = Bool_or(_t30, _t31);
    ;
    ;
    if (_t32) {
        Str *_t21 = Str_lit("Str", 3ULL);
        U64 _t22; { U64 *_hp = Str_size(); _t22 = *_hp; free(_hp); }
        U64 _t23 = 1;
        Array *_va0 = Array_new(_t21, &(U64){_t22}, &(U64){_t23});
        Str_delete(_t21, &(Bool){1});
        ;
        ;
        U64 _t24 = 0;
        Str *_t25 = Str_lit("value out of range (-32768 to 32767)", 36ULL);
        Array_set(_va0, &(U64){_t24}, _t25);
        ;
        Str *_t26 = Str_lit("I16.from_i64", 12ULL);
        panic(_t26, _va0);
        Str_delete(_t26, &(Bool){1});
        Array_delete(_va0, &(Bool){1});
    }
    ;
    /* TODO: nested func I16_from_i64_ext */
    I16 _t33 = I16_from_i64_ext(val);
    { I16 *_r = malloc(sizeof(I16)); *_r = _t33; return _r; }
}

static __attribute__((unused)) I16 * I16_neg(I16 * a) {
    I64 _t34 = 0;
    I64 _t35 = I16_to_i64(DEREF(a));
    I64 _t36 = I64_sub(_t34, _t35);
    ;
    ;
    I16 _t37; { I16 *_hp = I16_from_i64(&(I64){_t36}); _t37 = *_hp; free(_hp); }
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t37; return _r; }
}

static __attribute__((unused)) I16 * I16_abs(I16 * a) {
    I64 _t42 = I16_to_i64(DEREF(a));
    I64 _t43 = 0;
    Bool _t44; { Bool *_hp = I64_lt(&(I64){_t42}, &(I64){_t43}); _t44 = *_hp; free(_hp); }
    ;
    ;
    if (_t44) {
        I64 _t38 = 0;
        I64 _t39 = I16_to_i64(DEREF(a));
        I64 _t40 = I64_sub(_t38, _t39);
        ;
        ;
        I16 _t41; { I16 *_hp = I16_from_i64(&(I64){_t40}); _t41 = *_hp; free(_hp); }
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t41; return _r; }
    }
    ;
    I16 _t45 = I16_clone(a);
    { I16 *_r = malloc(sizeof(I16)); *_r = _t45; return _r; }
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b) {
    I64 _t47 = 0;
    I64 _t48 = 1;
    I64 _t49 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t50 = I64_sub(_t47, _t48);
    ;
    ;
    Bool _t51 = I64_eq(_t49, _t50);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t51; return _r; }
}

static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b) {
    I64 _t52 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t53 = 1;
    Bool _t54 = I64_eq(_t52, _t53);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t54; return _r; }
}

static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b) {
    Bool _t55 = I16_eq(DEREF(a), DEREF(b));
    Bool _t56 = Bool_not(_t55);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t56; return _r; }
}

static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b) {
    Bool _t57; { Bool *_hp = I16_gt(a, b); _t57 = *_hp; free(_hp); }
    Bool _t58 = Bool_not(_t57);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t58; return _r; }
}

static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b) {
    Bool _t59; { Bool *_hp = I16_lt(a, b); _t59 = *_hp; free(_hp); }
    Bool _t60 = Bool_not(_t59);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t60; return _r; }
}

static __attribute__((unused)) Str * I32_to_str(I32 * val) {
    I64 _t61 = I32_to_i64(DEREF(val));
    Str *_t62 = I64_to_str(&(I64){_t61});
    ;
    return _t62;
}

static __attribute__((unused)) I32 * I32_from_i64(I64 * val) {
    I64 _t69 = 2147483648;
    I64 _t70; { I64 *_hp = I64_neg(&(I64){_t69}); _t70 = *_hp; free(_hp); }
    ;
    I64 _t71 = 2147483647;
    Bool _t72; { Bool *_hp = I64_lt(val, &(I64){_t70}); _t72 = *_hp; free(_hp); }
    ;
    Bool _t73; { Bool *_hp = I64_gt(val, &(I64){_t71}); _t73 = *_hp; free(_hp); }
    ;
    Bool _t74 = Bool_or(_t72, _t73);
    ;
    ;
    if (_t74) {
        Str *_t63 = Str_lit("Str", 3ULL);
        U64 _t64; { U64 *_hp = Str_size(); _t64 = *_hp; free(_hp); }
        U64 _t65 = 1;
        Array *_va1 = Array_new(_t63, &(U64){_t64}, &(U64){_t65});
        Str_delete(_t63, &(Bool){1});
        ;
        ;
        U64 _t66 = 0;
        Str *_t67 = Str_lit("value out of range (-2147483648 to 2147483647)", 46ULL);
        Array_set(_va1, &(U64){_t66}, _t67);
        ;
        Str *_t68 = Str_lit("I32.from_i64", 12ULL);
        panic(_t68, _va1);
        Str_delete(_t68, &(Bool){1});
        Array_delete(_va1, &(Bool){1});
    }
    ;
    /* TODO: nested func I32_from_i64_ext */
    I32 _t75 = I32_from_i64_ext(val);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t75; return _r; }
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    I64 _t76 = 0;
    I64 _t77 = I32_to_i64(DEREF(a));
    I64 _t78 = I64_sub(_t76, _t77);
    ;
    ;
    I32 _t79; { I32 *_hp = I32_from_i64(&(I64){_t78}); _t79 = *_hp; free(_hp); }
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t79; return _r; }
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    I64 _t84 = I32_to_i64(DEREF(a));
    I64 _t85 = 0;
    Bool _t86; { Bool *_hp = I64_lt(&(I64){_t84}, &(I64){_t85}); _t86 = *_hp; free(_hp); }
    ;
    ;
    if (_t86) {
        I64 _t80 = 0;
        I64 _t81 = I32_to_i64(DEREF(a));
        I64 _t82 = I64_sub(_t80, _t81);
        ;
        ;
        I32 _t83; { I32 *_hp = I32_from_i64(&(I64){_t82}); _t83 = *_hp; free(_hp); }
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t83; return _r; }
    }
    ;
    I32 _t87 = I32_clone(a);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t87; return _r; }
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    I64 _t89 = 0;
    I64 _t90 = 1;
    I64 _t91 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t92 = I64_sub(_t89, _t90);
    ;
    ;
    Bool _t93 = I64_eq(_t91, _t92);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t93; return _r; }
}

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    I64 _t94 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t95 = 1;
    Bool _t96 = I64_eq(_t94, _t95);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t96; return _r; }
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    Bool _t97 = I32_eq(DEREF(a), DEREF(b));
    Bool _t98 = Bool_not(_t97);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t98; return _r; }
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    Bool _t99; { Bool *_hp = I32_gt(a, b); _t99 = *_hp; free(_hp); }
    Bool _t100 = Bool_not(_t99);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t100; return _r; }
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    Bool _t101; { Bool *_hp = I32_lt(a, b); _t101 = *_hp; free(_hp); }
    Bool _t102 = Bool_not(_t101);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t102; return _r; }
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 _t103 = F32_from_i64_ext(val);
    { F32 *_r = malloc(sizeof(F32)); *_r = _t103; return _r; }
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    I64 _t105 = 0;
    I64 _t106 = 1;
    I64 _t107 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t108 = I64_sub(_t105, _t106);
    ;
    ;
    Bool _t109 = I64_eq(_t107, _t108);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t109; return _r; }
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    I64 _t110 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t111 = 1;
    Bool _t112 = I64_eq(_t110, _t111);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t112; return _r; }
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    Bool _t113 = F32_eq(DEREF(a), DEREF(b));
    Bool _t114 = Bool_not(_t113);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t114; return _r; }
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    Bool _t115; { Bool *_hp = F32_gt(a, b); _t115 = *_hp; free(_hp); }
    Bool _t116 = Bool_not(_t115);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t116; return _r; }
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    Bool _t117; { Bool *_hp = F32_lt(a, b); _t117 = *_hp; free(_hp); }
    Bool _t118 = Bool_not(_t117);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t118; return _r; }
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    I64 _t119 = U32_to_i64(DEREF(val));
    Str *_t120 = I64_to_str(&(I64){_t119});
    ;
    return _t120;
}

static __attribute__((unused)) U32 * U32_from_i64(I64 * val) {
    I64 _t127 = 0;
    I64 _t128 = 4294967295;
    Bool _t129; { Bool *_hp = I64_lt(val, &(I64){_t127}); _t129 = *_hp; free(_hp); }
    ;
    Bool _t130; { Bool *_hp = I64_gt(val, &(I64){_t128}); _t130 = *_hp; free(_hp); }
    ;
    Bool _t131 = Bool_or(_t129, _t130);
    ;
    ;
    if (_t131) {
        Str *_t121 = Str_lit("Str", 3ULL);
        U64 _t122; { U64 *_hp = Str_size(); _t122 = *_hp; free(_hp); }
        U64 _t123 = 1;
        Array *_va2 = Array_new(_t121, &(U64){_t122}, &(U64){_t123});
        Str_delete(_t121, &(Bool){1});
        ;
        ;
        U64 _t124 = 0;
        Str *_t125 = Str_lit("value out of range (0-4294967295)", 33ULL);
        Array_set(_va2, &(U64){_t124}, _t125);
        ;
        Str *_t126 = Str_lit("U32.from_i64", 12ULL);
        panic(_t126, _va2);
        Str_delete(_t126, &(Bool){1});
        Array_delete(_va2, &(Bool){1});
    }
    ;
    /* TODO: nested func U32_from_i64_ext */
    U32 _t132 = U32_from_i64_ext(val);
    { U32 *_r = malloc(sizeof(U32)); *_r = _t132; return _r; }
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    I64 _t134 = 0;
    I64 _t135 = 1;
    I64 _t136 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t137 = I64_sub(_t134, _t135);
    ;
    ;
    Bool _t138 = I64_eq(_t136, _t137);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t138; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    I64 _t139 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t140 = 1;
    Bool _t141 = I64_eq(_t139, _t140);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t141; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    Bool _t142 = U32_eq(DEREF(a), DEREF(b));
    Bool _t143 = Bool_not(_t142);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t143; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    Bool _t144; { Bool *_hp = U32_gt(a, b); _t144 = *_hp; free(_hp); }
    Bool _t145 = Bool_not(_t144);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t145; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    Bool _t146; { Bool *_hp = U32_lt(a, b); _t146 = *_hp; free(_hp); }
    Bool _t147 = Bool_not(_t146);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t147; return _r; }
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t148 = U64_to_str_ext(val);
    return _t148;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 _t149 = U64_from_i64_ext(val);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t149; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    I64 _t151 = 0;
    I64 _t152 = 1;
    I64 _t153 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t154 = I64_sub(_t151, _t152);
    ;
    ;
    Bool _t155 = I64_eq(_t153, _t154);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t155; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    I64 _t156 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t157 = 1;
    Bool _t158 = I64_eq(_t156, _t157);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t158; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    Bool _t159 = U64_eq(DEREF(a), DEREF(b));
    Bool _t160 = Bool_not(_t159);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t160; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    Bool _t161; { Bool *_hp = U64_gt(a, b); _t161 = *_hp; free(_hp); }
    Bool _t162 = Bool_not(_t161);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t162; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    Bool _t163; { Bool *_hp = U64_lt(a, b); _t163 = *_hp; free(_hp); }
    Bool _t164 = Bool_not(_t163);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t164; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    I64 _t201 = 0;
    Bool _t202 = I64_eq(DEREF(val), _t201);
    ;
    if (_t202) {
        U64 _t165 = 2;
        U8 *buf = malloc(_t165);
        ;
        I64 _t166 = 48;
        U64 _t167 = 1;
        memcpy(buf, &(I64){_t166}, _t167);
        ;
        ;
        U64 *_t168 = malloc(sizeof(U64));
        *_t168 = 1;
        void *_t169 = ptr_add(buf, DEREF(_t168));
        I64 _t170 = 0;
        U64 _t171 = 1;
        memcpy(_t169, &(I64){_t170}, _t171);
        U64_delete(_t168, &(Bool){1});
        ;
        ;
        I64 _t172 = 1;
        I64 _t173 = 1;
        Str *_t174 = malloc(sizeof(Str));
        _t174->c_str = buf;
        _t174->count = _t172;
        _t174->cap = _t173;
        ;
        ;
        ;
        return _t174;
    }
    ;
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 _t203 = 0;
    Bool _t204; { Bool *_hp = I64_lt(val, &(I64){_t203}); _t204 = *_hp; free(_hp); }
    ;
    if (_t204) {
        Bool _t175 = 1;
        is_neg = _t175;
        ;
        I64 _t176 = 0;
        I64 _t177 = I64_sub(_t176, DEREF(val));
        ;
        v = _t177;
        ;
    }
    ;
    U64 ndigits = 0;
    I64 tmp = I64_clone(&(I64){v});
    while (1) {
        I64 _t179 = 0;
        Bool _wcond178; { Bool *_hp = I64_gt(&(I64){tmp}, &(I64){_t179}); _wcond178 = *_hp; free(_hp); }
        ;
        if (_wcond178) {
        } else {
            ;
            break;
        }
        ;
        U64 _t180 = 1;
        U64 _t181 = U64_add(ndigits, _t180);
        ;
        ndigits = _t181;
        ;
        I64 _t182 = 10;
        I64 _t183 = I64_div(tmp, _t182);
        ;
        tmp = _t183;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    ;
    if (is_neg) {
        U64 _t184 = 1;
        U64 _t185 = U64_add(DEREF(total), _t184);
        ;
        *total = _t185;
        ;
    }
    U64 _t205 = 1;
    U64 _t206 = U64_add(DEREF(total), _t205);
    ;
    U8 *buf = malloc(_t206);
    ;
    if (is_neg) {
        I64 _t186 = 45;
        U64 _t187 = 1;
        memcpy(buf, &(I64){_t186}, _t187);
        ;
        ;
    }
    ;
    U64 _t207 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t207);
    ;
    while (1) {
        I64 _t189 = 0;
        Bool _wcond188; { Bool *_hp = I64_gt(&(I64){v}, &(I64){_t189}); _wcond188 = *_hp; free(_hp); }
        ;
        if (_wcond188) {
        } else {
            ;
            break;
        }
        ;
        I64 _t190 = 10;
        I64 _t191 = I64_mod(v, _t190);
        ;
        I64 _t192 = 48;
        I64 _t193 = I64_add(_t191, _t192);
        ;
        ;
        void *_t194 = ptr_add(buf, DEREF(i));
        U8 _t195 = I64_to_u8(_t193);
        ;
        U64 _t196 = 1;
        memcpy(_t194, &(U8){_t195}, _t196);
        ;
        ;
        I64 _t197 = 10;
        I64 _t198 = I64_div(v, _t197);
        ;
        v = _t198;
        ;
        U64 _t199 = 1;
        U64 _t200 = U64_sub(DEREF(i), _t199);
        ;
        *i = _t200;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t208 = ptr_add(buf, DEREF(total));
    I64 _t209 = 0;
    U64 _t210 = 1;
    memcpy(_t208, &(I64){_t209}, _t210);
    ;
    ;
    U64 _t211 = U64_clone(total);
    U64 _t212 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t213 = malloc(sizeof(Str));
    _t213->c_str = buf;
    _t213->count = _t211;
    _t213->cap = _t212;
    ;
    ;
    return _t213;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    I64 _t214 = 0;
    I64 _t215 = I64_sub(_t214, DEREF(a));
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t215; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    I64 _t218 = 0;
    Bool _t219; { Bool *_hp = I64_lt(a, &(I64){_t218}); _t219 = *_hp; free(_hp); }
    ;
    if (_t219) {
        I64 _t216 = 0;
        I64 _t217 = I64_sub(_t216, DEREF(a));
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t217; return _r; }
    }
    ;
    I64 _t220 = I64_clone(a);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t220; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    I64 _t222 = 0;
    I64 _t223 = 1;
    I64 _t224 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t225 = I64_sub(_t222, _t223);
    ;
    ;
    Bool _t226 = I64_eq(_t224, _t225);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t226; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    I64 _t227 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t228 = 1;
    Bool _t229 = I64_eq(_t227, _t228);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t229; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    Bool _t230 = I64_eq(DEREF(a), DEREF(b));
    Bool _t231 = Bool_not(_t230);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t231; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    Bool _t232; { Bool *_hp = I64_gt(a, b); _t232 = *_hp; free(_hp); }
    Bool _t233 = Bool_not(_t232);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t233; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    Bool _t234; { Bool *_hp = I64_lt(a, b); _t234 = *_hp; free(_hp); }
    Bool _t235 = Bool_not(_t234);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t235; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    U64 _t236 = U64_clone(&(U64){start});
    U64 _t237 = U64_clone(&(U64){end});
    Range *_t238 = malloc(sizeof(Range));
    _t238->start = _t236;
    _t238->end = _t237;
    ;
    ;
    return _t238;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t240; { Bool *_hp = U64_lte(&self->start, &self->end); _t240 = *_hp; free(_hp); }
    if (_t240) {
        U64 _t239 = U64_sub(self->end, self->start);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t239; return _r; }
    }
    ;
    U64 _t241 = U64_sub(self->start, self->end);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t241; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    Bool _t243; { Bool *_hp = U64_lte(&self->start, &self->end); _t243 = *_hp; free(_hp); }
    if (_t243) {
        U64 _t242 = U64_add(self->start, i);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t242; return _r; }
    }
    ;
    U64 _t244 = U64_sub(self->start, i);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t244; return _r; }
}

Range * Range_clone(Range * val) {
    Range *_t245 = malloc(sizeof(Range));
    _t245->start = val->start;
    _t245->end = val->end;
    return _t245;
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
        Str *_t247 = Str_lit("true", 4ULL);
        return _t247;
    } else {
        Str *_t248 = Str_lit("false", 5ULL);
        return _t248;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool _t253 = Bool_eq(DEREF(a), DEREF(b));
    if (_t253) {
        I64 _t249 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t249; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t250 = 0;
        I64 _t251 = 1;
        I64 _t252 = I64_sub(_t250, _t251);
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t252; return _r; }
    }
    I64 _t254 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t254; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    I64 _t256 = 0;
    I64 _t257 = 1;
    I64 _t258; { I64 *_hp = Bool_cmp(a, b); _t258 = *_hp; free(_hp); }
    I64 _t259 = I64_sub(_t256, _t257);
    ;
    ;
    Bool _t260 = I64_eq(_t258, _t259);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t260; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    I64 _t261; { I64 *_hp = Bool_cmp(a, b); _t261 = *_hp; free(_hp); }
    I64 _t262 = 1;
    Bool _t263 = I64_eq(_t261, _t262);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t263; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    Bool _t264 = Bool_eq(DEREF(a), DEREF(b));
    Bool _t265 = Bool_not(_t264);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t265; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    Bool _t266; { Bool *_hp = Bool_gt(a, b); _t266 = *_hp; free(_hp); }
    Bool _t267 = Bool_not(_t266);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t267; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    Bool _t268; { Bool *_hp = Bool_lt(a, b); _t268 = *_hp; free(_hp); }
    Bool _t269 = Bool_not(_t268);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t269; return _r; }
}

void println(Array * parts) {
    {
        U64 *_fi270 = malloc(sizeof(U64));
        *_fi270 = 0;
        while (1) {
            U64 _t272; { U64 *_hp = Array_len(parts); _t272 = *_hp; free(_hp); }
            Bool _wcond271; { Bool *_hp = U64_lt(_fi270, &(U64){_t272}); _wcond271 = *_hp; free(_hp); }
            ;
            if (_wcond271) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi270);
            U64 _t273 = 1;
            U64 _t274 = U64_add(DEREF(_fi270), _t273);
            ;
            *_fi270 = _t274;
            ;
            print_single(s);
        }
        U64_delete(_fi270, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        U64 *_fi275 = malloc(sizeof(U64));
        *_fi275 = 0;
        while (1) {
            U64 _t277; { U64 *_hp = Array_len(parts); _t277 = *_hp; free(_hp); }
            Bool _wcond276; { Bool *_hp = U64_lt(_fi275, &(U64){_t277}); _wcond276 = *_hp; free(_hp); }
            ;
            if (_wcond276) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi275);
            U64 _t278 = 1;
            U64 _t279 = U64_add(DEREF(_fi275), _t278);
            ;
            *_fi275 = _t279;
            ;
            print_single(s);
        }
        U64_delete(_fi275, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 total = 0;
    {
        U64 *_fi280 = malloc(sizeof(U64));
        *_fi280 = 0;
        while (1) {
            U64 _t282; { U64 *_hp = Array_len(parts); _t282 = *_hp; free(_hp); }
            Bool _wcond281; { Bool *_hp = U64_lt(_fi280, &(U64){_t282}); _wcond281 = *_hp; free(_hp); }
            ;
            if (_wcond281) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi280);
            U64 _t283 = 1;
            U64 _t284 = U64_add(DEREF(_fi280), _t283);
            ;
            *_fi280 = _t284;
            ;
            U64 _t285; { U64 *_hp = Str_len(s); _t285 = *_hp; free(_hp); }
            U64 _t286 = U64_add(total, _t285);
            ;
            total = _t286;
            ;
        }
        U64_delete(_fi280, &(Bool){1});
    }
    U8 *buf = malloc(total);
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi287 = malloc(sizeof(U64));
        *_fi287 = 0;
        while (1) {
            U64 _t289; { U64 *_hp = Array_len(parts); _t289 = *_hp; free(_hp); }
            Bool _wcond288; { Bool *_hp = U64_lt(_fi287, &(U64){_t289}); _wcond288 = *_hp; free(_hp); }
            ;
            if (_wcond288) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi287);
            U64 _t290 = 1;
            U64 _t291 = U64_add(DEREF(_fi287), _t290);
            ;
            *_fi287 = _t291;
            ;
            void *_t292 = ptr_add(buf, DEREF(offset));
            U64 _t293; { U64 *_hp = Str_len(s); _t293 = *_hp; free(_hp); }
            memcpy(_t292, s->c_str, _t293);
            ;
            U64 _t294; { U64 *_hp = Str_len(s); _t294 = *_hp; free(_hp); }
            U64 _t295 = U64_add(DEREF(offset), _t294);
            ;
            *offset = _t295;
            ;
        }
        U64_delete(_fi287, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t296 = U64_clone(&(U64){total});
    U64 _t297 = U64_clone(&(U64){total});
    ;
    Str *_t298 = malloc(sizeof(Str));
    _t298->c_str = buf;
    _t298->count = _t296;
    _t298->cap = _t297;
    ;
    ;
    return _t298;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        I64 _t299 = 0;
        I64 _t300 = 1;
        I64 _t301 = I64_sub(_t299, _t300);
        ;
        ;
        Bool _t302; { Bool *_hp = I64_neq(&(I64){status}, &(I64){_t301}); _t302 = *_hp; free(_hp); }
        ;
        if (_t302) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t303 = 50;
        sleep_ms(_t303);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t309; { U64 *_hp = Array_len(args); _t309 = *_hp; free(_hp); }
        Bool _wcond304; { Bool *_hp = U64_lt(i, &(U64){_t309}); _wcond304 = *_hp; free(_hp); }
        ;
        if (_wcond304) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        U64 _t310 = 0;
        Bool _t311; { Bool *_hp = U64_gt(i, &(U64){_t310}); _t311 = *_hp; free(_hp); }
        ;
        if (_t311) {
            Str *_t305 = Str_lit(" '", 2ULL);
            Str *_t306 = Str_concat(cmd, _t305);
            Str_delete(_t305, &(Bool){1});
            Str *_t307 = Str_concat(_t306, arg);
            Str_delete(_t306, &(Bool){1});
            Str *_t308 = Str_lit("'", 1ULL);
            cmd = Str_concat(_t307, _t308);
            Str_delete(_t307, &(Bool){1});
            Str_delete(_t308, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t312 = 1;
        U64 _t313 = U64_add(DEREF(i), _t312);
        ;
        *i = _t313;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    Str *_t314 = Str_lit(" > ", 3ULL);
    Str *_t315 = Str_concat(cmd, _t314);
    Str_delete(_t314, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t316 = Str_concat(_t315, tmpf);
    Str_delete(_t315, &(Bool){1});
    Str *_t317 = Str_lit(" 2>&1", 5ULL);
    Str *_t318 = Str_concat(_t316, _t317);
    Str_delete(_t316, &(Bool){1});
    Str_delete(_t317, &(Bool){1});
    I64 pid; { I64 *_hp = spawn_cmd(_t318); pid = *_hp; free(_hp); }
    Str_delete(_t318, &(Bool){1});
    I64 ec; { I64 *_hp = wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    ;
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 _t319; { U64 *_hp = Str_size(); _t319 = *_hp; free(_hp); }
    memcpy(output, content, _t319);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    Str *_t320 = Str_lit("Str", 3ULL);
    U64 _t321; { U64 *_hp = Str_size(); _t321 = *_hp; free(_hp); }
    U64 _t322 = 3;
    Array *_va3 = Array_new(_t320, &(U64){_t321}, &(U64){_t322});
    Str_delete(_t320, &(Bool){1});
    ;
    ;
    U64 _t323 = 0;
    Str *_t324 = Str_clone(loc_str);
    Array_set(_va3, &(U64){_t323}, _t324);
    ;
    U64 _t325 = 1;
    Str *_t326 = Str_lit(": panic: ", 9ULL);
    Array_set(_va3, &(U64){_t325}, _t326);
    ;
    U64 _t327 = 2;
    Str *_t328 = format(parts);
    Array_set(_va3, &(U64){_t327}, _t328);
    ;
    println(_va3);
    I64 _t329 = 1;
    exit(_t329);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t330 = Str_lit("Str", 3ULL);
    U64 _t331; { U64 *_hp = Str_size(); _t331 = *_hp; free(_hp); }
    U64 _t332 = 2;
    Array *_va4 = Array_new(_t330, &(U64){_t331}, &(U64){_t332});
    Str_delete(_t330, &(Bool){1});
    ;
    ;
    U64 _t333 = 0;
    Str *_t334 = Str_lit("TODO: ", 6ULL);
    Array_set(_va4, &(U64){_t333}, _t334);
    ;
    U64 _t335 = 1;
    Str *_t336 = format(parts);
    Array_set(_va4, &(U64){_t335}, _t336);
    ;
    panic(loc_str, _va4);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t337 = Str_lit("Str", 3ULL);
    U64 _t338; { U64 *_hp = Str_size(); _t338 = *_hp; free(_hp); }
    U64 _t339 = 1;
    Array *_va5 = Array_new(_t337, &(U64){_t338}, &(U64){_t339});
    Str_delete(_t337, &(Bool){1});
    ;
    ;
    U64 _t340 = 0;
    Str *_t341 = Str_lit("unreachable", 11ULL);
    Array_set(_va5, &(U64){_t340}, _t341);
    ;
    panic(loc_str, _va5);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool _t349 = Bool_not(DEREF(cond));
    if (_t349) {
        Str *_t342 = Str_lit("Str", 3ULL);
        U64 _t343; { U64 *_hp = Str_size(); _t343 = *_hp; free(_hp); }
        U64 _t344 = 2;
        Array *_va6 = Array_new(_t342, &(U64){_t343}, &(U64){_t344});
        Str_delete(_t342, &(Bool){1});
        ;
        ;
        U64 _t345 = 0;
        Str *_t346 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va6, &(U64){_t345}, _t346);
        ;
        U64 _t347 = 1;
        Str *_t348 = format(parts);
        Array_set(_va6, &(U64){_t347}, _t348);
        ;
        panic(loc_str, _va6);
    }
    ;
    Bool _t350 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t350; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t351 = Str_lit("Str", 3ULL);
    U64 _t352; { U64 *_hp = Str_size(); _t352 = *_hp; free(_hp); }
    U64 _t353 = 0;
    Array *_va7 = Array_new(_t351, &(U64){_t352}, &(U64){_t353});
    Str_delete(_t351, &(Bool){1});
    ;
    ;
    Bool _t354; { Bool *_hp = assertm(loc_str, cond, _va7); _t354 = *_hp; free(_hp); }
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t354; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t355 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool _t356; { Bool *_hp = assertm(loc_str, cond, _t355); _t356 = *_hp; free(_hp); }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool _t370; { Bool *_hp = I64_neq(a, b); _t370 = *_hp; free(_hp); }
    if (_t370) {
        Str *_t357 = Str_lit("Str", 3ULL);
        U64 _t358; { U64 *_hp = Str_size(); _t358 = *_hp; free(_hp); }
        U64 _t359 = 5;
        Array *_va8 = Array_new(_t357, &(U64){_t358}, &(U64){_t359});
        Str_delete(_t357, &(Bool){1});
        ;
        ;
        U64 _t360 = 0;
        Str *_t361 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va8, &(U64){_t360}, _t361);
        ;
        U64 _t362 = 1;
        Str *_t363 = I64_to_str(a);
        Array_set(_va8, &(U64){_t362}, _t363);
        ;
        U64 _t364 = 2;
        Str *_t365 = Str_lit("', found '", 10ULL);
        Array_set(_va8, &(U64){_t364}, _t365);
        ;
        U64 _t366 = 3;
        Str *_t367 = I64_to_str(b);
        Array_set(_va8, &(U64){_t366}, _t367);
        ;
        U64 _t368 = 4;
        Str *_t369 = Str_lit("'", 1ULL);
        Array_set(_va8, &(U64){_t368}, _t369);
        ;
        panic(loc_str, _va8);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool _t384; { Bool *_hp = Str_eq(a, b); _t384 = *_hp; free(_hp); }
    Bool _t385 = Bool_not(_t384);
    ;
    if (_t385) {
        Str *_t371 = Str_lit("Str", 3ULL);
        U64 _t372; { U64 *_hp = Str_size(); _t372 = *_hp; free(_hp); }
        U64 _t373 = 5;
        Array *_va9 = Array_new(_t371, &(U64){_t372}, &(U64){_t373});
        Str_delete(_t371, &(Bool){1});
        ;
        ;
        U64 _t374 = 0;
        Str *_t375 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va9, &(U64){_t374}, _t375);
        ;
        U64 _t376 = 1;
        Str *_t377 = Str_clone(a);
        Array_set(_va9, &(U64){_t376}, _t377);
        ;
        U64 _t378 = 2;
        Str *_t379 = Str_lit("', found '", 10ULL);
        Array_set(_va9, &(U64){_t378}, _t379);
        ;
        U64 _t380 = 3;
        Str *_t381 = Str_clone(b);
        Array_set(_va9, &(U64){_t380}, _t381);
        ;
        U64 _t382 = 4;
        Str *_t383 = Str_lit("'", 1ULL);
        Array_set(_va9, &(U64){_t382}, _t383);
        ;
        panic(loc_str, _va9);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    void *_t386 = calloc(DEREF(cap), DEREF(elem_size));
    U64 _t387 = U64_clone(cap);
    U64 _t388 = U64_clone(elem_size);
    Array *_t389 = malloc(sizeof(Array));
    _t389->data = _t386;
    _t389->cap = _t387;
    _t389->elem_size = _t388;
    { Str *_ca = Str_clone(elem_type); _t389->elem_type = *_ca; free(_ca); }
    ;
    ;
    return _t389;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    Bool _t404; { Bool *_hp = U64_gte(i, &self->cap); _t404 = *_hp; free(_hp); }
    if (_t404) {
        Str *_t390 = Str_lit("Str", 3ULL);
        U64 _t391; { U64 *_hp = Str_size(); _t391 = *_hp; free(_hp); }
        U64 _t392 = 5;
        Array *_va10 = Array_new(_t390, &(U64){_t391}, &(U64){_t392});
        Str_delete(_t390, &(Bool){1});
        ;
        ;
        U64 _t393 = 0;
        Str *_t394 = Str_lit("index ", 6ULL);
        Array_set(_va10, &(U64){_t393}, _t394);
        ;
        U64 _t395 = 1;
        Str *_t396 = U64_to_str(DEREF(i));
        Array_set(_va10, &(U64){_t395}, _t396);
        ;
        U64 _t397 = 2;
        Str *_t398 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va10, &(U64){_t397}, _t398);
        ;
        U64 _t399 = 3;
        Str *_t400 = U64_to_str(self->cap);
        Array_set(_va10, &(U64){_t399}, _t400);
        ;
        U64 _t401 = 4;
        Str *_t402 = Str_lit(")", 1ULL);
        Array_set(_va10, &(U64){_t401}, _t402);
        ;
        Str *_t403 = Str_lit("Array.get", 9ULL);
        panic(_t403, _va10);
        Str_delete(_t403, &(Bool){1});
    }
    ;
    U64 *_t405 = malloc(sizeof(U64)); *_t405 = U64_mul(DEREF(i), self->elem_size);
    void *_t406 = ptr_add(self->data, DEREF(_t405));
    U64_delete(_t405, &(Bool){1});
    return _t406;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    Bool _t421; { Bool *_hp = U64_gte(i, &self->cap); _t421 = *_hp; free(_hp); }
    if (_t421) {
        Str *_t407 = Str_lit("Str", 3ULL);
        U64 _t408; { U64 *_hp = Str_size(); _t408 = *_hp; free(_hp); }
        U64 _t409 = 5;
        Array *_va11 = Array_new(_t407, &(U64){_t408}, &(U64){_t409});
        Str_delete(_t407, &(Bool){1});
        ;
        ;
        U64 _t410 = 0;
        Str *_t411 = Str_lit("index ", 6ULL);
        Array_set(_va11, &(U64){_t410}, _t411);
        ;
        U64 _t412 = 1;
        Str *_t413 = U64_to_str(DEREF(i));
        Array_set(_va11, &(U64){_t412}, _t413);
        ;
        U64 _t414 = 2;
        Str *_t415 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va11, &(U64){_t414}, _t415);
        ;
        U64 _t416 = 3;
        Str *_t417 = U64_to_str(self->cap);
        Array_set(_va11, &(U64){_t416}, _t417);
        ;
        U64 _t418 = 4;
        Str *_t419 = Str_lit(")", 1ULL);
        Array_set(_va11, &(U64){_t418}, _t419);
        ;
        Str *_t420 = Str_lit("Array.set", 9ULL);
        panic(_t420, _va11);
        Str_delete(_t420, &(Bool){1});
    }
    ;
    U64 *_t422 = malloc(sizeof(U64)); *_t422 = U64_mul(DEREF(i), self->elem_size);
    void *_t423 = ptr_add(self->data, DEREF(_t422));
    Bool _t424 = 0;
    dyn_call_delete(&self->elem_type, _t423, &(Bool){_t424});
    U64_delete(_t422, &(Bool){1});
    ;
    U64 *_t425 = malloc(sizeof(U64)); *_t425 = U64_mul(DEREF(i), self->elem_size);
    void *_t426 = ptr_add(self->data, DEREF(_t425));
    memcpy(_t426, val, self->elem_size);
    U64_delete(_t425, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    {
        U64 _fi427 = 0;
        while (1) {
            U64 _t429 = 0;
            Range *_t430 = Range_new(_t429, self->cap);
            ;
            U64 _t431; { U64 *_hp = Range_len(_t430); _t431 = *_hp; free(_hp); }
            Range_delete(_t430, &(Bool){1});
            Bool _wcond428; { Bool *_hp = U64_lt(&(U64){_fi427}, &(U64){_t431}); _wcond428 = *_hp; free(_hp); }
            ;
            if (_wcond428) {
            } else {
                ;
                break;
            }
            ;
            U64 _t432 = 0;
            Range *_t433 = Range_new(_t432, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t433, _fi427); i = *_hp; free(_hp); }
            Range_delete(_t433, &(Bool){1});
            U64 _t434 = 1;
            U64 _t435 = U64_add(_fi427, _t434);
            ;
            _fi427 = _t435;
            ;
            U64 *_t436 = malloc(sizeof(U64)); *_t436 = U64_mul(i, self->elem_size);
            ;
            void *_t437 = ptr_add(self->data, DEREF(_t436));
            Bool _t438 = 0;
            dyn_call_delete(&self->elem_type, _t437, &(Bool){_t438});
            U64_delete(_t436, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t439 = 0;
    Str_delete(&self->elem_type, &(Bool){_t439});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t453 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t453);
    ;
    {
        U64 _fi440 = 0;
        while (1) {
            U64 _t442 = 0;
            Range *_t443 = Range_new(_t442, self->cap);
            ;
            U64 _t444; { U64 *_hp = Range_len(_t443); _t444 = *_hp; free(_hp); }
            Range_delete(_t443, &(Bool){1});
            Bool _wcond441; { Bool *_hp = U64_lt(&(U64){_fi440}, &(U64){_t444}); _wcond441 = *_hp; free(_hp); }
            ;
            if (_wcond441) {
            } else {
                ;
                break;
            }
            ;
            U64 _t445 = 0;
            Range *_t446 = Range_new(_t445, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t446, _fi440); i = *_hp; free(_hp); }
            Range_delete(_t446, &(Bool){1});
            U64 _t447 = 1;
            U64 _t448 = U64_add(_fi440, _t447);
            ;
            _fi440 = _t448;
            ;
            U64 *_t449 = malloc(sizeof(U64)); *_t449 = U64_mul(i, self->elem_size);
            void *_t450 = ptr_add(self->data, DEREF(_t449));
            void *cloned = dyn_call_clone(&self->elem_type, _t450);
            U64_delete(_t449, &(Bool){1});
            U64 *_t451 = malloc(sizeof(U64)); *_t451 = U64_mul(i, self->elem_size);
            ;
            void *_t452 = ptr_add(new_data, DEREF(_t451));
            memcpy(_t452, cloned, self->elem_size);
            U64_delete(_t451, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t454 = malloc(sizeof(Array));
    _t454->data = new_data;
    _t454->cap = self->cap;
    _t454->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t454->elem_type = *_ca; free(_ca); }
    return _t454;
}

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    Bool _t468; { Bool *_hp = Str_is_empty(key_type); _t468 = *_hp; free(_hp); }
    Bool _t469 = Bool_not(_t468);
    ;
    if (_t469) {
        Bool _t466 = dyn_has_cmp(key_type);
        Bool _t467 = Bool_not(_t466);
        ;
        if (_t467) {
            Str *_t456 = Str_lit("Str", 3ULL);
            U64 _t457; { U64 *_hp = Str_size(); _t457 = *_hp; free(_hp); }
            U64 _t458 = 3;
            Array *_va12 = Array_new(_t456, &(U64){_t457}, &(U64){_t458});
            Str_delete(_t456, &(Bool){1});
            ;
            ;
            U64 _t459 = 0;
            Str *_t460 = Str_lit("type ", 5ULL);
            Array_set(_va12, &(U64){_t459}, _t460);
            ;
            U64 _t461 = 1;
            Str *_t462 = Str_clone(key_type);
            Array_set(_va12, &(U64){_t461}, _t462);
            ;
            U64 _t463 = 2;
            Str *_t464 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va12, &(U64){_t463}, _t464);
            ;
            Str *_t465 = Str_lit("Map.new", 7ULL);
            panic(_t465, _va12);
            Str_delete(_t465, &(Bool){1});
        }
        ;
    }
    ;
    void *_t470 = malloc(DEREF(key_size));
    void *_t471 = malloc(DEREF(val_size));
    U64 _t472 = 0;
    I64 _t473 = 1;
    U64 _t474 = U64_clone(key_size);
    U64 _t475 = U64_clone(val_size);
    Map *_t476 = malloc(sizeof(Map));
    _t476->key_data = _t470;
    _t476->val_data = _t471;
    _t476->count = _t472;
    _t476->cap = _t473;
    _t476->key_size = _t474;
    { Str *_ca = Str_clone(key_type); _t476->key_type = *_ca; free(_ca); }
    _t476->val_size = _t475;
    { Str *_ca = Str_clone(val_type); _t476->val_type = *_ca; free(_ca); }
    ;
    ;
    ;
    ;
    return _t476;
}

U64 * Map_len(Map * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Map_has(Map * self, void * key) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond477; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond477 = *_hp; free(_hp); }
        if (_wcond477) {
        } else {
            ;
            break;
        }
        ;
        U64 _t484 = U64_sub(hi, lo);
        U64 _t485 = 2;
        U64 _t486 = U64_div(_t484, _t485);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t486);
        ;
        U64 *_t487 = malloc(sizeof(U64)); *_t487 = U64_mul(DEREF(mid), self->key_size);
        void *_t488 = ptr_add(self->key_data, DEREF(_t487));
        I64 *c = dyn_call_cmp(&self->key_type, _t488, key);
        U64_delete(_t487, &(Bool){1});
        I64 _t489 = 0;
        Bool _t490; { Bool *_hp = I64_lt(c, &(I64){_t489}); _t490 = *_hp; free(_hp); }
        ;
        if (_t490) {
            U64 _t478 = 1;
            U64 _t479 = U64_add(DEREF(mid), _t478);
            ;
            lo = _t479;
            ;
        } else {
            I64 _t482 = 0;
            Bool _t483; { Bool *_hp = I64_gt(c, &(I64){_t482}); _t483 = *_hp; free(_hp); }
            ;
            if (_t483) {
                U64 _t480 = U64_clone(mid);
                hi = _t480;
                ;
            } else {
                Bool _t481 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t481; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t491 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t491; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond492; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond492 = *_hp; free(_hp); }
        if (_wcond492) {
        } else {
            ;
            break;
        }
        ;
        U64 _t500 = U64_sub(hi, lo);
        U64 _t501 = 2;
        U64 _t502 = U64_div(_t500, _t501);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t502);
        ;
        U64 *_t503 = malloc(sizeof(U64)); *_t503 = U64_mul(DEREF(mid), self->key_size);
        void *_t504 = ptr_add(self->key_data, DEREF(_t503));
        I64 *c = dyn_call_cmp(&self->key_type, _t504, key);
        U64_delete(_t503, &(Bool){1});
        I64 _t505 = 0;
        Bool _t506; { Bool *_hp = I64_lt(c, &(I64){_t505}); _t506 = *_hp; free(_hp); }
        ;
        if (_t506) {
            U64 _t493 = 1;
            U64 _t494 = U64_add(DEREF(mid), _t493);
            ;
            lo = _t494;
            ;
        } else {
            I64 _t498 = 0;
            Bool _t499; { Bool *_hp = I64_gt(c, &(I64){_t498}); _t499 = *_hp; free(_hp); }
            ;
            if (_t499) {
                U64 _t495 = U64_clone(mid);
                hi = _t495;
                ;
            } else {
                U64 *_t496 = malloc(sizeof(U64)); *_t496 = U64_mul(DEREF(mid), self->val_size);
                void *_t497 = ptr_add(self->val_data, DEREF(_t496));
                U64_delete(_t496, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t497;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t507 = Str_lit("Str", 3ULL);
    U64 _t508; { U64 *_hp = Str_size(); _t508 = *_hp; free(_hp); }
    U64 _t509 = 1;
    Array *_va13 = Array_new(_t507, &(U64){_t508}, &(U64){_t509});
    Str_delete(_t507, &(Bool){1});
    ;
    ;
    U64 _t510 = 0;
    Str *_t511 = Str_lit("key not found", 13ULL);
    Array_set(_va13, &(U64){_t510}, _t511);
    ;
    Str *_t512 = Str_lit("Map.get", 7ULL);
    panic(_t512, _va13);
    Str_delete(_t512, &(Bool){1});
    U64 *_t513 = malloc(sizeof(U64));
    *_t513 = 0;
    void *_t514 = ptr_add(self->val_data, DEREF(_t513));
    U64_delete(_t513, &(Bool){1});
    return _t514;
}

void Map_set(Map * self, void * key, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond515; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond515 = *_hp; free(_hp); }
        if (_wcond515) {
        } else {
            ;
            break;
        }
        ;
        U64 _t524 = U64_sub(hi, lo);
        U64 _t525 = 2;
        U64 _t526 = U64_div(_t524, _t525);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t526);
        ;
        U64 *_t527 = malloc(sizeof(U64)); *_t527 = U64_mul(DEREF(mid), self->key_size);
        void *_t528 = ptr_add(self->key_data, DEREF(_t527));
        I64 *c = dyn_call_cmp(&self->key_type, _t528, key);
        U64_delete(_t527, &(Bool){1});
        I64 _t529 = 0;
        Bool _t530; { Bool *_hp = I64_lt(c, &(I64){_t529}); _t530 = *_hp; free(_hp); }
        ;
        if (_t530) {
            U64 _t516 = 1;
            U64 _t517 = U64_add(DEREF(mid), _t516);
            ;
            lo = _t517;
            ;
        } else {
            I64 _t522 = 0;
            Bool _t523; { Bool *_hp = I64_gt(c, &(I64){_t522}); _t523 = *_hp; free(_hp); }
            ;
            if (_t523) {
                U64 _t518 = U64_clone(mid);
                hi = _t518;
                ;
            } else {
                Bool _t519 = 1;
                found = _t519;
                ;
                U64 _t520 = U64_clone(mid);
                lo = _t520;
                ;
                U64 _t521 = U64_clone(mid);
                hi = _t521;
                ;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    if (found) {
        Bool _t535; { Bool *_hp = Str_is_empty(&self->key_type); _t535 = *_hp; free(_hp); }
        Bool _t536 = Bool_not(_t535);
        ;
        if (_t536) {
            Bool _t531 = 0;
            dyn_call_delete(&self->key_type, key, &(Bool){_t531});
            ;
        }
        ;
        free(key);
        Bool _t537; { Bool *_hp = Str_is_empty(&self->val_type); _t537 = *_hp; free(_hp); }
        Bool _t538 = Bool_not(_t537);
        ;
        if (_t538) {
            U64 *_t532 = malloc(sizeof(U64)); *_t532 = U64_mul(lo, self->val_size);
            void *_t533 = ptr_add(self->val_data, DEREF(_t532));
            Bool _t534 = 0;
            dyn_call_delete(&self->val_type, _t533, &(Bool){_t534});
            U64_delete(_t532, &(Bool){1});
            ;
        }
        ;
        U64 *_t539 = malloc(sizeof(U64)); *_t539 = U64_mul(lo, self->val_size);
        void *_t540 = ptr_add(self->val_data, DEREF(_t539));
        memcpy(_t540, val, self->val_size);
        U64_delete(_t539, &(Bool){1});
        free(val);
    } else {
        Bool _t547 = U64_eq(self->count, self->cap);
        if (_t547) {
            U64 _t541 = 2;
            U64 new_cap = U64_mul(self->cap, _t541);
            ;
            U64 _t542 = U64_mul(new_cap, self->key_size);
            void *_t543 = realloc(self->key_data, _t542);
            ;
            self->key_data = _t543;
            U64 _t544 = U64_mul(new_cap, self->val_size);
            void *_t545 = realloc(self->val_data, _t544);
            ;
            self->val_data = _t545;
            U64 _t546 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t546;
            ;
        }
        ;
        U64 _t548 = 1;
        U64 _t549 = U64_add(lo, _t548);
        ;
        U64 *_t550 = malloc(sizeof(U64)); *_t550 = U64_mul(_t549, self->key_size);
        ;
        U64 *_t551 = malloc(sizeof(U64)); *_t551 = U64_mul(lo, self->key_size);
        U64 _t552 = U64_sub(self->count, lo);
        void *_t553 = ptr_add(self->key_data, DEREF(_t550));
        void *_t554 = ptr_add(self->key_data, DEREF(_t551));
        U64 _t555 = U64_mul(_t552, self->key_size);
        ;
        memmove(_t553, _t554, _t555);
        U64_delete(_t550, &(Bool){1});
        U64_delete(_t551, &(Bool){1});
        ;
        U64 _t556 = 1;
        U64 _t557 = U64_add(lo, _t556);
        ;
        U64 *_t558 = malloc(sizeof(U64)); *_t558 = U64_mul(_t557, self->val_size);
        ;
        U64 *_t559 = malloc(sizeof(U64)); *_t559 = U64_mul(lo, self->val_size);
        U64 _t560 = U64_sub(self->count, lo);
        void *_t561 = ptr_add(self->val_data, DEREF(_t558));
        void *_t562 = ptr_add(self->val_data, DEREF(_t559));
        U64 _t563 = U64_mul(_t560, self->val_size);
        ;
        memmove(_t561, _t562, _t563);
        U64_delete(_t558, &(Bool){1});
        U64_delete(_t559, &(Bool){1});
        ;
        U64 *_t564 = malloc(sizeof(U64)); *_t564 = U64_mul(lo, self->key_size);
        void *_t565 = ptr_add(self->key_data, DEREF(_t564));
        memcpy(_t565, key, self->key_size);
        U64_delete(_t564, &(Bool){1});
        U64 *_t566 = malloc(sizeof(U64)); *_t566 = U64_mul(lo, self->val_size);
        void *_t567 = ptr_add(self->val_data, DEREF(_t566));
        memcpy(_t567, val, self->val_size);
        U64_delete(_t566, &(Bool){1});
        free(key);
        free(val);
        U64 _t568 = 1;
        U64 _t569 = U64_add(self->count, _t568);
        ;
        self->count = _t569;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    Bool _t596; { Bool *_hp = Str_is_empty(&self->key_type); _t596 = *_hp; free(_hp); }
    Bool _t597 = Bool_not(_t596);
    ;
    if (_t597) {
        {
            U64 _fi570 = 0;
            while (1) {
                U64 _t572 = 0;
                Range *_t573 = Range_new(_t572, self->count);
                ;
                U64 _t574; { U64 *_hp = Range_len(_t573); _t574 = *_hp; free(_hp); }
                Range_delete(_t573, &(Bool){1});
                Bool _wcond571; { Bool *_hp = U64_lt(&(U64){_fi570}, &(U64){_t574}); _wcond571 = *_hp; free(_hp); }
                ;
                if (_wcond571) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t575 = 0;
                Range *_t576 = Range_new(_t575, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t576, _fi570); i = *_hp; free(_hp); }
                Range_delete(_t576, &(Bool){1});
                U64 _t577 = 1;
                U64 _t578 = U64_add(_fi570, _t577);
                ;
                _fi570 = _t578;
                ;
                U64 *_t579 = malloc(sizeof(U64)); *_t579 = U64_mul(i, self->key_size);
                ;
                void *_t580 = ptr_add(self->key_data, DEREF(_t579));
                Bool _t581 = 0;
                dyn_call_delete(&self->key_type, _t580, &(Bool){_t581});
                U64_delete(_t579, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t598; { Bool *_hp = Str_is_empty(&self->val_type); _t598 = *_hp; free(_hp); }
    Bool _t599 = Bool_not(_t598);
    ;
    if (_t599) {
        {
            U64 _fi582 = 0;
            while (1) {
                U64 _t584 = 0;
                Range *_t585 = Range_new(_t584, self->count);
                ;
                U64 _t586; { U64 *_hp = Range_len(_t585); _t586 = *_hp; free(_hp); }
                Range_delete(_t585, &(Bool){1});
                Bool _wcond583; { Bool *_hp = U64_lt(&(U64){_fi582}, &(U64){_t586}); _wcond583 = *_hp; free(_hp); }
                ;
                if (_wcond583) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t587 = 0;
                Range *_t588 = Range_new(_t587, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t588, _fi582); i = *_hp; free(_hp); }
                Range_delete(_t588, &(Bool){1});
                U64 _t589 = 1;
                U64 _t590 = U64_add(_fi582, _t589);
                ;
                _fi582 = _t590;
                ;
                U64 *_t591 = malloc(sizeof(U64)); *_t591 = U64_mul(i, self->val_size);
                ;
                void *_t592 = ptr_add(self->val_data, DEREF(_t591));
                Bool _t593 = 0;
                dyn_call_delete(&self->val_type, _t592, &(Bool){_t593});
                U64_delete(_t591, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t600; { Bool *_hp = Str_is_empty(&self->key_type); _t600 = *_hp; free(_hp); }
    Bool _t601 = Bool_not(_t600);
    ;
    if (_t601) {
        Bool _t594 = 0;
        Str_delete(&self->key_type, &(Bool){_t594});
        ;
    }
    ;
    Bool _t602; { Bool *_hp = Str_is_empty(&self->val_type); _t602 = *_hp; free(_hp); }
    Bool _t603 = Bool_not(_t602);
    ;
    if (_t603) {
        Bool _t595 = 0;
        Str_delete(&self->val_type, &(Bool){_t595});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t621 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(_t621);
    ;
    U64 _t622 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(_t622);
    ;
    {
        U64 _fi604 = 0;
        while (1) {
            U64 _t606 = 0;
            Range *_t607 = Range_new(_t606, self->count);
            ;
            U64 _t608; { U64 *_hp = Range_len(_t607); _t608 = *_hp; free(_hp); }
            Range_delete(_t607, &(Bool){1});
            Bool _wcond605; { Bool *_hp = U64_lt(&(U64){_fi604}, &(U64){_t608}); _wcond605 = *_hp; free(_hp); }
            ;
            if (_wcond605) {
            } else {
                ;
                break;
            }
            ;
            U64 _t609 = 0;
            Range *_t610 = Range_new(_t609, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t610, _fi604); i = *_hp; free(_hp); }
            Range_delete(_t610, &(Bool){1});
            U64 _t611 = 1;
            U64 _t612 = U64_add(_fi604, _t611);
            ;
            _fi604 = _t612;
            ;
            U64 *_t613 = malloc(sizeof(U64)); *_t613 = U64_mul(i, self->key_size);
            void *_t614 = ptr_add(self->key_data, DEREF(_t613));
            void *ck = dyn_call_clone(&self->key_type, _t614);
            U64_delete(_t613, &(Bool){1});
            U64 *_t615 = malloc(sizeof(U64)); *_t615 = U64_mul(i, self->key_size);
            void *_t616 = ptr_add(new_keys, DEREF(_t615));
            memcpy(_t616, ck, self->key_size);
            U64_delete(_t615, &(Bool){1});
            free(ck);
            U64 *_t617 = malloc(sizeof(U64)); *_t617 = U64_mul(i, self->val_size);
            void *_t618 = ptr_add(self->val_data, DEREF(_t617));
            void *cv = dyn_call_clone(&self->val_type, _t618);
            U64_delete(_t617, &(Bool){1});
            U64 *_t619 = malloc(sizeof(U64)); *_t619 = U64_mul(i, self->val_size);
            ;
            void *_t620 = ptr_add(new_vals, DEREF(_t619));
            memcpy(_t620, cv, self->val_size);
            U64_delete(_t619, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t623 = malloc(sizeof(Map));
    _t623->key_data = new_keys;
    _t623->val_data = new_vals;
    _t623->count = self->count;
    _t623->cap = self->cap;
    _t623->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t623->key_type = *_ca; free(_ca); }
    _t623->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t623->val_type = *_ca; free(_ca); }
    return _t623;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    Bool _t637; { Bool *_hp = Str_is_empty(elem_type); _t637 = *_hp; free(_hp); }
    Bool _t638 = Bool_not(_t637);
    ;
    if (_t638) {
        Bool _t635 = dyn_has_cmp(elem_type);
        Bool _t636 = Bool_not(_t635);
        ;
        if (_t636) {
            Str *_t625 = Str_lit("Str", 3ULL);
            U64 _t626; { U64 *_hp = Str_size(); _t626 = *_hp; free(_hp); }
            U64 _t627 = 3;
            Array *_va14 = Array_new(_t625, &(U64){_t626}, &(U64){_t627});
            Str_delete(_t625, &(Bool){1});
            ;
            ;
            U64 _t628 = 0;
            Str *_t629 = Str_lit("type ", 5ULL);
            Array_set(_va14, &(U64){_t628}, _t629);
            ;
            U64 _t630 = 1;
            Str *_t631 = Str_clone(elem_type);
            Array_set(_va14, &(U64){_t630}, _t631);
            ;
            U64 _t632 = 2;
            Str *_t633 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va14, &(U64){_t632}, _t633);
            ;
            Str *_t634 = Str_lit("Set.new", 7ULL);
            panic(_t634, _va14);
            Str_delete(_t634, &(Bool){1});
        }
        ;
    }
    ;
    void *_t639 = malloc(DEREF(elem_size));
    U64 _t640 = 0;
    I64 _t641 = 1;
    U64 _t642 = U64_clone(elem_size);
    Set *_t643 = malloc(sizeof(Set));
    _t643->data = _t639;
    _t643->count = _t640;
    _t643->cap = _t641;
    _t643->elem_size = _t642;
    { Str *_ca = Str_clone(elem_type); _t643->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t643;
}

U64 * Set_len(Set * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Set_has(Set * self, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond644; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond644 = *_hp; free(_hp); }
        if (_wcond644) {
        } else {
            ;
            break;
        }
        ;
        U64 _t651 = U64_sub(hi, lo);
        U64 _t652 = 2;
        U64 _t653 = U64_div(_t651, _t652);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t653);
        ;
        U64 *_t654 = malloc(sizeof(U64)); *_t654 = U64_mul(DEREF(mid), self->elem_size);
        void *_t655 = ptr_add(self->data, DEREF(_t654));
        I64 *c = dyn_call_cmp(&self->elem_type, _t655, val);
        U64_delete(_t654, &(Bool){1});
        I64 _t656 = 0;
        Bool _t657; { Bool *_hp = I64_lt(c, &(I64){_t656}); _t657 = *_hp; free(_hp); }
        ;
        if (_t657) {
            U64 _t645 = 1;
            U64 _t646 = U64_add(DEREF(mid), _t645);
            ;
            lo = _t646;
            ;
        } else {
            I64 _t649 = 0;
            Bool _t650; { Bool *_hp = I64_gt(c, &(I64){_t649}); _t650 = *_hp; free(_hp); }
            ;
            if (_t650) {
                U64 _t647 = U64_clone(mid);
                hi = _t647;
                ;
            } else {
                Bool _t648 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t648; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t658 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t658; return _r; }
}

void Set_add(Set * self, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond659; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond659 = *_hp; free(_hp); }
        if (_wcond659) {
        } else {
            ;
            break;
        }
        ;
        U64 _t668 = U64_sub(hi, lo);
        U64 _t669 = 2;
        U64 _t670 = U64_div(_t668, _t669);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t670);
        ;
        U64 *_t671 = malloc(sizeof(U64)); *_t671 = U64_mul(DEREF(mid), self->elem_size);
        void *_t672 = ptr_add(self->data, DEREF(_t671));
        I64 *c = dyn_call_cmp(&self->elem_type, _t672, val);
        U64_delete(_t671, &(Bool){1});
        I64 _t673 = 0;
        Bool _t674; { Bool *_hp = I64_lt(c, &(I64){_t673}); _t674 = *_hp; free(_hp); }
        ;
        if (_t674) {
            U64 _t660 = 1;
            U64 _t661 = U64_add(DEREF(mid), _t660);
            ;
            lo = _t661;
            ;
        } else {
            I64 _t666 = 0;
            Bool _t667; { Bool *_hp = I64_gt(c, &(I64){_t666}); _t667 = *_hp; free(_hp); }
            ;
            if (_t667) {
                U64 _t662 = U64_clone(mid);
                hi = _t662;
                ;
            } else {
                Bool _t663 = 1;
                found = _t663;
                ;
                U64 _t664 = U64_clone(mid);
                lo = _t664;
                ;
                U64 _t665 = U64_clone(mid);
                hi = _t665;
                ;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    if (found) {
        Bool _t676; { Bool *_hp = Str_is_empty(&self->elem_type); _t676 = *_hp; free(_hp); }
        Bool _t677 = Bool_not(_t676);
        ;
        if (_t677) {
            Bool _t675 = 0;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t675});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t682 = U64_eq(self->count, self->cap);
        if (_t682) {
            U64 _t678 = 2;
            U64 new_cap = U64_mul(self->cap, _t678);
            ;
            U64 _t679 = U64_mul(new_cap, self->elem_size);
            void *_t680 = realloc(self->data, _t679);
            ;
            self->data = _t680;
            U64 _t681 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t681;
            ;
        }
        ;
        U64 _t683 = 1;
        U64 _t684 = U64_add(lo, _t683);
        ;
        U64 *_t685 = malloc(sizeof(U64)); *_t685 = U64_mul(_t684, self->elem_size);
        ;
        U64 *_t686 = malloc(sizeof(U64)); *_t686 = U64_mul(lo, self->elem_size);
        U64 _t687 = U64_sub(self->count, lo);
        void *_t688 = ptr_add(self->data, DEREF(_t685));
        void *_t689 = ptr_add(self->data, DEREF(_t686));
        U64 _t690 = U64_mul(_t687, self->elem_size);
        ;
        memmove(_t688, _t689, _t690);
        U64_delete(_t685, &(Bool){1});
        U64_delete(_t686, &(Bool){1});
        ;
        U64 *_t691 = malloc(sizeof(U64)); *_t691 = U64_mul(lo, self->elem_size);
        void *_t692 = ptr_add(self->data, DEREF(_t691));
        memcpy(_t692, val, self->elem_size);
        U64_delete(_t691, &(Bool){1});
        free(val);
        U64 _t693 = 1;
        U64 _t694 = U64_add(self->count, _t693);
        ;
        self->count = _t694;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    Bool _t708; { Bool *_hp = Str_is_empty(&self->elem_type); _t708 = *_hp; free(_hp); }
    Bool _t709 = Bool_not(_t708);
    ;
    if (_t709) {
        {
            U64 _fi695 = 0;
            while (1) {
                U64 _t697 = 0;
                Range *_t698 = Range_new(_t697, self->count);
                ;
                U64 _t699; { U64 *_hp = Range_len(_t698); _t699 = *_hp; free(_hp); }
                Range_delete(_t698, &(Bool){1});
                Bool _wcond696; { Bool *_hp = U64_lt(&(U64){_fi695}, &(U64){_t699}); _wcond696 = *_hp; free(_hp); }
                ;
                if (_wcond696) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t700 = 0;
                Range *_t701 = Range_new(_t700, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t701, _fi695); i = *_hp; free(_hp); }
                Range_delete(_t701, &(Bool){1});
                U64 _t702 = 1;
                U64 _t703 = U64_add(_fi695, _t702);
                ;
                _fi695 = _t703;
                ;
                U64 *_t704 = malloc(sizeof(U64)); *_t704 = U64_mul(i, self->elem_size);
                ;
                void *_t705 = ptr_add(self->data, DEREF(_t704));
                Bool _t706 = 0;
                dyn_call_delete(&self->elem_type, _t705, &(Bool){_t706});
                U64_delete(_t704, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t710; { Bool *_hp = Str_is_empty(&self->elem_type); _t710 = *_hp; free(_hp); }
    Bool _t711 = Bool_not(_t710);
    ;
    if (_t711) {
        Bool _t707 = 0;
        Str_delete(&self->elem_type, &(Bool){_t707});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t725 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t725);
    ;
    {
        U64 _fi712 = 0;
        while (1) {
            U64 _t714 = 0;
            Range *_t715 = Range_new(_t714, self->count);
            ;
            U64 _t716; { U64 *_hp = Range_len(_t715); _t716 = *_hp; free(_hp); }
            Range_delete(_t715, &(Bool){1});
            Bool _wcond713; { Bool *_hp = U64_lt(&(U64){_fi712}, &(U64){_t716}); _wcond713 = *_hp; free(_hp); }
            ;
            if (_wcond713) {
            } else {
                ;
                break;
            }
            ;
            U64 _t717 = 0;
            Range *_t718 = Range_new(_t717, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t718, _fi712); i = *_hp; free(_hp); }
            Range_delete(_t718, &(Bool){1});
            U64 _t719 = 1;
            U64 _t720 = U64_add(_fi712, _t719);
            ;
            _fi712 = _t720;
            ;
            U64 *_t721 = malloc(sizeof(U64)); *_t721 = U64_mul(i, self->elem_size);
            void *_t722 = ptr_add(self->data, DEREF(_t721));
            void *cloned = dyn_call_clone(&self->elem_type, _t722);
            U64_delete(_t721, &(Bool){1});
            U64 *_t723 = malloc(sizeof(U64)); *_t723 = U64_mul(i, self->elem_size);
            ;
            void *_t724 = ptr_add(new_data, DEREF(_t723));
            memcpy(_t724, cloned, self->elem_size);
            U64_delete(_t723, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t726 = malloc(sizeof(Set));
    _t726->data = new_data;
    _t726->count = self->count;
    _t726->cap = self->cap;
    _t726->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t726->elem_type = *_ca; free(_ca); }
    return _t726;
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
    Bool _t734; { Bool *_hp = U64_gte(i, &self->count); _t734 = *_hp; free(_hp); }
    if (_t734) {
        Str *_t728 = Str_lit("Str", 3ULL);
        U64 _t729; { U64 *_hp = Str_size(); _t729 = *_hp; free(_hp); }
        U64 _t730 = 1;
        Array *_va15 = Array_new(_t728, &(U64){_t729}, &(U64){_t730});
        Str_delete(_t728, &(Bool){1});
        ;
        ;
        U64 _t731 = 0;
        Str *_t732 = Str_lit("index out of bounds", 19ULL);
        Array_set(_va15, &(U64){_t731}, _t732);
        ;
        Str *_t733 = Str_lit("Str.get", 7ULL);
        panic(_t733, _va15);
        Str_delete(_t733, &(Bool){1});
    }
    ;
    void *_t735 = ptr_add(self->c_str, DEREF(i));
    return _t735;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 min_len = a->count;
    Bool _t741; { Bool *_hp = U64_lt(&b->count, &a->count); _t741 = *_hp; free(_hp); }
    if (_t741) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond736; { Bool *_hp = U64_lt(i, &(U64){min_len}); _wcond736 = *_hp; free(_hp); }
        if (_wcond736) {
        } else {
            ;
            break;
        }
        ;
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 _t737 = 0;
        Bool _t738; { Bool *_hp = I64_neq(c, &(I64){_t737}); _t738 = *_hp; free(_hp); }
        ;
        if (_t738) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t739 = 1;
        U64 _t740 = U64_add(DEREF(i), _t739);
        ;
        *i = _t740;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t742 = U64_cmp(a->count, b->count);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t742; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    U64 _t743 = 1;
    U64 _t744 = U64_add(DEREF(new_len), _t743);
    ;
    U8 *new_data = malloc(_t744);
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t745 = ptr_add(new_data, a->count);
    memcpy(_t745, b->c_str, b->count);
    void *_t746 = ptr_add(new_data, DEREF(new_len));
    I64 _t747 = 0;
    U64 _t748 = 1;
    memcpy(_t746, &(I64){_t747}, _t748);
    ;
    ;
    U64 _t749 = U64_clone(new_len);
    U64 _t750 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t751 = malloc(sizeof(Str));
    _t751->c_str = new_data;
    _t751->count = _t749;
    _t751->cap = _t750;
    ;
    ;
    return _t751;
}

Str * Str_with_capacity(U64 * n) {
    U64 _t752 = 1;
    U64 _t753 = U64_add(DEREF(n), _t752);
    ;
    U8 *buf = malloc(_t753);
    ;
    I64 _t754 = 0;
    U64 _t755 = 1;
    memcpy(buf, &(I64){_t754}, _t755);
    ;
    ;
    I64 _t756 = 0;
    U64 _t757 = U64_clone(n);
    Str *_t758 = malloc(sizeof(Str));
    _t758->c_str = buf;
    _t758->count = _t756;
    _t758->cap = _t757;
    ;
    ;
    return _t758;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    Bool _t771; { Bool *_hp = U64_gte(&self->cap, CAP_VIEW); _t771 = *_hp; free(_hp); }
    if (_t771) {
        Str *_t759 = Str_lit("Str", 3ULL);
        U64 _t760; { U64 *_hp = Str_size(); _t760 = *_hp; free(_hp); }
        U64 _t761 = 1;
        Array *_va16 = Array_new(_t759, &(U64){_t760}, &(U64){_t761});
        Str_delete(_t759, &(Bool){1});
        ;
        ;
        U64 _t762 = 0;
        Str *_t763 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va16, &(U64){_t762}, _t763);
        ;
        Str *_t764 = Str_lit("Str.push_str", 12ULL);
        panic(_t764, _va16);
        Str_delete(_t764, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool _t772; { Bool *_hp = U64_gt(new_len, &self->cap); _t772 = *_hp; free(_hp); }
    if (_t772) {
        Str *_t765 = Str_lit("Str", 3ULL);
        U64 _t766; { U64 *_hp = Str_size(); _t766 = *_hp; free(_hp); }
        U64 _t767 = 1;
        Array *_va17 = Array_new(_t765, &(U64){_t766}, &(U64){_t767});
        Str_delete(_t765, &(Bool){1});
        ;
        ;
        U64 _t768 = 0;
        Str *_t769 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va17, &(U64){_t768}, _t769);
        ;
        Str *_t770 = Str_lit("Str.push_str", 12ULL);
        panic(_t770, _va17);
        Str_delete(_t770, &(Bool){1});
    }
    ;
    void *_t773 = ptr_add(self->c_str, self->count);
    memcpy(_t773, s->c_str, s->count);
    U64 _t774 = U64_clone(new_len);
    self->count = _t774;
    ;
    void *_t775 = ptr_add(self->c_str, DEREF(new_len));
    I64 _t776 = 0;
    U64 _t777 = 1;
    memcpy(_t775, &(I64){_t776}, _t777);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    U64 _t778 = 1;
    U64 _t779 = U64_add(val->count, _t778);
    ;
    U8 *new_data = malloc(_t779);
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t780 = ptr_add(new_data, val->count);
    I64 _t781 = 0;
    U64 _t782 = 1;
    memcpy(_t780, &(I64){_t781}, _t782);
    ;
    ;
    Str *_t783 = malloc(sizeof(Str));
    _t783->c_str = new_data;
    _t783->count = val->count;
    _t783->cap = val->count;
    return _t783;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    Bool _t784; { Bool *_hp = U64_lt(&self->cap, CAP_VIEW); _t784 = *_hp; free(_hp); }
    if (_t784) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t785 = Str_clone(val);
    return _t785;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    U64 ln = U64_clone(n);
    Bool _t787; { Bool *_hp = U64_gt(st, &s->count); _t787 = *_hp; free(_hp); }
    if (_t787) {
        *st = s->count;
    }
    ;
    U64 _t788 = U64_add(DEREF(st), ln);
    Bool _t789; { Bool *_hp = U64_gt(&(U64){_t788}, &s->count); _t789 = *_hp; free(_hp); }
    ;
    if (_t789) {
        U64 _t786 = U64_sub(s->count, DEREF(st));
        ln = _t786;
        ;
    }
    ;
    void *_t790 = ptr_add(s->c_str, DEREF(st));
    U64 _t791 = U64_clone(&(U64){ln});
    ;
    U64 _t792 = U64_clone(CAP_VIEW);
    Str *_t793 = malloc(sizeof(Str));
    _t793->c_str = _t790;
    _t793->count = _t791;
    _t793->cap = _t792;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t793;
}

Bool * Str_contains(Str * a, Str * b) {
    U64 _t807 = 0;
    Bool _t808 = U64_eq(b->count, _t807);
    ;
    if (_t808) {
        Bool _t794 = 1;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t794; return _r; }
    }
    ;
    Bool _t809; { Bool *_hp = U64_gt(&b->count, &a->count); _t809 = *_hp; free(_hp); }
    if (_t809) {
        Bool _t795 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t795; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t804 = U64_sub(a->count, b->count);
        Bool _wcond796; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t804}); _wcond796 = *_hp; free(_hp); }
        ;
        if (_wcond796) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond797; { Bool *_hp = U64_lt(j, &b->count); _wcond797 = *_hp; free(_hp); }
            if (_wcond797) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t799 = malloc(sizeof(U64)); *_t799 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(a, _t799);
            U8 *bc = Str_get(b, j);
            Bool _t800; { Bool *_hp = U8_neq(ac, bc); _t800 = *_hp; free(_hp); }
            U64_delete(_t799, &(Bool){1});
            if (_t800) {
                Bool _t798 = 0;
                found = _t798;
                ;
            }
            ;
            U64 _t801 = 1;
            U64 _t802 = U64_add(DEREF(j), _t801);
            ;
            *j = _t802;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t803 = 1;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t803; return _r; }
        }
        ;
        U64 _t805 = 1;
        U64 _t806 = U64_add(i, _t805);
        ;
        i = _t806;
        ;
    }
    ;
    Bool _t810 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t810; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool _t817; { Bool *_hp = U64_gt(&b->count, &a->count); _t817 = *_hp; free(_hp); }
    if (_t817) {
        Bool _t811 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t811; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond812; { Bool *_hp = U64_lt(i, &b->count); _wcond812 = *_hp; free(_hp); }
        if (_wcond812) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool _t814; { Bool *_hp = U8_neq(ac, bc); _t814 = *_hp; free(_hp); }
        if (_t814) {
            Bool _t813 = 0;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t813; return _r; }
        }
        ;
        U64 _t815 = 1;
        U64 _t816 = U64_add(DEREF(i), _t815);
        ;
        *i = _t816;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t818 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t818; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool _t826; { Bool *_hp = U64_gt(&b->count, &a->count); _t826 = *_hp; free(_hp); }
    if (_t826) {
        Bool _t819 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t819; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond820; { Bool *_hp = U64_lt(i, &b->count); _wcond820 = *_hp; free(_hp); }
        if (_wcond820) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t822 = malloc(sizeof(U64)); *_t822 = U64_add(offset, DEREF(i));
        U8 *ac = Str_get(a, _t822);
        U8 *bc = Str_get(b, i);
        Bool _t823; { Bool *_hp = U8_neq(ac, bc); _t823 = *_hp; free(_hp); }
        U64_delete(_t822, &(Bool){1});
        if (_t823) {
            Bool _t821 = 0;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t821; return _r; }
        }
        ;
        U64 _t824 = 1;
        U64 _t825 = U64_add(DEREF(i), _t824);
        ;
        *i = _t825;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t827 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t827; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t828 = 0;
    Bool _t829 = U64_eq(self->count, _t828);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t829; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    U64 _t847 = 0;
    Bool _t848 = U64_eq(needle->count, _t847);
    ;
    if (_t848) {
        I64 _t830 = 0;
        I64 _t831 = 1;
        I64 _t832 = I64_sub(_t830, _t831);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t832; return _r; }
    }
    ;
    Bool _t849; { Bool *_hp = U64_gt(&needle->count, &self->count); _t849 = *_hp; free(_hp); }
    if (_t849) {
        I64 _t833 = 0;
        I64 _t834 = 1;
        I64 _t835 = I64_sub(_t833, _t834);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t835; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t844 = U64_sub(self->count, needle->count);
        Bool _wcond836; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t844}); _wcond836 = *_hp; free(_hp); }
        ;
        if (_wcond836) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond837; { Bool *_hp = U64_lt(j, &needle->count); _wcond837 = *_hp; free(_hp); }
            if (_wcond837) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t839 = malloc(sizeof(U64)); *_t839 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t839);
            U8 *bc = Str_get(needle, j);
            Bool _t840; { Bool *_hp = U8_neq(ac, bc); _t840 = *_hp; free(_hp); }
            U64_delete(_t839, &(Bool){1});
            if (_t840) {
                Bool _t838 = 0;
                found = _t838;
                ;
            }
            ;
            U64 _t841 = 1;
            U64 _t842 = U64_add(DEREF(j), _t841);
            ;
            *j = _t842;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t843 = U64_to_i64(i);
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t843; return _r; }
        }
        ;
        U64 _t845 = 1;
        U64 _t846 = U64_add(i, _t845);
        ;
        i = _t846;
        ;
    }
    ;
    I64 _t850 = 0;
    I64 _t851 = 1;
    I64 _t852 = I64_sub(_t850, _t851);
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t852; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    U64 _t870 = 0;
    Bool _t871 = U64_eq(needle->count, _t870);
    ;
    if (_t871) {
        I64 _t853 = 0;
        I64 _t854 = 1;
        I64 _t855 = I64_sub(_t853, _t854);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t855; return _r; }
    }
    ;
    Bool _t872; { Bool *_hp = U64_gt(&needle->count, &self->count); _t872 = *_hp; free(_hp); }
    if (_t872) {
        I64 _t856 = 0;
        I64 _t857 = 1;
        I64 _t858 = I64_sub(_t856, _t857);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t858; return _r; }
    }
    ;
    I64 _t873 = 0;
    I64 _t874 = 1;
    I64 last = I64_sub(_t873, _t874);
    ;
    ;
    U64 i = 0;
    while (1) {
        U64 _t867 = U64_sub(self->count, needle->count);
        Bool _wcond859; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t867}); _wcond859 = *_hp; free(_hp); }
        ;
        if (_wcond859) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond860; { Bool *_hp = U64_lt(j, &needle->count); _wcond860 = *_hp; free(_hp); }
            if (_wcond860) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t862 = malloc(sizeof(U64)); *_t862 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t862);
            U8 *bc = Str_get(needle, j);
            Bool _t863; { Bool *_hp = U8_neq(ac, bc); _t863 = *_hp; free(_hp); }
            U64_delete(_t862, &(Bool){1});
            if (_t863) {
                Bool _t861 = 0;
                found = _t861;
                ;
            }
            ;
            U64 _t864 = 1;
            U64 _t865 = U64_add(DEREF(j), _t864);
            ;
            *j = _t865;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t866 = U64_to_i64(i);
            last = _t866;
            ;
        }
        ;
        U64 _t868 = 1;
        U64 _t869 = U64_add(i, _t868);
        ;
        i = _t869;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    U64 _t890 = 0;
    Bool _t891 = U64_eq(from->count, _t890);
    ;
    if (_t891) {
        Str *_t875 = Str_clone(self);
        ;
        return _t875;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 start = 0;
    while (1) {
        U64 _t877 = U64_sub(self->count, from->count);
        Bool _wcond876; { Bool *_hp = U64_lte(&(U64){start}, &(U64){_t877}); _wcond876 = *_hp; free(_hp); }
        ;
        if (_wcond876) {
        } else {
            ;
            break;
        }
        ;
        U64 _t878 = U64_sub(self->count, start);
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t878});
        ;
        I64 pos; { I64 *_hp = Str_find(rest, from); pos = *_hp; free(_hp); }
        I64 _t879 = 0;
        I64 _t880 = 1;
        I64 _t881 = I64_sub(_t879, _t880);
        ;
        ;
        Bool _t882 = I64_eq(pos, _t881);
        ;
        if (_t882) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t883; { U64 *_hp = U64_from_i64(&(I64){pos}); _t883 = *_hp; free(_hp); }
        Str *_t884 = Str_substr(self, &(U64){start}, &(U64){_t883});
        ;
        result = Str_concat(result, _t884);
        Str_delete(_t884, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t885; { U64 *_hp = U64_from_i64(&(I64){pos}); _t885 = *_hp; free(_hp); }
        ;
        U64 _t886 = U64_add(start, _t885);
        ;
        U64 _t887 = U64_add(_t886, from->count);
        ;
        start = _t887;
        ;
    }
    Bool _t892; { Bool *_hp = U64_lt(&(U64){start}, &self->count); _t892 = *_hp; free(_hp); }
    if (_t892) {
        U64 _t888 = U64_sub(self->count, start);
        Str *_t889 = Str_substr(self, &(U64){start}, &(U64){_t888});
        ;
        result = Str_concat(result, _t889);
        Str_delete(_t889, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    U64 _t893 = 1;
    Str *_t894 = Str_substr(self, i, &(U64){_t893});
    ;
    return _t894;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    Bool _t897; { Bool *_hp = Str_starts_with(self, prefix); _t897 = *_hp; free(_hp); }
    if (_t897) {
        U64 _t895 = U64_sub(self->count, prefix->count);
        Str *_t896 = Str_substr(self, &prefix->count, &(U64){_t895});
        ;
        ;
        return _t896;
    }
    ;
    Str *_t898 = Str_clone(self);
    return _t898;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    Bool _t902; { Bool *_hp = Str_ends_with(self, suffix); _t902 = *_hp; free(_hp); }
    if (_t902) {
        U64 _t899 = 0;
        U64 _t900 = U64_sub(self->count, suffix->count);
        Str *_t901 = Str_substr(self, &(U64){_t899}, &(U64){_t900});
        ;
        ;
        ;
        return _t901;
    }
    ;
    Str *_t903 = Str_clone(self);
    return _t903;
}

Str * Str_from_byte(U8 * byte) {
    U64 _t904 = 2;
    U8 *buf = malloc(_t904);
    ;
    U64 _t905 = 1;
    memcpy(buf, byte, _t905);
    ;
    U64 *_t906 = malloc(sizeof(U64));
    *_t906 = 1;
    void *_t907 = ptr_add(buf, DEREF(_t906));
    I64 _t908 = 0;
    U64 _t909 = 1;
    memcpy(_t907, &(I64){_t908}, _t909);
    U64_delete(_t906, &(Bool){1});
    ;
    ;
    I64 _t910 = 1;
    I64 _t911 = 1;
    Str *_t912 = malloc(sizeof(Str));
    _t912->c_str = buf;
    _t912->count = _t910;
    _t912->cap = _t911;
    ;
    ;
    return _t912;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t953 = 0;
    Bool _t954 = U64_eq(self->count, _t953);
    ;
    if (_t954) {
        Str *_t913 = Str_lit("Str", 3ULL);
        U64 _t914; { U64 *_hp = Str_size(); _t914 = *_hp; free(_hp); }
        U64 _t915 = 1;
        Array *_va18 = Array_new(_t913, &(U64){_t914}, &(U64){_t915});
        Str_delete(_t913, &(Bool){1});
        ;
        ;
        U64 _t916 = 0;
        Str *_t917 = Str_lit("empty string", 12ULL);
        Array_set(_va18, &(U64){_t916}, _t917);
        ;
        Str *_t918 = Str_lit("Str.to_i64", 10ULL);
        panic(_t918, _va18);
        Str_delete(_t918, &(Bool){1});
    }
    ;
    I64 result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool neg = 0;
    U64 *_t955 = malloc(sizeof(U64));
    *_t955 = 0;
    U8 *first = Str_get(self, _t955);
    U8 _t956 = 45;
    Bool _t957 = U8_eq(DEREF(first), _t956);
    U64_delete(_t955, &(Bool){1});
    ;
    if (_t957) {
        Bool _t919 = 1;
        neg = _t919;
        ;
        I64 _t920 = 1;
        U64 _t921; { U64 *_hp = U64_from_i64(&(I64){_t920}); _t921 = *_hp; free(_hp); }
        ;
        *i = _t921;
        ;
    }
    ;
    Bool _t958 = U64_eq(DEREF(i), self->count);
    if (_t958) {
        Str *_t922 = Str_lit("Str", 3ULL);
        U64 _t923; { U64 *_hp = Str_size(); _t923 = *_hp; free(_hp); }
        U64 _t924 = 1;
        Array *_va19 = Array_new(_t922, &(U64){_t923}, &(U64){_t924});
        Str_delete(_t922, &(Bool){1});
        ;
        ;
        U64 _t925 = 0;
        Str *_t926 = Str_lit("no digits", 9ULL);
        Array_set(_va19, &(U64){_t925}, _t926);
        ;
        Str *_t927 = Str_lit("Str.to_i64", 10ULL);
        panic(_t927, _va19);
        Str_delete(_t927, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond928; { Bool *_hp = U64_lt(i, &self->count); _wcond928 = *_hp; free(_hp); }
        if (_wcond928) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        I64 _t939 = U8_to_i64(DEREF(ch));
        I64 _t940 = 48;
        I64 d = I64_sub(_t939, _t940);
        ;
        ;
        I64 _t941 = 0;
        I64 _t942 = 9;
        Bool _t943; { Bool *_hp = I64_lt(&(I64){d}, &(I64){_t941}); _t943 = *_hp; free(_hp); }
        ;
        Bool _t944; { Bool *_hp = I64_gt(&(I64){d}, &(I64){_t942}); _t944 = *_hp; free(_hp); }
        ;
        Bool _t945 = Bool_or(_t943, _t944);
        ;
        ;
        if (_t945) {
            Str *_t929 = Str_lit("Str", 3ULL);
            U64 _t930; { U64 *_hp = Str_size(); _t930 = *_hp; free(_hp); }
            U64 _t931 = 3;
            Array *_va20 = Array_new(_t929, &(U64){_t930}, &(U64){_t931});
            Str_delete(_t929, &(Bool){1});
            ;
            ;
            U64 _t932 = 0;
            Str *_t933 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va20, &(U64){_t932}, _t933);
            ;
            U64 _t934 = 1;
            Str *_t935 = Str_clone(self);
            Array_set(_va20, &(U64){_t934}, _t935);
            ;
            U64 _t936 = 2;
            Str *_t937 = Str_lit("'", 1ULL);
            Array_set(_va20, &(U64){_t936}, _t937);
            ;
            Str *_t938 = Str_lit("Str.to_i64", 10ULL);
            panic(_t938, _va20);
            Str_delete(_t938, &(Bool){1});
        }
        ;
        I64 _t946 = 10;
        I64 _t947 = I64_mul(result, _t946);
        ;
        I64 _t948 = I64_add(_t947, d);
        ;
        ;
        result = _t948;
        ;
        U64 _t949 = 1;
        U64 _t950 = U64_add(DEREF(i), _t949);
        ;
        *i = _t950;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t951 = 0;
        I64 _t952 = I64_sub(_t951, result);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t952; return _r; }
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = result; return _r; }
}

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    I64 _t960; { I64 *_hp = Str_cmp(a, b); _t960 = *_hp; free(_hp); }
    I64 _t961 = 0;
    Bool _t962 = I64_eq(_t960, _t961);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t962; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    I64 _t963 = 0;
    I64 _t964 = 1;
    I64 _t965; { I64 *_hp = Str_cmp(a, b); _t965 = *_hp; free(_hp); }
    I64 _t966 = I64_sub(_t963, _t964);
    ;
    ;
    Bool _t967 = I64_eq(_t965, _t966);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t967; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    I64 _t968; { I64 *_hp = Str_cmp(a, b); _t968 = *_hp; free(_hp); }
    I64 _t969 = 1;
    Bool _t970 = I64_eq(_t968, _t969);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t970; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    Bool _t971; { Bool *_hp = Str_eq(a, b); _t971 = *_hp; free(_hp); }
    Bool _t972 = Bool_not(_t971);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t972; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    Bool _t973; { Bool *_hp = Str_gt(a, b); _t973 = *_hp; free(_hp); }
    Bool _t974 = Bool_not(_t973);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t974; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    Bool _t975; { Bool *_hp = Str_lt(a, b); _t975 = *_hp; free(_hp); }
    Bool _t976 = Bool_not(_t975);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t976; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t977 = malloc(DEREF(elem_size));
    U64 _t978 = 0;
    I64 _t979 = 1;
    U64 _t980 = U64_clone(elem_size);
    Vec *_t981 = malloc(sizeof(Vec));
    _t981->data = _t977;
    _t981->count = _t978;
    _t981->cap = _t979;
    _t981->elem_size = _t980;
    { Str *_ca = Str_clone(elem_type); _t981->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t981;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    Bool _t986 = U64_eq(self->count, self->cap);
    if (_t986) {
        U64 _t982 = 2;
        U64 new_cap = U64_mul(self->cap, _t982);
        ;
        U64 _t983 = U64_mul(new_cap, self->elem_size);
        void *_t984 = realloc(self->data, _t983);
        ;
        self->data = _t984;
        U64 _t985 = U64_clone(&(U64){new_cap});
        ;
        self->cap = _t985;
        ;
    }
    ;
    U64 *_t987 = malloc(sizeof(U64)); *_t987 = U64_mul(self->count, self->elem_size);
    void *_t988 = ptr_add(self->data, DEREF(_t987));
    memcpy(_t988, val, self->elem_size);
    U64_delete(_t987, &(Bool){1});
    free(val);
    U64 _t989 = 1;
    U64 _t990 = U64_add(self->count, _t989);
    ;
    self->count = _t990;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    Bool _t1005; { Bool *_hp = U64_gte(i, &self->count); _t1005 = *_hp; free(_hp); }
    if (_t1005) {
        Str *_t991 = Str_lit("Str", 3ULL);
        U64 _t992; { U64 *_hp = Str_size(); _t992 = *_hp; free(_hp); }
        U64 _t993 = 5;
        Array *_va21 = Array_new(_t991, &(U64){_t992}, &(U64){_t993});
        Str_delete(_t991, &(Bool){1});
        ;
        ;
        U64 _t994 = 0;
        Str *_t995 = Str_lit("index ", 6ULL);
        Array_set(_va21, &(U64){_t994}, _t995);
        ;
        U64 _t996 = 1;
        Str *_t997 = U64_to_str(DEREF(i));
        Array_set(_va21, &(U64){_t996}, _t997);
        ;
        U64 _t998 = 2;
        Str *_t999 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va21, &(U64){_t998}, _t999);
        ;
        U64 _t1000 = 3;
        Str *_t1001 = U64_to_str(self->count);
        Array_set(_va21, &(U64){_t1000}, _t1001);
        ;
        U64 _t1002 = 4;
        Str *_t1003 = Str_lit(")", 1ULL);
        Array_set(_va21, &(U64){_t1002}, _t1003);
        ;
        Str *_t1004 = Str_lit("Vec.get", 7ULL);
        panic(_t1004, _va21);
        Str_delete(_t1004, &(Bool){1});
    }
    ;
    U64 *_t1006 = malloc(sizeof(U64)); *_t1006 = U64_mul(DEREF(i), self->elem_size);
    void *_t1007 = ptr_add(self->data, DEREF(_t1006));
    U64_delete(_t1006, &(Bool){1});
    return _t1007;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    Bool _t1021; { Bool *_hp = Str_is_empty(&self->elem_type); _t1021 = *_hp; free(_hp); }
    Bool _t1022 = Bool_not(_t1021);
    ;
    if (_t1022) {
        {
            U64 _fi1008 = 0;
            while (1) {
                U64 _t1010 = 0;
                Range *_t1011 = Range_new(_t1010, self->count);
                ;
                U64 _t1012; { U64 *_hp = Range_len(_t1011); _t1012 = *_hp; free(_hp); }
                Range_delete(_t1011, &(Bool){1});
                Bool _wcond1009; { Bool *_hp = U64_lt(&(U64){_fi1008}, &(U64){_t1012}); _wcond1009 = *_hp; free(_hp); }
                ;
                if (_wcond1009) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1013 = 0;
                Range *_t1014 = Range_new(_t1013, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t1014, _fi1008); i = *_hp; free(_hp); }
                Range_delete(_t1014, &(Bool){1});
                U64 _t1015 = 1;
                U64 _t1016 = U64_add(_fi1008, _t1015);
                ;
                _fi1008 = _t1016;
                ;
                U64 *_t1017 = malloc(sizeof(U64)); *_t1017 = U64_mul(i, self->elem_size);
                ;
                void *_t1018 = ptr_add(self->data, DEREF(_t1017));
                Bool _t1019 = 0;
                dyn_call_delete(&self->elem_type, _t1018, &(Bool){_t1019});
                U64_delete(_t1017, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1023; { Bool *_hp = Str_is_empty(&self->elem_type); _t1023 = *_hp; free(_hp); }
    Bool _t1024 = Bool_not(_t1023);
    ;
    if (_t1024) {
        Bool _t1020 = 0;
        Str_delete(&self->elem_type, &(Bool){_t1020});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1038 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t1038);
    ;
    {
        U64 _fi1025 = 0;
        while (1) {
            U64 _t1027 = 0;
            Range *_t1028 = Range_new(_t1027, self->count);
            ;
            U64 _t1029; { U64 *_hp = Range_len(_t1028); _t1029 = *_hp; free(_hp); }
            Range_delete(_t1028, &(Bool){1});
            Bool _wcond1026; { Bool *_hp = U64_lt(&(U64){_fi1025}, &(U64){_t1029}); _wcond1026 = *_hp; free(_hp); }
            ;
            if (_wcond1026) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1030 = 0;
            Range *_t1031 = Range_new(_t1030, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t1031, _fi1025); i = *_hp; free(_hp); }
            Range_delete(_t1031, &(Bool){1});
            U64 _t1032 = 1;
            U64 _t1033 = U64_add(_fi1025, _t1032);
            ;
            _fi1025 = _t1033;
            ;
            U64 *_t1034 = malloc(sizeof(U64)); *_t1034 = U64_mul(i, self->elem_size);
            void *_t1035 = ptr_add(self->data, DEREF(_t1034));
            void *cloned = dyn_call_clone(&self->elem_type, _t1035);
            U64_delete(_t1034, &(Bool){1});
            U64 *_t1036 = malloc(sizeof(U64)); *_t1036 = U64_mul(i, self->elem_size);
            ;
            void *_t1037 = ptr_add(new_data, DEREF(_t1036));
            memcpy(_t1037, cloned, self->elem_size);
            U64_delete(_t1036, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1039 = malloc(sizeof(Vec));
    _t1039->data = new_data;
    _t1039->count = self->count;
    _t1039->cap = self->cap;
    _t1039->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1039->elem_type = *_ca; free(_ca); }
    return _t1039;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t1057 = Str_lit("Str", 3ULL);
    U64 _t1058; { U64 *_hp = Str_size(); _t1058 = *_hp; free(_hp); }
    Vec *parts = Vec_new(_t1057, &(U64){_t1058});
    Str_delete(_t1057, &(Bool){1});
    ;
    U64 _t1059; { U64 *_hp = Str_len(delim); _t1059 = *_hp; free(_hp); }
    U64 _t1060 = 0;
    Bool _t1061 = U64_eq(_t1059, _t1060);
    ;
    ;
    if (_t1061) {
        Str *_t1041 = Str_clone(s);
        Vec_push(parts, _t1041);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    U64 pos = 0;
    while (1) {
        U64 _t1051; { U64 *_hp = Str_len(s); _t1051 = *_hp; free(_hp); }
        U64 _t1052; { U64 *_hp = Str_len(delim); _t1052 = *_hp; free(_hp); }
        U64 _t1053 = U64_sub(_t1051, _t1052);
        ;
        ;
        Bool _wcond1042; { Bool *_hp = U64_lte(&(U64){pos}, &(U64){_t1053}); _wcond1042 = *_hp; free(_hp); }
        ;
        if (_wcond1042) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1054; { U64 *_hp = Str_len(delim); _t1054 = *_hp; free(_hp); }
        Str *_t1055 = Str_substr(s, &(U64){pos}, &(U64){_t1054});
        ;
        Bool _t1056; { Bool *_hp = Str_eq(_t1055, delim); _t1056 = *_hp; free(_hp); }
        Str_delete(_t1055, &(Bool){1});
        if (_t1056) {
            U64 _t1043 = U64_sub(pos, start);
            Str *_t1044 = Str_substr(s, &(U64){start}, &(U64){_t1043});
            ;
            Str *_t1045 = Str_clone(_t1044);
            Str_delete(_t1044, &(Bool){1});
            Vec_push(parts, _t1045);
            U64 _t1046; { U64 *_hp = Str_len(delim); _t1046 = *_hp; free(_hp); }
            U64 _t1047 = U64_add(pos, _t1046);
            ;
            start = _t1047;
            ;
            U64 _t1048 = U64_clone(&(U64){start});
            pos = _t1048;
            ;
        } else {
            U64 _t1049 = 1;
            U64 _t1050 = U64_add(pos, _t1049);
            ;
            pos = _t1050;
            ;
        }
        ;
    }
    ;
    U64 _t1062; { U64 *_hp = Str_len(s); _t1062 = *_hp; free(_hp); }
    U64 _t1063 = U64_sub(_t1062, start);
    ;
    Str *_t1064 = Str_substr(s, &(U64){start}, &(U64){_t1063});
    ;
    ;
    Str *_t1065 = Str_clone(_t1064);
    Str_delete(_t1064, &(Bool){1});
    Vec_push(parts, _t1065);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 _t1073; { U64 *_hp = Vec_len(parts); _t1073 = *_hp; free(_hp); }
    U64 _t1074 = 0;
    Bool _t1075 = U64_eq(_t1073, _t1074);
    ;
    ;
    if (_t1075) {
        Str *_t1066 = Str_lit("", 0ULL);
        ;
        return _t1066;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t1068; { U64 *_hp = Vec_len(parts); _t1068 = *_hp; free(_hp); }
        Bool _wcond1067; { Bool *_hp = U64_lt(i, &(U64){_t1068}); _wcond1067 = *_hp; free(_hp); }
        ;
        if (_wcond1067) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1069 = 0;
        Bool _t1070; { Bool *_hp = U64_gt(i, &(U64){_t1069}); _t1070 = *_hp; free(_hp); }
        ;
        if (_t1070) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        U64 _t1071 = 1;
        U64 _t1072 = U64_add(DEREF(i), _t1071);
        ;
        *i = _t1072;
        ;
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
    Bool _t1139; { Bool *_hp = TokenType_is_Eof(self); _t1139 = *_hp; free(_hp); }
    if (_t1139) {
        Bool _t1076; { Bool *_hp = TokenType_is_Eof(other); _t1076 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1076; return _r; }
    }
    ;
    Bool _t1140; { Bool *_hp = TokenType_is_LParen(self); _t1140 = *_hp; free(_hp); }
    if (_t1140) {
        Bool _t1077; { Bool *_hp = TokenType_is_LParen(other); _t1077 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1077; return _r; }
    }
    ;
    Bool _t1141; { Bool *_hp = TokenType_is_RParen(self); _t1141 = *_hp; free(_hp); }
    if (_t1141) {
        Bool _t1078; { Bool *_hp = TokenType_is_RParen(other); _t1078 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1078; return _r; }
    }
    ;
    Bool _t1142; { Bool *_hp = TokenType_is_LBrace(self); _t1142 = *_hp; free(_hp); }
    if (_t1142) {
        Bool _t1079; { Bool *_hp = TokenType_is_LBrace(other); _t1079 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1079; return _r; }
    }
    ;
    Bool _t1143; { Bool *_hp = TokenType_is_RBrace(self); _t1143 = *_hp; free(_hp); }
    if (_t1143) {
        Bool _t1080; { Bool *_hp = TokenType_is_RBrace(other); _t1080 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1080; return _r; }
    }
    ;
    Bool _t1144; { Bool *_hp = TokenType_is_LBracket(self); _t1144 = *_hp; free(_hp); }
    if (_t1144) {
        Bool _t1081; { Bool *_hp = TokenType_is_LBracket(other); _t1081 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1081; return _r; }
    }
    ;
    Bool _t1145; { Bool *_hp = TokenType_is_RBracket(self); _t1145 = *_hp; free(_hp); }
    if (_t1145) {
        Bool _t1082; { Bool *_hp = TokenType_is_RBracket(other); _t1082 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1082; return _r; }
    }
    ;
    Bool _t1146; { Bool *_hp = TokenType_is_Comma(self); _t1146 = *_hp; free(_hp); }
    if (_t1146) {
        Bool _t1083; { Bool *_hp = TokenType_is_Comma(other); _t1083 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1083; return _r; }
    }
    ;
    Bool _t1147; { Bool *_hp = TokenType_is_Colon(self); _t1147 = *_hp; free(_hp); }
    if (_t1147) {
        Bool _t1084; { Bool *_hp = TokenType_is_Colon(other); _t1084 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1084; return _r; }
    }
    ;
    Bool _t1148; { Bool *_hp = TokenType_is_Question(self); _t1148 = *_hp; free(_hp); }
    if (_t1148) {
        Bool _t1085; { Bool *_hp = TokenType_is_Question(other); _t1085 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1085; return _r; }
    }
    ;
    Bool _t1149; { Bool *_hp = TokenType_is_Bang(self); _t1149 = *_hp; free(_hp); }
    if (_t1149) {
        Bool _t1086; { Bool *_hp = TokenType_is_Bang(other); _t1086 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1086; return _r; }
    }
    ;
    Bool _t1150; { Bool *_hp = TokenType_is_Minus(self); _t1150 = *_hp; free(_hp); }
    if (_t1150) {
        Bool _t1087; { Bool *_hp = TokenType_is_Minus(other); _t1087 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1087; return _r; }
    }
    ;
    Bool _t1151; { Bool *_hp = TokenType_is_Plus(self); _t1151 = *_hp; free(_hp); }
    if (_t1151) {
        Bool _t1088; { Bool *_hp = TokenType_is_Plus(other); _t1088 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1088; return _r; }
    }
    ;
    Bool _t1152; { Bool *_hp = TokenType_is_Star(self); _t1152 = *_hp; free(_hp); }
    if (_t1152) {
        Bool _t1089; { Bool *_hp = TokenType_is_Star(other); _t1089 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1089; return _r; }
    }
    ;
    Bool _t1153; { Bool *_hp = TokenType_is_Slash(self); _t1153 = *_hp; free(_hp); }
    if (_t1153) {
        Bool _t1090; { Bool *_hp = TokenType_is_Slash(other); _t1090 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1090; return _r; }
    }
    ;
    Bool _t1154; { Bool *_hp = TokenType_is_Dot(self); _t1154 = *_hp; free(_hp); }
    if (_t1154) {
        Bool _t1091; { Bool *_hp = TokenType_is_Dot(other); _t1091 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1091; return _r; }
    }
    ;
    Bool _t1155; { Bool *_hp = TokenType_is_DotDot(self); _t1155 = *_hp; free(_hp); }
    if (_t1155) {
        Bool _t1092; { Bool *_hp = TokenType_is_DotDot(other); _t1092 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1092; return _r; }
    }
    ;
    Bool _t1156; { Bool *_hp = TokenType_is_Eq(self); _t1156 = *_hp; free(_hp); }
    if (_t1156) {
        Bool _t1093; { Bool *_hp = TokenType_is_Eq(other); _t1093 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1093; return _r; }
    }
    ;
    Bool _t1157; { Bool *_hp = TokenType_is_EqEq(self); _t1157 = *_hp; free(_hp); }
    if (_t1157) {
        Bool _t1094; { Bool *_hp = TokenType_is_EqEq(other); _t1094 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1094; return _r; }
    }
    ;
    Bool _t1158; { Bool *_hp = TokenType_is_Neq(self); _t1158 = *_hp; free(_hp); }
    if (_t1158) {
        Bool _t1095; { Bool *_hp = TokenType_is_Neq(other); _t1095 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1095; return _r; }
    }
    ;
    Bool _t1159; { Bool *_hp = TokenType_is_Lt(self); _t1159 = *_hp; free(_hp); }
    if (_t1159) {
        Bool _t1096; { Bool *_hp = TokenType_is_Lt(other); _t1096 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1096; return _r; }
    }
    ;
    Bool _t1160; { Bool *_hp = TokenType_is_LtEq(self); _t1160 = *_hp; free(_hp); }
    if (_t1160) {
        Bool _t1097; { Bool *_hp = TokenType_is_LtEq(other); _t1097 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1097; return _r; }
    }
    ;
    Bool _t1161; { Bool *_hp = TokenType_is_Gt(self); _t1161 = *_hp; free(_hp); }
    if (_t1161) {
        Bool _t1098; { Bool *_hp = TokenType_is_Gt(other); _t1098 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1098; return _r; }
    }
    ;
    Bool _t1162; { Bool *_hp = TokenType_is_GtEq(self); _t1162 = *_hp; free(_hp); }
    if (_t1162) {
        Bool _t1099; { Bool *_hp = TokenType_is_GtEq(other); _t1099 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1099; return _r; }
    }
    ;
    Bool _t1163; { Bool *_hp = TokenType_is_ColonEq(self); _t1163 = *_hp; free(_hp); }
    if (_t1163) {
        Bool _t1100; { Bool *_hp = TokenType_is_ColonEq(other); _t1100 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1100; return _r; }
    }
    ;
    Bool _t1164; { Bool *_hp = TokenType_is_Ident(self); _t1164 = *_hp; free(_hp); }
    if (_t1164) {
        Bool _t1101; { Bool *_hp = TokenType_is_Ident(other); _t1101 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1101; return _r; }
    }
    ;
    Bool _t1165; { Bool *_hp = TokenType_is_StringTok(self); _t1165 = *_hp; free(_hp); }
    if (_t1165) {
        Bool _t1102; { Bool *_hp = TokenType_is_StringTok(other); _t1102 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1102; return _r; }
    }
    ;
    Bool _t1166; { Bool *_hp = TokenType_is_Number(self); _t1166 = *_hp; free(_hp); }
    if (_t1166) {
        Bool _t1103; { Bool *_hp = TokenType_is_Number(other); _t1103 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1103; return _r; }
    }
    ;
    Bool _t1167; { Bool *_hp = TokenType_is_Char(self); _t1167 = *_hp; free(_hp); }
    if (_t1167) {
        Bool _t1104; { Bool *_hp = TokenType_is_Char(other); _t1104 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1104; return _r; }
    }
    ;
    Bool _t1168; { Bool *_hp = TokenType_is_KwMode(self); _t1168 = *_hp; free(_hp); }
    if (_t1168) {
        Bool _t1105; { Bool *_hp = TokenType_is_KwMode(other); _t1105 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1105; return _r; }
    }
    ;
    Bool _t1169; { Bool *_hp = TokenType_is_KwMut(self); _t1169 = *_hp; free(_hp); }
    if (_t1169) {
        Bool _t1106; { Bool *_hp = TokenType_is_KwMut(other); _t1106 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1106; return _r; }
    }
    ;
    Bool _t1170; { Bool *_hp = TokenType_is_KwOwn(self); _t1170 = *_hp; free(_hp); }
    if (_t1170) {
        Bool _t1107; { Bool *_hp = TokenType_is_KwOwn(other); _t1107 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1107; return _r; }
    }
    ;
    Bool _t1171; { Bool *_hp = TokenType_is_KwRef(self); _t1171 = *_hp; free(_hp); }
    if (_t1171) {
        Bool _t1108; { Bool *_hp = TokenType_is_KwRef(other); _t1108 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1108; return _r; }
    }
    ;
    Bool _t1172; { Bool *_hp = TokenType_is_KwStruct(self); _t1172 = *_hp; free(_hp); }
    if (_t1172) {
        Bool _t1109; { Bool *_hp = TokenType_is_KwStruct(other); _t1109 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1109; return _r; }
    }
    ;
    Bool _t1173; { Bool *_hp = TokenType_is_KwExtStruct(self); _t1173 = *_hp; free(_hp); }
    if (_t1173) {
        Bool _t1110; { Bool *_hp = TokenType_is_KwExtStruct(other); _t1110 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1110; return _r; }
    }
    ;
    Bool _t1174; { Bool *_hp = TokenType_is_KwEnum(self); _t1174 = *_hp; free(_hp); }
    if (_t1174) {
        Bool _t1111; { Bool *_hp = TokenType_is_KwEnum(other); _t1111 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1111; return _r; }
    }
    ;
    Bool _t1175; { Bool *_hp = TokenType_is_KwNamespace(self); _t1175 = *_hp; free(_hp); }
    if (_t1175) {
        Bool _t1112; { Bool *_hp = TokenType_is_KwNamespace(other); _t1112 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1112; return _r; }
    }
    ;
    Bool _t1176; { Bool *_hp = TokenType_is_KwFunc(self); _t1176 = *_hp; free(_hp); }
    if (_t1176) {
        Bool _t1113; { Bool *_hp = TokenType_is_KwFunc(other); _t1113 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1113; return _r; }
    }
    ;
    Bool _t1177; { Bool *_hp = TokenType_is_KwProc(self); _t1177 = *_hp; free(_hp); }
    if (_t1177) {
        Bool _t1114; { Bool *_hp = TokenType_is_KwProc(other); _t1114 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1114; return _r; }
    }
    ;
    Bool _t1178; { Bool *_hp = TokenType_is_KwTest(self); _t1178 = *_hp; free(_hp); }
    if (_t1178) {
        Bool _t1115; { Bool *_hp = TokenType_is_KwTest(other); _t1115 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1115; return _r; }
    }
    ;
    Bool _t1179; { Bool *_hp = TokenType_is_KwMacro(self); _t1179 = *_hp; free(_hp); }
    if (_t1179) {
        Bool _t1116; { Bool *_hp = TokenType_is_KwMacro(other); _t1116 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1116; return _r; }
    }
    ;
    Bool _t1180; { Bool *_hp = TokenType_is_KwExtFunc(self); _t1180 = *_hp; free(_hp); }
    if (_t1180) {
        Bool _t1117; { Bool *_hp = TokenType_is_KwExtFunc(other); _t1117 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1117; return _r; }
    }
    ;
    Bool _t1181; { Bool *_hp = TokenType_is_KwExtProc(self); _t1181 = *_hp; free(_hp); }
    if (_t1181) {
        Bool _t1118; { Bool *_hp = TokenType_is_KwExtProc(other); _t1118 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1118; return _r; }
    }
    ;
    Bool _t1182; { Bool *_hp = TokenType_is_KwReturns(self); _t1182 = *_hp; free(_hp); }
    if (_t1182) {
        Bool _t1119; { Bool *_hp = TokenType_is_KwReturns(other); _t1119 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1119; return _r; }
    }
    ;
    Bool _t1183; { Bool *_hp = TokenType_is_KwThrows(self); _t1183 = *_hp; free(_hp); }
    if (_t1183) {
        Bool _t1120; { Bool *_hp = TokenType_is_KwThrows(other); _t1120 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1120; return _r; }
    }
    ;
    Bool _t1184; { Bool *_hp = TokenType_is_KwIf(self); _t1184 = *_hp; free(_hp); }
    if (_t1184) {
        Bool _t1121; { Bool *_hp = TokenType_is_KwIf(other); _t1121 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1121; return _r; }
    }
    ;
    Bool _t1185; { Bool *_hp = TokenType_is_KwElse(self); _t1185 = *_hp; free(_hp); }
    if (_t1185) {
        Bool _t1122; { Bool *_hp = TokenType_is_KwElse(other); _t1122 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1122; return _r; }
    }
    ;
    Bool _t1186; { Bool *_hp = TokenType_is_KwWhile(self); _t1186 = *_hp; free(_hp); }
    if (_t1186) {
        Bool _t1123; { Bool *_hp = TokenType_is_KwWhile(other); _t1123 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1123; return _r; }
    }
    ;
    Bool _t1187; { Bool *_hp = TokenType_is_KwFor(self); _t1187 = *_hp; free(_hp); }
    if (_t1187) {
        Bool _t1124; { Bool *_hp = TokenType_is_KwFor(other); _t1124 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1124; return _r; }
    }
    ;
    Bool _t1188; { Bool *_hp = TokenType_is_KwIn(self); _t1188 = *_hp; free(_hp); }
    if (_t1188) {
        Bool _t1125; { Bool *_hp = TokenType_is_KwIn(other); _t1125 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1125; return _r; }
    }
    ;
    Bool _t1189; { Bool *_hp = TokenType_is_KwSwitch(self); _t1189 = *_hp; free(_hp); }
    if (_t1189) {
        Bool _t1126; { Bool *_hp = TokenType_is_KwSwitch(other); _t1126 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1126; return _r; }
    }
    ;
    Bool _t1190; { Bool *_hp = TokenType_is_KwMatch(self); _t1190 = *_hp; free(_hp); }
    if (_t1190) {
        Bool _t1127; { Bool *_hp = TokenType_is_KwMatch(other); _t1127 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1127; return _r; }
    }
    ;
    Bool _t1191; { Bool *_hp = TokenType_is_KwCase(self); _t1191 = *_hp; free(_hp); }
    if (_t1191) {
        Bool _t1128; { Bool *_hp = TokenType_is_KwCase(other); _t1128 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1128; return _r; }
    }
    ;
    Bool _t1192; { Bool *_hp = TokenType_is_KwDefault(self); _t1192 = *_hp; free(_hp); }
    if (_t1192) {
        Bool _t1129; { Bool *_hp = TokenType_is_KwDefault(other); _t1129 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1129; return _r; }
    }
    ;
    Bool _t1193; { Bool *_hp = TokenType_is_KwReturn(self); _t1193 = *_hp; free(_hp); }
    if (_t1193) {
        Bool _t1130; { Bool *_hp = TokenType_is_KwReturn(other); _t1130 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1130; return _r; }
    }
    ;
    Bool _t1194; { Bool *_hp = TokenType_is_KwThrow(self); _t1194 = *_hp; free(_hp); }
    if (_t1194) {
        Bool _t1131; { Bool *_hp = TokenType_is_KwThrow(other); _t1131 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1131; return _r; }
    }
    ;
    Bool _t1195; { Bool *_hp = TokenType_is_KwCatch(self); _t1195 = *_hp; free(_hp); }
    if (_t1195) {
        Bool _t1132; { Bool *_hp = TokenType_is_KwCatch(other); _t1132 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1132; return _r; }
    }
    ;
    Bool _t1196; { Bool *_hp = TokenType_is_KwBreak(self); _t1196 = *_hp; free(_hp); }
    if (_t1196) {
        Bool _t1133; { Bool *_hp = TokenType_is_KwBreak(other); _t1133 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1133; return _r; }
    }
    ;
    Bool _t1197; { Bool *_hp = TokenType_is_KwContinue(self); _t1197 = *_hp; free(_hp); }
    if (_t1197) {
        Bool _t1134; { Bool *_hp = TokenType_is_KwContinue(other); _t1134 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1134; return _r; }
    }
    ;
    Bool _t1198; { Bool *_hp = TokenType_is_KwDefer(self); _t1198 = *_hp; free(_hp); }
    if (_t1198) {
        Bool _t1135; { Bool *_hp = TokenType_is_KwDefer(other); _t1135 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1135; return _r; }
    }
    ;
    Bool _t1199; { Bool *_hp = TokenType_is_KwTrue(self); _t1199 = *_hp; free(_hp); }
    if (_t1199) {
        Bool _t1136; { Bool *_hp = TokenType_is_KwTrue(other); _t1136 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1136; return _r; }
    }
    ;
    Bool _t1200; { Bool *_hp = TokenType_is_KwFalse(self); _t1200 = *_hp; free(_hp); }
    if (_t1200) {
        Bool _t1137; { Bool *_hp = TokenType_is_KwFalse(other); _t1137 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1137; return _r; }
    }
    ;
    Bool _t1201; { Bool *_hp = TokenType_is_Error(self); _t1201 = *_hp; free(_hp); }
    if (_t1201) {
        Bool _t1138; { Bool *_hp = TokenType_is_Error(other); _t1138 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1138; return _r; }
    }
    ;
    Bool _t1202 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1202; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1203; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1203 = *_hp; free(_hp); }
    if (_t1203) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1204; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1204 = *_hp; free(_hp); }
    if (_t1204) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1205; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1205 = *_hp; free(_hp); }
    if (_t1205) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1206; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1206 = *_hp; free(_hp); }
    if (_t1206) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1207; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1207 = *_hp; free(_hp); }
    if (_t1207) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1208; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1208 = *_hp; free(_hp); }
    if (_t1208) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1209; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1209 = *_hp; free(_hp); }
    if (_t1209) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1210; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1210 = *_hp; free(_hp); }
    if (_t1210) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1211; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1211 = *_hp; free(_hp); }
    if (_t1211) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1212; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1212 = *_hp; free(_hp); }
    if (_t1212) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1213; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1213 = *_hp; free(_hp); }
    if (_t1213) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1214; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1214 = *_hp; free(_hp); }
    if (_t1214) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1215; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1215 = *_hp; free(_hp); }
    if (_t1215) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1216; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1216 = *_hp; free(_hp); }
    if (_t1216) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1217; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1217 = *_hp; free(_hp); }
    if (_t1217) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1218; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1218 = *_hp; free(_hp); }
    if (_t1218) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1219; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1219 = *_hp; free(_hp); }
    if (_t1219) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1220; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1220 = *_hp; free(_hp); }
    if (_t1220) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1221; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1221 = *_hp; free(_hp); }
    if (_t1221) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1222; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1222 = *_hp; free(_hp); }
    if (_t1222) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1223; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1223 = *_hp; free(_hp); }
    if (_t1223) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1224; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1224 = *_hp; free(_hp); }
    if (_t1224) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1225; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1225 = *_hp; free(_hp); }
    if (_t1225) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1226; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1226 = *_hp; free(_hp); }
    if (_t1226) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1227; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1227 = *_hp; free(_hp); }
    if (_t1227) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1228; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1228 = *_hp; free(_hp); }
    if (_t1228) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1229; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1229 = *_hp; free(_hp); }
    if (_t1229) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1230; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1230 = *_hp; free(_hp); }
    if (_t1230) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1231; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1231 = *_hp; free(_hp); }
    if (_t1231) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1232; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1232 = *_hp; free(_hp); }
    if (_t1232) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1233; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1233 = *_hp; free(_hp); }
    if (_t1233) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1234; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1234 = *_hp; free(_hp); }
    if (_t1234) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1235; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1235 = *_hp; free(_hp); }
    if (_t1235) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1236; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1236 = *_hp; free(_hp); }
    if (_t1236) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1237; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1237 = *_hp; free(_hp); }
    if (_t1237) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1238; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1238 = *_hp; free(_hp); }
    if (_t1238) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1239; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1239 = *_hp; free(_hp); }
    if (_t1239) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1240; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1240 = *_hp; free(_hp); }
    if (_t1240) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1241; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1241 = *_hp; free(_hp); }
    if (_t1241) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1242; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1242 = *_hp; free(_hp); }
    if (_t1242) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1243; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1243 = *_hp; free(_hp); }
    if (_t1243) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1244; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1244 = *_hp; free(_hp); }
    if (_t1244) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1245; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1245 = *_hp; free(_hp); }
    if (_t1245) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1246; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1246 = *_hp; free(_hp); }
    if (_t1246) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1247; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1247 = *_hp; free(_hp); }
    if (_t1247) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1248; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1248 = *_hp; free(_hp); }
    if (_t1248) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1249; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1249 = *_hp; free(_hp); }
    if (_t1249) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1250; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1250 = *_hp; free(_hp); }
    if (_t1250) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1251; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1251 = *_hp; free(_hp); }
    if (_t1251) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1252; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1252 = *_hp; free(_hp); }
    if (_t1252) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1253; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1253 = *_hp; free(_hp); }
    if (_t1253) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1254; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1254 = *_hp; free(_hp); }
    if (_t1254) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1255; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1255 = *_hp; free(_hp); }
    if (_t1255) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1256; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1256 = *_hp; free(_hp); }
    if (_t1256) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1257; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1257 = *_hp; free(_hp); }
    if (_t1257) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1258; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1258 = *_hp; free(_hp); }
    if (_t1258) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1259; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1259 = *_hp; free(_hp); }
    if (_t1259) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1260; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1260 = *_hp; free(_hp); }
    if (_t1260) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1261; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1261 = *_hp; free(_hp); }
    if (_t1261) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1262; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1262 = *_hp; free(_hp); }
    if (_t1262) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1263; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1263 = *_hp; free(_hp); }
    if (_t1263) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1264; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1264 = *_hp; free(_hp); }
    if (_t1264) {
        ;
        return TokenType_KwFalse();
    }
    ;
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
    Bool _t1328; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1328 = *_hp; free(_hp); }
    if (_t1328) {
        Str *_t1265 = Str_lit("Eof", 3ULL);
        ;
        return _t1265;
    }
    ;
    Bool _t1329; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1329 = *_hp; free(_hp); }
    if (_t1329) {
        Str *_t1266 = Str_lit("LParen", 6ULL);
        ;
        return _t1266;
    }
    ;
    Bool _t1330; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1330 = *_hp; free(_hp); }
    if (_t1330) {
        Str *_t1267 = Str_lit("RParen", 6ULL);
        ;
        return _t1267;
    }
    ;
    Bool _t1331; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1331 = *_hp; free(_hp); }
    if (_t1331) {
        Str *_t1268 = Str_lit("LBrace", 6ULL);
        ;
        return _t1268;
    }
    ;
    Bool _t1332; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1332 = *_hp; free(_hp); }
    if (_t1332) {
        Str *_t1269 = Str_lit("RBrace", 6ULL);
        ;
        return _t1269;
    }
    ;
    Bool _t1333; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1333 = *_hp; free(_hp); }
    if (_t1333) {
        Str *_t1270 = Str_lit("LBracket", 8ULL);
        ;
        return _t1270;
    }
    ;
    Bool _t1334; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1334 = *_hp; free(_hp); }
    if (_t1334) {
        Str *_t1271 = Str_lit("RBracket", 8ULL);
        ;
        return _t1271;
    }
    ;
    Bool _t1335; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1335 = *_hp; free(_hp); }
    if (_t1335) {
        Str *_t1272 = Str_lit("Comma", 5ULL);
        ;
        return _t1272;
    }
    ;
    Bool _t1336; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1336 = *_hp; free(_hp); }
    if (_t1336) {
        Str *_t1273 = Str_lit("Colon", 5ULL);
        ;
        return _t1273;
    }
    ;
    Bool _t1337; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1337 = *_hp; free(_hp); }
    if (_t1337) {
        Str *_t1274 = Str_lit("Question", 8ULL);
        ;
        return _t1274;
    }
    ;
    Bool _t1338; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1338 = *_hp; free(_hp); }
    if (_t1338) {
        Str *_t1275 = Str_lit("Bang", 4ULL);
        ;
        return _t1275;
    }
    ;
    Bool _t1339; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1339 = *_hp; free(_hp); }
    if (_t1339) {
        Str *_t1276 = Str_lit("Minus", 5ULL);
        ;
        return _t1276;
    }
    ;
    Bool _t1340; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1340 = *_hp; free(_hp); }
    if (_t1340) {
        Str *_t1277 = Str_lit("Plus", 4ULL);
        ;
        return _t1277;
    }
    ;
    Bool _t1341; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1341 = *_hp; free(_hp); }
    if (_t1341) {
        Str *_t1278 = Str_lit("Star", 4ULL);
        ;
        return _t1278;
    }
    ;
    Bool _t1342; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1342 = *_hp; free(_hp); }
    if (_t1342) {
        Str *_t1279 = Str_lit("Slash", 5ULL);
        ;
        return _t1279;
    }
    ;
    Bool _t1343; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1343 = *_hp; free(_hp); }
    if (_t1343) {
        Str *_t1280 = Str_lit("Dot", 3ULL);
        ;
        return _t1280;
    }
    ;
    Bool _t1344; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1344 = *_hp; free(_hp); }
    if (_t1344) {
        Str *_t1281 = Str_lit("DotDot", 6ULL);
        ;
        return _t1281;
    }
    ;
    Bool _t1345; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1345 = *_hp; free(_hp); }
    if (_t1345) {
        Str *_t1282 = Str_lit("Eq", 2ULL);
        ;
        return _t1282;
    }
    ;
    Bool _t1346; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1346 = *_hp; free(_hp); }
    if (_t1346) {
        Str *_t1283 = Str_lit("EqEq", 4ULL);
        ;
        return _t1283;
    }
    ;
    Bool _t1347; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1347 = *_hp; free(_hp); }
    if (_t1347) {
        Str *_t1284 = Str_lit("Neq", 3ULL);
        ;
        return _t1284;
    }
    ;
    Bool _t1348; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1348 = *_hp; free(_hp); }
    if (_t1348) {
        Str *_t1285 = Str_lit("Lt", 2ULL);
        ;
        return _t1285;
    }
    ;
    Bool _t1349; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1349 = *_hp; free(_hp); }
    if (_t1349) {
        Str *_t1286 = Str_lit("LtEq", 4ULL);
        ;
        return _t1286;
    }
    ;
    Bool _t1350; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1350 = *_hp; free(_hp); }
    if (_t1350) {
        Str *_t1287 = Str_lit("Gt", 2ULL);
        ;
        return _t1287;
    }
    ;
    Bool _t1351; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1351 = *_hp; free(_hp); }
    if (_t1351) {
        Str *_t1288 = Str_lit("GtEq", 4ULL);
        ;
        return _t1288;
    }
    ;
    Bool _t1352; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1352 = *_hp; free(_hp); }
    if (_t1352) {
        Str *_t1289 = Str_lit("ColonEq", 7ULL);
        ;
        return _t1289;
    }
    ;
    Bool _t1353; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1353 = *_hp; free(_hp); }
    if (_t1353) {
        Str *_t1290 = Str_lit("Ident", 5ULL);
        ;
        return _t1290;
    }
    ;
    Bool _t1354; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1354 = *_hp; free(_hp); }
    if (_t1354) {
        Str *_t1291 = Str_lit("StringTok", 9ULL);
        ;
        return _t1291;
    }
    ;
    Bool _t1355; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1355 = *_hp; free(_hp); }
    if (_t1355) {
        Str *_t1292 = Str_lit("Number", 6ULL);
        ;
        return _t1292;
    }
    ;
    Bool _t1356; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1356 = *_hp; free(_hp); }
    if (_t1356) {
        Str *_t1293 = Str_lit("Char", 4ULL);
        ;
        return _t1293;
    }
    ;
    Bool _t1357; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1357 = *_hp; free(_hp); }
    if (_t1357) {
        Str *_t1294 = Str_lit("KwMode", 6ULL);
        ;
        return _t1294;
    }
    ;
    Bool _t1358; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1358 = *_hp; free(_hp); }
    if (_t1358) {
        Str *_t1295 = Str_lit("KwMut", 5ULL);
        ;
        return _t1295;
    }
    ;
    Bool _t1359; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1359 = *_hp; free(_hp); }
    if (_t1359) {
        Str *_t1296 = Str_lit("KwOwn", 5ULL);
        ;
        return _t1296;
    }
    ;
    Bool _t1360; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1360 = *_hp; free(_hp); }
    if (_t1360) {
        Str *_t1297 = Str_lit("KwRef", 5ULL);
        ;
        return _t1297;
    }
    ;
    Bool _t1361; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1361 = *_hp; free(_hp); }
    if (_t1361) {
        Str *_t1298 = Str_lit("KwStruct", 8ULL);
        ;
        return _t1298;
    }
    ;
    Bool _t1362; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1362 = *_hp; free(_hp); }
    if (_t1362) {
        Str *_t1299 = Str_lit("KwExtStruct", 11ULL);
        ;
        return _t1299;
    }
    ;
    Bool _t1363; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1363 = *_hp; free(_hp); }
    if (_t1363) {
        Str *_t1300 = Str_lit("KwEnum", 6ULL);
        ;
        return _t1300;
    }
    ;
    Bool _t1364; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1364 = *_hp; free(_hp); }
    if (_t1364) {
        Str *_t1301 = Str_lit("KwNamespace", 11ULL);
        ;
        return _t1301;
    }
    ;
    Bool _t1365; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1365 = *_hp; free(_hp); }
    if (_t1365) {
        Str *_t1302 = Str_lit("KwFunc", 6ULL);
        ;
        return _t1302;
    }
    ;
    Bool _t1366; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1366 = *_hp; free(_hp); }
    if (_t1366) {
        Str *_t1303 = Str_lit("KwProc", 6ULL);
        ;
        return _t1303;
    }
    ;
    Bool _t1367; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1367 = *_hp; free(_hp); }
    if (_t1367) {
        Str *_t1304 = Str_lit("KwTest", 6ULL);
        ;
        return _t1304;
    }
    ;
    Bool _t1368; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1368 = *_hp; free(_hp); }
    if (_t1368) {
        Str *_t1305 = Str_lit("KwMacro", 7ULL);
        ;
        return _t1305;
    }
    ;
    Bool _t1369; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1369 = *_hp; free(_hp); }
    if (_t1369) {
        Str *_t1306 = Str_lit("KwExtFunc", 9ULL);
        ;
        return _t1306;
    }
    ;
    Bool _t1370; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1370 = *_hp; free(_hp); }
    if (_t1370) {
        Str *_t1307 = Str_lit("KwExtProc", 9ULL);
        ;
        return _t1307;
    }
    ;
    Bool _t1371; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1371 = *_hp; free(_hp); }
    if (_t1371) {
        Str *_t1308 = Str_lit("KwReturns", 9ULL);
        ;
        return _t1308;
    }
    ;
    Bool _t1372; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1372 = *_hp; free(_hp); }
    if (_t1372) {
        Str *_t1309 = Str_lit("KwThrows", 8ULL);
        ;
        return _t1309;
    }
    ;
    Bool _t1373; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1373 = *_hp; free(_hp); }
    if (_t1373) {
        Str *_t1310 = Str_lit("KwIf", 4ULL);
        ;
        return _t1310;
    }
    ;
    Bool _t1374; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1374 = *_hp; free(_hp); }
    if (_t1374) {
        Str *_t1311 = Str_lit("KwElse", 6ULL);
        ;
        return _t1311;
    }
    ;
    Bool _t1375; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1375 = *_hp; free(_hp); }
    if (_t1375) {
        Str *_t1312 = Str_lit("KwWhile", 7ULL);
        ;
        return _t1312;
    }
    ;
    Bool _t1376; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1376 = *_hp; free(_hp); }
    if (_t1376) {
        Str *_t1313 = Str_lit("KwFor", 5ULL);
        ;
        return _t1313;
    }
    ;
    Bool _t1377; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1377 = *_hp; free(_hp); }
    if (_t1377) {
        Str *_t1314 = Str_lit("KwIn", 4ULL);
        ;
        return _t1314;
    }
    ;
    Bool _t1378; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1378 = *_hp; free(_hp); }
    if (_t1378) {
        Str *_t1315 = Str_lit("KwSwitch", 8ULL);
        ;
        return _t1315;
    }
    ;
    Bool _t1379; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1379 = *_hp; free(_hp); }
    if (_t1379) {
        Str *_t1316 = Str_lit("KwMatch", 7ULL);
        ;
        return _t1316;
    }
    ;
    Bool _t1380; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1380 = *_hp; free(_hp); }
    if (_t1380) {
        Str *_t1317 = Str_lit("KwCase", 6ULL);
        ;
        return _t1317;
    }
    ;
    Bool _t1381; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1381 = *_hp; free(_hp); }
    if (_t1381) {
        Str *_t1318 = Str_lit("KwDefault", 9ULL);
        ;
        return _t1318;
    }
    ;
    Bool _t1382; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1382 = *_hp; free(_hp); }
    if (_t1382) {
        Str *_t1319 = Str_lit("KwReturn", 8ULL);
        ;
        return _t1319;
    }
    ;
    Bool _t1383; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1383 = *_hp; free(_hp); }
    if (_t1383) {
        Str *_t1320 = Str_lit("KwThrow", 7ULL);
        ;
        return _t1320;
    }
    ;
    Bool _t1384; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1384 = *_hp; free(_hp); }
    if (_t1384) {
        Str *_t1321 = Str_lit("KwCatch", 7ULL);
        ;
        return _t1321;
    }
    ;
    Bool _t1385; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1385 = *_hp; free(_hp); }
    if (_t1385) {
        Str *_t1322 = Str_lit("KwBreak", 7ULL);
        ;
        return _t1322;
    }
    ;
    Bool _t1386; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1386 = *_hp; free(_hp); }
    if (_t1386) {
        Str *_t1323 = Str_lit("KwContinue", 10ULL);
        ;
        return _t1323;
    }
    ;
    Bool _t1387; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1387 = *_hp; free(_hp); }
    if (_t1387) {
        Str *_t1324 = Str_lit("KwDefer", 7ULL);
        ;
        return _t1324;
    }
    ;
    Bool _t1388; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1388 = *_hp; free(_hp); }
    if (_t1388) {
        Str *_t1325 = Str_lit("KwTrue", 6ULL);
        ;
        return _t1325;
    }
    ;
    Bool _t1389; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1389 = *_hp; free(_hp); }
    if (_t1389) {
        Str *_t1326 = Str_lit("KwFalse", 7ULL);
        ;
        return _t1326;
    }
    ;
    Bool _t1390; { Bool *_hp = TokenType_eq(self, TokenType_Error()); _t1390 = *_hp; free(_hp); }
    if (_t1390) {
        Str *_t1327 = Str_lit("Error", 5ULL);
        ;
        return _t1327;
    }
    ;
    Str *_t1391 = Str_lit("unknown", 7ULL);
    return _t1391;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1393 = I64_clone(&self->line);
    I64 _t1394 = I64_clone(&self->col);
    Token *_t1395 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1395->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1395->text = *_ca; free(_ca); }
    _t1395->line = _t1393;
    _t1395->col = _t1394;
    ;
    ;
    return _t1395;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    Bool _t1396 = 0;
    TokenType_delete(&self->type, &(Bool){_t1396});
    ;
    Bool _t1397 = 0;
    Str_delete(&self->text, &(Bool){_t1397});
    ;
    Bool _t1398 = 0;
    I64_delete(&self->line, &(Bool){_t1398});
    ;
    Bool _t1399 = 0;
    I64_delete(&self->col, &(Bool){_t1399});
    ;
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
    U8 _t1401 = 48;
    U8 _t1402 = 57;
    Bool _t1403; { Bool *_hp = U8_gte(c, &(U8){_t1401}); _t1403 = *_hp; free(_hp); }
    ;
    Bool _t1404; { Bool *_hp = U8_lte(c, &(U8){_t1402}); _t1404 = *_hp; free(_hp); }
    ;
    Bool _t1405 = Bool_and(_t1403, _t1404);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1405; return _r; }
}

Bool * is_alpha(U8 * c) {
    U8 _t1406 = 97;
    U8 _t1407 = 122;
    Bool _t1408; { Bool *_hp = U8_gte(c, &(U8){_t1406}); _t1408 = *_hp; free(_hp); }
    ;
    Bool _t1409; { Bool *_hp = U8_lte(c, &(U8){_t1407}); _t1409 = *_hp; free(_hp); }
    ;
    U8 _t1410 = 65;
    U8 _t1411 = 90;
    Bool _t1412; { Bool *_hp = U8_gte(c, &(U8){_t1410}); _t1412 = *_hp; free(_hp); }
    ;
    Bool _t1413; { Bool *_hp = U8_lte(c, &(U8){_t1411}); _t1413 = *_hp; free(_hp); }
    ;
    Bool _t1414 = Bool_and(_t1408, _t1409);
    ;
    ;
    Bool _t1415 = Bool_and(_t1412, _t1413);
    ;
    ;
    U8 _t1416 = 95;
    Bool _t1417 = Bool_or(_t1414, _t1415);
    ;
    ;
    Bool _t1418 = U8_eq(DEREF(c), _t1416);
    ;
    Bool _t1419 = Bool_or(_t1417, _t1418);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1419; return _r; }
}

Bool * is_alnum(U8 * c) {
    Bool _t1420; { Bool *_hp = is_alpha(c); _t1420 = *_hp; free(_hp); }
    Bool _t1421; { Bool *_hp = is_digit(c); _t1421 = *_hp; free(_hp); }
    Bool _t1422 = Bool_or(_t1420, _t1421);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1422; return _r; }
}

Str * tok_name(TokenType * type) {
    {
        TokenType *_sw1423 = TokenType_clone(type);
        Bool _t1550; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Eof()); _t1550 = *_hp; free(_hp); }
        if (_t1550) {
            Str *_t1424 = Str_lit("eof", 3ULL);
            TokenType_delete(_sw1423, &(Bool){1});
            ;
            return _t1424;
        } else {
            Bool _t1549; { Bool *_hp = TokenType_eq(_sw1423, TokenType_LParen()); _t1549 = *_hp; free(_hp); }
            if (_t1549) {
                Str *_t1425 = Str_lit("(", 1ULL);
                ;
                TokenType_delete(_sw1423, &(Bool){1});
                ;
                return _t1425;
            } else {
                Bool _t1548; { Bool *_hp = TokenType_eq(_sw1423, TokenType_RParen()); _t1548 = *_hp; free(_hp); }
                if (_t1548) {
                    Str *_t1426 = Str_lit(")", 1ULL);
                    ;
                    ;
                    TokenType_delete(_sw1423, &(Bool){1});
                    ;
                    return _t1426;
                } else {
                    Bool _t1547; { Bool *_hp = TokenType_eq(_sw1423, TokenType_LBrace()); _t1547 = *_hp; free(_hp); }
                    if (_t1547) {
                        Str *_t1427 = Str_lit("{", 1ULL);
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1423, &(Bool){1});
                        ;
                        return _t1427;
                    } else {
                        Bool _t1546; { Bool *_hp = TokenType_eq(_sw1423, TokenType_RBrace()); _t1546 = *_hp; free(_hp); }
                        if (_t1546) {
                            Str *_t1428 = Str_lit("}", 1ULL);
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1423, &(Bool){1});
                            ;
                            return _t1428;
                        } else {
                            Bool _t1545; { Bool *_hp = TokenType_eq(_sw1423, TokenType_LBracket()); _t1545 = *_hp; free(_hp); }
                            if (_t1545) {
                                Str *_t1429 = Str_lit("[", 1ULL);
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1423, &(Bool){1});
                                ;
                                return _t1429;
                            } else {
                                Bool _t1544; { Bool *_hp = TokenType_eq(_sw1423, TokenType_RBracket()); _t1544 = *_hp; free(_hp); }
                                if (_t1544) {
                                    Str *_t1430 = Str_lit("]", 1ULL);
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1423, &(Bool){1});
                                    ;
                                    return _t1430;
                                } else {
                                    Bool _t1543; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Comma()); _t1543 = *_hp; free(_hp); }
                                    if (_t1543) {
                                        Str *_t1431 = Str_lit(",", 1ULL);
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1423, &(Bool){1});
                                        ;
                                        return _t1431;
                                    } else {
                                        Bool _t1542; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Colon()); _t1542 = *_hp; free(_hp); }
                                        if (_t1542) {
                                            Str *_t1432 = Str_lit(":", 1ULL);
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1423, &(Bool){1});
                                            ;
                                            return _t1432;
                                        } else {
                                            Bool _t1541; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Question()); _t1541 = *_hp; free(_hp); }
                                            if (_t1541) {
                                                Str *_t1433 = Str_lit("?", 1ULL);
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1423, &(Bool){1});
                                                ;
                                                return _t1433;
                                            } else {
                                                Bool _t1540; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Bang()); _t1540 = *_hp; free(_hp); }
                                                if (_t1540) {
                                                    Str *_t1434 = Str_lit("!", 1ULL);
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                    ;
                                                    return _t1434;
                                                } else {
                                                    Bool _t1539; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Minus()); _t1539 = *_hp; free(_hp); }
                                                    if (_t1539) {
                                                        Str *_t1435 = Str_lit("-", 1ULL);
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                        ;
                                                        return _t1435;
                                                    } else {
                                                        Bool _t1538; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Plus()); _t1538 = *_hp; free(_hp); }
                                                        if (_t1538) {
                                                            Str *_t1436 = Str_lit("+", 1ULL);
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                            ;
                                                            return _t1436;
                                                        } else {
                                                            Bool _t1537; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Star()); _t1537 = *_hp; free(_hp); }
                                                            if (_t1537) {
                                                                Str *_t1437 = Str_lit("*", 1ULL);
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                ;
                                                                return _t1437;
                                                            } else {
                                                                Bool _t1536; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Slash()); _t1536 = *_hp; free(_hp); }
                                                                if (_t1536) {
                                                                    Str *_t1438 = Str_lit("/", 1ULL);
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                    ;
                                                                    return _t1438;
                                                                } else {
                                                                    Bool _t1535; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Dot()); _t1535 = *_hp; free(_hp); }
                                                                    if (_t1535) {
                                                                        Str *_t1439 = Str_lit(".", 1ULL);
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                        ;
                                                                        return _t1439;
                                                                    } else {
                                                                        Bool _t1534; { Bool *_hp = TokenType_eq(_sw1423, TokenType_DotDot()); _t1534 = *_hp; free(_hp); }
                                                                        if (_t1534) {
                                                                            Str *_t1440 = Str_lit("..", 2ULL);
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                            ;
                                                                            return _t1440;
                                                                        } else {
                                                                            Bool _t1533; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Eq()); _t1533 = *_hp; free(_hp); }
                                                                            if (_t1533) {
                                                                                Str *_t1441 = Str_lit("=", 1ULL);
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                ;
                                                                                return _t1441;
                                                                            } else {
                                                                                Bool _t1532; { Bool *_hp = TokenType_eq(_sw1423, TokenType_EqEq()); _t1532 = *_hp; free(_hp); }
                                                                                if (_t1532) {
                                                                                    Str *_t1442 = Str_lit("==", 2ULL);
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                    ;
                                                                                    return _t1442;
                                                                                } else {
                                                                                    Bool _t1531; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Neq()); _t1531 = *_hp; free(_hp); }
                                                                                    if (_t1531) {
                                                                                        Str *_t1443 = Str_lit("!=", 2ULL);
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                        ;
                                                                                        return _t1443;
                                                                                    } else {
                                                                                        Bool _t1530; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Lt()); _t1530 = *_hp; free(_hp); }
                                                                                        if (_t1530) {
                                                                                            Str *_t1444 = Str_lit("<", 1ULL);
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                            ;
                                                                                            return _t1444;
                                                                                        } else {
                                                                                            Bool _t1529; { Bool *_hp = TokenType_eq(_sw1423, TokenType_LtEq()); _t1529 = *_hp; free(_hp); }
                                                                                            if (_t1529) {
                                                                                                Str *_t1445 = Str_lit("<=", 2ULL);
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                ;
                                                                                                return _t1445;
                                                                                            } else {
                                                                                                Bool _t1528; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Gt()); _t1528 = *_hp; free(_hp); }
                                                                                                if (_t1528) {
                                                                                                    Str *_t1446 = Str_lit(">", 1ULL);
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1446;
                                                                                                } else {
                                                                                                    Bool _t1527; { Bool *_hp = TokenType_eq(_sw1423, TokenType_GtEq()); _t1527 = *_hp; free(_hp); }
                                                                                                    if (_t1527) {
                                                                                                        Str *_t1447 = Str_lit(">=", 2ULL);
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1447;
                                                                                                    } else {
                                                                                                        Bool _t1526; { Bool *_hp = TokenType_eq(_sw1423, TokenType_ColonEq()); _t1526 = *_hp; free(_hp); }
                                                                                                        if (_t1526) {
                                                                                                            Str *_t1448 = Str_lit(":=", 2ULL);
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1448;
                                                                                                        } else {
                                                                                                            Bool _t1525; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Ident()); _t1525 = *_hp; free(_hp); }
                                                                                                            if (_t1525) {
                                                                                                                Str *_t1449 = Str_lit("identifier", 10ULL);
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1449;
                                                                                                            } else {
                                                                                                                Bool _t1524; { Bool *_hp = TokenType_eq(_sw1423, TokenType_StringTok()); _t1524 = *_hp; free(_hp); }
                                                                                                                if (_t1524) {
                                                                                                                    Str *_t1450 = Str_lit("string", 6ULL);
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1450;
                                                                                                                } else {
                                                                                                                    Bool _t1523; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Number()); _t1523 = *_hp; free(_hp); }
                                                                                                                    if (_t1523) {
                                                                                                                        Str *_t1451 = Str_lit("number", 6ULL);
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1451;
                                                                                                                    } else {
                                                                                                                        Bool _t1522; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Char()); _t1522 = *_hp; free(_hp); }
                                                                                                                        if (_t1522) {
                                                                                                                            Str *_t1452 = Str_lit("char", 4ULL);
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1452;
                                                                                                                        } else {
                                                                                                                            Bool _t1521; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwMode()); _t1521 = *_hp; free(_hp); }
                                                                                                                            if (_t1521) {
                                                                                                                                Str *_t1453 = Str_lit("mode", 4ULL);
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1453;
                                                                                                                            } else {
                                                                                                                                Bool _t1520; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwMut()); _t1520 = *_hp; free(_hp); }
                                                                                                                                if (_t1520) {
                                                                                                                                    Str *_t1454 = Str_lit("mut", 3ULL);
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1454;
                                                                                                                                } else {
                                                                                                                                    Bool _t1519; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwOwn()); _t1519 = *_hp; free(_hp); }
                                                                                                                                    if (_t1519) {
                                                                                                                                        Str *_t1455 = Str_lit("own", 3ULL);
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1455;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1518; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwRef()); _t1518 = *_hp; free(_hp); }
                                                                                                                                        if (_t1518) {
                                                                                                                                            Str *_t1456 = Str_lit("ref", 3ULL);
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1456;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1517; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwStruct()); _t1517 = *_hp; free(_hp); }
                                                                                                                                            if (_t1517) {
                                                                                                                                                Str *_t1457 = Str_lit("struct", 6ULL);
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1457;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1516; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwExtStruct()); _t1516 = *_hp; free(_hp); }
                                                                                                                                                if (_t1516) {
                                                                                                                                                    Str *_t1458 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1458;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1515; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwEnum()); _t1515 = *_hp; free(_hp); }
                                                                                                                                                    if (_t1515) {
                                                                                                                                                        Str *_t1459 = Str_lit("enum", 4ULL);
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1459;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1514; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwNamespace()); _t1514 = *_hp; free(_hp); }
                                                                                                                                                        if (_t1514) {
                                                                                                                                                            Str *_t1460 = Str_lit("namespace", 9ULL);
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1460;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1513; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwFunc()); _t1513 = *_hp; free(_hp); }
                                                                                                                                                            if (_t1513) {
                                                                                                                                                                Str *_t1461 = Str_lit("func", 4ULL);
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1461;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1512; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwProc()); _t1512 = *_hp; free(_hp); }
                                                                                                                                                                if (_t1512) {
                                                                                                                                                                    Str *_t1462 = Str_lit("proc", 4ULL);
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1462;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1511; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwTest()); _t1511 = *_hp; free(_hp); }
                                                                                                                                                                    if (_t1511) {
                                                                                                                                                                        Str *_t1463 = Str_lit("test", 4ULL);
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1463;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1510; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwMacro()); _t1510 = *_hp; free(_hp); }
                                                                                                                                                                        if (_t1510) {
                                                                                                                                                                            Str *_t1464 = Str_lit("macro", 5ULL);
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1464;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1509; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwExtFunc()); _t1509 = *_hp; free(_hp); }
                                                                                                                                                                            if (_t1509) {
                                                                                                                                                                                Str *_t1465 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1465;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1508; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwExtProc()); _t1508 = *_hp; free(_hp); }
                                                                                                                                                                                if (_t1508) {
                                                                                                                                                                                    Str *_t1466 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1466;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1507; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwReturns()); _t1507 = *_hp; free(_hp); }
                                                                                                                                                                                    if (_t1507) {
                                                                                                                                                                                        Str *_t1467 = Str_lit("returns", 7ULL);
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1467;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1506; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwThrows()); _t1506 = *_hp; free(_hp); }
                                                                                                                                                                                        if (_t1506) {
                                                                                                                                                                                            Str *_t1468 = Str_lit("throws", 6ULL);
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1468;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1505; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwIf()); _t1505 = *_hp; free(_hp); }
                                                                                                                                                                                            if (_t1505) {
                                                                                                                                                                                                Str *_t1469 = Str_lit("if", 2ULL);
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1469;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1504; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwElse()); _t1504 = *_hp; free(_hp); }
                                                                                                                                                                                                if (_t1504) {
                                                                                                                                                                                                    Str *_t1470 = Str_lit("else", 4ULL);
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1470;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1503; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwWhile()); _t1503 = *_hp; free(_hp); }
                                                                                                                                                                                                    if (_t1503) {
                                                                                                                                                                                                        Str *_t1471 = Str_lit("while", 5ULL);
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1471;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1502; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwFor()); _t1502 = *_hp; free(_hp); }
                                                                                                                                                                                                        if (_t1502) {
                                                                                                                                                                                                            Str *_t1472 = Str_lit("for", 3ULL);
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1472;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1501; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwIn()); _t1501 = *_hp; free(_hp); }
                                                                                                                                                                                                            if (_t1501) {
                                                                                                                                                                                                                Str *_t1473 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1473;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1500; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwSwitch()); _t1500 = *_hp; free(_hp); }
                                                                                                                                                                                                                if (_t1500) {
                                                                                                                                                                                                                    Str *_t1474 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1474;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1499; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwMatch()); _t1499 = *_hp; free(_hp); }
                                                                                                                                                                                                                    if (_t1499) {
                                                                                                                                                                                                                        Str *_t1475 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1475;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1498; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwCase()); _t1498 = *_hp; free(_hp); }
                                                                                                                                                                                                                        if (_t1498) {
                                                                                                                                                                                                                            Str *_t1476 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1476;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1497; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwDefault()); _t1497 = *_hp; free(_hp); }
                                                                                                                                                                                                                            if (_t1497) {
                                                                                                                                                                                                                                Str *_t1477 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1477;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1496; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwReturn()); _t1496 = *_hp; free(_hp); }
                                                                                                                                                                                                                                if (_t1496) {
                                                                                                                                                                                                                                    Str *_t1478 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1478;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1495; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwThrow()); _t1495 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    if (_t1495) {
                                                                                                                                                                                                                                        Str *_t1479 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1479;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1494; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwCatch()); _t1494 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        if (_t1494) {
                                                                                                                                                                                                                                            Str *_t1480 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1480;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1493; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwBreak()); _t1493 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            if (_t1493) {
                                                                                                                                                                                                                                                Str *_t1481 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1481;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1492; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwContinue()); _t1492 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                if (_t1492) {
                                                                                                                                                                                                                                                    Str *_t1482 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1482;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1491; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwDefer()); _t1491 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    if (_t1491) {
                                                                                                                                                                                                                                                        Str *_t1483 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1483;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1490; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwTrue()); _t1490 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        if (_t1490) {
                                                                                                                                                                                                                                                            Str *_t1484 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1484;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1489; { Bool *_hp = TokenType_eq(_sw1423, TokenType_KwFalse()); _t1489 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            if (_t1489) {
                                                                                                                                                                                                                                                                Str *_t1485 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1485;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1488; { Bool *_hp = TokenType_eq(_sw1423, TokenType_Error()); _t1488 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                if (_t1488) {
                                                                                                                                                                                                                                                                    Str *_t1486 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1486;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Str *_t1487 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1423, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1487;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1423, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    {
        Str *_sw1551 = Str_clone(word);
        Str *_t1616 = Str_lit("mode", 4ULL);
        Bool _t1617; { Bool *_hp = Str_eq(_sw1551, _t1616); _t1617 = *_hp; free(_hp); }
        Str_delete(_t1616, &(Bool){1});
        if (_t1617) {
            Str_delete(_sw1551, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1614 = Str_lit("mut", 3ULL);
            Bool _t1615; { Bool *_hp = Str_eq(_sw1551, _t1614); _t1615 = *_hp; free(_hp); }
            Str_delete(_t1614, &(Bool){1});
            if (_t1615) {
                ;
                Str_delete(_sw1551, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1612 = Str_lit("own", 3ULL);
                Bool _t1613; { Bool *_hp = Str_eq(_sw1551, _t1612); _t1613 = *_hp; free(_hp); }
                Str_delete(_t1612, &(Bool){1});
                if (_t1613) {
                    ;
                    ;
                    Str_delete(_sw1551, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1610 = Str_lit("ref", 3ULL);
                    Bool _t1611; { Bool *_hp = Str_eq(_sw1551, _t1610); _t1611 = *_hp; free(_hp); }
                    Str_delete(_t1610, &(Bool){1});
                    if (_t1611) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1551, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1608 = Str_lit("struct", 6ULL);
                        Bool _t1609; { Bool *_hp = Str_eq(_sw1551, _t1608); _t1609 = *_hp; free(_hp); }
                        Str_delete(_t1608, &(Bool){1});
                        if (_t1609) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1551, &(Bool){1});
                            ;
                            return TokenType_KwStruct();
                        } else {
                            Str *_t1606 = Str_lit("ext_struct", 10ULL);
                            Bool _t1607; { Bool *_hp = Str_eq(_sw1551, _t1606); _t1607 = *_hp; free(_hp); }
                            Str_delete(_t1606, &(Bool){1});
                            if (_t1607) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1551, &(Bool){1});
                                ;
                                return TokenType_KwExtStruct();
                            } else {
                                Str *_t1604 = Str_lit("enum", 4ULL);
                                Bool _t1605; { Bool *_hp = Str_eq(_sw1551, _t1604); _t1605 = *_hp; free(_hp); }
                                Str_delete(_t1604, &(Bool){1});
                                if (_t1605) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1551, &(Bool){1});
                                    ;
                                    return TokenType_KwEnum();
                                } else {
                                    Str *_t1602 = Str_lit("namespace", 9ULL);
                                    Bool _t1603; { Bool *_hp = Str_eq(_sw1551, _t1602); _t1603 = *_hp; free(_hp); }
                                    Str_delete(_t1602, &(Bool){1});
                                    if (_t1603) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1551, &(Bool){1});
                                        ;
                                        return TokenType_KwNamespace();
                                    } else {
                                        Str *_t1600 = Str_lit("func", 4ULL);
                                        Bool _t1601; { Bool *_hp = Str_eq(_sw1551, _t1600); _t1601 = *_hp; free(_hp); }
                                        Str_delete(_t1600, &(Bool){1});
                                        if (_t1601) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1551, &(Bool){1});
                                            ;
                                            return TokenType_KwFunc();
                                        } else {
                                            Str *_t1598 = Str_lit("proc", 4ULL);
                                            Bool _t1599; { Bool *_hp = Str_eq(_sw1551, _t1598); _t1599 = *_hp; free(_hp); }
                                            Str_delete(_t1598, &(Bool){1});
                                            if (_t1599) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw1551, &(Bool){1});
                                                ;
                                                return TokenType_KwProc();
                                            } else {
                                                Str *_t1596 = Str_lit("test", 4ULL);
                                                Bool _t1597; { Bool *_hp = Str_eq(_sw1551, _t1596); _t1597 = *_hp; free(_hp); }
                                                Str_delete(_t1596, &(Bool){1});
                                                if (_t1597) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw1551, &(Bool){1});
                                                    ;
                                                    return TokenType_KwTest();
                                                } else {
                                                    Str *_t1594 = Str_lit("macro", 5ULL);
                                                    Bool _t1595; { Bool *_hp = Str_eq(_sw1551, _t1594); _t1595 = *_hp; free(_hp); }
                                                    Str_delete(_t1594, &(Bool){1});
                                                    if (_t1595) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw1551, &(Bool){1});
                                                        ;
                                                        return TokenType_KwMacro();
                                                    } else {
                                                        Str *_t1592 = Str_lit("ext_func", 8ULL);
                                                        Bool _t1593; { Bool *_hp = Str_eq(_sw1551, _t1592); _t1593 = *_hp; free(_hp); }
                                                        Str_delete(_t1592, &(Bool){1});
                                                        if (_t1593) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw1551, &(Bool){1});
                                                            ;
                                                            return TokenType_KwExtFunc();
                                                        } else {
                                                            Str *_t1590 = Str_lit("ext_proc", 8ULL);
                                                            Bool _t1591; { Bool *_hp = Str_eq(_sw1551, _t1590); _t1591 = *_hp; free(_hp); }
                                                            Str_delete(_t1590, &(Bool){1});
                                                            if (_t1591) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw1551, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtProc();
                                                            } else {
                                                                Str *_t1588 = Str_lit("returns", 7ULL);
                                                                Bool _t1589; { Bool *_hp = Str_eq(_sw1551, _t1588); _t1589 = *_hp; free(_hp); }
                                                                Str_delete(_t1588, &(Bool){1});
                                                                if (_t1589) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1551, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwReturns();
                                                                } else {
                                                                    Str *_t1586 = Str_lit("throws", 6ULL);
                                                                    Bool _t1587; { Bool *_hp = Str_eq(_sw1551, _t1586); _t1587 = *_hp; free(_hp); }
                                                                    Str_delete(_t1586, &(Bool){1});
                                                                    if (_t1587) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1551, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwThrows();
                                                                    } else {
                                                                        Str *_t1584 = Str_lit("if", 2ULL);
                                                                        Bool _t1585; { Bool *_hp = Str_eq(_sw1551, _t1584); _t1585 = *_hp; free(_hp); }
                                                                        Str_delete(_t1584, &(Bool){1});
                                                                        if (_t1585) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1551, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwIf();
                                                                        } else {
                                                                            Str *_t1582 = Str_lit("else", 4ULL);
                                                                            Bool _t1583; { Bool *_hp = Str_eq(_sw1551, _t1582); _t1583 = *_hp; free(_hp); }
                                                                            Str_delete(_t1582, &(Bool){1});
                                                                            if (_t1583) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1551, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwElse();
                                                                            } else {
                                                                                Str *_t1580 = Str_lit("while", 5ULL);
                                                                                Bool _t1581; { Bool *_hp = Str_eq(_sw1551, _t1580); _t1581 = *_hp; free(_hp); }
                                                                                Str_delete(_t1580, &(Bool){1});
                                                                                if (_t1581) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1551, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwWhile();
                                                                                } else {
                                                                                    Str *_t1578 = Str_lit("for", 3ULL);
                                                                                    Bool _t1579; { Bool *_hp = Str_eq(_sw1551, _t1578); _t1579 = *_hp; free(_hp); }
                                                                                    Str_delete(_t1578, &(Bool){1});
                                                                                    if (_t1579) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1551, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwFor();
                                                                                    } else {
                                                                                        Str *_t1576 = Str_lit("in", 2ULL);
                                                                                        Bool _t1577; { Bool *_hp = Str_eq(_sw1551, _t1576); _t1577 = *_hp; free(_hp); }
                                                                                        Str_delete(_t1576, &(Bool){1});
                                                                                        if (_t1577) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1551, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwIn();
                                                                                        } else {
                                                                                            Str *_t1574 = Str_lit("switch", 6ULL);
                                                                                            Bool _t1575; { Bool *_hp = Str_eq(_sw1551, _t1574); _t1575 = *_hp; free(_hp); }
                                                                                            Str_delete(_t1574, &(Bool){1});
                                                                                            if (_t1575) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1551, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwSwitch();
                                                                                            } else {
                                                                                                Str *_t1572 = Str_lit("match", 5ULL);
                                                                                                Bool _t1573; { Bool *_hp = Str_eq(_sw1551, _t1572); _t1573 = *_hp; free(_hp); }
                                                                                                Str_delete(_t1572, &(Bool){1});
                                                                                                if (_t1573) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1551, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwMatch();
                                                                                                } else {
                                                                                                    Str *_t1570 = Str_lit("case", 4ULL);
                                                                                                    Bool _t1571; { Bool *_hp = Str_eq(_sw1551, _t1570); _t1571 = *_hp; free(_hp); }
                                                                                                    Str_delete(_t1570, &(Bool){1});
                                                                                                    if (_t1571) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1551, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwCase();
                                                                                                    } else {
                                                                                                        Str *_t1568 = Str_lit("default", 7ULL);
                                                                                                        Bool _t1569; { Bool *_hp = Str_eq(_sw1551, _t1568); _t1569 = *_hp; free(_hp); }
                                                                                                        Str_delete(_t1568, &(Bool){1});
                                                                                                        if (_t1569) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1551, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwDefault();
                                                                                                        } else {
                                                                                                            Str *_t1566 = Str_lit("return", 6ULL);
                                                                                                            Bool _t1567; { Bool *_hp = Str_eq(_sw1551, _t1566); _t1567 = *_hp; free(_hp); }
                                                                                                            Str_delete(_t1566, &(Bool){1});
                                                                                                            if (_t1567) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1551, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwReturn();
                                                                                                            } else {
                                                                                                                Str *_t1564 = Str_lit("throw", 5ULL);
                                                                                                                Bool _t1565; { Bool *_hp = Str_eq(_sw1551, _t1564); _t1565 = *_hp; free(_hp); }
                                                                                                                Str_delete(_t1564, &(Bool){1});
                                                                                                                if (_t1565) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1551, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwThrow();
                                                                                                                } else {
                                                                                                                    Str *_t1562 = Str_lit("catch", 5ULL);
                                                                                                                    Bool _t1563; { Bool *_hp = Str_eq(_sw1551, _t1562); _t1563 = *_hp; free(_hp); }
                                                                                                                    Str_delete(_t1562, &(Bool){1});
                                                                                                                    if (_t1563) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1551, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwCatch();
                                                                                                                    } else {
                                                                                                                        Str *_t1560 = Str_lit("break", 5ULL);
                                                                                                                        Bool _t1561; { Bool *_hp = Str_eq(_sw1551, _t1560); _t1561 = *_hp; free(_hp); }
                                                                                                                        Str_delete(_t1560, &(Bool){1});
                                                                                                                        if (_t1561) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1551, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwBreak();
                                                                                                                        } else {
                                                                                                                            Str *_t1558 = Str_lit("continue", 8ULL);
                                                                                                                            Bool _t1559; { Bool *_hp = Str_eq(_sw1551, _t1558); _t1559 = *_hp; free(_hp); }
                                                                                                                            Str_delete(_t1558, &(Bool){1});
                                                                                                                            if (_t1559) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1551, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwContinue();
                                                                                                                            } else {
                                                                                                                                Str *_t1556 = Str_lit("defer", 5ULL);
                                                                                                                                Bool _t1557; { Bool *_hp = Str_eq(_sw1551, _t1556); _t1557 = *_hp; free(_hp); }
                                                                                                                                Str_delete(_t1556, &(Bool){1});
                                                                                                                                if (_t1557) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1551, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwDefer();
                                                                                                                                } else {
                                                                                                                                    Str *_t1554 = Str_lit("true", 4ULL);
                                                                                                                                    Bool _t1555; { Bool *_hp = Str_eq(_sw1551, _t1554); _t1555 = *_hp; free(_hp); }
                                                                                                                                    Str_delete(_t1554, &(Bool){1});
                                                                                                                                    if (_t1555) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1551, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwTrue();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1552 = Str_lit("false", 5ULL);
                                                                                                                                        Bool _t1553; { Bool *_hp = Str_eq(_sw1551, _t1552); _t1553 = *_hp; free(_hp); }
                                                                                                                                        Str_delete(_t1552, &(Bool){1});
                                                                                                                                        if (_t1553) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1551, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwFalse();
                                                                                                                                        } else {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1551, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_Ident();
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        Str_delete(_sw1551, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * source, Str * path) {
    Str *_t1973 = Str_lit("Token", 5ULL);
    U64 _t1974; { U64 *_hp = Token_size(); _t1974 = *_hp; free(_hp); }
    Vec *tokens = Vec_new(_t1973, &(U64){_t1974});
    Str_delete(_t1973, &(Bool){1});
    ;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    I64 line = 1;
    U64 line_start = 0;
    U64 src_len; { U64 *_hp = Str_len(source); src_len = *_hp; free(_hp); }
    while (1) {
        Bool _wcond1618; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1618 = *_hp; free(_hp); }
        if (_wcond1618) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_get(source, pos);
        U8 _t1918 = 32;
        U8 _t1919 = 9;
        Bool _t1920 = U8_eq(DEREF(c), _t1918);
        ;
        Bool _t1921 = U8_eq(DEREF(c), _t1919);
        ;
        U8 _t1922 = 13;
        Bool _t1923 = Bool_or(_t1920, _t1921);
        ;
        ;
        Bool _t1924 = U8_eq(DEREF(c), _t1922);
        ;
        U8 _t1925 = 59;
        Bool _t1926 = Bool_or(_t1923, _t1924);
        ;
        ;
        Bool _t1927 = U8_eq(DEREF(c), _t1925);
        ;
        Bool _t1928 = Bool_or(_t1926, _t1927);
        ;
        ;
        if (_t1928) {
            U64 _t1619 = 1;
            U64 _t1620 = U64_add(DEREF(pos), _t1619);
            ;
            *pos = _t1620;
            ;
            ;
            continue;
        }
        ;
        U8 _t1929 = 10;
        Bool _t1930 = U8_eq(DEREF(c), _t1929);
        ;
        if (_t1930) {
            U64 _t1621 = 1;
            U64 _t1622 = U64_add(DEREF(pos), _t1621);
            ;
            *pos = _t1622;
            ;
            I64 _t1623 = 1;
            I64 _t1624 = I64_add(line, _t1623);
            ;
            line = _t1624;
            ;
            U64 _t1625 = U64_clone(pos);
            line_start = _t1625;
            ;
            ;
            continue;
        }
        ;
        U64 _t1931 = U64_sub(DEREF(pos), line_start);
        U64 _t1932 = 1;
        U64 _t1933 = U64_add(_t1931, _t1932);
        ;
        ;
        I64 col = U64_to_i64(_t1933);
        ;
        U64 start = U64_clone(pos);
        U8 _t1934 = 35;
        Bool _t1935 = U8_eq(DEREF(c), _t1934);
        ;
        if (_t1935) {
            while (1) {
                Bool _wcond1626; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1626 = *_hp; free(_hp); }
                if (_wcond1626) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1627 = Str_get(source, pos);
                U8 _t1628 = 10;
                Bool _t1629 = U8_eq(DEREF(_t1627), _t1628);
                ;
                if (_t1629) {
                    ;
                    break;
                }
                ;
                U64 _t1630 = 1;
                U64 _t1631 = U64_add(DEREF(pos), _t1630);
                ;
                *pos = _t1631;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1936 = 47;
        U64 _t1937 = 1;
        U64 _t1938 = U64_add(DEREF(pos), _t1937);
        ;
        Bool _t1939 = U8_eq(DEREF(c), _t1936);
        ;
        Bool _t1940; { Bool *_hp = U64_lt(&(U64){_t1938}, &(U64){src_len}); _t1940 = *_hp; free(_hp); }
        ;
        Bool _t1941 = Bool_and(_t1939, _t1940);
        ;
        ;
        if (_t1941) {
            U64 _t1692 = 1;
            U64 *_t1693 = malloc(sizeof(U64)); *_t1693 = U64_add(DEREF(pos), _t1692);
            ;
            U8 *c2 = Str_get(source, _t1693);
            U8 _t1694 = 47;
            Bool _t1695 = U8_eq(DEREF(c2), _t1694);
            ;
            if (_t1695) {
                while (1) {
                    Bool _wcond1632; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1632 = *_hp; free(_hp); }
                    if (_wcond1632) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1633 = Str_get(source, pos);
                    U8 _t1634 = 10;
                    Bool _t1635 = U8_eq(DEREF(_t1633), _t1634);
                    ;
                    if (_t1635) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1636 = 1;
                    U64 _t1637 = U64_add(DEREF(pos), _t1636);
                    ;
                    *pos = _t1637;
                    ;
                }
                U64_delete(_t1693, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1696 = 42;
            Bool _t1697 = U8_eq(DEREF(c2), _t1696);
            U64_delete(_t1693, &(Bool){1});
            ;
            if (_t1697) {
                U64 _t1688 = 2;
                U64 _t1689 = U64_add(DEREF(pos), _t1688);
                ;
                *pos = _t1689;
                ;
                I64 depth = 1;
                while (1) {
                    Bool _wcond1638; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1638 = *_hp; free(_hp); }
                    if (_wcond1638) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1663 = 0;
                    Bool _t1664; { Bool *_hp = I64_lte(&(I64){depth}, &(I64){_t1663}); _t1664 = *_hp; free(_hp); }
                    ;
                    if (_t1664) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1665 = 1;
                    U64 _t1666 = U64_add(DEREF(pos), _t1665);
                    ;
                    Bool _t1667; { Bool *_hp = U64_lt(&(U64){_t1666}, &(U64){src_len}); _t1667 = *_hp; free(_hp); }
                    ;
                    if (_t1667) {
                        U8 *b1 = Str_get(source, pos);
                        U64 _t1647 = 1;
                        U64 *_t1648 = malloc(sizeof(U64)); *_t1648 = U64_add(DEREF(pos), _t1647);
                        ;
                        U8 *b2 = Str_get(source, _t1648);
                        U8 _t1649 = 47;
                        U8 _t1650 = 42;
                        Bool _t1651 = U8_eq(DEREF(b1), _t1649);
                        ;
                        Bool _t1652 = U8_eq(DEREF(b2), _t1650);
                        ;
                        Bool _t1653 = Bool_and(_t1651, _t1652);
                        ;
                        ;
                        if (_t1653) {
                            I64 _t1639 = 1;
                            I64 _t1640 = I64_add(depth, _t1639);
                            ;
                            depth = _t1640;
                            ;
                            U64 _t1641 = 2;
                            U64 _t1642 = U64_add(DEREF(pos), _t1641);
                            ;
                            *pos = _t1642;
                            ;
                            U64_delete(_t1648, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1654 = 42;
                        U8 _t1655 = 47;
                        Bool _t1656 = U8_eq(DEREF(b1), _t1654);
                        ;
                        Bool _t1657 = U8_eq(DEREF(b2), _t1655);
                        U64_delete(_t1648, &(Bool){1});
                        ;
                        Bool _t1658 = Bool_and(_t1656, _t1657);
                        ;
                        ;
                        if (_t1658) {
                            I64 _t1643 = 1;
                            I64 _t1644 = I64_sub(depth, _t1643);
                            ;
                            depth = _t1644;
                            ;
                            U64 _t1645 = 2;
                            U64 _t1646 = U64_add(DEREF(pos), _t1645);
                            ;
                            *pos = _t1646;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1668 = Str_get(source, pos);
                    U8 _t1669 = 10;
                    Bool _t1670 = U8_eq(DEREF(_t1668), _t1669);
                    ;
                    if (_t1670) {
                        I64 _t1659 = 1;
                        I64 _t1660 = I64_add(line, _t1659);
                        ;
                        line = _t1660;
                        ;
                        U64 _t1661 = 1;
                        U64 _t1662 = U64_add(DEREF(pos), _t1661);
                        ;
                        line_start = _t1662;
                        ;
                    }
                    ;
                    U64 _t1671 = 1;
                    U64 _t1672 = U64_add(DEREF(pos), _t1671);
                    ;
                    *pos = _t1672;
                    ;
                }
                I64 _t1690 = 0;
                Bool _t1691; { Bool *_hp = I64_gt(&(I64){depth}, &(I64){_t1690}); _t1691 = *_hp; free(_hp); }
                ;
                ;
                if (_t1691) {
                    Str *_t1673 = Str_lit("Str", 3ULL);
                    U64 _t1674; { U64 *_hp = Str_size(); _t1674 = *_hp; free(_hp); }
                    U64 _t1675 = 6;
                    Array *_va22 = Array_new(_t1673, &(U64){_t1674}, &(U64){_t1675});
                    Str_delete(_t1673, &(Bool){1});
                    ;
                    ;
                    U64 _t1676 = 0;
                    Str *_t1677 = Str_clone(path);
                    Array_set(_va22, &(U64){_t1676}, _t1677);
                    ;
                    U64 _t1678 = 1;
                    Str *_t1679 = Str_lit(":", 1ULL);
                    Array_set(_va22, &(U64){_t1678}, _t1679);
                    ;
                    U64 _t1680 = 2;
                    Str *_t1681 = I64_to_str(&(I64){line});
                    Array_set(_va22, &(U64){_t1680}, _t1681);
                    ;
                    U64 _t1682 = 3;
                    Str *_t1683 = Str_lit(":", 1ULL);
                    Array_set(_va22, &(U64){_t1682}, _t1683);
                    ;
                    U64 _t1684 = 4;
                    Str *_t1685 = I64_to_str(&(I64){col});
                    Array_set(_va22, &(U64){_t1684}, _t1685);
                    ;
                    U64 _t1686 = 5;
                    Str *_t1687 = Str_lit(": error: unterminated comment", 29ULL);
                    Array_set(_va22, &(U64){_t1686}, _t1687);
                    ;
                    println(_va22);
                }
                ;
                ;
                ;
                ;
                ;
                continue;
            }
            ;
        }
        ;
        Bool _t1942; { Bool *_hp = is_digit(c); _t1942 = *_hp; free(_hp); }
        if (_t1942) {
            while (1) {
                Bool _wcond1698; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1698 = *_hp; free(_hp); }
                if (_wcond1698) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1699 = Str_get(source, pos);
                Bool _t1700; { Bool *_hp = is_digit(_t1699); _t1700 = *_hp; free(_hp); }
                Bool _t1701 = Bool_not(_t1700);
                ;
                if (_t1701) {
                    ;
                    break;
                }
                ;
                U64 _t1702 = 1;
                U64 _t1703 = U64_add(DEREF(pos), _t1702);
                ;
                *pos = _t1703;
                ;
            }
            U64 _t1720 = 1;
            U64 _t1721 = U64_add(DEREF(pos), _t1720);
            ;
            Bool _t1722; { Bool *_hp = U64_lt(&(U64){_t1721}, &(U64){src_len}); _t1722 = *_hp; free(_hp); }
            ;
            if (_t1722) {
                U8 *_t1712 = Str_get(source, pos);
                U8 _t1713 = 46;
                U64 _t1714 = 1;
                U64 *_t1715 = malloc(sizeof(U64)); *_t1715 = U64_add(DEREF(pos), _t1714);
                ;
                U8 *_t1716 = Str_get(source, _t1715);
                Bool _t1717 = U8_eq(DEREF(_t1712), _t1713);
                ;
                Bool _t1718; { Bool *_hp = is_digit(_t1716); _t1718 = *_hp; free(_hp); }
                U64_delete(_t1715, &(Bool){1});
                Bool _t1719 = Bool_and(_t1717, _t1718);
                ;
                ;
                if (_t1719) {
                    U64 _t1710 = 1;
                    U64 _t1711 = U64_add(DEREF(pos), _t1710);
                    ;
                    *pos = _t1711;
                    ;
                    while (1) {
                        Bool _wcond1704; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1704 = *_hp; free(_hp); }
                        if (_wcond1704) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1705 = Str_get(source, pos);
                        Bool _t1706; { Bool *_hp = is_digit(_t1705); _t1706 = *_hp; free(_hp); }
                        Bool _t1707 = Bool_not(_t1706);
                        ;
                        if (_t1707) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1708 = 1;
                        U64 _t1709 = U64_add(DEREF(pos), _t1708);
                        ;
                        *pos = _t1709;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1723 = U64_sub(DEREF(pos), start);
            I64 _t1724 = I64_clone(&(I64){col});
            Token *_t1725 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1725->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1723}); _t1725->text = *_ca; free(_ca); }
            _t1725->line = I64_clone(&(I64){line});
            _t1725->col = _t1724;
            ;
            ;
            Vec_push(tokens, _t1725);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1943; { Bool *_hp = is_alpha(c); _t1943 = *_hp; free(_hp); }
        if (_t1943) {
            while (1) {
                Bool _wcond1726; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1726 = *_hp; free(_hp); }
                if (_wcond1726) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1727 = Str_get(source, pos);
                Bool _t1728; { Bool *_hp = is_alnum(_t1727); _t1728 = *_hp; free(_hp); }
                Bool _t1729 = Bool_not(_t1728);
                ;
                if (_t1729) {
                    ;
                    break;
                }
                ;
                U64 _t1730 = 1;
                U64 _t1731 = U64_add(DEREF(pos), _t1730);
                ;
                *pos = _t1731;
                ;
            }
            U64 _t1732 = U64_sub(DEREF(pos), start);
            Str *word = Str_substr(source, &(U64){start}, &(U64){_t1732});
            ;
            TokenType *type = lookup_keyword(word);
            I64 _t1733 = I64_clone(&(I64){line});
            I64 _t1734 = I64_clone(&(I64){col});
            Token *_t1735 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1735->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1735->text = *_ca; free(_ca); }
            _t1735->line = _t1733;
            _t1735->col = _t1734;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1735);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1944 = 34;
        Bool _t1945 = U8_eq(DEREF(c), _t1944);
        ;
        if (_t1945) {
            U64 _t1785 = 1;
            U64 _t1786 = U64_add(DEREF(pos), _t1785);
            ;
            *pos = _t1786;
            ;
            while (1) {
                Bool _wcond1736; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1736 = *_hp; free(_hp); }
                if (_wcond1736) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1743 = Str_get(source, pos);
                U8 _t1744 = 34;
                Bool _t1745 = U8_eq(DEREF(_t1743), _t1744);
                ;
                if (_t1745) {
                    ;
                    break;
                }
                ;
                U8 *_t1746 = Str_get(source, pos);
                U8 _t1747 = 92;
                U64 _t1748 = 1;
                U64 _t1749 = U64_add(DEREF(pos), _t1748);
                ;
                Bool _t1750 = U8_eq(DEREF(_t1746), _t1747);
                ;
                Bool _t1751; { Bool *_hp = U64_lt(&(U64){_t1749}, &(U64){src_len}); _t1751 = *_hp; free(_hp); }
                ;
                Bool _t1752 = Bool_and(_t1750, _t1751);
                ;
                ;
                if (_t1752) {
                    U64 _t1737 = 1;
                    U64 _t1738 = U64_add(DEREF(pos), _t1737);
                    ;
                    *pos = _t1738;
                    ;
                }
                ;
                U8 *_t1753 = Str_get(source, pos);
                U8 _t1754 = 10;
                Bool _t1755 = U8_eq(DEREF(_t1753), _t1754);
                ;
                if (_t1755) {
                    I64 _t1739 = 1;
                    I64 _t1740 = I64_add(line, _t1739);
                    ;
                    line = _t1740;
                    ;
                    U64 _t1741 = 1;
                    U64 _t1742 = U64_add(DEREF(pos), _t1741);
                    ;
                    line_start = _t1742;
                    ;
                }
                ;
                U64 _t1756 = 1;
                U64 _t1757 = U64_add(DEREF(pos), _t1756);
                ;
                *pos = _t1757;
                ;
            }
            U8 *_t1787 = Str_get(source, pos);
            U8 _t1788 = 34;
            Bool _t1789; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1789 = *_hp; free(_hp); }
            Bool _t1790 = U8_eq(DEREF(_t1787), _t1788);
            ;
            Bool _t1791 = Bool_and(_t1789, _t1790);
            ;
            ;
            if (_t1791) {
                U64 _t1758 = 1;
                U64 _t1759 = U64_add(DEREF(pos), _t1758);
                ;
                *pos = _t1759;
                ;
                U64 _t1760 = 1;
                U64 _t1761 = U64_sub(DEREF(pos), start);
                U64 _t1762 = 2;
                U64 _t1763 = U64_add(start, _t1760);
                ;
                U64 _t1764 = U64_sub(_t1761, _t1762);
                ;
                ;
                I64 _t1765 = I64_clone(&(I64){col});
                Token *_t1766 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1766->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){_t1763}, &(U64){_t1764}); _t1766->text = *_ca; free(_ca); }
                _t1766->line = I64_clone(&(I64){line});
                _t1766->col = _t1765;
                ;
                ;
                ;
                Vec_push(tokens, _t1766);
            } else {
                Str *_t1767 = Str_lit("Str", 3ULL);
                U64 _t1768; { U64 *_hp = Str_size(); _t1768 = *_hp; free(_hp); }
                U64 _t1769 = 6;
                Array *_va23 = Array_new(_t1767, &(U64){_t1768}, &(U64){_t1769});
                Str_delete(_t1767, &(Bool){1});
                ;
                ;
                U64 _t1770 = 0;
                Str *_t1771 = Str_clone(path);
                Array_set(_va23, &(U64){_t1770}, _t1771);
                ;
                U64 _t1772 = 1;
                Str *_t1773 = Str_lit(":", 1ULL);
                Array_set(_va23, &(U64){_t1772}, _t1773);
                ;
                U64 _t1774 = 2;
                Str *_t1775 = I64_to_str(&(I64){line});
                Array_set(_va23, &(U64){_t1774}, _t1775);
                ;
                U64 _t1776 = 3;
                Str *_t1777 = Str_lit(":", 1ULL);
                Array_set(_va23, &(U64){_t1776}, _t1777);
                ;
                U64 _t1778 = 4;
                Str *_t1779 = I64_to_str(&(I64){col});
                Array_set(_va23, &(U64){_t1778}, _t1779);
                ;
                U64 _t1780 = 5;
                Str *_t1781 = Str_lit(": error: unterminated string", 28ULL);
                Array_set(_va23, &(U64){_t1780}, _t1781);
                ;
                println(_va23);
                U64 _t1782 = U64_sub(DEREF(pos), start);
                I64 _t1783 = I64_clone(&(I64){col});
                Token *_t1784 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1784->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1782}); _t1784->text = *_ca; free(_ca); }
                _t1784->line = I64_clone(&(I64){line});
                _t1784->col = _t1783;
                ;
                ;
                Vec_push(tokens, _t1784);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1946 = 39;
        Bool _t1947 = U8_eq(DEREF(c), _t1946);
        ;
        if (_t1947) {
            U64 _t1817 = 1;
            U64 _t1818 = U64_add(DEREF(pos), _t1817);
            ;
            *pos = _t1818;
            ;
            U64 ch_start = U64_clone(pos);
            U8 *_t1819 = Str_get(source, pos);
            U8 _t1820 = 92;
            U64 _t1821 = 1;
            U64 _t1822 = U64_add(DEREF(pos), _t1821);
            ;
            Bool _t1823 = U8_eq(DEREF(_t1819), _t1820);
            ;
            Bool _t1824; { Bool *_hp = U64_lt(&(U64){_t1822}, &(U64){src_len}); _t1824 = *_hp; free(_hp); }
            ;
            Bool _t1825; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1825 = *_hp; free(_hp); }
            Bool _t1826 = Bool_and(_t1823, _t1824);
            ;
            ;
            Bool _t1827 = Bool_and(_t1825, _t1826);
            ;
            ;
            if (_t1827) {
                U64 _t1792 = 1;
                U64 _t1793 = U64_add(DEREF(pos), _t1792);
                ;
                *pos = _t1793;
                ;
            }
            ;
            U64 _t1828 = 1;
            U64 _t1829 = U64_add(DEREF(pos), _t1828);
            ;
            *pos = _t1829;
            ;
            U8 *_t1830 = Str_get(source, pos);
            U8 _t1831 = 39;
            Bool _t1832; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1832 = *_hp; free(_hp); }
            Bool _t1833 = U8_eq(DEREF(_t1830), _t1831);
            ;
            Bool _t1834 = Bool_and(_t1832, _t1833);
            ;
            ;
            if (_t1834) {
                U64 _t1794 = U64_sub(DEREF(pos), ch_start);
                I64 _t1795 = I64_clone(&(I64){col});
                Token *_t1796 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1796->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){ch_start}, &(U64){_t1794}); _t1796->text = *_ca; free(_ca); }
                _t1796->line = I64_clone(&(I64){line});
                _t1796->col = _t1795;
                ;
                ;
                Vec_push(tokens, _t1796);
                U64 _t1797 = 1;
                U64 _t1798 = U64_add(DEREF(pos), _t1797);
                ;
                *pos = _t1798;
                ;
            } else {
                Str *_t1799 = Str_lit("Str", 3ULL);
                U64 _t1800; { U64 *_hp = Str_size(); _t1800 = *_hp; free(_hp); }
                U64 _t1801 = 6;
                Array *_va24 = Array_new(_t1799, &(U64){_t1800}, &(U64){_t1801});
                Str_delete(_t1799, &(Bool){1});
                ;
                ;
                U64 _t1802 = 0;
                Str *_t1803 = Str_clone(path);
                Array_set(_va24, &(U64){_t1802}, _t1803);
                ;
                U64 _t1804 = 1;
                Str *_t1805 = Str_lit(":", 1ULL);
                Array_set(_va24, &(U64){_t1804}, _t1805);
                ;
                U64 _t1806 = 2;
                Str *_t1807 = I64_to_str(&(I64){line});
                Array_set(_va24, &(U64){_t1806}, _t1807);
                ;
                U64 _t1808 = 3;
                Str *_t1809 = Str_lit(":", 1ULL);
                Array_set(_va24, &(U64){_t1808}, _t1809);
                ;
                U64 _t1810 = 4;
                Str *_t1811 = I64_to_str(&(I64){col});
                Array_set(_va24, &(U64){_t1810}, _t1811);
                ;
                U64 _t1812 = 5;
                Str *_t1813 = Str_lit(": error: unterminated character literal", 39ULL);
                Array_set(_va24, &(U64){_t1812}, _t1813);
                ;
                println(_va24);
                U64 _t1814 = U64_sub(DEREF(pos), start);
                I64 _t1815 = I64_clone(&(I64){col});
                Token *_t1816 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1816->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1814}); _t1816->text = *_ca; free(_ca); }
                _t1816->line = I64_clone(&(I64){line});
                _t1816->col = _t1815;
                ;
                ;
                Vec_push(tokens, _t1816);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t1948 = 1;
        U64 _t1949 = U64_add(DEREF(pos), _t1948);
        ;
        Bool _t1950; { Bool *_hp = U64_lt(&(U64){_t1949}, &(U64){src_len}); _t1950 = *_hp; free(_hp); }
        ;
        if (_t1950) {
            U64 _t1841 = 1;
            U64 *_t1842 = malloc(sizeof(U64)); *_t1842 = U64_add(DEREF(pos), _t1841);
            ;
            U8 *c2 = Str_get(source, _t1842);
            TokenType *two = TokenType_clone(TokenType_Eof());
            U8 _t1843 = 58;
            U8 _t1844 = 61;
            Bool _t1845 = U8_eq(DEREF(c), _t1843);
            ;
            Bool _t1846 = U8_eq(DEREF(c2), _t1844);
            ;
            Bool _t1847 = Bool_and(_t1845, _t1846);
            ;
            ;
            if (_t1847) {
                two = TokenType_clone(TokenType_ColonEq());
            }
            ;
            U8 _t1848 = 61;
            U8 _t1849 = 61;
            Bool _t1850 = U8_eq(DEREF(c), _t1848);
            ;
            Bool _t1851 = U8_eq(DEREF(c2), _t1849);
            ;
            Bool _t1852 = Bool_and(_t1850, _t1851);
            ;
            ;
            if (_t1852) {
                two = TokenType_clone(TokenType_EqEq());
            }
            ;
            U8 _t1853 = 33;
            U8 _t1854 = 61;
            Bool _t1855 = U8_eq(DEREF(c), _t1853);
            ;
            Bool _t1856 = U8_eq(DEREF(c2), _t1854);
            ;
            Bool _t1857 = Bool_and(_t1855, _t1856);
            ;
            ;
            if (_t1857) {
                two = TokenType_clone(TokenType_Neq());
            }
            ;
            U8 _t1858 = 60;
            U8 _t1859 = 61;
            Bool _t1860 = U8_eq(DEREF(c), _t1858);
            ;
            Bool _t1861 = U8_eq(DEREF(c2), _t1859);
            ;
            Bool _t1862 = Bool_and(_t1860, _t1861);
            ;
            ;
            if (_t1862) {
                two = TokenType_clone(TokenType_LtEq());
            }
            ;
            U8 _t1863 = 62;
            U8 _t1864 = 61;
            Bool _t1865 = U8_eq(DEREF(c), _t1863);
            ;
            Bool _t1866 = U8_eq(DEREF(c2), _t1864);
            ;
            Bool _t1867 = Bool_and(_t1865, _t1866);
            ;
            ;
            if (_t1867) {
                two = TokenType_clone(TokenType_GtEq());
            }
            ;
            U8 _t1868 = 46;
            U8 _t1869 = 46;
            Bool _t1870 = U8_eq(DEREF(c), _t1868);
            ;
            Bool _t1871 = U8_eq(DEREF(c2), _t1869);
            U64_delete(_t1842, &(Bool){1});
            ;
            Bool _t1872 = Bool_and(_t1870, _t1871);
            ;
            ;
            if (_t1872) {
                two = TokenType_clone(TokenType_DotDot());
            }
            ;
            Bool _t1873; { Bool *_hp = TokenType_eq(two, TokenType_Eof()); _t1873 = *_hp; free(_hp); }
            Bool _t1874 = Bool_not(_t1873);
            ;
            if (_t1874) {
                U64 _t1835 = 2;
                I64 _t1836 = I64_clone(&(I64){line});
                I64 _t1837 = I64_clone(&(I64){col});
                Token *_t1838 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1838->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1835}); _t1838->text = *_ca; free(_ca); }
                _t1838->line = _t1836;
                _t1838->col = _t1837;
                ;
                ;
                ;
                Vec_push(tokens, _t1838);
                U64 _t1839 = 2;
                U64 _t1840 = U64_add(DEREF(pos), _t1839);
                ;
                *pos = _t1840;
                ;
                ;
                TokenType_delete(two, &(Bool){1});
                ;
                ;
                ;
                continue;
            }
            ;
            TokenType_delete(two, &(Bool){1});
        }
        ;
        TokenType *single = TokenType_clone(TokenType_Eof());
        {
            U8 _sw1875 = U8_clone(c);
            U8 _t1910 = 40;
            Bool _t1911 = U8_eq(_sw1875, _t1910);
            ;
            if (_t1911) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1908 = 41;
                Bool _t1909 = U8_eq(_sw1875, _t1908);
                ;
                if (_t1909) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1906 = 123;
                    Bool _t1907 = U8_eq(_sw1875, _t1906);
                    ;
                    if (_t1907) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1904 = 125;
                        Bool _t1905 = U8_eq(_sw1875, _t1904);
                        ;
                        if (_t1905) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1902 = 91;
                            Bool _t1903 = U8_eq(_sw1875, _t1902);
                            ;
                            if (_t1903) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1900 = 93;
                                Bool _t1901 = U8_eq(_sw1875, _t1900);
                                ;
                                if (_t1901) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1898 = 44;
                                    Bool _t1899 = U8_eq(_sw1875, _t1898);
                                    ;
                                    if (_t1899) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1896 = 58;
                                        Bool _t1897 = U8_eq(_sw1875, _t1896);
                                        ;
                                        if (_t1897) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1894 = 46;
                                            Bool _t1895 = U8_eq(_sw1875, _t1894);
                                            ;
                                            if (_t1895) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1892 = 63;
                                                Bool _t1893 = U8_eq(_sw1875, _t1892);
                                                ;
                                                if (_t1893) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1890 = 33;
                                                    Bool _t1891 = U8_eq(_sw1875, _t1890);
                                                    ;
                                                    if (_t1891) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1888 = 43;
                                                        Bool _t1889 = U8_eq(_sw1875, _t1888);
                                                        ;
                                                        if (_t1889) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1886 = 45;
                                                            Bool _t1887 = U8_eq(_sw1875, _t1886);
                                                            ;
                                                            if (_t1887) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1884 = 42;
                                                                Bool _t1885 = U8_eq(_sw1875, _t1884);
                                                                ;
                                                                if (_t1885) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1882 = 47;
                                                                    Bool _t1883 = U8_eq(_sw1875, _t1882);
                                                                    ;
                                                                    if (_t1883) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1880 = 61;
                                                                        Bool _t1881 = U8_eq(_sw1875, _t1880);
                                                                        ;
                                                                        if (_t1881) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1878 = 60;
                                                                            Bool _t1879 = U8_eq(_sw1875, _t1878);
                                                                            ;
                                                                            if (_t1879) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1876 = 62;
                                                                                Bool _t1877 = U8_eq(_sw1875, _t1876);
                                                                                ;
                                                                                if (_t1877) {
                                                                                    single = TokenType_clone(TokenType_Gt());
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
            ;
        }
        Bool _t1951; { Bool *_hp = TokenType_eq(single, TokenType_Eof()); _t1951 = *_hp; free(_hp); }
        Bool _t1952 = Bool_not(_t1951);
        ;
        if (_t1952) {
            U64 _t1912 = 1;
            I64 _t1913 = I64_clone(&(I64){line});
            I64 _t1914 = I64_clone(&(I64){col});
            Token *_t1915 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1915->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1912}); _t1915->text = *_ca; free(_ca); }
            _t1915->line = _t1913;
            _t1915->col = _t1914;
            ;
            ;
            ;
            Vec_push(tokens, _t1915);
            U64 _t1916 = 1;
            U64 _t1917 = U64_add(DEREF(pos), _t1916);
            ;
            *pos = _t1917;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t1953 = Str_lit("Str", 3ULL);
        U64 _t1954; { U64 *_hp = Str_size(); _t1954 = *_hp; free(_hp); }
        U64 _t1955 = 6;
        Array *_va25 = Array_new(_t1953, &(U64){_t1954}, &(U64){_t1955});
        Str_delete(_t1953, &(Bool){1});
        ;
        ;
        U64 _t1956 = 0;
        Str *_t1957 = Str_clone(path);
        Array_set(_va25, &(U64){_t1956}, _t1957);
        ;
        U64 _t1958 = 1;
        Str *_t1959 = Str_lit(":", 1ULL);
        Array_set(_va25, &(U64){_t1958}, _t1959);
        ;
        U64 _t1960 = 2;
        Str *_t1961 = I64_to_str(&(I64){line});
        Array_set(_va25, &(U64){_t1960}, _t1961);
        ;
        U64 _t1962 = 3;
        Str *_t1963 = Str_lit(":", 1ULL);
        Array_set(_va25, &(U64){_t1962}, _t1963);
        ;
        U64 _t1964 = 4;
        Str *_t1965 = I64_to_str(&(I64){col});
        Array_set(_va25, &(U64){_t1964}, _t1965);
        ;
        U64 _t1966 = 5;
        Str *_t1967 = Str_lit(": error: unexpected character", 29ULL);
        Array_set(_va25, &(U64){_t1966}, _t1967);
        ;
        println(_va25);
        U64 _t1968 = 1;
        I64 _t1969 = I64_clone(&(I64){col});
        ;
        Token *_t1970 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1970->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1968}); _t1970->text = *_ca; free(_ca); }
        _t1970->line = I64_clone(&(I64){line});
        _t1970->col = _t1969;
        ;
        ;
        ;
        Vec_push(tokens, _t1970);
        U64 _t1971 = 1;
        U64 _t1972 = U64_add(DEREF(pos), _t1971);
        ;
        *pos = _t1972;
        ;
    }
    ;
    U64 _t1975 = U64_sub(DEREF(pos), line_start);
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t1976 = 1;
    U64 _t1977 = U64_add(_t1975, _t1976);
    ;
    ;
    I64 col = U64_to_i64(_t1977);
    ;
    I64 _t1978 = I64_clone(&(I64){col});
    ;
    Token *_t1979 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t1979->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1979->text = *_ca; free(_ca); }
    _t1979->line = I64_clone(&(I64){line});
    _t1979->col = _t1978;
    ;
    ;
    Vec_push(tokens, _t1979);
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
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) { I16 *_r = malloc(sizeof(I16)); *_r = I16_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) { F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(val); return _r; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return (void *)Range_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(val); return _r; }
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

Bool dyn_has_cmp(Str *type_name) {
    (void)type_name;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return 1;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return 1;
    return 0;
}

__attribute__((constructor))
static void _til_lib_init(void) {
    _t1980 = malloc(sizeof(I64));
    *_t1980 = 0;
    _t1981 = malloc(sizeof(I64));
    *_t1981 = 1;
    _t1982 = malloc(sizeof(I64)); *_t1982 = I64_sub(DEREF(_t1980), DEREF(_t1981));
    CAP_LIT = U64_from_i64(_t1982);
    _t1983 = malloc(sizeof(I64));
    *_t1983 = 0;
    _t1984 = malloc(sizeof(I64));
    *_t1984 = 2;
    _t1985 = malloc(sizeof(I64)); *_t1985 = I64_sub(DEREF(_t1983), DEREF(_t1984));
    CAP_VIEW = U64_from_i64(_t1985);
}

