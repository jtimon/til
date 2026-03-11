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
static __attribute__((unused)) I16 * I16_neg(I16 * a);
static __attribute__((unused)) I16 * I16_abs(I16 * a);
static __attribute__((unused)) U64 * I16_size(void);
static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b);
static __attribute__((unused)) Str * I32_to_str(I32 * val);
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

static I64 *_t1954;
static I64 *_t1955;
static I64 *_t1956;
static U64 *CAP_LIT;
static I64 *_t1957;
static I64 *_t1958;
static I64 *_t1959;
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

static __attribute__((unused)) I16 * I16_neg(I16 * a) {
    I64 _t21 = 0;
    I64 _t22 = I16_to_i64(DEREF(a));
    I64 _t23 = I64_sub(_t21, _t22);
    ;
    ;
    I16 _t24 = I64_to_i16(_t23);
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t24; return _r; }
}

static __attribute__((unused)) I16 * I16_abs(I16 * a) {
    I64 _t29 = I16_to_i64(DEREF(a));
    I64 _t30 = 0;
    Bool _t31; { Bool *_hp = I64_lt(&(I64){_t29}, &(I64){_t30}); _t31 = *_hp; free(_hp); }
    ;
    ;
    if (_t31) {
        I64 _t25 = 0;
        I64 _t26 = I16_to_i64(DEREF(a));
        I64 _t27 = I64_sub(_t25, _t26);
        ;
        ;
        I16 _t28 = I64_to_i16(_t27);
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t28; return _r; }
    }
    ;
    I16 _t32 = I16_clone(a);
    { I16 *_r = malloc(sizeof(I16)); *_r = _t32; return _r; }
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b) {
    I64 _t34 = 0;
    I64 _t35 = 1;
    I64 _t36 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t37 = I64_sub(_t34, _t35);
    ;
    ;
    Bool _t38 = I64_eq(_t36, _t37);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t38; return _r; }
}

static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b) {
    I64 _t39 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t40 = 1;
    Bool _t41 = I64_eq(_t39, _t40);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t41; return _r; }
}

static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b) {
    Bool _t42 = I16_eq(DEREF(a), DEREF(b));
    Bool _t43 = Bool_not(_t42);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t43; return _r; }
}

static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b) {
    Bool _t44; { Bool *_hp = I16_gt(a, b); _t44 = *_hp; free(_hp); }
    Bool _t45 = Bool_not(_t44);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t45; return _r; }
}

static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b) {
    Bool _t46; { Bool *_hp = I16_lt(a, b); _t46 = *_hp; free(_hp); }
    Bool _t47 = Bool_not(_t46);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t47; return _r; }
}

static __attribute__((unused)) Str * I32_to_str(I32 * val) {
    I64 _t48 = I32_to_i64(DEREF(val));
    Str *_t49 = I64_to_str(&(I64){_t48});
    ;
    return _t49;
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    I64 _t50 = 0;
    I64 _t51 = I32_to_i64(DEREF(a));
    I64 _t52 = I64_sub(_t50, _t51);
    ;
    ;
    I32 _t53 = I64_to_i32(_t52);
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t53; return _r; }
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    I64 _t58 = I32_to_i64(DEREF(a));
    I64 _t59 = 0;
    Bool _t60; { Bool *_hp = I64_lt(&(I64){_t58}, &(I64){_t59}); _t60 = *_hp; free(_hp); }
    ;
    ;
    if (_t60) {
        I64 _t54 = 0;
        I64 _t55 = I32_to_i64(DEREF(a));
        I64 _t56 = I64_sub(_t54, _t55);
        ;
        ;
        I32 _t57 = I64_to_i32(_t56);
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t57; return _r; }
    }
    ;
    I32 _t61 = I32_clone(a);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t61; return _r; }
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    I64 _t63 = 0;
    I64 _t64 = 1;
    I64 _t65 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t66 = I64_sub(_t63, _t64);
    ;
    ;
    Bool _t67 = I64_eq(_t65, _t66);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t67; return _r; }
}

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    I64 _t68 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t69 = 1;
    Bool _t70 = I64_eq(_t68, _t69);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t70; return _r; }
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    Bool _t71 = I32_eq(DEREF(a), DEREF(b));
    Bool _t72 = Bool_not(_t71);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t72; return _r; }
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    Bool _t73; { Bool *_hp = I32_gt(a, b); _t73 = *_hp; free(_hp); }
    Bool _t74 = Bool_not(_t73);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t74; return _r; }
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    Bool _t75; { Bool *_hp = I32_lt(a, b); _t75 = *_hp; free(_hp); }
    Bool _t76 = Bool_not(_t75);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t76; return _r; }
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 _t77 = F32_from_i64_ext(val);
    { F32 *_r = malloc(sizeof(F32)); *_r = _t77; return _r; }
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    I64 _t79 = 0;
    I64 _t80 = 1;
    I64 _t81 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t82 = I64_sub(_t79, _t80);
    ;
    ;
    Bool _t83 = I64_eq(_t81, _t82);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t83; return _r; }
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    I64 _t84 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t85 = 1;
    Bool _t86 = I64_eq(_t84, _t85);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t86; return _r; }
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    Bool _t87 = F32_eq(DEREF(a), DEREF(b));
    Bool _t88 = Bool_not(_t87);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t88; return _r; }
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    Bool _t89; { Bool *_hp = F32_gt(a, b); _t89 = *_hp; free(_hp); }
    Bool _t90 = Bool_not(_t89);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t90; return _r; }
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    Bool _t91; { Bool *_hp = F32_lt(a, b); _t91 = *_hp; free(_hp); }
    Bool _t92 = Bool_not(_t91);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t92; return _r; }
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    I64 _t93 = U32_to_i64(DEREF(val));
    Str *_t94 = I64_to_str(&(I64){_t93});
    ;
    return _t94;
}

static __attribute__((unused)) U32 * U32_from_i64(I64 * val) {
    I64 _t101 = 0;
    I64 _t102 = 4294967295;
    Bool _t103; { Bool *_hp = I64_lt(val, &(I64){_t101}); _t103 = *_hp; free(_hp); }
    ;
    Bool _t104; { Bool *_hp = I64_gt(val, &(I64){_t102}); _t104 = *_hp; free(_hp); }
    ;
    Bool _t105 = Bool_or(_t103, _t104);
    ;
    ;
    if (_t105) {
        Str *_t95 = Str_lit("Str", 3ULL);
        U64 _t96; { U64 *_hp = Str_size(); _t96 = *_hp; free(_hp); }
        U64 _t97 = 1;
        Array *_va0 = Array_new(_t95, &(U64){_t96}, &(U64){_t97});
        Str_delete(_t95, &(Bool){1});
        ;
        ;
        U64 _t98 = 0;
        Str *_t99 = Str_lit("value out of range (0-4294967295)", 33ULL);
        Array_set(_va0, &(U64){_t98}, _t99);
        ;
        Str *_t100 = Str_lit("U32.from_i64", 12ULL);
        panic(_t100, _va0);
        Str_delete(_t100, &(Bool){1});
        Array_delete(_va0, &(Bool){1});
    }
    ;
    /* TODO: nested func U32_from_i64_ext */
    U32 _t106 = U32_from_i64_ext(val);
    { U32 *_r = malloc(sizeof(U32)); *_r = _t106; return _r; }
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    I64 _t108 = 0;
    I64 _t109 = 1;
    I64 _t110 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t111 = I64_sub(_t108, _t109);
    ;
    ;
    Bool _t112 = I64_eq(_t110, _t111);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t112; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    I64 _t113 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t114 = 1;
    Bool _t115 = I64_eq(_t113, _t114);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t115; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    Bool _t116 = U32_eq(DEREF(a), DEREF(b));
    Bool _t117 = Bool_not(_t116);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t117; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    Bool _t118; { Bool *_hp = U32_gt(a, b); _t118 = *_hp; free(_hp); }
    Bool _t119 = Bool_not(_t118);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t119; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    Bool _t120; { Bool *_hp = U32_lt(a, b); _t120 = *_hp; free(_hp); }
    Bool _t121 = Bool_not(_t120);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t121; return _r; }
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t122 = U64_to_str_ext(val);
    return _t122;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 _t123 = U64_from_i64_ext(val);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t123; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    I64 _t125 = 0;
    I64 _t126 = 1;
    I64 _t127 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t128 = I64_sub(_t125, _t126);
    ;
    ;
    Bool _t129 = I64_eq(_t127, _t128);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t129; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    I64 _t130 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t131 = 1;
    Bool _t132 = I64_eq(_t130, _t131);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t132; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    Bool _t133 = U64_eq(DEREF(a), DEREF(b));
    Bool _t134 = Bool_not(_t133);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t134; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    Bool _t135; { Bool *_hp = U64_gt(a, b); _t135 = *_hp; free(_hp); }
    Bool _t136 = Bool_not(_t135);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t136; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    Bool _t137; { Bool *_hp = U64_lt(a, b); _t137 = *_hp; free(_hp); }
    Bool _t138 = Bool_not(_t137);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t138; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    I64 _t175 = 0;
    Bool _t176 = I64_eq(DEREF(val), _t175);
    ;
    if (_t176) {
        U64 _t139 = 2;
        U8 *buf = malloc(_t139);
        ;
        I64 _t140 = 48;
        U64 _t141 = 1;
        memcpy(buf, &(I64){_t140}, _t141);
        ;
        ;
        U64 *_t142 = malloc(sizeof(U64));
        *_t142 = 1;
        void *_t143 = ptr_add(buf, DEREF(_t142));
        I64 _t144 = 0;
        U64 _t145 = 1;
        memcpy(_t143, &(I64){_t144}, _t145);
        U64_delete(_t142, &(Bool){1});
        ;
        ;
        I64 _t146 = 1;
        I64 _t147 = 1;
        Str *_t148 = malloc(sizeof(Str));
        _t148->c_str = buf;
        _t148->count = _t146;
        _t148->cap = _t147;
        ;
        ;
        ;
        return _t148;
    }
    ;
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 _t177 = 0;
    Bool _t178; { Bool *_hp = I64_lt(val, &(I64){_t177}); _t178 = *_hp; free(_hp); }
    ;
    if (_t178) {
        Bool _t149 = 1;
        is_neg = _t149;
        ;
        I64 _t150 = 0;
        I64 _t151 = I64_sub(_t150, DEREF(val));
        ;
        v = _t151;
        ;
    }
    ;
    U64 ndigits = 0;
    I64 tmp = I64_clone(&(I64){v});
    while (1) {
        I64 _t153 = 0;
        Bool _wcond152; { Bool *_hp = I64_gt(&(I64){tmp}, &(I64){_t153}); _wcond152 = *_hp; free(_hp); }
        ;
        if (_wcond152) {
        } else {
            ;
            break;
        }
        ;
        U64 _t154 = 1;
        U64 _t155 = U64_add(ndigits, _t154);
        ;
        ndigits = _t155;
        ;
        I64 _t156 = 10;
        I64 _t157 = I64_div(tmp, _t156);
        ;
        tmp = _t157;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    ;
    if (is_neg) {
        U64 _t158 = 1;
        U64 _t159 = U64_add(DEREF(total), _t158);
        ;
        *total = _t159;
        ;
    }
    U64 _t179 = 1;
    U64 _t180 = U64_add(DEREF(total), _t179);
    ;
    U8 *buf = malloc(_t180);
    ;
    if (is_neg) {
        I64 _t160 = 45;
        U64 _t161 = 1;
        memcpy(buf, &(I64){_t160}, _t161);
        ;
        ;
    }
    ;
    U64 _t181 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t181);
    ;
    while (1) {
        I64 _t163 = 0;
        Bool _wcond162; { Bool *_hp = I64_gt(&(I64){v}, &(I64){_t163}); _wcond162 = *_hp; free(_hp); }
        ;
        if (_wcond162) {
        } else {
            ;
            break;
        }
        ;
        I64 _t164 = 10;
        I64 _t165 = I64_mod(v, _t164);
        ;
        I64 _t166 = 48;
        I64 _t167 = I64_add(_t165, _t166);
        ;
        ;
        void *_t168 = ptr_add(buf, DEREF(i));
        U8 _t169 = I64_to_u8(_t167);
        ;
        U64 _t170 = 1;
        memcpy(_t168, &(U8){_t169}, _t170);
        ;
        ;
        I64 _t171 = 10;
        I64 _t172 = I64_div(v, _t171);
        ;
        v = _t172;
        ;
        U64 _t173 = 1;
        U64 _t174 = U64_sub(DEREF(i), _t173);
        ;
        *i = _t174;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t182 = ptr_add(buf, DEREF(total));
    I64 _t183 = 0;
    U64 _t184 = 1;
    memcpy(_t182, &(I64){_t183}, _t184);
    ;
    ;
    U64 _t185 = U64_clone(total);
    U64 _t186 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t187 = malloc(sizeof(Str));
    _t187->c_str = buf;
    _t187->count = _t185;
    _t187->cap = _t186;
    ;
    ;
    return _t187;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    I64 _t188 = 0;
    I64 _t189 = I64_sub(_t188, DEREF(a));
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t189; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    I64 _t192 = 0;
    Bool _t193; { Bool *_hp = I64_lt(a, &(I64){_t192}); _t193 = *_hp; free(_hp); }
    ;
    if (_t193) {
        I64 _t190 = 0;
        I64 _t191 = I64_sub(_t190, DEREF(a));
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t191; return _r; }
    }
    ;
    I64 _t194 = I64_clone(a);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t194; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    I64 _t196 = 0;
    I64 _t197 = 1;
    I64 _t198 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t199 = I64_sub(_t196, _t197);
    ;
    ;
    Bool _t200 = I64_eq(_t198, _t199);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t200; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    I64 _t201 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t202 = 1;
    Bool _t203 = I64_eq(_t201, _t202);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t203; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    Bool _t204 = I64_eq(DEREF(a), DEREF(b));
    Bool _t205 = Bool_not(_t204);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t205; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    Bool _t206; { Bool *_hp = I64_gt(a, b); _t206 = *_hp; free(_hp); }
    Bool _t207 = Bool_not(_t206);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t207; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    Bool _t208; { Bool *_hp = I64_lt(a, b); _t208 = *_hp; free(_hp); }
    Bool _t209 = Bool_not(_t208);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t209; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    U64 _t210 = U64_clone(&(U64){start});
    U64 _t211 = U64_clone(&(U64){end});
    Range *_t212 = malloc(sizeof(Range));
    _t212->start = _t210;
    _t212->end = _t211;
    ;
    ;
    return _t212;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t214; { Bool *_hp = U64_lte(&self->start, &self->end); _t214 = *_hp; free(_hp); }
    if (_t214) {
        U64 _t213 = U64_sub(self->end, self->start);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t213; return _r; }
    }
    ;
    U64 _t215 = U64_sub(self->start, self->end);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t215; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    Bool _t217; { Bool *_hp = U64_lte(&self->start, &self->end); _t217 = *_hp; free(_hp); }
    if (_t217) {
        U64 _t216 = U64_add(self->start, i);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t216; return _r; }
    }
    ;
    U64 _t218 = U64_sub(self->start, i);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t218; return _r; }
}

Range * Range_clone(Range * val) {
    Range *_t219 = malloc(sizeof(Range));
    _t219->start = val->start;
    _t219->end = val->end;
    return _t219;
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
        Str *_t221 = Str_lit("true", 4ULL);
        return _t221;
    } else {
        Str *_t222 = Str_lit("false", 5ULL);
        return _t222;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool _t227 = Bool_eq(DEREF(a), DEREF(b));
    if (_t227) {
        I64 _t223 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t223; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t224 = 0;
        I64 _t225 = 1;
        I64 _t226 = I64_sub(_t224, _t225);
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t226; return _r; }
    }
    I64 _t228 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t228; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    I64 _t230 = 0;
    I64 _t231 = 1;
    I64 _t232; { I64 *_hp = Bool_cmp(a, b); _t232 = *_hp; free(_hp); }
    I64 _t233 = I64_sub(_t230, _t231);
    ;
    ;
    Bool _t234 = I64_eq(_t232, _t233);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t234; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    I64 _t235; { I64 *_hp = Bool_cmp(a, b); _t235 = *_hp; free(_hp); }
    I64 _t236 = 1;
    Bool _t237 = I64_eq(_t235, _t236);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t237; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    Bool _t238 = Bool_eq(DEREF(a), DEREF(b));
    Bool _t239 = Bool_not(_t238);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t239; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    Bool _t240; { Bool *_hp = Bool_gt(a, b); _t240 = *_hp; free(_hp); }
    Bool _t241 = Bool_not(_t240);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t241; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    Bool _t242; { Bool *_hp = Bool_lt(a, b); _t242 = *_hp; free(_hp); }
    Bool _t243 = Bool_not(_t242);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t243; return _r; }
}

void println(Array * parts) {
    {
        U64 *_fi244 = malloc(sizeof(U64));
        *_fi244 = 0;
        while (1) {
            U64 _t246; { U64 *_hp = Array_len(parts); _t246 = *_hp; free(_hp); }
            Bool _wcond245; { Bool *_hp = U64_lt(_fi244, &(U64){_t246}); _wcond245 = *_hp; free(_hp); }
            ;
            if (_wcond245) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi244);
            U64 _t247 = 1;
            U64 _t248 = U64_add(DEREF(_fi244), _t247);
            ;
            *_fi244 = _t248;
            ;
            print_single(s);
        }
        U64_delete(_fi244, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        U64 *_fi249 = malloc(sizeof(U64));
        *_fi249 = 0;
        while (1) {
            U64 _t251; { U64 *_hp = Array_len(parts); _t251 = *_hp; free(_hp); }
            Bool _wcond250; { Bool *_hp = U64_lt(_fi249, &(U64){_t251}); _wcond250 = *_hp; free(_hp); }
            ;
            if (_wcond250) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi249);
            U64 _t252 = 1;
            U64 _t253 = U64_add(DEREF(_fi249), _t252);
            ;
            *_fi249 = _t253;
            ;
            print_single(s);
        }
        U64_delete(_fi249, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 total = 0;
    {
        U64 *_fi254 = malloc(sizeof(U64));
        *_fi254 = 0;
        while (1) {
            U64 _t256; { U64 *_hp = Array_len(parts); _t256 = *_hp; free(_hp); }
            Bool _wcond255; { Bool *_hp = U64_lt(_fi254, &(U64){_t256}); _wcond255 = *_hp; free(_hp); }
            ;
            if (_wcond255) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi254);
            U64 _t257 = 1;
            U64 _t258 = U64_add(DEREF(_fi254), _t257);
            ;
            *_fi254 = _t258;
            ;
            U64 _t259; { U64 *_hp = Str_len(s); _t259 = *_hp; free(_hp); }
            U64 _t260 = U64_add(total, _t259);
            ;
            total = _t260;
            ;
        }
        U64_delete(_fi254, &(Bool){1});
    }
    U8 *buf = malloc(total);
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi261 = malloc(sizeof(U64));
        *_fi261 = 0;
        while (1) {
            U64 _t263; { U64 *_hp = Array_len(parts); _t263 = *_hp; free(_hp); }
            Bool _wcond262; { Bool *_hp = U64_lt(_fi261, &(U64){_t263}); _wcond262 = *_hp; free(_hp); }
            ;
            if (_wcond262) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi261);
            U64 _t264 = 1;
            U64 _t265 = U64_add(DEREF(_fi261), _t264);
            ;
            *_fi261 = _t265;
            ;
            void *_t266 = ptr_add(buf, DEREF(offset));
            U64 _t267; { U64 *_hp = Str_len(s); _t267 = *_hp; free(_hp); }
            memcpy(_t266, s->c_str, _t267);
            ;
            U64 _t268; { U64 *_hp = Str_len(s); _t268 = *_hp; free(_hp); }
            U64 _t269 = U64_add(DEREF(offset), _t268);
            ;
            *offset = _t269;
            ;
        }
        U64_delete(_fi261, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t270 = U64_clone(&(U64){total});
    U64 _t271 = U64_clone(&(U64){total});
    ;
    Str *_t272 = malloc(sizeof(Str));
    _t272->c_str = buf;
    _t272->count = _t270;
    _t272->cap = _t271;
    ;
    ;
    return _t272;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        I64 _t273 = 0;
        I64 _t274 = 1;
        I64 _t275 = I64_sub(_t273, _t274);
        ;
        ;
        Bool _t276; { Bool *_hp = I64_neq(&(I64){status}, &(I64){_t275}); _t276 = *_hp; free(_hp); }
        ;
        if (_t276) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t277 = 50;
        sleep_ms(_t277);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t283; { U64 *_hp = Array_len(args); _t283 = *_hp; free(_hp); }
        Bool _wcond278; { Bool *_hp = U64_lt(i, &(U64){_t283}); _wcond278 = *_hp; free(_hp); }
        ;
        if (_wcond278) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        U64 _t284 = 0;
        Bool _t285; { Bool *_hp = U64_gt(i, &(U64){_t284}); _t285 = *_hp; free(_hp); }
        ;
        if (_t285) {
            Str *_t279 = Str_lit(" '", 2ULL);
            Str *_t280 = Str_concat(cmd, _t279);
            Str_delete(_t279, &(Bool){1});
            Str *_t281 = Str_concat(_t280, arg);
            Str_delete(_t280, &(Bool){1});
            Str *_t282 = Str_lit("'", 1ULL);
            cmd = Str_concat(_t281, _t282);
            Str_delete(_t281, &(Bool){1});
            Str_delete(_t282, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t286 = 1;
        U64 _t287 = U64_add(DEREF(i), _t286);
        ;
        *i = _t287;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    Str *_t288 = Str_lit(" > ", 3ULL);
    Str *_t289 = Str_concat(cmd, _t288);
    Str_delete(_t288, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t290 = Str_concat(_t289, tmpf);
    Str_delete(_t289, &(Bool){1});
    Str *_t291 = Str_lit(" 2>&1", 5ULL);
    Str *_t292 = Str_concat(_t290, _t291);
    Str_delete(_t290, &(Bool){1});
    Str_delete(_t291, &(Bool){1});
    I64 pid; { I64 *_hp = spawn_cmd(_t292); pid = *_hp; free(_hp); }
    Str_delete(_t292, &(Bool){1});
    I64 ec; { I64 *_hp = wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    ;
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 _t293; { U64 *_hp = Str_size(); _t293 = *_hp; free(_hp); }
    memcpy(output, content, _t293);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    Str *_t294 = Str_lit("Str", 3ULL);
    U64 _t295; { U64 *_hp = Str_size(); _t295 = *_hp; free(_hp); }
    U64 _t296 = 3;
    Array *_va1 = Array_new(_t294, &(U64){_t295}, &(U64){_t296});
    Str_delete(_t294, &(Bool){1});
    ;
    ;
    U64 _t297 = 0;
    Str *_t298 = Str_clone(loc_str);
    Array_set(_va1, &(U64){_t297}, _t298);
    ;
    U64 _t299 = 1;
    Str *_t300 = Str_lit(": panic: ", 9ULL);
    Array_set(_va1, &(U64){_t299}, _t300);
    ;
    U64 _t301 = 2;
    Str *_t302 = format(parts);
    Array_set(_va1, &(U64){_t301}, _t302);
    ;
    println(_va1);
    I64 _t303 = 1;
    exit(_t303);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t304 = Str_lit("Str", 3ULL);
    U64 _t305; { U64 *_hp = Str_size(); _t305 = *_hp; free(_hp); }
    U64 _t306 = 2;
    Array *_va2 = Array_new(_t304, &(U64){_t305}, &(U64){_t306});
    Str_delete(_t304, &(Bool){1});
    ;
    ;
    U64 _t307 = 0;
    Str *_t308 = Str_lit("TODO: ", 6ULL);
    Array_set(_va2, &(U64){_t307}, _t308);
    ;
    U64 _t309 = 1;
    Str *_t310 = format(parts);
    Array_set(_va2, &(U64){_t309}, _t310);
    ;
    panic(loc_str, _va2);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t311 = Str_lit("Str", 3ULL);
    U64 _t312; { U64 *_hp = Str_size(); _t312 = *_hp; free(_hp); }
    U64 _t313 = 1;
    Array *_va3 = Array_new(_t311, &(U64){_t312}, &(U64){_t313});
    Str_delete(_t311, &(Bool){1});
    ;
    ;
    U64 _t314 = 0;
    Str *_t315 = Str_lit("unreachable", 11ULL);
    Array_set(_va3, &(U64){_t314}, _t315);
    ;
    panic(loc_str, _va3);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool _t323 = Bool_not(DEREF(cond));
    if (_t323) {
        Str *_t316 = Str_lit("Str", 3ULL);
        U64 _t317; { U64 *_hp = Str_size(); _t317 = *_hp; free(_hp); }
        U64 _t318 = 2;
        Array *_va4 = Array_new(_t316, &(U64){_t317}, &(U64){_t318});
        Str_delete(_t316, &(Bool){1});
        ;
        ;
        U64 _t319 = 0;
        Str *_t320 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va4, &(U64){_t319}, _t320);
        ;
        U64 _t321 = 1;
        Str *_t322 = format(parts);
        Array_set(_va4, &(U64){_t321}, _t322);
        ;
        panic(loc_str, _va4);
    }
    ;
    Bool _t324 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t324; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t325 = Str_lit("Str", 3ULL);
    U64 _t326; { U64 *_hp = Str_size(); _t326 = *_hp; free(_hp); }
    U64 _t327 = 0;
    Array *_va5 = Array_new(_t325, &(U64){_t326}, &(U64){_t327});
    Str_delete(_t325, &(Bool){1});
    ;
    ;
    Bool _t328; { Bool *_hp = assertm(loc_str, cond, _va5); _t328 = *_hp; free(_hp); }
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t328; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t329 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool _t330; { Bool *_hp = assertm(loc_str, cond, _t329); _t330 = *_hp; free(_hp); }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool _t344; { Bool *_hp = I64_neq(a, b); _t344 = *_hp; free(_hp); }
    if (_t344) {
        Str *_t331 = Str_lit("Str", 3ULL);
        U64 _t332; { U64 *_hp = Str_size(); _t332 = *_hp; free(_hp); }
        U64 _t333 = 5;
        Array *_va6 = Array_new(_t331, &(U64){_t332}, &(U64){_t333});
        Str_delete(_t331, &(Bool){1});
        ;
        ;
        U64 _t334 = 0;
        Str *_t335 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va6, &(U64){_t334}, _t335);
        ;
        U64 _t336 = 1;
        Str *_t337 = I64_to_str(a);
        Array_set(_va6, &(U64){_t336}, _t337);
        ;
        U64 _t338 = 2;
        Str *_t339 = Str_lit("', found '", 10ULL);
        Array_set(_va6, &(U64){_t338}, _t339);
        ;
        U64 _t340 = 3;
        Str *_t341 = I64_to_str(b);
        Array_set(_va6, &(U64){_t340}, _t341);
        ;
        U64 _t342 = 4;
        Str *_t343 = Str_lit("'", 1ULL);
        Array_set(_va6, &(U64){_t342}, _t343);
        ;
        panic(loc_str, _va6);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool _t358; { Bool *_hp = Str_eq(a, b); _t358 = *_hp; free(_hp); }
    Bool _t359 = Bool_not(_t358);
    ;
    if (_t359) {
        Str *_t345 = Str_lit("Str", 3ULL);
        U64 _t346; { U64 *_hp = Str_size(); _t346 = *_hp; free(_hp); }
        U64 _t347 = 5;
        Array *_va7 = Array_new(_t345, &(U64){_t346}, &(U64){_t347});
        Str_delete(_t345, &(Bool){1});
        ;
        ;
        U64 _t348 = 0;
        Str *_t349 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va7, &(U64){_t348}, _t349);
        ;
        U64 _t350 = 1;
        Str *_t351 = Str_clone(a);
        Array_set(_va7, &(U64){_t350}, _t351);
        ;
        U64 _t352 = 2;
        Str *_t353 = Str_lit("', found '", 10ULL);
        Array_set(_va7, &(U64){_t352}, _t353);
        ;
        U64 _t354 = 3;
        Str *_t355 = Str_clone(b);
        Array_set(_va7, &(U64){_t354}, _t355);
        ;
        U64 _t356 = 4;
        Str *_t357 = Str_lit("'", 1ULL);
        Array_set(_va7, &(U64){_t356}, _t357);
        ;
        panic(loc_str, _va7);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    void *_t360 = calloc(DEREF(cap), DEREF(elem_size));
    U64 _t361 = U64_clone(cap);
    U64 _t362 = U64_clone(elem_size);
    Array *_t363 = malloc(sizeof(Array));
    _t363->data = _t360;
    _t363->cap = _t361;
    _t363->elem_size = _t362;
    { Str *_ca = Str_clone(elem_type); _t363->elem_type = *_ca; free(_ca); }
    ;
    ;
    return _t363;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    Bool _t378; { Bool *_hp = U64_gte(i, &self->cap); _t378 = *_hp; free(_hp); }
    if (_t378) {
        Str *_t364 = Str_lit("Str", 3ULL);
        U64 _t365; { U64 *_hp = Str_size(); _t365 = *_hp; free(_hp); }
        U64 _t366 = 5;
        Array *_va8 = Array_new(_t364, &(U64){_t365}, &(U64){_t366});
        Str_delete(_t364, &(Bool){1});
        ;
        ;
        U64 _t367 = 0;
        Str *_t368 = Str_lit("index ", 6ULL);
        Array_set(_va8, &(U64){_t367}, _t368);
        ;
        U64 _t369 = 1;
        Str *_t370 = U64_to_str(DEREF(i));
        Array_set(_va8, &(U64){_t369}, _t370);
        ;
        U64 _t371 = 2;
        Str *_t372 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va8, &(U64){_t371}, _t372);
        ;
        U64 _t373 = 3;
        Str *_t374 = U64_to_str(self->cap);
        Array_set(_va8, &(U64){_t373}, _t374);
        ;
        U64 _t375 = 4;
        Str *_t376 = Str_lit(")", 1ULL);
        Array_set(_va8, &(U64){_t375}, _t376);
        ;
        Str *_t377 = Str_lit("Array.get", 9ULL);
        panic(_t377, _va8);
        Str_delete(_t377, &(Bool){1});
    }
    ;
    U64 *_t379 = malloc(sizeof(U64)); *_t379 = U64_mul(DEREF(i), self->elem_size);
    void *_t380 = ptr_add(self->data, DEREF(_t379));
    U64_delete(_t379, &(Bool){1});
    return _t380;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    Bool _t395; { Bool *_hp = U64_gte(i, &self->cap); _t395 = *_hp; free(_hp); }
    if (_t395) {
        Str *_t381 = Str_lit("Str", 3ULL);
        U64 _t382; { U64 *_hp = Str_size(); _t382 = *_hp; free(_hp); }
        U64 _t383 = 5;
        Array *_va9 = Array_new(_t381, &(U64){_t382}, &(U64){_t383});
        Str_delete(_t381, &(Bool){1});
        ;
        ;
        U64 _t384 = 0;
        Str *_t385 = Str_lit("index ", 6ULL);
        Array_set(_va9, &(U64){_t384}, _t385);
        ;
        U64 _t386 = 1;
        Str *_t387 = U64_to_str(DEREF(i));
        Array_set(_va9, &(U64){_t386}, _t387);
        ;
        U64 _t388 = 2;
        Str *_t389 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va9, &(U64){_t388}, _t389);
        ;
        U64 _t390 = 3;
        Str *_t391 = U64_to_str(self->cap);
        Array_set(_va9, &(U64){_t390}, _t391);
        ;
        U64 _t392 = 4;
        Str *_t393 = Str_lit(")", 1ULL);
        Array_set(_va9, &(U64){_t392}, _t393);
        ;
        Str *_t394 = Str_lit("Array.set", 9ULL);
        panic(_t394, _va9);
        Str_delete(_t394, &(Bool){1});
    }
    ;
    U64 *_t396 = malloc(sizeof(U64)); *_t396 = U64_mul(DEREF(i), self->elem_size);
    void *_t397 = ptr_add(self->data, DEREF(_t396));
    Bool _t398 = 0;
    dyn_call_delete(&self->elem_type, _t397, &(Bool){_t398});
    U64_delete(_t396, &(Bool){1});
    ;
    U64 *_t399 = malloc(sizeof(U64)); *_t399 = U64_mul(DEREF(i), self->elem_size);
    void *_t400 = ptr_add(self->data, DEREF(_t399));
    memcpy(_t400, val, self->elem_size);
    U64_delete(_t399, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    {
        U64 _fi401 = 0;
        while (1) {
            U64 _t403 = 0;
            Range *_t404 = Range_new(_t403, self->cap);
            ;
            U64 _t405; { U64 *_hp = Range_len(_t404); _t405 = *_hp; free(_hp); }
            Range_delete(_t404, &(Bool){1});
            Bool _wcond402; { Bool *_hp = U64_lt(&(U64){_fi401}, &(U64){_t405}); _wcond402 = *_hp; free(_hp); }
            ;
            if (_wcond402) {
            } else {
                ;
                break;
            }
            ;
            U64 _t406 = 0;
            Range *_t407 = Range_new(_t406, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t407, _fi401); i = *_hp; free(_hp); }
            Range_delete(_t407, &(Bool){1});
            U64 _t408 = 1;
            U64 _t409 = U64_add(_fi401, _t408);
            ;
            _fi401 = _t409;
            ;
            U64 *_t410 = malloc(sizeof(U64)); *_t410 = U64_mul(i, self->elem_size);
            ;
            void *_t411 = ptr_add(self->data, DEREF(_t410));
            Bool _t412 = 0;
            dyn_call_delete(&self->elem_type, _t411, &(Bool){_t412});
            U64_delete(_t410, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t413 = 0;
    Str_delete(&self->elem_type, &(Bool){_t413});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t427 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t427);
    ;
    {
        U64 _fi414 = 0;
        while (1) {
            U64 _t416 = 0;
            Range *_t417 = Range_new(_t416, self->cap);
            ;
            U64 _t418; { U64 *_hp = Range_len(_t417); _t418 = *_hp; free(_hp); }
            Range_delete(_t417, &(Bool){1});
            Bool _wcond415; { Bool *_hp = U64_lt(&(U64){_fi414}, &(U64){_t418}); _wcond415 = *_hp; free(_hp); }
            ;
            if (_wcond415) {
            } else {
                ;
                break;
            }
            ;
            U64 _t419 = 0;
            Range *_t420 = Range_new(_t419, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t420, _fi414); i = *_hp; free(_hp); }
            Range_delete(_t420, &(Bool){1});
            U64 _t421 = 1;
            U64 _t422 = U64_add(_fi414, _t421);
            ;
            _fi414 = _t422;
            ;
            U64 *_t423 = malloc(sizeof(U64)); *_t423 = U64_mul(i, self->elem_size);
            void *_t424 = ptr_add(self->data, DEREF(_t423));
            void *cloned = dyn_call_clone(&self->elem_type, _t424);
            U64_delete(_t423, &(Bool){1});
            U64 *_t425 = malloc(sizeof(U64)); *_t425 = U64_mul(i, self->elem_size);
            ;
            void *_t426 = ptr_add(new_data, DEREF(_t425));
            memcpy(_t426, cloned, self->elem_size);
            U64_delete(_t425, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t428 = malloc(sizeof(Array));
    _t428->data = new_data;
    _t428->cap = self->cap;
    _t428->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t428->elem_type = *_ca; free(_ca); }
    return _t428;
}

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    Bool _t442; { Bool *_hp = Str_is_empty(key_type); _t442 = *_hp; free(_hp); }
    Bool _t443 = Bool_not(_t442);
    ;
    if (_t443) {
        Bool _t440 = dyn_has_cmp(key_type);
        Bool _t441 = Bool_not(_t440);
        ;
        if (_t441) {
            Str *_t430 = Str_lit("Str", 3ULL);
            U64 _t431; { U64 *_hp = Str_size(); _t431 = *_hp; free(_hp); }
            U64 _t432 = 3;
            Array *_va10 = Array_new(_t430, &(U64){_t431}, &(U64){_t432});
            Str_delete(_t430, &(Bool){1});
            ;
            ;
            U64 _t433 = 0;
            Str *_t434 = Str_lit("type ", 5ULL);
            Array_set(_va10, &(U64){_t433}, _t434);
            ;
            U64 _t435 = 1;
            Str *_t436 = Str_clone(key_type);
            Array_set(_va10, &(U64){_t435}, _t436);
            ;
            U64 _t437 = 2;
            Str *_t438 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va10, &(U64){_t437}, _t438);
            ;
            Str *_t439 = Str_lit("Map.new", 7ULL);
            panic(_t439, _va10);
            Str_delete(_t439, &(Bool){1});
        }
        ;
    }
    ;
    void *_t444 = malloc(DEREF(key_size));
    void *_t445 = malloc(DEREF(val_size));
    U64 _t446 = 0;
    I64 _t447 = 1;
    U64 _t448 = U64_clone(key_size);
    U64 _t449 = U64_clone(val_size);
    Map *_t450 = malloc(sizeof(Map));
    _t450->key_data = _t444;
    _t450->val_data = _t445;
    _t450->count = _t446;
    _t450->cap = _t447;
    _t450->key_size = _t448;
    { Str *_ca = Str_clone(key_type); _t450->key_type = *_ca; free(_ca); }
    _t450->val_size = _t449;
    { Str *_ca = Str_clone(val_type); _t450->val_type = *_ca; free(_ca); }
    ;
    ;
    ;
    ;
    return _t450;
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
        Bool _wcond451; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond451 = *_hp; free(_hp); }
        if (_wcond451) {
        } else {
            ;
            break;
        }
        ;
        U64 _t458 = U64_sub(hi, lo);
        U64 _t459 = 2;
        U64 _t460 = U64_div(_t458, _t459);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t460);
        ;
        U64 *_t461 = malloc(sizeof(U64)); *_t461 = U64_mul(DEREF(mid), self->key_size);
        void *_t462 = ptr_add(self->key_data, DEREF(_t461));
        I64 *c = dyn_call_cmp(&self->key_type, _t462, key);
        U64_delete(_t461, &(Bool){1});
        I64 _t463 = 0;
        Bool _t464; { Bool *_hp = I64_lt(c, &(I64){_t463}); _t464 = *_hp; free(_hp); }
        ;
        if (_t464) {
            U64 _t452 = 1;
            U64 _t453 = U64_add(DEREF(mid), _t452);
            ;
            lo = _t453;
            ;
        } else {
            I64 _t456 = 0;
            Bool _t457; { Bool *_hp = I64_gt(c, &(I64){_t456}); _t457 = *_hp; free(_hp); }
            ;
            if (_t457) {
                U64 _t454 = U64_clone(mid);
                hi = _t454;
                ;
            } else {
                Bool _t455 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t455; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t465 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t465; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond466; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond466 = *_hp; free(_hp); }
        if (_wcond466) {
        } else {
            ;
            break;
        }
        ;
        U64 _t474 = U64_sub(hi, lo);
        U64 _t475 = 2;
        U64 _t476 = U64_div(_t474, _t475);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t476);
        ;
        U64 *_t477 = malloc(sizeof(U64)); *_t477 = U64_mul(DEREF(mid), self->key_size);
        void *_t478 = ptr_add(self->key_data, DEREF(_t477));
        I64 *c = dyn_call_cmp(&self->key_type, _t478, key);
        U64_delete(_t477, &(Bool){1});
        I64 _t479 = 0;
        Bool _t480; { Bool *_hp = I64_lt(c, &(I64){_t479}); _t480 = *_hp; free(_hp); }
        ;
        if (_t480) {
            U64 _t467 = 1;
            U64 _t468 = U64_add(DEREF(mid), _t467);
            ;
            lo = _t468;
            ;
        } else {
            I64 _t472 = 0;
            Bool _t473; { Bool *_hp = I64_gt(c, &(I64){_t472}); _t473 = *_hp; free(_hp); }
            ;
            if (_t473) {
                U64 _t469 = U64_clone(mid);
                hi = _t469;
                ;
            } else {
                U64 *_t470 = malloc(sizeof(U64)); *_t470 = U64_mul(DEREF(mid), self->val_size);
                void *_t471 = ptr_add(self->val_data, DEREF(_t470));
                U64_delete(_t470, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t471;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t481 = Str_lit("Str", 3ULL);
    U64 _t482; { U64 *_hp = Str_size(); _t482 = *_hp; free(_hp); }
    U64 _t483 = 1;
    Array *_va11 = Array_new(_t481, &(U64){_t482}, &(U64){_t483});
    Str_delete(_t481, &(Bool){1});
    ;
    ;
    U64 _t484 = 0;
    Str *_t485 = Str_lit("key not found", 13ULL);
    Array_set(_va11, &(U64){_t484}, _t485);
    ;
    Str *_t486 = Str_lit("Map.get", 7ULL);
    panic(_t486, _va11);
    Str_delete(_t486, &(Bool){1});
    U64 *_t487 = malloc(sizeof(U64));
    *_t487 = 0;
    void *_t488 = ptr_add(self->val_data, DEREF(_t487));
    U64_delete(_t487, &(Bool){1});
    return _t488;
}

void Map_set(Map * self, void * key, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond489; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond489 = *_hp; free(_hp); }
        if (_wcond489) {
        } else {
            ;
            break;
        }
        ;
        U64 _t498 = U64_sub(hi, lo);
        U64 _t499 = 2;
        U64 _t500 = U64_div(_t498, _t499);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t500);
        ;
        U64 *_t501 = malloc(sizeof(U64)); *_t501 = U64_mul(DEREF(mid), self->key_size);
        void *_t502 = ptr_add(self->key_data, DEREF(_t501));
        I64 *c = dyn_call_cmp(&self->key_type, _t502, key);
        U64_delete(_t501, &(Bool){1});
        I64 _t503 = 0;
        Bool _t504; { Bool *_hp = I64_lt(c, &(I64){_t503}); _t504 = *_hp; free(_hp); }
        ;
        if (_t504) {
            U64 _t490 = 1;
            U64 _t491 = U64_add(DEREF(mid), _t490);
            ;
            lo = _t491;
            ;
        } else {
            I64 _t496 = 0;
            Bool _t497; { Bool *_hp = I64_gt(c, &(I64){_t496}); _t497 = *_hp; free(_hp); }
            ;
            if (_t497) {
                U64 _t492 = U64_clone(mid);
                hi = _t492;
                ;
            } else {
                Bool _t493 = 1;
                found = _t493;
                ;
                U64 _t494 = U64_clone(mid);
                lo = _t494;
                ;
                U64 _t495 = U64_clone(mid);
                hi = _t495;
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
        Bool _t509; { Bool *_hp = Str_is_empty(&self->key_type); _t509 = *_hp; free(_hp); }
        Bool _t510 = Bool_not(_t509);
        ;
        if (_t510) {
            Bool _t505 = 0;
            dyn_call_delete(&self->key_type, key, &(Bool){_t505});
            ;
        }
        ;
        free(key);
        Bool _t511; { Bool *_hp = Str_is_empty(&self->val_type); _t511 = *_hp; free(_hp); }
        Bool _t512 = Bool_not(_t511);
        ;
        if (_t512) {
            U64 *_t506 = malloc(sizeof(U64)); *_t506 = U64_mul(lo, self->val_size);
            void *_t507 = ptr_add(self->val_data, DEREF(_t506));
            Bool _t508 = 0;
            dyn_call_delete(&self->val_type, _t507, &(Bool){_t508});
            U64_delete(_t506, &(Bool){1});
            ;
        }
        ;
        U64 *_t513 = malloc(sizeof(U64)); *_t513 = U64_mul(lo, self->val_size);
        void *_t514 = ptr_add(self->val_data, DEREF(_t513));
        memcpy(_t514, val, self->val_size);
        U64_delete(_t513, &(Bool){1});
        free(val);
    } else {
        Bool _t521 = U64_eq(self->count, self->cap);
        if (_t521) {
            U64 _t515 = 2;
            U64 new_cap = U64_mul(self->cap, _t515);
            ;
            U64 _t516 = U64_mul(new_cap, self->key_size);
            void *_t517 = realloc(self->key_data, _t516);
            ;
            self->key_data = _t517;
            U64 _t518 = U64_mul(new_cap, self->val_size);
            void *_t519 = realloc(self->val_data, _t518);
            ;
            self->val_data = _t519;
            U64 _t520 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t520;
            ;
        }
        ;
        U64 _t522 = 1;
        U64 _t523 = U64_add(lo, _t522);
        ;
        U64 *_t524 = malloc(sizeof(U64)); *_t524 = U64_mul(_t523, self->key_size);
        ;
        U64 *_t525 = malloc(sizeof(U64)); *_t525 = U64_mul(lo, self->key_size);
        U64 _t526 = U64_sub(self->count, lo);
        void *_t527 = ptr_add(self->key_data, DEREF(_t524));
        void *_t528 = ptr_add(self->key_data, DEREF(_t525));
        U64 _t529 = U64_mul(_t526, self->key_size);
        ;
        memmove(_t527, _t528, _t529);
        U64_delete(_t524, &(Bool){1});
        U64_delete(_t525, &(Bool){1});
        ;
        U64 _t530 = 1;
        U64 _t531 = U64_add(lo, _t530);
        ;
        U64 *_t532 = malloc(sizeof(U64)); *_t532 = U64_mul(_t531, self->val_size);
        ;
        U64 *_t533 = malloc(sizeof(U64)); *_t533 = U64_mul(lo, self->val_size);
        U64 _t534 = U64_sub(self->count, lo);
        void *_t535 = ptr_add(self->val_data, DEREF(_t532));
        void *_t536 = ptr_add(self->val_data, DEREF(_t533));
        U64 _t537 = U64_mul(_t534, self->val_size);
        ;
        memmove(_t535, _t536, _t537);
        U64_delete(_t532, &(Bool){1});
        U64_delete(_t533, &(Bool){1});
        ;
        U64 *_t538 = malloc(sizeof(U64)); *_t538 = U64_mul(lo, self->key_size);
        void *_t539 = ptr_add(self->key_data, DEREF(_t538));
        memcpy(_t539, key, self->key_size);
        U64_delete(_t538, &(Bool){1});
        U64 *_t540 = malloc(sizeof(U64)); *_t540 = U64_mul(lo, self->val_size);
        void *_t541 = ptr_add(self->val_data, DEREF(_t540));
        memcpy(_t541, val, self->val_size);
        U64_delete(_t540, &(Bool){1});
        free(key);
        free(val);
        U64 _t542 = 1;
        U64 _t543 = U64_add(self->count, _t542);
        ;
        self->count = _t543;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    Bool _t570; { Bool *_hp = Str_is_empty(&self->key_type); _t570 = *_hp; free(_hp); }
    Bool _t571 = Bool_not(_t570);
    ;
    if (_t571) {
        {
            U64 _fi544 = 0;
            while (1) {
                U64 _t546 = 0;
                Range *_t547 = Range_new(_t546, self->count);
                ;
                U64 _t548; { U64 *_hp = Range_len(_t547); _t548 = *_hp; free(_hp); }
                Range_delete(_t547, &(Bool){1});
                Bool _wcond545; { Bool *_hp = U64_lt(&(U64){_fi544}, &(U64){_t548}); _wcond545 = *_hp; free(_hp); }
                ;
                if (_wcond545) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t549 = 0;
                Range *_t550 = Range_new(_t549, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t550, _fi544); i = *_hp; free(_hp); }
                Range_delete(_t550, &(Bool){1});
                U64 _t551 = 1;
                U64 _t552 = U64_add(_fi544, _t551);
                ;
                _fi544 = _t552;
                ;
                U64 *_t553 = malloc(sizeof(U64)); *_t553 = U64_mul(i, self->key_size);
                ;
                void *_t554 = ptr_add(self->key_data, DEREF(_t553));
                Bool _t555 = 0;
                dyn_call_delete(&self->key_type, _t554, &(Bool){_t555});
                U64_delete(_t553, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t572; { Bool *_hp = Str_is_empty(&self->val_type); _t572 = *_hp; free(_hp); }
    Bool _t573 = Bool_not(_t572);
    ;
    if (_t573) {
        {
            U64 _fi556 = 0;
            while (1) {
                U64 _t558 = 0;
                Range *_t559 = Range_new(_t558, self->count);
                ;
                U64 _t560; { U64 *_hp = Range_len(_t559); _t560 = *_hp; free(_hp); }
                Range_delete(_t559, &(Bool){1});
                Bool _wcond557; { Bool *_hp = U64_lt(&(U64){_fi556}, &(U64){_t560}); _wcond557 = *_hp; free(_hp); }
                ;
                if (_wcond557) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t561 = 0;
                Range *_t562 = Range_new(_t561, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t562, _fi556); i = *_hp; free(_hp); }
                Range_delete(_t562, &(Bool){1});
                U64 _t563 = 1;
                U64 _t564 = U64_add(_fi556, _t563);
                ;
                _fi556 = _t564;
                ;
                U64 *_t565 = malloc(sizeof(U64)); *_t565 = U64_mul(i, self->val_size);
                ;
                void *_t566 = ptr_add(self->val_data, DEREF(_t565));
                Bool _t567 = 0;
                dyn_call_delete(&self->val_type, _t566, &(Bool){_t567});
                U64_delete(_t565, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t574; { Bool *_hp = Str_is_empty(&self->key_type); _t574 = *_hp; free(_hp); }
    Bool _t575 = Bool_not(_t574);
    ;
    if (_t575) {
        Bool _t568 = 0;
        Str_delete(&self->key_type, &(Bool){_t568});
        ;
    }
    ;
    Bool _t576; { Bool *_hp = Str_is_empty(&self->val_type); _t576 = *_hp; free(_hp); }
    Bool _t577 = Bool_not(_t576);
    ;
    if (_t577) {
        Bool _t569 = 0;
        Str_delete(&self->val_type, &(Bool){_t569});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t595 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(_t595);
    ;
    U64 _t596 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(_t596);
    ;
    {
        U64 _fi578 = 0;
        while (1) {
            U64 _t580 = 0;
            Range *_t581 = Range_new(_t580, self->count);
            ;
            U64 _t582; { U64 *_hp = Range_len(_t581); _t582 = *_hp; free(_hp); }
            Range_delete(_t581, &(Bool){1});
            Bool _wcond579; { Bool *_hp = U64_lt(&(U64){_fi578}, &(U64){_t582}); _wcond579 = *_hp; free(_hp); }
            ;
            if (_wcond579) {
            } else {
                ;
                break;
            }
            ;
            U64 _t583 = 0;
            Range *_t584 = Range_new(_t583, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t584, _fi578); i = *_hp; free(_hp); }
            Range_delete(_t584, &(Bool){1});
            U64 _t585 = 1;
            U64 _t586 = U64_add(_fi578, _t585);
            ;
            _fi578 = _t586;
            ;
            U64 *_t587 = malloc(sizeof(U64)); *_t587 = U64_mul(i, self->key_size);
            void *_t588 = ptr_add(self->key_data, DEREF(_t587));
            void *ck = dyn_call_clone(&self->key_type, _t588);
            U64_delete(_t587, &(Bool){1});
            U64 *_t589 = malloc(sizeof(U64)); *_t589 = U64_mul(i, self->key_size);
            void *_t590 = ptr_add(new_keys, DEREF(_t589));
            memcpy(_t590, ck, self->key_size);
            U64_delete(_t589, &(Bool){1});
            free(ck);
            U64 *_t591 = malloc(sizeof(U64)); *_t591 = U64_mul(i, self->val_size);
            void *_t592 = ptr_add(self->val_data, DEREF(_t591));
            void *cv = dyn_call_clone(&self->val_type, _t592);
            U64_delete(_t591, &(Bool){1});
            U64 *_t593 = malloc(sizeof(U64)); *_t593 = U64_mul(i, self->val_size);
            ;
            void *_t594 = ptr_add(new_vals, DEREF(_t593));
            memcpy(_t594, cv, self->val_size);
            U64_delete(_t593, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t597 = malloc(sizeof(Map));
    _t597->key_data = new_keys;
    _t597->val_data = new_vals;
    _t597->count = self->count;
    _t597->cap = self->cap;
    _t597->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t597->key_type = *_ca; free(_ca); }
    _t597->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t597->val_type = *_ca; free(_ca); }
    return _t597;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    Bool _t611; { Bool *_hp = Str_is_empty(elem_type); _t611 = *_hp; free(_hp); }
    Bool _t612 = Bool_not(_t611);
    ;
    if (_t612) {
        Bool _t609 = dyn_has_cmp(elem_type);
        Bool _t610 = Bool_not(_t609);
        ;
        if (_t610) {
            Str *_t599 = Str_lit("Str", 3ULL);
            U64 _t600; { U64 *_hp = Str_size(); _t600 = *_hp; free(_hp); }
            U64 _t601 = 3;
            Array *_va12 = Array_new(_t599, &(U64){_t600}, &(U64){_t601});
            Str_delete(_t599, &(Bool){1});
            ;
            ;
            U64 _t602 = 0;
            Str *_t603 = Str_lit("type ", 5ULL);
            Array_set(_va12, &(U64){_t602}, _t603);
            ;
            U64 _t604 = 1;
            Str *_t605 = Str_clone(elem_type);
            Array_set(_va12, &(U64){_t604}, _t605);
            ;
            U64 _t606 = 2;
            Str *_t607 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va12, &(U64){_t606}, _t607);
            ;
            Str *_t608 = Str_lit("Set.new", 7ULL);
            panic(_t608, _va12);
            Str_delete(_t608, &(Bool){1});
        }
        ;
    }
    ;
    void *_t613 = malloc(DEREF(elem_size));
    U64 _t614 = 0;
    I64 _t615 = 1;
    U64 _t616 = U64_clone(elem_size);
    Set *_t617 = malloc(sizeof(Set));
    _t617->data = _t613;
    _t617->count = _t614;
    _t617->cap = _t615;
    _t617->elem_size = _t616;
    { Str *_ca = Str_clone(elem_type); _t617->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t617;
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
        Bool _wcond618; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond618 = *_hp; free(_hp); }
        if (_wcond618) {
        } else {
            ;
            break;
        }
        ;
        U64 _t625 = U64_sub(hi, lo);
        U64 _t626 = 2;
        U64 _t627 = U64_div(_t625, _t626);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t627);
        ;
        U64 *_t628 = malloc(sizeof(U64)); *_t628 = U64_mul(DEREF(mid), self->elem_size);
        void *_t629 = ptr_add(self->data, DEREF(_t628));
        I64 *c = dyn_call_cmp(&self->elem_type, _t629, val);
        U64_delete(_t628, &(Bool){1});
        I64 _t630 = 0;
        Bool _t631; { Bool *_hp = I64_lt(c, &(I64){_t630}); _t631 = *_hp; free(_hp); }
        ;
        if (_t631) {
            U64 _t619 = 1;
            U64 _t620 = U64_add(DEREF(mid), _t619);
            ;
            lo = _t620;
            ;
        } else {
            I64 _t623 = 0;
            Bool _t624; { Bool *_hp = I64_gt(c, &(I64){_t623}); _t624 = *_hp; free(_hp); }
            ;
            if (_t624) {
                U64 _t621 = U64_clone(mid);
                hi = _t621;
                ;
            } else {
                Bool _t622 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t622; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t632 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t632; return _r; }
}

void Set_add(Set * self, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond633; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond633 = *_hp; free(_hp); }
        if (_wcond633) {
        } else {
            ;
            break;
        }
        ;
        U64 _t642 = U64_sub(hi, lo);
        U64 _t643 = 2;
        U64 _t644 = U64_div(_t642, _t643);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t644);
        ;
        U64 *_t645 = malloc(sizeof(U64)); *_t645 = U64_mul(DEREF(mid), self->elem_size);
        void *_t646 = ptr_add(self->data, DEREF(_t645));
        I64 *c = dyn_call_cmp(&self->elem_type, _t646, val);
        U64_delete(_t645, &(Bool){1});
        I64 _t647 = 0;
        Bool _t648; { Bool *_hp = I64_lt(c, &(I64){_t647}); _t648 = *_hp; free(_hp); }
        ;
        if (_t648) {
            U64 _t634 = 1;
            U64 _t635 = U64_add(DEREF(mid), _t634);
            ;
            lo = _t635;
            ;
        } else {
            I64 _t640 = 0;
            Bool _t641; { Bool *_hp = I64_gt(c, &(I64){_t640}); _t641 = *_hp; free(_hp); }
            ;
            if (_t641) {
                U64 _t636 = U64_clone(mid);
                hi = _t636;
                ;
            } else {
                Bool _t637 = 1;
                found = _t637;
                ;
                U64 _t638 = U64_clone(mid);
                lo = _t638;
                ;
                U64 _t639 = U64_clone(mid);
                hi = _t639;
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
        Bool _t650; { Bool *_hp = Str_is_empty(&self->elem_type); _t650 = *_hp; free(_hp); }
        Bool _t651 = Bool_not(_t650);
        ;
        if (_t651) {
            Bool _t649 = 0;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t649});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t656 = U64_eq(self->count, self->cap);
        if (_t656) {
            U64 _t652 = 2;
            U64 new_cap = U64_mul(self->cap, _t652);
            ;
            U64 _t653 = U64_mul(new_cap, self->elem_size);
            void *_t654 = realloc(self->data, _t653);
            ;
            self->data = _t654;
            U64 _t655 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t655;
            ;
        }
        ;
        U64 _t657 = 1;
        U64 _t658 = U64_add(lo, _t657);
        ;
        U64 *_t659 = malloc(sizeof(U64)); *_t659 = U64_mul(_t658, self->elem_size);
        ;
        U64 *_t660 = malloc(sizeof(U64)); *_t660 = U64_mul(lo, self->elem_size);
        U64 _t661 = U64_sub(self->count, lo);
        void *_t662 = ptr_add(self->data, DEREF(_t659));
        void *_t663 = ptr_add(self->data, DEREF(_t660));
        U64 _t664 = U64_mul(_t661, self->elem_size);
        ;
        memmove(_t662, _t663, _t664);
        U64_delete(_t659, &(Bool){1});
        U64_delete(_t660, &(Bool){1});
        ;
        U64 *_t665 = malloc(sizeof(U64)); *_t665 = U64_mul(lo, self->elem_size);
        void *_t666 = ptr_add(self->data, DEREF(_t665));
        memcpy(_t666, val, self->elem_size);
        U64_delete(_t665, &(Bool){1});
        free(val);
        U64 _t667 = 1;
        U64 _t668 = U64_add(self->count, _t667);
        ;
        self->count = _t668;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    Bool _t682; { Bool *_hp = Str_is_empty(&self->elem_type); _t682 = *_hp; free(_hp); }
    Bool _t683 = Bool_not(_t682);
    ;
    if (_t683) {
        {
            U64 _fi669 = 0;
            while (1) {
                U64 _t671 = 0;
                Range *_t672 = Range_new(_t671, self->count);
                ;
                U64 _t673; { U64 *_hp = Range_len(_t672); _t673 = *_hp; free(_hp); }
                Range_delete(_t672, &(Bool){1});
                Bool _wcond670; { Bool *_hp = U64_lt(&(U64){_fi669}, &(U64){_t673}); _wcond670 = *_hp; free(_hp); }
                ;
                if (_wcond670) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t674 = 0;
                Range *_t675 = Range_new(_t674, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t675, _fi669); i = *_hp; free(_hp); }
                Range_delete(_t675, &(Bool){1});
                U64 _t676 = 1;
                U64 _t677 = U64_add(_fi669, _t676);
                ;
                _fi669 = _t677;
                ;
                U64 *_t678 = malloc(sizeof(U64)); *_t678 = U64_mul(i, self->elem_size);
                ;
                void *_t679 = ptr_add(self->data, DEREF(_t678));
                Bool _t680 = 0;
                dyn_call_delete(&self->elem_type, _t679, &(Bool){_t680});
                U64_delete(_t678, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t684; { Bool *_hp = Str_is_empty(&self->elem_type); _t684 = *_hp; free(_hp); }
    Bool _t685 = Bool_not(_t684);
    ;
    if (_t685) {
        Bool _t681 = 0;
        Str_delete(&self->elem_type, &(Bool){_t681});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t699 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t699);
    ;
    {
        U64 _fi686 = 0;
        while (1) {
            U64 _t688 = 0;
            Range *_t689 = Range_new(_t688, self->count);
            ;
            U64 _t690; { U64 *_hp = Range_len(_t689); _t690 = *_hp; free(_hp); }
            Range_delete(_t689, &(Bool){1});
            Bool _wcond687; { Bool *_hp = U64_lt(&(U64){_fi686}, &(U64){_t690}); _wcond687 = *_hp; free(_hp); }
            ;
            if (_wcond687) {
            } else {
                ;
                break;
            }
            ;
            U64 _t691 = 0;
            Range *_t692 = Range_new(_t691, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t692, _fi686); i = *_hp; free(_hp); }
            Range_delete(_t692, &(Bool){1});
            U64 _t693 = 1;
            U64 _t694 = U64_add(_fi686, _t693);
            ;
            _fi686 = _t694;
            ;
            U64 *_t695 = malloc(sizeof(U64)); *_t695 = U64_mul(i, self->elem_size);
            void *_t696 = ptr_add(self->data, DEREF(_t695));
            void *cloned = dyn_call_clone(&self->elem_type, _t696);
            U64_delete(_t695, &(Bool){1});
            U64 *_t697 = malloc(sizeof(U64)); *_t697 = U64_mul(i, self->elem_size);
            ;
            void *_t698 = ptr_add(new_data, DEREF(_t697));
            memcpy(_t698, cloned, self->elem_size);
            U64_delete(_t697, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t700 = malloc(sizeof(Set));
    _t700->data = new_data;
    _t700->count = self->count;
    _t700->cap = self->cap;
    _t700->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t700->elem_type = *_ca; free(_ca); }
    return _t700;
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
    Bool _t708; { Bool *_hp = U64_gte(i, &self->count); _t708 = *_hp; free(_hp); }
    if (_t708) {
        Str *_t702 = Str_lit("Str", 3ULL);
        U64 _t703; { U64 *_hp = Str_size(); _t703 = *_hp; free(_hp); }
        U64 _t704 = 1;
        Array *_va13 = Array_new(_t702, &(U64){_t703}, &(U64){_t704});
        Str_delete(_t702, &(Bool){1});
        ;
        ;
        U64 _t705 = 0;
        Str *_t706 = Str_lit("index out of bounds", 19ULL);
        Array_set(_va13, &(U64){_t705}, _t706);
        ;
        Str *_t707 = Str_lit("Str.get", 7ULL);
        panic(_t707, _va13);
        Str_delete(_t707, &(Bool){1});
    }
    ;
    void *_t709 = ptr_add(self->c_str, DEREF(i));
    return _t709;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 min_len = a->count;
    Bool _t715; { Bool *_hp = U64_lt(&b->count, &a->count); _t715 = *_hp; free(_hp); }
    if (_t715) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond710; { Bool *_hp = U64_lt(i, &(U64){min_len}); _wcond710 = *_hp; free(_hp); }
        if (_wcond710) {
        } else {
            ;
            break;
        }
        ;
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 _t711 = 0;
        Bool _t712; { Bool *_hp = I64_neq(c, &(I64){_t711}); _t712 = *_hp; free(_hp); }
        ;
        if (_t712) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t713 = 1;
        U64 _t714 = U64_add(DEREF(i), _t713);
        ;
        *i = _t714;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t716 = U64_cmp(a->count, b->count);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t716; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    U64 _t717 = 1;
    U64 _t718 = U64_add(DEREF(new_len), _t717);
    ;
    U8 *new_data = malloc(_t718);
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t719 = ptr_add(new_data, a->count);
    memcpy(_t719, b->c_str, b->count);
    void *_t720 = ptr_add(new_data, DEREF(new_len));
    I64 _t721 = 0;
    U64 _t722 = 1;
    memcpy(_t720, &(I64){_t721}, _t722);
    ;
    ;
    U64 _t723 = U64_clone(new_len);
    U64 _t724 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t725 = malloc(sizeof(Str));
    _t725->c_str = new_data;
    _t725->count = _t723;
    _t725->cap = _t724;
    ;
    ;
    return _t725;
}

Str * Str_with_capacity(U64 * n) {
    U64 _t726 = 1;
    U64 _t727 = U64_add(DEREF(n), _t726);
    ;
    U8 *buf = malloc(_t727);
    ;
    I64 _t728 = 0;
    U64 _t729 = 1;
    memcpy(buf, &(I64){_t728}, _t729);
    ;
    ;
    I64 _t730 = 0;
    U64 _t731 = U64_clone(n);
    Str *_t732 = malloc(sizeof(Str));
    _t732->c_str = buf;
    _t732->count = _t730;
    _t732->cap = _t731;
    ;
    ;
    return _t732;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    Bool _t745; { Bool *_hp = U64_gte(&self->cap, CAP_VIEW); _t745 = *_hp; free(_hp); }
    if (_t745) {
        Str *_t733 = Str_lit("Str", 3ULL);
        U64 _t734; { U64 *_hp = Str_size(); _t734 = *_hp; free(_hp); }
        U64 _t735 = 1;
        Array *_va14 = Array_new(_t733, &(U64){_t734}, &(U64){_t735});
        Str_delete(_t733, &(Bool){1});
        ;
        ;
        U64 _t736 = 0;
        Str *_t737 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va14, &(U64){_t736}, _t737);
        ;
        Str *_t738 = Str_lit("Str.push_str", 12ULL);
        panic(_t738, _va14);
        Str_delete(_t738, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool _t746; { Bool *_hp = U64_gt(new_len, &self->cap); _t746 = *_hp; free(_hp); }
    if (_t746) {
        Str *_t739 = Str_lit("Str", 3ULL);
        U64 _t740; { U64 *_hp = Str_size(); _t740 = *_hp; free(_hp); }
        U64 _t741 = 1;
        Array *_va15 = Array_new(_t739, &(U64){_t740}, &(U64){_t741});
        Str_delete(_t739, &(Bool){1});
        ;
        ;
        U64 _t742 = 0;
        Str *_t743 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va15, &(U64){_t742}, _t743);
        ;
        Str *_t744 = Str_lit("Str.push_str", 12ULL);
        panic(_t744, _va15);
        Str_delete(_t744, &(Bool){1});
    }
    ;
    void *_t747 = ptr_add(self->c_str, self->count);
    memcpy(_t747, s->c_str, s->count);
    U64 _t748 = U64_clone(new_len);
    self->count = _t748;
    ;
    void *_t749 = ptr_add(self->c_str, DEREF(new_len));
    I64 _t750 = 0;
    U64 _t751 = 1;
    memcpy(_t749, &(I64){_t750}, _t751);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    U64 _t752 = 1;
    U64 _t753 = U64_add(val->count, _t752);
    ;
    U8 *new_data = malloc(_t753);
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t754 = ptr_add(new_data, val->count);
    I64 _t755 = 0;
    U64 _t756 = 1;
    memcpy(_t754, &(I64){_t755}, _t756);
    ;
    ;
    Str *_t757 = malloc(sizeof(Str));
    _t757->c_str = new_data;
    _t757->count = val->count;
    _t757->cap = val->count;
    return _t757;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    Bool _t758; { Bool *_hp = U64_lt(&self->cap, CAP_VIEW); _t758 = *_hp; free(_hp); }
    if (_t758) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t759 = Str_clone(val);
    return _t759;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    U64 ln = U64_clone(n);
    Bool _t761; { Bool *_hp = U64_gt(st, &s->count); _t761 = *_hp; free(_hp); }
    if (_t761) {
        *st = s->count;
    }
    ;
    U64 _t762 = U64_add(DEREF(st), ln);
    Bool _t763; { Bool *_hp = U64_gt(&(U64){_t762}, &s->count); _t763 = *_hp; free(_hp); }
    ;
    if (_t763) {
        U64 _t760 = U64_sub(s->count, DEREF(st));
        ln = _t760;
        ;
    }
    ;
    void *_t764 = ptr_add(s->c_str, DEREF(st));
    U64 _t765 = U64_clone(&(U64){ln});
    ;
    U64 _t766 = U64_clone(CAP_VIEW);
    Str *_t767 = malloc(sizeof(Str));
    _t767->c_str = _t764;
    _t767->count = _t765;
    _t767->cap = _t766;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t767;
}

Bool * Str_contains(Str * a, Str * b) {
    U64 _t781 = 0;
    Bool _t782 = U64_eq(b->count, _t781);
    ;
    if (_t782) {
        Bool _t768 = 1;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t768; return _r; }
    }
    ;
    Bool _t783; { Bool *_hp = U64_gt(&b->count, &a->count); _t783 = *_hp; free(_hp); }
    if (_t783) {
        Bool _t769 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t769; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t778 = U64_sub(a->count, b->count);
        Bool _wcond770; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t778}); _wcond770 = *_hp; free(_hp); }
        ;
        if (_wcond770) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond771; { Bool *_hp = U64_lt(j, &b->count); _wcond771 = *_hp; free(_hp); }
            if (_wcond771) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t773 = malloc(sizeof(U64)); *_t773 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(a, _t773);
            U8 *bc = Str_get(b, j);
            Bool _t774; { Bool *_hp = U8_neq(ac, bc); _t774 = *_hp; free(_hp); }
            U64_delete(_t773, &(Bool){1});
            if (_t774) {
                Bool _t772 = 0;
                found = _t772;
                ;
            }
            ;
            U64 _t775 = 1;
            U64 _t776 = U64_add(DEREF(j), _t775);
            ;
            *j = _t776;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t777 = 1;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t777; return _r; }
        }
        ;
        U64 _t779 = 1;
        U64 _t780 = U64_add(i, _t779);
        ;
        i = _t780;
        ;
    }
    ;
    Bool _t784 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t784; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool _t791; { Bool *_hp = U64_gt(&b->count, &a->count); _t791 = *_hp; free(_hp); }
    if (_t791) {
        Bool _t785 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t785; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond786; { Bool *_hp = U64_lt(i, &b->count); _wcond786 = *_hp; free(_hp); }
        if (_wcond786) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool _t788; { Bool *_hp = U8_neq(ac, bc); _t788 = *_hp; free(_hp); }
        if (_t788) {
            Bool _t787 = 0;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t787; return _r; }
        }
        ;
        U64 _t789 = 1;
        U64 _t790 = U64_add(DEREF(i), _t789);
        ;
        *i = _t790;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t792 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t792; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool _t800; { Bool *_hp = U64_gt(&b->count, &a->count); _t800 = *_hp; free(_hp); }
    if (_t800) {
        Bool _t793 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t793; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond794; { Bool *_hp = U64_lt(i, &b->count); _wcond794 = *_hp; free(_hp); }
        if (_wcond794) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t796 = malloc(sizeof(U64)); *_t796 = U64_add(offset, DEREF(i));
        U8 *ac = Str_get(a, _t796);
        U8 *bc = Str_get(b, i);
        Bool _t797; { Bool *_hp = U8_neq(ac, bc); _t797 = *_hp; free(_hp); }
        U64_delete(_t796, &(Bool){1});
        if (_t797) {
            Bool _t795 = 0;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t795; return _r; }
        }
        ;
        U64 _t798 = 1;
        U64 _t799 = U64_add(DEREF(i), _t798);
        ;
        *i = _t799;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t801 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t801; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t802 = 0;
    Bool _t803 = U64_eq(self->count, _t802);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t803; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    U64 _t821 = 0;
    Bool _t822 = U64_eq(needle->count, _t821);
    ;
    if (_t822) {
        I64 _t804 = 0;
        I64 _t805 = 1;
        I64 _t806 = I64_sub(_t804, _t805);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t806; return _r; }
    }
    ;
    Bool _t823; { Bool *_hp = U64_gt(&needle->count, &self->count); _t823 = *_hp; free(_hp); }
    if (_t823) {
        I64 _t807 = 0;
        I64 _t808 = 1;
        I64 _t809 = I64_sub(_t807, _t808);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t809; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t818 = U64_sub(self->count, needle->count);
        Bool _wcond810; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t818}); _wcond810 = *_hp; free(_hp); }
        ;
        if (_wcond810) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond811; { Bool *_hp = U64_lt(j, &needle->count); _wcond811 = *_hp; free(_hp); }
            if (_wcond811) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t813 = malloc(sizeof(U64)); *_t813 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t813);
            U8 *bc = Str_get(needle, j);
            Bool _t814; { Bool *_hp = U8_neq(ac, bc); _t814 = *_hp; free(_hp); }
            U64_delete(_t813, &(Bool){1});
            if (_t814) {
                Bool _t812 = 0;
                found = _t812;
                ;
            }
            ;
            U64 _t815 = 1;
            U64 _t816 = U64_add(DEREF(j), _t815);
            ;
            *j = _t816;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t817 = U64_to_i64(i);
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t817; return _r; }
        }
        ;
        U64 _t819 = 1;
        U64 _t820 = U64_add(i, _t819);
        ;
        i = _t820;
        ;
    }
    ;
    I64 _t824 = 0;
    I64 _t825 = 1;
    I64 _t826 = I64_sub(_t824, _t825);
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t826; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    U64 _t844 = 0;
    Bool _t845 = U64_eq(needle->count, _t844);
    ;
    if (_t845) {
        I64 _t827 = 0;
        I64 _t828 = 1;
        I64 _t829 = I64_sub(_t827, _t828);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t829; return _r; }
    }
    ;
    Bool _t846; { Bool *_hp = U64_gt(&needle->count, &self->count); _t846 = *_hp; free(_hp); }
    if (_t846) {
        I64 _t830 = 0;
        I64 _t831 = 1;
        I64 _t832 = I64_sub(_t830, _t831);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t832; return _r; }
    }
    ;
    I64 _t847 = 0;
    I64 _t848 = 1;
    I64 last = I64_sub(_t847, _t848);
    ;
    ;
    U64 i = 0;
    while (1) {
        U64 _t841 = U64_sub(self->count, needle->count);
        Bool _wcond833; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t841}); _wcond833 = *_hp; free(_hp); }
        ;
        if (_wcond833) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond834; { Bool *_hp = U64_lt(j, &needle->count); _wcond834 = *_hp; free(_hp); }
            if (_wcond834) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t836 = malloc(sizeof(U64)); *_t836 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t836);
            U8 *bc = Str_get(needle, j);
            Bool _t837; { Bool *_hp = U8_neq(ac, bc); _t837 = *_hp; free(_hp); }
            U64_delete(_t836, &(Bool){1});
            if (_t837) {
                Bool _t835 = 0;
                found = _t835;
                ;
            }
            ;
            U64 _t838 = 1;
            U64 _t839 = U64_add(DEREF(j), _t838);
            ;
            *j = _t839;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t840 = U64_to_i64(i);
            last = _t840;
            ;
        }
        ;
        U64 _t842 = 1;
        U64 _t843 = U64_add(i, _t842);
        ;
        i = _t843;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    U64 _t864 = 0;
    Bool _t865 = U64_eq(from->count, _t864);
    ;
    if (_t865) {
        Str *_t849 = Str_clone(self);
        ;
        return _t849;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 start = 0;
    while (1) {
        U64 _t851 = U64_sub(self->count, from->count);
        Bool _wcond850; { Bool *_hp = U64_lte(&(U64){start}, &(U64){_t851}); _wcond850 = *_hp; free(_hp); }
        ;
        if (_wcond850) {
        } else {
            ;
            break;
        }
        ;
        U64 _t852 = U64_sub(self->count, start);
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t852});
        ;
        I64 pos; { I64 *_hp = Str_find(rest, from); pos = *_hp; free(_hp); }
        I64 _t853 = 0;
        I64 _t854 = 1;
        I64 _t855 = I64_sub(_t853, _t854);
        ;
        ;
        Bool _t856 = I64_eq(pos, _t855);
        ;
        if (_t856) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t857; { U64 *_hp = U64_from_i64(&(I64){pos}); _t857 = *_hp; free(_hp); }
        Str *_t858 = Str_substr(self, &(U64){start}, &(U64){_t857});
        ;
        result = Str_concat(result, _t858);
        Str_delete(_t858, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t859; { U64 *_hp = U64_from_i64(&(I64){pos}); _t859 = *_hp; free(_hp); }
        ;
        U64 _t860 = U64_add(start, _t859);
        ;
        U64 _t861 = U64_add(_t860, from->count);
        ;
        start = _t861;
        ;
    }
    Bool _t866; { Bool *_hp = U64_lt(&(U64){start}, &self->count); _t866 = *_hp; free(_hp); }
    if (_t866) {
        U64 _t862 = U64_sub(self->count, start);
        Str *_t863 = Str_substr(self, &(U64){start}, &(U64){_t862});
        ;
        result = Str_concat(result, _t863);
        Str_delete(_t863, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    U64 _t867 = 1;
    Str *_t868 = Str_substr(self, i, &(U64){_t867});
    ;
    return _t868;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    Bool _t871; { Bool *_hp = Str_starts_with(self, prefix); _t871 = *_hp; free(_hp); }
    if (_t871) {
        U64 _t869 = U64_sub(self->count, prefix->count);
        Str *_t870 = Str_substr(self, &prefix->count, &(U64){_t869});
        ;
        ;
        return _t870;
    }
    ;
    Str *_t872 = Str_clone(self);
    return _t872;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    Bool _t876; { Bool *_hp = Str_ends_with(self, suffix); _t876 = *_hp; free(_hp); }
    if (_t876) {
        U64 _t873 = 0;
        U64 _t874 = U64_sub(self->count, suffix->count);
        Str *_t875 = Str_substr(self, &(U64){_t873}, &(U64){_t874});
        ;
        ;
        ;
        return _t875;
    }
    ;
    Str *_t877 = Str_clone(self);
    return _t877;
}

Str * Str_from_byte(U8 * byte) {
    U64 _t878 = 2;
    U8 *buf = malloc(_t878);
    ;
    U64 _t879 = 1;
    memcpy(buf, byte, _t879);
    ;
    U64 *_t880 = malloc(sizeof(U64));
    *_t880 = 1;
    void *_t881 = ptr_add(buf, DEREF(_t880));
    I64 _t882 = 0;
    U64 _t883 = 1;
    memcpy(_t881, &(I64){_t882}, _t883);
    U64_delete(_t880, &(Bool){1});
    ;
    ;
    I64 _t884 = 1;
    I64 _t885 = 1;
    Str *_t886 = malloc(sizeof(Str));
    _t886->c_str = buf;
    _t886->count = _t884;
    _t886->cap = _t885;
    ;
    ;
    return _t886;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t927 = 0;
    Bool _t928 = U64_eq(self->count, _t927);
    ;
    if (_t928) {
        Str *_t887 = Str_lit("Str", 3ULL);
        U64 _t888; { U64 *_hp = Str_size(); _t888 = *_hp; free(_hp); }
        U64 _t889 = 1;
        Array *_va16 = Array_new(_t887, &(U64){_t888}, &(U64){_t889});
        Str_delete(_t887, &(Bool){1});
        ;
        ;
        U64 _t890 = 0;
        Str *_t891 = Str_lit("empty string", 12ULL);
        Array_set(_va16, &(U64){_t890}, _t891);
        ;
        Str *_t892 = Str_lit("Str.to_i64", 10ULL);
        panic(_t892, _va16);
        Str_delete(_t892, &(Bool){1});
    }
    ;
    I64 result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool neg = 0;
    U64 *_t929 = malloc(sizeof(U64));
    *_t929 = 0;
    U8 *first = Str_get(self, _t929);
    U8 _t930 = 45;
    Bool _t931 = U8_eq(DEREF(first), _t930);
    U64_delete(_t929, &(Bool){1});
    ;
    if (_t931) {
        Bool _t893 = 1;
        neg = _t893;
        ;
        I64 _t894 = 1;
        U64 _t895; { U64 *_hp = U64_from_i64(&(I64){_t894}); _t895 = *_hp; free(_hp); }
        ;
        *i = _t895;
        ;
    }
    ;
    Bool _t932 = U64_eq(DEREF(i), self->count);
    if (_t932) {
        Str *_t896 = Str_lit("Str", 3ULL);
        U64 _t897; { U64 *_hp = Str_size(); _t897 = *_hp; free(_hp); }
        U64 _t898 = 1;
        Array *_va17 = Array_new(_t896, &(U64){_t897}, &(U64){_t898});
        Str_delete(_t896, &(Bool){1});
        ;
        ;
        U64 _t899 = 0;
        Str *_t900 = Str_lit("no digits", 9ULL);
        Array_set(_va17, &(U64){_t899}, _t900);
        ;
        Str *_t901 = Str_lit("Str.to_i64", 10ULL);
        panic(_t901, _va17);
        Str_delete(_t901, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond902; { Bool *_hp = U64_lt(i, &self->count); _wcond902 = *_hp; free(_hp); }
        if (_wcond902) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        I64 _t913 = U8_to_i64(DEREF(ch));
        I64 _t914 = 48;
        I64 d = I64_sub(_t913, _t914);
        ;
        ;
        I64 _t915 = 0;
        I64 _t916 = 9;
        Bool _t917; { Bool *_hp = I64_lt(&(I64){d}, &(I64){_t915}); _t917 = *_hp; free(_hp); }
        ;
        Bool _t918; { Bool *_hp = I64_gt(&(I64){d}, &(I64){_t916}); _t918 = *_hp; free(_hp); }
        ;
        Bool _t919 = Bool_or(_t917, _t918);
        ;
        ;
        if (_t919) {
            Str *_t903 = Str_lit("Str", 3ULL);
            U64 _t904; { U64 *_hp = Str_size(); _t904 = *_hp; free(_hp); }
            U64 _t905 = 3;
            Array *_va18 = Array_new(_t903, &(U64){_t904}, &(U64){_t905});
            Str_delete(_t903, &(Bool){1});
            ;
            ;
            U64 _t906 = 0;
            Str *_t907 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va18, &(U64){_t906}, _t907);
            ;
            U64 _t908 = 1;
            Str *_t909 = Str_clone(self);
            Array_set(_va18, &(U64){_t908}, _t909);
            ;
            U64 _t910 = 2;
            Str *_t911 = Str_lit("'", 1ULL);
            Array_set(_va18, &(U64){_t910}, _t911);
            ;
            Str *_t912 = Str_lit("Str.to_i64", 10ULL);
            panic(_t912, _va18);
            Str_delete(_t912, &(Bool){1});
        }
        ;
        I64 _t920 = 10;
        I64 _t921 = I64_mul(result, _t920);
        ;
        I64 _t922 = I64_add(_t921, d);
        ;
        ;
        result = _t922;
        ;
        U64 _t923 = 1;
        U64 _t924 = U64_add(DEREF(i), _t923);
        ;
        *i = _t924;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t925 = 0;
        I64 _t926 = I64_sub(_t925, result);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t926; return _r; }
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
    I64 _t934; { I64 *_hp = Str_cmp(a, b); _t934 = *_hp; free(_hp); }
    I64 _t935 = 0;
    Bool _t936 = I64_eq(_t934, _t935);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t936; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    I64 _t937 = 0;
    I64 _t938 = 1;
    I64 _t939; { I64 *_hp = Str_cmp(a, b); _t939 = *_hp; free(_hp); }
    I64 _t940 = I64_sub(_t937, _t938);
    ;
    ;
    Bool _t941 = I64_eq(_t939, _t940);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t941; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    I64 _t942; { I64 *_hp = Str_cmp(a, b); _t942 = *_hp; free(_hp); }
    I64 _t943 = 1;
    Bool _t944 = I64_eq(_t942, _t943);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t944; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    Bool _t945; { Bool *_hp = Str_eq(a, b); _t945 = *_hp; free(_hp); }
    Bool _t946 = Bool_not(_t945);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t946; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    Bool _t947; { Bool *_hp = Str_gt(a, b); _t947 = *_hp; free(_hp); }
    Bool _t948 = Bool_not(_t947);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t948; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    Bool _t949; { Bool *_hp = Str_lt(a, b); _t949 = *_hp; free(_hp); }
    Bool _t950 = Bool_not(_t949);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t950; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t951 = malloc(DEREF(elem_size));
    U64 _t952 = 0;
    I64 _t953 = 1;
    U64 _t954 = U64_clone(elem_size);
    Vec *_t955 = malloc(sizeof(Vec));
    _t955->data = _t951;
    _t955->count = _t952;
    _t955->cap = _t953;
    _t955->elem_size = _t954;
    { Str *_ca = Str_clone(elem_type); _t955->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t955;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    Bool _t960 = U64_eq(self->count, self->cap);
    if (_t960) {
        U64 _t956 = 2;
        U64 new_cap = U64_mul(self->cap, _t956);
        ;
        U64 _t957 = U64_mul(new_cap, self->elem_size);
        void *_t958 = realloc(self->data, _t957);
        ;
        self->data = _t958;
        U64 _t959 = U64_clone(&(U64){new_cap});
        ;
        self->cap = _t959;
        ;
    }
    ;
    U64 *_t961 = malloc(sizeof(U64)); *_t961 = U64_mul(self->count, self->elem_size);
    void *_t962 = ptr_add(self->data, DEREF(_t961));
    memcpy(_t962, val, self->elem_size);
    U64_delete(_t961, &(Bool){1});
    free(val);
    U64 _t963 = 1;
    U64 _t964 = U64_add(self->count, _t963);
    ;
    self->count = _t964;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    Bool _t979; { Bool *_hp = U64_gte(i, &self->count); _t979 = *_hp; free(_hp); }
    if (_t979) {
        Str *_t965 = Str_lit("Str", 3ULL);
        U64 _t966; { U64 *_hp = Str_size(); _t966 = *_hp; free(_hp); }
        U64 _t967 = 5;
        Array *_va19 = Array_new(_t965, &(U64){_t966}, &(U64){_t967});
        Str_delete(_t965, &(Bool){1});
        ;
        ;
        U64 _t968 = 0;
        Str *_t969 = Str_lit("index ", 6ULL);
        Array_set(_va19, &(U64){_t968}, _t969);
        ;
        U64 _t970 = 1;
        Str *_t971 = U64_to_str(DEREF(i));
        Array_set(_va19, &(U64){_t970}, _t971);
        ;
        U64 _t972 = 2;
        Str *_t973 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va19, &(U64){_t972}, _t973);
        ;
        U64 _t974 = 3;
        Str *_t975 = U64_to_str(self->count);
        Array_set(_va19, &(U64){_t974}, _t975);
        ;
        U64 _t976 = 4;
        Str *_t977 = Str_lit(")", 1ULL);
        Array_set(_va19, &(U64){_t976}, _t977);
        ;
        Str *_t978 = Str_lit("Vec.get", 7ULL);
        panic(_t978, _va19);
        Str_delete(_t978, &(Bool){1});
    }
    ;
    U64 *_t980 = malloc(sizeof(U64)); *_t980 = U64_mul(DEREF(i), self->elem_size);
    void *_t981 = ptr_add(self->data, DEREF(_t980));
    U64_delete(_t980, &(Bool){1});
    return _t981;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    Bool _t995; { Bool *_hp = Str_is_empty(&self->elem_type); _t995 = *_hp; free(_hp); }
    Bool _t996 = Bool_not(_t995);
    ;
    if (_t996) {
        {
            U64 _fi982 = 0;
            while (1) {
                U64 _t984 = 0;
                Range *_t985 = Range_new(_t984, self->count);
                ;
                U64 _t986; { U64 *_hp = Range_len(_t985); _t986 = *_hp; free(_hp); }
                Range_delete(_t985, &(Bool){1});
                Bool _wcond983; { Bool *_hp = U64_lt(&(U64){_fi982}, &(U64){_t986}); _wcond983 = *_hp; free(_hp); }
                ;
                if (_wcond983) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t987 = 0;
                Range *_t988 = Range_new(_t987, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t988, _fi982); i = *_hp; free(_hp); }
                Range_delete(_t988, &(Bool){1});
                U64 _t989 = 1;
                U64 _t990 = U64_add(_fi982, _t989);
                ;
                _fi982 = _t990;
                ;
                U64 *_t991 = malloc(sizeof(U64)); *_t991 = U64_mul(i, self->elem_size);
                ;
                void *_t992 = ptr_add(self->data, DEREF(_t991));
                Bool _t993 = 0;
                dyn_call_delete(&self->elem_type, _t992, &(Bool){_t993});
                U64_delete(_t991, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t997; { Bool *_hp = Str_is_empty(&self->elem_type); _t997 = *_hp; free(_hp); }
    Bool _t998 = Bool_not(_t997);
    ;
    if (_t998) {
        Bool _t994 = 0;
        Str_delete(&self->elem_type, &(Bool){_t994});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1012 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t1012);
    ;
    {
        U64 _fi999 = 0;
        while (1) {
            U64 _t1001 = 0;
            Range *_t1002 = Range_new(_t1001, self->count);
            ;
            U64 _t1003; { U64 *_hp = Range_len(_t1002); _t1003 = *_hp; free(_hp); }
            Range_delete(_t1002, &(Bool){1});
            Bool _wcond1000; { Bool *_hp = U64_lt(&(U64){_fi999}, &(U64){_t1003}); _wcond1000 = *_hp; free(_hp); }
            ;
            if (_wcond1000) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1004 = 0;
            Range *_t1005 = Range_new(_t1004, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t1005, _fi999); i = *_hp; free(_hp); }
            Range_delete(_t1005, &(Bool){1});
            U64 _t1006 = 1;
            U64 _t1007 = U64_add(_fi999, _t1006);
            ;
            _fi999 = _t1007;
            ;
            U64 *_t1008 = malloc(sizeof(U64)); *_t1008 = U64_mul(i, self->elem_size);
            void *_t1009 = ptr_add(self->data, DEREF(_t1008));
            void *cloned = dyn_call_clone(&self->elem_type, _t1009);
            U64_delete(_t1008, &(Bool){1});
            U64 *_t1010 = malloc(sizeof(U64)); *_t1010 = U64_mul(i, self->elem_size);
            ;
            void *_t1011 = ptr_add(new_data, DEREF(_t1010));
            memcpy(_t1011, cloned, self->elem_size);
            U64_delete(_t1010, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1013 = malloc(sizeof(Vec));
    _t1013->data = new_data;
    _t1013->count = self->count;
    _t1013->cap = self->cap;
    _t1013->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1013->elem_type = *_ca; free(_ca); }
    return _t1013;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t1031 = Str_lit("Str", 3ULL);
    U64 _t1032; { U64 *_hp = Str_size(); _t1032 = *_hp; free(_hp); }
    Vec *parts = Vec_new(_t1031, &(U64){_t1032});
    Str_delete(_t1031, &(Bool){1});
    ;
    U64 _t1033; { U64 *_hp = Str_len(delim); _t1033 = *_hp; free(_hp); }
    U64 _t1034 = 0;
    Bool _t1035 = U64_eq(_t1033, _t1034);
    ;
    ;
    if (_t1035) {
        Str *_t1015 = Str_clone(s);
        Vec_push(parts, _t1015);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    U64 pos = 0;
    while (1) {
        U64 _t1025; { U64 *_hp = Str_len(s); _t1025 = *_hp; free(_hp); }
        U64 _t1026; { U64 *_hp = Str_len(delim); _t1026 = *_hp; free(_hp); }
        U64 _t1027 = U64_sub(_t1025, _t1026);
        ;
        ;
        Bool _wcond1016; { Bool *_hp = U64_lte(&(U64){pos}, &(U64){_t1027}); _wcond1016 = *_hp; free(_hp); }
        ;
        if (_wcond1016) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1028; { U64 *_hp = Str_len(delim); _t1028 = *_hp; free(_hp); }
        Str *_t1029 = Str_substr(s, &(U64){pos}, &(U64){_t1028});
        ;
        Bool _t1030; { Bool *_hp = Str_eq(_t1029, delim); _t1030 = *_hp; free(_hp); }
        Str_delete(_t1029, &(Bool){1});
        if (_t1030) {
            U64 _t1017 = U64_sub(pos, start);
            Str *_t1018 = Str_substr(s, &(U64){start}, &(U64){_t1017});
            ;
            Str *_t1019 = Str_clone(_t1018);
            Str_delete(_t1018, &(Bool){1});
            Vec_push(parts, _t1019);
            U64 _t1020; { U64 *_hp = Str_len(delim); _t1020 = *_hp; free(_hp); }
            U64 _t1021 = U64_add(pos, _t1020);
            ;
            start = _t1021;
            ;
            U64 _t1022 = U64_clone(&(U64){start});
            pos = _t1022;
            ;
        } else {
            U64 _t1023 = 1;
            U64 _t1024 = U64_add(pos, _t1023);
            ;
            pos = _t1024;
            ;
        }
        ;
    }
    ;
    U64 _t1036; { U64 *_hp = Str_len(s); _t1036 = *_hp; free(_hp); }
    U64 _t1037 = U64_sub(_t1036, start);
    ;
    Str *_t1038 = Str_substr(s, &(U64){start}, &(U64){_t1037});
    ;
    ;
    Str *_t1039 = Str_clone(_t1038);
    Str_delete(_t1038, &(Bool){1});
    Vec_push(parts, _t1039);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 _t1047; { U64 *_hp = Vec_len(parts); _t1047 = *_hp; free(_hp); }
    U64 _t1048 = 0;
    Bool _t1049 = U64_eq(_t1047, _t1048);
    ;
    ;
    if (_t1049) {
        Str *_t1040 = Str_lit("", 0ULL);
        ;
        return _t1040;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t1042; { U64 *_hp = Vec_len(parts); _t1042 = *_hp; free(_hp); }
        Bool _wcond1041; { Bool *_hp = U64_lt(i, &(U64){_t1042}); _wcond1041 = *_hp; free(_hp); }
        ;
        if (_wcond1041) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1043 = 0;
        Bool _t1044; { Bool *_hp = U64_gt(i, &(U64){_t1043}); _t1044 = *_hp; free(_hp); }
        ;
        if (_t1044) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        U64 _t1045 = 1;
        U64 _t1046 = U64_add(DEREF(i), _t1045);
        ;
        *i = _t1046;
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
    Bool _t1113; { Bool *_hp = TokenType_is_Eof(self); _t1113 = *_hp; free(_hp); }
    if (_t1113) {
        Bool _t1050; { Bool *_hp = TokenType_is_Eof(other); _t1050 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1050; return _r; }
    }
    ;
    Bool _t1114; { Bool *_hp = TokenType_is_LParen(self); _t1114 = *_hp; free(_hp); }
    if (_t1114) {
        Bool _t1051; { Bool *_hp = TokenType_is_LParen(other); _t1051 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1051; return _r; }
    }
    ;
    Bool _t1115; { Bool *_hp = TokenType_is_RParen(self); _t1115 = *_hp; free(_hp); }
    if (_t1115) {
        Bool _t1052; { Bool *_hp = TokenType_is_RParen(other); _t1052 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1052; return _r; }
    }
    ;
    Bool _t1116; { Bool *_hp = TokenType_is_LBrace(self); _t1116 = *_hp; free(_hp); }
    if (_t1116) {
        Bool _t1053; { Bool *_hp = TokenType_is_LBrace(other); _t1053 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1053; return _r; }
    }
    ;
    Bool _t1117; { Bool *_hp = TokenType_is_RBrace(self); _t1117 = *_hp; free(_hp); }
    if (_t1117) {
        Bool _t1054; { Bool *_hp = TokenType_is_RBrace(other); _t1054 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1054; return _r; }
    }
    ;
    Bool _t1118; { Bool *_hp = TokenType_is_LBracket(self); _t1118 = *_hp; free(_hp); }
    if (_t1118) {
        Bool _t1055; { Bool *_hp = TokenType_is_LBracket(other); _t1055 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1055; return _r; }
    }
    ;
    Bool _t1119; { Bool *_hp = TokenType_is_RBracket(self); _t1119 = *_hp; free(_hp); }
    if (_t1119) {
        Bool _t1056; { Bool *_hp = TokenType_is_RBracket(other); _t1056 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1056; return _r; }
    }
    ;
    Bool _t1120; { Bool *_hp = TokenType_is_Comma(self); _t1120 = *_hp; free(_hp); }
    if (_t1120) {
        Bool _t1057; { Bool *_hp = TokenType_is_Comma(other); _t1057 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1057; return _r; }
    }
    ;
    Bool _t1121; { Bool *_hp = TokenType_is_Colon(self); _t1121 = *_hp; free(_hp); }
    if (_t1121) {
        Bool _t1058; { Bool *_hp = TokenType_is_Colon(other); _t1058 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1058; return _r; }
    }
    ;
    Bool _t1122; { Bool *_hp = TokenType_is_Question(self); _t1122 = *_hp; free(_hp); }
    if (_t1122) {
        Bool _t1059; { Bool *_hp = TokenType_is_Question(other); _t1059 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1059; return _r; }
    }
    ;
    Bool _t1123; { Bool *_hp = TokenType_is_Bang(self); _t1123 = *_hp; free(_hp); }
    if (_t1123) {
        Bool _t1060; { Bool *_hp = TokenType_is_Bang(other); _t1060 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1060; return _r; }
    }
    ;
    Bool _t1124; { Bool *_hp = TokenType_is_Minus(self); _t1124 = *_hp; free(_hp); }
    if (_t1124) {
        Bool _t1061; { Bool *_hp = TokenType_is_Minus(other); _t1061 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1061; return _r; }
    }
    ;
    Bool _t1125; { Bool *_hp = TokenType_is_Plus(self); _t1125 = *_hp; free(_hp); }
    if (_t1125) {
        Bool _t1062; { Bool *_hp = TokenType_is_Plus(other); _t1062 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1062; return _r; }
    }
    ;
    Bool _t1126; { Bool *_hp = TokenType_is_Star(self); _t1126 = *_hp; free(_hp); }
    if (_t1126) {
        Bool _t1063; { Bool *_hp = TokenType_is_Star(other); _t1063 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1063; return _r; }
    }
    ;
    Bool _t1127; { Bool *_hp = TokenType_is_Slash(self); _t1127 = *_hp; free(_hp); }
    if (_t1127) {
        Bool _t1064; { Bool *_hp = TokenType_is_Slash(other); _t1064 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1064; return _r; }
    }
    ;
    Bool _t1128; { Bool *_hp = TokenType_is_Dot(self); _t1128 = *_hp; free(_hp); }
    if (_t1128) {
        Bool _t1065; { Bool *_hp = TokenType_is_Dot(other); _t1065 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1065; return _r; }
    }
    ;
    Bool _t1129; { Bool *_hp = TokenType_is_DotDot(self); _t1129 = *_hp; free(_hp); }
    if (_t1129) {
        Bool _t1066; { Bool *_hp = TokenType_is_DotDot(other); _t1066 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1066; return _r; }
    }
    ;
    Bool _t1130; { Bool *_hp = TokenType_is_Eq(self); _t1130 = *_hp; free(_hp); }
    if (_t1130) {
        Bool _t1067; { Bool *_hp = TokenType_is_Eq(other); _t1067 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1067; return _r; }
    }
    ;
    Bool _t1131; { Bool *_hp = TokenType_is_EqEq(self); _t1131 = *_hp; free(_hp); }
    if (_t1131) {
        Bool _t1068; { Bool *_hp = TokenType_is_EqEq(other); _t1068 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1068; return _r; }
    }
    ;
    Bool _t1132; { Bool *_hp = TokenType_is_Neq(self); _t1132 = *_hp; free(_hp); }
    if (_t1132) {
        Bool _t1069; { Bool *_hp = TokenType_is_Neq(other); _t1069 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1069; return _r; }
    }
    ;
    Bool _t1133; { Bool *_hp = TokenType_is_Lt(self); _t1133 = *_hp; free(_hp); }
    if (_t1133) {
        Bool _t1070; { Bool *_hp = TokenType_is_Lt(other); _t1070 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1070; return _r; }
    }
    ;
    Bool _t1134; { Bool *_hp = TokenType_is_LtEq(self); _t1134 = *_hp; free(_hp); }
    if (_t1134) {
        Bool _t1071; { Bool *_hp = TokenType_is_LtEq(other); _t1071 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1071; return _r; }
    }
    ;
    Bool _t1135; { Bool *_hp = TokenType_is_Gt(self); _t1135 = *_hp; free(_hp); }
    if (_t1135) {
        Bool _t1072; { Bool *_hp = TokenType_is_Gt(other); _t1072 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1072; return _r; }
    }
    ;
    Bool _t1136; { Bool *_hp = TokenType_is_GtEq(self); _t1136 = *_hp; free(_hp); }
    if (_t1136) {
        Bool _t1073; { Bool *_hp = TokenType_is_GtEq(other); _t1073 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1073; return _r; }
    }
    ;
    Bool _t1137; { Bool *_hp = TokenType_is_ColonEq(self); _t1137 = *_hp; free(_hp); }
    if (_t1137) {
        Bool _t1074; { Bool *_hp = TokenType_is_ColonEq(other); _t1074 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1074; return _r; }
    }
    ;
    Bool _t1138; { Bool *_hp = TokenType_is_Ident(self); _t1138 = *_hp; free(_hp); }
    if (_t1138) {
        Bool _t1075; { Bool *_hp = TokenType_is_Ident(other); _t1075 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1075; return _r; }
    }
    ;
    Bool _t1139; { Bool *_hp = TokenType_is_StringTok(self); _t1139 = *_hp; free(_hp); }
    if (_t1139) {
        Bool _t1076; { Bool *_hp = TokenType_is_StringTok(other); _t1076 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1076; return _r; }
    }
    ;
    Bool _t1140; { Bool *_hp = TokenType_is_Number(self); _t1140 = *_hp; free(_hp); }
    if (_t1140) {
        Bool _t1077; { Bool *_hp = TokenType_is_Number(other); _t1077 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1077; return _r; }
    }
    ;
    Bool _t1141; { Bool *_hp = TokenType_is_Char(self); _t1141 = *_hp; free(_hp); }
    if (_t1141) {
        Bool _t1078; { Bool *_hp = TokenType_is_Char(other); _t1078 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1078; return _r; }
    }
    ;
    Bool _t1142; { Bool *_hp = TokenType_is_KwMode(self); _t1142 = *_hp; free(_hp); }
    if (_t1142) {
        Bool _t1079; { Bool *_hp = TokenType_is_KwMode(other); _t1079 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1079; return _r; }
    }
    ;
    Bool _t1143; { Bool *_hp = TokenType_is_KwMut(self); _t1143 = *_hp; free(_hp); }
    if (_t1143) {
        Bool _t1080; { Bool *_hp = TokenType_is_KwMut(other); _t1080 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1080; return _r; }
    }
    ;
    Bool _t1144; { Bool *_hp = TokenType_is_KwOwn(self); _t1144 = *_hp; free(_hp); }
    if (_t1144) {
        Bool _t1081; { Bool *_hp = TokenType_is_KwOwn(other); _t1081 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1081; return _r; }
    }
    ;
    Bool _t1145; { Bool *_hp = TokenType_is_KwRef(self); _t1145 = *_hp; free(_hp); }
    if (_t1145) {
        Bool _t1082; { Bool *_hp = TokenType_is_KwRef(other); _t1082 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1082; return _r; }
    }
    ;
    Bool _t1146; { Bool *_hp = TokenType_is_KwStruct(self); _t1146 = *_hp; free(_hp); }
    if (_t1146) {
        Bool _t1083; { Bool *_hp = TokenType_is_KwStruct(other); _t1083 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1083; return _r; }
    }
    ;
    Bool _t1147; { Bool *_hp = TokenType_is_KwExtStruct(self); _t1147 = *_hp; free(_hp); }
    if (_t1147) {
        Bool _t1084; { Bool *_hp = TokenType_is_KwExtStruct(other); _t1084 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1084; return _r; }
    }
    ;
    Bool _t1148; { Bool *_hp = TokenType_is_KwEnum(self); _t1148 = *_hp; free(_hp); }
    if (_t1148) {
        Bool _t1085; { Bool *_hp = TokenType_is_KwEnum(other); _t1085 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1085; return _r; }
    }
    ;
    Bool _t1149; { Bool *_hp = TokenType_is_KwNamespace(self); _t1149 = *_hp; free(_hp); }
    if (_t1149) {
        Bool _t1086; { Bool *_hp = TokenType_is_KwNamespace(other); _t1086 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1086; return _r; }
    }
    ;
    Bool _t1150; { Bool *_hp = TokenType_is_KwFunc(self); _t1150 = *_hp; free(_hp); }
    if (_t1150) {
        Bool _t1087; { Bool *_hp = TokenType_is_KwFunc(other); _t1087 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1087; return _r; }
    }
    ;
    Bool _t1151; { Bool *_hp = TokenType_is_KwProc(self); _t1151 = *_hp; free(_hp); }
    if (_t1151) {
        Bool _t1088; { Bool *_hp = TokenType_is_KwProc(other); _t1088 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1088; return _r; }
    }
    ;
    Bool _t1152; { Bool *_hp = TokenType_is_KwTest(self); _t1152 = *_hp; free(_hp); }
    if (_t1152) {
        Bool _t1089; { Bool *_hp = TokenType_is_KwTest(other); _t1089 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1089; return _r; }
    }
    ;
    Bool _t1153; { Bool *_hp = TokenType_is_KwMacro(self); _t1153 = *_hp; free(_hp); }
    if (_t1153) {
        Bool _t1090; { Bool *_hp = TokenType_is_KwMacro(other); _t1090 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1090; return _r; }
    }
    ;
    Bool _t1154; { Bool *_hp = TokenType_is_KwExtFunc(self); _t1154 = *_hp; free(_hp); }
    if (_t1154) {
        Bool _t1091; { Bool *_hp = TokenType_is_KwExtFunc(other); _t1091 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1091; return _r; }
    }
    ;
    Bool _t1155; { Bool *_hp = TokenType_is_KwExtProc(self); _t1155 = *_hp; free(_hp); }
    if (_t1155) {
        Bool _t1092; { Bool *_hp = TokenType_is_KwExtProc(other); _t1092 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1092; return _r; }
    }
    ;
    Bool _t1156; { Bool *_hp = TokenType_is_KwReturns(self); _t1156 = *_hp; free(_hp); }
    if (_t1156) {
        Bool _t1093; { Bool *_hp = TokenType_is_KwReturns(other); _t1093 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1093; return _r; }
    }
    ;
    Bool _t1157; { Bool *_hp = TokenType_is_KwThrows(self); _t1157 = *_hp; free(_hp); }
    if (_t1157) {
        Bool _t1094; { Bool *_hp = TokenType_is_KwThrows(other); _t1094 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1094; return _r; }
    }
    ;
    Bool _t1158; { Bool *_hp = TokenType_is_KwIf(self); _t1158 = *_hp; free(_hp); }
    if (_t1158) {
        Bool _t1095; { Bool *_hp = TokenType_is_KwIf(other); _t1095 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1095; return _r; }
    }
    ;
    Bool _t1159; { Bool *_hp = TokenType_is_KwElse(self); _t1159 = *_hp; free(_hp); }
    if (_t1159) {
        Bool _t1096; { Bool *_hp = TokenType_is_KwElse(other); _t1096 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1096; return _r; }
    }
    ;
    Bool _t1160; { Bool *_hp = TokenType_is_KwWhile(self); _t1160 = *_hp; free(_hp); }
    if (_t1160) {
        Bool _t1097; { Bool *_hp = TokenType_is_KwWhile(other); _t1097 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1097; return _r; }
    }
    ;
    Bool _t1161; { Bool *_hp = TokenType_is_KwFor(self); _t1161 = *_hp; free(_hp); }
    if (_t1161) {
        Bool _t1098; { Bool *_hp = TokenType_is_KwFor(other); _t1098 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1098; return _r; }
    }
    ;
    Bool _t1162; { Bool *_hp = TokenType_is_KwIn(self); _t1162 = *_hp; free(_hp); }
    if (_t1162) {
        Bool _t1099; { Bool *_hp = TokenType_is_KwIn(other); _t1099 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1099; return _r; }
    }
    ;
    Bool _t1163; { Bool *_hp = TokenType_is_KwSwitch(self); _t1163 = *_hp; free(_hp); }
    if (_t1163) {
        Bool _t1100; { Bool *_hp = TokenType_is_KwSwitch(other); _t1100 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1100; return _r; }
    }
    ;
    Bool _t1164; { Bool *_hp = TokenType_is_KwMatch(self); _t1164 = *_hp; free(_hp); }
    if (_t1164) {
        Bool _t1101; { Bool *_hp = TokenType_is_KwMatch(other); _t1101 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1101; return _r; }
    }
    ;
    Bool _t1165; { Bool *_hp = TokenType_is_KwCase(self); _t1165 = *_hp; free(_hp); }
    if (_t1165) {
        Bool _t1102; { Bool *_hp = TokenType_is_KwCase(other); _t1102 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1102; return _r; }
    }
    ;
    Bool _t1166; { Bool *_hp = TokenType_is_KwDefault(self); _t1166 = *_hp; free(_hp); }
    if (_t1166) {
        Bool _t1103; { Bool *_hp = TokenType_is_KwDefault(other); _t1103 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1103; return _r; }
    }
    ;
    Bool _t1167; { Bool *_hp = TokenType_is_KwReturn(self); _t1167 = *_hp; free(_hp); }
    if (_t1167) {
        Bool _t1104; { Bool *_hp = TokenType_is_KwReturn(other); _t1104 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1104; return _r; }
    }
    ;
    Bool _t1168; { Bool *_hp = TokenType_is_KwThrow(self); _t1168 = *_hp; free(_hp); }
    if (_t1168) {
        Bool _t1105; { Bool *_hp = TokenType_is_KwThrow(other); _t1105 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1105; return _r; }
    }
    ;
    Bool _t1169; { Bool *_hp = TokenType_is_KwCatch(self); _t1169 = *_hp; free(_hp); }
    if (_t1169) {
        Bool _t1106; { Bool *_hp = TokenType_is_KwCatch(other); _t1106 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1106; return _r; }
    }
    ;
    Bool _t1170; { Bool *_hp = TokenType_is_KwBreak(self); _t1170 = *_hp; free(_hp); }
    if (_t1170) {
        Bool _t1107; { Bool *_hp = TokenType_is_KwBreak(other); _t1107 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1107; return _r; }
    }
    ;
    Bool _t1171; { Bool *_hp = TokenType_is_KwContinue(self); _t1171 = *_hp; free(_hp); }
    if (_t1171) {
        Bool _t1108; { Bool *_hp = TokenType_is_KwContinue(other); _t1108 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1108; return _r; }
    }
    ;
    Bool _t1172; { Bool *_hp = TokenType_is_KwDefer(self); _t1172 = *_hp; free(_hp); }
    if (_t1172) {
        Bool _t1109; { Bool *_hp = TokenType_is_KwDefer(other); _t1109 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1109; return _r; }
    }
    ;
    Bool _t1173; { Bool *_hp = TokenType_is_KwTrue(self); _t1173 = *_hp; free(_hp); }
    if (_t1173) {
        Bool _t1110; { Bool *_hp = TokenType_is_KwTrue(other); _t1110 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1110; return _r; }
    }
    ;
    Bool _t1174; { Bool *_hp = TokenType_is_KwFalse(self); _t1174 = *_hp; free(_hp); }
    if (_t1174) {
        Bool _t1111; { Bool *_hp = TokenType_is_KwFalse(other); _t1111 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1111; return _r; }
    }
    ;
    Bool _t1175; { Bool *_hp = TokenType_is_Error(self); _t1175 = *_hp; free(_hp); }
    if (_t1175) {
        Bool _t1112; { Bool *_hp = TokenType_is_Error(other); _t1112 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1112; return _r; }
    }
    ;
    Bool _t1176 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1176; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1177; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1177 = *_hp; free(_hp); }
    if (_t1177) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1178; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1178 = *_hp; free(_hp); }
    if (_t1178) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1179; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1179 = *_hp; free(_hp); }
    if (_t1179) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1180; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1180 = *_hp; free(_hp); }
    if (_t1180) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1181; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1181 = *_hp; free(_hp); }
    if (_t1181) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1182; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1182 = *_hp; free(_hp); }
    if (_t1182) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1183; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1183 = *_hp; free(_hp); }
    if (_t1183) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1184; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1184 = *_hp; free(_hp); }
    if (_t1184) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1185; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1185 = *_hp; free(_hp); }
    if (_t1185) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1186; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1186 = *_hp; free(_hp); }
    if (_t1186) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1187; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1187 = *_hp; free(_hp); }
    if (_t1187) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1188; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1188 = *_hp; free(_hp); }
    if (_t1188) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1189; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1189 = *_hp; free(_hp); }
    if (_t1189) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1190; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1190 = *_hp; free(_hp); }
    if (_t1190) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1191; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1191 = *_hp; free(_hp); }
    if (_t1191) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1192; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1192 = *_hp; free(_hp); }
    if (_t1192) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1193; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1193 = *_hp; free(_hp); }
    if (_t1193) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1194; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1194 = *_hp; free(_hp); }
    if (_t1194) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1195; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1195 = *_hp; free(_hp); }
    if (_t1195) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1196; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1196 = *_hp; free(_hp); }
    if (_t1196) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1197; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1197 = *_hp; free(_hp); }
    if (_t1197) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1198; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1198 = *_hp; free(_hp); }
    if (_t1198) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1199; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1199 = *_hp; free(_hp); }
    if (_t1199) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1200; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1200 = *_hp; free(_hp); }
    if (_t1200) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1201; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1201 = *_hp; free(_hp); }
    if (_t1201) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1202; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1202 = *_hp; free(_hp); }
    if (_t1202) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1203; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1203 = *_hp; free(_hp); }
    if (_t1203) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1204; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1204 = *_hp; free(_hp); }
    if (_t1204) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1205; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1205 = *_hp; free(_hp); }
    if (_t1205) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1206; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1206 = *_hp; free(_hp); }
    if (_t1206) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1207; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1207 = *_hp; free(_hp); }
    if (_t1207) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1208; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1208 = *_hp; free(_hp); }
    if (_t1208) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1209; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1209 = *_hp; free(_hp); }
    if (_t1209) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1210; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1210 = *_hp; free(_hp); }
    if (_t1210) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1211; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1211 = *_hp; free(_hp); }
    if (_t1211) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1212; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1212 = *_hp; free(_hp); }
    if (_t1212) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1213; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1213 = *_hp; free(_hp); }
    if (_t1213) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1214; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1214 = *_hp; free(_hp); }
    if (_t1214) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1215; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1215 = *_hp; free(_hp); }
    if (_t1215) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1216; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1216 = *_hp; free(_hp); }
    if (_t1216) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1217; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1217 = *_hp; free(_hp); }
    if (_t1217) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1218; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1218 = *_hp; free(_hp); }
    if (_t1218) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1219; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1219 = *_hp; free(_hp); }
    if (_t1219) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1220; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1220 = *_hp; free(_hp); }
    if (_t1220) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1221; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1221 = *_hp; free(_hp); }
    if (_t1221) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1222; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1222 = *_hp; free(_hp); }
    if (_t1222) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1223; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1223 = *_hp; free(_hp); }
    if (_t1223) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1224; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1224 = *_hp; free(_hp); }
    if (_t1224) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1225; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1225 = *_hp; free(_hp); }
    if (_t1225) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1226; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1226 = *_hp; free(_hp); }
    if (_t1226) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1227; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1227 = *_hp; free(_hp); }
    if (_t1227) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1228; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1228 = *_hp; free(_hp); }
    if (_t1228) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1229; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1229 = *_hp; free(_hp); }
    if (_t1229) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1230; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1230 = *_hp; free(_hp); }
    if (_t1230) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1231; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1231 = *_hp; free(_hp); }
    if (_t1231) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1232; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1232 = *_hp; free(_hp); }
    if (_t1232) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1233; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1233 = *_hp; free(_hp); }
    if (_t1233) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1234; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1234 = *_hp; free(_hp); }
    if (_t1234) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1235; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1235 = *_hp; free(_hp); }
    if (_t1235) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1236; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1236 = *_hp; free(_hp); }
    if (_t1236) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1237; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1237 = *_hp; free(_hp); }
    if (_t1237) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1238; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1238 = *_hp; free(_hp); }
    if (_t1238) {
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
    Bool _t1302; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1302 = *_hp; free(_hp); }
    if (_t1302) {
        Str *_t1239 = Str_lit("Eof", 3ULL);
        ;
        return _t1239;
    }
    ;
    Bool _t1303; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1303 = *_hp; free(_hp); }
    if (_t1303) {
        Str *_t1240 = Str_lit("LParen", 6ULL);
        ;
        return _t1240;
    }
    ;
    Bool _t1304; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1304 = *_hp; free(_hp); }
    if (_t1304) {
        Str *_t1241 = Str_lit("RParen", 6ULL);
        ;
        return _t1241;
    }
    ;
    Bool _t1305; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1305 = *_hp; free(_hp); }
    if (_t1305) {
        Str *_t1242 = Str_lit("LBrace", 6ULL);
        ;
        return _t1242;
    }
    ;
    Bool _t1306; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1306 = *_hp; free(_hp); }
    if (_t1306) {
        Str *_t1243 = Str_lit("RBrace", 6ULL);
        ;
        return _t1243;
    }
    ;
    Bool _t1307; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1307 = *_hp; free(_hp); }
    if (_t1307) {
        Str *_t1244 = Str_lit("LBracket", 8ULL);
        ;
        return _t1244;
    }
    ;
    Bool _t1308; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1308 = *_hp; free(_hp); }
    if (_t1308) {
        Str *_t1245 = Str_lit("RBracket", 8ULL);
        ;
        return _t1245;
    }
    ;
    Bool _t1309; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1309 = *_hp; free(_hp); }
    if (_t1309) {
        Str *_t1246 = Str_lit("Comma", 5ULL);
        ;
        return _t1246;
    }
    ;
    Bool _t1310; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1310 = *_hp; free(_hp); }
    if (_t1310) {
        Str *_t1247 = Str_lit("Colon", 5ULL);
        ;
        return _t1247;
    }
    ;
    Bool _t1311; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1311 = *_hp; free(_hp); }
    if (_t1311) {
        Str *_t1248 = Str_lit("Question", 8ULL);
        ;
        return _t1248;
    }
    ;
    Bool _t1312; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1312 = *_hp; free(_hp); }
    if (_t1312) {
        Str *_t1249 = Str_lit("Bang", 4ULL);
        ;
        return _t1249;
    }
    ;
    Bool _t1313; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1313 = *_hp; free(_hp); }
    if (_t1313) {
        Str *_t1250 = Str_lit("Minus", 5ULL);
        ;
        return _t1250;
    }
    ;
    Bool _t1314; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1314 = *_hp; free(_hp); }
    if (_t1314) {
        Str *_t1251 = Str_lit("Plus", 4ULL);
        ;
        return _t1251;
    }
    ;
    Bool _t1315; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1315 = *_hp; free(_hp); }
    if (_t1315) {
        Str *_t1252 = Str_lit("Star", 4ULL);
        ;
        return _t1252;
    }
    ;
    Bool _t1316; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1316 = *_hp; free(_hp); }
    if (_t1316) {
        Str *_t1253 = Str_lit("Slash", 5ULL);
        ;
        return _t1253;
    }
    ;
    Bool _t1317; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1317 = *_hp; free(_hp); }
    if (_t1317) {
        Str *_t1254 = Str_lit("Dot", 3ULL);
        ;
        return _t1254;
    }
    ;
    Bool _t1318; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1318 = *_hp; free(_hp); }
    if (_t1318) {
        Str *_t1255 = Str_lit("DotDot", 6ULL);
        ;
        return _t1255;
    }
    ;
    Bool _t1319; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1319 = *_hp; free(_hp); }
    if (_t1319) {
        Str *_t1256 = Str_lit("Eq", 2ULL);
        ;
        return _t1256;
    }
    ;
    Bool _t1320; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1320 = *_hp; free(_hp); }
    if (_t1320) {
        Str *_t1257 = Str_lit("EqEq", 4ULL);
        ;
        return _t1257;
    }
    ;
    Bool _t1321; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1321 = *_hp; free(_hp); }
    if (_t1321) {
        Str *_t1258 = Str_lit("Neq", 3ULL);
        ;
        return _t1258;
    }
    ;
    Bool _t1322; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1322 = *_hp; free(_hp); }
    if (_t1322) {
        Str *_t1259 = Str_lit("Lt", 2ULL);
        ;
        return _t1259;
    }
    ;
    Bool _t1323; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1323 = *_hp; free(_hp); }
    if (_t1323) {
        Str *_t1260 = Str_lit("LtEq", 4ULL);
        ;
        return _t1260;
    }
    ;
    Bool _t1324; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1324 = *_hp; free(_hp); }
    if (_t1324) {
        Str *_t1261 = Str_lit("Gt", 2ULL);
        ;
        return _t1261;
    }
    ;
    Bool _t1325; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1325 = *_hp; free(_hp); }
    if (_t1325) {
        Str *_t1262 = Str_lit("GtEq", 4ULL);
        ;
        return _t1262;
    }
    ;
    Bool _t1326; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1326 = *_hp; free(_hp); }
    if (_t1326) {
        Str *_t1263 = Str_lit("ColonEq", 7ULL);
        ;
        return _t1263;
    }
    ;
    Bool _t1327; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1327 = *_hp; free(_hp); }
    if (_t1327) {
        Str *_t1264 = Str_lit("Ident", 5ULL);
        ;
        return _t1264;
    }
    ;
    Bool _t1328; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1328 = *_hp; free(_hp); }
    if (_t1328) {
        Str *_t1265 = Str_lit("StringTok", 9ULL);
        ;
        return _t1265;
    }
    ;
    Bool _t1329; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1329 = *_hp; free(_hp); }
    if (_t1329) {
        Str *_t1266 = Str_lit("Number", 6ULL);
        ;
        return _t1266;
    }
    ;
    Bool _t1330; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1330 = *_hp; free(_hp); }
    if (_t1330) {
        Str *_t1267 = Str_lit("Char", 4ULL);
        ;
        return _t1267;
    }
    ;
    Bool _t1331; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1331 = *_hp; free(_hp); }
    if (_t1331) {
        Str *_t1268 = Str_lit("KwMode", 6ULL);
        ;
        return _t1268;
    }
    ;
    Bool _t1332; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1332 = *_hp; free(_hp); }
    if (_t1332) {
        Str *_t1269 = Str_lit("KwMut", 5ULL);
        ;
        return _t1269;
    }
    ;
    Bool _t1333; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1333 = *_hp; free(_hp); }
    if (_t1333) {
        Str *_t1270 = Str_lit("KwOwn", 5ULL);
        ;
        return _t1270;
    }
    ;
    Bool _t1334; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1334 = *_hp; free(_hp); }
    if (_t1334) {
        Str *_t1271 = Str_lit("KwRef", 5ULL);
        ;
        return _t1271;
    }
    ;
    Bool _t1335; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1335 = *_hp; free(_hp); }
    if (_t1335) {
        Str *_t1272 = Str_lit("KwStruct", 8ULL);
        ;
        return _t1272;
    }
    ;
    Bool _t1336; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1336 = *_hp; free(_hp); }
    if (_t1336) {
        Str *_t1273 = Str_lit("KwExtStruct", 11ULL);
        ;
        return _t1273;
    }
    ;
    Bool _t1337; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1337 = *_hp; free(_hp); }
    if (_t1337) {
        Str *_t1274 = Str_lit("KwEnum", 6ULL);
        ;
        return _t1274;
    }
    ;
    Bool _t1338; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1338 = *_hp; free(_hp); }
    if (_t1338) {
        Str *_t1275 = Str_lit("KwNamespace", 11ULL);
        ;
        return _t1275;
    }
    ;
    Bool _t1339; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1339 = *_hp; free(_hp); }
    if (_t1339) {
        Str *_t1276 = Str_lit("KwFunc", 6ULL);
        ;
        return _t1276;
    }
    ;
    Bool _t1340; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1340 = *_hp; free(_hp); }
    if (_t1340) {
        Str *_t1277 = Str_lit("KwProc", 6ULL);
        ;
        return _t1277;
    }
    ;
    Bool _t1341; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1341 = *_hp; free(_hp); }
    if (_t1341) {
        Str *_t1278 = Str_lit("KwTest", 6ULL);
        ;
        return _t1278;
    }
    ;
    Bool _t1342; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1342 = *_hp; free(_hp); }
    if (_t1342) {
        Str *_t1279 = Str_lit("KwMacro", 7ULL);
        ;
        return _t1279;
    }
    ;
    Bool _t1343; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1343 = *_hp; free(_hp); }
    if (_t1343) {
        Str *_t1280 = Str_lit("KwExtFunc", 9ULL);
        ;
        return _t1280;
    }
    ;
    Bool _t1344; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1344 = *_hp; free(_hp); }
    if (_t1344) {
        Str *_t1281 = Str_lit("KwExtProc", 9ULL);
        ;
        return _t1281;
    }
    ;
    Bool _t1345; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1345 = *_hp; free(_hp); }
    if (_t1345) {
        Str *_t1282 = Str_lit("KwReturns", 9ULL);
        ;
        return _t1282;
    }
    ;
    Bool _t1346; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1346 = *_hp; free(_hp); }
    if (_t1346) {
        Str *_t1283 = Str_lit("KwThrows", 8ULL);
        ;
        return _t1283;
    }
    ;
    Bool _t1347; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1347 = *_hp; free(_hp); }
    if (_t1347) {
        Str *_t1284 = Str_lit("KwIf", 4ULL);
        ;
        return _t1284;
    }
    ;
    Bool _t1348; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1348 = *_hp; free(_hp); }
    if (_t1348) {
        Str *_t1285 = Str_lit("KwElse", 6ULL);
        ;
        return _t1285;
    }
    ;
    Bool _t1349; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1349 = *_hp; free(_hp); }
    if (_t1349) {
        Str *_t1286 = Str_lit("KwWhile", 7ULL);
        ;
        return _t1286;
    }
    ;
    Bool _t1350; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1350 = *_hp; free(_hp); }
    if (_t1350) {
        Str *_t1287 = Str_lit("KwFor", 5ULL);
        ;
        return _t1287;
    }
    ;
    Bool _t1351; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1351 = *_hp; free(_hp); }
    if (_t1351) {
        Str *_t1288 = Str_lit("KwIn", 4ULL);
        ;
        return _t1288;
    }
    ;
    Bool _t1352; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1352 = *_hp; free(_hp); }
    if (_t1352) {
        Str *_t1289 = Str_lit("KwSwitch", 8ULL);
        ;
        return _t1289;
    }
    ;
    Bool _t1353; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1353 = *_hp; free(_hp); }
    if (_t1353) {
        Str *_t1290 = Str_lit("KwMatch", 7ULL);
        ;
        return _t1290;
    }
    ;
    Bool _t1354; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1354 = *_hp; free(_hp); }
    if (_t1354) {
        Str *_t1291 = Str_lit("KwCase", 6ULL);
        ;
        return _t1291;
    }
    ;
    Bool _t1355; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1355 = *_hp; free(_hp); }
    if (_t1355) {
        Str *_t1292 = Str_lit("KwDefault", 9ULL);
        ;
        return _t1292;
    }
    ;
    Bool _t1356; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1356 = *_hp; free(_hp); }
    if (_t1356) {
        Str *_t1293 = Str_lit("KwReturn", 8ULL);
        ;
        return _t1293;
    }
    ;
    Bool _t1357; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1357 = *_hp; free(_hp); }
    if (_t1357) {
        Str *_t1294 = Str_lit("KwThrow", 7ULL);
        ;
        return _t1294;
    }
    ;
    Bool _t1358; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1358 = *_hp; free(_hp); }
    if (_t1358) {
        Str *_t1295 = Str_lit("KwCatch", 7ULL);
        ;
        return _t1295;
    }
    ;
    Bool _t1359; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1359 = *_hp; free(_hp); }
    if (_t1359) {
        Str *_t1296 = Str_lit("KwBreak", 7ULL);
        ;
        return _t1296;
    }
    ;
    Bool _t1360; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1360 = *_hp; free(_hp); }
    if (_t1360) {
        Str *_t1297 = Str_lit("KwContinue", 10ULL);
        ;
        return _t1297;
    }
    ;
    Bool _t1361; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1361 = *_hp; free(_hp); }
    if (_t1361) {
        Str *_t1298 = Str_lit("KwDefer", 7ULL);
        ;
        return _t1298;
    }
    ;
    Bool _t1362; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1362 = *_hp; free(_hp); }
    if (_t1362) {
        Str *_t1299 = Str_lit("KwTrue", 6ULL);
        ;
        return _t1299;
    }
    ;
    Bool _t1363; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1363 = *_hp; free(_hp); }
    if (_t1363) {
        Str *_t1300 = Str_lit("KwFalse", 7ULL);
        ;
        return _t1300;
    }
    ;
    Bool _t1364; { Bool *_hp = TokenType_eq(self, TokenType_Error()); _t1364 = *_hp; free(_hp); }
    if (_t1364) {
        Str *_t1301 = Str_lit("Error", 5ULL);
        ;
        return _t1301;
    }
    ;
    Str *_t1365 = Str_lit("unknown", 7ULL);
    return _t1365;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1367 = I64_clone(&self->line);
    I64 _t1368 = I64_clone(&self->col);
    Token *_t1369 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1369->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1369->text = *_ca; free(_ca); }
    _t1369->line = _t1367;
    _t1369->col = _t1368;
    ;
    ;
    return _t1369;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    Bool _t1370 = 0;
    TokenType_delete(&self->type, &(Bool){_t1370});
    ;
    Bool _t1371 = 0;
    Str_delete(&self->text, &(Bool){_t1371});
    ;
    Bool _t1372 = 0;
    I64_delete(&self->line, &(Bool){_t1372});
    ;
    Bool _t1373 = 0;
    I64_delete(&self->col, &(Bool){_t1373});
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
    U8 _t1375 = 48;
    U8 _t1376 = 57;
    Bool _t1377; { Bool *_hp = U8_gte(c, &(U8){_t1375}); _t1377 = *_hp; free(_hp); }
    ;
    Bool _t1378; { Bool *_hp = U8_lte(c, &(U8){_t1376}); _t1378 = *_hp; free(_hp); }
    ;
    Bool _t1379 = Bool_and(_t1377, _t1378);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1379; return _r; }
}

Bool * is_alpha(U8 * c) {
    U8 _t1380 = 97;
    U8 _t1381 = 122;
    Bool _t1382; { Bool *_hp = U8_gte(c, &(U8){_t1380}); _t1382 = *_hp; free(_hp); }
    ;
    Bool _t1383; { Bool *_hp = U8_lte(c, &(U8){_t1381}); _t1383 = *_hp; free(_hp); }
    ;
    U8 _t1384 = 65;
    U8 _t1385 = 90;
    Bool _t1386; { Bool *_hp = U8_gte(c, &(U8){_t1384}); _t1386 = *_hp; free(_hp); }
    ;
    Bool _t1387; { Bool *_hp = U8_lte(c, &(U8){_t1385}); _t1387 = *_hp; free(_hp); }
    ;
    Bool _t1388 = Bool_and(_t1382, _t1383);
    ;
    ;
    Bool _t1389 = Bool_and(_t1386, _t1387);
    ;
    ;
    U8 _t1390 = 95;
    Bool _t1391 = Bool_or(_t1388, _t1389);
    ;
    ;
    Bool _t1392 = U8_eq(DEREF(c), _t1390);
    ;
    Bool _t1393 = Bool_or(_t1391, _t1392);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1393; return _r; }
}

Bool * is_alnum(U8 * c) {
    Bool _t1394; { Bool *_hp = is_alpha(c); _t1394 = *_hp; free(_hp); }
    Bool _t1395; { Bool *_hp = is_digit(c); _t1395 = *_hp; free(_hp); }
    Bool _t1396 = Bool_or(_t1394, _t1395);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1396; return _r; }
}

Str * tok_name(TokenType * type) {
    {
        TokenType *_sw1397 = TokenType_clone(type);
        Bool _t1524; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Eof()); _t1524 = *_hp; free(_hp); }
        if (_t1524) {
            Str *_t1398 = Str_lit("eof", 3ULL);
            TokenType_delete(_sw1397, &(Bool){1});
            ;
            return _t1398;
        } else {
            Bool _t1523; { Bool *_hp = TokenType_eq(_sw1397, TokenType_LParen()); _t1523 = *_hp; free(_hp); }
            if (_t1523) {
                Str *_t1399 = Str_lit("(", 1ULL);
                ;
                TokenType_delete(_sw1397, &(Bool){1});
                ;
                return _t1399;
            } else {
                Bool _t1522; { Bool *_hp = TokenType_eq(_sw1397, TokenType_RParen()); _t1522 = *_hp; free(_hp); }
                if (_t1522) {
                    Str *_t1400 = Str_lit(")", 1ULL);
                    ;
                    ;
                    TokenType_delete(_sw1397, &(Bool){1});
                    ;
                    return _t1400;
                } else {
                    Bool _t1521; { Bool *_hp = TokenType_eq(_sw1397, TokenType_LBrace()); _t1521 = *_hp; free(_hp); }
                    if (_t1521) {
                        Str *_t1401 = Str_lit("{", 1ULL);
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1397, &(Bool){1});
                        ;
                        return _t1401;
                    } else {
                        Bool _t1520; { Bool *_hp = TokenType_eq(_sw1397, TokenType_RBrace()); _t1520 = *_hp; free(_hp); }
                        if (_t1520) {
                            Str *_t1402 = Str_lit("}", 1ULL);
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1397, &(Bool){1});
                            ;
                            return _t1402;
                        } else {
                            Bool _t1519; { Bool *_hp = TokenType_eq(_sw1397, TokenType_LBracket()); _t1519 = *_hp; free(_hp); }
                            if (_t1519) {
                                Str *_t1403 = Str_lit("[", 1ULL);
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1397, &(Bool){1});
                                ;
                                return _t1403;
                            } else {
                                Bool _t1518; { Bool *_hp = TokenType_eq(_sw1397, TokenType_RBracket()); _t1518 = *_hp; free(_hp); }
                                if (_t1518) {
                                    Str *_t1404 = Str_lit("]", 1ULL);
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1397, &(Bool){1});
                                    ;
                                    return _t1404;
                                } else {
                                    Bool _t1517; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Comma()); _t1517 = *_hp; free(_hp); }
                                    if (_t1517) {
                                        Str *_t1405 = Str_lit(",", 1ULL);
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1397, &(Bool){1});
                                        ;
                                        return _t1405;
                                    } else {
                                        Bool _t1516; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Colon()); _t1516 = *_hp; free(_hp); }
                                        if (_t1516) {
                                            Str *_t1406 = Str_lit(":", 1ULL);
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1397, &(Bool){1});
                                            ;
                                            return _t1406;
                                        } else {
                                            Bool _t1515; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Question()); _t1515 = *_hp; free(_hp); }
                                            if (_t1515) {
                                                Str *_t1407 = Str_lit("?", 1ULL);
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1397, &(Bool){1});
                                                ;
                                                return _t1407;
                                            } else {
                                                Bool _t1514; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Bang()); _t1514 = *_hp; free(_hp); }
                                                if (_t1514) {
                                                    Str *_t1408 = Str_lit("!", 1ULL);
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                    ;
                                                    return _t1408;
                                                } else {
                                                    Bool _t1513; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Minus()); _t1513 = *_hp; free(_hp); }
                                                    if (_t1513) {
                                                        Str *_t1409 = Str_lit("-", 1ULL);
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                        ;
                                                        return _t1409;
                                                    } else {
                                                        Bool _t1512; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Plus()); _t1512 = *_hp; free(_hp); }
                                                        if (_t1512) {
                                                            Str *_t1410 = Str_lit("+", 1ULL);
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                            ;
                                                            return _t1410;
                                                        } else {
                                                            Bool _t1511; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Star()); _t1511 = *_hp; free(_hp); }
                                                            if (_t1511) {
                                                                Str *_t1411 = Str_lit("*", 1ULL);
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                ;
                                                                return _t1411;
                                                            } else {
                                                                Bool _t1510; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Slash()); _t1510 = *_hp; free(_hp); }
                                                                if (_t1510) {
                                                                    Str *_t1412 = Str_lit("/", 1ULL);
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                    ;
                                                                    return _t1412;
                                                                } else {
                                                                    Bool _t1509; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Dot()); _t1509 = *_hp; free(_hp); }
                                                                    if (_t1509) {
                                                                        Str *_t1413 = Str_lit(".", 1ULL);
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                        ;
                                                                        return _t1413;
                                                                    } else {
                                                                        Bool _t1508; { Bool *_hp = TokenType_eq(_sw1397, TokenType_DotDot()); _t1508 = *_hp; free(_hp); }
                                                                        if (_t1508) {
                                                                            Str *_t1414 = Str_lit("..", 2ULL);
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                            ;
                                                                            return _t1414;
                                                                        } else {
                                                                            Bool _t1507; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Eq()); _t1507 = *_hp; free(_hp); }
                                                                            if (_t1507) {
                                                                                Str *_t1415 = Str_lit("=", 1ULL);
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                ;
                                                                                return _t1415;
                                                                            } else {
                                                                                Bool _t1506; { Bool *_hp = TokenType_eq(_sw1397, TokenType_EqEq()); _t1506 = *_hp; free(_hp); }
                                                                                if (_t1506) {
                                                                                    Str *_t1416 = Str_lit("==", 2ULL);
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                    ;
                                                                                    return _t1416;
                                                                                } else {
                                                                                    Bool _t1505; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Neq()); _t1505 = *_hp; free(_hp); }
                                                                                    if (_t1505) {
                                                                                        Str *_t1417 = Str_lit("!=", 2ULL);
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                        ;
                                                                                        return _t1417;
                                                                                    } else {
                                                                                        Bool _t1504; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Lt()); _t1504 = *_hp; free(_hp); }
                                                                                        if (_t1504) {
                                                                                            Str *_t1418 = Str_lit("<", 1ULL);
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                            ;
                                                                                            return _t1418;
                                                                                        } else {
                                                                                            Bool _t1503; { Bool *_hp = TokenType_eq(_sw1397, TokenType_LtEq()); _t1503 = *_hp; free(_hp); }
                                                                                            if (_t1503) {
                                                                                                Str *_t1419 = Str_lit("<=", 2ULL);
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                ;
                                                                                                return _t1419;
                                                                                            } else {
                                                                                                Bool _t1502; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Gt()); _t1502 = *_hp; free(_hp); }
                                                                                                if (_t1502) {
                                                                                                    Str *_t1420 = Str_lit(">", 1ULL);
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1420;
                                                                                                } else {
                                                                                                    Bool _t1501; { Bool *_hp = TokenType_eq(_sw1397, TokenType_GtEq()); _t1501 = *_hp; free(_hp); }
                                                                                                    if (_t1501) {
                                                                                                        Str *_t1421 = Str_lit(">=", 2ULL);
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1421;
                                                                                                    } else {
                                                                                                        Bool _t1500; { Bool *_hp = TokenType_eq(_sw1397, TokenType_ColonEq()); _t1500 = *_hp; free(_hp); }
                                                                                                        if (_t1500) {
                                                                                                            Str *_t1422 = Str_lit(":=", 2ULL);
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1422;
                                                                                                        } else {
                                                                                                            Bool _t1499; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Ident()); _t1499 = *_hp; free(_hp); }
                                                                                                            if (_t1499) {
                                                                                                                Str *_t1423 = Str_lit("identifier", 10ULL);
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1423;
                                                                                                            } else {
                                                                                                                Bool _t1498; { Bool *_hp = TokenType_eq(_sw1397, TokenType_StringTok()); _t1498 = *_hp; free(_hp); }
                                                                                                                if (_t1498) {
                                                                                                                    Str *_t1424 = Str_lit("string", 6ULL);
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1424;
                                                                                                                } else {
                                                                                                                    Bool _t1497; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Number()); _t1497 = *_hp; free(_hp); }
                                                                                                                    if (_t1497) {
                                                                                                                        Str *_t1425 = Str_lit("number", 6ULL);
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1425;
                                                                                                                    } else {
                                                                                                                        Bool _t1496; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Char()); _t1496 = *_hp; free(_hp); }
                                                                                                                        if (_t1496) {
                                                                                                                            Str *_t1426 = Str_lit("char", 4ULL);
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1426;
                                                                                                                        } else {
                                                                                                                            Bool _t1495; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwMode()); _t1495 = *_hp; free(_hp); }
                                                                                                                            if (_t1495) {
                                                                                                                                Str *_t1427 = Str_lit("mode", 4ULL);
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1427;
                                                                                                                            } else {
                                                                                                                                Bool _t1494; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwMut()); _t1494 = *_hp; free(_hp); }
                                                                                                                                if (_t1494) {
                                                                                                                                    Str *_t1428 = Str_lit("mut", 3ULL);
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1428;
                                                                                                                                } else {
                                                                                                                                    Bool _t1493; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwOwn()); _t1493 = *_hp; free(_hp); }
                                                                                                                                    if (_t1493) {
                                                                                                                                        Str *_t1429 = Str_lit("own", 3ULL);
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1429;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1492; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwRef()); _t1492 = *_hp; free(_hp); }
                                                                                                                                        if (_t1492) {
                                                                                                                                            Str *_t1430 = Str_lit("ref", 3ULL);
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1430;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1491; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwStruct()); _t1491 = *_hp; free(_hp); }
                                                                                                                                            if (_t1491) {
                                                                                                                                                Str *_t1431 = Str_lit("struct", 6ULL);
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1431;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1490; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwExtStruct()); _t1490 = *_hp; free(_hp); }
                                                                                                                                                if (_t1490) {
                                                                                                                                                    Str *_t1432 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1432;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1489; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwEnum()); _t1489 = *_hp; free(_hp); }
                                                                                                                                                    if (_t1489) {
                                                                                                                                                        Str *_t1433 = Str_lit("enum", 4ULL);
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1433;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1488; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwNamespace()); _t1488 = *_hp; free(_hp); }
                                                                                                                                                        if (_t1488) {
                                                                                                                                                            Str *_t1434 = Str_lit("namespace", 9ULL);
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1434;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1487; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwFunc()); _t1487 = *_hp; free(_hp); }
                                                                                                                                                            if (_t1487) {
                                                                                                                                                                Str *_t1435 = Str_lit("func", 4ULL);
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1435;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1486; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwProc()); _t1486 = *_hp; free(_hp); }
                                                                                                                                                                if (_t1486) {
                                                                                                                                                                    Str *_t1436 = Str_lit("proc", 4ULL);
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1436;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1485; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwTest()); _t1485 = *_hp; free(_hp); }
                                                                                                                                                                    if (_t1485) {
                                                                                                                                                                        Str *_t1437 = Str_lit("test", 4ULL);
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1437;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1484; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwMacro()); _t1484 = *_hp; free(_hp); }
                                                                                                                                                                        if (_t1484) {
                                                                                                                                                                            Str *_t1438 = Str_lit("macro", 5ULL);
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1438;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1483; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwExtFunc()); _t1483 = *_hp; free(_hp); }
                                                                                                                                                                            if (_t1483) {
                                                                                                                                                                                Str *_t1439 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1439;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1482; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwExtProc()); _t1482 = *_hp; free(_hp); }
                                                                                                                                                                                if (_t1482) {
                                                                                                                                                                                    Str *_t1440 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1440;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1481; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwReturns()); _t1481 = *_hp; free(_hp); }
                                                                                                                                                                                    if (_t1481) {
                                                                                                                                                                                        Str *_t1441 = Str_lit("returns", 7ULL);
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1441;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1480; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwThrows()); _t1480 = *_hp; free(_hp); }
                                                                                                                                                                                        if (_t1480) {
                                                                                                                                                                                            Str *_t1442 = Str_lit("throws", 6ULL);
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1442;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1479; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwIf()); _t1479 = *_hp; free(_hp); }
                                                                                                                                                                                            if (_t1479) {
                                                                                                                                                                                                Str *_t1443 = Str_lit("if", 2ULL);
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1443;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1478; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwElse()); _t1478 = *_hp; free(_hp); }
                                                                                                                                                                                                if (_t1478) {
                                                                                                                                                                                                    Str *_t1444 = Str_lit("else", 4ULL);
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1444;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1477; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwWhile()); _t1477 = *_hp; free(_hp); }
                                                                                                                                                                                                    if (_t1477) {
                                                                                                                                                                                                        Str *_t1445 = Str_lit("while", 5ULL);
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1445;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1476; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwFor()); _t1476 = *_hp; free(_hp); }
                                                                                                                                                                                                        if (_t1476) {
                                                                                                                                                                                                            Str *_t1446 = Str_lit("for", 3ULL);
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1446;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1475; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwIn()); _t1475 = *_hp; free(_hp); }
                                                                                                                                                                                                            if (_t1475) {
                                                                                                                                                                                                                Str *_t1447 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1447;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1474; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwSwitch()); _t1474 = *_hp; free(_hp); }
                                                                                                                                                                                                                if (_t1474) {
                                                                                                                                                                                                                    Str *_t1448 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1448;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1473; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwMatch()); _t1473 = *_hp; free(_hp); }
                                                                                                                                                                                                                    if (_t1473) {
                                                                                                                                                                                                                        Str *_t1449 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1449;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1472; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwCase()); _t1472 = *_hp; free(_hp); }
                                                                                                                                                                                                                        if (_t1472) {
                                                                                                                                                                                                                            Str *_t1450 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1450;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1471; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwDefault()); _t1471 = *_hp; free(_hp); }
                                                                                                                                                                                                                            if (_t1471) {
                                                                                                                                                                                                                                Str *_t1451 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1451;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1470; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwReturn()); _t1470 = *_hp; free(_hp); }
                                                                                                                                                                                                                                if (_t1470) {
                                                                                                                                                                                                                                    Str *_t1452 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1452;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1469; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwThrow()); _t1469 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    if (_t1469) {
                                                                                                                                                                                                                                        Str *_t1453 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1453;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1468; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwCatch()); _t1468 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        if (_t1468) {
                                                                                                                                                                                                                                            Str *_t1454 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1454;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1467; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwBreak()); _t1467 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            if (_t1467) {
                                                                                                                                                                                                                                                Str *_t1455 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1455;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1466; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwContinue()); _t1466 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                if (_t1466) {
                                                                                                                                                                                                                                                    Str *_t1456 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1456;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1465; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwDefer()); _t1465 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    if (_t1465) {
                                                                                                                                                                                                                                                        Str *_t1457 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1457;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1464; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwTrue()); _t1464 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        if (_t1464) {
                                                                                                                                                                                                                                                            Str *_t1458 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1458;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1463; { Bool *_hp = TokenType_eq(_sw1397, TokenType_KwFalse()); _t1463 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            if (_t1463) {
                                                                                                                                                                                                                                                                Str *_t1459 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1459;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1462; { Bool *_hp = TokenType_eq(_sw1397, TokenType_Error()); _t1462 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                if (_t1462) {
                                                                                                                                                                                                                                                                    Str *_t1460 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1460;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Str *_t1461 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1397, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1461;
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
        TokenType_delete(_sw1397, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    {
        Str *_sw1525 = Str_clone(word);
        Str *_t1590 = Str_lit("mode", 4ULL);
        Bool _t1591; { Bool *_hp = Str_eq(_sw1525, _t1590); _t1591 = *_hp; free(_hp); }
        Str_delete(_t1590, &(Bool){1});
        if (_t1591) {
            Str_delete(_sw1525, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1588 = Str_lit("mut", 3ULL);
            Bool _t1589; { Bool *_hp = Str_eq(_sw1525, _t1588); _t1589 = *_hp; free(_hp); }
            Str_delete(_t1588, &(Bool){1});
            if (_t1589) {
                ;
                Str_delete(_sw1525, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1586 = Str_lit("own", 3ULL);
                Bool _t1587; { Bool *_hp = Str_eq(_sw1525, _t1586); _t1587 = *_hp; free(_hp); }
                Str_delete(_t1586, &(Bool){1});
                if (_t1587) {
                    ;
                    ;
                    Str_delete(_sw1525, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1584 = Str_lit("ref", 3ULL);
                    Bool _t1585; { Bool *_hp = Str_eq(_sw1525, _t1584); _t1585 = *_hp; free(_hp); }
                    Str_delete(_t1584, &(Bool){1});
                    if (_t1585) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1525, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1582 = Str_lit("struct", 6ULL);
                        Bool _t1583; { Bool *_hp = Str_eq(_sw1525, _t1582); _t1583 = *_hp; free(_hp); }
                        Str_delete(_t1582, &(Bool){1});
                        if (_t1583) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1525, &(Bool){1});
                            ;
                            return TokenType_KwStruct();
                        } else {
                            Str *_t1580 = Str_lit("ext_struct", 10ULL);
                            Bool _t1581; { Bool *_hp = Str_eq(_sw1525, _t1580); _t1581 = *_hp; free(_hp); }
                            Str_delete(_t1580, &(Bool){1});
                            if (_t1581) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1525, &(Bool){1});
                                ;
                                return TokenType_KwExtStruct();
                            } else {
                                Str *_t1578 = Str_lit("enum", 4ULL);
                                Bool _t1579; { Bool *_hp = Str_eq(_sw1525, _t1578); _t1579 = *_hp; free(_hp); }
                                Str_delete(_t1578, &(Bool){1});
                                if (_t1579) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1525, &(Bool){1});
                                    ;
                                    return TokenType_KwEnum();
                                } else {
                                    Str *_t1576 = Str_lit("namespace", 9ULL);
                                    Bool _t1577; { Bool *_hp = Str_eq(_sw1525, _t1576); _t1577 = *_hp; free(_hp); }
                                    Str_delete(_t1576, &(Bool){1});
                                    if (_t1577) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1525, &(Bool){1});
                                        ;
                                        return TokenType_KwNamespace();
                                    } else {
                                        Str *_t1574 = Str_lit("func", 4ULL);
                                        Bool _t1575; { Bool *_hp = Str_eq(_sw1525, _t1574); _t1575 = *_hp; free(_hp); }
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
                                            Str_delete(_sw1525, &(Bool){1});
                                            ;
                                            return TokenType_KwFunc();
                                        } else {
                                            Str *_t1572 = Str_lit("proc", 4ULL);
                                            Bool _t1573; { Bool *_hp = Str_eq(_sw1525, _t1572); _t1573 = *_hp; free(_hp); }
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
                                                Str_delete(_sw1525, &(Bool){1});
                                                ;
                                                return TokenType_KwProc();
                                            } else {
                                                Str *_t1570 = Str_lit("test", 4ULL);
                                                Bool _t1571; { Bool *_hp = Str_eq(_sw1525, _t1570); _t1571 = *_hp; free(_hp); }
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
                                                    Str_delete(_sw1525, &(Bool){1});
                                                    ;
                                                    return TokenType_KwTest();
                                                } else {
                                                    Str *_t1568 = Str_lit("macro", 5ULL);
                                                    Bool _t1569; { Bool *_hp = Str_eq(_sw1525, _t1568); _t1569 = *_hp; free(_hp); }
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
                                                        Str_delete(_sw1525, &(Bool){1});
                                                        ;
                                                        return TokenType_KwMacro();
                                                    } else {
                                                        Str *_t1566 = Str_lit("ext_func", 8ULL);
                                                        Bool _t1567; { Bool *_hp = Str_eq(_sw1525, _t1566); _t1567 = *_hp; free(_hp); }
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
                                                            Str_delete(_sw1525, &(Bool){1});
                                                            ;
                                                            return TokenType_KwExtFunc();
                                                        } else {
                                                            Str *_t1564 = Str_lit("ext_proc", 8ULL);
                                                            Bool _t1565; { Bool *_hp = Str_eq(_sw1525, _t1564); _t1565 = *_hp; free(_hp); }
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
                                                                Str_delete(_sw1525, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtProc();
                                                            } else {
                                                                Str *_t1562 = Str_lit("returns", 7ULL);
                                                                Bool _t1563; { Bool *_hp = Str_eq(_sw1525, _t1562); _t1563 = *_hp; free(_hp); }
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
                                                                    Str_delete(_sw1525, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwReturns();
                                                                } else {
                                                                    Str *_t1560 = Str_lit("throws", 6ULL);
                                                                    Bool _t1561; { Bool *_hp = Str_eq(_sw1525, _t1560); _t1561 = *_hp; free(_hp); }
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
                                                                        Str_delete(_sw1525, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwThrows();
                                                                    } else {
                                                                        Str *_t1558 = Str_lit("if", 2ULL);
                                                                        Bool _t1559; { Bool *_hp = Str_eq(_sw1525, _t1558); _t1559 = *_hp; free(_hp); }
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
                                                                            Str_delete(_sw1525, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwIf();
                                                                        } else {
                                                                            Str *_t1556 = Str_lit("else", 4ULL);
                                                                            Bool _t1557; { Bool *_hp = Str_eq(_sw1525, _t1556); _t1557 = *_hp; free(_hp); }
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
                                                                                Str_delete(_sw1525, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwElse();
                                                                            } else {
                                                                                Str *_t1554 = Str_lit("while", 5ULL);
                                                                                Bool _t1555; { Bool *_hp = Str_eq(_sw1525, _t1554); _t1555 = *_hp; free(_hp); }
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
                                                                                    Str_delete(_sw1525, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwWhile();
                                                                                } else {
                                                                                    Str *_t1552 = Str_lit("for", 3ULL);
                                                                                    Bool _t1553; { Bool *_hp = Str_eq(_sw1525, _t1552); _t1553 = *_hp; free(_hp); }
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
                                                                                        Str_delete(_sw1525, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwFor();
                                                                                    } else {
                                                                                        Str *_t1550 = Str_lit("in", 2ULL);
                                                                                        Bool _t1551; { Bool *_hp = Str_eq(_sw1525, _t1550); _t1551 = *_hp; free(_hp); }
                                                                                        Str_delete(_t1550, &(Bool){1});
                                                                                        if (_t1551) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1525, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwIn();
                                                                                        } else {
                                                                                            Str *_t1548 = Str_lit("switch", 6ULL);
                                                                                            Bool _t1549; { Bool *_hp = Str_eq(_sw1525, _t1548); _t1549 = *_hp; free(_hp); }
                                                                                            Str_delete(_t1548, &(Bool){1});
                                                                                            if (_t1549) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1525, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwSwitch();
                                                                                            } else {
                                                                                                Str *_t1546 = Str_lit("match", 5ULL);
                                                                                                Bool _t1547; { Bool *_hp = Str_eq(_sw1525, _t1546); _t1547 = *_hp; free(_hp); }
                                                                                                Str_delete(_t1546, &(Bool){1});
                                                                                                if (_t1547) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1525, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwMatch();
                                                                                                } else {
                                                                                                    Str *_t1544 = Str_lit("case", 4ULL);
                                                                                                    Bool _t1545; { Bool *_hp = Str_eq(_sw1525, _t1544); _t1545 = *_hp; free(_hp); }
                                                                                                    Str_delete(_t1544, &(Bool){1});
                                                                                                    if (_t1545) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1525, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwCase();
                                                                                                    } else {
                                                                                                        Str *_t1542 = Str_lit("default", 7ULL);
                                                                                                        Bool _t1543; { Bool *_hp = Str_eq(_sw1525, _t1542); _t1543 = *_hp; free(_hp); }
                                                                                                        Str_delete(_t1542, &(Bool){1});
                                                                                                        if (_t1543) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1525, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwDefault();
                                                                                                        } else {
                                                                                                            Str *_t1540 = Str_lit("return", 6ULL);
                                                                                                            Bool _t1541; { Bool *_hp = Str_eq(_sw1525, _t1540); _t1541 = *_hp; free(_hp); }
                                                                                                            Str_delete(_t1540, &(Bool){1});
                                                                                                            if (_t1541) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1525, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwReturn();
                                                                                                            } else {
                                                                                                                Str *_t1538 = Str_lit("throw", 5ULL);
                                                                                                                Bool _t1539; { Bool *_hp = Str_eq(_sw1525, _t1538); _t1539 = *_hp; free(_hp); }
                                                                                                                Str_delete(_t1538, &(Bool){1});
                                                                                                                if (_t1539) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1525, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwThrow();
                                                                                                                } else {
                                                                                                                    Str *_t1536 = Str_lit("catch", 5ULL);
                                                                                                                    Bool _t1537; { Bool *_hp = Str_eq(_sw1525, _t1536); _t1537 = *_hp; free(_hp); }
                                                                                                                    Str_delete(_t1536, &(Bool){1});
                                                                                                                    if (_t1537) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1525, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwCatch();
                                                                                                                    } else {
                                                                                                                        Str *_t1534 = Str_lit("break", 5ULL);
                                                                                                                        Bool _t1535; { Bool *_hp = Str_eq(_sw1525, _t1534); _t1535 = *_hp; free(_hp); }
                                                                                                                        Str_delete(_t1534, &(Bool){1});
                                                                                                                        if (_t1535) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1525, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwBreak();
                                                                                                                        } else {
                                                                                                                            Str *_t1532 = Str_lit("continue", 8ULL);
                                                                                                                            Bool _t1533; { Bool *_hp = Str_eq(_sw1525, _t1532); _t1533 = *_hp; free(_hp); }
                                                                                                                            Str_delete(_t1532, &(Bool){1});
                                                                                                                            if (_t1533) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1525, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwContinue();
                                                                                                                            } else {
                                                                                                                                Str *_t1530 = Str_lit("defer", 5ULL);
                                                                                                                                Bool _t1531; { Bool *_hp = Str_eq(_sw1525, _t1530); _t1531 = *_hp; free(_hp); }
                                                                                                                                Str_delete(_t1530, &(Bool){1});
                                                                                                                                if (_t1531) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1525, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwDefer();
                                                                                                                                } else {
                                                                                                                                    Str *_t1528 = Str_lit("true", 4ULL);
                                                                                                                                    Bool _t1529; { Bool *_hp = Str_eq(_sw1525, _t1528); _t1529 = *_hp; free(_hp); }
                                                                                                                                    Str_delete(_t1528, &(Bool){1});
                                                                                                                                    if (_t1529) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1525, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwTrue();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1526 = Str_lit("false", 5ULL);
                                                                                                                                        Bool _t1527; { Bool *_hp = Str_eq(_sw1525, _t1526); _t1527 = *_hp; free(_hp); }
                                                                                                                                        Str_delete(_t1526, &(Bool){1});
                                                                                                                                        if (_t1527) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1525, &(Bool){1});
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
                                                                                                                                            Str_delete(_sw1525, &(Bool){1});
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
        Str_delete(_sw1525, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * source, Str * path) {
    Str *_t1947 = Str_lit("Token", 5ULL);
    U64 _t1948; { U64 *_hp = Token_size(); _t1948 = *_hp; free(_hp); }
    Vec *tokens = Vec_new(_t1947, &(U64){_t1948});
    Str_delete(_t1947, &(Bool){1});
    ;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    I64 line = 1;
    U64 line_start = 0;
    U64 src_len; { U64 *_hp = Str_len(source); src_len = *_hp; free(_hp); }
    while (1) {
        Bool _wcond1592; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1592 = *_hp; free(_hp); }
        if (_wcond1592) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_get(source, pos);
        U8 _t1892 = 32;
        U8 _t1893 = 9;
        Bool _t1894 = U8_eq(DEREF(c), _t1892);
        ;
        Bool _t1895 = U8_eq(DEREF(c), _t1893);
        ;
        U8 _t1896 = 13;
        Bool _t1897 = Bool_or(_t1894, _t1895);
        ;
        ;
        Bool _t1898 = U8_eq(DEREF(c), _t1896);
        ;
        U8 _t1899 = 59;
        Bool _t1900 = Bool_or(_t1897, _t1898);
        ;
        ;
        Bool _t1901 = U8_eq(DEREF(c), _t1899);
        ;
        Bool _t1902 = Bool_or(_t1900, _t1901);
        ;
        ;
        if (_t1902) {
            U64 _t1593 = 1;
            U64 _t1594 = U64_add(DEREF(pos), _t1593);
            ;
            *pos = _t1594;
            ;
            ;
            continue;
        }
        ;
        U8 _t1903 = 10;
        Bool _t1904 = U8_eq(DEREF(c), _t1903);
        ;
        if (_t1904) {
            U64 _t1595 = 1;
            U64 _t1596 = U64_add(DEREF(pos), _t1595);
            ;
            *pos = _t1596;
            ;
            I64 _t1597 = 1;
            I64 _t1598 = I64_add(line, _t1597);
            ;
            line = _t1598;
            ;
            U64 _t1599 = U64_clone(pos);
            line_start = _t1599;
            ;
            ;
            continue;
        }
        ;
        U64 _t1905 = U64_sub(DEREF(pos), line_start);
        U64 _t1906 = 1;
        U64 _t1907 = U64_add(_t1905, _t1906);
        ;
        ;
        I64 col = U64_to_i64(_t1907);
        ;
        U64 start = U64_clone(pos);
        U8 _t1908 = 35;
        Bool _t1909 = U8_eq(DEREF(c), _t1908);
        ;
        if (_t1909) {
            while (1) {
                Bool _wcond1600; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1600 = *_hp; free(_hp); }
                if (_wcond1600) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1601 = Str_get(source, pos);
                U8 _t1602 = 10;
                Bool _t1603 = U8_eq(DEREF(_t1601), _t1602);
                ;
                if (_t1603) {
                    ;
                    break;
                }
                ;
                U64 _t1604 = 1;
                U64 _t1605 = U64_add(DEREF(pos), _t1604);
                ;
                *pos = _t1605;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1910 = 47;
        U64 _t1911 = 1;
        U64 _t1912 = U64_add(DEREF(pos), _t1911);
        ;
        Bool _t1913 = U8_eq(DEREF(c), _t1910);
        ;
        Bool _t1914; { Bool *_hp = U64_lt(&(U64){_t1912}, &(U64){src_len}); _t1914 = *_hp; free(_hp); }
        ;
        Bool _t1915 = Bool_and(_t1913, _t1914);
        ;
        ;
        if (_t1915) {
            U64 _t1666 = 1;
            U64 *_t1667 = malloc(sizeof(U64)); *_t1667 = U64_add(DEREF(pos), _t1666);
            ;
            U8 *c2 = Str_get(source, _t1667);
            U8 _t1668 = 47;
            Bool _t1669 = U8_eq(DEREF(c2), _t1668);
            ;
            if (_t1669) {
                while (1) {
                    Bool _wcond1606; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1606 = *_hp; free(_hp); }
                    if (_wcond1606) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1607 = Str_get(source, pos);
                    U8 _t1608 = 10;
                    Bool _t1609 = U8_eq(DEREF(_t1607), _t1608);
                    ;
                    if (_t1609) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1610 = 1;
                    U64 _t1611 = U64_add(DEREF(pos), _t1610);
                    ;
                    *pos = _t1611;
                    ;
                }
                U64_delete(_t1667, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1670 = 42;
            Bool _t1671 = U8_eq(DEREF(c2), _t1670);
            U64_delete(_t1667, &(Bool){1});
            ;
            if (_t1671) {
                U64 _t1662 = 2;
                U64 _t1663 = U64_add(DEREF(pos), _t1662);
                ;
                *pos = _t1663;
                ;
                I64 depth = 1;
                while (1) {
                    Bool _wcond1612; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1612 = *_hp; free(_hp); }
                    if (_wcond1612) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1637 = 0;
                    Bool _t1638; { Bool *_hp = I64_lte(&(I64){depth}, &(I64){_t1637}); _t1638 = *_hp; free(_hp); }
                    ;
                    if (_t1638) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1639 = 1;
                    U64 _t1640 = U64_add(DEREF(pos), _t1639);
                    ;
                    Bool _t1641; { Bool *_hp = U64_lt(&(U64){_t1640}, &(U64){src_len}); _t1641 = *_hp; free(_hp); }
                    ;
                    if (_t1641) {
                        U8 *b1 = Str_get(source, pos);
                        U64 _t1621 = 1;
                        U64 *_t1622 = malloc(sizeof(U64)); *_t1622 = U64_add(DEREF(pos), _t1621);
                        ;
                        U8 *b2 = Str_get(source, _t1622);
                        U8 _t1623 = 47;
                        U8 _t1624 = 42;
                        Bool _t1625 = U8_eq(DEREF(b1), _t1623);
                        ;
                        Bool _t1626 = U8_eq(DEREF(b2), _t1624);
                        ;
                        Bool _t1627 = Bool_and(_t1625, _t1626);
                        ;
                        ;
                        if (_t1627) {
                            I64 _t1613 = 1;
                            I64 _t1614 = I64_add(depth, _t1613);
                            ;
                            depth = _t1614;
                            ;
                            U64 _t1615 = 2;
                            U64 _t1616 = U64_add(DEREF(pos), _t1615);
                            ;
                            *pos = _t1616;
                            ;
                            U64_delete(_t1622, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1628 = 42;
                        U8 _t1629 = 47;
                        Bool _t1630 = U8_eq(DEREF(b1), _t1628);
                        ;
                        Bool _t1631 = U8_eq(DEREF(b2), _t1629);
                        U64_delete(_t1622, &(Bool){1});
                        ;
                        Bool _t1632 = Bool_and(_t1630, _t1631);
                        ;
                        ;
                        if (_t1632) {
                            I64 _t1617 = 1;
                            I64 _t1618 = I64_sub(depth, _t1617);
                            ;
                            depth = _t1618;
                            ;
                            U64 _t1619 = 2;
                            U64 _t1620 = U64_add(DEREF(pos), _t1619);
                            ;
                            *pos = _t1620;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1642 = Str_get(source, pos);
                    U8 _t1643 = 10;
                    Bool _t1644 = U8_eq(DEREF(_t1642), _t1643);
                    ;
                    if (_t1644) {
                        I64 _t1633 = 1;
                        I64 _t1634 = I64_add(line, _t1633);
                        ;
                        line = _t1634;
                        ;
                        U64 _t1635 = 1;
                        U64 _t1636 = U64_add(DEREF(pos), _t1635);
                        ;
                        line_start = _t1636;
                        ;
                    }
                    ;
                    U64 _t1645 = 1;
                    U64 _t1646 = U64_add(DEREF(pos), _t1645);
                    ;
                    *pos = _t1646;
                    ;
                }
                I64 _t1664 = 0;
                Bool _t1665; { Bool *_hp = I64_gt(&(I64){depth}, &(I64){_t1664}); _t1665 = *_hp; free(_hp); }
                ;
                ;
                if (_t1665) {
                    Str *_t1647 = Str_lit("Str", 3ULL);
                    U64 _t1648; { U64 *_hp = Str_size(); _t1648 = *_hp; free(_hp); }
                    U64 _t1649 = 6;
                    Array *_va20 = Array_new(_t1647, &(U64){_t1648}, &(U64){_t1649});
                    Str_delete(_t1647, &(Bool){1});
                    ;
                    ;
                    U64 _t1650 = 0;
                    Str *_t1651 = Str_clone(path);
                    Array_set(_va20, &(U64){_t1650}, _t1651);
                    ;
                    U64 _t1652 = 1;
                    Str *_t1653 = Str_lit(":", 1ULL);
                    Array_set(_va20, &(U64){_t1652}, _t1653);
                    ;
                    U64 _t1654 = 2;
                    Str *_t1655 = I64_to_str(&(I64){line});
                    Array_set(_va20, &(U64){_t1654}, _t1655);
                    ;
                    U64 _t1656 = 3;
                    Str *_t1657 = Str_lit(":", 1ULL);
                    Array_set(_va20, &(U64){_t1656}, _t1657);
                    ;
                    U64 _t1658 = 4;
                    Str *_t1659 = I64_to_str(&(I64){col});
                    Array_set(_va20, &(U64){_t1658}, _t1659);
                    ;
                    U64 _t1660 = 5;
                    Str *_t1661 = Str_lit(": error: unterminated comment", 29ULL);
                    Array_set(_va20, &(U64){_t1660}, _t1661);
                    ;
                    println(_va20);
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
        Bool _t1916; { Bool *_hp = is_digit(c); _t1916 = *_hp; free(_hp); }
        if (_t1916) {
            while (1) {
                Bool _wcond1672; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1672 = *_hp; free(_hp); }
                if (_wcond1672) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1673 = Str_get(source, pos);
                Bool _t1674; { Bool *_hp = is_digit(_t1673); _t1674 = *_hp; free(_hp); }
                Bool _t1675 = Bool_not(_t1674);
                ;
                if (_t1675) {
                    ;
                    break;
                }
                ;
                U64 _t1676 = 1;
                U64 _t1677 = U64_add(DEREF(pos), _t1676);
                ;
                *pos = _t1677;
                ;
            }
            U64 _t1694 = 1;
            U64 _t1695 = U64_add(DEREF(pos), _t1694);
            ;
            Bool _t1696; { Bool *_hp = U64_lt(&(U64){_t1695}, &(U64){src_len}); _t1696 = *_hp; free(_hp); }
            ;
            if (_t1696) {
                U8 *_t1686 = Str_get(source, pos);
                U8 _t1687 = 46;
                U64 _t1688 = 1;
                U64 *_t1689 = malloc(sizeof(U64)); *_t1689 = U64_add(DEREF(pos), _t1688);
                ;
                U8 *_t1690 = Str_get(source, _t1689);
                Bool _t1691 = U8_eq(DEREF(_t1686), _t1687);
                ;
                Bool _t1692; { Bool *_hp = is_digit(_t1690); _t1692 = *_hp; free(_hp); }
                U64_delete(_t1689, &(Bool){1});
                Bool _t1693 = Bool_and(_t1691, _t1692);
                ;
                ;
                if (_t1693) {
                    U64 _t1684 = 1;
                    U64 _t1685 = U64_add(DEREF(pos), _t1684);
                    ;
                    *pos = _t1685;
                    ;
                    while (1) {
                        Bool _wcond1678; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1678 = *_hp; free(_hp); }
                        if (_wcond1678) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1679 = Str_get(source, pos);
                        Bool _t1680; { Bool *_hp = is_digit(_t1679); _t1680 = *_hp; free(_hp); }
                        Bool _t1681 = Bool_not(_t1680);
                        ;
                        if (_t1681) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1682 = 1;
                        U64 _t1683 = U64_add(DEREF(pos), _t1682);
                        ;
                        *pos = _t1683;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1697 = U64_sub(DEREF(pos), start);
            I64 _t1698 = I64_clone(&(I64){col});
            Token *_t1699 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1699->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1697}); _t1699->text = *_ca; free(_ca); }
            _t1699->line = I64_clone(&(I64){line});
            _t1699->col = _t1698;
            ;
            ;
            Vec_push(tokens, _t1699);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1917; { Bool *_hp = is_alpha(c); _t1917 = *_hp; free(_hp); }
        if (_t1917) {
            while (1) {
                Bool _wcond1700; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1700 = *_hp; free(_hp); }
                if (_wcond1700) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1701 = Str_get(source, pos);
                Bool _t1702; { Bool *_hp = is_alnum(_t1701); _t1702 = *_hp; free(_hp); }
                Bool _t1703 = Bool_not(_t1702);
                ;
                if (_t1703) {
                    ;
                    break;
                }
                ;
                U64 _t1704 = 1;
                U64 _t1705 = U64_add(DEREF(pos), _t1704);
                ;
                *pos = _t1705;
                ;
            }
            U64 _t1706 = U64_sub(DEREF(pos), start);
            Str *word = Str_substr(source, &(U64){start}, &(U64){_t1706});
            ;
            TokenType *type = lookup_keyword(word);
            I64 _t1707 = I64_clone(&(I64){line});
            I64 _t1708 = I64_clone(&(I64){col});
            Token *_t1709 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1709->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1709->text = *_ca; free(_ca); }
            _t1709->line = _t1707;
            _t1709->col = _t1708;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1709);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1918 = 34;
        Bool _t1919 = U8_eq(DEREF(c), _t1918);
        ;
        if (_t1919) {
            U64 _t1759 = 1;
            U64 _t1760 = U64_add(DEREF(pos), _t1759);
            ;
            *pos = _t1760;
            ;
            while (1) {
                Bool _wcond1710; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1710 = *_hp; free(_hp); }
                if (_wcond1710) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1717 = Str_get(source, pos);
                U8 _t1718 = 34;
                Bool _t1719 = U8_eq(DEREF(_t1717), _t1718);
                ;
                if (_t1719) {
                    ;
                    break;
                }
                ;
                U8 *_t1720 = Str_get(source, pos);
                U8 _t1721 = 92;
                U64 _t1722 = 1;
                U64 _t1723 = U64_add(DEREF(pos), _t1722);
                ;
                Bool _t1724 = U8_eq(DEREF(_t1720), _t1721);
                ;
                Bool _t1725; { Bool *_hp = U64_lt(&(U64){_t1723}, &(U64){src_len}); _t1725 = *_hp; free(_hp); }
                ;
                Bool _t1726 = Bool_and(_t1724, _t1725);
                ;
                ;
                if (_t1726) {
                    U64 _t1711 = 1;
                    U64 _t1712 = U64_add(DEREF(pos), _t1711);
                    ;
                    *pos = _t1712;
                    ;
                }
                ;
                U8 *_t1727 = Str_get(source, pos);
                U8 _t1728 = 10;
                Bool _t1729 = U8_eq(DEREF(_t1727), _t1728);
                ;
                if (_t1729) {
                    I64 _t1713 = 1;
                    I64 _t1714 = I64_add(line, _t1713);
                    ;
                    line = _t1714;
                    ;
                    U64 _t1715 = 1;
                    U64 _t1716 = U64_add(DEREF(pos), _t1715);
                    ;
                    line_start = _t1716;
                    ;
                }
                ;
                U64 _t1730 = 1;
                U64 _t1731 = U64_add(DEREF(pos), _t1730);
                ;
                *pos = _t1731;
                ;
            }
            U8 *_t1761 = Str_get(source, pos);
            U8 _t1762 = 34;
            Bool _t1763; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1763 = *_hp; free(_hp); }
            Bool _t1764 = U8_eq(DEREF(_t1761), _t1762);
            ;
            Bool _t1765 = Bool_and(_t1763, _t1764);
            ;
            ;
            if (_t1765) {
                U64 _t1732 = 1;
                U64 _t1733 = U64_add(DEREF(pos), _t1732);
                ;
                *pos = _t1733;
                ;
                U64 _t1734 = 1;
                U64 _t1735 = U64_sub(DEREF(pos), start);
                U64 _t1736 = 2;
                U64 _t1737 = U64_add(start, _t1734);
                ;
                U64 _t1738 = U64_sub(_t1735, _t1736);
                ;
                ;
                I64 _t1739 = I64_clone(&(I64){col});
                Token *_t1740 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1740->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){_t1737}, &(U64){_t1738}); _t1740->text = *_ca; free(_ca); }
                _t1740->line = I64_clone(&(I64){line});
                _t1740->col = _t1739;
                ;
                ;
                ;
                Vec_push(tokens, _t1740);
            } else {
                Str *_t1741 = Str_lit("Str", 3ULL);
                U64 _t1742; { U64 *_hp = Str_size(); _t1742 = *_hp; free(_hp); }
                U64 _t1743 = 6;
                Array *_va21 = Array_new(_t1741, &(U64){_t1742}, &(U64){_t1743});
                Str_delete(_t1741, &(Bool){1});
                ;
                ;
                U64 _t1744 = 0;
                Str *_t1745 = Str_clone(path);
                Array_set(_va21, &(U64){_t1744}, _t1745);
                ;
                U64 _t1746 = 1;
                Str *_t1747 = Str_lit(":", 1ULL);
                Array_set(_va21, &(U64){_t1746}, _t1747);
                ;
                U64 _t1748 = 2;
                Str *_t1749 = I64_to_str(&(I64){line});
                Array_set(_va21, &(U64){_t1748}, _t1749);
                ;
                U64 _t1750 = 3;
                Str *_t1751 = Str_lit(":", 1ULL);
                Array_set(_va21, &(U64){_t1750}, _t1751);
                ;
                U64 _t1752 = 4;
                Str *_t1753 = I64_to_str(&(I64){col});
                Array_set(_va21, &(U64){_t1752}, _t1753);
                ;
                U64 _t1754 = 5;
                Str *_t1755 = Str_lit(": error: unterminated string", 28ULL);
                Array_set(_va21, &(U64){_t1754}, _t1755);
                ;
                println(_va21);
                U64 _t1756 = U64_sub(DEREF(pos), start);
                I64 _t1757 = I64_clone(&(I64){col});
                Token *_t1758 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1758->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1756}); _t1758->text = *_ca; free(_ca); }
                _t1758->line = I64_clone(&(I64){line});
                _t1758->col = _t1757;
                ;
                ;
                Vec_push(tokens, _t1758);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1920 = 39;
        Bool _t1921 = U8_eq(DEREF(c), _t1920);
        ;
        if (_t1921) {
            U64 _t1791 = 1;
            U64 _t1792 = U64_add(DEREF(pos), _t1791);
            ;
            *pos = _t1792;
            ;
            U64 ch_start = U64_clone(pos);
            U8 *_t1793 = Str_get(source, pos);
            U8 _t1794 = 92;
            U64 _t1795 = 1;
            U64 _t1796 = U64_add(DEREF(pos), _t1795);
            ;
            Bool _t1797 = U8_eq(DEREF(_t1793), _t1794);
            ;
            Bool _t1798; { Bool *_hp = U64_lt(&(U64){_t1796}, &(U64){src_len}); _t1798 = *_hp; free(_hp); }
            ;
            Bool _t1799; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1799 = *_hp; free(_hp); }
            Bool _t1800 = Bool_and(_t1797, _t1798);
            ;
            ;
            Bool _t1801 = Bool_and(_t1799, _t1800);
            ;
            ;
            if (_t1801) {
                U64 _t1766 = 1;
                U64 _t1767 = U64_add(DEREF(pos), _t1766);
                ;
                *pos = _t1767;
                ;
            }
            ;
            U64 _t1802 = 1;
            U64 _t1803 = U64_add(DEREF(pos), _t1802);
            ;
            *pos = _t1803;
            ;
            U8 *_t1804 = Str_get(source, pos);
            U8 _t1805 = 39;
            Bool _t1806; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1806 = *_hp; free(_hp); }
            Bool _t1807 = U8_eq(DEREF(_t1804), _t1805);
            ;
            Bool _t1808 = Bool_and(_t1806, _t1807);
            ;
            ;
            if (_t1808) {
                U64 _t1768 = U64_sub(DEREF(pos), ch_start);
                I64 _t1769 = I64_clone(&(I64){col});
                Token *_t1770 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1770->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){ch_start}, &(U64){_t1768}); _t1770->text = *_ca; free(_ca); }
                _t1770->line = I64_clone(&(I64){line});
                _t1770->col = _t1769;
                ;
                ;
                Vec_push(tokens, _t1770);
                U64 _t1771 = 1;
                U64 _t1772 = U64_add(DEREF(pos), _t1771);
                ;
                *pos = _t1772;
                ;
            } else {
                Str *_t1773 = Str_lit("Str", 3ULL);
                U64 _t1774; { U64 *_hp = Str_size(); _t1774 = *_hp; free(_hp); }
                U64 _t1775 = 6;
                Array *_va22 = Array_new(_t1773, &(U64){_t1774}, &(U64){_t1775});
                Str_delete(_t1773, &(Bool){1});
                ;
                ;
                U64 _t1776 = 0;
                Str *_t1777 = Str_clone(path);
                Array_set(_va22, &(U64){_t1776}, _t1777);
                ;
                U64 _t1778 = 1;
                Str *_t1779 = Str_lit(":", 1ULL);
                Array_set(_va22, &(U64){_t1778}, _t1779);
                ;
                U64 _t1780 = 2;
                Str *_t1781 = I64_to_str(&(I64){line});
                Array_set(_va22, &(U64){_t1780}, _t1781);
                ;
                U64 _t1782 = 3;
                Str *_t1783 = Str_lit(":", 1ULL);
                Array_set(_va22, &(U64){_t1782}, _t1783);
                ;
                U64 _t1784 = 4;
                Str *_t1785 = I64_to_str(&(I64){col});
                Array_set(_va22, &(U64){_t1784}, _t1785);
                ;
                U64 _t1786 = 5;
                Str *_t1787 = Str_lit(": error: unterminated character literal", 39ULL);
                Array_set(_va22, &(U64){_t1786}, _t1787);
                ;
                println(_va22);
                U64 _t1788 = U64_sub(DEREF(pos), start);
                I64 _t1789 = I64_clone(&(I64){col});
                Token *_t1790 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1790->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1788}); _t1790->text = *_ca; free(_ca); }
                _t1790->line = I64_clone(&(I64){line});
                _t1790->col = _t1789;
                ;
                ;
                Vec_push(tokens, _t1790);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t1922 = 1;
        U64 _t1923 = U64_add(DEREF(pos), _t1922);
        ;
        Bool _t1924; { Bool *_hp = U64_lt(&(U64){_t1923}, &(U64){src_len}); _t1924 = *_hp; free(_hp); }
        ;
        if (_t1924) {
            U64 _t1815 = 1;
            U64 *_t1816 = malloc(sizeof(U64)); *_t1816 = U64_add(DEREF(pos), _t1815);
            ;
            U8 *c2 = Str_get(source, _t1816);
            TokenType *two = TokenType_clone(TokenType_Eof());
            U8 _t1817 = 58;
            U8 _t1818 = 61;
            Bool _t1819 = U8_eq(DEREF(c), _t1817);
            ;
            Bool _t1820 = U8_eq(DEREF(c2), _t1818);
            ;
            Bool _t1821 = Bool_and(_t1819, _t1820);
            ;
            ;
            if (_t1821) {
                two = TokenType_clone(TokenType_ColonEq());
            }
            ;
            U8 _t1822 = 61;
            U8 _t1823 = 61;
            Bool _t1824 = U8_eq(DEREF(c), _t1822);
            ;
            Bool _t1825 = U8_eq(DEREF(c2), _t1823);
            ;
            Bool _t1826 = Bool_and(_t1824, _t1825);
            ;
            ;
            if (_t1826) {
                two = TokenType_clone(TokenType_EqEq());
            }
            ;
            U8 _t1827 = 33;
            U8 _t1828 = 61;
            Bool _t1829 = U8_eq(DEREF(c), _t1827);
            ;
            Bool _t1830 = U8_eq(DEREF(c2), _t1828);
            ;
            Bool _t1831 = Bool_and(_t1829, _t1830);
            ;
            ;
            if (_t1831) {
                two = TokenType_clone(TokenType_Neq());
            }
            ;
            U8 _t1832 = 60;
            U8 _t1833 = 61;
            Bool _t1834 = U8_eq(DEREF(c), _t1832);
            ;
            Bool _t1835 = U8_eq(DEREF(c2), _t1833);
            ;
            Bool _t1836 = Bool_and(_t1834, _t1835);
            ;
            ;
            if (_t1836) {
                two = TokenType_clone(TokenType_LtEq());
            }
            ;
            U8 _t1837 = 62;
            U8 _t1838 = 61;
            Bool _t1839 = U8_eq(DEREF(c), _t1837);
            ;
            Bool _t1840 = U8_eq(DEREF(c2), _t1838);
            ;
            Bool _t1841 = Bool_and(_t1839, _t1840);
            ;
            ;
            if (_t1841) {
                two = TokenType_clone(TokenType_GtEq());
            }
            ;
            U8 _t1842 = 46;
            U8 _t1843 = 46;
            Bool _t1844 = U8_eq(DEREF(c), _t1842);
            ;
            Bool _t1845 = U8_eq(DEREF(c2), _t1843);
            U64_delete(_t1816, &(Bool){1});
            ;
            Bool _t1846 = Bool_and(_t1844, _t1845);
            ;
            ;
            if (_t1846) {
                two = TokenType_clone(TokenType_DotDot());
            }
            ;
            Bool _t1847; { Bool *_hp = TokenType_eq(two, TokenType_Eof()); _t1847 = *_hp; free(_hp); }
            Bool _t1848 = Bool_not(_t1847);
            ;
            if (_t1848) {
                U64 _t1809 = 2;
                I64 _t1810 = I64_clone(&(I64){line});
                I64 _t1811 = I64_clone(&(I64){col});
                Token *_t1812 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1812->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1809}); _t1812->text = *_ca; free(_ca); }
                _t1812->line = _t1810;
                _t1812->col = _t1811;
                ;
                ;
                ;
                Vec_push(tokens, _t1812);
                U64 _t1813 = 2;
                U64 _t1814 = U64_add(DEREF(pos), _t1813);
                ;
                *pos = _t1814;
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
            U8 _sw1849 = U8_clone(c);
            U8 _t1884 = 40;
            Bool _t1885 = U8_eq(_sw1849, _t1884);
            ;
            if (_t1885) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1882 = 41;
                Bool _t1883 = U8_eq(_sw1849, _t1882);
                ;
                if (_t1883) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1880 = 123;
                    Bool _t1881 = U8_eq(_sw1849, _t1880);
                    ;
                    if (_t1881) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1878 = 125;
                        Bool _t1879 = U8_eq(_sw1849, _t1878);
                        ;
                        if (_t1879) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1876 = 91;
                            Bool _t1877 = U8_eq(_sw1849, _t1876);
                            ;
                            if (_t1877) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1874 = 93;
                                Bool _t1875 = U8_eq(_sw1849, _t1874);
                                ;
                                if (_t1875) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1872 = 44;
                                    Bool _t1873 = U8_eq(_sw1849, _t1872);
                                    ;
                                    if (_t1873) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1870 = 58;
                                        Bool _t1871 = U8_eq(_sw1849, _t1870);
                                        ;
                                        if (_t1871) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1868 = 46;
                                            Bool _t1869 = U8_eq(_sw1849, _t1868);
                                            ;
                                            if (_t1869) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1866 = 63;
                                                Bool _t1867 = U8_eq(_sw1849, _t1866);
                                                ;
                                                if (_t1867) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1864 = 33;
                                                    Bool _t1865 = U8_eq(_sw1849, _t1864);
                                                    ;
                                                    if (_t1865) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1862 = 43;
                                                        Bool _t1863 = U8_eq(_sw1849, _t1862);
                                                        ;
                                                        if (_t1863) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1860 = 45;
                                                            Bool _t1861 = U8_eq(_sw1849, _t1860);
                                                            ;
                                                            if (_t1861) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1858 = 42;
                                                                Bool _t1859 = U8_eq(_sw1849, _t1858);
                                                                ;
                                                                if (_t1859) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1856 = 47;
                                                                    Bool _t1857 = U8_eq(_sw1849, _t1856);
                                                                    ;
                                                                    if (_t1857) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1854 = 61;
                                                                        Bool _t1855 = U8_eq(_sw1849, _t1854);
                                                                        ;
                                                                        if (_t1855) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1852 = 60;
                                                                            Bool _t1853 = U8_eq(_sw1849, _t1852);
                                                                            ;
                                                                            if (_t1853) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1850 = 62;
                                                                                Bool _t1851 = U8_eq(_sw1849, _t1850);
                                                                                ;
                                                                                if (_t1851) {
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
        Bool _t1925; { Bool *_hp = TokenType_eq(single, TokenType_Eof()); _t1925 = *_hp; free(_hp); }
        Bool _t1926 = Bool_not(_t1925);
        ;
        if (_t1926) {
            U64 _t1886 = 1;
            I64 _t1887 = I64_clone(&(I64){line});
            I64 _t1888 = I64_clone(&(I64){col});
            Token *_t1889 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1889->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1886}); _t1889->text = *_ca; free(_ca); }
            _t1889->line = _t1887;
            _t1889->col = _t1888;
            ;
            ;
            ;
            Vec_push(tokens, _t1889);
            U64 _t1890 = 1;
            U64 _t1891 = U64_add(DEREF(pos), _t1890);
            ;
            *pos = _t1891;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t1927 = Str_lit("Str", 3ULL);
        U64 _t1928; { U64 *_hp = Str_size(); _t1928 = *_hp; free(_hp); }
        U64 _t1929 = 6;
        Array *_va23 = Array_new(_t1927, &(U64){_t1928}, &(U64){_t1929});
        Str_delete(_t1927, &(Bool){1});
        ;
        ;
        U64 _t1930 = 0;
        Str *_t1931 = Str_clone(path);
        Array_set(_va23, &(U64){_t1930}, _t1931);
        ;
        U64 _t1932 = 1;
        Str *_t1933 = Str_lit(":", 1ULL);
        Array_set(_va23, &(U64){_t1932}, _t1933);
        ;
        U64 _t1934 = 2;
        Str *_t1935 = I64_to_str(&(I64){line});
        Array_set(_va23, &(U64){_t1934}, _t1935);
        ;
        U64 _t1936 = 3;
        Str *_t1937 = Str_lit(":", 1ULL);
        Array_set(_va23, &(U64){_t1936}, _t1937);
        ;
        U64 _t1938 = 4;
        Str *_t1939 = I64_to_str(&(I64){col});
        Array_set(_va23, &(U64){_t1938}, _t1939);
        ;
        U64 _t1940 = 5;
        Str *_t1941 = Str_lit(": error: unexpected character", 29ULL);
        Array_set(_va23, &(U64){_t1940}, _t1941);
        ;
        println(_va23);
        U64 _t1942 = 1;
        I64 _t1943 = I64_clone(&(I64){col});
        ;
        Token *_t1944 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1944->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1942}); _t1944->text = *_ca; free(_ca); }
        _t1944->line = I64_clone(&(I64){line});
        _t1944->col = _t1943;
        ;
        ;
        ;
        Vec_push(tokens, _t1944);
        U64 _t1945 = 1;
        U64 _t1946 = U64_add(DEREF(pos), _t1945);
        ;
        *pos = _t1946;
        ;
    }
    ;
    U64 _t1949 = U64_sub(DEREF(pos), line_start);
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t1950 = 1;
    U64 _t1951 = U64_add(_t1949, _t1950);
    ;
    ;
    I64 col = U64_to_i64(_t1951);
    ;
    I64 _t1952 = I64_clone(&(I64){col});
    ;
    Token *_t1953 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t1953->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1953->text = *_ca; free(_ca); }
    _t1953->line = I64_clone(&(I64){line});
    _t1953->col = _t1952;
    ;
    ;
    Vec_push(tokens, _t1953);
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
    _t1954 = malloc(sizeof(I64));
    *_t1954 = 0;
    _t1955 = malloc(sizeof(I64));
    *_t1955 = 1;
    _t1956 = malloc(sizeof(I64)); *_t1956 = I64_sub(DEREF(_t1954), DEREF(_t1955));
    CAP_LIT = U64_from_i64(_t1956);
    _t1957 = malloc(sizeof(I64));
    *_t1957 = 0;
    _t1958 = malloc(sizeof(I64));
    *_t1958 = 2;
    _t1959 = malloc(sizeof(I64)); *_t1959 = I64_sub(DEREF(_t1957), DEREF(_t1958));
    CAP_VIEW = U64_from_i64(_t1959);
}

