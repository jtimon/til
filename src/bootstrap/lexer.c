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

static I64 *_t1967;
static I64 *_t1968;
static I64 *_t1969;
static U64 *CAP_LIT;
static I64 *_t1970;
static I64 *_t1971;
static I64 *_t1972;
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

static __attribute__((unused)) I32 * I32_from_i64(I64 * val) {
    I64 _t56 = 2147483648;
    I64 _t57; { I64 *_hp = I64_neg(&(I64){_t56}); _t57 = *_hp; free(_hp); }
    ;
    I64 _t58 = 2147483647;
    Bool _t59; { Bool *_hp = I64_lt(val, &(I64){_t57}); _t59 = *_hp; free(_hp); }
    ;
    Bool _t60; { Bool *_hp = I64_gt(val, &(I64){_t58}); _t60 = *_hp; free(_hp); }
    ;
    Bool _t61 = Bool_or(_t59, _t60);
    ;
    ;
    if (_t61) {
        Str *_t50 = Str_lit("Str", 3ULL);
        U64 _t51; { U64 *_hp = Str_size(); _t51 = *_hp; free(_hp); }
        U64 _t52 = 1;
        Array *_va0 = Array_new(_t50, &(U64){_t51}, &(U64){_t52});
        Str_delete(_t50, &(Bool){1});
        ;
        ;
        U64 _t53 = 0;
        Str *_t54 = Str_lit("value out of range (-2147483648 to 2147483647)", 46ULL);
        Array_set(_va0, &(U64){_t53}, _t54);
        ;
        Str *_t55 = Str_lit("I32.from_i64", 12ULL);
        panic(_t55, _va0);
        Str_delete(_t55, &(Bool){1});
        Array_delete(_va0, &(Bool){1});
    }
    ;
    /* TODO: nested func I32_from_i64_ext */
    I32 _t62 = I32_from_i64_ext(val);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t62; return _r; }
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    I64 _t63 = 0;
    I64 _t64 = I32_to_i64(DEREF(a));
    I64 _t65 = I64_sub(_t63, _t64);
    ;
    ;
    I32 _t66; { I32 *_hp = I32_from_i64(&(I64){_t65}); _t66 = *_hp; free(_hp); }
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t66; return _r; }
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    I64 _t71 = I32_to_i64(DEREF(a));
    I64 _t72 = 0;
    Bool _t73; { Bool *_hp = I64_lt(&(I64){_t71}, &(I64){_t72}); _t73 = *_hp; free(_hp); }
    ;
    ;
    if (_t73) {
        I64 _t67 = 0;
        I64 _t68 = I32_to_i64(DEREF(a));
        I64 _t69 = I64_sub(_t67, _t68);
        ;
        ;
        I32 _t70; { I32 *_hp = I32_from_i64(&(I64){_t69}); _t70 = *_hp; free(_hp); }
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t70; return _r; }
    }
    ;
    I32 _t74 = I32_clone(a);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t74; return _r; }
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    I64 _t76 = 0;
    I64 _t77 = 1;
    I64 _t78 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t79 = I64_sub(_t76, _t77);
    ;
    ;
    Bool _t80 = I64_eq(_t78, _t79);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t80; return _r; }
}

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    I64 _t81 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t82 = 1;
    Bool _t83 = I64_eq(_t81, _t82);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t83; return _r; }
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    Bool _t84 = I32_eq(DEREF(a), DEREF(b));
    Bool _t85 = Bool_not(_t84);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t85; return _r; }
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    Bool _t86; { Bool *_hp = I32_gt(a, b); _t86 = *_hp; free(_hp); }
    Bool _t87 = Bool_not(_t86);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t87; return _r; }
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    Bool _t88; { Bool *_hp = I32_lt(a, b); _t88 = *_hp; free(_hp); }
    Bool _t89 = Bool_not(_t88);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t89; return _r; }
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 _t90 = F32_from_i64_ext(val);
    { F32 *_r = malloc(sizeof(F32)); *_r = _t90; return _r; }
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    I64 _t92 = 0;
    I64 _t93 = 1;
    I64 _t94 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t95 = I64_sub(_t92, _t93);
    ;
    ;
    Bool _t96 = I64_eq(_t94, _t95);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t96; return _r; }
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    I64 _t97 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t98 = 1;
    Bool _t99 = I64_eq(_t97, _t98);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t99; return _r; }
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    Bool _t100 = F32_eq(DEREF(a), DEREF(b));
    Bool _t101 = Bool_not(_t100);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t101; return _r; }
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    Bool _t102; { Bool *_hp = F32_gt(a, b); _t102 = *_hp; free(_hp); }
    Bool _t103 = Bool_not(_t102);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t103; return _r; }
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    Bool _t104; { Bool *_hp = F32_lt(a, b); _t104 = *_hp; free(_hp); }
    Bool _t105 = Bool_not(_t104);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t105; return _r; }
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    I64 _t106 = U32_to_i64(DEREF(val));
    Str *_t107 = I64_to_str(&(I64){_t106});
    ;
    return _t107;
}

static __attribute__((unused)) U32 * U32_from_i64(I64 * val) {
    I64 _t114 = 0;
    I64 _t115 = 4294967295;
    Bool _t116; { Bool *_hp = I64_lt(val, &(I64){_t114}); _t116 = *_hp; free(_hp); }
    ;
    Bool _t117; { Bool *_hp = I64_gt(val, &(I64){_t115}); _t117 = *_hp; free(_hp); }
    ;
    Bool _t118 = Bool_or(_t116, _t117);
    ;
    ;
    if (_t118) {
        Str *_t108 = Str_lit("Str", 3ULL);
        U64 _t109; { U64 *_hp = Str_size(); _t109 = *_hp; free(_hp); }
        U64 _t110 = 1;
        Array *_va1 = Array_new(_t108, &(U64){_t109}, &(U64){_t110});
        Str_delete(_t108, &(Bool){1});
        ;
        ;
        U64 _t111 = 0;
        Str *_t112 = Str_lit("value out of range (0-4294967295)", 33ULL);
        Array_set(_va1, &(U64){_t111}, _t112);
        ;
        Str *_t113 = Str_lit("U32.from_i64", 12ULL);
        panic(_t113, _va1);
        Str_delete(_t113, &(Bool){1});
        Array_delete(_va1, &(Bool){1});
    }
    ;
    /* TODO: nested func U32_from_i64_ext */
    U32 _t119 = U32_from_i64_ext(val);
    { U32 *_r = malloc(sizeof(U32)); *_r = _t119; return _r; }
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    I64 _t121 = 0;
    I64 _t122 = 1;
    I64 _t123 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t124 = I64_sub(_t121, _t122);
    ;
    ;
    Bool _t125 = I64_eq(_t123, _t124);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t125; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    I64 _t126 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t127 = 1;
    Bool _t128 = I64_eq(_t126, _t127);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t128; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    Bool _t129 = U32_eq(DEREF(a), DEREF(b));
    Bool _t130 = Bool_not(_t129);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t130; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    Bool _t131; { Bool *_hp = U32_gt(a, b); _t131 = *_hp; free(_hp); }
    Bool _t132 = Bool_not(_t131);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t132; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    Bool _t133; { Bool *_hp = U32_lt(a, b); _t133 = *_hp; free(_hp); }
    Bool _t134 = Bool_not(_t133);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t134; return _r; }
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t135 = U64_to_str_ext(val);
    return _t135;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 _t136 = U64_from_i64_ext(val);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t136; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    I64 _t138 = 0;
    I64 _t139 = 1;
    I64 _t140 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t141 = I64_sub(_t138, _t139);
    ;
    ;
    Bool _t142 = I64_eq(_t140, _t141);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t142; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    I64 _t143 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t144 = 1;
    Bool _t145 = I64_eq(_t143, _t144);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t145; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    Bool _t146 = U64_eq(DEREF(a), DEREF(b));
    Bool _t147 = Bool_not(_t146);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t147; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    Bool _t148; { Bool *_hp = U64_gt(a, b); _t148 = *_hp; free(_hp); }
    Bool _t149 = Bool_not(_t148);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t149; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    Bool _t150; { Bool *_hp = U64_lt(a, b); _t150 = *_hp; free(_hp); }
    Bool _t151 = Bool_not(_t150);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t151; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    I64 _t188 = 0;
    Bool _t189 = I64_eq(DEREF(val), _t188);
    ;
    if (_t189) {
        U64 _t152 = 2;
        U8 *buf = malloc(_t152);
        ;
        I64 _t153 = 48;
        U64 _t154 = 1;
        memcpy(buf, &(I64){_t153}, _t154);
        ;
        ;
        U64 *_t155 = malloc(sizeof(U64));
        *_t155 = 1;
        void *_t156 = ptr_add(buf, DEREF(_t155));
        I64 _t157 = 0;
        U64 _t158 = 1;
        memcpy(_t156, &(I64){_t157}, _t158);
        U64_delete(_t155, &(Bool){1});
        ;
        ;
        I64 _t159 = 1;
        I64 _t160 = 1;
        Str *_t161 = malloc(sizeof(Str));
        _t161->c_str = buf;
        _t161->count = _t159;
        _t161->cap = _t160;
        ;
        ;
        ;
        return _t161;
    }
    ;
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 _t190 = 0;
    Bool _t191; { Bool *_hp = I64_lt(val, &(I64){_t190}); _t191 = *_hp; free(_hp); }
    ;
    if (_t191) {
        Bool _t162 = 1;
        is_neg = _t162;
        ;
        I64 _t163 = 0;
        I64 _t164 = I64_sub(_t163, DEREF(val));
        ;
        v = _t164;
        ;
    }
    ;
    U64 ndigits = 0;
    I64 tmp = I64_clone(&(I64){v});
    while (1) {
        I64 _t166 = 0;
        Bool _wcond165; { Bool *_hp = I64_gt(&(I64){tmp}, &(I64){_t166}); _wcond165 = *_hp; free(_hp); }
        ;
        if (_wcond165) {
        } else {
            ;
            break;
        }
        ;
        U64 _t167 = 1;
        U64 _t168 = U64_add(ndigits, _t167);
        ;
        ndigits = _t168;
        ;
        I64 _t169 = 10;
        I64 _t170 = I64_div(tmp, _t169);
        ;
        tmp = _t170;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    ;
    if (is_neg) {
        U64 _t171 = 1;
        U64 _t172 = U64_add(DEREF(total), _t171);
        ;
        *total = _t172;
        ;
    }
    U64 _t192 = 1;
    U64 _t193 = U64_add(DEREF(total), _t192);
    ;
    U8 *buf = malloc(_t193);
    ;
    if (is_neg) {
        I64 _t173 = 45;
        U64 _t174 = 1;
        memcpy(buf, &(I64){_t173}, _t174);
        ;
        ;
    }
    ;
    U64 _t194 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t194);
    ;
    while (1) {
        I64 _t176 = 0;
        Bool _wcond175; { Bool *_hp = I64_gt(&(I64){v}, &(I64){_t176}); _wcond175 = *_hp; free(_hp); }
        ;
        if (_wcond175) {
        } else {
            ;
            break;
        }
        ;
        I64 _t177 = 10;
        I64 _t178 = I64_mod(v, _t177);
        ;
        I64 _t179 = 48;
        I64 _t180 = I64_add(_t178, _t179);
        ;
        ;
        void *_t181 = ptr_add(buf, DEREF(i));
        U8 _t182 = I64_to_u8(_t180);
        ;
        U64 _t183 = 1;
        memcpy(_t181, &(U8){_t182}, _t183);
        ;
        ;
        I64 _t184 = 10;
        I64 _t185 = I64_div(v, _t184);
        ;
        v = _t185;
        ;
        U64 _t186 = 1;
        U64 _t187 = U64_sub(DEREF(i), _t186);
        ;
        *i = _t187;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t195 = ptr_add(buf, DEREF(total));
    I64 _t196 = 0;
    U64 _t197 = 1;
    memcpy(_t195, &(I64){_t196}, _t197);
    ;
    ;
    U64 _t198 = U64_clone(total);
    U64 _t199 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t200 = malloc(sizeof(Str));
    _t200->c_str = buf;
    _t200->count = _t198;
    _t200->cap = _t199;
    ;
    ;
    return _t200;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    I64 _t201 = 0;
    I64 _t202 = I64_sub(_t201, DEREF(a));
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t202; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    I64 _t205 = 0;
    Bool _t206; { Bool *_hp = I64_lt(a, &(I64){_t205}); _t206 = *_hp; free(_hp); }
    ;
    if (_t206) {
        I64 _t203 = 0;
        I64 _t204 = I64_sub(_t203, DEREF(a));
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t204; return _r; }
    }
    ;
    I64 _t207 = I64_clone(a);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t207; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    I64 _t209 = 0;
    I64 _t210 = 1;
    I64 _t211 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t212 = I64_sub(_t209, _t210);
    ;
    ;
    Bool _t213 = I64_eq(_t211, _t212);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t213; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    I64 _t214 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t215 = 1;
    Bool _t216 = I64_eq(_t214, _t215);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t216; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    Bool _t217 = I64_eq(DEREF(a), DEREF(b));
    Bool _t218 = Bool_not(_t217);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t218; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    Bool _t219; { Bool *_hp = I64_gt(a, b); _t219 = *_hp; free(_hp); }
    Bool _t220 = Bool_not(_t219);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t220; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    Bool _t221; { Bool *_hp = I64_lt(a, b); _t221 = *_hp; free(_hp); }
    Bool _t222 = Bool_not(_t221);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t222; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    U64 _t223 = U64_clone(&(U64){start});
    U64 _t224 = U64_clone(&(U64){end});
    Range *_t225 = malloc(sizeof(Range));
    _t225->start = _t223;
    _t225->end = _t224;
    ;
    ;
    return _t225;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t227; { Bool *_hp = U64_lte(&self->start, &self->end); _t227 = *_hp; free(_hp); }
    if (_t227) {
        U64 _t226 = U64_sub(self->end, self->start);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t226; return _r; }
    }
    ;
    U64 _t228 = U64_sub(self->start, self->end);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t228; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    Bool _t230; { Bool *_hp = U64_lte(&self->start, &self->end); _t230 = *_hp; free(_hp); }
    if (_t230) {
        U64 _t229 = U64_add(self->start, i);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t229; return _r; }
    }
    ;
    U64 _t231 = U64_sub(self->start, i);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t231; return _r; }
}

Range * Range_clone(Range * val) {
    Range *_t232 = malloc(sizeof(Range));
    _t232->start = val->start;
    _t232->end = val->end;
    return _t232;
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
        Str *_t234 = Str_lit("true", 4ULL);
        return _t234;
    } else {
        Str *_t235 = Str_lit("false", 5ULL);
        return _t235;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool _t240 = Bool_eq(DEREF(a), DEREF(b));
    if (_t240) {
        I64 _t236 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t236; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t237 = 0;
        I64 _t238 = 1;
        I64 _t239 = I64_sub(_t237, _t238);
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t239; return _r; }
    }
    I64 _t241 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t241; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    I64 _t243 = 0;
    I64 _t244 = 1;
    I64 _t245; { I64 *_hp = Bool_cmp(a, b); _t245 = *_hp; free(_hp); }
    I64 _t246 = I64_sub(_t243, _t244);
    ;
    ;
    Bool _t247 = I64_eq(_t245, _t246);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t247; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    I64 _t248; { I64 *_hp = Bool_cmp(a, b); _t248 = *_hp; free(_hp); }
    I64 _t249 = 1;
    Bool _t250 = I64_eq(_t248, _t249);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t250; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    Bool _t251 = Bool_eq(DEREF(a), DEREF(b));
    Bool _t252 = Bool_not(_t251);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t252; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    Bool _t253; { Bool *_hp = Bool_gt(a, b); _t253 = *_hp; free(_hp); }
    Bool _t254 = Bool_not(_t253);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t254; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    Bool _t255; { Bool *_hp = Bool_lt(a, b); _t255 = *_hp; free(_hp); }
    Bool _t256 = Bool_not(_t255);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t256; return _r; }
}

void println(Array * parts) {
    {
        U64 *_fi257 = malloc(sizeof(U64));
        *_fi257 = 0;
        while (1) {
            U64 _t259; { U64 *_hp = Array_len(parts); _t259 = *_hp; free(_hp); }
            Bool _wcond258; { Bool *_hp = U64_lt(_fi257, &(U64){_t259}); _wcond258 = *_hp; free(_hp); }
            ;
            if (_wcond258) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi257);
            U64 _t260 = 1;
            U64 _t261 = U64_add(DEREF(_fi257), _t260);
            ;
            *_fi257 = _t261;
            ;
            print_single(s);
        }
        U64_delete(_fi257, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        U64 *_fi262 = malloc(sizeof(U64));
        *_fi262 = 0;
        while (1) {
            U64 _t264; { U64 *_hp = Array_len(parts); _t264 = *_hp; free(_hp); }
            Bool _wcond263; { Bool *_hp = U64_lt(_fi262, &(U64){_t264}); _wcond263 = *_hp; free(_hp); }
            ;
            if (_wcond263) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi262);
            U64 _t265 = 1;
            U64 _t266 = U64_add(DEREF(_fi262), _t265);
            ;
            *_fi262 = _t266;
            ;
            print_single(s);
        }
        U64_delete(_fi262, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 total = 0;
    {
        U64 *_fi267 = malloc(sizeof(U64));
        *_fi267 = 0;
        while (1) {
            U64 _t269; { U64 *_hp = Array_len(parts); _t269 = *_hp; free(_hp); }
            Bool _wcond268; { Bool *_hp = U64_lt(_fi267, &(U64){_t269}); _wcond268 = *_hp; free(_hp); }
            ;
            if (_wcond268) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi267);
            U64 _t270 = 1;
            U64 _t271 = U64_add(DEREF(_fi267), _t270);
            ;
            *_fi267 = _t271;
            ;
            U64 _t272; { U64 *_hp = Str_len(s); _t272 = *_hp; free(_hp); }
            U64 _t273 = U64_add(total, _t272);
            ;
            total = _t273;
            ;
        }
        U64_delete(_fi267, &(Bool){1});
    }
    U8 *buf = malloc(total);
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi274 = malloc(sizeof(U64));
        *_fi274 = 0;
        while (1) {
            U64 _t276; { U64 *_hp = Array_len(parts); _t276 = *_hp; free(_hp); }
            Bool _wcond275; { Bool *_hp = U64_lt(_fi274, &(U64){_t276}); _wcond275 = *_hp; free(_hp); }
            ;
            if (_wcond275) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi274);
            U64 _t277 = 1;
            U64 _t278 = U64_add(DEREF(_fi274), _t277);
            ;
            *_fi274 = _t278;
            ;
            void *_t279 = ptr_add(buf, DEREF(offset));
            U64 _t280; { U64 *_hp = Str_len(s); _t280 = *_hp; free(_hp); }
            memcpy(_t279, s->c_str, _t280);
            ;
            U64 _t281; { U64 *_hp = Str_len(s); _t281 = *_hp; free(_hp); }
            U64 _t282 = U64_add(DEREF(offset), _t281);
            ;
            *offset = _t282;
            ;
        }
        U64_delete(_fi274, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t283 = U64_clone(&(U64){total});
    U64 _t284 = U64_clone(&(U64){total});
    ;
    Str *_t285 = malloc(sizeof(Str));
    _t285->c_str = buf;
    _t285->count = _t283;
    _t285->cap = _t284;
    ;
    ;
    return _t285;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        I64 _t286 = 0;
        I64 _t287 = 1;
        I64 _t288 = I64_sub(_t286, _t287);
        ;
        ;
        Bool _t289; { Bool *_hp = I64_neq(&(I64){status}, &(I64){_t288}); _t289 = *_hp; free(_hp); }
        ;
        if (_t289) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t290 = 50;
        sleep_ms(_t290);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t296; { U64 *_hp = Array_len(args); _t296 = *_hp; free(_hp); }
        Bool _wcond291; { Bool *_hp = U64_lt(i, &(U64){_t296}); _wcond291 = *_hp; free(_hp); }
        ;
        if (_wcond291) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        U64 _t297 = 0;
        Bool _t298; { Bool *_hp = U64_gt(i, &(U64){_t297}); _t298 = *_hp; free(_hp); }
        ;
        if (_t298) {
            Str *_t292 = Str_lit(" '", 2ULL);
            Str *_t293 = Str_concat(cmd, _t292);
            Str_delete(_t292, &(Bool){1});
            Str *_t294 = Str_concat(_t293, arg);
            Str_delete(_t293, &(Bool){1});
            Str *_t295 = Str_lit("'", 1ULL);
            cmd = Str_concat(_t294, _t295);
            Str_delete(_t294, &(Bool){1});
            Str_delete(_t295, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t299 = 1;
        U64 _t300 = U64_add(DEREF(i), _t299);
        ;
        *i = _t300;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    Str *_t301 = Str_lit(" > ", 3ULL);
    Str *_t302 = Str_concat(cmd, _t301);
    Str_delete(_t301, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t303 = Str_concat(_t302, tmpf);
    Str_delete(_t302, &(Bool){1});
    Str *_t304 = Str_lit(" 2>&1", 5ULL);
    Str *_t305 = Str_concat(_t303, _t304);
    Str_delete(_t303, &(Bool){1});
    Str_delete(_t304, &(Bool){1});
    I64 pid; { I64 *_hp = spawn_cmd(_t305); pid = *_hp; free(_hp); }
    Str_delete(_t305, &(Bool){1});
    I64 ec; { I64 *_hp = wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    ;
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 _t306; { U64 *_hp = Str_size(); _t306 = *_hp; free(_hp); }
    memcpy(output, content, _t306);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    Str *_t307 = Str_lit("Str", 3ULL);
    U64 _t308; { U64 *_hp = Str_size(); _t308 = *_hp; free(_hp); }
    U64 _t309 = 3;
    Array *_va2 = Array_new(_t307, &(U64){_t308}, &(U64){_t309});
    Str_delete(_t307, &(Bool){1});
    ;
    ;
    U64 _t310 = 0;
    Str *_t311 = Str_clone(loc_str);
    Array_set(_va2, &(U64){_t310}, _t311);
    ;
    U64 _t312 = 1;
    Str *_t313 = Str_lit(": panic: ", 9ULL);
    Array_set(_va2, &(U64){_t312}, _t313);
    ;
    U64 _t314 = 2;
    Str *_t315 = format(parts);
    Array_set(_va2, &(U64){_t314}, _t315);
    ;
    println(_va2);
    I64 _t316 = 1;
    exit(_t316);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t317 = Str_lit("Str", 3ULL);
    U64 _t318; { U64 *_hp = Str_size(); _t318 = *_hp; free(_hp); }
    U64 _t319 = 2;
    Array *_va3 = Array_new(_t317, &(U64){_t318}, &(U64){_t319});
    Str_delete(_t317, &(Bool){1});
    ;
    ;
    U64 _t320 = 0;
    Str *_t321 = Str_lit("TODO: ", 6ULL);
    Array_set(_va3, &(U64){_t320}, _t321);
    ;
    U64 _t322 = 1;
    Str *_t323 = format(parts);
    Array_set(_va3, &(U64){_t322}, _t323);
    ;
    panic(loc_str, _va3);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t324 = Str_lit("Str", 3ULL);
    U64 _t325; { U64 *_hp = Str_size(); _t325 = *_hp; free(_hp); }
    U64 _t326 = 1;
    Array *_va4 = Array_new(_t324, &(U64){_t325}, &(U64){_t326});
    Str_delete(_t324, &(Bool){1});
    ;
    ;
    U64 _t327 = 0;
    Str *_t328 = Str_lit("unreachable", 11ULL);
    Array_set(_va4, &(U64){_t327}, _t328);
    ;
    panic(loc_str, _va4);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool _t336 = Bool_not(DEREF(cond));
    if (_t336) {
        Str *_t329 = Str_lit("Str", 3ULL);
        U64 _t330; { U64 *_hp = Str_size(); _t330 = *_hp; free(_hp); }
        U64 _t331 = 2;
        Array *_va5 = Array_new(_t329, &(U64){_t330}, &(U64){_t331});
        Str_delete(_t329, &(Bool){1});
        ;
        ;
        U64 _t332 = 0;
        Str *_t333 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va5, &(U64){_t332}, _t333);
        ;
        U64 _t334 = 1;
        Str *_t335 = format(parts);
        Array_set(_va5, &(U64){_t334}, _t335);
        ;
        panic(loc_str, _va5);
    }
    ;
    Bool _t337 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t337; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t338 = Str_lit("Str", 3ULL);
    U64 _t339; { U64 *_hp = Str_size(); _t339 = *_hp; free(_hp); }
    U64 _t340 = 0;
    Array *_va6 = Array_new(_t338, &(U64){_t339}, &(U64){_t340});
    Str_delete(_t338, &(Bool){1});
    ;
    ;
    Bool _t341; { Bool *_hp = assertm(loc_str, cond, _va6); _t341 = *_hp; free(_hp); }
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t341; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t342 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool _t343; { Bool *_hp = assertm(loc_str, cond, _t342); _t343 = *_hp; free(_hp); }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool _t357; { Bool *_hp = I64_neq(a, b); _t357 = *_hp; free(_hp); }
    if (_t357) {
        Str *_t344 = Str_lit("Str", 3ULL);
        U64 _t345; { U64 *_hp = Str_size(); _t345 = *_hp; free(_hp); }
        U64 _t346 = 5;
        Array *_va7 = Array_new(_t344, &(U64){_t345}, &(U64){_t346});
        Str_delete(_t344, &(Bool){1});
        ;
        ;
        U64 _t347 = 0;
        Str *_t348 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va7, &(U64){_t347}, _t348);
        ;
        U64 _t349 = 1;
        Str *_t350 = I64_to_str(a);
        Array_set(_va7, &(U64){_t349}, _t350);
        ;
        U64 _t351 = 2;
        Str *_t352 = Str_lit("', found '", 10ULL);
        Array_set(_va7, &(U64){_t351}, _t352);
        ;
        U64 _t353 = 3;
        Str *_t354 = I64_to_str(b);
        Array_set(_va7, &(U64){_t353}, _t354);
        ;
        U64 _t355 = 4;
        Str *_t356 = Str_lit("'", 1ULL);
        Array_set(_va7, &(U64){_t355}, _t356);
        ;
        panic(loc_str, _va7);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool _t371; { Bool *_hp = Str_eq(a, b); _t371 = *_hp; free(_hp); }
    Bool _t372 = Bool_not(_t371);
    ;
    if (_t372) {
        Str *_t358 = Str_lit("Str", 3ULL);
        U64 _t359; { U64 *_hp = Str_size(); _t359 = *_hp; free(_hp); }
        U64 _t360 = 5;
        Array *_va8 = Array_new(_t358, &(U64){_t359}, &(U64){_t360});
        Str_delete(_t358, &(Bool){1});
        ;
        ;
        U64 _t361 = 0;
        Str *_t362 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va8, &(U64){_t361}, _t362);
        ;
        U64 _t363 = 1;
        Str *_t364 = Str_clone(a);
        Array_set(_va8, &(U64){_t363}, _t364);
        ;
        U64 _t365 = 2;
        Str *_t366 = Str_lit("', found '", 10ULL);
        Array_set(_va8, &(U64){_t365}, _t366);
        ;
        U64 _t367 = 3;
        Str *_t368 = Str_clone(b);
        Array_set(_va8, &(U64){_t367}, _t368);
        ;
        U64 _t369 = 4;
        Str *_t370 = Str_lit("'", 1ULL);
        Array_set(_va8, &(U64){_t369}, _t370);
        ;
        panic(loc_str, _va8);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    void *_t373 = calloc(DEREF(cap), DEREF(elem_size));
    U64 _t374 = U64_clone(cap);
    U64 _t375 = U64_clone(elem_size);
    Array *_t376 = malloc(sizeof(Array));
    _t376->data = _t373;
    _t376->cap = _t374;
    _t376->elem_size = _t375;
    { Str *_ca = Str_clone(elem_type); _t376->elem_type = *_ca; free(_ca); }
    ;
    ;
    return _t376;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    Bool _t391; { Bool *_hp = U64_gte(i, &self->cap); _t391 = *_hp; free(_hp); }
    if (_t391) {
        Str *_t377 = Str_lit("Str", 3ULL);
        U64 _t378; { U64 *_hp = Str_size(); _t378 = *_hp; free(_hp); }
        U64 _t379 = 5;
        Array *_va9 = Array_new(_t377, &(U64){_t378}, &(U64){_t379});
        Str_delete(_t377, &(Bool){1});
        ;
        ;
        U64 _t380 = 0;
        Str *_t381 = Str_lit("index ", 6ULL);
        Array_set(_va9, &(U64){_t380}, _t381);
        ;
        U64 _t382 = 1;
        Str *_t383 = U64_to_str(DEREF(i));
        Array_set(_va9, &(U64){_t382}, _t383);
        ;
        U64 _t384 = 2;
        Str *_t385 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va9, &(U64){_t384}, _t385);
        ;
        U64 _t386 = 3;
        Str *_t387 = U64_to_str(self->cap);
        Array_set(_va9, &(U64){_t386}, _t387);
        ;
        U64 _t388 = 4;
        Str *_t389 = Str_lit(")", 1ULL);
        Array_set(_va9, &(U64){_t388}, _t389);
        ;
        Str *_t390 = Str_lit("Array.get", 9ULL);
        panic(_t390, _va9);
        Str_delete(_t390, &(Bool){1});
    }
    ;
    U64 *_t392 = malloc(sizeof(U64)); *_t392 = U64_mul(DEREF(i), self->elem_size);
    void *_t393 = ptr_add(self->data, DEREF(_t392));
    U64_delete(_t392, &(Bool){1});
    return _t393;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    Bool _t408; { Bool *_hp = U64_gte(i, &self->cap); _t408 = *_hp; free(_hp); }
    if (_t408) {
        Str *_t394 = Str_lit("Str", 3ULL);
        U64 _t395; { U64 *_hp = Str_size(); _t395 = *_hp; free(_hp); }
        U64 _t396 = 5;
        Array *_va10 = Array_new(_t394, &(U64){_t395}, &(U64){_t396});
        Str_delete(_t394, &(Bool){1});
        ;
        ;
        U64 _t397 = 0;
        Str *_t398 = Str_lit("index ", 6ULL);
        Array_set(_va10, &(U64){_t397}, _t398);
        ;
        U64 _t399 = 1;
        Str *_t400 = U64_to_str(DEREF(i));
        Array_set(_va10, &(U64){_t399}, _t400);
        ;
        U64 _t401 = 2;
        Str *_t402 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va10, &(U64){_t401}, _t402);
        ;
        U64 _t403 = 3;
        Str *_t404 = U64_to_str(self->cap);
        Array_set(_va10, &(U64){_t403}, _t404);
        ;
        U64 _t405 = 4;
        Str *_t406 = Str_lit(")", 1ULL);
        Array_set(_va10, &(U64){_t405}, _t406);
        ;
        Str *_t407 = Str_lit("Array.set", 9ULL);
        panic(_t407, _va10);
        Str_delete(_t407, &(Bool){1});
    }
    ;
    U64 *_t409 = malloc(sizeof(U64)); *_t409 = U64_mul(DEREF(i), self->elem_size);
    void *_t410 = ptr_add(self->data, DEREF(_t409));
    Bool _t411 = 0;
    dyn_call_delete(&self->elem_type, _t410, &(Bool){_t411});
    U64_delete(_t409, &(Bool){1});
    ;
    U64 *_t412 = malloc(sizeof(U64)); *_t412 = U64_mul(DEREF(i), self->elem_size);
    void *_t413 = ptr_add(self->data, DEREF(_t412));
    memcpy(_t413, val, self->elem_size);
    U64_delete(_t412, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
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
            ;
            void *_t424 = ptr_add(self->data, DEREF(_t423));
            Bool _t425 = 0;
            dyn_call_delete(&self->elem_type, _t424, &(Bool){_t425});
            U64_delete(_t423, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t426 = 0;
    Str_delete(&self->elem_type, &(Bool){_t426});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t440 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t440);
    ;
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
            void *_t437 = ptr_add(self->data, DEREF(_t436));
            void *cloned = dyn_call_clone(&self->elem_type, _t437);
            U64_delete(_t436, &(Bool){1});
            U64 *_t438 = malloc(sizeof(U64)); *_t438 = U64_mul(i, self->elem_size);
            ;
            void *_t439 = ptr_add(new_data, DEREF(_t438));
            memcpy(_t439, cloned, self->elem_size);
            U64_delete(_t438, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t441 = malloc(sizeof(Array));
    _t441->data = new_data;
    _t441->cap = self->cap;
    _t441->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t441->elem_type = *_ca; free(_ca); }
    return _t441;
}

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    Bool _t455; { Bool *_hp = Str_is_empty(key_type); _t455 = *_hp; free(_hp); }
    Bool _t456 = Bool_not(_t455);
    ;
    if (_t456) {
        Bool _t453 = dyn_has_cmp(key_type);
        Bool _t454 = Bool_not(_t453);
        ;
        if (_t454) {
            Str *_t443 = Str_lit("Str", 3ULL);
            U64 _t444; { U64 *_hp = Str_size(); _t444 = *_hp; free(_hp); }
            U64 _t445 = 3;
            Array *_va11 = Array_new(_t443, &(U64){_t444}, &(U64){_t445});
            Str_delete(_t443, &(Bool){1});
            ;
            ;
            U64 _t446 = 0;
            Str *_t447 = Str_lit("type ", 5ULL);
            Array_set(_va11, &(U64){_t446}, _t447);
            ;
            U64 _t448 = 1;
            Str *_t449 = Str_clone(key_type);
            Array_set(_va11, &(U64){_t448}, _t449);
            ;
            U64 _t450 = 2;
            Str *_t451 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va11, &(U64){_t450}, _t451);
            ;
            Str *_t452 = Str_lit("Map.new", 7ULL);
            panic(_t452, _va11);
            Str_delete(_t452, &(Bool){1});
        }
        ;
    }
    ;
    void *_t457 = malloc(DEREF(key_size));
    void *_t458 = malloc(DEREF(val_size));
    U64 _t459 = 0;
    I64 _t460 = 1;
    U64 _t461 = U64_clone(key_size);
    U64 _t462 = U64_clone(val_size);
    Map *_t463 = malloc(sizeof(Map));
    _t463->key_data = _t457;
    _t463->val_data = _t458;
    _t463->count = _t459;
    _t463->cap = _t460;
    _t463->key_size = _t461;
    { Str *_ca = Str_clone(key_type); _t463->key_type = *_ca; free(_ca); }
    _t463->val_size = _t462;
    { Str *_ca = Str_clone(val_type); _t463->val_type = *_ca; free(_ca); }
    ;
    ;
    ;
    ;
    return _t463;
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
        Bool _wcond464; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond464 = *_hp; free(_hp); }
        if (_wcond464) {
        } else {
            ;
            break;
        }
        ;
        U64 _t471 = U64_sub(hi, lo);
        U64 _t472 = 2;
        U64 _t473 = U64_div(_t471, _t472);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t473);
        ;
        U64 *_t474 = malloc(sizeof(U64)); *_t474 = U64_mul(DEREF(mid), self->key_size);
        void *_t475 = ptr_add(self->key_data, DEREF(_t474));
        I64 *c = dyn_call_cmp(&self->key_type, _t475, key);
        U64_delete(_t474, &(Bool){1});
        I64 _t476 = 0;
        Bool _t477; { Bool *_hp = I64_lt(c, &(I64){_t476}); _t477 = *_hp; free(_hp); }
        ;
        if (_t477) {
            U64 _t465 = 1;
            U64 _t466 = U64_add(DEREF(mid), _t465);
            ;
            lo = _t466;
            ;
        } else {
            I64 _t469 = 0;
            Bool _t470; { Bool *_hp = I64_gt(c, &(I64){_t469}); _t470 = *_hp; free(_hp); }
            ;
            if (_t470) {
                U64 _t467 = U64_clone(mid);
                hi = _t467;
                ;
            } else {
                Bool _t468 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t468; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t478 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t478; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond479; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond479 = *_hp; free(_hp); }
        if (_wcond479) {
        } else {
            ;
            break;
        }
        ;
        U64 _t487 = U64_sub(hi, lo);
        U64 _t488 = 2;
        U64 _t489 = U64_div(_t487, _t488);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t489);
        ;
        U64 *_t490 = malloc(sizeof(U64)); *_t490 = U64_mul(DEREF(mid), self->key_size);
        void *_t491 = ptr_add(self->key_data, DEREF(_t490));
        I64 *c = dyn_call_cmp(&self->key_type, _t491, key);
        U64_delete(_t490, &(Bool){1});
        I64 _t492 = 0;
        Bool _t493; { Bool *_hp = I64_lt(c, &(I64){_t492}); _t493 = *_hp; free(_hp); }
        ;
        if (_t493) {
            U64 _t480 = 1;
            U64 _t481 = U64_add(DEREF(mid), _t480);
            ;
            lo = _t481;
            ;
        } else {
            I64 _t485 = 0;
            Bool _t486; { Bool *_hp = I64_gt(c, &(I64){_t485}); _t486 = *_hp; free(_hp); }
            ;
            if (_t486) {
                U64 _t482 = U64_clone(mid);
                hi = _t482;
                ;
            } else {
                U64 *_t483 = malloc(sizeof(U64)); *_t483 = U64_mul(DEREF(mid), self->val_size);
                void *_t484 = ptr_add(self->val_data, DEREF(_t483));
                U64_delete(_t483, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t484;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t494 = Str_lit("Str", 3ULL);
    U64 _t495; { U64 *_hp = Str_size(); _t495 = *_hp; free(_hp); }
    U64 _t496 = 1;
    Array *_va12 = Array_new(_t494, &(U64){_t495}, &(U64){_t496});
    Str_delete(_t494, &(Bool){1});
    ;
    ;
    U64 _t497 = 0;
    Str *_t498 = Str_lit("key not found", 13ULL);
    Array_set(_va12, &(U64){_t497}, _t498);
    ;
    Str *_t499 = Str_lit("Map.get", 7ULL);
    panic(_t499, _va12);
    Str_delete(_t499, &(Bool){1});
    U64 *_t500 = malloc(sizeof(U64));
    *_t500 = 0;
    void *_t501 = ptr_add(self->val_data, DEREF(_t500));
    U64_delete(_t500, &(Bool){1});
    return _t501;
}

void Map_set(Map * self, void * key, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond502; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond502 = *_hp; free(_hp); }
        if (_wcond502) {
        } else {
            ;
            break;
        }
        ;
        U64 _t511 = U64_sub(hi, lo);
        U64 _t512 = 2;
        U64 _t513 = U64_div(_t511, _t512);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t513);
        ;
        U64 *_t514 = malloc(sizeof(U64)); *_t514 = U64_mul(DEREF(mid), self->key_size);
        void *_t515 = ptr_add(self->key_data, DEREF(_t514));
        I64 *c = dyn_call_cmp(&self->key_type, _t515, key);
        U64_delete(_t514, &(Bool){1});
        I64 _t516 = 0;
        Bool _t517; { Bool *_hp = I64_lt(c, &(I64){_t516}); _t517 = *_hp; free(_hp); }
        ;
        if (_t517) {
            U64 _t503 = 1;
            U64 _t504 = U64_add(DEREF(mid), _t503);
            ;
            lo = _t504;
            ;
        } else {
            I64 _t509 = 0;
            Bool _t510; { Bool *_hp = I64_gt(c, &(I64){_t509}); _t510 = *_hp; free(_hp); }
            ;
            if (_t510) {
                U64 _t505 = U64_clone(mid);
                hi = _t505;
                ;
            } else {
                Bool _t506 = 1;
                found = _t506;
                ;
                U64 _t507 = U64_clone(mid);
                lo = _t507;
                ;
                U64 _t508 = U64_clone(mid);
                hi = _t508;
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
        Bool _t522; { Bool *_hp = Str_is_empty(&self->key_type); _t522 = *_hp; free(_hp); }
        Bool _t523 = Bool_not(_t522);
        ;
        if (_t523) {
            Bool _t518 = 0;
            dyn_call_delete(&self->key_type, key, &(Bool){_t518});
            ;
        }
        ;
        free(key);
        Bool _t524; { Bool *_hp = Str_is_empty(&self->val_type); _t524 = *_hp; free(_hp); }
        Bool _t525 = Bool_not(_t524);
        ;
        if (_t525) {
            U64 *_t519 = malloc(sizeof(U64)); *_t519 = U64_mul(lo, self->val_size);
            void *_t520 = ptr_add(self->val_data, DEREF(_t519));
            Bool _t521 = 0;
            dyn_call_delete(&self->val_type, _t520, &(Bool){_t521});
            U64_delete(_t519, &(Bool){1});
            ;
        }
        ;
        U64 *_t526 = malloc(sizeof(U64)); *_t526 = U64_mul(lo, self->val_size);
        void *_t527 = ptr_add(self->val_data, DEREF(_t526));
        memcpy(_t527, val, self->val_size);
        U64_delete(_t526, &(Bool){1});
        free(val);
    } else {
        Bool _t534 = U64_eq(self->count, self->cap);
        if (_t534) {
            U64 _t528 = 2;
            U64 new_cap = U64_mul(self->cap, _t528);
            ;
            U64 _t529 = U64_mul(new_cap, self->key_size);
            void *_t530 = realloc(self->key_data, _t529);
            ;
            self->key_data = _t530;
            U64 _t531 = U64_mul(new_cap, self->val_size);
            void *_t532 = realloc(self->val_data, _t531);
            ;
            self->val_data = _t532;
            U64 _t533 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t533;
            ;
        }
        ;
        U64 _t535 = 1;
        U64 _t536 = U64_add(lo, _t535);
        ;
        U64 *_t537 = malloc(sizeof(U64)); *_t537 = U64_mul(_t536, self->key_size);
        ;
        U64 *_t538 = malloc(sizeof(U64)); *_t538 = U64_mul(lo, self->key_size);
        U64 _t539 = U64_sub(self->count, lo);
        void *_t540 = ptr_add(self->key_data, DEREF(_t537));
        void *_t541 = ptr_add(self->key_data, DEREF(_t538));
        U64 _t542 = U64_mul(_t539, self->key_size);
        ;
        memmove(_t540, _t541, _t542);
        U64_delete(_t537, &(Bool){1});
        U64_delete(_t538, &(Bool){1});
        ;
        U64 _t543 = 1;
        U64 _t544 = U64_add(lo, _t543);
        ;
        U64 *_t545 = malloc(sizeof(U64)); *_t545 = U64_mul(_t544, self->val_size);
        ;
        U64 *_t546 = malloc(sizeof(U64)); *_t546 = U64_mul(lo, self->val_size);
        U64 _t547 = U64_sub(self->count, lo);
        void *_t548 = ptr_add(self->val_data, DEREF(_t545));
        void *_t549 = ptr_add(self->val_data, DEREF(_t546));
        U64 _t550 = U64_mul(_t547, self->val_size);
        ;
        memmove(_t548, _t549, _t550);
        U64_delete(_t545, &(Bool){1});
        U64_delete(_t546, &(Bool){1});
        ;
        U64 *_t551 = malloc(sizeof(U64)); *_t551 = U64_mul(lo, self->key_size);
        void *_t552 = ptr_add(self->key_data, DEREF(_t551));
        memcpy(_t552, key, self->key_size);
        U64_delete(_t551, &(Bool){1});
        U64 *_t553 = malloc(sizeof(U64)); *_t553 = U64_mul(lo, self->val_size);
        void *_t554 = ptr_add(self->val_data, DEREF(_t553));
        memcpy(_t554, val, self->val_size);
        U64_delete(_t553, &(Bool){1});
        free(key);
        free(val);
        U64 _t555 = 1;
        U64 _t556 = U64_add(self->count, _t555);
        ;
        self->count = _t556;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    Bool _t583; { Bool *_hp = Str_is_empty(&self->key_type); _t583 = *_hp; free(_hp); }
    Bool _t584 = Bool_not(_t583);
    ;
    if (_t584) {
        {
            U64 _fi557 = 0;
            while (1) {
                U64 _t559 = 0;
                Range *_t560 = Range_new(_t559, self->count);
                ;
                U64 _t561; { U64 *_hp = Range_len(_t560); _t561 = *_hp; free(_hp); }
                Range_delete(_t560, &(Bool){1});
                Bool _wcond558; { Bool *_hp = U64_lt(&(U64){_fi557}, &(U64){_t561}); _wcond558 = *_hp; free(_hp); }
                ;
                if (_wcond558) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t562 = 0;
                Range *_t563 = Range_new(_t562, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t563, _fi557); i = *_hp; free(_hp); }
                Range_delete(_t563, &(Bool){1});
                U64 _t564 = 1;
                U64 _t565 = U64_add(_fi557, _t564);
                ;
                _fi557 = _t565;
                ;
                U64 *_t566 = malloc(sizeof(U64)); *_t566 = U64_mul(i, self->key_size);
                ;
                void *_t567 = ptr_add(self->key_data, DEREF(_t566));
                Bool _t568 = 0;
                dyn_call_delete(&self->key_type, _t567, &(Bool){_t568});
                U64_delete(_t566, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t585; { Bool *_hp = Str_is_empty(&self->val_type); _t585 = *_hp; free(_hp); }
    Bool _t586 = Bool_not(_t585);
    ;
    if (_t586) {
        {
            U64 _fi569 = 0;
            while (1) {
                U64 _t571 = 0;
                Range *_t572 = Range_new(_t571, self->count);
                ;
                U64 _t573; { U64 *_hp = Range_len(_t572); _t573 = *_hp; free(_hp); }
                Range_delete(_t572, &(Bool){1});
                Bool _wcond570; { Bool *_hp = U64_lt(&(U64){_fi569}, &(U64){_t573}); _wcond570 = *_hp; free(_hp); }
                ;
                if (_wcond570) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t574 = 0;
                Range *_t575 = Range_new(_t574, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t575, _fi569); i = *_hp; free(_hp); }
                Range_delete(_t575, &(Bool){1});
                U64 _t576 = 1;
                U64 _t577 = U64_add(_fi569, _t576);
                ;
                _fi569 = _t577;
                ;
                U64 *_t578 = malloc(sizeof(U64)); *_t578 = U64_mul(i, self->val_size);
                ;
                void *_t579 = ptr_add(self->val_data, DEREF(_t578));
                Bool _t580 = 0;
                dyn_call_delete(&self->val_type, _t579, &(Bool){_t580});
                U64_delete(_t578, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t587; { Bool *_hp = Str_is_empty(&self->key_type); _t587 = *_hp; free(_hp); }
    Bool _t588 = Bool_not(_t587);
    ;
    if (_t588) {
        Bool _t581 = 0;
        Str_delete(&self->key_type, &(Bool){_t581});
        ;
    }
    ;
    Bool _t589; { Bool *_hp = Str_is_empty(&self->val_type); _t589 = *_hp; free(_hp); }
    Bool _t590 = Bool_not(_t589);
    ;
    if (_t590) {
        Bool _t582 = 0;
        Str_delete(&self->val_type, &(Bool){_t582});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t608 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(_t608);
    ;
    U64 _t609 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(_t609);
    ;
    {
        U64 _fi591 = 0;
        while (1) {
            U64 _t593 = 0;
            Range *_t594 = Range_new(_t593, self->count);
            ;
            U64 _t595; { U64 *_hp = Range_len(_t594); _t595 = *_hp; free(_hp); }
            Range_delete(_t594, &(Bool){1});
            Bool _wcond592; { Bool *_hp = U64_lt(&(U64){_fi591}, &(U64){_t595}); _wcond592 = *_hp; free(_hp); }
            ;
            if (_wcond592) {
            } else {
                ;
                break;
            }
            ;
            U64 _t596 = 0;
            Range *_t597 = Range_new(_t596, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t597, _fi591); i = *_hp; free(_hp); }
            Range_delete(_t597, &(Bool){1});
            U64 _t598 = 1;
            U64 _t599 = U64_add(_fi591, _t598);
            ;
            _fi591 = _t599;
            ;
            U64 *_t600 = malloc(sizeof(U64)); *_t600 = U64_mul(i, self->key_size);
            void *_t601 = ptr_add(self->key_data, DEREF(_t600));
            void *ck = dyn_call_clone(&self->key_type, _t601);
            U64_delete(_t600, &(Bool){1});
            U64 *_t602 = malloc(sizeof(U64)); *_t602 = U64_mul(i, self->key_size);
            void *_t603 = ptr_add(new_keys, DEREF(_t602));
            memcpy(_t603, ck, self->key_size);
            U64_delete(_t602, &(Bool){1});
            free(ck);
            U64 *_t604 = malloc(sizeof(U64)); *_t604 = U64_mul(i, self->val_size);
            void *_t605 = ptr_add(self->val_data, DEREF(_t604));
            void *cv = dyn_call_clone(&self->val_type, _t605);
            U64_delete(_t604, &(Bool){1});
            U64 *_t606 = malloc(sizeof(U64)); *_t606 = U64_mul(i, self->val_size);
            ;
            void *_t607 = ptr_add(new_vals, DEREF(_t606));
            memcpy(_t607, cv, self->val_size);
            U64_delete(_t606, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t610 = malloc(sizeof(Map));
    _t610->key_data = new_keys;
    _t610->val_data = new_vals;
    _t610->count = self->count;
    _t610->cap = self->cap;
    _t610->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t610->key_type = *_ca; free(_ca); }
    _t610->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t610->val_type = *_ca; free(_ca); }
    return _t610;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    Bool _t624; { Bool *_hp = Str_is_empty(elem_type); _t624 = *_hp; free(_hp); }
    Bool _t625 = Bool_not(_t624);
    ;
    if (_t625) {
        Bool _t622 = dyn_has_cmp(elem_type);
        Bool _t623 = Bool_not(_t622);
        ;
        if (_t623) {
            Str *_t612 = Str_lit("Str", 3ULL);
            U64 _t613; { U64 *_hp = Str_size(); _t613 = *_hp; free(_hp); }
            U64 _t614 = 3;
            Array *_va13 = Array_new(_t612, &(U64){_t613}, &(U64){_t614});
            Str_delete(_t612, &(Bool){1});
            ;
            ;
            U64 _t615 = 0;
            Str *_t616 = Str_lit("type ", 5ULL);
            Array_set(_va13, &(U64){_t615}, _t616);
            ;
            U64 _t617 = 1;
            Str *_t618 = Str_clone(elem_type);
            Array_set(_va13, &(U64){_t617}, _t618);
            ;
            U64 _t619 = 2;
            Str *_t620 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va13, &(U64){_t619}, _t620);
            ;
            Str *_t621 = Str_lit("Set.new", 7ULL);
            panic(_t621, _va13);
            Str_delete(_t621, &(Bool){1});
        }
        ;
    }
    ;
    void *_t626 = malloc(DEREF(elem_size));
    U64 _t627 = 0;
    I64 _t628 = 1;
    U64 _t629 = U64_clone(elem_size);
    Set *_t630 = malloc(sizeof(Set));
    _t630->data = _t626;
    _t630->count = _t627;
    _t630->cap = _t628;
    _t630->elem_size = _t629;
    { Str *_ca = Str_clone(elem_type); _t630->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t630;
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
        Bool _wcond631; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond631 = *_hp; free(_hp); }
        if (_wcond631) {
        } else {
            ;
            break;
        }
        ;
        U64 _t638 = U64_sub(hi, lo);
        U64 _t639 = 2;
        U64 _t640 = U64_div(_t638, _t639);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t640);
        ;
        U64 *_t641 = malloc(sizeof(U64)); *_t641 = U64_mul(DEREF(mid), self->elem_size);
        void *_t642 = ptr_add(self->data, DEREF(_t641));
        I64 *c = dyn_call_cmp(&self->elem_type, _t642, val);
        U64_delete(_t641, &(Bool){1});
        I64 _t643 = 0;
        Bool _t644; { Bool *_hp = I64_lt(c, &(I64){_t643}); _t644 = *_hp; free(_hp); }
        ;
        if (_t644) {
            U64 _t632 = 1;
            U64 _t633 = U64_add(DEREF(mid), _t632);
            ;
            lo = _t633;
            ;
        } else {
            I64 _t636 = 0;
            Bool _t637; { Bool *_hp = I64_gt(c, &(I64){_t636}); _t637 = *_hp; free(_hp); }
            ;
            if (_t637) {
                U64 _t634 = U64_clone(mid);
                hi = _t634;
                ;
            } else {
                Bool _t635 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t635; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t645 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t645; return _r; }
}

void Set_add(Set * self, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond646; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond646 = *_hp; free(_hp); }
        if (_wcond646) {
        } else {
            ;
            break;
        }
        ;
        U64 _t655 = U64_sub(hi, lo);
        U64 _t656 = 2;
        U64 _t657 = U64_div(_t655, _t656);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t657);
        ;
        U64 *_t658 = malloc(sizeof(U64)); *_t658 = U64_mul(DEREF(mid), self->elem_size);
        void *_t659 = ptr_add(self->data, DEREF(_t658));
        I64 *c = dyn_call_cmp(&self->elem_type, _t659, val);
        U64_delete(_t658, &(Bool){1});
        I64 _t660 = 0;
        Bool _t661; { Bool *_hp = I64_lt(c, &(I64){_t660}); _t661 = *_hp; free(_hp); }
        ;
        if (_t661) {
            U64 _t647 = 1;
            U64 _t648 = U64_add(DEREF(mid), _t647);
            ;
            lo = _t648;
            ;
        } else {
            I64 _t653 = 0;
            Bool _t654; { Bool *_hp = I64_gt(c, &(I64){_t653}); _t654 = *_hp; free(_hp); }
            ;
            if (_t654) {
                U64 _t649 = U64_clone(mid);
                hi = _t649;
                ;
            } else {
                Bool _t650 = 1;
                found = _t650;
                ;
                U64 _t651 = U64_clone(mid);
                lo = _t651;
                ;
                U64 _t652 = U64_clone(mid);
                hi = _t652;
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
        Bool _t663; { Bool *_hp = Str_is_empty(&self->elem_type); _t663 = *_hp; free(_hp); }
        Bool _t664 = Bool_not(_t663);
        ;
        if (_t664) {
            Bool _t662 = 0;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t662});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t669 = U64_eq(self->count, self->cap);
        if (_t669) {
            U64 _t665 = 2;
            U64 new_cap = U64_mul(self->cap, _t665);
            ;
            U64 _t666 = U64_mul(new_cap, self->elem_size);
            void *_t667 = realloc(self->data, _t666);
            ;
            self->data = _t667;
            U64 _t668 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t668;
            ;
        }
        ;
        U64 _t670 = 1;
        U64 _t671 = U64_add(lo, _t670);
        ;
        U64 *_t672 = malloc(sizeof(U64)); *_t672 = U64_mul(_t671, self->elem_size);
        ;
        U64 *_t673 = malloc(sizeof(U64)); *_t673 = U64_mul(lo, self->elem_size);
        U64 _t674 = U64_sub(self->count, lo);
        void *_t675 = ptr_add(self->data, DEREF(_t672));
        void *_t676 = ptr_add(self->data, DEREF(_t673));
        U64 _t677 = U64_mul(_t674, self->elem_size);
        ;
        memmove(_t675, _t676, _t677);
        U64_delete(_t672, &(Bool){1});
        U64_delete(_t673, &(Bool){1});
        ;
        U64 *_t678 = malloc(sizeof(U64)); *_t678 = U64_mul(lo, self->elem_size);
        void *_t679 = ptr_add(self->data, DEREF(_t678));
        memcpy(_t679, val, self->elem_size);
        U64_delete(_t678, &(Bool){1});
        free(val);
        U64 _t680 = 1;
        U64 _t681 = U64_add(self->count, _t680);
        ;
        self->count = _t681;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    Bool _t695; { Bool *_hp = Str_is_empty(&self->elem_type); _t695 = *_hp; free(_hp); }
    Bool _t696 = Bool_not(_t695);
    ;
    if (_t696) {
        {
            U64 _fi682 = 0;
            while (1) {
                U64 _t684 = 0;
                Range *_t685 = Range_new(_t684, self->count);
                ;
                U64 _t686; { U64 *_hp = Range_len(_t685); _t686 = *_hp; free(_hp); }
                Range_delete(_t685, &(Bool){1});
                Bool _wcond683; { Bool *_hp = U64_lt(&(U64){_fi682}, &(U64){_t686}); _wcond683 = *_hp; free(_hp); }
                ;
                if (_wcond683) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t687 = 0;
                Range *_t688 = Range_new(_t687, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t688, _fi682); i = *_hp; free(_hp); }
                Range_delete(_t688, &(Bool){1});
                U64 _t689 = 1;
                U64 _t690 = U64_add(_fi682, _t689);
                ;
                _fi682 = _t690;
                ;
                U64 *_t691 = malloc(sizeof(U64)); *_t691 = U64_mul(i, self->elem_size);
                ;
                void *_t692 = ptr_add(self->data, DEREF(_t691));
                Bool _t693 = 0;
                dyn_call_delete(&self->elem_type, _t692, &(Bool){_t693});
                U64_delete(_t691, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t697; { Bool *_hp = Str_is_empty(&self->elem_type); _t697 = *_hp; free(_hp); }
    Bool _t698 = Bool_not(_t697);
    ;
    if (_t698) {
        Bool _t694 = 0;
        Str_delete(&self->elem_type, &(Bool){_t694});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t712 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t712);
    ;
    {
        U64 _fi699 = 0;
        while (1) {
            U64 _t701 = 0;
            Range *_t702 = Range_new(_t701, self->count);
            ;
            U64 _t703; { U64 *_hp = Range_len(_t702); _t703 = *_hp; free(_hp); }
            Range_delete(_t702, &(Bool){1});
            Bool _wcond700; { Bool *_hp = U64_lt(&(U64){_fi699}, &(U64){_t703}); _wcond700 = *_hp; free(_hp); }
            ;
            if (_wcond700) {
            } else {
                ;
                break;
            }
            ;
            U64 _t704 = 0;
            Range *_t705 = Range_new(_t704, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t705, _fi699); i = *_hp; free(_hp); }
            Range_delete(_t705, &(Bool){1});
            U64 _t706 = 1;
            U64 _t707 = U64_add(_fi699, _t706);
            ;
            _fi699 = _t707;
            ;
            U64 *_t708 = malloc(sizeof(U64)); *_t708 = U64_mul(i, self->elem_size);
            void *_t709 = ptr_add(self->data, DEREF(_t708));
            void *cloned = dyn_call_clone(&self->elem_type, _t709);
            U64_delete(_t708, &(Bool){1});
            U64 *_t710 = malloc(sizeof(U64)); *_t710 = U64_mul(i, self->elem_size);
            ;
            void *_t711 = ptr_add(new_data, DEREF(_t710));
            memcpy(_t711, cloned, self->elem_size);
            U64_delete(_t710, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t713 = malloc(sizeof(Set));
    _t713->data = new_data;
    _t713->count = self->count;
    _t713->cap = self->cap;
    _t713->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t713->elem_type = *_ca; free(_ca); }
    return _t713;
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
    Bool _t721; { Bool *_hp = U64_gte(i, &self->count); _t721 = *_hp; free(_hp); }
    if (_t721) {
        Str *_t715 = Str_lit("Str", 3ULL);
        U64 _t716; { U64 *_hp = Str_size(); _t716 = *_hp; free(_hp); }
        U64 _t717 = 1;
        Array *_va14 = Array_new(_t715, &(U64){_t716}, &(U64){_t717});
        Str_delete(_t715, &(Bool){1});
        ;
        ;
        U64 _t718 = 0;
        Str *_t719 = Str_lit("index out of bounds", 19ULL);
        Array_set(_va14, &(U64){_t718}, _t719);
        ;
        Str *_t720 = Str_lit("Str.get", 7ULL);
        panic(_t720, _va14);
        Str_delete(_t720, &(Bool){1});
    }
    ;
    void *_t722 = ptr_add(self->c_str, DEREF(i));
    return _t722;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 min_len = a->count;
    Bool _t728; { Bool *_hp = U64_lt(&b->count, &a->count); _t728 = *_hp; free(_hp); }
    if (_t728) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond723; { Bool *_hp = U64_lt(i, &(U64){min_len}); _wcond723 = *_hp; free(_hp); }
        if (_wcond723) {
        } else {
            ;
            break;
        }
        ;
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 _t724 = 0;
        Bool _t725; { Bool *_hp = I64_neq(c, &(I64){_t724}); _t725 = *_hp; free(_hp); }
        ;
        if (_t725) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t726 = 1;
        U64 _t727 = U64_add(DEREF(i), _t726);
        ;
        *i = _t727;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t729 = U64_cmp(a->count, b->count);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t729; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    U64 _t730 = 1;
    U64 _t731 = U64_add(DEREF(new_len), _t730);
    ;
    U8 *new_data = malloc(_t731);
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t732 = ptr_add(new_data, a->count);
    memcpy(_t732, b->c_str, b->count);
    void *_t733 = ptr_add(new_data, DEREF(new_len));
    I64 _t734 = 0;
    U64 _t735 = 1;
    memcpy(_t733, &(I64){_t734}, _t735);
    ;
    ;
    U64 _t736 = U64_clone(new_len);
    U64 _t737 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t738 = malloc(sizeof(Str));
    _t738->c_str = new_data;
    _t738->count = _t736;
    _t738->cap = _t737;
    ;
    ;
    return _t738;
}

Str * Str_with_capacity(U64 * n) {
    U64 _t739 = 1;
    U64 _t740 = U64_add(DEREF(n), _t739);
    ;
    U8 *buf = malloc(_t740);
    ;
    I64 _t741 = 0;
    U64 _t742 = 1;
    memcpy(buf, &(I64){_t741}, _t742);
    ;
    ;
    I64 _t743 = 0;
    U64 _t744 = U64_clone(n);
    Str *_t745 = malloc(sizeof(Str));
    _t745->c_str = buf;
    _t745->count = _t743;
    _t745->cap = _t744;
    ;
    ;
    return _t745;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    Bool _t758; { Bool *_hp = U64_gte(&self->cap, CAP_VIEW); _t758 = *_hp; free(_hp); }
    if (_t758) {
        Str *_t746 = Str_lit("Str", 3ULL);
        U64 _t747; { U64 *_hp = Str_size(); _t747 = *_hp; free(_hp); }
        U64 _t748 = 1;
        Array *_va15 = Array_new(_t746, &(U64){_t747}, &(U64){_t748});
        Str_delete(_t746, &(Bool){1});
        ;
        ;
        U64 _t749 = 0;
        Str *_t750 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va15, &(U64){_t749}, _t750);
        ;
        Str *_t751 = Str_lit("Str.push_str", 12ULL);
        panic(_t751, _va15);
        Str_delete(_t751, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool _t759; { Bool *_hp = U64_gt(new_len, &self->cap); _t759 = *_hp; free(_hp); }
    if (_t759) {
        Str *_t752 = Str_lit("Str", 3ULL);
        U64 _t753; { U64 *_hp = Str_size(); _t753 = *_hp; free(_hp); }
        U64 _t754 = 1;
        Array *_va16 = Array_new(_t752, &(U64){_t753}, &(U64){_t754});
        Str_delete(_t752, &(Bool){1});
        ;
        ;
        U64 _t755 = 0;
        Str *_t756 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va16, &(U64){_t755}, _t756);
        ;
        Str *_t757 = Str_lit("Str.push_str", 12ULL);
        panic(_t757, _va16);
        Str_delete(_t757, &(Bool){1});
    }
    ;
    void *_t760 = ptr_add(self->c_str, self->count);
    memcpy(_t760, s->c_str, s->count);
    U64 _t761 = U64_clone(new_len);
    self->count = _t761;
    ;
    void *_t762 = ptr_add(self->c_str, DEREF(new_len));
    I64 _t763 = 0;
    U64 _t764 = 1;
    memcpy(_t762, &(I64){_t763}, _t764);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    U64 _t765 = 1;
    U64 _t766 = U64_add(val->count, _t765);
    ;
    U8 *new_data = malloc(_t766);
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t767 = ptr_add(new_data, val->count);
    I64 _t768 = 0;
    U64 _t769 = 1;
    memcpy(_t767, &(I64){_t768}, _t769);
    ;
    ;
    Str *_t770 = malloc(sizeof(Str));
    _t770->c_str = new_data;
    _t770->count = val->count;
    _t770->cap = val->count;
    return _t770;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    Bool _t771; { Bool *_hp = U64_lt(&self->cap, CAP_VIEW); _t771 = *_hp; free(_hp); }
    if (_t771) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t772 = Str_clone(val);
    return _t772;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    U64 ln = U64_clone(n);
    Bool _t774; { Bool *_hp = U64_gt(st, &s->count); _t774 = *_hp; free(_hp); }
    if (_t774) {
        *st = s->count;
    }
    ;
    U64 _t775 = U64_add(DEREF(st), ln);
    Bool _t776; { Bool *_hp = U64_gt(&(U64){_t775}, &s->count); _t776 = *_hp; free(_hp); }
    ;
    if (_t776) {
        U64 _t773 = U64_sub(s->count, DEREF(st));
        ln = _t773;
        ;
    }
    ;
    void *_t777 = ptr_add(s->c_str, DEREF(st));
    U64 _t778 = U64_clone(&(U64){ln});
    ;
    U64 _t779 = U64_clone(CAP_VIEW);
    Str *_t780 = malloc(sizeof(Str));
    _t780->c_str = _t777;
    _t780->count = _t778;
    _t780->cap = _t779;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t780;
}

Bool * Str_contains(Str * a, Str * b) {
    U64 _t794 = 0;
    Bool _t795 = U64_eq(b->count, _t794);
    ;
    if (_t795) {
        Bool _t781 = 1;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t781; return _r; }
    }
    ;
    Bool _t796; { Bool *_hp = U64_gt(&b->count, &a->count); _t796 = *_hp; free(_hp); }
    if (_t796) {
        Bool _t782 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t782; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t791 = U64_sub(a->count, b->count);
        Bool _wcond783; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t791}); _wcond783 = *_hp; free(_hp); }
        ;
        if (_wcond783) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond784; { Bool *_hp = U64_lt(j, &b->count); _wcond784 = *_hp; free(_hp); }
            if (_wcond784) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t786 = malloc(sizeof(U64)); *_t786 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(a, _t786);
            U8 *bc = Str_get(b, j);
            Bool _t787; { Bool *_hp = U8_neq(ac, bc); _t787 = *_hp; free(_hp); }
            U64_delete(_t786, &(Bool){1});
            if (_t787) {
                Bool _t785 = 0;
                found = _t785;
                ;
            }
            ;
            U64 _t788 = 1;
            U64 _t789 = U64_add(DEREF(j), _t788);
            ;
            *j = _t789;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t790 = 1;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t790; return _r; }
        }
        ;
        U64 _t792 = 1;
        U64 _t793 = U64_add(i, _t792);
        ;
        i = _t793;
        ;
    }
    ;
    Bool _t797 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t797; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool _t804; { Bool *_hp = U64_gt(&b->count, &a->count); _t804 = *_hp; free(_hp); }
    if (_t804) {
        Bool _t798 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t798; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond799; { Bool *_hp = U64_lt(i, &b->count); _wcond799 = *_hp; free(_hp); }
        if (_wcond799) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool _t801; { Bool *_hp = U8_neq(ac, bc); _t801 = *_hp; free(_hp); }
        if (_t801) {
            Bool _t800 = 0;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t800; return _r; }
        }
        ;
        U64 _t802 = 1;
        U64 _t803 = U64_add(DEREF(i), _t802);
        ;
        *i = _t803;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t805 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t805; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool _t813; { Bool *_hp = U64_gt(&b->count, &a->count); _t813 = *_hp; free(_hp); }
    if (_t813) {
        Bool _t806 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t806; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond807; { Bool *_hp = U64_lt(i, &b->count); _wcond807 = *_hp; free(_hp); }
        if (_wcond807) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t809 = malloc(sizeof(U64)); *_t809 = U64_add(offset, DEREF(i));
        U8 *ac = Str_get(a, _t809);
        U8 *bc = Str_get(b, i);
        Bool _t810; { Bool *_hp = U8_neq(ac, bc); _t810 = *_hp; free(_hp); }
        U64_delete(_t809, &(Bool){1});
        if (_t810) {
            Bool _t808 = 0;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t808; return _r; }
        }
        ;
        U64 _t811 = 1;
        U64 _t812 = U64_add(DEREF(i), _t811);
        ;
        *i = _t812;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t814 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t814; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t815 = 0;
    Bool _t816 = U64_eq(self->count, _t815);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t816; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    U64 _t834 = 0;
    Bool _t835 = U64_eq(needle->count, _t834);
    ;
    if (_t835) {
        I64 _t817 = 0;
        I64 _t818 = 1;
        I64 _t819 = I64_sub(_t817, _t818);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t819; return _r; }
    }
    ;
    Bool _t836; { Bool *_hp = U64_gt(&needle->count, &self->count); _t836 = *_hp; free(_hp); }
    if (_t836) {
        I64 _t820 = 0;
        I64 _t821 = 1;
        I64 _t822 = I64_sub(_t820, _t821);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t822; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t831 = U64_sub(self->count, needle->count);
        Bool _wcond823; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t831}); _wcond823 = *_hp; free(_hp); }
        ;
        if (_wcond823) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond824; { Bool *_hp = U64_lt(j, &needle->count); _wcond824 = *_hp; free(_hp); }
            if (_wcond824) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t826 = malloc(sizeof(U64)); *_t826 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t826);
            U8 *bc = Str_get(needle, j);
            Bool _t827; { Bool *_hp = U8_neq(ac, bc); _t827 = *_hp; free(_hp); }
            U64_delete(_t826, &(Bool){1});
            if (_t827) {
                Bool _t825 = 0;
                found = _t825;
                ;
            }
            ;
            U64 _t828 = 1;
            U64 _t829 = U64_add(DEREF(j), _t828);
            ;
            *j = _t829;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t830 = U64_to_i64(i);
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t830; return _r; }
        }
        ;
        U64 _t832 = 1;
        U64 _t833 = U64_add(i, _t832);
        ;
        i = _t833;
        ;
    }
    ;
    I64 _t837 = 0;
    I64 _t838 = 1;
    I64 _t839 = I64_sub(_t837, _t838);
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t839; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    U64 _t857 = 0;
    Bool _t858 = U64_eq(needle->count, _t857);
    ;
    if (_t858) {
        I64 _t840 = 0;
        I64 _t841 = 1;
        I64 _t842 = I64_sub(_t840, _t841);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t842; return _r; }
    }
    ;
    Bool _t859; { Bool *_hp = U64_gt(&needle->count, &self->count); _t859 = *_hp; free(_hp); }
    if (_t859) {
        I64 _t843 = 0;
        I64 _t844 = 1;
        I64 _t845 = I64_sub(_t843, _t844);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t845; return _r; }
    }
    ;
    I64 _t860 = 0;
    I64 _t861 = 1;
    I64 last = I64_sub(_t860, _t861);
    ;
    ;
    U64 i = 0;
    while (1) {
        U64 _t854 = U64_sub(self->count, needle->count);
        Bool _wcond846; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t854}); _wcond846 = *_hp; free(_hp); }
        ;
        if (_wcond846) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond847; { Bool *_hp = U64_lt(j, &needle->count); _wcond847 = *_hp; free(_hp); }
            if (_wcond847) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t849 = malloc(sizeof(U64)); *_t849 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t849);
            U8 *bc = Str_get(needle, j);
            Bool _t850; { Bool *_hp = U8_neq(ac, bc); _t850 = *_hp; free(_hp); }
            U64_delete(_t849, &(Bool){1});
            if (_t850) {
                Bool _t848 = 0;
                found = _t848;
                ;
            }
            ;
            U64 _t851 = 1;
            U64 _t852 = U64_add(DEREF(j), _t851);
            ;
            *j = _t852;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t853 = U64_to_i64(i);
            last = _t853;
            ;
        }
        ;
        U64 _t855 = 1;
        U64 _t856 = U64_add(i, _t855);
        ;
        i = _t856;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    U64 _t877 = 0;
    Bool _t878 = U64_eq(from->count, _t877);
    ;
    if (_t878) {
        Str *_t862 = Str_clone(self);
        ;
        return _t862;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 start = 0;
    while (1) {
        U64 _t864 = U64_sub(self->count, from->count);
        Bool _wcond863; { Bool *_hp = U64_lte(&(U64){start}, &(U64){_t864}); _wcond863 = *_hp; free(_hp); }
        ;
        if (_wcond863) {
        } else {
            ;
            break;
        }
        ;
        U64 _t865 = U64_sub(self->count, start);
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t865});
        ;
        I64 pos; { I64 *_hp = Str_find(rest, from); pos = *_hp; free(_hp); }
        I64 _t866 = 0;
        I64 _t867 = 1;
        I64 _t868 = I64_sub(_t866, _t867);
        ;
        ;
        Bool _t869 = I64_eq(pos, _t868);
        ;
        if (_t869) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t870; { U64 *_hp = U64_from_i64(&(I64){pos}); _t870 = *_hp; free(_hp); }
        Str *_t871 = Str_substr(self, &(U64){start}, &(U64){_t870});
        ;
        result = Str_concat(result, _t871);
        Str_delete(_t871, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t872; { U64 *_hp = U64_from_i64(&(I64){pos}); _t872 = *_hp; free(_hp); }
        ;
        U64 _t873 = U64_add(start, _t872);
        ;
        U64 _t874 = U64_add(_t873, from->count);
        ;
        start = _t874;
        ;
    }
    Bool _t879; { Bool *_hp = U64_lt(&(U64){start}, &self->count); _t879 = *_hp; free(_hp); }
    if (_t879) {
        U64 _t875 = U64_sub(self->count, start);
        Str *_t876 = Str_substr(self, &(U64){start}, &(U64){_t875});
        ;
        result = Str_concat(result, _t876);
        Str_delete(_t876, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    U64 _t880 = 1;
    Str *_t881 = Str_substr(self, i, &(U64){_t880});
    ;
    return _t881;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    Bool _t884; { Bool *_hp = Str_starts_with(self, prefix); _t884 = *_hp; free(_hp); }
    if (_t884) {
        U64 _t882 = U64_sub(self->count, prefix->count);
        Str *_t883 = Str_substr(self, &prefix->count, &(U64){_t882});
        ;
        ;
        return _t883;
    }
    ;
    Str *_t885 = Str_clone(self);
    return _t885;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    Bool _t889; { Bool *_hp = Str_ends_with(self, suffix); _t889 = *_hp; free(_hp); }
    if (_t889) {
        U64 _t886 = 0;
        U64 _t887 = U64_sub(self->count, suffix->count);
        Str *_t888 = Str_substr(self, &(U64){_t886}, &(U64){_t887});
        ;
        ;
        ;
        return _t888;
    }
    ;
    Str *_t890 = Str_clone(self);
    return _t890;
}

Str * Str_from_byte(U8 * byte) {
    U64 _t891 = 2;
    U8 *buf = malloc(_t891);
    ;
    U64 _t892 = 1;
    memcpy(buf, byte, _t892);
    ;
    U64 *_t893 = malloc(sizeof(U64));
    *_t893 = 1;
    void *_t894 = ptr_add(buf, DEREF(_t893));
    I64 _t895 = 0;
    U64 _t896 = 1;
    memcpy(_t894, &(I64){_t895}, _t896);
    U64_delete(_t893, &(Bool){1});
    ;
    ;
    I64 _t897 = 1;
    I64 _t898 = 1;
    Str *_t899 = malloc(sizeof(Str));
    _t899->c_str = buf;
    _t899->count = _t897;
    _t899->cap = _t898;
    ;
    ;
    return _t899;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t940 = 0;
    Bool _t941 = U64_eq(self->count, _t940);
    ;
    if (_t941) {
        Str *_t900 = Str_lit("Str", 3ULL);
        U64 _t901; { U64 *_hp = Str_size(); _t901 = *_hp; free(_hp); }
        U64 _t902 = 1;
        Array *_va17 = Array_new(_t900, &(U64){_t901}, &(U64){_t902});
        Str_delete(_t900, &(Bool){1});
        ;
        ;
        U64 _t903 = 0;
        Str *_t904 = Str_lit("empty string", 12ULL);
        Array_set(_va17, &(U64){_t903}, _t904);
        ;
        Str *_t905 = Str_lit("Str.to_i64", 10ULL);
        panic(_t905, _va17);
        Str_delete(_t905, &(Bool){1});
    }
    ;
    I64 result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool neg = 0;
    U64 *_t942 = malloc(sizeof(U64));
    *_t942 = 0;
    U8 *first = Str_get(self, _t942);
    U8 _t943 = 45;
    Bool _t944 = U8_eq(DEREF(first), _t943);
    U64_delete(_t942, &(Bool){1});
    ;
    if (_t944) {
        Bool _t906 = 1;
        neg = _t906;
        ;
        I64 _t907 = 1;
        U64 _t908; { U64 *_hp = U64_from_i64(&(I64){_t907}); _t908 = *_hp; free(_hp); }
        ;
        *i = _t908;
        ;
    }
    ;
    Bool _t945 = U64_eq(DEREF(i), self->count);
    if (_t945) {
        Str *_t909 = Str_lit("Str", 3ULL);
        U64 _t910; { U64 *_hp = Str_size(); _t910 = *_hp; free(_hp); }
        U64 _t911 = 1;
        Array *_va18 = Array_new(_t909, &(U64){_t910}, &(U64){_t911});
        Str_delete(_t909, &(Bool){1});
        ;
        ;
        U64 _t912 = 0;
        Str *_t913 = Str_lit("no digits", 9ULL);
        Array_set(_va18, &(U64){_t912}, _t913);
        ;
        Str *_t914 = Str_lit("Str.to_i64", 10ULL);
        panic(_t914, _va18);
        Str_delete(_t914, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond915; { Bool *_hp = U64_lt(i, &self->count); _wcond915 = *_hp; free(_hp); }
        if (_wcond915) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        I64 _t926 = U8_to_i64(DEREF(ch));
        I64 _t927 = 48;
        I64 d = I64_sub(_t926, _t927);
        ;
        ;
        I64 _t928 = 0;
        I64 _t929 = 9;
        Bool _t930; { Bool *_hp = I64_lt(&(I64){d}, &(I64){_t928}); _t930 = *_hp; free(_hp); }
        ;
        Bool _t931; { Bool *_hp = I64_gt(&(I64){d}, &(I64){_t929}); _t931 = *_hp; free(_hp); }
        ;
        Bool _t932 = Bool_or(_t930, _t931);
        ;
        ;
        if (_t932) {
            Str *_t916 = Str_lit("Str", 3ULL);
            U64 _t917; { U64 *_hp = Str_size(); _t917 = *_hp; free(_hp); }
            U64 _t918 = 3;
            Array *_va19 = Array_new(_t916, &(U64){_t917}, &(U64){_t918});
            Str_delete(_t916, &(Bool){1});
            ;
            ;
            U64 _t919 = 0;
            Str *_t920 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va19, &(U64){_t919}, _t920);
            ;
            U64 _t921 = 1;
            Str *_t922 = Str_clone(self);
            Array_set(_va19, &(U64){_t921}, _t922);
            ;
            U64 _t923 = 2;
            Str *_t924 = Str_lit("'", 1ULL);
            Array_set(_va19, &(U64){_t923}, _t924);
            ;
            Str *_t925 = Str_lit("Str.to_i64", 10ULL);
            panic(_t925, _va19);
            Str_delete(_t925, &(Bool){1});
        }
        ;
        I64 _t933 = 10;
        I64 _t934 = I64_mul(result, _t933);
        ;
        I64 _t935 = I64_add(_t934, d);
        ;
        ;
        result = _t935;
        ;
        U64 _t936 = 1;
        U64 _t937 = U64_add(DEREF(i), _t936);
        ;
        *i = _t937;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t938 = 0;
        I64 _t939 = I64_sub(_t938, result);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t939; return _r; }
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
    I64 _t947; { I64 *_hp = Str_cmp(a, b); _t947 = *_hp; free(_hp); }
    I64 _t948 = 0;
    Bool _t949 = I64_eq(_t947, _t948);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t949; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    I64 _t950 = 0;
    I64 _t951 = 1;
    I64 _t952; { I64 *_hp = Str_cmp(a, b); _t952 = *_hp; free(_hp); }
    I64 _t953 = I64_sub(_t950, _t951);
    ;
    ;
    Bool _t954 = I64_eq(_t952, _t953);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t954; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    I64 _t955; { I64 *_hp = Str_cmp(a, b); _t955 = *_hp; free(_hp); }
    I64 _t956 = 1;
    Bool _t957 = I64_eq(_t955, _t956);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t957; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    Bool _t958; { Bool *_hp = Str_eq(a, b); _t958 = *_hp; free(_hp); }
    Bool _t959 = Bool_not(_t958);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t959; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    Bool _t960; { Bool *_hp = Str_gt(a, b); _t960 = *_hp; free(_hp); }
    Bool _t961 = Bool_not(_t960);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t961; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    Bool _t962; { Bool *_hp = Str_lt(a, b); _t962 = *_hp; free(_hp); }
    Bool _t963 = Bool_not(_t962);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t963; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t964 = malloc(DEREF(elem_size));
    U64 _t965 = 0;
    I64 _t966 = 1;
    U64 _t967 = U64_clone(elem_size);
    Vec *_t968 = malloc(sizeof(Vec));
    _t968->data = _t964;
    _t968->count = _t965;
    _t968->cap = _t966;
    _t968->elem_size = _t967;
    { Str *_ca = Str_clone(elem_type); _t968->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t968;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    Bool _t973 = U64_eq(self->count, self->cap);
    if (_t973) {
        U64 _t969 = 2;
        U64 new_cap = U64_mul(self->cap, _t969);
        ;
        U64 _t970 = U64_mul(new_cap, self->elem_size);
        void *_t971 = realloc(self->data, _t970);
        ;
        self->data = _t971;
        U64 _t972 = U64_clone(&(U64){new_cap});
        ;
        self->cap = _t972;
        ;
    }
    ;
    U64 *_t974 = malloc(sizeof(U64)); *_t974 = U64_mul(self->count, self->elem_size);
    void *_t975 = ptr_add(self->data, DEREF(_t974));
    memcpy(_t975, val, self->elem_size);
    U64_delete(_t974, &(Bool){1});
    free(val);
    U64 _t976 = 1;
    U64 _t977 = U64_add(self->count, _t976);
    ;
    self->count = _t977;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    Bool _t992; { Bool *_hp = U64_gte(i, &self->count); _t992 = *_hp; free(_hp); }
    if (_t992) {
        Str *_t978 = Str_lit("Str", 3ULL);
        U64 _t979; { U64 *_hp = Str_size(); _t979 = *_hp; free(_hp); }
        U64 _t980 = 5;
        Array *_va20 = Array_new(_t978, &(U64){_t979}, &(U64){_t980});
        Str_delete(_t978, &(Bool){1});
        ;
        ;
        U64 _t981 = 0;
        Str *_t982 = Str_lit("index ", 6ULL);
        Array_set(_va20, &(U64){_t981}, _t982);
        ;
        U64 _t983 = 1;
        Str *_t984 = U64_to_str(DEREF(i));
        Array_set(_va20, &(U64){_t983}, _t984);
        ;
        U64 _t985 = 2;
        Str *_t986 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va20, &(U64){_t985}, _t986);
        ;
        U64 _t987 = 3;
        Str *_t988 = U64_to_str(self->count);
        Array_set(_va20, &(U64){_t987}, _t988);
        ;
        U64 _t989 = 4;
        Str *_t990 = Str_lit(")", 1ULL);
        Array_set(_va20, &(U64){_t989}, _t990);
        ;
        Str *_t991 = Str_lit("Vec.get", 7ULL);
        panic(_t991, _va20);
        Str_delete(_t991, &(Bool){1});
    }
    ;
    U64 *_t993 = malloc(sizeof(U64)); *_t993 = U64_mul(DEREF(i), self->elem_size);
    void *_t994 = ptr_add(self->data, DEREF(_t993));
    U64_delete(_t993, &(Bool){1});
    return _t994;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    Bool _t1008; { Bool *_hp = Str_is_empty(&self->elem_type); _t1008 = *_hp; free(_hp); }
    Bool _t1009 = Bool_not(_t1008);
    ;
    if (_t1009) {
        {
            U64 _fi995 = 0;
            while (1) {
                U64 _t997 = 0;
                Range *_t998 = Range_new(_t997, self->count);
                ;
                U64 _t999; { U64 *_hp = Range_len(_t998); _t999 = *_hp; free(_hp); }
                Range_delete(_t998, &(Bool){1});
                Bool _wcond996; { Bool *_hp = U64_lt(&(U64){_fi995}, &(U64){_t999}); _wcond996 = *_hp; free(_hp); }
                ;
                if (_wcond996) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1000 = 0;
                Range *_t1001 = Range_new(_t1000, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t1001, _fi995); i = *_hp; free(_hp); }
                Range_delete(_t1001, &(Bool){1});
                U64 _t1002 = 1;
                U64 _t1003 = U64_add(_fi995, _t1002);
                ;
                _fi995 = _t1003;
                ;
                U64 *_t1004 = malloc(sizeof(U64)); *_t1004 = U64_mul(i, self->elem_size);
                ;
                void *_t1005 = ptr_add(self->data, DEREF(_t1004));
                Bool _t1006 = 0;
                dyn_call_delete(&self->elem_type, _t1005, &(Bool){_t1006});
                U64_delete(_t1004, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1010; { Bool *_hp = Str_is_empty(&self->elem_type); _t1010 = *_hp; free(_hp); }
    Bool _t1011 = Bool_not(_t1010);
    ;
    if (_t1011) {
        Bool _t1007 = 0;
        Str_delete(&self->elem_type, &(Bool){_t1007});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1025 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t1025);
    ;
    {
        U64 _fi1012 = 0;
        while (1) {
            U64 _t1014 = 0;
            Range *_t1015 = Range_new(_t1014, self->count);
            ;
            U64 _t1016; { U64 *_hp = Range_len(_t1015); _t1016 = *_hp; free(_hp); }
            Range_delete(_t1015, &(Bool){1});
            Bool _wcond1013; { Bool *_hp = U64_lt(&(U64){_fi1012}, &(U64){_t1016}); _wcond1013 = *_hp; free(_hp); }
            ;
            if (_wcond1013) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1017 = 0;
            Range *_t1018 = Range_new(_t1017, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t1018, _fi1012); i = *_hp; free(_hp); }
            Range_delete(_t1018, &(Bool){1});
            U64 _t1019 = 1;
            U64 _t1020 = U64_add(_fi1012, _t1019);
            ;
            _fi1012 = _t1020;
            ;
            U64 *_t1021 = malloc(sizeof(U64)); *_t1021 = U64_mul(i, self->elem_size);
            void *_t1022 = ptr_add(self->data, DEREF(_t1021));
            void *cloned = dyn_call_clone(&self->elem_type, _t1022);
            U64_delete(_t1021, &(Bool){1});
            U64 *_t1023 = malloc(sizeof(U64)); *_t1023 = U64_mul(i, self->elem_size);
            ;
            void *_t1024 = ptr_add(new_data, DEREF(_t1023));
            memcpy(_t1024, cloned, self->elem_size);
            U64_delete(_t1023, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1026 = malloc(sizeof(Vec));
    _t1026->data = new_data;
    _t1026->count = self->count;
    _t1026->cap = self->cap;
    _t1026->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1026->elem_type = *_ca; free(_ca); }
    return _t1026;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t1044 = Str_lit("Str", 3ULL);
    U64 _t1045; { U64 *_hp = Str_size(); _t1045 = *_hp; free(_hp); }
    Vec *parts = Vec_new(_t1044, &(U64){_t1045});
    Str_delete(_t1044, &(Bool){1});
    ;
    U64 _t1046; { U64 *_hp = Str_len(delim); _t1046 = *_hp; free(_hp); }
    U64 _t1047 = 0;
    Bool _t1048 = U64_eq(_t1046, _t1047);
    ;
    ;
    if (_t1048) {
        Str *_t1028 = Str_clone(s);
        Vec_push(parts, _t1028);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    U64 pos = 0;
    while (1) {
        U64 _t1038; { U64 *_hp = Str_len(s); _t1038 = *_hp; free(_hp); }
        U64 _t1039; { U64 *_hp = Str_len(delim); _t1039 = *_hp; free(_hp); }
        U64 _t1040 = U64_sub(_t1038, _t1039);
        ;
        ;
        Bool _wcond1029; { Bool *_hp = U64_lte(&(U64){pos}, &(U64){_t1040}); _wcond1029 = *_hp; free(_hp); }
        ;
        if (_wcond1029) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1041; { U64 *_hp = Str_len(delim); _t1041 = *_hp; free(_hp); }
        Str *_t1042 = Str_substr(s, &(U64){pos}, &(U64){_t1041});
        ;
        Bool _t1043; { Bool *_hp = Str_eq(_t1042, delim); _t1043 = *_hp; free(_hp); }
        Str_delete(_t1042, &(Bool){1});
        if (_t1043) {
            U64 _t1030 = U64_sub(pos, start);
            Str *_t1031 = Str_substr(s, &(U64){start}, &(U64){_t1030});
            ;
            Str *_t1032 = Str_clone(_t1031);
            Str_delete(_t1031, &(Bool){1});
            Vec_push(parts, _t1032);
            U64 _t1033; { U64 *_hp = Str_len(delim); _t1033 = *_hp; free(_hp); }
            U64 _t1034 = U64_add(pos, _t1033);
            ;
            start = _t1034;
            ;
            U64 _t1035 = U64_clone(&(U64){start});
            pos = _t1035;
            ;
        } else {
            U64 _t1036 = 1;
            U64 _t1037 = U64_add(pos, _t1036);
            ;
            pos = _t1037;
            ;
        }
        ;
    }
    ;
    U64 _t1049; { U64 *_hp = Str_len(s); _t1049 = *_hp; free(_hp); }
    U64 _t1050 = U64_sub(_t1049, start);
    ;
    Str *_t1051 = Str_substr(s, &(U64){start}, &(U64){_t1050});
    ;
    ;
    Str *_t1052 = Str_clone(_t1051);
    Str_delete(_t1051, &(Bool){1});
    Vec_push(parts, _t1052);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 _t1060; { U64 *_hp = Vec_len(parts); _t1060 = *_hp; free(_hp); }
    U64 _t1061 = 0;
    Bool _t1062 = U64_eq(_t1060, _t1061);
    ;
    ;
    if (_t1062) {
        Str *_t1053 = Str_lit("", 0ULL);
        ;
        return _t1053;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t1055; { U64 *_hp = Vec_len(parts); _t1055 = *_hp; free(_hp); }
        Bool _wcond1054; { Bool *_hp = U64_lt(i, &(U64){_t1055}); _wcond1054 = *_hp; free(_hp); }
        ;
        if (_wcond1054) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1056 = 0;
        Bool _t1057; { Bool *_hp = U64_gt(i, &(U64){_t1056}); _t1057 = *_hp; free(_hp); }
        ;
        if (_t1057) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        U64 _t1058 = 1;
        U64 _t1059 = U64_add(DEREF(i), _t1058);
        ;
        *i = _t1059;
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
    Bool _t1126; { Bool *_hp = TokenType_is_Eof(self); _t1126 = *_hp; free(_hp); }
    if (_t1126) {
        Bool _t1063; { Bool *_hp = TokenType_is_Eof(other); _t1063 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1063; return _r; }
    }
    ;
    Bool _t1127; { Bool *_hp = TokenType_is_LParen(self); _t1127 = *_hp; free(_hp); }
    if (_t1127) {
        Bool _t1064; { Bool *_hp = TokenType_is_LParen(other); _t1064 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1064; return _r; }
    }
    ;
    Bool _t1128; { Bool *_hp = TokenType_is_RParen(self); _t1128 = *_hp; free(_hp); }
    if (_t1128) {
        Bool _t1065; { Bool *_hp = TokenType_is_RParen(other); _t1065 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1065; return _r; }
    }
    ;
    Bool _t1129; { Bool *_hp = TokenType_is_LBrace(self); _t1129 = *_hp; free(_hp); }
    if (_t1129) {
        Bool _t1066; { Bool *_hp = TokenType_is_LBrace(other); _t1066 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1066; return _r; }
    }
    ;
    Bool _t1130; { Bool *_hp = TokenType_is_RBrace(self); _t1130 = *_hp; free(_hp); }
    if (_t1130) {
        Bool _t1067; { Bool *_hp = TokenType_is_RBrace(other); _t1067 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1067; return _r; }
    }
    ;
    Bool _t1131; { Bool *_hp = TokenType_is_LBracket(self); _t1131 = *_hp; free(_hp); }
    if (_t1131) {
        Bool _t1068; { Bool *_hp = TokenType_is_LBracket(other); _t1068 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1068; return _r; }
    }
    ;
    Bool _t1132; { Bool *_hp = TokenType_is_RBracket(self); _t1132 = *_hp; free(_hp); }
    if (_t1132) {
        Bool _t1069; { Bool *_hp = TokenType_is_RBracket(other); _t1069 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1069; return _r; }
    }
    ;
    Bool _t1133; { Bool *_hp = TokenType_is_Comma(self); _t1133 = *_hp; free(_hp); }
    if (_t1133) {
        Bool _t1070; { Bool *_hp = TokenType_is_Comma(other); _t1070 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1070; return _r; }
    }
    ;
    Bool _t1134; { Bool *_hp = TokenType_is_Colon(self); _t1134 = *_hp; free(_hp); }
    if (_t1134) {
        Bool _t1071; { Bool *_hp = TokenType_is_Colon(other); _t1071 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1071; return _r; }
    }
    ;
    Bool _t1135; { Bool *_hp = TokenType_is_Question(self); _t1135 = *_hp; free(_hp); }
    if (_t1135) {
        Bool _t1072; { Bool *_hp = TokenType_is_Question(other); _t1072 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1072; return _r; }
    }
    ;
    Bool _t1136; { Bool *_hp = TokenType_is_Bang(self); _t1136 = *_hp; free(_hp); }
    if (_t1136) {
        Bool _t1073; { Bool *_hp = TokenType_is_Bang(other); _t1073 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1073; return _r; }
    }
    ;
    Bool _t1137; { Bool *_hp = TokenType_is_Minus(self); _t1137 = *_hp; free(_hp); }
    if (_t1137) {
        Bool _t1074; { Bool *_hp = TokenType_is_Minus(other); _t1074 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1074; return _r; }
    }
    ;
    Bool _t1138; { Bool *_hp = TokenType_is_Plus(self); _t1138 = *_hp; free(_hp); }
    if (_t1138) {
        Bool _t1075; { Bool *_hp = TokenType_is_Plus(other); _t1075 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1075; return _r; }
    }
    ;
    Bool _t1139; { Bool *_hp = TokenType_is_Star(self); _t1139 = *_hp; free(_hp); }
    if (_t1139) {
        Bool _t1076; { Bool *_hp = TokenType_is_Star(other); _t1076 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1076; return _r; }
    }
    ;
    Bool _t1140; { Bool *_hp = TokenType_is_Slash(self); _t1140 = *_hp; free(_hp); }
    if (_t1140) {
        Bool _t1077; { Bool *_hp = TokenType_is_Slash(other); _t1077 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1077; return _r; }
    }
    ;
    Bool _t1141; { Bool *_hp = TokenType_is_Dot(self); _t1141 = *_hp; free(_hp); }
    if (_t1141) {
        Bool _t1078; { Bool *_hp = TokenType_is_Dot(other); _t1078 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1078; return _r; }
    }
    ;
    Bool _t1142; { Bool *_hp = TokenType_is_DotDot(self); _t1142 = *_hp; free(_hp); }
    if (_t1142) {
        Bool _t1079; { Bool *_hp = TokenType_is_DotDot(other); _t1079 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1079; return _r; }
    }
    ;
    Bool _t1143; { Bool *_hp = TokenType_is_Eq(self); _t1143 = *_hp; free(_hp); }
    if (_t1143) {
        Bool _t1080; { Bool *_hp = TokenType_is_Eq(other); _t1080 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1080; return _r; }
    }
    ;
    Bool _t1144; { Bool *_hp = TokenType_is_EqEq(self); _t1144 = *_hp; free(_hp); }
    if (_t1144) {
        Bool _t1081; { Bool *_hp = TokenType_is_EqEq(other); _t1081 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1081; return _r; }
    }
    ;
    Bool _t1145; { Bool *_hp = TokenType_is_Neq(self); _t1145 = *_hp; free(_hp); }
    if (_t1145) {
        Bool _t1082; { Bool *_hp = TokenType_is_Neq(other); _t1082 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1082; return _r; }
    }
    ;
    Bool _t1146; { Bool *_hp = TokenType_is_Lt(self); _t1146 = *_hp; free(_hp); }
    if (_t1146) {
        Bool _t1083; { Bool *_hp = TokenType_is_Lt(other); _t1083 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1083; return _r; }
    }
    ;
    Bool _t1147; { Bool *_hp = TokenType_is_LtEq(self); _t1147 = *_hp; free(_hp); }
    if (_t1147) {
        Bool _t1084; { Bool *_hp = TokenType_is_LtEq(other); _t1084 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1084; return _r; }
    }
    ;
    Bool _t1148; { Bool *_hp = TokenType_is_Gt(self); _t1148 = *_hp; free(_hp); }
    if (_t1148) {
        Bool _t1085; { Bool *_hp = TokenType_is_Gt(other); _t1085 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1085; return _r; }
    }
    ;
    Bool _t1149; { Bool *_hp = TokenType_is_GtEq(self); _t1149 = *_hp; free(_hp); }
    if (_t1149) {
        Bool _t1086; { Bool *_hp = TokenType_is_GtEq(other); _t1086 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1086; return _r; }
    }
    ;
    Bool _t1150; { Bool *_hp = TokenType_is_ColonEq(self); _t1150 = *_hp; free(_hp); }
    if (_t1150) {
        Bool _t1087; { Bool *_hp = TokenType_is_ColonEq(other); _t1087 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1087; return _r; }
    }
    ;
    Bool _t1151; { Bool *_hp = TokenType_is_Ident(self); _t1151 = *_hp; free(_hp); }
    if (_t1151) {
        Bool _t1088; { Bool *_hp = TokenType_is_Ident(other); _t1088 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1088; return _r; }
    }
    ;
    Bool _t1152; { Bool *_hp = TokenType_is_StringTok(self); _t1152 = *_hp; free(_hp); }
    if (_t1152) {
        Bool _t1089; { Bool *_hp = TokenType_is_StringTok(other); _t1089 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1089; return _r; }
    }
    ;
    Bool _t1153; { Bool *_hp = TokenType_is_Number(self); _t1153 = *_hp; free(_hp); }
    if (_t1153) {
        Bool _t1090; { Bool *_hp = TokenType_is_Number(other); _t1090 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1090; return _r; }
    }
    ;
    Bool _t1154; { Bool *_hp = TokenType_is_Char(self); _t1154 = *_hp; free(_hp); }
    if (_t1154) {
        Bool _t1091; { Bool *_hp = TokenType_is_Char(other); _t1091 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1091; return _r; }
    }
    ;
    Bool _t1155; { Bool *_hp = TokenType_is_KwMode(self); _t1155 = *_hp; free(_hp); }
    if (_t1155) {
        Bool _t1092; { Bool *_hp = TokenType_is_KwMode(other); _t1092 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1092; return _r; }
    }
    ;
    Bool _t1156; { Bool *_hp = TokenType_is_KwMut(self); _t1156 = *_hp; free(_hp); }
    if (_t1156) {
        Bool _t1093; { Bool *_hp = TokenType_is_KwMut(other); _t1093 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1093; return _r; }
    }
    ;
    Bool _t1157; { Bool *_hp = TokenType_is_KwOwn(self); _t1157 = *_hp; free(_hp); }
    if (_t1157) {
        Bool _t1094; { Bool *_hp = TokenType_is_KwOwn(other); _t1094 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1094; return _r; }
    }
    ;
    Bool _t1158; { Bool *_hp = TokenType_is_KwRef(self); _t1158 = *_hp; free(_hp); }
    if (_t1158) {
        Bool _t1095; { Bool *_hp = TokenType_is_KwRef(other); _t1095 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1095; return _r; }
    }
    ;
    Bool _t1159; { Bool *_hp = TokenType_is_KwStruct(self); _t1159 = *_hp; free(_hp); }
    if (_t1159) {
        Bool _t1096; { Bool *_hp = TokenType_is_KwStruct(other); _t1096 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1096; return _r; }
    }
    ;
    Bool _t1160; { Bool *_hp = TokenType_is_KwExtStruct(self); _t1160 = *_hp; free(_hp); }
    if (_t1160) {
        Bool _t1097; { Bool *_hp = TokenType_is_KwExtStruct(other); _t1097 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1097; return _r; }
    }
    ;
    Bool _t1161; { Bool *_hp = TokenType_is_KwEnum(self); _t1161 = *_hp; free(_hp); }
    if (_t1161) {
        Bool _t1098; { Bool *_hp = TokenType_is_KwEnum(other); _t1098 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1098; return _r; }
    }
    ;
    Bool _t1162; { Bool *_hp = TokenType_is_KwNamespace(self); _t1162 = *_hp; free(_hp); }
    if (_t1162) {
        Bool _t1099; { Bool *_hp = TokenType_is_KwNamespace(other); _t1099 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1099; return _r; }
    }
    ;
    Bool _t1163; { Bool *_hp = TokenType_is_KwFunc(self); _t1163 = *_hp; free(_hp); }
    if (_t1163) {
        Bool _t1100; { Bool *_hp = TokenType_is_KwFunc(other); _t1100 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1100; return _r; }
    }
    ;
    Bool _t1164; { Bool *_hp = TokenType_is_KwProc(self); _t1164 = *_hp; free(_hp); }
    if (_t1164) {
        Bool _t1101; { Bool *_hp = TokenType_is_KwProc(other); _t1101 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1101; return _r; }
    }
    ;
    Bool _t1165; { Bool *_hp = TokenType_is_KwTest(self); _t1165 = *_hp; free(_hp); }
    if (_t1165) {
        Bool _t1102; { Bool *_hp = TokenType_is_KwTest(other); _t1102 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1102; return _r; }
    }
    ;
    Bool _t1166; { Bool *_hp = TokenType_is_KwMacro(self); _t1166 = *_hp; free(_hp); }
    if (_t1166) {
        Bool _t1103; { Bool *_hp = TokenType_is_KwMacro(other); _t1103 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1103; return _r; }
    }
    ;
    Bool _t1167; { Bool *_hp = TokenType_is_KwExtFunc(self); _t1167 = *_hp; free(_hp); }
    if (_t1167) {
        Bool _t1104; { Bool *_hp = TokenType_is_KwExtFunc(other); _t1104 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1104; return _r; }
    }
    ;
    Bool _t1168; { Bool *_hp = TokenType_is_KwExtProc(self); _t1168 = *_hp; free(_hp); }
    if (_t1168) {
        Bool _t1105; { Bool *_hp = TokenType_is_KwExtProc(other); _t1105 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1105; return _r; }
    }
    ;
    Bool _t1169; { Bool *_hp = TokenType_is_KwReturns(self); _t1169 = *_hp; free(_hp); }
    if (_t1169) {
        Bool _t1106; { Bool *_hp = TokenType_is_KwReturns(other); _t1106 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1106; return _r; }
    }
    ;
    Bool _t1170; { Bool *_hp = TokenType_is_KwThrows(self); _t1170 = *_hp; free(_hp); }
    if (_t1170) {
        Bool _t1107; { Bool *_hp = TokenType_is_KwThrows(other); _t1107 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1107; return _r; }
    }
    ;
    Bool _t1171; { Bool *_hp = TokenType_is_KwIf(self); _t1171 = *_hp; free(_hp); }
    if (_t1171) {
        Bool _t1108; { Bool *_hp = TokenType_is_KwIf(other); _t1108 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1108; return _r; }
    }
    ;
    Bool _t1172; { Bool *_hp = TokenType_is_KwElse(self); _t1172 = *_hp; free(_hp); }
    if (_t1172) {
        Bool _t1109; { Bool *_hp = TokenType_is_KwElse(other); _t1109 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1109; return _r; }
    }
    ;
    Bool _t1173; { Bool *_hp = TokenType_is_KwWhile(self); _t1173 = *_hp; free(_hp); }
    if (_t1173) {
        Bool _t1110; { Bool *_hp = TokenType_is_KwWhile(other); _t1110 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1110; return _r; }
    }
    ;
    Bool _t1174; { Bool *_hp = TokenType_is_KwFor(self); _t1174 = *_hp; free(_hp); }
    if (_t1174) {
        Bool _t1111; { Bool *_hp = TokenType_is_KwFor(other); _t1111 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1111; return _r; }
    }
    ;
    Bool _t1175; { Bool *_hp = TokenType_is_KwIn(self); _t1175 = *_hp; free(_hp); }
    if (_t1175) {
        Bool _t1112; { Bool *_hp = TokenType_is_KwIn(other); _t1112 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1112; return _r; }
    }
    ;
    Bool _t1176; { Bool *_hp = TokenType_is_KwSwitch(self); _t1176 = *_hp; free(_hp); }
    if (_t1176) {
        Bool _t1113; { Bool *_hp = TokenType_is_KwSwitch(other); _t1113 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1113; return _r; }
    }
    ;
    Bool _t1177; { Bool *_hp = TokenType_is_KwMatch(self); _t1177 = *_hp; free(_hp); }
    if (_t1177) {
        Bool _t1114; { Bool *_hp = TokenType_is_KwMatch(other); _t1114 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1114; return _r; }
    }
    ;
    Bool _t1178; { Bool *_hp = TokenType_is_KwCase(self); _t1178 = *_hp; free(_hp); }
    if (_t1178) {
        Bool _t1115; { Bool *_hp = TokenType_is_KwCase(other); _t1115 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1115; return _r; }
    }
    ;
    Bool _t1179; { Bool *_hp = TokenType_is_KwDefault(self); _t1179 = *_hp; free(_hp); }
    if (_t1179) {
        Bool _t1116; { Bool *_hp = TokenType_is_KwDefault(other); _t1116 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1116; return _r; }
    }
    ;
    Bool _t1180; { Bool *_hp = TokenType_is_KwReturn(self); _t1180 = *_hp; free(_hp); }
    if (_t1180) {
        Bool _t1117; { Bool *_hp = TokenType_is_KwReturn(other); _t1117 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1117; return _r; }
    }
    ;
    Bool _t1181; { Bool *_hp = TokenType_is_KwThrow(self); _t1181 = *_hp; free(_hp); }
    if (_t1181) {
        Bool _t1118; { Bool *_hp = TokenType_is_KwThrow(other); _t1118 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1118; return _r; }
    }
    ;
    Bool _t1182; { Bool *_hp = TokenType_is_KwCatch(self); _t1182 = *_hp; free(_hp); }
    if (_t1182) {
        Bool _t1119; { Bool *_hp = TokenType_is_KwCatch(other); _t1119 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1119; return _r; }
    }
    ;
    Bool _t1183; { Bool *_hp = TokenType_is_KwBreak(self); _t1183 = *_hp; free(_hp); }
    if (_t1183) {
        Bool _t1120; { Bool *_hp = TokenType_is_KwBreak(other); _t1120 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1120; return _r; }
    }
    ;
    Bool _t1184; { Bool *_hp = TokenType_is_KwContinue(self); _t1184 = *_hp; free(_hp); }
    if (_t1184) {
        Bool _t1121; { Bool *_hp = TokenType_is_KwContinue(other); _t1121 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1121; return _r; }
    }
    ;
    Bool _t1185; { Bool *_hp = TokenType_is_KwDefer(self); _t1185 = *_hp; free(_hp); }
    if (_t1185) {
        Bool _t1122; { Bool *_hp = TokenType_is_KwDefer(other); _t1122 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1122; return _r; }
    }
    ;
    Bool _t1186; { Bool *_hp = TokenType_is_KwTrue(self); _t1186 = *_hp; free(_hp); }
    if (_t1186) {
        Bool _t1123; { Bool *_hp = TokenType_is_KwTrue(other); _t1123 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1123; return _r; }
    }
    ;
    Bool _t1187; { Bool *_hp = TokenType_is_KwFalse(self); _t1187 = *_hp; free(_hp); }
    if (_t1187) {
        Bool _t1124; { Bool *_hp = TokenType_is_KwFalse(other); _t1124 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1124; return _r; }
    }
    ;
    Bool _t1188; { Bool *_hp = TokenType_is_Error(self); _t1188 = *_hp; free(_hp); }
    if (_t1188) {
        Bool _t1125; { Bool *_hp = TokenType_is_Error(other); _t1125 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1125; return _r; }
    }
    ;
    Bool _t1189 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1189; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1190; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1190 = *_hp; free(_hp); }
    if (_t1190) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1191; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1191 = *_hp; free(_hp); }
    if (_t1191) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1192; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1192 = *_hp; free(_hp); }
    if (_t1192) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1193; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1193 = *_hp; free(_hp); }
    if (_t1193) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1194; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1194 = *_hp; free(_hp); }
    if (_t1194) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1195; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1195 = *_hp; free(_hp); }
    if (_t1195) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1196; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1196 = *_hp; free(_hp); }
    if (_t1196) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1197; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1197 = *_hp; free(_hp); }
    if (_t1197) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1198; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1198 = *_hp; free(_hp); }
    if (_t1198) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1199; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1199 = *_hp; free(_hp); }
    if (_t1199) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1200; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1200 = *_hp; free(_hp); }
    if (_t1200) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1201; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1201 = *_hp; free(_hp); }
    if (_t1201) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1202; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1202 = *_hp; free(_hp); }
    if (_t1202) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1203; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1203 = *_hp; free(_hp); }
    if (_t1203) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1204; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1204 = *_hp; free(_hp); }
    if (_t1204) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1205; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1205 = *_hp; free(_hp); }
    if (_t1205) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1206; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1206 = *_hp; free(_hp); }
    if (_t1206) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1207; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1207 = *_hp; free(_hp); }
    if (_t1207) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1208; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1208 = *_hp; free(_hp); }
    if (_t1208) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1209; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1209 = *_hp; free(_hp); }
    if (_t1209) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1210; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1210 = *_hp; free(_hp); }
    if (_t1210) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1211; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1211 = *_hp; free(_hp); }
    if (_t1211) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1212; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1212 = *_hp; free(_hp); }
    if (_t1212) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1213; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1213 = *_hp; free(_hp); }
    if (_t1213) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1214; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1214 = *_hp; free(_hp); }
    if (_t1214) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1215; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1215 = *_hp; free(_hp); }
    if (_t1215) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1216; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1216 = *_hp; free(_hp); }
    if (_t1216) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1217; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1217 = *_hp; free(_hp); }
    if (_t1217) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1218; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1218 = *_hp; free(_hp); }
    if (_t1218) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1219; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1219 = *_hp; free(_hp); }
    if (_t1219) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1220; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1220 = *_hp; free(_hp); }
    if (_t1220) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1221; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1221 = *_hp; free(_hp); }
    if (_t1221) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1222; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1222 = *_hp; free(_hp); }
    if (_t1222) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1223; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1223 = *_hp; free(_hp); }
    if (_t1223) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1224; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1224 = *_hp; free(_hp); }
    if (_t1224) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1225; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1225 = *_hp; free(_hp); }
    if (_t1225) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1226; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1226 = *_hp; free(_hp); }
    if (_t1226) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1227; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1227 = *_hp; free(_hp); }
    if (_t1227) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1228; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1228 = *_hp; free(_hp); }
    if (_t1228) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1229; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1229 = *_hp; free(_hp); }
    if (_t1229) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1230; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1230 = *_hp; free(_hp); }
    if (_t1230) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1231; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1231 = *_hp; free(_hp); }
    if (_t1231) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1232; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1232 = *_hp; free(_hp); }
    if (_t1232) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1233; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1233 = *_hp; free(_hp); }
    if (_t1233) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1234; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1234 = *_hp; free(_hp); }
    if (_t1234) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1235; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1235 = *_hp; free(_hp); }
    if (_t1235) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1236; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1236 = *_hp; free(_hp); }
    if (_t1236) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1237; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1237 = *_hp; free(_hp); }
    if (_t1237) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1238; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1238 = *_hp; free(_hp); }
    if (_t1238) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1239; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1239 = *_hp; free(_hp); }
    if (_t1239) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1240; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1240 = *_hp; free(_hp); }
    if (_t1240) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1241; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1241 = *_hp; free(_hp); }
    if (_t1241) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1242; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1242 = *_hp; free(_hp); }
    if (_t1242) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1243; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1243 = *_hp; free(_hp); }
    if (_t1243) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1244; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1244 = *_hp; free(_hp); }
    if (_t1244) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1245; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1245 = *_hp; free(_hp); }
    if (_t1245) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1246; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1246 = *_hp; free(_hp); }
    if (_t1246) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1247; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1247 = *_hp; free(_hp); }
    if (_t1247) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1248; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1248 = *_hp; free(_hp); }
    if (_t1248) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1249; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1249 = *_hp; free(_hp); }
    if (_t1249) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1250; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1250 = *_hp; free(_hp); }
    if (_t1250) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1251; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1251 = *_hp; free(_hp); }
    if (_t1251) {
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
    Bool _t1315; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1315 = *_hp; free(_hp); }
    if (_t1315) {
        Str *_t1252 = Str_lit("Eof", 3ULL);
        ;
        return _t1252;
    }
    ;
    Bool _t1316; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1316 = *_hp; free(_hp); }
    if (_t1316) {
        Str *_t1253 = Str_lit("LParen", 6ULL);
        ;
        return _t1253;
    }
    ;
    Bool _t1317; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1317 = *_hp; free(_hp); }
    if (_t1317) {
        Str *_t1254 = Str_lit("RParen", 6ULL);
        ;
        return _t1254;
    }
    ;
    Bool _t1318; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1318 = *_hp; free(_hp); }
    if (_t1318) {
        Str *_t1255 = Str_lit("LBrace", 6ULL);
        ;
        return _t1255;
    }
    ;
    Bool _t1319; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1319 = *_hp; free(_hp); }
    if (_t1319) {
        Str *_t1256 = Str_lit("RBrace", 6ULL);
        ;
        return _t1256;
    }
    ;
    Bool _t1320; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1320 = *_hp; free(_hp); }
    if (_t1320) {
        Str *_t1257 = Str_lit("LBracket", 8ULL);
        ;
        return _t1257;
    }
    ;
    Bool _t1321; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1321 = *_hp; free(_hp); }
    if (_t1321) {
        Str *_t1258 = Str_lit("RBracket", 8ULL);
        ;
        return _t1258;
    }
    ;
    Bool _t1322; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1322 = *_hp; free(_hp); }
    if (_t1322) {
        Str *_t1259 = Str_lit("Comma", 5ULL);
        ;
        return _t1259;
    }
    ;
    Bool _t1323; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1323 = *_hp; free(_hp); }
    if (_t1323) {
        Str *_t1260 = Str_lit("Colon", 5ULL);
        ;
        return _t1260;
    }
    ;
    Bool _t1324; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1324 = *_hp; free(_hp); }
    if (_t1324) {
        Str *_t1261 = Str_lit("Question", 8ULL);
        ;
        return _t1261;
    }
    ;
    Bool _t1325; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1325 = *_hp; free(_hp); }
    if (_t1325) {
        Str *_t1262 = Str_lit("Bang", 4ULL);
        ;
        return _t1262;
    }
    ;
    Bool _t1326; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1326 = *_hp; free(_hp); }
    if (_t1326) {
        Str *_t1263 = Str_lit("Minus", 5ULL);
        ;
        return _t1263;
    }
    ;
    Bool _t1327; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1327 = *_hp; free(_hp); }
    if (_t1327) {
        Str *_t1264 = Str_lit("Plus", 4ULL);
        ;
        return _t1264;
    }
    ;
    Bool _t1328; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1328 = *_hp; free(_hp); }
    if (_t1328) {
        Str *_t1265 = Str_lit("Star", 4ULL);
        ;
        return _t1265;
    }
    ;
    Bool _t1329; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1329 = *_hp; free(_hp); }
    if (_t1329) {
        Str *_t1266 = Str_lit("Slash", 5ULL);
        ;
        return _t1266;
    }
    ;
    Bool _t1330; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1330 = *_hp; free(_hp); }
    if (_t1330) {
        Str *_t1267 = Str_lit("Dot", 3ULL);
        ;
        return _t1267;
    }
    ;
    Bool _t1331; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1331 = *_hp; free(_hp); }
    if (_t1331) {
        Str *_t1268 = Str_lit("DotDot", 6ULL);
        ;
        return _t1268;
    }
    ;
    Bool _t1332; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1332 = *_hp; free(_hp); }
    if (_t1332) {
        Str *_t1269 = Str_lit("Eq", 2ULL);
        ;
        return _t1269;
    }
    ;
    Bool _t1333; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1333 = *_hp; free(_hp); }
    if (_t1333) {
        Str *_t1270 = Str_lit("EqEq", 4ULL);
        ;
        return _t1270;
    }
    ;
    Bool _t1334; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1334 = *_hp; free(_hp); }
    if (_t1334) {
        Str *_t1271 = Str_lit("Neq", 3ULL);
        ;
        return _t1271;
    }
    ;
    Bool _t1335; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1335 = *_hp; free(_hp); }
    if (_t1335) {
        Str *_t1272 = Str_lit("Lt", 2ULL);
        ;
        return _t1272;
    }
    ;
    Bool _t1336; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1336 = *_hp; free(_hp); }
    if (_t1336) {
        Str *_t1273 = Str_lit("LtEq", 4ULL);
        ;
        return _t1273;
    }
    ;
    Bool _t1337; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1337 = *_hp; free(_hp); }
    if (_t1337) {
        Str *_t1274 = Str_lit("Gt", 2ULL);
        ;
        return _t1274;
    }
    ;
    Bool _t1338; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1338 = *_hp; free(_hp); }
    if (_t1338) {
        Str *_t1275 = Str_lit("GtEq", 4ULL);
        ;
        return _t1275;
    }
    ;
    Bool _t1339; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1339 = *_hp; free(_hp); }
    if (_t1339) {
        Str *_t1276 = Str_lit("ColonEq", 7ULL);
        ;
        return _t1276;
    }
    ;
    Bool _t1340; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1340 = *_hp; free(_hp); }
    if (_t1340) {
        Str *_t1277 = Str_lit("Ident", 5ULL);
        ;
        return _t1277;
    }
    ;
    Bool _t1341; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1341 = *_hp; free(_hp); }
    if (_t1341) {
        Str *_t1278 = Str_lit("StringTok", 9ULL);
        ;
        return _t1278;
    }
    ;
    Bool _t1342; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1342 = *_hp; free(_hp); }
    if (_t1342) {
        Str *_t1279 = Str_lit("Number", 6ULL);
        ;
        return _t1279;
    }
    ;
    Bool _t1343; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1343 = *_hp; free(_hp); }
    if (_t1343) {
        Str *_t1280 = Str_lit("Char", 4ULL);
        ;
        return _t1280;
    }
    ;
    Bool _t1344; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1344 = *_hp; free(_hp); }
    if (_t1344) {
        Str *_t1281 = Str_lit("KwMode", 6ULL);
        ;
        return _t1281;
    }
    ;
    Bool _t1345; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1345 = *_hp; free(_hp); }
    if (_t1345) {
        Str *_t1282 = Str_lit("KwMut", 5ULL);
        ;
        return _t1282;
    }
    ;
    Bool _t1346; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1346 = *_hp; free(_hp); }
    if (_t1346) {
        Str *_t1283 = Str_lit("KwOwn", 5ULL);
        ;
        return _t1283;
    }
    ;
    Bool _t1347; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1347 = *_hp; free(_hp); }
    if (_t1347) {
        Str *_t1284 = Str_lit("KwRef", 5ULL);
        ;
        return _t1284;
    }
    ;
    Bool _t1348; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1348 = *_hp; free(_hp); }
    if (_t1348) {
        Str *_t1285 = Str_lit("KwStruct", 8ULL);
        ;
        return _t1285;
    }
    ;
    Bool _t1349; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1349 = *_hp; free(_hp); }
    if (_t1349) {
        Str *_t1286 = Str_lit("KwExtStruct", 11ULL);
        ;
        return _t1286;
    }
    ;
    Bool _t1350; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1350 = *_hp; free(_hp); }
    if (_t1350) {
        Str *_t1287 = Str_lit("KwEnum", 6ULL);
        ;
        return _t1287;
    }
    ;
    Bool _t1351; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1351 = *_hp; free(_hp); }
    if (_t1351) {
        Str *_t1288 = Str_lit("KwNamespace", 11ULL);
        ;
        return _t1288;
    }
    ;
    Bool _t1352; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1352 = *_hp; free(_hp); }
    if (_t1352) {
        Str *_t1289 = Str_lit("KwFunc", 6ULL);
        ;
        return _t1289;
    }
    ;
    Bool _t1353; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1353 = *_hp; free(_hp); }
    if (_t1353) {
        Str *_t1290 = Str_lit("KwProc", 6ULL);
        ;
        return _t1290;
    }
    ;
    Bool _t1354; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1354 = *_hp; free(_hp); }
    if (_t1354) {
        Str *_t1291 = Str_lit("KwTest", 6ULL);
        ;
        return _t1291;
    }
    ;
    Bool _t1355; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1355 = *_hp; free(_hp); }
    if (_t1355) {
        Str *_t1292 = Str_lit("KwMacro", 7ULL);
        ;
        return _t1292;
    }
    ;
    Bool _t1356; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1356 = *_hp; free(_hp); }
    if (_t1356) {
        Str *_t1293 = Str_lit("KwExtFunc", 9ULL);
        ;
        return _t1293;
    }
    ;
    Bool _t1357; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1357 = *_hp; free(_hp); }
    if (_t1357) {
        Str *_t1294 = Str_lit("KwExtProc", 9ULL);
        ;
        return _t1294;
    }
    ;
    Bool _t1358; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1358 = *_hp; free(_hp); }
    if (_t1358) {
        Str *_t1295 = Str_lit("KwReturns", 9ULL);
        ;
        return _t1295;
    }
    ;
    Bool _t1359; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1359 = *_hp; free(_hp); }
    if (_t1359) {
        Str *_t1296 = Str_lit("KwThrows", 8ULL);
        ;
        return _t1296;
    }
    ;
    Bool _t1360; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1360 = *_hp; free(_hp); }
    if (_t1360) {
        Str *_t1297 = Str_lit("KwIf", 4ULL);
        ;
        return _t1297;
    }
    ;
    Bool _t1361; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1361 = *_hp; free(_hp); }
    if (_t1361) {
        Str *_t1298 = Str_lit("KwElse", 6ULL);
        ;
        return _t1298;
    }
    ;
    Bool _t1362; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1362 = *_hp; free(_hp); }
    if (_t1362) {
        Str *_t1299 = Str_lit("KwWhile", 7ULL);
        ;
        return _t1299;
    }
    ;
    Bool _t1363; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1363 = *_hp; free(_hp); }
    if (_t1363) {
        Str *_t1300 = Str_lit("KwFor", 5ULL);
        ;
        return _t1300;
    }
    ;
    Bool _t1364; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1364 = *_hp; free(_hp); }
    if (_t1364) {
        Str *_t1301 = Str_lit("KwIn", 4ULL);
        ;
        return _t1301;
    }
    ;
    Bool _t1365; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1365 = *_hp; free(_hp); }
    if (_t1365) {
        Str *_t1302 = Str_lit("KwSwitch", 8ULL);
        ;
        return _t1302;
    }
    ;
    Bool _t1366; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1366 = *_hp; free(_hp); }
    if (_t1366) {
        Str *_t1303 = Str_lit("KwMatch", 7ULL);
        ;
        return _t1303;
    }
    ;
    Bool _t1367; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1367 = *_hp; free(_hp); }
    if (_t1367) {
        Str *_t1304 = Str_lit("KwCase", 6ULL);
        ;
        return _t1304;
    }
    ;
    Bool _t1368; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1368 = *_hp; free(_hp); }
    if (_t1368) {
        Str *_t1305 = Str_lit("KwDefault", 9ULL);
        ;
        return _t1305;
    }
    ;
    Bool _t1369; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1369 = *_hp; free(_hp); }
    if (_t1369) {
        Str *_t1306 = Str_lit("KwReturn", 8ULL);
        ;
        return _t1306;
    }
    ;
    Bool _t1370; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1370 = *_hp; free(_hp); }
    if (_t1370) {
        Str *_t1307 = Str_lit("KwThrow", 7ULL);
        ;
        return _t1307;
    }
    ;
    Bool _t1371; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1371 = *_hp; free(_hp); }
    if (_t1371) {
        Str *_t1308 = Str_lit("KwCatch", 7ULL);
        ;
        return _t1308;
    }
    ;
    Bool _t1372; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1372 = *_hp; free(_hp); }
    if (_t1372) {
        Str *_t1309 = Str_lit("KwBreak", 7ULL);
        ;
        return _t1309;
    }
    ;
    Bool _t1373; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1373 = *_hp; free(_hp); }
    if (_t1373) {
        Str *_t1310 = Str_lit("KwContinue", 10ULL);
        ;
        return _t1310;
    }
    ;
    Bool _t1374; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1374 = *_hp; free(_hp); }
    if (_t1374) {
        Str *_t1311 = Str_lit("KwDefer", 7ULL);
        ;
        return _t1311;
    }
    ;
    Bool _t1375; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1375 = *_hp; free(_hp); }
    if (_t1375) {
        Str *_t1312 = Str_lit("KwTrue", 6ULL);
        ;
        return _t1312;
    }
    ;
    Bool _t1376; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1376 = *_hp; free(_hp); }
    if (_t1376) {
        Str *_t1313 = Str_lit("KwFalse", 7ULL);
        ;
        return _t1313;
    }
    ;
    Bool _t1377; { Bool *_hp = TokenType_eq(self, TokenType_Error()); _t1377 = *_hp; free(_hp); }
    if (_t1377) {
        Str *_t1314 = Str_lit("Error", 5ULL);
        ;
        return _t1314;
    }
    ;
    Str *_t1378 = Str_lit("unknown", 7ULL);
    return _t1378;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1380 = I64_clone(&self->line);
    I64 _t1381 = I64_clone(&self->col);
    Token *_t1382 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1382->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1382->text = *_ca; free(_ca); }
    _t1382->line = _t1380;
    _t1382->col = _t1381;
    ;
    ;
    return _t1382;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    Bool _t1383 = 0;
    TokenType_delete(&self->type, &(Bool){_t1383});
    ;
    Bool _t1384 = 0;
    Str_delete(&self->text, &(Bool){_t1384});
    ;
    Bool _t1385 = 0;
    I64_delete(&self->line, &(Bool){_t1385});
    ;
    Bool _t1386 = 0;
    I64_delete(&self->col, &(Bool){_t1386});
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
    U8 _t1388 = 48;
    U8 _t1389 = 57;
    Bool _t1390; { Bool *_hp = U8_gte(c, &(U8){_t1388}); _t1390 = *_hp; free(_hp); }
    ;
    Bool _t1391; { Bool *_hp = U8_lte(c, &(U8){_t1389}); _t1391 = *_hp; free(_hp); }
    ;
    Bool _t1392 = Bool_and(_t1390, _t1391);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1392; return _r; }
}

Bool * is_alpha(U8 * c) {
    U8 _t1393 = 97;
    U8 _t1394 = 122;
    Bool _t1395; { Bool *_hp = U8_gte(c, &(U8){_t1393}); _t1395 = *_hp; free(_hp); }
    ;
    Bool _t1396; { Bool *_hp = U8_lte(c, &(U8){_t1394}); _t1396 = *_hp; free(_hp); }
    ;
    U8 _t1397 = 65;
    U8 _t1398 = 90;
    Bool _t1399; { Bool *_hp = U8_gte(c, &(U8){_t1397}); _t1399 = *_hp; free(_hp); }
    ;
    Bool _t1400; { Bool *_hp = U8_lte(c, &(U8){_t1398}); _t1400 = *_hp; free(_hp); }
    ;
    Bool _t1401 = Bool_and(_t1395, _t1396);
    ;
    ;
    Bool _t1402 = Bool_and(_t1399, _t1400);
    ;
    ;
    U8 _t1403 = 95;
    Bool _t1404 = Bool_or(_t1401, _t1402);
    ;
    ;
    Bool _t1405 = U8_eq(DEREF(c), _t1403);
    ;
    Bool _t1406 = Bool_or(_t1404, _t1405);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1406; return _r; }
}

Bool * is_alnum(U8 * c) {
    Bool _t1407; { Bool *_hp = is_alpha(c); _t1407 = *_hp; free(_hp); }
    Bool _t1408; { Bool *_hp = is_digit(c); _t1408 = *_hp; free(_hp); }
    Bool _t1409 = Bool_or(_t1407, _t1408);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1409; return _r; }
}

Str * tok_name(TokenType * type) {
    {
        TokenType *_sw1410 = TokenType_clone(type);
        Bool _t1537; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Eof()); _t1537 = *_hp; free(_hp); }
        if (_t1537) {
            Str *_t1411 = Str_lit("eof", 3ULL);
            TokenType_delete(_sw1410, &(Bool){1});
            ;
            return _t1411;
        } else {
            Bool _t1536; { Bool *_hp = TokenType_eq(_sw1410, TokenType_LParen()); _t1536 = *_hp; free(_hp); }
            if (_t1536) {
                Str *_t1412 = Str_lit("(", 1ULL);
                ;
                TokenType_delete(_sw1410, &(Bool){1});
                ;
                return _t1412;
            } else {
                Bool _t1535; { Bool *_hp = TokenType_eq(_sw1410, TokenType_RParen()); _t1535 = *_hp; free(_hp); }
                if (_t1535) {
                    Str *_t1413 = Str_lit(")", 1ULL);
                    ;
                    ;
                    TokenType_delete(_sw1410, &(Bool){1});
                    ;
                    return _t1413;
                } else {
                    Bool _t1534; { Bool *_hp = TokenType_eq(_sw1410, TokenType_LBrace()); _t1534 = *_hp; free(_hp); }
                    if (_t1534) {
                        Str *_t1414 = Str_lit("{", 1ULL);
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1410, &(Bool){1});
                        ;
                        return _t1414;
                    } else {
                        Bool _t1533; { Bool *_hp = TokenType_eq(_sw1410, TokenType_RBrace()); _t1533 = *_hp; free(_hp); }
                        if (_t1533) {
                            Str *_t1415 = Str_lit("}", 1ULL);
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1410, &(Bool){1});
                            ;
                            return _t1415;
                        } else {
                            Bool _t1532; { Bool *_hp = TokenType_eq(_sw1410, TokenType_LBracket()); _t1532 = *_hp; free(_hp); }
                            if (_t1532) {
                                Str *_t1416 = Str_lit("[", 1ULL);
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1410, &(Bool){1});
                                ;
                                return _t1416;
                            } else {
                                Bool _t1531; { Bool *_hp = TokenType_eq(_sw1410, TokenType_RBracket()); _t1531 = *_hp; free(_hp); }
                                if (_t1531) {
                                    Str *_t1417 = Str_lit("]", 1ULL);
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1410, &(Bool){1});
                                    ;
                                    return _t1417;
                                } else {
                                    Bool _t1530; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Comma()); _t1530 = *_hp; free(_hp); }
                                    if (_t1530) {
                                        Str *_t1418 = Str_lit(",", 1ULL);
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1410, &(Bool){1});
                                        ;
                                        return _t1418;
                                    } else {
                                        Bool _t1529; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Colon()); _t1529 = *_hp; free(_hp); }
                                        if (_t1529) {
                                            Str *_t1419 = Str_lit(":", 1ULL);
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1410, &(Bool){1});
                                            ;
                                            return _t1419;
                                        } else {
                                            Bool _t1528; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Question()); _t1528 = *_hp; free(_hp); }
                                            if (_t1528) {
                                                Str *_t1420 = Str_lit("?", 1ULL);
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1410, &(Bool){1});
                                                ;
                                                return _t1420;
                                            } else {
                                                Bool _t1527; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Bang()); _t1527 = *_hp; free(_hp); }
                                                if (_t1527) {
                                                    Str *_t1421 = Str_lit("!", 1ULL);
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                    ;
                                                    return _t1421;
                                                } else {
                                                    Bool _t1526; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Minus()); _t1526 = *_hp; free(_hp); }
                                                    if (_t1526) {
                                                        Str *_t1422 = Str_lit("-", 1ULL);
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                        ;
                                                        return _t1422;
                                                    } else {
                                                        Bool _t1525; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Plus()); _t1525 = *_hp; free(_hp); }
                                                        if (_t1525) {
                                                            Str *_t1423 = Str_lit("+", 1ULL);
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                            ;
                                                            return _t1423;
                                                        } else {
                                                            Bool _t1524; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Star()); _t1524 = *_hp; free(_hp); }
                                                            if (_t1524) {
                                                                Str *_t1424 = Str_lit("*", 1ULL);
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                ;
                                                                return _t1424;
                                                            } else {
                                                                Bool _t1523; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Slash()); _t1523 = *_hp; free(_hp); }
                                                                if (_t1523) {
                                                                    Str *_t1425 = Str_lit("/", 1ULL);
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                    ;
                                                                    return _t1425;
                                                                } else {
                                                                    Bool _t1522; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Dot()); _t1522 = *_hp; free(_hp); }
                                                                    if (_t1522) {
                                                                        Str *_t1426 = Str_lit(".", 1ULL);
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                        ;
                                                                        return _t1426;
                                                                    } else {
                                                                        Bool _t1521; { Bool *_hp = TokenType_eq(_sw1410, TokenType_DotDot()); _t1521 = *_hp; free(_hp); }
                                                                        if (_t1521) {
                                                                            Str *_t1427 = Str_lit("..", 2ULL);
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                            ;
                                                                            return _t1427;
                                                                        } else {
                                                                            Bool _t1520; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Eq()); _t1520 = *_hp; free(_hp); }
                                                                            if (_t1520) {
                                                                                Str *_t1428 = Str_lit("=", 1ULL);
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                ;
                                                                                return _t1428;
                                                                            } else {
                                                                                Bool _t1519; { Bool *_hp = TokenType_eq(_sw1410, TokenType_EqEq()); _t1519 = *_hp; free(_hp); }
                                                                                if (_t1519) {
                                                                                    Str *_t1429 = Str_lit("==", 2ULL);
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                    ;
                                                                                    return _t1429;
                                                                                } else {
                                                                                    Bool _t1518; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Neq()); _t1518 = *_hp; free(_hp); }
                                                                                    if (_t1518) {
                                                                                        Str *_t1430 = Str_lit("!=", 2ULL);
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                        ;
                                                                                        return _t1430;
                                                                                    } else {
                                                                                        Bool _t1517; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Lt()); _t1517 = *_hp; free(_hp); }
                                                                                        if (_t1517) {
                                                                                            Str *_t1431 = Str_lit("<", 1ULL);
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                            ;
                                                                                            return _t1431;
                                                                                        } else {
                                                                                            Bool _t1516; { Bool *_hp = TokenType_eq(_sw1410, TokenType_LtEq()); _t1516 = *_hp; free(_hp); }
                                                                                            if (_t1516) {
                                                                                                Str *_t1432 = Str_lit("<=", 2ULL);
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                ;
                                                                                                return _t1432;
                                                                                            } else {
                                                                                                Bool _t1515; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Gt()); _t1515 = *_hp; free(_hp); }
                                                                                                if (_t1515) {
                                                                                                    Str *_t1433 = Str_lit(">", 1ULL);
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1433;
                                                                                                } else {
                                                                                                    Bool _t1514; { Bool *_hp = TokenType_eq(_sw1410, TokenType_GtEq()); _t1514 = *_hp; free(_hp); }
                                                                                                    if (_t1514) {
                                                                                                        Str *_t1434 = Str_lit(">=", 2ULL);
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1434;
                                                                                                    } else {
                                                                                                        Bool _t1513; { Bool *_hp = TokenType_eq(_sw1410, TokenType_ColonEq()); _t1513 = *_hp; free(_hp); }
                                                                                                        if (_t1513) {
                                                                                                            Str *_t1435 = Str_lit(":=", 2ULL);
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1435;
                                                                                                        } else {
                                                                                                            Bool _t1512; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Ident()); _t1512 = *_hp; free(_hp); }
                                                                                                            if (_t1512) {
                                                                                                                Str *_t1436 = Str_lit("identifier", 10ULL);
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1436;
                                                                                                            } else {
                                                                                                                Bool _t1511; { Bool *_hp = TokenType_eq(_sw1410, TokenType_StringTok()); _t1511 = *_hp; free(_hp); }
                                                                                                                if (_t1511) {
                                                                                                                    Str *_t1437 = Str_lit("string", 6ULL);
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1437;
                                                                                                                } else {
                                                                                                                    Bool _t1510; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Number()); _t1510 = *_hp; free(_hp); }
                                                                                                                    if (_t1510) {
                                                                                                                        Str *_t1438 = Str_lit("number", 6ULL);
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1438;
                                                                                                                    } else {
                                                                                                                        Bool _t1509; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Char()); _t1509 = *_hp; free(_hp); }
                                                                                                                        if (_t1509) {
                                                                                                                            Str *_t1439 = Str_lit("char", 4ULL);
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1439;
                                                                                                                        } else {
                                                                                                                            Bool _t1508; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwMode()); _t1508 = *_hp; free(_hp); }
                                                                                                                            if (_t1508) {
                                                                                                                                Str *_t1440 = Str_lit("mode", 4ULL);
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1440;
                                                                                                                            } else {
                                                                                                                                Bool _t1507; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwMut()); _t1507 = *_hp; free(_hp); }
                                                                                                                                if (_t1507) {
                                                                                                                                    Str *_t1441 = Str_lit("mut", 3ULL);
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1441;
                                                                                                                                } else {
                                                                                                                                    Bool _t1506; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwOwn()); _t1506 = *_hp; free(_hp); }
                                                                                                                                    if (_t1506) {
                                                                                                                                        Str *_t1442 = Str_lit("own", 3ULL);
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1442;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1505; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwRef()); _t1505 = *_hp; free(_hp); }
                                                                                                                                        if (_t1505) {
                                                                                                                                            Str *_t1443 = Str_lit("ref", 3ULL);
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1443;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1504; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwStruct()); _t1504 = *_hp; free(_hp); }
                                                                                                                                            if (_t1504) {
                                                                                                                                                Str *_t1444 = Str_lit("struct", 6ULL);
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1444;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1503; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwExtStruct()); _t1503 = *_hp; free(_hp); }
                                                                                                                                                if (_t1503) {
                                                                                                                                                    Str *_t1445 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1445;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1502; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwEnum()); _t1502 = *_hp; free(_hp); }
                                                                                                                                                    if (_t1502) {
                                                                                                                                                        Str *_t1446 = Str_lit("enum", 4ULL);
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1446;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1501; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwNamespace()); _t1501 = *_hp; free(_hp); }
                                                                                                                                                        if (_t1501) {
                                                                                                                                                            Str *_t1447 = Str_lit("namespace", 9ULL);
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1447;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1500; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwFunc()); _t1500 = *_hp; free(_hp); }
                                                                                                                                                            if (_t1500) {
                                                                                                                                                                Str *_t1448 = Str_lit("func", 4ULL);
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1448;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1499; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwProc()); _t1499 = *_hp; free(_hp); }
                                                                                                                                                                if (_t1499) {
                                                                                                                                                                    Str *_t1449 = Str_lit("proc", 4ULL);
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1449;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1498; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwTest()); _t1498 = *_hp; free(_hp); }
                                                                                                                                                                    if (_t1498) {
                                                                                                                                                                        Str *_t1450 = Str_lit("test", 4ULL);
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1450;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1497; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwMacro()); _t1497 = *_hp; free(_hp); }
                                                                                                                                                                        if (_t1497) {
                                                                                                                                                                            Str *_t1451 = Str_lit("macro", 5ULL);
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1451;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1496; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwExtFunc()); _t1496 = *_hp; free(_hp); }
                                                                                                                                                                            if (_t1496) {
                                                                                                                                                                                Str *_t1452 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1452;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1495; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwExtProc()); _t1495 = *_hp; free(_hp); }
                                                                                                                                                                                if (_t1495) {
                                                                                                                                                                                    Str *_t1453 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1453;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1494; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwReturns()); _t1494 = *_hp; free(_hp); }
                                                                                                                                                                                    if (_t1494) {
                                                                                                                                                                                        Str *_t1454 = Str_lit("returns", 7ULL);
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1454;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1493; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwThrows()); _t1493 = *_hp; free(_hp); }
                                                                                                                                                                                        if (_t1493) {
                                                                                                                                                                                            Str *_t1455 = Str_lit("throws", 6ULL);
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1455;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1492; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwIf()); _t1492 = *_hp; free(_hp); }
                                                                                                                                                                                            if (_t1492) {
                                                                                                                                                                                                Str *_t1456 = Str_lit("if", 2ULL);
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1456;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1491; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwElse()); _t1491 = *_hp; free(_hp); }
                                                                                                                                                                                                if (_t1491) {
                                                                                                                                                                                                    Str *_t1457 = Str_lit("else", 4ULL);
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1457;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1490; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwWhile()); _t1490 = *_hp; free(_hp); }
                                                                                                                                                                                                    if (_t1490) {
                                                                                                                                                                                                        Str *_t1458 = Str_lit("while", 5ULL);
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1458;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1489; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwFor()); _t1489 = *_hp; free(_hp); }
                                                                                                                                                                                                        if (_t1489) {
                                                                                                                                                                                                            Str *_t1459 = Str_lit("for", 3ULL);
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1459;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1488; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwIn()); _t1488 = *_hp; free(_hp); }
                                                                                                                                                                                                            if (_t1488) {
                                                                                                                                                                                                                Str *_t1460 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1460;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1487; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwSwitch()); _t1487 = *_hp; free(_hp); }
                                                                                                                                                                                                                if (_t1487) {
                                                                                                                                                                                                                    Str *_t1461 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1461;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1486; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwMatch()); _t1486 = *_hp; free(_hp); }
                                                                                                                                                                                                                    if (_t1486) {
                                                                                                                                                                                                                        Str *_t1462 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1462;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1485; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwCase()); _t1485 = *_hp; free(_hp); }
                                                                                                                                                                                                                        if (_t1485) {
                                                                                                                                                                                                                            Str *_t1463 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1463;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1484; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwDefault()); _t1484 = *_hp; free(_hp); }
                                                                                                                                                                                                                            if (_t1484) {
                                                                                                                                                                                                                                Str *_t1464 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1464;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1483; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwReturn()); _t1483 = *_hp; free(_hp); }
                                                                                                                                                                                                                                if (_t1483) {
                                                                                                                                                                                                                                    Str *_t1465 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1465;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1482; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwThrow()); _t1482 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    if (_t1482) {
                                                                                                                                                                                                                                        Str *_t1466 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1466;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1481; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwCatch()); _t1481 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        if (_t1481) {
                                                                                                                                                                                                                                            Str *_t1467 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1467;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1480; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwBreak()); _t1480 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            if (_t1480) {
                                                                                                                                                                                                                                                Str *_t1468 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1468;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1479; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwContinue()); _t1479 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                if (_t1479) {
                                                                                                                                                                                                                                                    Str *_t1469 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1469;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1478; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwDefer()); _t1478 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    if (_t1478) {
                                                                                                                                                                                                                                                        Str *_t1470 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1470;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1477; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwTrue()); _t1477 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        if (_t1477) {
                                                                                                                                                                                                                                                            Str *_t1471 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1471;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1476; { Bool *_hp = TokenType_eq(_sw1410, TokenType_KwFalse()); _t1476 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            if (_t1476) {
                                                                                                                                                                                                                                                                Str *_t1472 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1472;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1475; { Bool *_hp = TokenType_eq(_sw1410, TokenType_Error()); _t1475 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                if (_t1475) {
                                                                                                                                                                                                                                                                    Str *_t1473 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1473;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Str *_t1474 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1410, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1474;
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
        TokenType_delete(_sw1410, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    {
        Str *_sw1538 = Str_clone(word);
        Str *_t1603 = Str_lit("mode", 4ULL);
        Bool _t1604; { Bool *_hp = Str_eq(_sw1538, _t1603); _t1604 = *_hp; free(_hp); }
        Str_delete(_t1603, &(Bool){1});
        if (_t1604) {
            Str_delete(_sw1538, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1601 = Str_lit("mut", 3ULL);
            Bool _t1602; { Bool *_hp = Str_eq(_sw1538, _t1601); _t1602 = *_hp; free(_hp); }
            Str_delete(_t1601, &(Bool){1});
            if (_t1602) {
                ;
                Str_delete(_sw1538, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1599 = Str_lit("own", 3ULL);
                Bool _t1600; { Bool *_hp = Str_eq(_sw1538, _t1599); _t1600 = *_hp; free(_hp); }
                Str_delete(_t1599, &(Bool){1});
                if (_t1600) {
                    ;
                    ;
                    Str_delete(_sw1538, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1597 = Str_lit("ref", 3ULL);
                    Bool _t1598; { Bool *_hp = Str_eq(_sw1538, _t1597); _t1598 = *_hp; free(_hp); }
                    Str_delete(_t1597, &(Bool){1});
                    if (_t1598) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1538, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1595 = Str_lit("struct", 6ULL);
                        Bool _t1596; { Bool *_hp = Str_eq(_sw1538, _t1595); _t1596 = *_hp; free(_hp); }
                        Str_delete(_t1595, &(Bool){1});
                        if (_t1596) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1538, &(Bool){1});
                            ;
                            return TokenType_KwStruct();
                        } else {
                            Str *_t1593 = Str_lit("ext_struct", 10ULL);
                            Bool _t1594; { Bool *_hp = Str_eq(_sw1538, _t1593); _t1594 = *_hp; free(_hp); }
                            Str_delete(_t1593, &(Bool){1});
                            if (_t1594) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1538, &(Bool){1});
                                ;
                                return TokenType_KwExtStruct();
                            } else {
                                Str *_t1591 = Str_lit("enum", 4ULL);
                                Bool _t1592; { Bool *_hp = Str_eq(_sw1538, _t1591); _t1592 = *_hp; free(_hp); }
                                Str_delete(_t1591, &(Bool){1});
                                if (_t1592) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1538, &(Bool){1});
                                    ;
                                    return TokenType_KwEnum();
                                } else {
                                    Str *_t1589 = Str_lit("namespace", 9ULL);
                                    Bool _t1590; { Bool *_hp = Str_eq(_sw1538, _t1589); _t1590 = *_hp; free(_hp); }
                                    Str_delete(_t1589, &(Bool){1});
                                    if (_t1590) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1538, &(Bool){1});
                                        ;
                                        return TokenType_KwNamespace();
                                    } else {
                                        Str *_t1587 = Str_lit("func", 4ULL);
                                        Bool _t1588; { Bool *_hp = Str_eq(_sw1538, _t1587); _t1588 = *_hp; free(_hp); }
                                        Str_delete(_t1587, &(Bool){1});
                                        if (_t1588) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1538, &(Bool){1});
                                            ;
                                            return TokenType_KwFunc();
                                        } else {
                                            Str *_t1585 = Str_lit("proc", 4ULL);
                                            Bool _t1586; { Bool *_hp = Str_eq(_sw1538, _t1585); _t1586 = *_hp; free(_hp); }
                                            Str_delete(_t1585, &(Bool){1});
                                            if (_t1586) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw1538, &(Bool){1});
                                                ;
                                                return TokenType_KwProc();
                                            } else {
                                                Str *_t1583 = Str_lit("test", 4ULL);
                                                Bool _t1584; { Bool *_hp = Str_eq(_sw1538, _t1583); _t1584 = *_hp; free(_hp); }
                                                Str_delete(_t1583, &(Bool){1});
                                                if (_t1584) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw1538, &(Bool){1});
                                                    ;
                                                    return TokenType_KwTest();
                                                } else {
                                                    Str *_t1581 = Str_lit("macro", 5ULL);
                                                    Bool _t1582; { Bool *_hp = Str_eq(_sw1538, _t1581); _t1582 = *_hp; free(_hp); }
                                                    Str_delete(_t1581, &(Bool){1});
                                                    if (_t1582) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw1538, &(Bool){1});
                                                        ;
                                                        return TokenType_KwMacro();
                                                    } else {
                                                        Str *_t1579 = Str_lit("ext_func", 8ULL);
                                                        Bool _t1580; { Bool *_hp = Str_eq(_sw1538, _t1579); _t1580 = *_hp; free(_hp); }
                                                        Str_delete(_t1579, &(Bool){1});
                                                        if (_t1580) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw1538, &(Bool){1});
                                                            ;
                                                            return TokenType_KwExtFunc();
                                                        } else {
                                                            Str *_t1577 = Str_lit("ext_proc", 8ULL);
                                                            Bool _t1578; { Bool *_hp = Str_eq(_sw1538, _t1577); _t1578 = *_hp; free(_hp); }
                                                            Str_delete(_t1577, &(Bool){1});
                                                            if (_t1578) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw1538, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtProc();
                                                            } else {
                                                                Str *_t1575 = Str_lit("returns", 7ULL);
                                                                Bool _t1576; { Bool *_hp = Str_eq(_sw1538, _t1575); _t1576 = *_hp; free(_hp); }
                                                                Str_delete(_t1575, &(Bool){1});
                                                                if (_t1576) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1538, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwReturns();
                                                                } else {
                                                                    Str *_t1573 = Str_lit("throws", 6ULL);
                                                                    Bool _t1574; { Bool *_hp = Str_eq(_sw1538, _t1573); _t1574 = *_hp; free(_hp); }
                                                                    Str_delete(_t1573, &(Bool){1});
                                                                    if (_t1574) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1538, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwThrows();
                                                                    } else {
                                                                        Str *_t1571 = Str_lit("if", 2ULL);
                                                                        Bool _t1572; { Bool *_hp = Str_eq(_sw1538, _t1571); _t1572 = *_hp; free(_hp); }
                                                                        Str_delete(_t1571, &(Bool){1});
                                                                        if (_t1572) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1538, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwIf();
                                                                        } else {
                                                                            Str *_t1569 = Str_lit("else", 4ULL);
                                                                            Bool _t1570; { Bool *_hp = Str_eq(_sw1538, _t1569); _t1570 = *_hp; free(_hp); }
                                                                            Str_delete(_t1569, &(Bool){1});
                                                                            if (_t1570) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1538, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwElse();
                                                                            } else {
                                                                                Str *_t1567 = Str_lit("while", 5ULL);
                                                                                Bool _t1568; { Bool *_hp = Str_eq(_sw1538, _t1567); _t1568 = *_hp; free(_hp); }
                                                                                Str_delete(_t1567, &(Bool){1});
                                                                                if (_t1568) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1538, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwWhile();
                                                                                } else {
                                                                                    Str *_t1565 = Str_lit("for", 3ULL);
                                                                                    Bool _t1566; { Bool *_hp = Str_eq(_sw1538, _t1565); _t1566 = *_hp; free(_hp); }
                                                                                    Str_delete(_t1565, &(Bool){1});
                                                                                    if (_t1566) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1538, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwFor();
                                                                                    } else {
                                                                                        Str *_t1563 = Str_lit("in", 2ULL);
                                                                                        Bool _t1564; { Bool *_hp = Str_eq(_sw1538, _t1563); _t1564 = *_hp; free(_hp); }
                                                                                        Str_delete(_t1563, &(Bool){1});
                                                                                        if (_t1564) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1538, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwIn();
                                                                                        } else {
                                                                                            Str *_t1561 = Str_lit("switch", 6ULL);
                                                                                            Bool _t1562; { Bool *_hp = Str_eq(_sw1538, _t1561); _t1562 = *_hp; free(_hp); }
                                                                                            Str_delete(_t1561, &(Bool){1});
                                                                                            if (_t1562) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1538, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwSwitch();
                                                                                            } else {
                                                                                                Str *_t1559 = Str_lit("match", 5ULL);
                                                                                                Bool _t1560; { Bool *_hp = Str_eq(_sw1538, _t1559); _t1560 = *_hp; free(_hp); }
                                                                                                Str_delete(_t1559, &(Bool){1});
                                                                                                if (_t1560) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1538, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwMatch();
                                                                                                } else {
                                                                                                    Str *_t1557 = Str_lit("case", 4ULL);
                                                                                                    Bool _t1558; { Bool *_hp = Str_eq(_sw1538, _t1557); _t1558 = *_hp; free(_hp); }
                                                                                                    Str_delete(_t1557, &(Bool){1});
                                                                                                    if (_t1558) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1538, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwCase();
                                                                                                    } else {
                                                                                                        Str *_t1555 = Str_lit("default", 7ULL);
                                                                                                        Bool _t1556; { Bool *_hp = Str_eq(_sw1538, _t1555); _t1556 = *_hp; free(_hp); }
                                                                                                        Str_delete(_t1555, &(Bool){1});
                                                                                                        if (_t1556) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1538, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwDefault();
                                                                                                        } else {
                                                                                                            Str *_t1553 = Str_lit("return", 6ULL);
                                                                                                            Bool _t1554; { Bool *_hp = Str_eq(_sw1538, _t1553); _t1554 = *_hp; free(_hp); }
                                                                                                            Str_delete(_t1553, &(Bool){1});
                                                                                                            if (_t1554) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1538, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwReturn();
                                                                                                            } else {
                                                                                                                Str *_t1551 = Str_lit("throw", 5ULL);
                                                                                                                Bool _t1552; { Bool *_hp = Str_eq(_sw1538, _t1551); _t1552 = *_hp; free(_hp); }
                                                                                                                Str_delete(_t1551, &(Bool){1});
                                                                                                                if (_t1552) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1538, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwThrow();
                                                                                                                } else {
                                                                                                                    Str *_t1549 = Str_lit("catch", 5ULL);
                                                                                                                    Bool _t1550; { Bool *_hp = Str_eq(_sw1538, _t1549); _t1550 = *_hp; free(_hp); }
                                                                                                                    Str_delete(_t1549, &(Bool){1});
                                                                                                                    if (_t1550) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1538, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwCatch();
                                                                                                                    } else {
                                                                                                                        Str *_t1547 = Str_lit("break", 5ULL);
                                                                                                                        Bool _t1548; { Bool *_hp = Str_eq(_sw1538, _t1547); _t1548 = *_hp; free(_hp); }
                                                                                                                        Str_delete(_t1547, &(Bool){1});
                                                                                                                        if (_t1548) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1538, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwBreak();
                                                                                                                        } else {
                                                                                                                            Str *_t1545 = Str_lit("continue", 8ULL);
                                                                                                                            Bool _t1546; { Bool *_hp = Str_eq(_sw1538, _t1545); _t1546 = *_hp; free(_hp); }
                                                                                                                            Str_delete(_t1545, &(Bool){1});
                                                                                                                            if (_t1546) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1538, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwContinue();
                                                                                                                            } else {
                                                                                                                                Str *_t1543 = Str_lit("defer", 5ULL);
                                                                                                                                Bool _t1544; { Bool *_hp = Str_eq(_sw1538, _t1543); _t1544 = *_hp; free(_hp); }
                                                                                                                                Str_delete(_t1543, &(Bool){1});
                                                                                                                                if (_t1544) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1538, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwDefer();
                                                                                                                                } else {
                                                                                                                                    Str *_t1541 = Str_lit("true", 4ULL);
                                                                                                                                    Bool _t1542; { Bool *_hp = Str_eq(_sw1538, _t1541); _t1542 = *_hp; free(_hp); }
                                                                                                                                    Str_delete(_t1541, &(Bool){1});
                                                                                                                                    if (_t1542) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1538, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwTrue();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1539 = Str_lit("false", 5ULL);
                                                                                                                                        Bool _t1540; { Bool *_hp = Str_eq(_sw1538, _t1539); _t1540 = *_hp; free(_hp); }
                                                                                                                                        Str_delete(_t1539, &(Bool){1});
                                                                                                                                        if (_t1540) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1538, &(Bool){1});
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
                                                                                                                                            Str_delete(_sw1538, &(Bool){1});
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
        Str_delete(_sw1538, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * source, Str * path) {
    Str *_t1960 = Str_lit("Token", 5ULL);
    U64 _t1961; { U64 *_hp = Token_size(); _t1961 = *_hp; free(_hp); }
    Vec *tokens = Vec_new(_t1960, &(U64){_t1961});
    Str_delete(_t1960, &(Bool){1});
    ;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    I64 line = 1;
    U64 line_start = 0;
    U64 src_len; { U64 *_hp = Str_len(source); src_len = *_hp; free(_hp); }
    while (1) {
        Bool _wcond1605; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1605 = *_hp; free(_hp); }
        if (_wcond1605) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_get(source, pos);
        U8 _t1905 = 32;
        U8 _t1906 = 9;
        Bool _t1907 = U8_eq(DEREF(c), _t1905);
        ;
        Bool _t1908 = U8_eq(DEREF(c), _t1906);
        ;
        U8 _t1909 = 13;
        Bool _t1910 = Bool_or(_t1907, _t1908);
        ;
        ;
        Bool _t1911 = U8_eq(DEREF(c), _t1909);
        ;
        U8 _t1912 = 59;
        Bool _t1913 = Bool_or(_t1910, _t1911);
        ;
        ;
        Bool _t1914 = U8_eq(DEREF(c), _t1912);
        ;
        Bool _t1915 = Bool_or(_t1913, _t1914);
        ;
        ;
        if (_t1915) {
            U64 _t1606 = 1;
            U64 _t1607 = U64_add(DEREF(pos), _t1606);
            ;
            *pos = _t1607;
            ;
            ;
            continue;
        }
        ;
        U8 _t1916 = 10;
        Bool _t1917 = U8_eq(DEREF(c), _t1916);
        ;
        if (_t1917) {
            U64 _t1608 = 1;
            U64 _t1609 = U64_add(DEREF(pos), _t1608);
            ;
            *pos = _t1609;
            ;
            I64 _t1610 = 1;
            I64 _t1611 = I64_add(line, _t1610);
            ;
            line = _t1611;
            ;
            U64 _t1612 = U64_clone(pos);
            line_start = _t1612;
            ;
            ;
            continue;
        }
        ;
        U64 _t1918 = U64_sub(DEREF(pos), line_start);
        U64 _t1919 = 1;
        U64 _t1920 = U64_add(_t1918, _t1919);
        ;
        ;
        I64 col = U64_to_i64(_t1920);
        ;
        U64 start = U64_clone(pos);
        U8 _t1921 = 35;
        Bool _t1922 = U8_eq(DEREF(c), _t1921);
        ;
        if (_t1922) {
            while (1) {
                Bool _wcond1613; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1613 = *_hp; free(_hp); }
                if (_wcond1613) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1614 = Str_get(source, pos);
                U8 _t1615 = 10;
                Bool _t1616 = U8_eq(DEREF(_t1614), _t1615);
                ;
                if (_t1616) {
                    ;
                    break;
                }
                ;
                U64 _t1617 = 1;
                U64 _t1618 = U64_add(DEREF(pos), _t1617);
                ;
                *pos = _t1618;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1923 = 47;
        U64 _t1924 = 1;
        U64 _t1925 = U64_add(DEREF(pos), _t1924);
        ;
        Bool _t1926 = U8_eq(DEREF(c), _t1923);
        ;
        Bool _t1927; { Bool *_hp = U64_lt(&(U64){_t1925}, &(U64){src_len}); _t1927 = *_hp; free(_hp); }
        ;
        Bool _t1928 = Bool_and(_t1926, _t1927);
        ;
        ;
        if (_t1928) {
            U64 _t1679 = 1;
            U64 *_t1680 = malloc(sizeof(U64)); *_t1680 = U64_add(DEREF(pos), _t1679);
            ;
            U8 *c2 = Str_get(source, _t1680);
            U8 _t1681 = 47;
            Bool _t1682 = U8_eq(DEREF(c2), _t1681);
            ;
            if (_t1682) {
                while (1) {
                    Bool _wcond1619; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1619 = *_hp; free(_hp); }
                    if (_wcond1619) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1620 = Str_get(source, pos);
                    U8 _t1621 = 10;
                    Bool _t1622 = U8_eq(DEREF(_t1620), _t1621);
                    ;
                    if (_t1622) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1623 = 1;
                    U64 _t1624 = U64_add(DEREF(pos), _t1623);
                    ;
                    *pos = _t1624;
                    ;
                }
                U64_delete(_t1680, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1683 = 42;
            Bool _t1684 = U8_eq(DEREF(c2), _t1683);
            U64_delete(_t1680, &(Bool){1});
            ;
            if (_t1684) {
                U64 _t1675 = 2;
                U64 _t1676 = U64_add(DEREF(pos), _t1675);
                ;
                *pos = _t1676;
                ;
                I64 depth = 1;
                while (1) {
                    Bool _wcond1625; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1625 = *_hp; free(_hp); }
                    if (_wcond1625) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1650 = 0;
                    Bool _t1651; { Bool *_hp = I64_lte(&(I64){depth}, &(I64){_t1650}); _t1651 = *_hp; free(_hp); }
                    ;
                    if (_t1651) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1652 = 1;
                    U64 _t1653 = U64_add(DEREF(pos), _t1652);
                    ;
                    Bool _t1654; { Bool *_hp = U64_lt(&(U64){_t1653}, &(U64){src_len}); _t1654 = *_hp; free(_hp); }
                    ;
                    if (_t1654) {
                        U8 *b1 = Str_get(source, pos);
                        U64 _t1634 = 1;
                        U64 *_t1635 = malloc(sizeof(U64)); *_t1635 = U64_add(DEREF(pos), _t1634);
                        ;
                        U8 *b2 = Str_get(source, _t1635);
                        U8 _t1636 = 47;
                        U8 _t1637 = 42;
                        Bool _t1638 = U8_eq(DEREF(b1), _t1636);
                        ;
                        Bool _t1639 = U8_eq(DEREF(b2), _t1637);
                        ;
                        Bool _t1640 = Bool_and(_t1638, _t1639);
                        ;
                        ;
                        if (_t1640) {
                            I64 _t1626 = 1;
                            I64 _t1627 = I64_add(depth, _t1626);
                            ;
                            depth = _t1627;
                            ;
                            U64 _t1628 = 2;
                            U64 _t1629 = U64_add(DEREF(pos), _t1628);
                            ;
                            *pos = _t1629;
                            ;
                            U64_delete(_t1635, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1641 = 42;
                        U8 _t1642 = 47;
                        Bool _t1643 = U8_eq(DEREF(b1), _t1641);
                        ;
                        Bool _t1644 = U8_eq(DEREF(b2), _t1642);
                        U64_delete(_t1635, &(Bool){1});
                        ;
                        Bool _t1645 = Bool_and(_t1643, _t1644);
                        ;
                        ;
                        if (_t1645) {
                            I64 _t1630 = 1;
                            I64 _t1631 = I64_sub(depth, _t1630);
                            ;
                            depth = _t1631;
                            ;
                            U64 _t1632 = 2;
                            U64 _t1633 = U64_add(DEREF(pos), _t1632);
                            ;
                            *pos = _t1633;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1655 = Str_get(source, pos);
                    U8 _t1656 = 10;
                    Bool _t1657 = U8_eq(DEREF(_t1655), _t1656);
                    ;
                    if (_t1657) {
                        I64 _t1646 = 1;
                        I64 _t1647 = I64_add(line, _t1646);
                        ;
                        line = _t1647;
                        ;
                        U64 _t1648 = 1;
                        U64 _t1649 = U64_add(DEREF(pos), _t1648);
                        ;
                        line_start = _t1649;
                        ;
                    }
                    ;
                    U64 _t1658 = 1;
                    U64 _t1659 = U64_add(DEREF(pos), _t1658);
                    ;
                    *pos = _t1659;
                    ;
                }
                I64 _t1677 = 0;
                Bool _t1678; { Bool *_hp = I64_gt(&(I64){depth}, &(I64){_t1677}); _t1678 = *_hp; free(_hp); }
                ;
                ;
                if (_t1678) {
                    Str *_t1660 = Str_lit("Str", 3ULL);
                    U64 _t1661; { U64 *_hp = Str_size(); _t1661 = *_hp; free(_hp); }
                    U64 _t1662 = 6;
                    Array *_va21 = Array_new(_t1660, &(U64){_t1661}, &(U64){_t1662});
                    Str_delete(_t1660, &(Bool){1});
                    ;
                    ;
                    U64 _t1663 = 0;
                    Str *_t1664 = Str_clone(path);
                    Array_set(_va21, &(U64){_t1663}, _t1664);
                    ;
                    U64 _t1665 = 1;
                    Str *_t1666 = Str_lit(":", 1ULL);
                    Array_set(_va21, &(U64){_t1665}, _t1666);
                    ;
                    U64 _t1667 = 2;
                    Str *_t1668 = I64_to_str(&(I64){line});
                    Array_set(_va21, &(U64){_t1667}, _t1668);
                    ;
                    U64 _t1669 = 3;
                    Str *_t1670 = Str_lit(":", 1ULL);
                    Array_set(_va21, &(U64){_t1669}, _t1670);
                    ;
                    U64 _t1671 = 4;
                    Str *_t1672 = I64_to_str(&(I64){col});
                    Array_set(_va21, &(U64){_t1671}, _t1672);
                    ;
                    U64 _t1673 = 5;
                    Str *_t1674 = Str_lit(": error: unterminated comment", 29ULL);
                    Array_set(_va21, &(U64){_t1673}, _t1674);
                    ;
                    println(_va21);
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
        Bool _t1929; { Bool *_hp = is_digit(c); _t1929 = *_hp; free(_hp); }
        if (_t1929) {
            while (1) {
                Bool _wcond1685; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1685 = *_hp; free(_hp); }
                if (_wcond1685) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1686 = Str_get(source, pos);
                Bool _t1687; { Bool *_hp = is_digit(_t1686); _t1687 = *_hp; free(_hp); }
                Bool _t1688 = Bool_not(_t1687);
                ;
                if (_t1688) {
                    ;
                    break;
                }
                ;
                U64 _t1689 = 1;
                U64 _t1690 = U64_add(DEREF(pos), _t1689);
                ;
                *pos = _t1690;
                ;
            }
            U64 _t1707 = 1;
            U64 _t1708 = U64_add(DEREF(pos), _t1707);
            ;
            Bool _t1709; { Bool *_hp = U64_lt(&(U64){_t1708}, &(U64){src_len}); _t1709 = *_hp; free(_hp); }
            ;
            if (_t1709) {
                U8 *_t1699 = Str_get(source, pos);
                U8 _t1700 = 46;
                U64 _t1701 = 1;
                U64 *_t1702 = malloc(sizeof(U64)); *_t1702 = U64_add(DEREF(pos), _t1701);
                ;
                U8 *_t1703 = Str_get(source, _t1702);
                Bool _t1704 = U8_eq(DEREF(_t1699), _t1700);
                ;
                Bool _t1705; { Bool *_hp = is_digit(_t1703); _t1705 = *_hp; free(_hp); }
                U64_delete(_t1702, &(Bool){1});
                Bool _t1706 = Bool_and(_t1704, _t1705);
                ;
                ;
                if (_t1706) {
                    U64 _t1697 = 1;
                    U64 _t1698 = U64_add(DEREF(pos), _t1697);
                    ;
                    *pos = _t1698;
                    ;
                    while (1) {
                        Bool _wcond1691; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1691 = *_hp; free(_hp); }
                        if (_wcond1691) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1692 = Str_get(source, pos);
                        Bool _t1693; { Bool *_hp = is_digit(_t1692); _t1693 = *_hp; free(_hp); }
                        Bool _t1694 = Bool_not(_t1693);
                        ;
                        if (_t1694) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1695 = 1;
                        U64 _t1696 = U64_add(DEREF(pos), _t1695);
                        ;
                        *pos = _t1696;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1710 = U64_sub(DEREF(pos), start);
            I64 _t1711 = I64_clone(&(I64){col});
            Token *_t1712 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1712->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1710}); _t1712->text = *_ca; free(_ca); }
            _t1712->line = I64_clone(&(I64){line});
            _t1712->col = _t1711;
            ;
            ;
            Vec_push(tokens, _t1712);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1930; { Bool *_hp = is_alpha(c); _t1930 = *_hp; free(_hp); }
        if (_t1930) {
            while (1) {
                Bool _wcond1713; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1713 = *_hp; free(_hp); }
                if (_wcond1713) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1714 = Str_get(source, pos);
                Bool _t1715; { Bool *_hp = is_alnum(_t1714); _t1715 = *_hp; free(_hp); }
                Bool _t1716 = Bool_not(_t1715);
                ;
                if (_t1716) {
                    ;
                    break;
                }
                ;
                U64 _t1717 = 1;
                U64 _t1718 = U64_add(DEREF(pos), _t1717);
                ;
                *pos = _t1718;
                ;
            }
            U64 _t1719 = U64_sub(DEREF(pos), start);
            Str *word = Str_substr(source, &(U64){start}, &(U64){_t1719});
            ;
            TokenType *type = lookup_keyword(word);
            I64 _t1720 = I64_clone(&(I64){line});
            I64 _t1721 = I64_clone(&(I64){col});
            Token *_t1722 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1722->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1722->text = *_ca; free(_ca); }
            _t1722->line = _t1720;
            _t1722->col = _t1721;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1722);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1931 = 34;
        Bool _t1932 = U8_eq(DEREF(c), _t1931);
        ;
        if (_t1932) {
            U64 _t1772 = 1;
            U64 _t1773 = U64_add(DEREF(pos), _t1772);
            ;
            *pos = _t1773;
            ;
            while (1) {
                Bool _wcond1723; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1723 = *_hp; free(_hp); }
                if (_wcond1723) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1730 = Str_get(source, pos);
                U8 _t1731 = 34;
                Bool _t1732 = U8_eq(DEREF(_t1730), _t1731);
                ;
                if (_t1732) {
                    ;
                    break;
                }
                ;
                U8 *_t1733 = Str_get(source, pos);
                U8 _t1734 = 92;
                U64 _t1735 = 1;
                U64 _t1736 = U64_add(DEREF(pos), _t1735);
                ;
                Bool _t1737 = U8_eq(DEREF(_t1733), _t1734);
                ;
                Bool _t1738; { Bool *_hp = U64_lt(&(U64){_t1736}, &(U64){src_len}); _t1738 = *_hp; free(_hp); }
                ;
                Bool _t1739 = Bool_and(_t1737, _t1738);
                ;
                ;
                if (_t1739) {
                    U64 _t1724 = 1;
                    U64 _t1725 = U64_add(DEREF(pos), _t1724);
                    ;
                    *pos = _t1725;
                    ;
                }
                ;
                U8 *_t1740 = Str_get(source, pos);
                U8 _t1741 = 10;
                Bool _t1742 = U8_eq(DEREF(_t1740), _t1741);
                ;
                if (_t1742) {
                    I64 _t1726 = 1;
                    I64 _t1727 = I64_add(line, _t1726);
                    ;
                    line = _t1727;
                    ;
                    U64 _t1728 = 1;
                    U64 _t1729 = U64_add(DEREF(pos), _t1728);
                    ;
                    line_start = _t1729;
                    ;
                }
                ;
                U64 _t1743 = 1;
                U64 _t1744 = U64_add(DEREF(pos), _t1743);
                ;
                *pos = _t1744;
                ;
            }
            U8 *_t1774 = Str_get(source, pos);
            U8 _t1775 = 34;
            Bool _t1776; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1776 = *_hp; free(_hp); }
            Bool _t1777 = U8_eq(DEREF(_t1774), _t1775);
            ;
            Bool _t1778 = Bool_and(_t1776, _t1777);
            ;
            ;
            if (_t1778) {
                U64 _t1745 = 1;
                U64 _t1746 = U64_add(DEREF(pos), _t1745);
                ;
                *pos = _t1746;
                ;
                U64 _t1747 = 1;
                U64 _t1748 = U64_sub(DEREF(pos), start);
                U64 _t1749 = 2;
                U64 _t1750 = U64_add(start, _t1747);
                ;
                U64 _t1751 = U64_sub(_t1748, _t1749);
                ;
                ;
                I64 _t1752 = I64_clone(&(I64){col});
                Token *_t1753 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1753->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){_t1750}, &(U64){_t1751}); _t1753->text = *_ca; free(_ca); }
                _t1753->line = I64_clone(&(I64){line});
                _t1753->col = _t1752;
                ;
                ;
                ;
                Vec_push(tokens, _t1753);
            } else {
                Str *_t1754 = Str_lit("Str", 3ULL);
                U64 _t1755; { U64 *_hp = Str_size(); _t1755 = *_hp; free(_hp); }
                U64 _t1756 = 6;
                Array *_va22 = Array_new(_t1754, &(U64){_t1755}, &(U64){_t1756});
                Str_delete(_t1754, &(Bool){1});
                ;
                ;
                U64 _t1757 = 0;
                Str *_t1758 = Str_clone(path);
                Array_set(_va22, &(U64){_t1757}, _t1758);
                ;
                U64 _t1759 = 1;
                Str *_t1760 = Str_lit(":", 1ULL);
                Array_set(_va22, &(U64){_t1759}, _t1760);
                ;
                U64 _t1761 = 2;
                Str *_t1762 = I64_to_str(&(I64){line});
                Array_set(_va22, &(U64){_t1761}, _t1762);
                ;
                U64 _t1763 = 3;
                Str *_t1764 = Str_lit(":", 1ULL);
                Array_set(_va22, &(U64){_t1763}, _t1764);
                ;
                U64 _t1765 = 4;
                Str *_t1766 = I64_to_str(&(I64){col});
                Array_set(_va22, &(U64){_t1765}, _t1766);
                ;
                U64 _t1767 = 5;
                Str *_t1768 = Str_lit(": error: unterminated string", 28ULL);
                Array_set(_va22, &(U64){_t1767}, _t1768);
                ;
                println(_va22);
                U64 _t1769 = U64_sub(DEREF(pos), start);
                I64 _t1770 = I64_clone(&(I64){col});
                Token *_t1771 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1771->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1769}); _t1771->text = *_ca; free(_ca); }
                _t1771->line = I64_clone(&(I64){line});
                _t1771->col = _t1770;
                ;
                ;
                Vec_push(tokens, _t1771);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1933 = 39;
        Bool _t1934 = U8_eq(DEREF(c), _t1933);
        ;
        if (_t1934) {
            U64 _t1804 = 1;
            U64 _t1805 = U64_add(DEREF(pos), _t1804);
            ;
            *pos = _t1805;
            ;
            U64 ch_start = U64_clone(pos);
            U8 *_t1806 = Str_get(source, pos);
            U8 _t1807 = 92;
            U64 _t1808 = 1;
            U64 _t1809 = U64_add(DEREF(pos), _t1808);
            ;
            Bool _t1810 = U8_eq(DEREF(_t1806), _t1807);
            ;
            Bool _t1811; { Bool *_hp = U64_lt(&(U64){_t1809}, &(U64){src_len}); _t1811 = *_hp; free(_hp); }
            ;
            Bool _t1812; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1812 = *_hp; free(_hp); }
            Bool _t1813 = Bool_and(_t1810, _t1811);
            ;
            ;
            Bool _t1814 = Bool_and(_t1812, _t1813);
            ;
            ;
            if (_t1814) {
                U64 _t1779 = 1;
                U64 _t1780 = U64_add(DEREF(pos), _t1779);
                ;
                *pos = _t1780;
                ;
            }
            ;
            U64 _t1815 = 1;
            U64 _t1816 = U64_add(DEREF(pos), _t1815);
            ;
            *pos = _t1816;
            ;
            U8 *_t1817 = Str_get(source, pos);
            U8 _t1818 = 39;
            Bool _t1819; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1819 = *_hp; free(_hp); }
            Bool _t1820 = U8_eq(DEREF(_t1817), _t1818);
            ;
            Bool _t1821 = Bool_and(_t1819, _t1820);
            ;
            ;
            if (_t1821) {
                U64 _t1781 = U64_sub(DEREF(pos), ch_start);
                I64 _t1782 = I64_clone(&(I64){col});
                Token *_t1783 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1783->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){ch_start}, &(U64){_t1781}); _t1783->text = *_ca; free(_ca); }
                _t1783->line = I64_clone(&(I64){line});
                _t1783->col = _t1782;
                ;
                ;
                Vec_push(tokens, _t1783);
                U64 _t1784 = 1;
                U64 _t1785 = U64_add(DEREF(pos), _t1784);
                ;
                *pos = _t1785;
                ;
            } else {
                Str *_t1786 = Str_lit("Str", 3ULL);
                U64 _t1787; { U64 *_hp = Str_size(); _t1787 = *_hp; free(_hp); }
                U64 _t1788 = 6;
                Array *_va23 = Array_new(_t1786, &(U64){_t1787}, &(U64){_t1788});
                Str_delete(_t1786, &(Bool){1});
                ;
                ;
                U64 _t1789 = 0;
                Str *_t1790 = Str_clone(path);
                Array_set(_va23, &(U64){_t1789}, _t1790);
                ;
                U64 _t1791 = 1;
                Str *_t1792 = Str_lit(":", 1ULL);
                Array_set(_va23, &(U64){_t1791}, _t1792);
                ;
                U64 _t1793 = 2;
                Str *_t1794 = I64_to_str(&(I64){line});
                Array_set(_va23, &(U64){_t1793}, _t1794);
                ;
                U64 _t1795 = 3;
                Str *_t1796 = Str_lit(":", 1ULL);
                Array_set(_va23, &(U64){_t1795}, _t1796);
                ;
                U64 _t1797 = 4;
                Str *_t1798 = I64_to_str(&(I64){col});
                Array_set(_va23, &(U64){_t1797}, _t1798);
                ;
                U64 _t1799 = 5;
                Str *_t1800 = Str_lit(": error: unterminated character literal", 39ULL);
                Array_set(_va23, &(U64){_t1799}, _t1800);
                ;
                println(_va23);
                U64 _t1801 = U64_sub(DEREF(pos), start);
                I64 _t1802 = I64_clone(&(I64){col});
                Token *_t1803 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1803->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1801}); _t1803->text = *_ca; free(_ca); }
                _t1803->line = I64_clone(&(I64){line});
                _t1803->col = _t1802;
                ;
                ;
                Vec_push(tokens, _t1803);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t1935 = 1;
        U64 _t1936 = U64_add(DEREF(pos), _t1935);
        ;
        Bool _t1937; { Bool *_hp = U64_lt(&(U64){_t1936}, &(U64){src_len}); _t1937 = *_hp; free(_hp); }
        ;
        if (_t1937) {
            U64 _t1828 = 1;
            U64 *_t1829 = malloc(sizeof(U64)); *_t1829 = U64_add(DEREF(pos), _t1828);
            ;
            U8 *c2 = Str_get(source, _t1829);
            TokenType *two = TokenType_clone(TokenType_Eof());
            U8 _t1830 = 58;
            U8 _t1831 = 61;
            Bool _t1832 = U8_eq(DEREF(c), _t1830);
            ;
            Bool _t1833 = U8_eq(DEREF(c2), _t1831);
            ;
            Bool _t1834 = Bool_and(_t1832, _t1833);
            ;
            ;
            if (_t1834) {
                two = TokenType_clone(TokenType_ColonEq());
            }
            ;
            U8 _t1835 = 61;
            U8 _t1836 = 61;
            Bool _t1837 = U8_eq(DEREF(c), _t1835);
            ;
            Bool _t1838 = U8_eq(DEREF(c2), _t1836);
            ;
            Bool _t1839 = Bool_and(_t1837, _t1838);
            ;
            ;
            if (_t1839) {
                two = TokenType_clone(TokenType_EqEq());
            }
            ;
            U8 _t1840 = 33;
            U8 _t1841 = 61;
            Bool _t1842 = U8_eq(DEREF(c), _t1840);
            ;
            Bool _t1843 = U8_eq(DEREF(c2), _t1841);
            ;
            Bool _t1844 = Bool_and(_t1842, _t1843);
            ;
            ;
            if (_t1844) {
                two = TokenType_clone(TokenType_Neq());
            }
            ;
            U8 _t1845 = 60;
            U8 _t1846 = 61;
            Bool _t1847 = U8_eq(DEREF(c), _t1845);
            ;
            Bool _t1848 = U8_eq(DEREF(c2), _t1846);
            ;
            Bool _t1849 = Bool_and(_t1847, _t1848);
            ;
            ;
            if (_t1849) {
                two = TokenType_clone(TokenType_LtEq());
            }
            ;
            U8 _t1850 = 62;
            U8 _t1851 = 61;
            Bool _t1852 = U8_eq(DEREF(c), _t1850);
            ;
            Bool _t1853 = U8_eq(DEREF(c2), _t1851);
            ;
            Bool _t1854 = Bool_and(_t1852, _t1853);
            ;
            ;
            if (_t1854) {
                two = TokenType_clone(TokenType_GtEq());
            }
            ;
            U8 _t1855 = 46;
            U8 _t1856 = 46;
            Bool _t1857 = U8_eq(DEREF(c), _t1855);
            ;
            Bool _t1858 = U8_eq(DEREF(c2), _t1856);
            U64_delete(_t1829, &(Bool){1});
            ;
            Bool _t1859 = Bool_and(_t1857, _t1858);
            ;
            ;
            if (_t1859) {
                two = TokenType_clone(TokenType_DotDot());
            }
            ;
            Bool _t1860; { Bool *_hp = TokenType_eq(two, TokenType_Eof()); _t1860 = *_hp; free(_hp); }
            Bool _t1861 = Bool_not(_t1860);
            ;
            if (_t1861) {
                U64 _t1822 = 2;
                I64 _t1823 = I64_clone(&(I64){line});
                I64 _t1824 = I64_clone(&(I64){col});
                Token *_t1825 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1825->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1822}); _t1825->text = *_ca; free(_ca); }
                _t1825->line = _t1823;
                _t1825->col = _t1824;
                ;
                ;
                ;
                Vec_push(tokens, _t1825);
                U64 _t1826 = 2;
                U64 _t1827 = U64_add(DEREF(pos), _t1826);
                ;
                *pos = _t1827;
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
            U8 _sw1862 = U8_clone(c);
            U8 _t1897 = 40;
            Bool _t1898 = U8_eq(_sw1862, _t1897);
            ;
            if (_t1898) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1895 = 41;
                Bool _t1896 = U8_eq(_sw1862, _t1895);
                ;
                if (_t1896) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1893 = 123;
                    Bool _t1894 = U8_eq(_sw1862, _t1893);
                    ;
                    if (_t1894) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1891 = 125;
                        Bool _t1892 = U8_eq(_sw1862, _t1891);
                        ;
                        if (_t1892) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1889 = 91;
                            Bool _t1890 = U8_eq(_sw1862, _t1889);
                            ;
                            if (_t1890) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1887 = 93;
                                Bool _t1888 = U8_eq(_sw1862, _t1887);
                                ;
                                if (_t1888) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1885 = 44;
                                    Bool _t1886 = U8_eq(_sw1862, _t1885);
                                    ;
                                    if (_t1886) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1883 = 58;
                                        Bool _t1884 = U8_eq(_sw1862, _t1883);
                                        ;
                                        if (_t1884) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1881 = 46;
                                            Bool _t1882 = U8_eq(_sw1862, _t1881);
                                            ;
                                            if (_t1882) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1879 = 63;
                                                Bool _t1880 = U8_eq(_sw1862, _t1879);
                                                ;
                                                if (_t1880) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1877 = 33;
                                                    Bool _t1878 = U8_eq(_sw1862, _t1877);
                                                    ;
                                                    if (_t1878) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1875 = 43;
                                                        Bool _t1876 = U8_eq(_sw1862, _t1875);
                                                        ;
                                                        if (_t1876) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1873 = 45;
                                                            Bool _t1874 = U8_eq(_sw1862, _t1873);
                                                            ;
                                                            if (_t1874) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1871 = 42;
                                                                Bool _t1872 = U8_eq(_sw1862, _t1871);
                                                                ;
                                                                if (_t1872) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1869 = 47;
                                                                    Bool _t1870 = U8_eq(_sw1862, _t1869);
                                                                    ;
                                                                    if (_t1870) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1867 = 61;
                                                                        Bool _t1868 = U8_eq(_sw1862, _t1867);
                                                                        ;
                                                                        if (_t1868) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1865 = 60;
                                                                            Bool _t1866 = U8_eq(_sw1862, _t1865);
                                                                            ;
                                                                            if (_t1866) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1863 = 62;
                                                                                Bool _t1864 = U8_eq(_sw1862, _t1863);
                                                                                ;
                                                                                if (_t1864) {
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
        Bool _t1938; { Bool *_hp = TokenType_eq(single, TokenType_Eof()); _t1938 = *_hp; free(_hp); }
        Bool _t1939 = Bool_not(_t1938);
        ;
        if (_t1939) {
            U64 _t1899 = 1;
            I64 _t1900 = I64_clone(&(I64){line});
            I64 _t1901 = I64_clone(&(I64){col});
            Token *_t1902 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1902->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1899}); _t1902->text = *_ca; free(_ca); }
            _t1902->line = _t1900;
            _t1902->col = _t1901;
            ;
            ;
            ;
            Vec_push(tokens, _t1902);
            U64 _t1903 = 1;
            U64 _t1904 = U64_add(DEREF(pos), _t1903);
            ;
            *pos = _t1904;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t1940 = Str_lit("Str", 3ULL);
        U64 _t1941; { U64 *_hp = Str_size(); _t1941 = *_hp; free(_hp); }
        U64 _t1942 = 6;
        Array *_va24 = Array_new(_t1940, &(U64){_t1941}, &(U64){_t1942});
        Str_delete(_t1940, &(Bool){1});
        ;
        ;
        U64 _t1943 = 0;
        Str *_t1944 = Str_clone(path);
        Array_set(_va24, &(U64){_t1943}, _t1944);
        ;
        U64 _t1945 = 1;
        Str *_t1946 = Str_lit(":", 1ULL);
        Array_set(_va24, &(U64){_t1945}, _t1946);
        ;
        U64 _t1947 = 2;
        Str *_t1948 = I64_to_str(&(I64){line});
        Array_set(_va24, &(U64){_t1947}, _t1948);
        ;
        U64 _t1949 = 3;
        Str *_t1950 = Str_lit(":", 1ULL);
        Array_set(_va24, &(U64){_t1949}, _t1950);
        ;
        U64 _t1951 = 4;
        Str *_t1952 = I64_to_str(&(I64){col});
        Array_set(_va24, &(U64){_t1951}, _t1952);
        ;
        U64 _t1953 = 5;
        Str *_t1954 = Str_lit(": error: unexpected character", 29ULL);
        Array_set(_va24, &(U64){_t1953}, _t1954);
        ;
        println(_va24);
        U64 _t1955 = 1;
        I64 _t1956 = I64_clone(&(I64){col});
        ;
        Token *_t1957 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1957->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1955}); _t1957->text = *_ca; free(_ca); }
        _t1957->line = I64_clone(&(I64){line});
        _t1957->col = _t1956;
        ;
        ;
        ;
        Vec_push(tokens, _t1957);
        U64 _t1958 = 1;
        U64 _t1959 = U64_add(DEREF(pos), _t1958);
        ;
        *pos = _t1959;
        ;
    }
    ;
    U64 _t1962 = U64_sub(DEREF(pos), line_start);
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t1963 = 1;
    U64 _t1964 = U64_add(_t1962, _t1963);
    ;
    ;
    I64 col = U64_to_i64(_t1964);
    ;
    I64 _t1965 = I64_clone(&(I64){col});
    ;
    Token *_t1966 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t1966->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1966->text = *_ca; free(_ca); }
    _t1966->line = I64_clone(&(I64){line});
    _t1966->col = _t1965;
    ;
    ;
    Vec_push(tokens, _t1966);
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
    _t1967 = malloc(sizeof(I64));
    *_t1967 = 0;
    _t1968 = malloc(sizeof(I64));
    *_t1968 = 1;
    _t1969 = malloc(sizeof(I64)); *_t1969 = I64_sub(DEREF(_t1967), DEREF(_t1968));
    CAP_LIT = U64_from_i64(_t1969);
    _t1970 = malloc(sizeof(I64));
    *_t1970 = 0;
    _t1971 = malloc(sizeof(I64));
    *_t1971 = 2;
    _t1972 = malloc(sizeof(I64)); *_t1972 = I64_sub(DEREF(_t1970), DEREF(_t1971));
    CAP_VIEW = U64_from_i64(_t1972);
}

