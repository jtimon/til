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
    TokenType_TAG_KwShallow,
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
    TokenType_TAG_KwNull,
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
Bool * TokenType_is_KwShallow(TokenType * self);
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
Bool * TokenType_is_KwNull(TokenType * self);
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
TokenType *TokenType_KwShallow();
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
TokenType *TokenType_KwNull();
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

static I64 *_t1959;
static I64 *_t1960;
static I64 *_t1961;
static U64 *CAP_LIT;
static I64 *_t1962;
static I64 *_t1963;
static I64 *_t1964;
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

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    I64 _t96 = 0;
    I64 _t97 = 1;
    I64 _t98 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t99 = I64_sub(_t96, _t97);
    ;
    ;
    Bool _t100 = I64_eq(_t98, _t99);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t100; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    I64 _t101 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t102 = 1;
    Bool _t103 = I64_eq(_t101, _t102);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t103; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    Bool _t104 = U32_eq(DEREF(a), DEREF(b));
    Bool _t105 = Bool_not(_t104);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t105; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    Bool _t106; { Bool *_hp = U32_gt(a, b); _t106 = *_hp; free(_hp); }
    Bool _t107 = Bool_not(_t106);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t107; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    Bool _t108; { Bool *_hp = U32_lt(a, b); _t108 = *_hp; free(_hp); }
    Bool _t109 = Bool_not(_t108);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t109; return _r; }
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t110 = U64_to_str_ext(val);
    return _t110;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 _t111 = U64_from_i64_ext(val);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t111; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    I64 _t113 = 0;
    I64 _t114 = 1;
    I64 _t115 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t116 = I64_sub(_t113, _t114);
    ;
    ;
    Bool _t117 = I64_eq(_t115, _t116);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t117; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    I64 _t118 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t119 = 1;
    Bool _t120 = I64_eq(_t118, _t119);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t120; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    Bool _t121 = U64_eq(DEREF(a), DEREF(b));
    Bool _t122 = Bool_not(_t121);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t122; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    Bool _t123; { Bool *_hp = U64_gt(a, b); _t123 = *_hp; free(_hp); }
    Bool _t124 = Bool_not(_t123);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t124; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    Bool _t125; { Bool *_hp = U64_lt(a, b); _t125 = *_hp; free(_hp); }
    Bool _t126 = Bool_not(_t125);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t126; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    I64 _t163 = 0;
    Bool _t164 = I64_eq(DEREF(val), _t163);
    ;
    if (_t164) {
        U64 _t127 = 2;
        U8 *buf = malloc(_t127);
        ;
        I64 _t128 = 48;
        U64 _t129 = 1;
        memcpy(buf, &(I64){_t128}, _t129);
        ;
        ;
        U64 *_t130 = malloc(sizeof(U64));
        *_t130 = 1;
        void *_t131 = ptr_add(buf, DEREF(_t130));
        I64 _t132 = 0;
        U64 _t133 = 1;
        memcpy(_t131, &(I64){_t132}, _t133);
        U64_delete(_t130, &(Bool){1});
        ;
        ;
        I64 _t134 = 1;
        I64 _t135 = 1;
        Str *_t136 = malloc(sizeof(Str));
        _t136->c_str = buf;
        _t136->count = _t134;
        _t136->cap = _t135;
        ;
        ;
        ;
        return _t136;
    }
    ;
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 _t165 = 0;
    Bool _t166; { Bool *_hp = I64_lt(val, &(I64){_t165}); _t166 = *_hp; free(_hp); }
    ;
    if (_t166) {
        Bool _t137 = 1;
        is_neg = _t137;
        ;
        I64 _t138 = 0;
        I64 _t139 = I64_sub(_t138, DEREF(val));
        ;
        v = _t139;
        ;
    }
    ;
    U64 ndigits = 0;
    I64 tmp = I64_clone(&(I64){v});
    while (1) {
        I64 _t141 = 0;
        Bool _wcond140; { Bool *_hp = I64_gt(&(I64){tmp}, &(I64){_t141}); _wcond140 = *_hp; free(_hp); }
        ;
        if (_wcond140) {
        } else {
            ;
            break;
        }
        ;
        U64 _t142 = 1;
        U64 _t143 = U64_add(ndigits, _t142);
        ;
        ndigits = _t143;
        ;
        I64 _t144 = 10;
        I64 _t145 = I64_div(tmp, _t144);
        ;
        tmp = _t145;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    ;
    if (is_neg) {
        U64 _t146 = 1;
        U64 _t147 = U64_add(DEREF(total), _t146);
        ;
        *total = _t147;
        ;
    }
    U64 _t167 = 1;
    U64 _t168 = U64_add(DEREF(total), _t167);
    ;
    U8 *buf = malloc(_t168);
    ;
    if (is_neg) {
        I64 _t148 = 45;
        U64 _t149 = 1;
        memcpy(buf, &(I64){_t148}, _t149);
        ;
        ;
    }
    ;
    U64 _t169 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t169);
    ;
    while (1) {
        I64 _t151 = 0;
        Bool _wcond150; { Bool *_hp = I64_gt(&(I64){v}, &(I64){_t151}); _wcond150 = *_hp; free(_hp); }
        ;
        if (_wcond150) {
        } else {
            ;
            break;
        }
        ;
        I64 _t152 = 10;
        I64 _t153 = I64_mod(v, _t152);
        ;
        I64 _t154 = 48;
        I64 _t155 = I64_add(_t153, _t154);
        ;
        ;
        void *_t156 = ptr_add(buf, DEREF(i));
        U8 _t157 = I64_to_u8(_t155);
        ;
        U64 _t158 = 1;
        memcpy(_t156, &(U8){_t157}, _t158);
        ;
        ;
        I64 _t159 = 10;
        I64 _t160 = I64_div(v, _t159);
        ;
        v = _t160;
        ;
        U64 _t161 = 1;
        U64 _t162 = U64_sub(DEREF(i), _t161);
        ;
        *i = _t162;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t170 = ptr_add(buf, DEREF(total));
    I64 _t171 = 0;
    U64 _t172 = 1;
    memcpy(_t170, &(I64){_t171}, _t172);
    ;
    ;
    U64 _t173 = U64_clone(total);
    U64 _t174 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t175 = malloc(sizeof(Str));
    _t175->c_str = buf;
    _t175->count = _t173;
    _t175->cap = _t174;
    ;
    ;
    return _t175;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    I64 _t176 = 0;
    I64 _t177 = I64_sub(_t176, DEREF(a));
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t177; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    I64 _t180 = 0;
    Bool _t181; { Bool *_hp = I64_lt(a, &(I64){_t180}); _t181 = *_hp; free(_hp); }
    ;
    if (_t181) {
        I64 _t178 = 0;
        I64 _t179 = I64_sub(_t178, DEREF(a));
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t179; return _r; }
    }
    ;
    I64 _t182 = I64_clone(a);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t182; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    I64 _t184 = 0;
    I64 _t185 = 1;
    I64 _t186 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t187 = I64_sub(_t184, _t185);
    ;
    ;
    Bool _t188 = I64_eq(_t186, _t187);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t188; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    I64 _t189 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t190 = 1;
    Bool _t191 = I64_eq(_t189, _t190);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t191; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    Bool _t192 = I64_eq(DEREF(a), DEREF(b));
    Bool _t193 = Bool_not(_t192);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t193; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    Bool _t194; { Bool *_hp = I64_gt(a, b); _t194 = *_hp; free(_hp); }
    Bool _t195 = Bool_not(_t194);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t195; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    Bool _t196; { Bool *_hp = I64_lt(a, b); _t196 = *_hp; free(_hp); }
    Bool _t197 = Bool_not(_t196);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t197; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    U64 _t198 = U64_clone(&(U64){start});
    U64 _t199 = U64_clone(&(U64){end});
    Range *_t200 = malloc(sizeof(Range));
    _t200->start = _t198;
    _t200->end = _t199;
    ;
    ;
    return _t200;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t202; { Bool *_hp = U64_lte(&self->start, &self->end); _t202 = *_hp; free(_hp); }
    if (_t202) {
        U64 _t201 = U64_sub(self->end, self->start);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t201; return _r; }
    }
    ;
    U64 _t203 = U64_sub(self->start, self->end);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t203; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    Bool _t205; { Bool *_hp = U64_lte(&self->start, &self->end); _t205 = *_hp; free(_hp); }
    if (_t205) {
        U64 _t204 = U64_add(self->start, i);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t204; return _r; }
    }
    ;
    U64 _t206 = U64_sub(self->start, i);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t206; return _r; }
}

Range * Range_clone(Range * val) {
    Range *_t207 = malloc(sizeof(Range));
    _t207->start = val->start;
    _t207->end = val->end;
    return _t207;
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
        Str *_t209 = Str_lit("true", 4ULL);
        return _t209;
    } else {
        Str *_t210 = Str_lit("false", 5ULL);
        return _t210;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool _t215 = Bool_eq(DEREF(a), DEREF(b));
    if (_t215) {
        I64 _t211 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t211; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t212 = 0;
        I64 _t213 = 1;
        I64 _t214 = I64_sub(_t212, _t213);
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t214; return _r; }
    }
    I64 _t216 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t216; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    I64 _t218 = 0;
    I64 _t219 = 1;
    I64 _t220; { I64 *_hp = Bool_cmp(a, b); _t220 = *_hp; free(_hp); }
    I64 _t221 = I64_sub(_t218, _t219);
    ;
    ;
    Bool _t222 = I64_eq(_t220, _t221);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t222; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    I64 _t223; { I64 *_hp = Bool_cmp(a, b); _t223 = *_hp; free(_hp); }
    I64 _t224 = 1;
    Bool _t225 = I64_eq(_t223, _t224);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t225; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    Bool _t226 = Bool_eq(DEREF(a), DEREF(b));
    Bool _t227 = Bool_not(_t226);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t227; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    Bool _t228; { Bool *_hp = Bool_gt(a, b); _t228 = *_hp; free(_hp); }
    Bool _t229 = Bool_not(_t228);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t229; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    Bool _t230; { Bool *_hp = Bool_lt(a, b); _t230 = *_hp; free(_hp); }
    Bool _t231 = Bool_not(_t230);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t231; return _r; }
}

void println(Array * parts) {
    {
        U64 *_fi232 = malloc(sizeof(U64));
        *_fi232 = 0;
        while (1) {
            U64 _t234; { U64 *_hp = Array_len(parts); _t234 = *_hp; free(_hp); }
            Bool _wcond233; { Bool *_hp = U64_lt(_fi232, &(U64){_t234}); _wcond233 = *_hp; free(_hp); }
            ;
            if (_wcond233) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi232);
            U64 _t235 = 1;
            U64 _t236 = U64_add(DEREF(_fi232), _t235);
            ;
            *_fi232 = _t236;
            ;
            print_single(s);
        }
        U64_delete(_fi232, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        U64 *_fi237 = malloc(sizeof(U64));
        *_fi237 = 0;
        while (1) {
            U64 _t239; { U64 *_hp = Array_len(parts); _t239 = *_hp; free(_hp); }
            Bool _wcond238; { Bool *_hp = U64_lt(_fi237, &(U64){_t239}); _wcond238 = *_hp; free(_hp); }
            ;
            if (_wcond238) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi237);
            U64 _t240 = 1;
            U64 _t241 = U64_add(DEREF(_fi237), _t240);
            ;
            *_fi237 = _t241;
            ;
            print_single(s);
        }
        U64_delete(_fi237, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 total = 0;
    {
        U64 *_fi242 = malloc(sizeof(U64));
        *_fi242 = 0;
        while (1) {
            U64 _t244; { U64 *_hp = Array_len(parts); _t244 = *_hp; free(_hp); }
            Bool _wcond243; { Bool *_hp = U64_lt(_fi242, &(U64){_t244}); _wcond243 = *_hp; free(_hp); }
            ;
            if (_wcond243) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi242);
            U64 _t245 = 1;
            U64 _t246 = U64_add(DEREF(_fi242), _t245);
            ;
            *_fi242 = _t246;
            ;
            U64 _t247; { U64 *_hp = Str_len(s); _t247 = *_hp; free(_hp); }
            U64 _t248 = U64_add(total, _t247);
            ;
            total = _t248;
            ;
        }
        U64_delete(_fi242, &(Bool){1});
    }
    U8 *buf = malloc(total);
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
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
            void *_t254 = ptr_add(buf, DEREF(offset));
            U64 _t255; { U64 *_hp = Str_len(s); _t255 = *_hp; free(_hp); }
            memcpy(_t254, s->c_str, _t255);
            ;
            U64 _t256; { U64 *_hp = Str_len(s); _t256 = *_hp; free(_hp); }
            U64 _t257 = U64_add(DEREF(offset), _t256);
            ;
            *offset = _t257;
            ;
        }
        U64_delete(_fi249, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t258 = U64_clone(&(U64){total});
    U64 _t259 = U64_clone(&(U64){total});
    ;
    Str *_t260 = malloc(sizeof(Str));
    _t260->c_str = buf;
    _t260->count = _t258;
    _t260->cap = _t259;
    ;
    ;
    return _t260;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        I64 _t261 = 0;
        I64 _t262 = 1;
        I64 _t263 = I64_sub(_t261, _t262);
        ;
        ;
        Bool _t264; { Bool *_hp = I64_neq(&(I64){status}, &(I64){_t263}); _t264 = *_hp; free(_hp); }
        ;
        if (_t264) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t265 = 50;
        sleep_ms(_t265);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t271; { U64 *_hp = Array_len(args); _t271 = *_hp; free(_hp); }
        Bool _wcond266; { Bool *_hp = U64_lt(i, &(U64){_t271}); _wcond266 = *_hp; free(_hp); }
        ;
        if (_wcond266) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        U64 _t272 = 0;
        Bool _t273; { Bool *_hp = U64_gt(i, &(U64){_t272}); _t273 = *_hp; free(_hp); }
        ;
        if (_t273) {
            Str *_t267 = Str_lit(" '", 2ULL);
            Str *_t268 = Str_concat(cmd, _t267);
            Str_delete(_t267, &(Bool){1});
            Str *_t269 = Str_concat(_t268, arg);
            Str_delete(_t268, &(Bool){1});
            Str *_t270 = Str_lit("'", 1ULL);
            cmd = Str_concat(_t269, _t270);
            Str_delete(_t269, &(Bool){1});
            Str_delete(_t270, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t274 = 1;
        U64 _t275 = U64_add(DEREF(i), _t274);
        ;
        *i = _t275;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    Str *_t276 = Str_lit(" > ", 3ULL);
    Str *_t277 = Str_concat(cmd, _t276);
    Str_delete(_t276, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t278 = Str_concat(_t277, tmpf);
    Str_delete(_t277, &(Bool){1});
    Str *_t279 = Str_lit(" 2>&1", 5ULL);
    Str *_t280 = Str_concat(_t278, _t279);
    Str_delete(_t278, &(Bool){1});
    Str_delete(_t279, &(Bool){1});
    I64 pid; { I64 *_hp = spawn_cmd(_t280); pid = *_hp; free(_hp); }
    Str_delete(_t280, &(Bool){1});
    I64 ec; { I64 *_hp = wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    ;
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 _t281; { U64 *_hp = Str_size(); _t281 = *_hp; free(_hp); }
    memcpy(output, content, _t281);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    Str *_t282 = Str_lit("Str", 3ULL);
    U64 _t283; { U64 *_hp = Str_size(); _t283 = *_hp; free(_hp); }
    U64 _t284 = 3;
    Array *_va0 = Array_new(_t282, &(U64){_t283}, &(U64){_t284});
    Str_delete(_t282, &(Bool){1});
    ;
    ;
    U64 _t285 = 0;
    Str *_t286 = Str_clone(loc_str);
    Array_set(_va0, &(U64){_t285}, _t286);
    ;
    U64 _t287 = 1;
    Str *_t288 = Str_lit(": panic: ", 9ULL);
    Array_set(_va0, &(U64){_t287}, _t288);
    ;
    U64 _t289 = 2;
    Str *_t290 = format(parts);
    Array_set(_va0, &(U64){_t289}, _t290);
    ;
    println(_va0);
    I64 _t291 = 1;
    exit(_t291);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t292 = Str_lit("Str", 3ULL);
    U64 _t293; { U64 *_hp = Str_size(); _t293 = *_hp; free(_hp); }
    U64 _t294 = 2;
    Array *_va1 = Array_new(_t292, &(U64){_t293}, &(U64){_t294});
    Str_delete(_t292, &(Bool){1});
    ;
    ;
    U64 _t295 = 0;
    Str *_t296 = Str_lit("TODO: ", 6ULL);
    Array_set(_va1, &(U64){_t295}, _t296);
    ;
    U64 _t297 = 1;
    Str *_t298 = format(parts);
    Array_set(_va1, &(U64){_t297}, _t298);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t299 = Str_lit("Str", 3ULL);
    U64 _t300; { U64 *_hp = Str_size(); _t300 = *_hp; free(_hp); }
    U64 _t301 = 1;
    Array *_va2 = Array_new(_t299, &(U64){_t300}, &(U64){_t301});
    Str_delete(_t299, &(Bool){1});
    ;
    ;
    U64 _t302 = 0;
    Str *_t303 = Str_lit("unreachable", 11ULL);
    Array_set(_va2, &(U64){_t302}, _t303);
    ;
    panic(loc_str, _va2);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool _t311 = Bool_not(DEREF(cond));
    if (_t311) {
        Str *_t304 = Str_lit("Str", 3ULL);
        U64 _t305; { U64 *_hp = Str_size(); _t305 = *_hp; free(_hp); }
        U64 _t306 = 2;
        Array *_va3 = Array_new(_t304, &(U64){_t305}, &(U64){_t306});
        Str_delete(_t304, &(Bool){1});
        ;
        ;
        U64 _t307 = 0;
        Str *_t308 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va3, &(U64){_t307}, _t308);
        ;
        U64 _t309 = 1;
        Str *_t310 = format(parts);
        Array_set(_va3, &(U64){_t309}, _t310);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t312 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t312; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t313 = Str_lit("Str", 3ULL);
    U64 _t314; { U64 *_hp = Str_size(); _t314 = *_hp; free(_hp); }
    U64 _t315 = 0;
    Array *_va4 = Array_new(_t313, &(U64){_t314}, &(U64){_t315});
    Str_delete(_t313, &(Bool){1});
    ;
    ;
    Bool _t316; { Bool *_hp = assertm(loc_str, cond, _va4); _t316 = *_hp; free(_hp); }
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t316; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t317 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool _t318; { Bool *_hp = assertm(loc_str, cond, _t317); _t318 = *_hp; free(_hp); }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool _t332; { Bool *_hp = I64_neq(a, b); _t332 = *_hp; free(_hp); }
    if (_t332) {
        Str *_t319 = Str_lit("Str", 3ULL);
        U64 _t320; { U64 *_hp = Str_size(); _t320 = *_hp; free(_hp); }
        U64 _t321 = 5;
        Array *_va5 = Array_new(_t319, &(U64){_t320}, &(U64){_t321});
        Str_delete(_t319, &(Bool){1});
        ;
        ;
        U64 _t322 = 0;
        Str *_t323 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va5, &(U64){_t322}, _t323);
        ;
        U64 _t324 = 1;
        Str *_t325 = I64_to_str(a);
        Array_set(_va5, &(U64){_t324}, _t325);
        ;
        U64 _t326 = 2;
        Str *_t327 = Str_lit("', found '", 10ULL);
        Array_set(_va5, &(U64){_t326}, _t327);
        ;
        U64 _t328 = 3;
        Str *_t329 = I64_to_str(b);
        Array_set(_va5, &(U64){_t328}, _t329);
        ;
        U64 _t330 = 4;
        Str *_t331 = Str_lit("'", 1ULL);
        Array_set(_va5, &(U64){_t330}, _t331);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool _t346; { Bool *_hp = Str_eq(a, b); _t346 = *_hp; free(_hp); }
    Bool _t347 = Bool_not(_t346);
    ;
    if (_t347) {
        Str *_t333 = Str_lit("Str", 3ULL);
        U64 _t334; { U64 *_hp = Str_size(); _t334 = *_hp; free(_hp); }
        U64 _t335 = 5;
        Array *_va6 = Array_new(_t333, &(U64){_t334}, &(U64){_t335});
        Str_delete(_t333, &(Bool){1});
        ;
        ;
        U64 _t336 = 0;
        Str *_t337 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va6, &(U64){_t336}, _t337);
        ;
        U64 _t338 = 1;
        Str *_t339 = Str_clone(a);
        Array_set(_va6, &(U64){_t338}, _t339);
        ;
        U64 _t340 = 2;
        Str *_t341 = Str_lit("', found '", 10ULL);
        Array_set(_va6, &(U64){_t340}, _t341);
        ;
        U64 _t342 = 3;
        Str *_t343 = Str_clone(b);
        Array_set(_va6, &(U64){_t342}, _t343);
        ;
        U64 _t344 = 4;
        Str *_t345 = Str_lit("'", 1ULL);
        Array_set(_va6, &(U64){_t344}, _t345);
        ;
        panic(loc_str, _va6);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    void *_t348 = calloc(DEREF(cap), DEREF(elem_size));
    U64 _t349 = U64_clone(cap);
    U64 _t350 = U64_clone(elem_size);
    Array *_t351 = malloc(sizeof(Array));
    _t351->data = _t348;
    _t351->cap = _t349;
    _t351->elem_size = _t350;
    { Str *_ca = Str_clone(elem_type); _t351->elem_type = *_ca; free(_ca); }
    ;
    ;
    return _t351;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    Bool _t366; { Bool *_hp = U64_gte(i, &self->cap); _t366 = *_hp; free(_hp); }
    if (_t366) {
        Str *_t352 = Str_lit("Str", 3ULL);
        U64 _t353; { U64 *_hp = Str_size(); _t353 = *_hp; free(_hp); }
        U64 _t354 = 5;
        Array *_va7 = Array_new(_t352, &(U64){_t353}, &(U64){_t354});
        Str_delete(_t352, &(Bool){1});
        ;
        ;
        U64 _t355 = 0;
        Str *_t356 = Str_lit("Array.get: index ", 17ULL);
        Array_set(_va7, &(U64){_t355}, _t356);
        ;
        U64 _t357 = 1;
        Str *_t358 = U64_to_str(DEREF(i));
        Array_set(_va7, &(U64){_t357}, _t358);
        ;
        U64 _t359 = 2;
        Str *_t360 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va7, &(U64){_t359}, _t360);
        ;
        U64 _t361 = 3;
        Str *_t362 = U64_to_str(self->cap);
        Array_set(_va7, &(U64){_t361}, _t362);
        ;
        U64 _t363 = 4;
        Str *_t364 = Str_lit(")", 1ULL);
        Array_set(_va7, &(U64){_t363}, _t364);
        ;
        Str *_t365 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:19:19", 62ULL);
        panic(_t365, _va7);
        Str_delete(_t365, &(Bool){1});
    }
    ;
    U64 *_t367 = malloc(sizeof(U64)); *_t367 = U64_mul(DEREF(i), self->elem_size);
    void *_t368 = ptr_add(self->data, DEREF(_t367));
    U64_delete(_t367, &(Bool){1});
    return _t368;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    Bool _t383; { Bool *_hp = U64_gte(i, &self->cap); _t383 = *_hp; free(_hp); }
    if (_t383) {
        Str *_t369 = Str_lit("Str", 3ULL);
        U64 _t370; { U64 *_hp = Str_size(); _t370 = *_hp; free(_hp); }
        U64 _t371 = 5;
        Array *_va8 = Array_new(_t369, &(U64){_t370}, &(U64){_t371});
        Str_delete(_t369, &(Bool){1});
        ;
        ;
        U64 _t372 = 0;
        Str *_t373 = Str_lit("Array.set: index ", 17ULL);
        Array_set(_va8, &(U64){_t372}, _t373);
        ;
        U64 _t374 = 1;
        Str *_t375 = U64_to_str(DEREF(i));
        Array_set(_va8, &(U64){_t374}, _t375);
        ;
        U64 _t376 = 2;
        Str *_t377 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va8, &(U64){_t376}, _t377);
        ;
        U64 _t378 = 3;
        Str *_t379 = U64_to_str(self->cap);
        Array_set(_va8, &(U64){_t378}, _t379);
        ;
        U64 _t380 = 4;
        Str *_t381 = Str_lit(")", 1ULL);
        Array_set(_va8, &(U64){_t380}, _t381);
        ;
        Str *_t382 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:27:19", 62ULL);
        panic(_t382, _va8);
        Str_delete(_t382, &(Bool){1});
    }
    ;
    U64 *_t384 = malloc(sizeof(U64)); *_t384 = U64_mul(DEREF(i), self->elem_size);
    void *_t385 = ptr_add(self->data, DEREF(_t384));
    Bool _t386 = 0;
    dyn_call_delete(&self->elem_type, _t385, &(Bool){_t386});
    U64_delete(_t384, &(Bool){1});
    ;
    U64 *_t387 = malloc(sizeof(U64)); *_t387 = U64_mul(DEREF(i), self->elem_size);
    void *_t388 = ptr_add(self->data, DEREF(_t387));
    memcpy(_t388, val, self->elem_size);
    U64_delete(_t387, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    {
        U64 _fi389 = 0;
        while (1) {
            U64 _t391 = 0;
            Range *_t392 = Range_new(_t391, self->cap);
            ;
            U64 _t393; { U64 *_hp = Range_len(_t392); _t393 = *_hp; free(_hp); }
            Range_delete(_t392, &(Bool){1});
            Bool _wcond390; { Bool *_hp = U64_lt(&(U64){_fi389}, &(U64){_t393}); _wcond390 = *_hp; free(_hp); }
            ;
            if (_wcond390) {
            } else {
                ;
                break;
            }
            ;
            U64 _t394 = 0;
            Range *_t395 = Range_new(_t394, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t395, _fi389); i = *_hp; free(_hp); }
            Range_delete(_t395, &(Bool){1});
            U64 _t396 = 1;
            U64 _t397 = U64_add(_fi389, _t396);
            ;
            _fi389 = _t397;
            ;
            U64 *_t398 = malloc(sizeof(U64)); *_t398 = U64_mul(i, self->elem_size);
            ;
            void *_t399 = ptr_add(self->data, DEREF(_t398));
            Bool _t400 = 0;
            dyn_call_delete(&self->elem_type, _t399, &(Bool){_t400});
            U64_delete(_t398, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t401 = 0;
    Str_delete(&self->elem_type, &(Bool){_t401});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t415 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t415);
    ;
    {
        U64 _fi402 = 0;
        while (1) {
            U64 _t404 = 0;
            Range *_t405 = Range_new(_t404, self->cap);
            ;
            U64 _t406; { U64 *_hp = Range_len(_t405); _t406 = *_hp; free(_hp); }
            Range_delete(_t405, &(Bool){1});
            Bool _wcond403; { Bool *_hp = U64_lt(&(U64){_fi402}, &(U64){_t406}); _wcond403 = *_hp; free(_hp); }
            ;
            if (_wcond403) {
            } else {
                ;
                break;
            }
            ;
            U64 _t407 = 0;
            Range *_t408 = Range_new(_t407, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t408, _fi402); i = *_hp; free(_hp); }
            Range_delete(_t408, &(Bool){1});
            U64 _t409 = 1;
            U64 _t410 = U64_add(_fi402, _t409);
            ;
            _fi402 = _t410;
            ;
            U64 *_t411 = malloc(sizeof(U64)); *_t411 = U64_mul(i, self->elem_size);
            void *_t412 = ptr_add(self->data, DEREF(_t411));
            void *cloned = dyn_call_clone(&self->elem_type, _t412);
            U64_delete(_t411, &(Bool){1});
            U64 *_t413 = malloc(sizeof(U64)); *_t413 = U64_mul(i, self->elem_size);
            ;
            void *_t414 = ptr_add(new_data, DEREF(_t413));
            memcpy(_t414, cloned, self->elem_size);
            U64_delete(_t413, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t416 = malloc(sizeof(Array));
    _t416->data = new_data;
    _t416->cap = self->cap;
    _t416->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t416->elem_type = *_ca; free(_ca); }
    return _t416;
}

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    Bool _t430; { Bool *_hp = Str_is_empty(key_type); _t430 = *_hp; free(_hp); }
    Bool _t431 = Bool_not(_t430);
    ;
    if (_t431) {
        Bool _t428 = dyn_has_cmp(key_type);
        Bool _t429 = Bool_not(_t428);
        ;
        if (_t429) {
            Str *_t418 = Str_lit("Str", 3ULL);
            U64 _t419; { U64 *_hp = Str_size(); _t419 = *_hp; free(_hp); }
            U64 _t420 = 3;
            Array *_va9 = Array_new(_t418, &(U64){_t419}, &(U64){_t420});
            Str_delete(_t418, &(Bool){1});
            ;
            ;
            U64 _t421 = 0;
            Str *_t422 = Str_lit("Map.new: type ", 14ULL);
            Array_set(_va9, &(U64){_t421}, _t422);
            ;
            U64 _t423 = 1;
            Str *_t424 = Str_clone(key_type);
            Array_set(_va9, &(U64){_t423}, _t424);
            ;
            U64 _t425 = 2;
            Str *_t426 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va9, &(U64){_t425}, _t426);
            ;
            Str *_t427 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
            panic(_t427, _va9);
            Str_delete(_t427, &(Bool){1});
        }
        ;
    }
    ;
    void *_t432 = malloc(DEREF(key_size));
    void *_t433 = malloc(DEREF(val_size));
    U64 _t434 = 0;
    I64 _t435 = 1;
    U64 _t436 = U64_clone(key_size);
    U64 _t437 = U64_clone(val_size);
    Map *_t438 = malloc(sizeof(Map));
    _t438->key_data = _t432;
    _t438->val_data = _t433;
    _t438->count = _t434;
    _t438->cap = _t435;
    _t438->key_size = _t436;
    { Str *_ca = Str_clone(key_type); _t438->key_type = *_ca; free(_ca); }
    _t438->val_size = _t437;
    { Str *_ca = Str_clone(val_type); _t438->val_type = *_ca; free(_ca); }
    ;
    ;
    ;
    ;
    return _t438;
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
        Bool _wcond439; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond439 = *_hp; free(_hp); }
        if (_wcond439) {
        } else {
            ;
            break;
        }
        ;
        U64 _t446 = U64_sub(hi, lo);
        U64 _t447 = 2;
        U64 _t448 = U64_div(_t446, _t447);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t448);
        ;
        U64 *_t449 = malloc(sizeof(U64)); *_t449 = U64_mul(DEREF(mid), self->key_size);
        void *_t450 = ptr_add(self->key_data, DEREF(_t449));
        I64 *c = dyn_call_cmp(&self->key_type, _t450, key);
        U64_delete(_t449, &(Bool){1});
        I64 _t451 = 0;
        Bool _t452; { Bool *_hp = I64_lt(c, &(I64){_t451}); _t452 = *_hp; free(_hp); }
        ;
        if (_t452) {
            U64 _t440 = 1;
            U64 _t441 = U64_add(DEREF(mid), _t440);
            ;
            lo = _t441;
            ;
        } else {
            I64 _t444 = 0;
            Bool _t445; { Bool *_hp = I64_gt(c, &(I64){_t444}); _t445 = *_hp; free(_hp); }
            ;
            if (_t445) {
                U64 _t442 = U64_clone(mid);
                hi = _t442;
                ;
            } else {
                Bool _t443 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t443; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t453 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t453; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond454; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond454 = *_hp; free(_hp); }
        if (_wcond454) {
        } else {
            ;
            break;
        }
        ;
        U64 _t462 = U64_sub(hi, lo);
        U64 _t463 = 2;
        U64 _t464 = U64_div(_t462, _t463);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t464);
        ;
        U64 *_t465 = malloc(sizeof(U64)); *_t465 = U64_mul(DEREF(mid), self->key_size);
        void *_t466 = ptr_add(self->key_data, DEREF(_t465));
        I64 *c = dyn_call_cmp(&self->key_type, _t466, key);
        U64_delete(_t465, &(Bool){1});
        I64 _t467 = 0;
        Bool _t468; { Bool *_hp = I64_lt(c, &(I64){_t467}); _t468 = *_hp; free(_hp); }
        ;
        if (_t468) {
            U64 _t455 = 1;
            U64 _t456 = U64_add(DEREF(mid), _t455);
            ;
            lo = _t456;
            ;
        } else {
            I64 _t460 = 0;
            Bool _t461; { Bool *_hp = I64_gt(c, &(I64){_t460}); _t461 = *_hp; free(_hp); }
            ;
            if (_t461) {
                U64 _t457 = U64_clone(mid);
                hi = _t457;
                ;
            } else {
                U64 *_t458 = malloc(sizeof(U64)); *_t458 = U64_mul(DEREF(mid), self->val_size);
                void *_t459 = ptr_add(self->val_data, DEREF(_t458));
                U64_delete(_t458, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t459;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t469 = Str_lit("Str", 3ULL);
    U64 _t470; { U64 *_hp = Str_size(); _t470 = *_hp; free(_hp); }
    U64 _t471 = 1;
    Array *_va10 = Array_new(_t469, &(U64){_t470}, &(U64){_t471});
    Str_delete(_t469, &(Bool){1});
    ;
    ;
    U64 _t472 = 0;
    Str *_t473 = Str_lit("Map.get: key not found", 22ULL);
    Array_set(_va10, &(U64){_t472}, _t473);
    ;
    Str *_t474 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
    panic(_t474, _va10);
    Str_delete(_t474, &(Bool){1});
    U64 *_t475 = malloc(sizeof(U64));
    *_t475 = 0;
    void *_t476 = ptr_add(self->val_data, DEREF(_t475));
    U64_delete(_t475, &(Bool){1});
    return _t476;
}

void Map_set(Map * self, void * key, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond477; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond477 = *_hp; free(_hp); }
        if (_wcond477) {
        } else {
            ;
            break;
        }
        ;
        U64 _t486 = U64_sub(hi, lo);
        U64 _t487 = 2;
        U64 _t488 = U64_div(_t486, _t487);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t488);
        ;
        U64 *_t489 = malloc(sizeof(U64)); *_t489 = U64_mul(DEREF(mid), self->key_size);
        void *_t490 = ptr_add(self->key_data, DEREF(_t489));
        I64 *c = dyn_call_cmp(&self->key_type, _t490, key);
        U64_delete(_t489, &(Bool){1});
        I64 _t491 = 0;
        Bool _t492; { Bool *_hp = I64_lt(c, &(I64){_t491}); _t492 = *_hp; free(_hp); }
        ;
        if (_t492) {
            U64 _t478 = 1;
            U64 _t479 = U64_add(DEREF(mid), _t478);
            ;
            lo = _t479;
            ;
        } else {
            I64 _t484 = 0;
            Bool _t485; { Bool *_hp = I64_gt(c, &(I64){_t484}); _t485 = *_hp; free(_hp); }
            ;
            if (_t485) {
                U64 _t480 = U64_clone(mid);
                hi = _t480;
                ;
            } else {
                Bool _t481 = 1;
                found = _t481;
                ;
                U64 _t482 = U64_clone(mid);
                lo = _t482;
                ;
                U64 _t483 = U64_clone(mid);
                hi = _t483;
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
        Bool _t497; { Bool *_hp = Str_is_empty(&self->key_type); _t497 = *_hp; free(_hp); }
        Bool _t498 = Bool_not(_t497);
        ;
        if (_t498) {
            Bool _t493 = 0;
            dyn_call_delete(&self->key_type, key, &(Bool){_t493});
            ;
        }
        ;
        free(key);
        Bool _t499; { Bool *_hp = Str_is_empty(&self->val_type); _t499 = *_hp; free(_hp); }
        Bool _t500 = Bool_not(_t499);
        ;
        if (_t500) {
            U64 *_t494 = malloc(sizeof(U64)); *_t494 = U64_mul(lo, self->val_size);
            void *_t495 = ptr_add(self->val_data, DEREF(_t494));
            Bool _t496 = 0;
            dyn_call_delete(&self->val_type, _t495, &(Bool){_t496});
            U64_delete(_t494, &(Bool){1});
            ;
        }
        ;
        U64 *_t501 = malloc(sizeof(U64)); *_t501 = U64_mul(lo, self->val_size);
        void *_t502 = ptr_add(self->val_data, DEREF(_t501));
        memcpy(_t502, val, self->val_size);
        U64_delete(_t501, &(Bool){1});
        free(val);
    } else {
        Bool _t509 = U64_eq(self->count, self->cap);
        if (_t509) {
            U64 _t503 = 2;
            U64 new_cap = U64_mul(self->cap, _t503);
            ;
            U64 _t504 = U64_mul(new_cap, self->key_size);
            void *_t505 = realloc(self->key_data, _t504);
            ;
            self->key_data = _t505;
            U64 _t506 = U64_mul(new_cap, self->val_size);
            void *_t507 = realloc(self->val_data, _t506);
            ;
            self->val_data = _t507;
            U64 _t508 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t508;
            ;
        }
        ;
        U64 _t510 = 1;
        U64 _t511 = U64_add(lo, _t510);
        ;
        U64 *_t512 = malloc(sizeof(U64)); *_t512 = U64_mul(_t511, self->key_size);
        ;
        U64 *_t513 = malloc(sizeof(U64)); *_t513 = U64_mul(lo, self->key_size);
        U64 _t514 = U64_sub(self->count, lo);
        void *_t515 = ptr_add(self->key_data, DEREF(_t512));
        void *_t516 = ptr_add(self->key_data, DEREF(_t513));
        U64 _t517 = U64_mul(_t514, self->key_size);
        ;
        memmove(_t515, _t516, _t517);
        U64_delete(_t512, &(Bool){1});
        U64_delete(_t513, &(Bool){1});
        ;
        U64 _t518 = 1;
        U64 _t519 = U64_add(lo, _t518);
        ;
        U64 *_t520 = malloc(sizeof(U64)); *_t520 = U64_mul(_t519, self->val_size);
        ;
        U64 *_t521 = malloc(sizeof(U64)); *_t521 = U64_mul(lo, self->val_size);
        U64 _t522 = U64_sub(self->count, lo);
        void *_t523 = ptr_add(self->val_data, DEREF(_t520));
        void *_t524 = ptr_add(self->val_data, DEREF(_t521));
        U64 _t525 = U64_mul(_t522, self->val_size);
        ;
        memmove(_t523, _t524, _t525);
        U64_delete(_t520, &(Bool){1});
        U64_delete(_t521, &(Bool){1});
        ;
        U64 *_t526 = malloc(sizeof(U64)); *_t526 = U64_mul(lo, self->key_size);
        void *_t527 = ptr_add(self->key_data, DEREF(_t526));
        memcpy(_t527, key, self->key_size);
        U64_delete(_t526, &(Bool){1});
        U64 *_t528 = malloc(sizeof(U64)); *_t528 = U64_mul(lo, self->val_size);
        void *_t529 = ptr_add(self->val_data, DEREF(_t528));
        memcpy(_t529, val, self->val_size);
        U64_delete(_t528, &(Bool){1});
        free(key);
        free(val);
        U64 _t530 = 1;
        U64 _t531 = U64_add(self->count, _t530);
        ;
        self->count = _t531;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    Bool _t558; { Bool *_hp = Str_is_empty(&self->key_type); _t558 = *_hp; free(_hp); }
    Bool _t559 = Bool_not(_t558);
    ;
    if (_t559) {
        {
            U64 _fi532 = 0;
            while (1) {
                U64 _t534 = 0;
                Range *_t535 = Range_new(_t534, self->count);
                ;
                U64 _t536; { U64 *_hp = Range_len(_t535); _t536 = *_hp; free(_hp); }
                Range_delete(_t535, &(Bool){1});
                Bool _wcond533; { Bool *_hp = U64_lt(&(U64){_fi532}, &(U64){_t536}); _wcond533 = *_hp; free(_hp); }
                ;
                if (_wcond533) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t537 = 0;
                Range *_t538 = Range_new(_t537, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t538, _fi532); i = *_hp; free(_hp); }
                Range_delete(_t538, &(Bool){1});
                U64 _t539 = 1;
                U64 _t540 = U64_add(_fi532, _t539);
                ;
                _fi532 = _t540;
                ;
                U64 *_t541 = malloc(sizeof(U64)); *_t541 = U64_mul(i, self->key_size);
                ;
                void *_t542 = ptr_add(self->key_data, DEREF(_t541));
                Bool _t543 = 0;
                dyn_call_delete(&self->key_type, _t542, &(Bool){_t543});
                U64_delete(_t541, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t560; { Bool *_hp = Str_is_empty(&self->val_type); _t560 = *_hp; free(_hp); }
    Bool _t561 = Bool_not(_t560);
    ;
    if (_t561) {
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
                U64 *_t553 = malloc(sizeof(U64)); *_t553 = U64_mul(i, self->val_size);
                ;
                void *_t554 = ptr_add(self->val_data, DEREF(_t553));
                Bool _t555 = 0;
                dyn_call_delete(&self->val_type, _t554, &(Bool){_t555});
                U64_delete(_t553, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t562; { Bool *_hp = Str_is_empty(&self->key_type); _t562 = *_hp; free(_hp); }
    Bool _t563 = Bool_not(_t562);
    ;
    if (_t563) {
        Bool _t556 = 0;
        Str_delete(&self->key_type, &(Bool){_t556});
        ;
    }
    ;
    Bool _t564; { Bool *_hp = Str_is_empty(&self->val_type); _t564 = *_hp; free(_hp); }
    Bool _t565 = Bool_not(_t564);
    ;
    if (_t565) {
        Bool _t557 = 0;
        Str_delete(&self->val_type, &(Bool){_t557});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t583 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(_t583);
    ;
    U64 _t584 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(_t584);
    ;
    {
        U64 _fi566 = 0;
        while (1) {
            U64 _t568 = 0;
            Range *_t569 = Range_new(_t568, self->count);
            ;
            U64 _t570; { U64 *_hp = Range_len(_t569); _t570 = *_hp; free(_hp); }
            Range_delete(_t569, &(Bool){1});
            Bool _wcond567; { Bool *_hp = U64_lt(&(U64){_fi566}, &(U64){_t570}); _wcond567 = *_hp; free(_hp); }
            ;
            if (_wcond567) {
            } else {
                ;
                break;
            }
            ;
            U64 _t571 = 0;
            Range *_t572 = Range_new(_t571, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t572, _fi566); i = *_hp; free(_hp); }
            Range_delete(_t572, &(Bool){1});
            U64 _t573 = 1;
            U64 _t574 = U64_add(_fi566, _t573);
            ;
            _fi566 = _t574;
            ;
            U64 *_t575 = malloc(sizeof(U64)); *_t575 = U64_mul(i, self->key_size);
            void *_t576 = ptr_add(self->key_data, DEREF(_t575));
            void *ck = dyn_call_clone(&self->key_type, _t576);
            U64_delete(_t575, &(Bool){1});
            U64 *_t577 = malloc(sizeof(U64)); *_t577 = U64_mul(i, self->key_size);
            void *_t578 = ptr_add(new_keys, DEREF(_t577));
            memcpy(_t578, ck, self->key_size);
            U64_delete(_t577, &(Bool){1});
            free(ck);
            U64 *_t579 = malloc(sizeof(U64)); *_t579 = U64_mul(i, self->val_size);
            void *_t580 = ptr_add(self->val_data, DEREF(_t579));
            void *cv = dyn_call_clone(&self->val_type, _t580);
            U64_delete(_t579, &(Bool){1});
            U64 *_t581 = malloc(sizeof(U64)); *_t581 = U64_mul(i, self->val_size);
            ;
            void *_t582 = ptr_add(new_vals, DEREF(_t581));
            memcpy(_t582, cv, self->val_size);
            U64_delete(_t581, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t585 = malloc(sizeof(Map));
    _t585->key_data = new_keys;
    _t585->val_data = new_vals;
    _t585->count = self->count;
    _t585->cap = self->cap;
    _t585->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t585->key_type = *_ca; free(_ca); }
    _t585->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t585->val_type = *_ca; free(_ca); }
    return _t585;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    Bool _t599; { Bool *_hp = Str_is_empty(elem_type); _t599 = *_hp; free(_hp); }
    Bool _t600 = Bool_not(_t599);
    ;
    if (_t600) {
        Bool _t597 = dyn_has_cmp(elem_type);
        Bool _t598 = Bool_not(_t597);
        ;
        if (_t598) {
            Str *_t587 = Str_lit("Str", 3ULL);
            U64 _t588; { U64 *_hp = Str_size(); _t588 = *_hp; free(_hp); }
            U64 _t589 = 3;
            Array *_va11 = Array_new(_t587, &(U64){_t588}, &(U64){_t589});
            Str_delete(_t587, &(Bool){1});
            ;
            ;
            U64 _t590 = 0;
            Str *_t591 = Str_lit("Set.new: type ", 14ULL);
            Array_set(_va11, &(U64){_t590}, _t591);
            ;
            U64 _t592 = 1;
            Str *_t593 = Str_clone(elem_type);
            Array_set(_va11, &(U64){_t592}, _t593);
            ;
            U64 _t594 = 2;
            Str *_t595 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va11, &(U64){_t594}, _t595);
            ;
            Str *_t596 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
            panic(_t596, _va11);
            Str_delete(_t596, &(Bool){1});
        }
        ;
    }
    ;
    void *_t601 = malloc(DEREF(elem_size));
    U64 _t602 = 0;
    I64 _t603 = 1;
    U64 _t604 = U64_clone(elem_size);
    Set *_t605 = malloc(sizeof(Set));
    _t605->data = _t601;
    _t605->count = _t602;
    _t605->cap = _t603;
    _t605->elem_size = _t604;
    { Str *_ca = Str_clone(elem_type); _t605->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t605;
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
        Bool _wcond606; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond606 = *_hp; free(_hp); }
        if (_wcond606) {
        } else {
            ;
            break;
        }
        ;
        U64 _t613 = U64_sub(hi, lo);
        U64 _t614 = 2;
        U64 _t615 = U64_div(_t613, _t614);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t615);
        ;
        U64 *_t616 = malloc(sizeof(U64)); *_t616 = U64_mul(DEREF(mid), self->elem_size);
        void *_t617 = ptr_add(self->data, DEREF(_t616));
        I64 *c = dyn_call_cmp(&self->elem_type, _t617, val);
        U64_delete(_t616, &(Bool){1});
        I64 _t618 = 0;
        Bool _t619; { Bool *_hp = I64_lt(c, &(I64){_t618}); _t619 = *_hp; free(_hp); }
        ;
        if (_t619) {
            U64 _t607 = 1;
            U64 _t608 = U64_add(DEREF(mid), _t607);
            ;
            lo = _t608;
            ;
        } else {
            I64 _t611 = 0;
            Bool _t612; { Bool *_hp = I64_gt(c, &(I64){_t611}); _t612 = *_hp; free(_hp); }
            ;
            if (_t612) {
                U64 _t609 = U64_clone(mid);
                hi = _t609;
                ;
            } else {
                Bool _t610 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t610; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t620 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t620; return _r; }
}

void Set_add(Set * self, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond621; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond621 = *_hp; free(_hp); }
        if (_wcond621) {
        } else {
            ;
            break;
        }
        ;
        U64 _t630 = U64_sub(hi, lo);
        U64 _t631 = 2;
        U64 _t632 = U64_div(_t630, _t631);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t632);
        ;
        U64 *_t633 = malloc(sizeof(U64)); *_t633 = U64_mul(DEREF(mid), self->elem_size);
        void *_t634 = ptr_add(self->data, DEREF(_t633));
        I64 *c = dyn_call_cmp(&self->elem_type, _t634, val);
        U64_delete(_t633, &(Bool){1});
        I64 _t635 = 0;
        Bool _t636; { Bool *_hp = I64_lt(c, &(I64){_t635}); _t636 = *_hp; free(_hp); }
        ;
        if (_t636) {
            U64 _t622 = 1;
            U64 _t623 = U64_add(DEREF(mid), _t622);
            ;
            lo = _t623;
            ;
        } else {
            I64 _t628 = 0;
            Bool _t629; { Bool *_hp = I64_gt(c, &(I64){_t628}); _t629 = *_hp; free(_hp); }
            ;
            if (_t629) {
                U64 _t624 = U64_clone(mid);
                hi = _t624;
                ;
            } else {
                Bool _t625 = 1;
                found = _t625;
                ;
                U64 _t626 = U64_clone(mid);
                lo = _t626;
                ;
                U64 _t627 = U64_clone(mid);
                hi = _t627;
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
        Bool _t638; { Bool *_hp = Str_is_empty(&self->elem_type); _t638 = *_hp; free(_hp); }
        Bool _t639 = Bool_not(_t638);
        ;
        if (_t639) {
            Bool _t637 = 0;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t637});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t644 = U64_eq(self->count, self->cap);
        if (_t644) {
            U64 _t640 = 2;
            U64 new_cap = U64_mul(self->cap, _t640);
            ;
            U64 _t641 = U64_mul(new_cap, self->elem_size);
            void *_t642 = realloc(self->data, _t641);
            ;
            self->data = _t642;
            U64 _t643 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t643;
            ;
        }
        ;
        U64 _t645 = 1;
        U64 _t646 = U64_add(lo, _t645);
        ;
        U64 *_t647 = malloc(sizeof(U64)); *_t647 = U64_mul(_t646, self->elem_size);
        ;
        U64 *_t648 = malloc(sizeof(U64)); *_t648 = U64_mul(lo, self->elem_size);
        U64 _t649 = U64_sub(self->count, lo);
        void *_t650 = ptr_add(self->data, DEREF(_t647));
        void *_t651 = ptr_add(self->data, DEREF(_t648));
        U64 _t652 = U64_mul(_t649, self->elem_size);
        ;
        memmove(_t650, _t651, _t652);
        U64_delete(_t647, &(Bool){1});
        U64_delete(_t648, &(Bool){1});
        ;
        U64 *_t653 = malloc(sizeof(U64)); *_t653 = U64_mul(lo, self->elem_size);
        void *_t654 = ptr_add(self->data, DEREF(_t653));
        memcpy(_t654, val, self->elem_size);
        U64_delete(_t653, &(Bool){1});
        free(val);
        U64 _t655 = 1;
        U64 _t656 = U64_add(self->count, _t655);
        ;
        self->count = _t656;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    Bool _t670; { Bool *_hp = Str_is_empty(&self->elem_type); _t670 = *_hp; free(_hp); }
    Bool _t671 = Bool_not(_t670);
    ;
    if (_t671) {
        {
            U64 _fi657 = 0;
            while (1) {
                U64 _t659 = 0;
                Range *_t660 = Range_new(_t659, self->count);
                ;
                U64 _t661; { U64 *_hp = Range_len(_t660); _t661 = *_hp; free(_hp); }
                Range_delete(_t660, &(Bool){1});
                Bool _wcond658; { Bool *_hp = U64_lt(&(U64){_fi657}, &(U64){_t661}); _wcond658 = *_hp; free(_hp); }
                ;
                if (_wcond658) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t662 = 0;
                Range *_t663 = Range_new(_t662, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t663, _fi657); i = *_hp; free(_hp); }
                Range_delete(_t663, &(Bool){1});
                U64 _t664 = 1;
                U64 _t665 = U64_add(_fi657, _t664);
                ;
                _fi657 = _t665;
                ;
                U64 *_t666 = malloc(sizeof(U64)); *_t666 = U64_mul(i, self->elem_size);
                ;
                void *_t667 = ptr_add(self->data, DEREF(_t666));
                Bool _t668 = 0;
                dyn_call_delete(&self->elem_type, _t667, &(Bool){_t668});
                U64_delete(_t666, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t672; { Bool *_hp = Str_is_empty(&self->elem_type); _t672 = *_hp; free(_hp); }
    Bool _t673 = Bool_not(_t672);
    ;
    if (_t673) {
        Bool _t669 = 0;
        Str_delete(&self->elem_type, &(Bool){_t669});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t687 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t687);
    ;
    {
        U64 _fi674 = 0;
        while (1) {
            U64 _t676 = 0;
            Range *_t677 = Range_new(_t676, self->count);
            ;
            U64 _t678; { U64 *_hp = Range_len(_t677); _t678 = *_hp; free(_hp); }
            Range_delete(_t677, &(Bool){1});
            Bool _wcond675; { Bool *_hp = U64_lt(&(U64){_fi674}, &(U64){_t678}); _wcond675 = *_hp; free(_hp); }
            ;
            if (_wcond675) {
            } else {
                ;
                break;
            }
            ;
            U64 _t679 = 0;
            Range *_t680 = Range_new(_t679, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t680, _fi674); i = *_hp; free(_hp); }
            Range_delete(_t680, &(Bool){1});
            U64 _t681 = 1;
            U64 _t682 = U64_add(_fi674, _t681);
            ;
            _fi674 = _t682;
            ;
            U64 *_t683 = malloc(sizeof(U64)); *_t683 = U64_mul(i, self->elem_size);
            void *_t684 = ptr_add(self->data, DEREF(_t683));
            void *cloned = dyn_call_clone(&self->elem_type, _t684);
            U64_delete(_t683, &(Bool){1});
            U64 *_t685 = malloc(sizeof(U64)); *_t685 = U64_mul(i, self->elem_size);
            ;
            void *_t686 = ptr_add(new_data, DEREF(_t685));
            memcpy(_t686, cloned, self->elem_size);
            U64_delete(_t685, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t688 = malloc(sizeof(Set));
    _t688->data = new_data;
    _t688->count = self->count;
    _t688->cap = self->cap;
    _t688->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t688->elem_type = *_ca; free(_ca); }
    return _t688;
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
    Bool _t696; { Bool *_hp = U64_gte(i, &self->count); _t696 = *_hp; free(_hp); }
    if (_t696) {
        Str *_t690 = Str_lit("Str", 3ULL);
        U64 _t691; { U64 *_hp = Str_size(); _t691 = *_hp; free(_hp); }
        U64 _t692 = 1;
        Array *_va12 = Array_new(_t690, &(U64){_t691}, &(U64){_t692});
        Str_delete(_t690, &(Bool){1});
        ;
        ;
        U64 _t693 = 0;
        Str *_t694 = Str_lit("Str.get: index out of bounds", 28ULL);
        Array_set(_va12, &(U64){_t693}, _t694);
        ;
        Str *_t695 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        panic(_t695, _va12);
        Str_delete(_t695, &(Bool){1});
    }
    ;
    void *_t697 = ptr_add(self->c_str, DEREF(i));
    return _t697;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 min_len = a->count;
    Bool _t703; { Bool *_hp = U64_lt(&b->count, &a->count); _t703 = *_hp; free(_hp); }
    if (_t703) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond698; { Bool *_hp = U64_lt(i, &(U64){min_len}); _wcond698 = *_hp; free(_hp); }
        if (_wcond698) {
        } else {
            ;
            break;
        }
        ;
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 _t699 = 0;
        Bool _t700; { Bool *_hp = I64_neq(c, &(I64){_t699}); _t700 = *_hp; free(_hp); }
        ;
        if (_t700) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t701 = 1;
        U64 _t702 = U64_add(DEREF(i), _t701);
        ;
        *i = _t702;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t704 = U64_cmp(a->count, b->count);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t704; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    U64 _t705 = 1;
    U64 _t706 = U64_add(DEREF(new_len), _t705);
    ;
    U8 *new_data = malloc(_t706);
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t707 = ptr_add(new_data, a->count);
    memcpy(_t707, b->c_str, b->count);
    void *_t708 = ptr_add(new_data, DEREF(new_len));
    I64 _t709 = 0;
    U64 _t710 = 1;
    memcpy(_t708, &(I64){_t709}, _t710);
    ;
    ;
    U64 _t711 = U64_clone(new_len);
    U64 _t712 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t713 = malloc(sizeof(Str));
    _t713->c_str = new_data;
    _t713->count = _t711;
    _t713->cap = _t712;
    ;
    ;
    return _t713;
}

Str * Str_with_capacity(U64 * n) {
    U64 _t714 = 1;
    U64 _t715 = U64_add(DEREF(n), _t714);
    ;
    U8 *buf = malloc(_t715);
    ;
    I64 _t716 = 0;
    U64 _t717 = 1;
    memcpy(buf, &(I64){_t716}, _t717);
    ;
    ;
    I64 _t718 = 0;
    U64 _t719 = U64_clone(n);
    Str *_t720 = malloc(sizeof(Str));
    _t720->c_str = buf;
    _t720->count = _t718;
    _t720->cap = _t719;
    ;
    ;
    return _t720;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    Bool _t733; { Bool *_hp = U64_gte(&self->cap, CAP_VIEW); _t733 = *_hp; free(_hp); }
    if (_t733) {
        Str *_t721 = Str_lit("Str", 3ULL);
        U64 _t722; { U64 *_hp = Str_size(); _t722 = *_hp; free(_hp); }
        U64 _t723 = 1;
        Array *_va13 = Array_new(_t721, &(U64){_t722}, &(U64){_t723});
        Str_delete(_t721, &(Bool){1});
        ;
        ;
        U64 _t724 = 0;
        Str *_t725 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        Array_set(_va13, &(U64){_t724}, _t725);
        ;
        Str *_t726 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:52:19", 60ULL);
        panic(_t726, _va13);
        Str_delete(_t726, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool _t734; { Bool *_hp = U64_gt(new_len, &self->cap); _t734 = *_hp; free(_hp); }
    if (_t734) {
        Str *_t727 = Str_lit("Str", 3ULL);
        U64 _t728; { U64 *_hp = Str_size(); _t728 = *_hp; free(_hp); }
        U64 _t729 = 1;
        Array *_va14 = Array_new(_t727, &(U64){_t728}, &(U64){_t729});
        Str_delete(_t727, &(Bool){1});
        ;
        ;
        U64 _t730 = 0;
        Str *_t731 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        Array_set(_va14, &(U64){_t730}, _t731);
        ;
        Str *_t732 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:56:19", 60ULL);
        panic(_t732, _va14);
        Str_delete(_t732, &(Bool){1});
    }
    ;
    void *_t735 = ptr_add(self->c_str, self->count);
    memcpy(_t735, s->c_str, s->count);
    U64 _t736 = U64_clone(new_len);
    self->count = _t736;
    ;
    void *_t737 = ptr_add(self->c_str, DEREF(new_len));
    I64 _t738 = 0;
    U64 _t739 = 1;
    memcpy(_t737, &(I64){_t738}, _t739);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    U64 _t740 = 1;
    U64 _t741 = U64_add(val->count, _t740);
    ;
    U8 *new_data = malloc(_t741);
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t742 = ptr_add(new_data, val->count);
    I64 _t743 = 0;
    U64 _t744 = 1;
    memcpy(_t742, &(I64){_t743}, _t744);
    ;
    ;
    Str *_t745 = malloc(sizeof(Str));
    _t745->c_str = new_data;
    _t745->count = val->count;
    _t745->cap = val->count;
    return _t745;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    Bool _t746; { Bool *_hp = U64_lt(&self->cap, CAP_VIEW); _t746 = *_hp; free(_hp); }
    if (_t746) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t747 = Str_clone(val);
    return _t747;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    U64 ln = U64_clone(n);
    Bool _t749; { Bool *_hp = U64_gt(st, &s->count); _t749 = *_hp; free(_hp); }
    if (_t749) {
        *st = s->count;
    }
    ;
    U64 _t750 = U64_add(DEREF(st), ln);
    Bool _t751; { Bool *_hp = U64_gt(&(U64){_t750}, &s->count); _t751 = *_hp; free(_hp); }
    ;
    if (_t751) {
        U64 _t748 = U64_sub(s->count, DEREF(st));
        ln = _t748;
        ;
    }
    ;
    void *_t752 = ptr_add(s->c_str, DEREF(st));
    U64 _t753 = U64_clone(&(U64){ln});
    ;
    U64 _t754 = U64_clone(CAP_VIEW);
    Str *_t755 = malloc(sizeof(Str));
    _t755->c_str = _t752;
    _t755->count = _t753;
    _t755->cap = _t754;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t755;
}

Bool * Str_contains(Str * a, Str * b) {
    U64 _t769 = 0;
    Bool _t770 = U64_eq(b->count, _t769);
    ;
    if (_t770) {
        Bool _t756 = 1;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t756; return _r; }
    }
    ;
    Bool _t771; { Bool *_hp = U64_gt(&b->count, &a->count); _t771 = *_hp; free(_hp); }
    if (_t771) {
        Bool _t757 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t757; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t766 = U64_sub(a->count, b->count);
        Bool _wcond758; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t766}); _wcond758 = *_hp; free(_hp); }
        ;
        if (_wcond758) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond759; { Bool *_hp = U64_lt(j, &b->count); _wcond759 = *_hp; free(_hp); }
            if (_wcond759) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t761 = malloc(sizeof(U64)); *_t761 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(a, _t761);
            U8 *bc = Str_get(b, j);
            Bool _t762; { Bool *_hp = U8_neq(ac, bc); _t762 = *_hp; free(_hp); }
            U64_delete(_t761, &(Bool){1});
            if (_t762) {
                Bool _t760 = 0;
                found = _t760;
                ;
            }
            ;
            U64 _t763 = 1;
            U64 _t764 = U64_add(DEREF(j), _t763);
            ;
            *j = _t764;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t765 = 1;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t765; return _r; }
        }
        ;
        U64 _t767 = 1;
        U64 _t768 = U64_add(i, _t767);
        ;
        i = _t768;
        ;
    }
    ;
    Bool _t772 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t772; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool _t779; { Bool *_hp = U64_gt(&b->count, &a->count); _t779 = *_hp; free(_hp); }
    if (_t779) {
        Bool _t773 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t773; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond774; { Bool *_hp = U64_lt(i, &b->count); _wcond774 = *_hp; free(_hp); }
        if (_wcond774) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool _t776; { Bool *_hp = U8_neq(ac, bc); _t776 = *_hp; free(_hp); }
        if (_t776) {
            Bool _t775 = 0;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t775; return _r; }
        }
        ;
        U64 _t777 = 1;
        U64 _t778 = U64_add(DEREF(i), _t777);
        ;
        *i = _t778;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t780 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t780; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool _t788; { Bool *_hp = U64_gt(&b->count, &a->count); _t788 = *_hp; free(_hp); }
    if (_t788) {
        Bool _t781 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t781; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond782; { Bool *_hp = U64_lt(i, &b->count); _wcond782 = *_hp; free(_hp); }
        if (_wcond782) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t784 = malloc(sizeof(U64)); *_t784 = U64_add(offset, DEREF(i));
        U8 *ac = Str_get(a, _t784);
        U8 *bc = Str_get(b, i);
        Bool _t785; { Bool *_hp = U8_neq(ac, bc); _t785 = *_hp; free(_hp); }
        U64_delete(_t784, &(Bool){1});
        if (_t785) {
            Bool _t783 = 0;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t783; return _r; }
        }
        ;
        U64 _t786 = 1;
        U64 _t787 = U64_add(DEREF(i), _t786);
        ;
        *i = _t787;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t789 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t789; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t790 = 0;
    Bool _t791 = U64_eq(self->count, _t790);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t791; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    U64 _t809 = 0;
    Bool _t810 = U64_eq(needle->count, _t809);
    ;
    if (_t810) {
        I64 _t792 = 0;
        I64 _t793 = 1;
        I64 _t794 = I64_sub(_t792, _t793);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t794; return _r; }
    }
    ;
    Bool _t811; { Bool *_hp = U64_gt(&needle->count, &self->count); _t811 = *_hp; free(_hp); }
    if (_t811) {
        I64 _t795 = 0;
        I64 _t796 = 1;
        I64 _t797 = I64_sub(_t795, _t796);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t797; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t806 = U64_sub(self->count, needle->count);
        Bool _wcond798; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t806}); _wcond798 = *_hp; free(_hp); }
        ;
        if (_wcond798) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond799; { Bool *_hp = U64_lt(j, &needle->count); _wcond799 = *_hp; free(_hp); }
            if (_wcond799) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t801 = malloc(sizeof(U64)); *_t801 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t801);
            U8 *bc = Str_get(needle, j);
            Bool _t802; { Bool *_hp = U8_neq(ac, bc); _t802 = *_hp; free(_hp); }
            U64_delete(_t801, &(Bool){1});
            if (_t802) {
                Bool _t800 = 0;
                found = _t800;
                ;
            }
            ;
            U64 _t803 = 1;
            U64 _t804 = U64_add(DEREF(j), _t803);
            ;
            *j = _t804;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t805 = U64_to_i64(i);
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t805; return _r; }
        }
        ;
        U64 _t807 = 1;
        U64 _t808 = U64_add(i, _t807);
        ;
        i = _t808;
        ;
    }
    ;
    I64 _t812 = 0;
    I64 _t813 = 1;
    I64 _t814 = I64_sub(_t812, _t813);
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t814; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    U64 _t832 = 0;
    Bool _t833 = U64_eq(needle->count, _t832);
    ;
    if (_t833) {
        I64 _t815 = 0;
        I64 _t816 = 1;
        I64 _t817 = I64_sub(_t815, _t816);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t817; return _r; }
    }
    ;
    Bool _t834; { Bool *_hp = U64_gt(&needle->count, &self->count); _t834 = *_hp; free(_hp); }
    if (_t834) {
        I64 _t818 = 0;
        I64 _t819 = 1;
        I64 _t820 = I64_sub(_t818, _t819);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t820; return _r; }
    }
    ;
    I64 _t835 = 0;
    I64 _t836 = 1;
    I64 last = I64_sub(_t835, _t836);
    ;
    ;
    U64 i = 0;
    while (1) {
        U64 _t829 = U64_sub(self->count, needle->count);
        Bool _wcond821; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t829}); _wcond821 = *_hp; free(_hp); }
        ;
        if (_wcond821) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond822; { Bool *_hp = U64_lt(j, &needle->count); _wcond822 = *_hp; free(_hp); }
            if (_wcond822) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t824 = malloc(sizeof(U64)); *_t824 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t824);
            U8 *bc = Str_get(needle, j);
            Bool _t825; { Bool *_hp = U8_neq(ac, bc); _t825 = *_hp; free(_hp); }
            U64_delete(_t824, &(Bool){1});
            if (_t825) {
                Bool _t823 = 0;
                found = _t823;
                ;
            }
            ;
            U64 _t826 = 1;
            U64 _t827 = U64_add(DEREF(j), _t826);
            ;
            *j = _t827;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t828 = U64_to_i64(i);
            last = _t828;
            ;
        }
        ;
        U64 _t830 = 1;
        U64 _t831 = U64_add(i, _t830);
        ;
        i = _t831;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    U64 _t852 = 0;
    Bool _t853 = U64_eq(from->count, _t852);
    ;
    if (_t853) {
        Str *_t837 = Str_clone(self);
        ;
        return _t837;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 start = 0;
    while (1) {
        U64 _t839 = U64_sub(self->count, from->count);
        Bool _wcond838; { Bool *_hp = U64_lte(&(U64){start}, &(U64){_t839}); _wcond838 = *_hp; free(_hp); }
        ;
        if (_wcond838) {
        } else {
            ;
            break;
        }
        ;
        U64 _t840 = U64_sub(self->count, start);
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t840});
        ;
        I64 pos; { I64 *_hp = Str_find(rest, from); pos = *_hp; free(_hp); }
        I64 _t841 = 0;
        I64 _t842 = 1;
        I64 _t843 = I64_sub(_t841, _t842);
        ;
        ;
        Bool _t844 = I64_eq(pos, _t843);
        ;
        if (_t844) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t845 = I64_to_u64(pos);
        Str *_t846 = Str_substr(self, &(U64){start}, &(U64){_t845});
        ;
        result = Str_concat(result, _t846);
        Str_delete(_t846, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t847 = I64_to_u64(pos);
        ;
        U64 _t848 = U64_add(start, _t847);
        ;
        U64 _t849 = U64_add(_t848, from->count);
        ;
        start = _t849;
        ;
    }
    Bool _t854; { Bool *_hp = U64_lt(&(U64){start}, &self->count); _t854 = *_hp; free(_hp); }
    if (_t854) {
        U64 _t850 = U64_sub(self->count, start);
        Str *_t851 = Str_substr(self, &(U64){start}, &(U64){_t850});
        ;
        result = Str_concat(result, _t851);
        Str_delete(_t851, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    U64 _t855 = 1;
    Str *_t856 = Str_substr(self, i, &(U64){_t855});
    ;
    return _t856;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    Bool _t859; { Bool *_hp = Str_starts_with(self, prefix); _t859 = *_hp; free(_hp); }
    if (_t859) {
        U64 _t857 = U64_sub(self->count, prefix->count);
        Str *_t858 = Str_substr(self, &prefix->count, &(U64){_t857});
        ;
        ;
        return _t858;
    }
    ;
    Str *_t860 = Str_clone(self);
    return _t860;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    Bool _t864; { Bool *_hp = Str_ends_with(self, suffix); _t864 = *_hp; free(_hp); }
    if (_t864) {
        U64 _t861 = 0;
        U64 _t862 = U64_sub(self->count, suffix->count);
        Str *_t863 = Str_substr(self, &(U64){_t861}, &(U64){_t862});
        ;
        ;
        ;
        return _t863;
    }
    ;
    Str *_t865 = Str_clone(self);
    return _t865;
}

Str * Str_from_byte(U8 * byte) {
    U64 _t866 = 2;
    U8 *buf = malloc(_t866);
    ;
    U64 _t867 = 1;
    memcpy(buf, byte, _t867);
    ;
    U64 *_t868 = malloc(sizeof(U64));
    *_t868 = 1;
    void *_t869 = ptr_add(buf, DEREF(_t868));
    I64 _t870 = 0;
    U64 _t871 = 1;
    memcpy(_t869, &(I64){_t870}, _t871);
    U64_delete(_t868, &(Bool){1});
    ;
    ;
    I64 _t872 = 1;
    I64 _t873 = 1;
    Str *_t874 = malloc(sizeof(Str));
    _t874->c_str = buf;
    _t874->count = _t872;
    _t874->cap = _t873;
    ;
    ;
    return _t874;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t914 = 0;
    Bool _t915 = U64_eq(self->count, _t914);
    ;
    if (_t915) {
        Str *_t875 = Str_lit("Str", 3ULL);
        U64 _t876; { U64 *_hp = Str_size(); _t876 = *_hp; free(_hp); }
        U64 _t877 = 1;
        Array *_va15 = Array_new(_t875, &(U64){_t876}, &(U64){_t877});
        Str_delete(_t875, &(Bool){1});
        ;
        ;
        U64 _t878 = 0;
        Str *_t879 = Str_lit("Str.to_i64: empty string", 24ULL);
        Array_set(_va15, &(U64){_t878}, _t879);
        ;
        Str *_t880 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:219:37", 61ULL);
        panic(_t880, _va15);
        Str_delete(_t880, &(Bool){1});
    }
    ;
    I64 result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool neg = 0;
    U64 *_t916 = malloc(sizeof(U64));
    *_t916 = 0;
    U8 *first = Str_get(self, _t916);
    U8 _t917 = 45;
    Bool _t918 = U8_eq(DEREF(first), _t917);
    U64_delete(_t916, &(Bool){1});
    ;
    if (_t918) {
        Bool _t881 = 1;
        neg = _t881;
        ;
        U64 _t882 = 1;
        *i = _t882;
        ;
    }
    ;
    Bool _t919 = U64_eq(DEREF(i), self->count);
    if (_t919) {
        Str *_t883 = Str_lit("Str", 3ULL);
        U64 _t884; { U64 *_hp = Str_size(); _t884 = *_hp; free(_hp); }
        U64 _t885 = 1;
        Array *_va16 = Array_new(_t883, &(U64){_t884}, &(U64){_t885});
        Str_delete(_t883, &(Bool){1});
        ;
        ;
        U64 _t886 = 0;
        Str *_t887 = Str_lit("Str.to_i64: no digits", 21ULL);
        Array_set(_va16, &(U64){_t886}, _t887);
        ;
        Str *_t888 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:228:37", 61ULL);
        panic(_t888, _va16);
        Str_delete(_t888, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond889; { Bool *_hp = U64_lt(i, &self->count); _wcond889 = *_hp; free(_hp); }
        if (_wcond889) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        I64 _t900 = U8_to_i64(DEREF(ch));
        I64 _t901 = 48;
        I64 d = I64_sub(_t900, _t901);
        ;
        ;
        I64 _t902 = 0;
        I64 _t903 = 9;
        Bool _t904; { Bool *_hp = I64_lt(&(I64){d}, &(I64){_t902}); _t904 = *_hp; free(_hp); }
        ;
        Bool _t905; { Bool *_hp = I64_gt(&(I64){d}, &(I64){_t903}); _t905 = *_hp; free(_hp); }
        ;
        Bool _t906 = Bool_or(_t904, _t905);
        ;
        ;
        if (_t906) {
            Str *_t890 = Str_lit("Str", 3ULL);
            U64 _t891; { U64 *_hp = Str_size(); _t891 = *_hp; free(_hp); }
            U64 _t892 = 3;
            Array *_va17 = Array_new(_t890, &(U64){_t891}, &(U64){_t892});
            Str_delete(_t890, &(Bool){1});
            ;
            ;
            U64 _t893 = 0;
            Str *_t894 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
            Array_set(_va17, &(U64){_t893}, _t894);
            ;
            U64 _t895 = 1;
            Str *_t896 = Str_clone(self);
            Array_set(_va17, &(U64){_t895}, _t896);
            ;
            U64 _t897 = 2;
            Str *_t898 = Str_lit("'", 1ULL);
            Array_set(_va17, &(U64){_t897}, _t898);
            ;
            Str *_t899 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:233:23", 61ULL);
            panic(_t899, _va17);
            Str_delete(_t899, &(Bool){1});
        }
        ;
        I64 _t907 = 10;
        I64 _t908 = I64_mul(result, _t907);
        ;
        I64 _t909 = I64_add(_t908, d);
        ;
        ;
        result = _t909;
        ;
        U64 _t910 = 1;
        U64 _t911 = U64_add(DEREF(i), _t910);
        ;
        *i = _t911;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t912 = 0;
        I64 _t913 = I64_sub(_t912, result);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t913; return _r; }
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
    I64 _t921; { I64 *_hp = Str_cmp(a, b); _t921 = *_hp; free(_hp); }
    I64 _t922 = 0;
    Bool _t923 = I64_eq(_t921, _t922);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t923; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    I64 _t924 = 0;
    I64 _t925 = 1;
    I64 _t926; { I64 *_hp = Str_cmp(a, b); _t926 = *_hp; free(_hp); }
    I64 _t927 = I64_sub(_t924, _t925);
    ;
    ;
    Bool _t928 = I64_eq(_t926, _t927);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t928; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    I64 _t929; { I64 *_hp = Str_cmp(a, b); _t929 = *_hp; free(_hp); }
    I64 _t930 = 1;
    Bool _t931 = I64_eq(_t929, _t930);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t931; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    Bool _t932; { Bool *_hp = Str_eq(a, b); _t932 = *_hp; free(_hp); }
    Bool _t933 = Bool_not(_t932);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t933; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    Bool _t934; { Bool *_hp = Str_gt(a, b); _t934 = *_hp; free(_hp); }
    Bool _t935 = Bool_not(_t934);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t935; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    Bool _t936; { Bool *_hp = Str_lt(a, b); _t936 = *_hp; free(_hp); }
    Bool _t937 = Bool_not(_t936);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t937; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t938 = malloc(DEREF(elem_size));
    U64 _t939 = 0;
    I64 _t940 = 1;
    U64 _t941 = U64_clone(elem_size);
    Vec *_t942 = malloc(sizeof(Vec));
    _t942->data = _t938;
    _t942->count = _t939;
    _t942->cap = _t940;
    _t942->elem_size = _t941;
    { Str *_ca = Str_clone(elem_type); _t942->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t942;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    Bool _t947 = U64_eq(self->count, self->cap);
    if (_t947) {
        U64 _t943 = 2;
        U64 new_cap = U64_mul(self->cap, _t943);
        ;
        U64 _t944 = U64_mul(new_cap, self->elem_size);
        void *_t945 = realloc(self->data, _t944);
        ;
        self->data = _t945;
        U64 _t946 = U64_clone(&(U64){new_cap});
        ;
        self->cap = _t946;
        ;
    }
    ;
    U64 *_t948 = malloc(sizeof(U64)); *_t948 = U64_mul(self->count, self->elem_size);
    void *_t949 = ptr_add(self->data, DEREF(_t948));
    memcpy(_t949, val, self->elem_size);
    U64_delete(_t948, &(Bool){1});
    free(val);
    U64 _t950 = 1;
    U64 _t951 = U64_add(self->count, _t950);
    ;
    self->count = _t951;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    Bool _t966; { Bool *_hp = U64_gte(i, &self->count); _t966 = *_hp; free(_hp); }
    if (_t966) {
        Str *_t952 = Str_lit("Str", 3ULL);
        U64 _t953; { U64 *_hp = Str_size(); _t953 = *_hp; free(_hp); }
        U64 _t954 = 5;
        Array *_va18 = Array_new(_t952, &(U64){_t953}, &(U64){_t954});
        Str_delete(_t952, &(Bool){1});
        ;
        ;
        U64 _t955 = 0;
        Str *_t956 = Str_lit("Vec.get: index ", 15ULL);
        Array_set(_va18, &(U64){_t955}, _t956);
        ;
        U64 _t957 = 1;
        Str *_t958 = U64_to_str(DEREF(i));
        Array_set(_va18, &(U64){_t957}, _t958);
        ;
        U64 _t959 = 2;
        Str *_t960 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va18, &(U64){_t959}, _t960);
        ;
        U64 _t961 = 3;
        Str *_t962 = U64_to_str(self->count);
        Array_set(_va18, &(U64){_t961}, _t962);
        ;
        U64 _t963 = 4;
        Str *_t964 = Str_lit(")", 1ULL);
        Array_set(_va18, &(U64){_t963}, _t964);
        ;
        Str *_t965 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        panic(_t965, _va18);
        Str_delete(_t965, &(Bool){1});
    }
    ;
    U64 *_t967 = malloc(sizeof(U64)); *_t967 = U64_mul(DEREF(i), self->elem_size);
    void *_t968 = ptr_add(self->data, DEREF(_t967));
    U64_delete(_t967, &(Bool){1});
    return _t968;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    Bool _t982; { Bool *_hp = Str_is_empty(&self->elem_type); _t982 = *_hp; free(_hp); }
    Bool _t983 = Bool_not(_t982);
    ;
    if (_t983) {
        {
            U64 _fi969 = 0;
            while (1) {
                U64 _t971 = 0;
                Range *_t972 = Range_new(_t971, self->count);
                ;
                U64 _t973; { U64 *_hp = Range_len(_t972); _t973 = *_hp; free(_hp); }
                Range_delete(_t972, &(Bool){1});
                Bool _wcond970; { Bool *_hp = U64_lt(&(U64){_fi969}, &(U64){_t973}); _wcond970 = *_hp; free(_hp); }
                ;
                if (_wcond970) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t974 = 0;
                Range *_t975 = Range_new(_t974, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t975, _fi969); i = *_hp; free(_hp); }
                Range_delete(_t975, &(Bool){1});
                U64 _t976 = 1;
                U64 _t977 = U64_add(_fi969, _t976);
                ;
                _fi969 = _t977;
                ;
                U64 *_t978 = malloc(sizeof(U64)); *_t978 = U64_mul(i, self->elem_size);
                ;
                void *_t979 = ptr_add(self->data, DEREF(_t978));
                Bool _t980 = 0;
                dyn_call_delete(&self->elem_type, _t979, &(Bool){_t980});
                U64_delete(_t978, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t984; { Bool *_hp = Str_is_empty(&self->elem_type); _t984 = *_hp; free(_hp); }
    Bool _t985 = Bool_not(_t984);
    ;
    if (_t985) {
        Bool _t981 = 0;
        Str_delete(&self->elem_type, &(Bool){_t981});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t999 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t999);
    ;
    {
        U64 _fi986 = 0;
        while (1) {
            U64 _t988 = 0;
            Range *_t989 = Range_new(_t988, self->count);
            ;
            U64 _t990; { U64 *_hp = Range_len(_t989); _t990 = *_hp; free(_hp); }
            Range_delete(_t989, &(Bool){1});
            Bool _wcond987; { Bool *_hp = U64_lt(&(U64){_fi986}, &(U64){_t990}); _wcond987 = *_hp; free(_hp); }
            ;
            if (_wcond987) {
            } else {
                ;
                break;
            }
            ;
            U64 _t991 = 0;
            Range *_t992 = Range_new(_t991, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t992, _fi986); i = *_hp; free(_hp); }
            Range_delete(_t992, &(Bool){1});
            U64 _t993 = 1;
            U64 _t994 = U64_add(_fi986, _t993);
            ;
            _fi986 = _t994;
            ;
            U64 *_t995 = malloc(sizeof(U64)); *_t995 = U64_mul(i, self->elem_size);
            void *_t996 = ptr_add(self->data, DEREF(_t995));
            void *cloned = dyn_call_clone(&self->elem_type, _t996);
            U64_delete(_t995, &(Bool){1});
            U64 *_t997 = malloc(sizeof(U64)); *_t997 = U64_mul(i, self->elem_size);
            ;
            void *_t998 = ptr_add(new_data, DEREF(_t997));
            memcpy(_t998, cloned, self->elem_size);
            U64_delete(_t997, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1000 = malloc(sizeof(Vec));
    _t1000->data = new_data;
    _t1000->count = self->count;
    _t1000->cap = self->cap;
    _t1000->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1000->elem_type = *_ca; free(_ca); }
    return _t1000;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t1018 = Str_lit("Str", 3ULL);
    U64 _t1019; { U64 *_hp = Str_size(); _t1019 = *_hp; free(_hp); }
    Vec *parts = Vec_new(_t1018, &(U64){_t1019});
    Str_delete(_t1018, &(Bool){1});
    ;
    U64 _t1020; { U64 *_hp = Str_len(delim); _t1020 = *_hp; free(_hp); }
    U64 _t1021 = 0;
    Bool _t1022 = U64_eq(_t1020, _t1021);
    ;
    ;
    if (_t1022) {
        Str *_t1002 = Str_clone(s);
        Vec_push(parts, _t1002);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    U64 pos = 0;
    while (1) {
        U64 _t1012; { U64 *_hp = Str_len(s); _t1012 = *_hp; free(_hp); }
        U64 _t1013; { U64 *_hp = Str_len(delim); _t1013 = *_hp; free(_hp); }
        U64 _t1014 = U64_sub(_t1012, _t1013);
        ;
        ;
        Bool _wcond1003; { Bool *_hp = U64_lte(&(U64){pos}, &(U64){_t1014}); _wcond1003 = *_hp; free(_hp); }
        ;
        if (_wcond1003) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1015; { U64 *_hp = Str_len(delim); _t1015 = *_hp; free(_hp); }
        Str *_t1016 = Str_substr(s, &(U64){pos}, &(U64){_t1015});
        ;
        Bool _t1017; { Bool *_hp = Str_eq(_t1016, delim); _t1017 = *_hp; free(_hp); }
        Str_delete(_t1016, &(Bool){1});
        if (_t1017) {
            U64 _t1004 = U64_sub(pos, start);
            Str *_t1005 = Str_substr(s, &(U64){start}, &(U64){_t1004});
            ;
            Str *_t1006 = Str_clone(_t1005);
            Str_delete(_t1005, &(Bool){1});
            Vec_push(parts, _t1006);
            U64 _t1007; { U64 *_hp = Str_len(delim); _t1007 = *_hp; free(_hp); }
            U64 _t1008 = U64_add(pos, _t1007);
            ;
            start = _t1008;
            ;
            U64 _t1009 = U64_clone(&(U64){start});
            pos = _t1009;
            ;
        } else {
            U64 _t1010 = 1;
            U64 _t1011 = U64_add(pos, _t1010);
            ;
            pos = _t1011;
            ;
        }
        ;
    }
    ;
    U64 _t1023; { U64 *_hp = Str_len(s); _t1023 = *_hp; free(_hp); }
    U64 _t1024 = U64_sub(_t1023, start);
    ;
    Str *_t1025 = Str_substr(s, &(U64){start}, &(U64){_t1024});
    ;
    ;
    Str *_t1026 = Str_clone(_t1025);
    Str_delete(_t1025, &(Bool){1});
    Vec_push(parts, _t1026);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 _t1034; { U64 *_hp = Vec_len(parts); _t1034 = *_hp; free(_hp); }
    U64 _t1035 = 0;
    Bool _t1036 = U64_eq(_t1034, _t1035);
    ;
    ;
    if (_t1036) {
        Str *_t1027 = Str_lit("", 0ULL);
        ;
        return _t1027;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t1029; { U64 *_hp = Vec_len(parts); _t1029 = *_hp; free(_hp); }
        Bool _wcond1028; { Bool *_hp = U64_lt(i, &(U64){_t1029}); _wcond1028 = *_hp; free(_hp); }
        ;
        if (_wcond1028) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1030 = 0;
        Bool _t1031; { Bool *_hp = U64_gt(i, &(U64){_t1030}); _t1031 = *_hp; free(_hp); }
        ;
        if (_t1031) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        U64 _t1032 = 1;
        U64 _t1033 = U64_add(DEREF(i), _t1032);
        ;
        *i = _t1033;
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
TokenType *TokenType_KwShallow() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwShallow };
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
TokenType *TokenType_KwNull() {
    TokenType *r = malloc(sizeof(TokenType));
    *r = (TokenType){ .tag = TokenType_TAG_KwNull };
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
Bool *TokenType_is_KwShallow(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwShallow);
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
Bool *TokenType_is_KwNull(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_KwNull);
    return r;
}
Bool *TokenType_is_Error(TokenType *self) {
    Bool *r = malloc(sizeof(Bool));
    *r = (self->tag == TokenType_TAG_Error);
    return r;
}
Bool * TokenType_eq(TokenType * self, TokenType * other) {
    (void)self;
    Bool _t1102; { Bool *_hp = TokenType_is_Eof(self); _t1102 = *_hp; free(_hp); }
    if (_t1102) {
        Bool _t1037; { Bool *_hp = TokenType_is_Eof(other); _t1037 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1037; return _r; }
    }
    ;
    Bool _t1103; { Bool *_hp = TokenType_is_LParen(self); _t1103 = *_hp; free(_hp); }
    if (_t1103) {
        Bool _t1038; { Bool *_hp = TokenType_is_LParen(other); _t1038 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1038; return _r; }
    }
    ;
    Bool _t1104; { Bool *_hp = TokenType_is_RParen(self); _t1104 = *_hp; free(_hp); }
    if (_t1104) {
        Bool _t1039; { Bool *_hp = TokenType_is_RParen(other); _t1039 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1039; return _r; }
    }
    ;
    Bool _t1105; { Bool *_hp = TokenType_is_LBrace(self); _t1105 = *_hp; free(_hp); }
    if (_t1105) {
        Bool _t1040; { Bool *_hp = TokenType_is_LBrace(other); _t1040 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1040; return _r; }
    }
    ;
    Bool _t1106; { Bool *_hp = TokenType_is_RBrace(self); _t1106 = *_hp; free(_hp); }
    if (_t1106) {
        Bool _t1041; { Bool *_hp = TokenType_is_RBrace(other); _t1041 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1041; return _r; }
    }
    ;
    Bool _t1107; { Bool *_hp = TokenType_is_LBracket(self); _t1107 = *_hp; free(_hp); }
    if (_t1107) {
        Bool _t1042; { Bool *_hp = TokenType_is_LBracket(other); _t1042 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1042; return _r; }
    }
    ;
    Bool _t1108; { Bool *_hp = TokenType_is_RBracket(self); _t1108 = *_hp; free(_hp); }
    if (_t1108) {
        Bool _t1043; { Bool *_hp = TokenType_is_RBracket(other); _t1043 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1043; return _r; }
    }
    ;
    Bool _t1109; { Bool *_hp = TokenType_is_Comma(self); _t1109 = *_hp; free(_hp); }
    if (_t1109) {
        Bool _t1044; { Bool *_hp = TokenType_is_Comma(other); _t1044 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1044; return _r; }
    }
    ;
    Bool _t1110; { Bool *_hp = TokenType_is_Colon(self); _t1110 = *_hp; free(_hp); }
    if (_t1110) {
        Bool _t1045; { Bool *_hp = TokenType_is_Colon(other); _t1045 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1045; return _r; }
    }
    ;
    Bool _t1111; { Bool *_hp = TokenType_is_Question(self); _t1111 = *_hp; free(_hp); }
    if (_t1111) {
        Bool _t1046; { Bool *_hp = TokenType_is_Question(other); _t1046 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1046; return _r; }
    }
    ;
    Bool _t1112; { Bool *_hp = TokenType_is_Bang(self); _t1112 = *_hp; free(_hp); }
    if (_t1112) {
        Bool _t1047; { Bool *_hp = TokenType_is_Bang(other); _t1047 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1047; return _r; }
    }
    ;
    Bool _t1113; { Bool *_hp = TokenType_is_Minus(self); _t1113 = *_hp; free(_hp); }
    if (_t1113) {
        Bool _t1048; { Bool *_hp = TokenType_is_Minus(other); _t1048 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1048; return _r; }
    }
    ;
    Bool _t1114; { Bool *_hp = TokenType_is_Plus(self); _t1114 = *_hp; free(_hp); }
    if (_t1114) {
        Bool _t1049; { Bool *_hp = TokenType_is_Plus(other); _t1049 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1049; return _r; }
    }
    ;
    Bool _t1115; { Bool *_hp = TokenType_is_Star(self); _t1115 = *_hp; free(_hp); }
    if (_t1115) {
        Bool _t1050; { Bool *_hp = TokenType_is_Star(other); _t1050 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1050; return _r; }
    }
    ;
    Bool _t1116; { Bool *_hp = TokenType_is_Slash(self); _t1116 = *_hp; free(_hp); }
    if (_t1116) {
        Bool _t1051; { Bool *_hp = TokenType_is_Slash(other); _t1051 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1051; return _r; }
    }
    ;
    Bool _t1117; { Bool *_hp = TokenType_is_Dot(self); _t1117 = *_hp; free(_hp); }
    if (_t1117) {
        Bool _t1052; { Bool *_hp = TokenType_is_Dot(other); _t1052 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1052; return _r; }
    }
    ;
    Bool _t1118; { Bool *_hp = TokenType_is_DotDot(self); _t1118 = *_hp; free(_hp); }
    if (_t1118) {
        Bool _t1053; { Bool *_hp = TokenType_is_DotDot(other); _t1053 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1053; return _r; }
    }
    ;
    Bool _t1119; { Bool *_hp = TokenType_is_Eq(self); _t1119 = *_hp; free(_hp); }
    if (_t1119) {
        Bool _t1054; { Bool *_hp = TokenType_is_Eq(other); _t1054 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1054; return _r; }
    }
    ;
    Bool _t1120; { Bool *_hp = TokenType_is_EqEq(self); _t1120 = *_hp; free(_hp); }
    if (_t1120) {
        Bool _t1055; { Bool *_hp = TokenType_is_EqEq(other); _t1055 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1055; return _r; }
    }
    ;
    Bool _t1121; { Bool *_hp = TokenType_is_Neq(self); _t1121 = *_hp; free(_hp); }
    if (_t1121) {
        Bool _t1056; { Bool *_hp = TokenType_is_Neq(other); _t1056 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1056; return _r; }
    }
    ;
    Bool _t1122; { Bool *_hp = TokenType_is_Lt(self); _t1122 = *_hp; free(_hp); }
    if (_t1122) {
        Bool _t1057; { Bool *_hp = TokenType_is_Lt(other); _t1057 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1057; return _r; }
    }
    ;
    Bool _t1123; { Bool *_hp = TokenType_is_LtEq(self); _t1123 = *_hp; free(_hp); }
    if (_t1123) {
        Bool _t1058; { Bool *_hp = TokenType_is_LtEq(other); _t1058 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1058; return _r; }
    }
    ;
    Bool _t1124; { Bool *_hp = TokenType_is_Gt(self); _t1124 = *_hp; free(_hp); }
    if (_t1124) {
        Bool _t1059; { Bool *_hp = TokenType_is_Gt(other); _t1059 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1059; return _r; }
    }
    ;
    Bool _t1125; { Bool *_hp = TokenType_is_GtEq(self); _t1125 = *_hp; free(_hp); }
    if (_t1125) {
        Bool _t1060; { Bool *_hp = TokenType_is_GtEq(other); _t1060 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1060; return _r; }
    }
    ;
    Bool _t1126; { Bool *_hp = TokenType_is_ColonEq(self); _t1126 = *_hp; free(_hp); }
    if (_t1126) {
        Bool _t1061; { Bool *_hp = TokenType_is_ColonEq(other); _t1061 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1061; return _r; }
    }
    ;
    Bool _t1127; { Bool *_hp = TokenType_is_Ident(self); _t1127 = *_hp; free(_hp); }
    if (_t1127) {
        Bool _t1062; { Bool *_hp = TokenType_is_Ident(other); _t1062 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1062; return _r; }
    }
    ;
    Bool _t1128; { Bool *_hp = TokenType_is_StringTok(self); _t1128 = *_hp; free(_hp); }
    if (_t1128) {
        Bool _t1063; { Bool *_hp = TokenType_is_StringTok(other); _t1063 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1063; return _r; }
    }
    ;
    Bool _t1129; { Bool *_hp = TokenType_is_Number(self); _t1129 = *_hp; free(_hp); }
    if (_t1129) {
        Bool _t1064; { Bool *_hp = TokenType_is_Number(other); _t1064 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1064; return _r; }
    }
    ;
    Bool _t1130; { Bool *_hp = TokenType_is_Char(self); _t1130 = *_hp; free(_hp); }
    if (_t1130) {
        Bool _t1065; { Bool *_hp = TokenType_is_Char(other); _t1065 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1065; return _r; }
    }
    ;
    Bool _t1131; { Bool *_hp = TokenType_is_KwMode(self); _t1131 = *_hp; free(_hp); }
    if (_t1131) {
        Bool _t1066; { Bool *_hp = TokenType_is_KwMode(other); _t1066 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1066; return _r; }
    }
    ;
    Bool _t1132; { Bool *_hp = TokenType_is_KwMut(self); _t1132 = *_hp; free(_hp); }
    if (_t1132) {
        Bool _t1067; { Bool *_hp = TokenType_is_KwMut(other); _t1067 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1067; return _r; }
    }
    ;
    Bool _t1133; { Bool *_hp = TokenType_is_KwOwn(self); _t1133 = *_hp; free(_hp); }
    if (_t1133) {
        Bool _t1068; { Bool *_hp = TokenType_is_KwOwn(other); _t1068 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1068; return _r; }
    }
    ;
    Bool _t1134; { Bool *_hp = TokenType_is_KwRef(self); _t1134 = *_hp; free(_hp); }
    if (_t1134) {
        Bool _t1069; { Bool *_hp = TokenType_is_KwRef(other); _t1069 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1069; return _r; }
    }
    ;
    Bool _t1135; { Bool *_hp = TokenType_is_KwShallow(self); _t1135 = *_hp; free(_hp); }
    if (_t1135) {
        Bool _t1070; { Bool *_hp = TokenType_is_KwShallow(other); _t1070 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1070; return _r; }
    }
    ;
    Bool _t1136; { Bool *_hp = TokenType_is_KwStruct(self); _t1136 = *_hp; free(_hp); }
    if (_t1136) {
        Bool _t1071; { Bool *_hp = TokenType_is_KwStruct(other); _t1071 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1071; return _r; }
    }
    ;
    Bool _t1137; { Bool *_hp = TokenType_is_KwExtStruct(self); _t1137 = *_hp; free(_hp); }
    if (_t1137) {
        Bool _t1072; { Bool *_hp = TokenType_is_KwExtStruct(other); _t1072 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1072; return _r; }
    }
    ;
    Bool _t1138; { Bool *_hp = TokenType_is_KwEnum(self); _t1138 = *_hp; free(_hp); }
    if (_t1138) {
        Bool _t1073; { Bool *_hp = TokenType_is_KwEnum(other); _t1073 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1073; return _r; }
    }
    ;
    Bool _t1139; { Bool *_hp = TokenType_is_KwNamespace(self); _t1139 = *_hp; free(_hp); }
    if (_t1139) {
        Bool _t1074; { Bool *_hp = TokenType_is_KwNamespace(other); _t1074 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1074; return _r; }
    }
    ;
    Bool _t1140; { Bool *_hp = TokenType_is_KwFunc(self); _t1140 = *_hp; free(_hp); }
    if (_t1140) {
        Bool _t1075; { Bool *_hp = TokenType_is_KwFunc(other); _t1075 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1075; return _r; }
    }
    ;
    Bool _t1141; { Bool *_hp = TokenType_is_KwProc(self); _t1141 = *_hp; free(_hp); }
    if (_t1141) {
        Bool _t1076; { Bool *_hp = TokenType_is_KwProc(other); _t1076 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1076; return _r; }
    }
    ;
    Bool _t1142; { Bool *_hp = TokenType_is_KwTest(self); _t1142 = *_hp; free(_hp); }
    if (_t1142) {
        Bool _t1077; { Bool *_hp = TokenType_is_KwTest(other); _t1077 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1077; return _r; }
    }
    ;
    Bool _t1143; { Bool *_hp = TokenType_is_KwMacro(self); _t1143 = *_hp; free(_hp); }
    if (_t1143) {
        Bool _t1078; { Bool *_hp = TokenType_is_KwMacro(other); _t1078 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1078; return _r; }
    }
    ;
    Bool _t1144; { Bool *_hp = TokenType_is_KwExtFunc(self); _t1144 = *_hp; free(_hp); }
    if (_t1144) {
        Bool _t1079; { Bool *_hp = TokenType_is_KwExtFunc(other); _t1079 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1079; return _r; }
    }
    ;
    Bool _t1145; { Bool *_hp = TokenType_is_KwExtProc(self); _t1145 = *_hp; free(_hp); }
    if (_t1145) {
        Bool _t1080; { Bool *_hp = TokenType_is_KwExtProc(other); _t1080 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1080; return _r; }
    }
    ;
    Bool _t1146; { Bool *_hp = TokenType_is_KwReturns(self); _t1146 = *_hp; free(_hp); }
    if (_t1146) {
        Bool _t1081; { Bool *_hp = TokenType_is_KwReturns(other); _t1081 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1081; return _r; }
    }
    ;
    Bool _t1147; { Bool *_hp = TokenType_is_KwThrows(self); _t1147 = *_hp; free(_hp); }
    if (_t1147) {
        Bool _t1082; { Bool *_hp = TokenType_is_KwThrows(other); _t1082 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1082; return _r; }
    }
    ;
    Bool _t1148; { Bool *_hp = TokenType_is_KwIf(self); _t1148 = *_hp; free(_hp); }
    if (_t1148) {
        Bool _t1083; { Bool *_hp = TokenType_is_KwIf(other); _t1083 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1083; return _r; }
    }
    ;
    Bool _t1149; { Bool *_hp = TokenType_is_KwElse(self); _t1149 = *_hp; free(_hp); }
    if (_t1149) {
        Bool _t1084; { Bool *_hp = TokenType_is_KwElse(other); _t1084 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1084; return _r; }
    }
    ;
    Bool _t1150; { Bool *_hp = TokenType_is_KwWhile(self); _t1150 = *_hp; free(_hp); }
    if (_t1150) {
        Bool _t1085; { Bool *_hp = TokenType_is_KwWhile(other); _t1085 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1085; return _r; }
    }
    ;
    Bool _t1151; { Bool *_hp = TokenType_is_KwFor(self); _t1151 = *_hp; free(_hp); }
    if (_t1151) {
        Bool _t1086; { Bool *_hp = TokenType_is_KwFor(other); _t1086 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1086; return _r; }
    }
    ;
    Bool _t1152; { Bool *_hp = TokenType_is_KwIn(self); _t1152 = *_hp; free(_hp); }
    if (_t1152) {
        Bool _t1087; { Bool *_hp = TokenType_is_KwIn(other); _t1087 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1087; return _r; }
    }
    ;
    Bool _t1153; { Bool *_hp = TokenType_is_KwSwitch(self); _t1153 = *_hp; free(_hp); }
    if (_t1153) {
        Bool _t1088; { Bool *_hp = TokenType_is_KwSwitch(other); _t1088 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1088; return _r; }
    }
    ;
    Bool _t1154; { Bool *_hp = TokenType_is_KwMatch(self); _t1154 = *_hp; free(_hp); }
    if (_t1154) {
        Bool _t1089; { Bool *_hp = TokenType_is_KwMatch(other); _t1089 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1089; return _r; }
    }
    ;
    Bool _t1155; { Bool *_hp = TokenType_is_KwCase(self); _t1155 = *_hp; free(_hp); }
    if (_t1155) {
        Bool _t1090; { Bool *_hp = TokenType_is_KwCase(other); _t1090 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1090; return _r; }
    }
    ;
    Bool _t1156; { Bool *_hp = TokenType_is_KwDefault(self); _t1156 = *_hp; free(_hp); }
    if (_t1156) {
        Bool _t1091; { Bool *_hp = TokenType_is_KwDefault(other); _t1091 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1091; return _r; }
    }
    ;
    Bool _t1157; { Bool *_hp = TokenType_is_KwReturn(self); _t1157 = *_hp; free(_hp); }
    if (_t1157) {
        Bool _t1092; { Bool *_hp = TokenType_is_KwReturn(other); _t1092 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1092; return _r; }
    }
    ;
    Bool _t1158; { Bool *_hp = TokenType_is_KwThrow(self); _t1158 = *_hp; free(_hp); }
    if (_t1158) {
        Bool _t1093; { Bool *_hp = TokenType_is_KwThrow(other); _t1093 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1093; return _r; }
    }
    ;
    Bool _t1159; { Bool *_hp = TokenType_is_KwCatch(self); _t1159 = *_hp; free(_hp); }
    if (_t1159) {
        Bool _t1094; { Bool *_hp = TokenType_is_KwCatch(other); _t1094 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1094; return _r; }
    }
    ;
    Bool _t1160; { Bool *_hp = TokenType_is_KwBreak(self); _t1160 = *_hp; free(_hp); }
    if (_t1160) {
        Bool _t1095; { Bool *_hp = TokenType_is_KwBreak(other); _t1095 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1095; return _r; }
    }
    ;
    Bool _t1161; { Bool *_hp = TokenType_is_KwContinue(self); _t1161 = *_hp; free(_hp); }
    if (_t1161) {
        Bool _t1096; { Bool *_hp = TokenType_is_KwContinue(other); _t1096 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1096; return _r; }
    }
    ;
    Bool _t1162; { Bool *_hp = TokenType_is_KwDefer(self); _t1162 = *_hp; free(_hp); }
    if (_t1162) {
        Bool _t1097; { Bool *_hp = TokenType_is_KwDefer(other); _t1097 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1097; return _r; }
    }
    ;
    Bool _t1163; { Bool *_hp = TokenType_is_KwTrue(self); _t1163 = *_hp; free(_hp); }
    if (_t1163) {
        Bool _t1098; { Bool *_hp = TokenType_is_KwTrue(other); _t1098 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1098; return _r; }
    }
    ;
    Bool _t1164; { Bool *_hp = TokenType_is_KwFalse(self); _t1164 = *_hp; free(_hp); }
    if (_t1164) {
        Bool _t1099; { Bool *_hp = TokenType_is_KwFalse(other); _t1099 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1099; return _r; }
    }
    ;
    Bool _t1165; { Bool *_hp = TokenType_is_KwNull(self); _t1165 = *_hp; free(_hp); }
    if (_t1165) {
        Bool _t1100; { Bool *_hp = TokenType_is_KwNull(other); _t1100 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1100; return _r; }
    }
    ;
    Bool _t1166; { Bool *_hp = TokenType_is_Error(self); _t1166 = *_hp; free(_hp); }
    if (_t1166) {
        Bool _t1101; { Bool *_hp = TokenType_is_Error(other); _t1101 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1101; return _r; }
    }
    ;
    Bool _t1167 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1167; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1168; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1168 = *_hp; free(_hp); }
    if (_t1168) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1169; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1169 = *_hp; free(_hp); }
    if (_t1169) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1170; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1170 = *_hp; free(_hp); }
    if (_t1170) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1171; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1171 = *_hp; free(_hp); }
    if (_t1171) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1172; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1172 = *_hp; free(_hp); }
    if (_t1172) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1173; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1173 = *_hp; free(_hp); }
    if (_t1173) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1174; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1174 = *_hp; free(_hp); }
    if (_t1174) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1175; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1175 = *_hp; free(_hp); }
    if (_t1175) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1176; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1176 = *_hp; free(_hp); }
    if (_t1176) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1177; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1177 = *_hp; free(_hp); }
    if (_t1177) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1178; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1178 = *_hp; free(_hp); }
    if (_t1178) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1179; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1179 = *_hp; free(_hp); }
    if (_t1179) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1180; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1180 = *_hp; free(_hp); }
    if (_t1180) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1181; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1181 = *_hp; free(_hp); }
    if (_t1181) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1182; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1182 = *_hp; free(_hp); }
    if (_t1182) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1183; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1183 = *_hp; free(_hp); }
    if (_t1183) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1184; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1184 = *_hp; free(_hp); }
    if (_t1184) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1185; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1185 = *_hp; free(_hp); }
    if (_t1185) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1186; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1186 = *_hp; free(_hp); }
    if (_t1186) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1187; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1187 = *_hp; free(_hp); }
    if (_t1187) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1188; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1188 = *_hp; free(_hp); }
    if (_t1188) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1189; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1189 = *_hp; free(_hp); }
    if (_t1189) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1190; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1190 = *_hp; free(_hp); }
    if (_t1190) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1191; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1191 = *_hp; free(_hp); }
    if (_t1191) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1192; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1192 = *_hp; free(_hp); }
    if (_t1192) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1193; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1193 = *_hp; free(_hp); }
    if (_t1193) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1194; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1194 = *_hp; free(_hp); }
    if (_t1194) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1195; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1195 = *_hp; free(_hp); }
    if (_t1195) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1196; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1196 = *_hp; free(_hp); }
    if (_t1196) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1197; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1197 = *_hp; free(_hp); }
    if (_t1197) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1198; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1198 = *_hp; free(_hp); }
    if (_t1198) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1199; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1199 = *_hp; free(_hp); }
    if (_t1199) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1200; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1200 = *_hp; free(_hp); }
    if (_t1200) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1201; { Bool *_hp = TokenType_eq(self, TokenType_KwShallow()); _t1201 = *_hp; free(_hp); }
    if (_t1201) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t1202; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1202 = *_hp; free(_hp); }
    if (_t1202) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1203; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1203 = *_hp; free(_hp); }
    if (_t1203) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1204; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1204 = *_hp; free(_hp); }
    if (_t1204) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1205; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1205 = *_hp; free(_hp); }
    if (_t1205) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1206; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1206 = *_hp; free(_hp); }
    if (_t1206) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1207; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1207 = *_hp; free(_hp); }
    if (_t1207) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1208; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1208 = *_hp; free(_hp); }
    if (_t1208) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1209; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1209 = *_hp; free(_hp); }
    if (_t1209) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1210; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1210 = *_hp; free(_hp); }
    if (_t1210) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1211; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1211 = *_hp; free(_hp); }
    if (_t1211) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1212; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1212 = *_hp; free(_hp); }
    if (_t1212) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1213; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1213 = *_hp; free(_hp); }
    if (_t1213) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1214; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1214 = *_hp; free(_hp); }
    if (_t1214) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1215; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1215 = *_hp; free(_hp); }
    if (_t1215) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1216; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1216 = *_hp; free(_hp); }
    if (_t1216) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1217; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1217 = *_hp; free(_hp); }
    if (_t1217) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1218; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1218 = *_hp; free(_hp); }
    if (_t1218) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1219; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1219 = *_hp; free(_hp); }
    if (_t1219) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1220; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1220 = *_hp; free(_hp); }
    if (_t1220) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1221; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1221 = *_hp; free(_hp); }
    if (_t1221) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1222; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1222 = *_hp; free(_hp); }
    if (_t1222) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1223; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1223 = *_hp; free(_hp); }
    if (_t1223) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1224; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1224 = *_hp; free(_hp); }
    if (_t1224) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1225; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1225 = *_hp; free(_hp); }
    if (_t1225) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1226; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1226 = *_hp; free(_hp); }
    if (_t1226) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1227; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1227 = *_hp; free(_hp); }
    if (_t1227) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1228; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1228 = *_hp; free(_hp); }
    if (_t1228) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1229; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1229 = *_hp; free(_hp); }
    if (_t1229) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1230; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1230 = *_hp; free(_hp); }
    if (_t1230) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t1231; { Bool *_hp = TokenType_eq(self, TokenType_KwNull()); _t1231 = *_hp; free(_hp); }
    if (_t1231) {
        ;
        return TokenType_KwNull();
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
    Bool _t1297; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1297 = *_hp; free(_hp); }
    if (_t1297) {
        Str *_t1232 = Str_lit("Eof", 3ULL);
        ;
        return _t1232;
    }
    ;
    Bool _t1298; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1298 = *_hp; free(_hp); }
    if (_t1298) {
        Str *_t1233 = Str_lit("LParen", 6ULL);
        ;
        return _t1233;
    }
    ;
    Bool _t1299; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1299 = *_hp; free(_hp); }
    if (_t1299) {
        Str *_t1234 = Str_lit("RParen", 6ULL);
        ;
        return _t1234;
    }
    ;
    Bool _t1300; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1300 = *_hp; free(_hp); }
    if (_t1300) {
        Str *_t1235 = Str_lit("LBrace", 6ULL);
        ;
        return _t1235;
    }
    ;
    Bool _t1301; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1301 = *_hp; free(_hp); }
    if (_t1301) {
        Str *_t1236 = Str_lit("RBrace", 6ULL);
        ;
        return _t1236;
    }
    ;
    Bool _t1302; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1302 = *_hp; free(_hp); }
    if (_t1302) {
        Str *_t1237 = Str_lit("LBracket", 8ULL);
        ;
        return _t1237;
    }
    ;
    Bool _t1303; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1303 = *_hp; free(_hp); }
    if (_t1303) {
        Str *_t1238 = Str_lit("RBracket", 8ULL);
        ;
        return _t1238;
    }
    ;
    Bool _t1304; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1304 = *_hp; free(_hp); }
    if (_t1304) {
        Str *_t1239 = Str_lit("Comma", 5ULL);
        ;
        return _t1239;
    }
    ;
    Bool _t1305; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1305 = *_hp; free(_hp); }
    if (_t1305) {
        Str *_t1240 = Str_lit("Colon", 5ULL);
        ;
        return _t1240;
    }
    ;
    Bool _t1306; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1306 = *_hp; free(_hp); }
    if (_t1306) {
        Str *_t1241 = Str_lit("Question", 8ULL);
        ;
        return _t1241;
    }
    ;
    Bool _t1307; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1307 = *_hp; free(_hp); }
    if (_t1307) {
        Str *_t1242 = Str_lit("Bang", 4ULL);
        ;
        return _t1242;
    }
    ;
    Bool _t1308; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1308 = *_hp; free(_hp); }
    if (_t1308) {
        Str *_t1243 = Str_lit("Minus", 5ULL);
        ;
        return _t1243;
    }
    ;
    Bool _t1309; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1309 = *_hp; free(_hp); }
    if (_t1309) {
        Str *_t1244 = Str_lit("Plus", 4ULL);
        ;
        return _t1244;
    }
    ;
    Bool _t1310; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1310 = *_hp; free(_hp); }
    if (_t1310) {
        Str *_t1245 = Str_lit("Star", 4ULL);
        ;
        return _t1245;
    }
    ;
    Bool _t1311; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1311 = *_hp; free(_hp); }
    if (_t1311) {
        Str *_t1246 = Str_lit("Slash", 5ULL);
        ;
        return _t1246;
    }
    ;
    Bool _t1312; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1312 = *_hp; free(_hp); }
    if (_t1312) {
        Str *_t1247 = Str_lit("Dot", 3ULL);
        ;
        return _t1247;
    }
    ;
    Bool _t1313; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1313 = *_hp; free(_hp); }
    if (_t1313) {
        Str *_t1248 = Str_lit("DotDot", 6ULL);
        ;
        return _t1248;
    }
    ;
    Bool _t1314; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1314 = *_hp; free(_hp); }
    if (_t1314) {
        Str *_t1249 = Str_lit("Eq", 2ULL);
        ;
        return _t1249;
    }
    ;
    Bool _t1315; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1315 = *_hp; free(_hp); }
    if (_t1315) {
        Str *_t1250 = Str_lit("EqEq", 4ULL);
        ;
        return _t1250;
    }
    ;
    Bool _t1316; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1316 = *_hp; free(_hp); }
    if (_t1316) {
        Str *_t1251 = Str_lit("Neq", 3ULL);
        ;
        return _t1251;
    }
    ;
    Bool _t1317; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1317 = *_hp; free(_hp); }
    if (_t1317) {
        Str *_t1252 = Str_lit("Lt", 2ULL);
        ;
        return _t1252;
    }
    ;
    Bool _t1318; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1318 = *_hp; free(_hp); }
    if (_t1318) {
        Str *_t1253 = Str_lit("LtEq", 4ULL);
        ;
        return _t1253;
    }
    ;
    Bool _t1319; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1319 = *_hp; free(_hp); }
    if (_t1319) {
        Str *_t1254 = Str_lit("Gt", 2ULL);
        ;
        return _t1254;
    }
    ;
    Bool _t1320; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1320 = *_hp; free(_hp); }
    if (_t1320) {
        Str *_t1255 = Str_lit("GtEq", 4ULL);
        ;
        return _t1255;
    }
    ;
    Bool _t1321; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1321 = *_hp; free(_hp); }
    if (_t1321) {
        Str *_t1256 = Str_lit("ColonEq", 7ULL);
        ;
        return _t1256;
    }
    ;
    Bool _t1322; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1322 = *_hp; free(_hp); }
    if (_t1322) {
        Str *_t1257 = Str_lit("Ident", 5ULL);
        ;
        return _t1257;
    }
    ;
    Bool _t1323; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1323 = *_hp; free(_hp); }
    if (_t1323) {
        Str *_t1258 = Str_lit("StringTok", 9ULL);
        ;
        return _t1258;
    }
    ;
    Bool _t1324; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1324 = *_hp; free(_hp); }
    if (_t1324) {
        Str *_t1259 = Str_lit("Number", 6ULL);
        ;
        return _t1259;
    }
    ;
    Bool _t1325; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1325 = *_hp; free(_hp); }
    if (_t1325) {
        Str *_t1260 = Str_lit("Char", 4ULL);
        ;
        return _t1260;
    }
    ;
    Bool _t1326; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1326 = *_hp; free(_hp); }
    if (_t1326) {
        Str *_t1261 = Str_lit("KwMode", 6ULL);
        ;
        return _t1261;
    }
    ;
    Bool _t1327; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1327 = *_hp; free(_hp); }
    if (_t1327) {
        Str *_t1262 = Str_lit("KwMut", 5ULL);
        ;
        return _t1262;
    }
    ;
    Bool _t1328; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1328 = *_hp; free(_hp); }
    if (_t1328) {
        Str *_t1263 = Str_lit("KwOwn", 5ULL);
        ;
        return _t1263;
    }
    ;
    Bool _t1329; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1329 = *_hp; free(_hp); }
    if (_t1329) {
        Str *_t1264 = Str_lit("KwRef", 5ULL);
        ;
        return _t1264;
    }
    ;
    Bool _t1330; { Bool *_hp = TokenType_eq(self, TokenType_KwShallow()); _t1330 = *_hp; free(_hp); }
    if (_t1330) {
        Str *_t1265 = Str_lit("KwShallow", 9ULL);
        ;
        return _t1265;
    }
    ;
    Bool _t1331; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1331 = *_hp; free(_hp); }
    if (_t1331) {
        Str *_t1266 = Str_lit("KwStruct", 8ULL);
        ;
        return _t1266;
    }
    ;
    Bool _t1332; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1332 = *_hp; free(_hp); }
    if (_t1332) {
        Str *_t1267 = Str_lit("KwExtStruct", 11ULL);
        ;
        return _t1267;
    }
    ;
    Bool _t1333; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1333 = *_hp; free(_hp); }
    if (_t1333) {
        Str *_t1268 = Str_lit("KwEnum", 6ULL);
        ;
        return _t1268;
    }
    ;
    Bool _t1334; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1334 = *_hp; free(_hp); }
    if (_t1334) {
        Str *_t1269 = Str_lit("KwNamespace", 11ULL);
        ;
        return _t1269;
    }
    ;
    Bool _t1335; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1335 = *_hp; free(_hp); }
    if (_t1335) {
        Str *_t1270 = Str_lit("KwFunc", 6ULL);
        ;
        return _t1270;
    }
    ;
    Bool _t1336; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1336 = *_hp; free(_hp); }
    if (_t1336) {
        Str *_t1271 = Str_lit("KwProc", 6ULL);
        ;
        return _t1271;
    }
    ;
    Bool _t1337; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1337 = *_hp; free(_hp); }
    if (_t1337) {
        Str *_t1272 = Str_lit("KwTest", 6ULL);
        ;
        return _t1272;
    }
    ;
    Bool _t1338; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1338 = *_hp; free(_hp); }
    if (_t1338) {
        Str *_t1273 = Str_lit("KwMacro", 7ULL);
        ;
        return _t1273;
    }
    ;
    Bool _t1339; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1339 = *_hp; free(_hp); }
    if (_t1339) {
        Str *_t1274 = Str_lit("KwExtFunc", 9ULL);
        ;
        return _t1274;
    }
    ;
    Bool _t1340; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1340 = *_hp; free(_hp); }
    if (_t1340) {
        Str *_t1275 = Str_lit("KwExtProc", 9ULL);
        ;
        return _t1275;
    }
    ;
    Bool _t1341; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1341 = *_hp; free(_hp); }
    if (_t1341) {
        Str *_t1276 = Str_lit("KwReturns", 9ULL);
        ;
        return _t1276;
    }
    ;
    Bool _t1342; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1342 = *_hp; free(_hp); }
    if (_t1342) {
        Str *_t1277 = Str_lit("KwThrows", 8ULL);
        ;
        return _t1277;
    }
    ;
    Bool _t1343; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1343 = *_hp; free(_hp); }
    if (_t1343) {
        Str *_t1278 = Str_lit("KwIf", 4ULL);
        ;
        return _t1278;
    }
    ;
    Bool _t1344; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1344 = *_hp; free(_hp); }
    if (_t1344) {
        Str *_t1279 = Str_lit("KwElse", 6ULL);
        ;
        return _t1279;
    }
    ;
    Bool _t1345; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1345 = *_hp; free(_hp); }
    if (_t1345) {
        Str *_t1280 = Str_lit("KwWhile", 7ULL);
        ;
        return _t1280;
    }
    ;
    Bool _t1346; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1346 = *_hp; free(_hp); }
    if (_t1346) {
        Str *_t1281 = Str_lit("KwFor", 5ULL);
        ;
        return _t1281;
    }
    ;
    Bool _t1347; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1347 = *_hp; free(_hp); }
    if (_t1347) {
        Str *_t1282 = Str_lit("KwIn", 4ULL);
        ;
        return _t1282;
    }
    ;
    Bool _t1348; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1348 = *_hp; free(_hp); }
    if (_t1348) {
        Str *_t1283 = Str_lit("KwSwitch", 8ULL);
        ;
        return _t1283;
    }
    ;
    Bool _t1349; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1349 = *_hp; free(_hp); }
    if (_t1349) {
        Str *_t1284 = Str_lit("KwMatch", 7ULL);
        ;
        return _t1284;
    }
    ;
    Bool _t1350; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1350 = *_hp; free(_hp); }
    if (_t1350) {
        Str *_t1285 = Str_lit("KwCase", 6ULL);
        ;
        return _t1285;
    }
    ;
    Bool _t1351; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1351 = *_hp; free(_hp); }
    if (_t1351) {
        Str *_t1286 = Str_lit("KwDefault", 9ULL);
        ;
        return _t1286;
    }
    ;
    Bool _t1352; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1352 = *_hp; free(_hp); }
    if (_t1352) {
        Str *_t1287 = Str_lit("KwReturn", 8ULL);
        ;
        return _t1287;
    }
    ;
    Bool _t1353; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1353 = *_hp; free(_hp); }
    if (_t1353) {
        Str *_t1288 = Str_lit("KwThrow", 7ULL);
        ;
        return _t1288;
    }
    ;
    Bool _t1354; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1354 = *_hp; free(_hp); }
    if (_t1354) {
        Str *_t1289 = Str_lit("KwCatch", 7ULL);
        ;
        return _t1289;
    }
    ;
    Bool _t1355; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1355 = *_hp; free(_hp); }
    if (_t1355) {
        Str *_t1290 = Str_lit("KwBreak", 7ULL);
        ;
        return _t1290;
    }
    ;
    Bool _t1356; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1356 = *_hp; free(_hp); }
    if (_t1356) {
        Str *_t1291 = Str_lit("KwContinue", 10ULL);
        ;
        return _t1291;
    }
    ;
    Bool _t1357; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1357 = *_hp; free(_hp); }
    if (_t1357) {
        Str *_t1292 = Str_lit("KwDefer", 7ULL);
        ;
        return _t1292;
    }
    ;
    Bool _t1358; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1358 = *_hp; free(_hp); }
    if (_t1358) {
        Str *_t1293 = Str_lit("KwTrue", 6ULL);
        ;
        return _t1293;
    }
    ;
    Bool _t1359; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1359 = *_hp; free(_hp); }
    if (_t1359) {
        Str *_t1294 = Str_lit("KwFalse", 7ULL);
        ;
        return _t1294;
    }
    ;
    Bool _t1360; { Bool *_hp = TokenType_eq(self, TokenType_KwNull()); _t1360 = *_hp; free(_hp); }
    if (_t1360) {
        Str *_t1295 = Str_lit("KwNull", 6ULL);
        ;
        return _t1295;
    }
    ;
    Bool _t1361; { Bool *_hp = TokenType_eq(self, TokenType_Error()); _t1361 = *_hp; free(_hp); }
    if (_t1361) {
        Str *_t1296 = Str_lit("Error", 5ULL);
        ;
        return _t1296;
    }
    ;
    Str *_t1362 = Str_lit("unknown", 7ULL);
    return _t1362;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1364 = I64_clone(&self->line);
    I64 _t1365 = I64_clone(&self->col);
    Token *_t1366 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1366->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1366->text = *_ca; free(_ca); }
    _t1366->line = _t1364;
    _t1366->col = _t1365;
    ;
    ;
    return _t1366;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    Bool _t1367 = 0;
    TokenType_delete(&self->type, &(Bool){_t1367});
    ;
    Bool _t1368 = 0;
    Str_delete(&self->text, &(Bool){_t1368});
    ;
    Bool _t1369 = 0;
    I64_delete(&self->line, &(Bool){_t1369});
    ;
    Bool _t1370 = 0;
    I64_delete(&self->col, &(Bool){_t1370});
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
    U8 _t1372 = 48;
    U8 _t1373 = 57;
    Bool _t1374; { Bool *_hp = U8_gte(c, &(U8){_t1372}); _t1374 = *_hp; free(_hp); }
    ;
    Bool _t1375; { Bool *_hp = U8_lte(c, &(U8){_t1373}); _t1375 = *_hp; free(_hp); }
    ;
    Bool _t1376 = Bool_and(_t1374, _t1375);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1376; return _r; }
}

Bool * is_alpha(U8 * c) {
    U8 _t1377 = 97;
    U8 _t1378 = 122;
    Bool _t1379; { Bool *_hp = U8_gte(c, &(U8){_t1377}); _t1379 = *_hp; free(_hp); }
    ;
    Bool _t1380; { Bool *_hp = U8_lte(c, &(U8){_t1378}); _t1380 = *_hp; free(_hp); }
    ;
    U8 _t1381 = 65;
    U8 _t1382 = 90;
    Bool _t1383; { Bool *_hp = U8_gte(c, &(U8){_t1381}); _t1383 = *_hp; free(_hp); }
    ;
    Bool _t1384; { Bool *_hp = U8_lte(c, &(U8){_t1382}); _t1384 = *_hp; free(_hp); }
    ;
    Bool _t1385 = Bool_and(_t1379, _t1380);
    ;
    ;
    Bool _t1386 = Bool_and(_t1383, _t1384);
    ;
    ;
    U8 _t1387 = 95;
    Bool _t1388 = Bool_or(_t1385, _t1386);
    ;
    ;
    Bool _t1389 = U8_eq(DEREF(c), _t1387);
    ;
    Bool _t1390 = Bool_or(_t1388, _t1389);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1390; return _r; }
}

Bool * is_alnum(U8 * c) {
    Bool _t1391; { Bool *_hp = is_alpha(c); _t1391 = *_hp; free(_hp); }
    Bool _t1392; { Bool *_hp = is_digit(c); _t1392 = *_hp; free(_hp); }
    Bool _t1393 = Bool_or(_t1391, _t1392);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1393; return _r; }
}

Str * tok_name(TokenType * type) {
    {
        TokenType *_sw1394 = TokenType_clone(type);
        Bool _t1525; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Eof()); _t1525 = *_hp; free(_hp); }
        if (_t1525) {
            Str *_t1395 = Str_lit("eof", 3ULL);
            TokenType_delete(_sw1394, &(Bool){1});
            ;
            return _t1395;
        } else {
            Bool _t1524; { Bool *_hp = TokenType_eq(_sw1394, TokenType_LParen()); _t1524 = *_hp; free(_hp); }
            if (_t1524) {
                Str *_t1396 = Str_lit("(", 1ULL);
                ;
                TokenType_delete(_sw1394, &(Bool){1});
                ;
                return _t1396;
            } else {
                Bool _t1523; { Bool *_hp = TokenType_eq(_sw1394, TokenType_RParen()); _t1523 = *_hp; free(_hp); }
                if (_t1523) {
                    Str *_t1397 = Str_lit(")", 1ULL);
                    ;
                    ;
                    TokenType_delete(_sw1394, &(Bool){1});
                    ;
                    return _t1397;
                } else {
                    Bool _t1522; { Bool *_hp = TokenType_eq(_sw1394, TokenType_LBrace()); _t1522 = *_hp; free(_hp); }
                    if (_t1522) {
                        Str *_t1398 = Str_lit("{", 1ULL);
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1394, &(Bool){1});
                        ;
                        return _t1398;
                    } else {
                        Bool _t1521; { Bool *_hp = TokenType_eq(_sw1394, TokenType_RBrace()); _t1521 = *_hp; free(_hp); }
                        if (_t1521) {
                            Str *_t1399 = Str_lit("}", 1ULL);
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1394, &(Bool){1});
                            ;
                            return _t1399;
                        } else {
                            Bool _t1520; { Bool *_hp = TokenType_eq(_sw1394, TokenType_LBracket()); _t1520 = *_hp; free(_hp); }
                            if (_t1520) {
                                Str *_t1400 = Str_lit("[", 1ULL);
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1394, &(Bool){1});
                                ;
                                return _t1400;
                            } else {
                                Bool _t1519; { Bool *_hp = TokenType_eq(_sw1394, TokenType_RBracket()); _t1519 = *_hp; free(_hp); }
                                if (_t1519) {
                                    Str *_t1401 = Str_lit("]", 1ULL);
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1394, &(Bool){1});
                                    ;
                                    return _t1401;
                                } else {
                                    Bool _t1518; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Comma()); _t1518 = *_hp; free(_hp); }
                                    if (_t1518) {
                                        Str *_t1402 = Str_lit(",", 1ULL);
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1394, &(Bool){1});
                                        ;
                                        return _t1402;
                                    } else {
                                        Bool _t1517; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Colon()); _t1517 = *_hp; free(_hp); }
                                        if (_t1517) {
                                            Str *_t1403 = Str_lit(":", 1ULL);
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1394, &(Bool){1});
                                            ;
                                            return _t1403;
                                        } else {
                                            Bool _t1516; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Question()); _t1516 = *_hp; free(_hp); }
                                            if (_t1516) {
                                                Str *_t1404 = Str_lit("?", 1ULL);
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1394, &(Bool){1});
                                                ;
                                                return _t1404;
                                            } else {
                                                Bool _t1515; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Bang()); _t1515 = *_hp; free(_hp); }
                                                if (_t1515) {
                                                    Str *_t1405 = Str_lit("!", 1ULL);
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                    ;
                                                    return _t1405;
                                                } else {
                                                    Bool _t1514; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Minus()); _t1514 = *_hp; free(_hp); }
                                                    if (_t1514) {
                                                        Str *_t1406 = Str_lit("-", 1ULL);
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                        ;
                                                        return _t1406;
                                                    } else {
                                                        Bool _t1513; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Plus()); _t1513 = *_hp; free(_hp); }
                                                        if (_t1513) {
                                                            Str *_t1407 = Str_lit("+", 1ULL);
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                            ;
                                                            return _t1407;
                                                        } else {
                                                            Bool _t1512; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Star()); _t1512 = *_hp; free(_hp); }
                                                            if (_t1512) {
                                                                Str *_t1408 = Str_lit("*", 1ULL);
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                ;
                                                                return _t1408;
                                                            } else {
                                                                Bool _t1511; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Slash()); _t1511 = *_hp; free(_hp); }
                                                                if (_t1511) {
                                                                    Str *_t1409 = Str_lit("/", 1ULL);
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                    ;
                                                                    return _t1409;
                                                                } else {
                                                                    Bool _t1510; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Dot()); _t1510 = *_hp; free(_hp); }
                                                                    if (_t1510) {
                                                                        Str *_t1410 = Str_lit(".", 1ULL);
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                        ;
                                                                        return _t1410;
                                                                    } else {
                                                                        Bool _t1509; { Bool *_hp = TokenType_eq(_sw1394, TokenType_DotDot()); _t1509 = *_hp; free(_hp); }
                                                                        if (_t1509) {
                                                                            Str *_t1411 = Str_lit("..", 2ULL);
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                            ;
                                                                            return _t1411;
                                                                        } else {
                                                                            Bool _t1508; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Eq()); _t1508 = *_hp; free(_hp); }
                                                                            if (_t1508) {
                                                                                Str *_t1412 = Str_lit("=", 1ULL);
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                ;
                                                                                return _t1412;
                                                                            } else {
                                                                                Bool _t1507; { Bool *_hp = TokenType_eq(_sw1394, TokenType_EqEq()); _t1507 = *_hp; free(_hp); }
                                                                                if (_t1507) {
                                                                                    Str *_t1413 = Str_lit("==", 2ULL);
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                    ;
                                                                                    return _t1413;
                                                                                } else {
                                                                                    Bool _t1506; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Neq()); _t1506 = *_hp; free(_hp); }
                                                                                    if (_t1506) {
                                                                                        Str *_t1414 = Str_lit("!=", 2ULL);
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                        ;
                                                                                        return _t1414;
                                                                                    } else {
                                                                                        Bool _t1505; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Lt()); _t1505 = *_hp; free(_hp); }
                                                                                        if (_t1505) {
                                                                                            Str *_t1415 = Str_lit("<", 1ULL);
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                            ;
                                                                                            return _t1415;
                                                                                        } else {
                                                                                            Bool _t1504; { Bool *_hp = TokenType_eq(_sw1394, TokenType_LtEq()); _t1504 = *_hp; free(_hp); }
                                                                                            if (_t1504) {
                                                                                                Str *_t1416 = Str_lit("<=", 2ULL);
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                ;
                                                                                                return _t1416;
                                                                                            } else {
                                                                                                Bool _t1503; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Gt()); _t1503 = *_hp; free(_hp); }
                                                                                                if (_t1503) {
                                                                                                    Str *_t1417 = Str_lit(">", 1ULL);
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1417;
                                                                                                } else {
                                                                                                    Bool _t1502; { Bool *_hp = TokenType_eq(_sw1394, TokenType_GtEq()); _t1502 = *_hp; free(_hp); }
                                                                                                    if (_t1502) {
                                                                                                        Str *_t1418 = Str_lit(">=", 2ULL);
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1418;
                                                                                                    } else {
                                                                                                        Bool _t1501; { Bool *_hp = TokenType_eq(_sw1394, TokenType_ColonEq()); _t1501 = *_hp; free(_hp); }
                                                                                                        if (_t1501) {
                                                                                                            Str *_t1419 = Str_lit(":=", 2ULL);
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1419;
                                                                                                        } else {
                                                                                                            Bool _t1500; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Ident()); _t1500 = *_hp; free(_hp); }
                                                                                                            if (_t1500) {
                                                                                                                Str *_t1420 = Str_lit("identifier", 10ULL);
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1420;
                                                                                                            } else {
                                                                                                                Bool _t1499; { Bool *_hp = TokenType_eq(_sw1394, TokenType_StringTok()); _t1499 = *_hp; free(_hp); }
                                                                                                                if (_t1499) {
                                                                                                                    Str *_t1421 = Str_lit("string", 6ULL);
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1421;
                                                                                                                } else {
                                                                                                                    Bool _t1498; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Number()); _t1498 = *_hp; free(_hp); }
                                                                                                                    if (_t1498) {
                                                                                                                        Str *_t1422 = Str_lit("number", 6ULL);
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1422;
                                                                                                                    } else {
                                                                                                                        Bool _t1497; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Char()); _t1497 = *_hp; free(_hp); }
                                                                                                                        if (_t1497) {
                                                                                                                            Str *_t1423 = Str_lit("char", 4ULL);
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1423;
                                                                                                                        } else {
                                                                                                                            Bool _t1496; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwMode()); _t1496 = *_hp; free(_hp); }
                                                                                                                            if (_t1496) {
                                                                                                                                Str *_t1424 = Str_lit("mode", 4ULL);
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1424;
                                                                                                                            } else {
                                                                                                                                Bool _t1495; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwMut()); _t1495 = *_hp; free(_hp); }
                                                                                                                                if (_t1495) {
                                                                                                                                    Str *_t1425 = Str_lit("mut", 3ULL);
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1425;
                                                                                                                                } else {
                                                                                                                                    Bool _t1494; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwOwn()); _t1494 = *_hp; free(_hp); }
                                                                                                                                    if (_t1494) {
                                                                                                                                        Str *_t1426 = Str_lit("own", 3ULL);
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1426;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1493; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwRef()); _t1493 = *_hp; free(_hp); }
                                                                                                                                        if (_t1493) {
                                                                                                                                            Str *_t1427 = Str_lit("ref", 3ULL);
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1427;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1492; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwShallow()); _t1492 = *_hp; free(_hp); }
                                                                                                                                            if (_t1492) {
                                                                                                                                                Str *_t1428 = Str_lit("shallow", 7ULL);
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1428;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1491; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwStruct()); _t1491 = *_hp; free(_hp); }
                                                                                                                                                if (_t1491) {
                                                                                                                                                    Str *_t1429 = Str_lit("struct", 6ULL);
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1429;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1490; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwExtStruct()); _t1490 = *_hp; free(_hp); }
                                                                                                                                                    if (_t1490) {
                                                                                                                                                        Str *_t1430 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1430;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1489; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwEnum()); _t1489 = *_hp; free(_hp); }
                                                                                                                                                        if (_t1489) {
                                                                                                                                                            Str *_t1431 = Str_lit("enum", 4ULL);
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1431;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1488; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwNamespace()); _t1488 = *_hp; free(_hp); }
                                                                                                                                                            if (_t1488) {
                                                                                                                                                                Str *_t1432 = Str_lit("namespace", 9ULL);
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1432;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1487; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwFunc()); _t1487 = *_hp; free(_hp); }
                                                                                                                                                                if (_t1487) {
                                                                                                                                                                    Str *_t1433 = Str_lit("func", 4ULL);
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1433;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1486; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwProc()); _t1486 = *_hp; free(_hp); }
                                                                                                                                                                    if (_t1486) {
                                                                                                                                                                        Str *_t1434 = Str_lit("proc", 4ULL);
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1434;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1485; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwTest()); _t1485 = *_hp; free(_hp); }
                                                                                                                                                                        if (_t1485) {
                                                                                                                                                                            Str *_t1435 = Str_lit("test", 4ULL);
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1435;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1484; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwMacro()); _t1484 = *_hp; free(_hp); }
                                                                                                                                                                            if (_t1484) {
                                                                                                                                                                                Str *_t1436 = Str_lit("macro", 5ULL);
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1436;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1483; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwExtFunc()); _t1483 = *_hp; free(_hp); }
                                                                                                                                                                                if (_t1483) {
                                                                                                                                                                                    Str *_t1437 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1437;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1482; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwExtProc()); _t1482 = *_hp; free(_hp); }
                                                                                                                                                                                    if (_t1482) {
                                                                                                                                                                                        Str *_t1438 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1438;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1481; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwReturns()); _t1481 = *_hp; free(_hp); }
                                                                                                                                                                                        if (_t1481) {
                                                                                                                                                                                            Str *_t1439 = Str_lit("returns", 7ULL);
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1439;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1480; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwThrows()); _t1480 = *_hp; free(_hp); }
                                                                                                                                                                                            if (_t1480) {
                                                                                                                                                                                                Str *_t1440 = Str_lit("throws", 6ULL);
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1440;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1479; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwIf()); _t1479 = *_hp; free(_hp); }
                                                                                                                                                                                                if (_t1479) {
                                                                                                                                                                                                    Str *_t1441 = Str_lit("if", 2ULL);
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1441;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1478; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwElse()); _t1478 = *_hp; free(_hp); }
                                                                                                                                                                                                    if (_t1478) {
                                                                                                                                                                                                        Str *_t1442 = Str_lit("else", 4ULL);
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1442;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1477; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwWhile()); _t1477 = *_hp; free(_hp); }
                                                                                                                                                                                                        if (_t1477) {
                                                                                                                                                                                                            Str *_t1443 = Str_lit("while", 5ULL);
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1443;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1476; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwFor()); _t1476 = *_hp; free(_hp); }
                                                                                                                                                                                                            if (_t1476) {
                                                                                                                                                                                                                Str *_t1444 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1444;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1475; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwIn()); _t1475 = *_hp; free(_hp); }
                                                                                                                                                                                                                if (_t1475) {
                                                                                                                                                                                                                    Str *_t1445 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1445;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1474; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwSwitch()); _t1474 = *_hp; free(_hp); }
                                                                                                                                                                                                                    if (_t1474) {
                                                                                                                                                                                                                        Str *_t1446 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1446;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1473; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwMatch()); _t1473 = *_hp; free(_hp); }
                                                                                                                                                                                                                        if (_t1473) {
                                                                                                                                                                                                                            Str *_t1447 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1447;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1472; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwCase()); _t1472 = *_hp; free(_hp); }
                                                                                                                                                                                                                            if (_t1472) {
                                                                                                                                                                                                                                Str *_t1448 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1448;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1471; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwDefault()); _t1471 = *_hp; free(_hp); }
                                                                                                                                                                                                                                if (_t1471) {
                                                                                                                                                                                                                                    Str *_t1449 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1449;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1470; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwReturn()); _t1470 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    if (_t1470) {
                                                                                                                                                                                                                                        Str *_t1450 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1450;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1469; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwThrow()); _t1469 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        if (_t1469) {
                                                                                                                                                                                                                                            Str *_t1451 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1451;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1468; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwCatch()); _t1468 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            if (_t1468) {
                                                                                                                                                                                                                                                Str *_t1452 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1452;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1467; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwBreak()); _t1467 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                if (_t1467) {
                                                                                                                                                                                                                                                    Str *_t1453 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1453;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1466; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwContinue()); _t1466 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    if (_t1466) {
                                                                                                                                                                                                                                                        Str *_t1454 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1454;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1465; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwDefer()); _t1465 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        if (_t1465) {
                                                                                                                                                                                                                                                            Str *_t1455 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1455;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1464; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwTrue()); _t1464 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            if (_t1464) {
                                                                                                                                                                                                                                                                Str *_t1456 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1456;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1463; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwFalse()); _t1463 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                if (_t1463) {
                                                                                                                                                                                                                                                                    Str *_t1457 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1457;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1462; { Bool *_hp = TokenType_eq(_sw1394, TokenType_KwNull()); _t1462 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    if (_t1462) {
                                                                                                                                                                                                                                                                        Str *_t1458 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1458;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1461; { Bool *_hp = TokenType_eq(_sw1394, TokenType_Error()); _t1461 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        if (_t1461) {
                                                                                                                                                                                                                                                                            Str *_t1459 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1459;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Str *_t1460 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1394, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1460;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1394, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    {
        Str *_sw1526 = Str_clone(word);
        Str *_t1595 = Str_lit("mode", 4ULL);
        Bool _t1596; { Bool *_hp = Str_eq(_sw1526, _t1595); _t1596 = *_hp; free(_hp); }
        Str_delete(_t1595, &(Bool){1});
        if (_t1596) {
            Str_delete(_sw1526, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1593 = Str_lit("mut", 3ULL);
            Bool _t1594; { Bool *_hp = Str_eq(_sw1526, _t1593); _t1594 = *_hp; free(_hp); }
            Str_delete(_t1593, &(Bool){1});
            if (_t1594) {
                ;
                Str_delete(_sw1526, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1591 = Str_lit("own", 3ULL);
                Bool _t1592; { Bool *_hp = Str_eq(_sw1526, _t1591); _t1592 = *_hp; free(_hp); }
                Str_delete(_t1591, &(Bool){1});
                if (_t1592) {
                    ;
                    ;
                    Str_delete(_sw1526, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1589 = Str_lit("ref", 3ULL);
                    Bool _t1590; { Bool *_hp = Str_eq(_sw1526, _t1589); _t1590 = *_hp; free(_hp); }
                    Str_delete(_t1589, &(Bool){1});
                    if (_t1590) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1526, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1587 = Str_lit("shallow", 7ULL);
                        Bool _t1588; { Bool *_hp = Str_eq(_sw1526, _t1587); _t1588 = *_hp; free(_hp); }
                        Str_delete(_t1587, &(Bool){1});
                        if (_t1588) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1526, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1585 = Str_lit("struct", 6ULL);
                            Bool _t1586; { Bool *_hp = Str_eq(_sw1526, _t1585); _t1586 = *_hp; free(_hp); }
                            Str_delete(_t1585, &(Bool){1});
                            if (_t1586) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1526, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1583 = Str_lit("ext_struct", 10ULL);
                                Bool _t1584; { Bool *_hp = Str_eq(_sw1526, _t1583); _t1584 = *_hp; free(_hp); }
                                Str_delete(_t1583, &(Bool){1});
                                if (_t1584) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1526, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1581 = Str_lit("enum", 4ULL);
                                    Bool _t1582; { Bool *_hp = Str_eq(_sw1526, _t1581); _t1582 = *_hp; free(_hp); }
                                    Str_delete(_t1581, &(Bool){1});
                                    if (_t1582) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1526, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1579 = Str_lit("namespace", 9ULL);
                                        Bool _t1580; { Bool *_hp = Str_eq(_sw1526, _t1579); _t1580 = *_hp; free(_hp); }
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
                                            Str_delete(_sw1526, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1577 = Str_lit("func", 4ULL);
                                            Bool _t1578; { Bool *_hp = Str_eq(_sw1526, _t1577); _t1578 = *_hp; free(_hp); }
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
                                                Str_delete(_sw1526, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1575 = Str_lit("proc", 4ULL);
                                                Bool _t1576; { Bool *_hp = Str_eq(_sw1526, _t1575); _t1576 = *_hp; free(_hp); }
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
                                                    Str_delete(_sw1526, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1573 = Str_lit("test", 4ULL);
                                                    Bool _t1574; { Bool *_hp = Str_eq(_sw1526, _t1573); _t1574 = *_hp; free(_hp); }
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
                                                        Str_delete(_sw1526, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1571 = Str_lit("macro", 5ULL);
                                                        Bool _t1572; { Bool *_hp = Str_eq(_sw1526, _t1571); _t1572 = *_hp; free(_hp); }
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
                                                            Str_delete(_sw1526, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1569 = Str_lit("ext_func", 8ULL);
                                                            Bool _t1570; { Bool *_hp = Str_eq(_sw1526, _t1569); _t1570 = *_hp; free(_hp); }
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
                                                                Str_delete(_sw1526, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1567 = Str_lit("ext_proc", 8ULL);
                                                                Bool _t1568; { Bool *_hp = Str_eq(_sw1526, _t1567); _t1568 = *_hp; free(_hp); }
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
                                                                    Str_delete(_sw1526, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1565 = Str_lit("returns", 7ULL);
                                                                    Bool _t1566; { Bool *_hp = Str_eq(_sw1526, _t1565); _t1566 = *_hp; free(_hp); }
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
                                                                        Str_delete(_sw1526, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1563 = Str_lit("throws", 6ULL);
                                                                        Bool _t1564; { Bool *_hp = Str_eq(_sw1526, _t1563); _t1564 = *_hp; free(_hp); }
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
                                                                            Str_delete(_sw1526, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1561 = Str_lit("if", 2ULL);
                                                                            Bool _t1562; { Bool *_hp = Str_eq(_sw1526, _t1561); _t1562 = *_hp; free(_hp); }
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
                                                                                Str_delete(_sw1526, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1559 = Str_lit("else", 4ULL);
                                                                                Bool _t1560; { Bool *_hp = Str_eq(_sw1526, _t1559); _t1560 = *_hp; free(_hp); }
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
                                                                                    Str_delete(_sw1526, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1557 = Str_lit("while", 5ULL);
                                                                                    Bool _t1558; { Bool *_hp = Str_eq(_sw1526, _t1557); _t1558 = *_hp; free(_hp); }
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
                                                                                        Str_delete(_sw1526, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1555 = Str_lit("for", 3ULL);
                                                                                        Bool _t1556; { Bool *_hp = Str_eq(_sw1526, _t1555); _t1556 = *_hp; free(_hp); }
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
                                                                                            Str_delete(_sw1526, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1553 = Str_lit("in", 2ULL);
                                                                                            Bool _t1554; { Bool *_hp = Str_eq(_sw1526, _t1553); _t1554 = *_hp; free(_hp); }
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
                                                                                                Str_delete(_sw1526, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1551 = Str_lit("switch", 6ULL);
                                                                                                Bool _t1552; { Bool *_hp = Str_eq(_sw1526, _t1551); _t1552 = *_hp; free(_hp); }
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
                                                                                                    Str_delete(_sw1526, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1549 = Str_lit("match", 5ULL);
                                                                                                    Bool _t1550; { Bool *_hp = Str_eq(_sw1526, _t1549); _t1550 = *_hp; free(_hp); }
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
                                                                                                        Str_delete(_sw1526, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1547 = Str_lit("case", 4ULL);
                                                                                                        Bool _t1548; { Bool *_hp = Str_eq(_sw1526, _t1547); _t1548 = *_hp; free(_hp); }
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
                                                                                                            Str_delete(_sw1526, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1545 = Str_lit("default", 7ULL);
                                                                                                            Bool _t1546; { Bool *_hp = Str_eq(_sw1526, _t1545); _t1546 = *_hp; free(_hp); }
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
                                                                                                                Str_delete(_sw1526, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1543 = Str_lit("return", 6ULL);
                                                                                                                Bool _t1544; { Bool *_hp = Str_eq(_sw1526, _t1543); _t1544 = *_hp; free(_hp); }
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
                                                                                                                    Str_delete(_sw1526, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1541 = Str_lit("throw", 5ULL);
                                                                                                                    Bool _t1542; { Bool *_hp = Str_eq(_sw1526, _t1541); _t1542 = *_hp; free(_hp); }
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
                                                                                                                        Str_delete(_sw1526, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1539 = Str_lit("catch", 5ULL);
                                                                                                                        Bool _t1540; { Bool *_hp = Str_eq(_sw1526, _t1539); _t1540 = *_hp; free(_hp); }
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
                                                                                                                            Str_delete(_sw1526, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1537 = Str_lit("break", 5ULL);
                                                                                                                            Bool _t1538; { Bool *_hp = Str_eq(_sw1526, _t1537); _t1538 = *_hp; free(_hp); }
                                                                                                                            Str_delete(_t1537, &(Bool){1});
                                                                                                                            if (_t1538) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1526, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1535 = Str_lit("continue", 8ULL);
                                                                                                                                Bool _t1536; { Bool *_hp = Str_eq(_sw1526, _t1535); _t1536 = *_hp; free(_hp); }
                                                                                                                                Str_delete(_t1535, &(Bool){1});
                                                                                                                                if (_t1536) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1526, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1533 = Str_lit("defer", 5ULL);
                                                                                                                                    Bool _t1534; { Bool *_hp = Str_eq(_sw1526, _t1533); _t1534 = *_hp; free(_hp); }
                                                                                                                                    Str_delete(_t1533, &(Bool){1});
                                                                                                                                    if (_t1534) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1526, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1531 = Str_lit("true", 4ULL);
                                                                                                                                        Bool _t1532; { Bool *_hp = Str_eq(_sw1526, _t1531); _t1532 = *_hp; free(_hp); }
                                                                                                                                        Str_delete(_t1531, &(Bool){1});
                                                                                                                                        if (_t1532) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1526, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1529 = Str_lit("false", 5ULL);
                                                                                                                                            Bool _t1530; { Bool *_hp = Str_eq(_sw1526, _t1529); _t1530 = *_hp; free(_hp); }
                                                                                                                                            Str_delete(_t1529, &(Bool){1});
                                                                                                                                            if (_t1530) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1526, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1527 = Str_lit("NULL", 4ULL);
                                                                                                                                                Bool _t1528; { Bool *_hp = Str_eq(_sw1526, _t1527); _t1528 = *_hp; free(_hp); }
                                                                                                                                                Str_delete(_t1527, &(Bool){1});
                                                                                                                                                if (_t1528) {
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1526, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return TokenType_KwNull();
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1526, &(Bool){1});
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
                ;
            }
            ;
        }
        Str_delete(_sw1526, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * source, Str * path) {
    Str *_t1952 = Str_lit("Token", 5ULL);
    U64 _t1953; { U64 *_hp = Token_size(); _t1953 = *_hp; free(_hp); }
    Vec *tokens = Vec_new(_t1952, &(U64){_t1953});
    Str_delete(_t1952, &(Bool){1});
    ;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    I64 line = 1;
    U64 line_start = 0;
    U64 src_len; { U64 *_hp = Str_len(source); src_len = *_hp; free(_hp); }
    while (1) {
        Bool _wcond1597; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1597 = *_hp; free(_hp); }
        if (_wcond1597) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_get(source, pos);
        U8 _t1897 = 32;
        U8 _t1898 = 9;
        Bool _t1899 = U8_eq(DEREF(c), _t1897);
        ;
        Bool _t1900 = U8_eq(DEREF(c), _t1898);
        ;
        U8 _t1901 = 13;
        Bool _t1902 = Bool_or(_t1899, _t1900);
        ;
        ;
        Bool _t1903 = U8_eq(DEREF(c), _t1901);
        ;
        U8 _t1904 = 59;
        Bool _t1905 = Bool_or(_t1902, _t1903);
        ;
        ;
        Bool _t1906 = U8_eq(DEREF(c), _t1904);
        ;
        Bool _t1907 = Bool_or(_t1905, _t1906);
        ;
        ;
        if (_t1907) {
            U64 _t1598 = 1;
            U64 _t1599 = U64_add(DEREF(pos), _t1598);
            ;
            *pos = _t1599;
            ;
            ;
            continue;
        }
        ;
        U8 _t1908 = 10;
        Bool _t1909 = U8_eq(DEREF(c), _t1908);
        ;
        if (_t1909) {
            U64 _t1600 = 1;
            U64 _t1601 = U64_add(DEREF(pos), _t1600);
            ;
            *pos = _t1601;
            ;
            I64 _t1602 = 1;
            I64 _t1603 = I64_add(line, _t1602);
            ;
            line = _t1603;
            ;
            U64 _t1604 = U64_clone(pos);
            line_start = _t1604;
            ;
            ;
            continue;
        }
        ;
        U64 _t1910 = U64_sub(DEREF(pos), line_start);
        U64 _t1911 = 1;
        U64 _t1912 = U64_add(_t1910, _t1911);
        ;
        ;
        I64 col = U64_to_i64(_t1912);
        ;
        U64 start = U64_clone(pos);
        U8 _t1913 = 35;
        Bool _t1914 = U8_eq(DEREF(c), _t1913);
        ;
        if (_t1914) {
            while (1) {
                Bool _wcond1605; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1605 = *_hp; free(_hp); }
                if (_wcond1605) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1606 = Str_get(source, pos);
                U8 _t1607 = 10;
                Bool _t1608 = U8_eq(DEREF(_t1606), _t1607);
                ;
                if (_t1608) {
                    ;
                    break;
                }
                ;
                U64 _t1609 = 1;
                U64 _t1610 = U64_add(DEREF(pos), _t1609);
                ;
                *pos = _t1610;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1915 = 47;
        U64 _t1916 = 1;
        U64 _t1917 = U64_add(DEREF(pos), _t1916);
        ;
        Bool _t1918 = U8_eq(DEREF(c), _t1915);
        ;
        Bool _t1919; { Bool *_hp = U64_lt(&(U64){_t1917}, &(U64){src_len}); _t1919 = *_hp; free(_hp); }
        ;
        Bool _t1920 = Bool_and(_t1918, _t1919);
        ;
        ;
        if (_t1920) {
            U64 _t1671 = 1;
            U64 *_t1672 = malloc(sizeof(U64)); *_t1672 = U64_add(DEREF(pos), _t1671);
            ;
            U8 *c2 = Str_get(source, _t1672);
            U8 _t1673 = 47;
            Bool _t1674 = U8_eq(DEREF(c2), _t1673);
            ;
            if (_t1674) {
                while (1) {
                    Bool _wcond1611; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1611 = *_hp; free(_hp); }
                    if (_wcond1611) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1612 = Str_get(source, pos);
                    U8 _t1613 = 10;
                    Bool _t1614 = U8_eq(DEREF(_t1612), _t1613);
                    ;
                    if (_t1614) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1615 = 1;
                    U64 _t1616 = U64_add(DEREF(pos), _t1615);
                    ;
                    *pos = _t1616;
                    ;
                }
                U64_delete(_t1672, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1675 = 42;
            Bool _t1676 = U8_eq(DEREF(c2), _t1675);
            U64_delete(_t1672, &(Bool){1});
            ;
            if (_t1676) {
                U64 _t1667 = 2;
                U64 _t1668 = U64_add(DEREF(pos), _t1667);
                ;
                *pos = _t1668;
                ;
                I64 depth = 1;
                while (1) {
                    Bool _wcond1617; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1617 = *_hp; free(_hp); }
                    if (_wcond1617) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1642 = 0;
                    Bool _t1643; { Bool *_hp = I64_lte(&(I64){depth}, &(I64){_t1642}); _t1643 = *_hp; free(_hp); }
                    ;
                    if (_t1643) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1644 = 1;
                    U64 _t1645 = U64_add(DEREF(pos), _t1644);
                    ;
                    Bool _t1646; { Bool *_hp = U64_lt(&(U64){_t1645}, &(U64){src_len}); _t1646 = *_hp; free(_hp); }
                    ;
                    if (_t1646) {
                        U8 *b1 = Str_get(source, pos);
                        U64 _t1626 = 1;
                        U64 *_t1627 = malloc(sizeof(U64)); *_t1627 = U64_add(DEREF(pos), _t1626);
                        ;
                        U8 *b2 = Str_get(source, _t1627);
                        U8 _t1628 = 47;
                        U8 _t1629 = 42;
                        Bool _t1630 = U8_eq(DEREF(b1), _t1628);
                        ;
                        Bool _t1631 = U8_eq(DEREF(b2), _t1629);
                        ;
                        Bool _t1632 = Bool_and(_t1630, _t1631);
                        ;
                        ;
                        if (_t1632) {
                            I64 _t1618 = 1;
                            I64 _t1619 = I64_add(depth, _t1618);
                            ;
                            depth = _t1619;
                            ;
                            U64 _t1620 = 2;
                            U64 _t1621 = U64_add(DEREF(pos), _t1620);
                            ;
                            *pos = _t1621;
                            ;
                            U64_delete(_t1627, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1633 = 42;
                        U8 _t1634 = 47;
                        Bool _t1635 = U8_eq(DEREF(b1), _t1633);
                        ;
                        Bool _t1636 = U8_eq(DEREF(b2), _t1634);
                        U64_delete(_t1627, &(Bool){1});
                        ;
                        Bool _t1637 = Bool_and(_t1635, _t1636);
                        ;
                        ;
                        if (_t1637) {
                            I64 _t1622 = 1;
                            I64 _t1623 = I64_sub(depth, _t1622);
                            ;
                            depth = _t1623;
                            ;
                            U64 _t1624 = 2;
                            U64 _t1625 = U64_add(DEREF(pos), _t1624);
                            ;
                            *pos = _t1625;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1647 = Str_get(source, pos);
                    U8 _t1648 = 10;
                    Bool _t1649 = U8_eq(DEREF(_t1647), _t1648);
                    ;
                    if (_t1649) {
                        I64 _t1638 = 1;
                        I64 _t1639 = I64_add(line, _t1638);
                        ;
                        line = _t1639;
                        ;
                        U64 _t1640 = 1;
                        U64 _t1641 = U64_add(DEREF(pos), _t1640);
                        ;
                        line_start = _t1641;
                        ;
                    }
                    ;
                    U64 _t1650 = 1;
                    U64 _t1651 = U64_add(DEREF(pos), _t1650);
                    ;
                    *pos = _t1651;
                    ;
                }
                I64 _t1669 = 0;
                Bool _t1670; { Bool *_hp = I64_gt(&(I64){depth}, &(I64){_t1669}); _t1670 = *_hp; free(_hp); }
                ;
                ;
                if (_t1670) {
                    Str *_t1652 = Str_lit("Str", 3ULL);
                    U64 _t1653; { U64 *_hp = Str_size(); _t1653 = *_hp; free(_hp); }
                    U64 _t1654 = 6;
                    Array *_va19 = Array_new(_t1652, &(U64){_t1653}, &(U64){_t1654});
                    Str_delete(_t1652, &(Bool){1});
                    ;
                    ;
                    U64 _t1655 = 0;
                    Str *_t1656 = Str_clone(path);
                    Array_set(_va19, &(U64){_t1655}, _t1656);
                    ;
                    U64 _t1657 = 1;
                    Str *_t1658 = Str_lit(":", 1ULL);
                    Array_set(_va19, &(U64){_t1657}, _t1658);
                    ;
                    U64 _t1659 = 2;
                    Str *_t1660 = I64_to_str(&(I64){line});
                    Array_set(_va19, &(U64){_t1659}, _t1660);
                    ;
                    U64 _t1661 = 3;
                    Str *_t1662 = Str_lit(":", 1ULL);
                    Array_set(_va19, &(U64){_t1661}, _t1662);
                    ;
                    U64 _t1663 = 4;
                    Str *_t1664 = I64_to_str(&(I64){col});
                    Array_set(_va19, &(U64){_t1663}, _t1664);
                    ;
                    U64 _t1665 = 5;
                    Str *_t1666 = Str_lit(": error: unterminated comment", 29ULL);
                    Array_set(_va19, &(U64){_t1665}, _t1666);
                    ;
                    println(_va19);
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
        Bool _t1921; { Bool *_hp = is_digit(c); _t1921 = *_hp; free(_hp); }
        if (_t1921) {
            while (1) {
                Bool _wcond1677; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1677 = *_hp; free(_hp); }
                if (_wcond1677) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1678 = Str_get(source, pos);
                Bool _t1679; { Bool *_hp = is_digit(_t1678); _t1679 = *_hp; free(_hp); }
                Bool _t1680 = Bool_not(_t1679);
                ;
                if (_t1680) {
                    ;
                    break;
                }
                ;
                U64 _t1681 = 1;
                U64 _t1682 = U64_add(DEREF(pos), _t1681);
                ;
                *pos = _t1682;
                ;
            }
            U64 _t1699 = 1;
            U64 _t1700 = U64_add(DEREF(pos), _t1699);
            ;
            Bool _t1701; { Bool *_hp = U64_lt(&(U64){_t1700}, &(U64){src_len}); _t1701 = *_hp; free(_hp); }
            ;
            if (_t1701) {
                U8 *_t1691 = Str_get(source, pos);
                U8 _t1692 = 46;
                U64 _t1693 = 1;
                U64 *_t1694 = malloc(sizeof(U64)); *_t1694 = U64_add(DEREF(pos), _t1693);
                ;
                U8 *_t1695 = Str_get(source, _t1694);
                Bool _t1696 = U8_eq(DEREF(_t1691), _t1692);
                ;
                Bool _t1697; { Bool *_hp = is_digit(_t1695); _t1697 = *_hp; free(_hp); }
                U64_delete(_t1694, &(Bool){1});
                Bool _t1698 = Bool_and(_t1696, _t1697);
                ;
                ;
                if (_t1698) {
                    U64 _t1689 = 1;
                    U64 _t1690 = U64_add(DEREF(pos), _t1689);
                    ;
                    *pos = _t1690;
                    ;
                    while (1) {
                        Bool _wcond1683; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1683 = *_hp; free(_hp); }
                        if (_wcond1683) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1684 = Str_get(source, pos);
                        Bool _t1685; { Bool *_hp = is_digit(_t1684); _t1685 = *_hp; free(_hp); }
                        Bool _t1686 = Bool_not(_t1685);
                        ;
                        if (_t1686) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1687 = 1;
                        U64 _t1688 = U64_add(DEREF(pos), _t1687);
                        ;
                        *pos = _t1688;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1702 = U64_sub(DEREF(pos), start);
            I64 _t1703 = I64_clone(&(I64){col});
            Token *_t1704 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1704->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1702}); _t1704->text = *_ca; free(_ca); }
            _t1704->line = I64_clone(&(I64){line});
            _t1704->col = _t1703;
            ;
            ;
            Vec_push(tokens, _t1704);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1922; { Bool *_hp = is_alpha(c); _t1922 = *_hp; free(_hp); }
        if (_t1922) {
            while (1) {
                Bool _wcond1705; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1705 = *_hp; free(_hp); }
                if (_wcond1705) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1706 = Str_get(source, pos);
                Bool _t1707; { Bool *_hp = is_alnum(_t1706); _t1707 = *_hp; free(_hp); }
                Bool _t1708 = Bool_not(_t1707);
                ;
                if (_t1708) {
                    ;
                    break;
                }
                ;
                U64 _t1709 = 1;
                U64 _t1710 = U64_add(DEREF(pos), _t1709);
                ;
                *pos = _t1710;
                ;
            }
            U64 _t1711 = U64_sub(DEREF(pos), start);
            Str *word = Str_substr(source, &(U64){start}, &(U64){_t1711});
            ;
            TokenType *type = lookup_keyword(word);
            I64 _t1712 = I64_clone(&(I64){line});
            I64 _t1713 = I64_clone(&(I64){col});
            Token *_t1714 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1714->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1714->text = *_ca; free(_ca); }
            _t1714->line = _t1712;
            _t1714->col = _t1713;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1714);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1923 = 34;
        Bool _t1924 = U8_eq(DEREF(c), _t1923);
        ;
        if (_t1924) {
            U64 _t1764 = 1;
            U64 _t1765 = U64_add(DEREF(pos), _t1764);
            ;
            *pos = _t1765;
            ;
            while (1) {
                Bool _wcond1715; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1715 = *_hp; free(_hp); }
                if (_wcond1715) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1722 = Str_get(source, pos);
                U8 _t1723 = 34;
                Bool _t1724 = U8_eq(DEREF(_t1722), _t1723);
                ;
                if (_t1724) {
                    ;
                    break;
                }
                ;
                U8 *_t1725 = Str_get(source, pos);
                U8 _t1726 = 92;
                U64 _t1727 = 1;
                U64 _t1728 = U64_add(DEREF(pos), _t1727);
                ;
                Bool _t1729 = U8_eq(DEREF(_t1725), _t1726);
                ;
                Bool _t1730; { Bool *_hp = U64_lt(&(U64){_t1728}, &(U64){src_len}); _t1730 = *_hp; free(_hp); }
                ;
                Bool _t1731 = Bool_and(_t1729, _t1730);
                ;
                ;
                if (_t1731) {
                    U64 _t1716 = 1;
                    U64 _t1717 = U64_add(DEREF(pos), _t1716);
                    ;
                    *pos = _t1717;
                    ;
                }
                ;
                U8 *_t1732 = Str_get(source, pos);
                U8 _t1733 = 10;
                Bool _t1734 = U8_eq(DEREF(_t1732), _t1733);
                ;
                if (_t1734) {
                    I64 _t1718 = 1;
                    I64 _t1719 = I64_add(line, _t1718);
                    ;
                    line = _t1719;
                    ;
                    U64 _t1720 = 1;
                    U64 _t1721 = U64_add(DEREF(pos), _t1720);
                    ;
                    line_start = _t1721;
                    ;
                }
                ;
                U64 _t1735 = 1;
                U64 _t1736 = U64_add(DEREF(pos), _t1735);
                ;
                *pos = _t1736;
                ;
            }
            U8 *_t1766 = Str_get(source, pos);
            U8 _t1767 = 34;
            Bool _t1768; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1768 = *_hp; free(_hp); }
            Bool _t1769 = U8_eq(DEREF(_t1766), _t1767);
            ;
            Bool _t1770 = Bool_and(_t1768, _t1769);
            ;
            ;
            if (_t1770) {
                U64 _t1737 = 1;
                U64 _t1738 = U64_add(DEREF(pos), _t1737);
                ;
                *pos = _t1738;
                ;
                U64 _t1739 = 1;
                U64 _t1740 = U64_sub(DEREF(pos), start);
                U64 _t1741 = 2;
                U64 _t1742 = U64_add(start, _t1739);
                ;
                U64 _t1743 = U64_sub(_t1740, _t1741);
                ;
                ;
                I64 _t1744 = I64_clone(&(I64){col});
                Token *_t1745 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1745->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){_t1742}, &(U64){_t1743}); _t1745->text = *_ca; free(_ca); }
                _t1745->line = I64_clone(&(I64){line});
                _t1745->col = _t1744;
                ;
                ;
                ;
                Vec_push(tokens, _t1745);
            } else {
                Str *_t1746 = Str_lit("Str", 3ULL);
                U64 _t1747; { U64 *_hp = Str_size(); _t1747 = *_hp; free(_hp); }
                U64 _t1748 = 6;
                Array *_va20 = Array_new(_t1746, &(U64){_t1747}, &(U64){_t1748});
                Str_delete(_t1746, &(Bool){1});
                ;
                ;
                U64 _t1749 = 0;
                Str *_t1750 = Str_clone(path);
                Array_set(_va20, &(U64){_t1749}, _t1750);
                ;
                U64 _t1751 = 1;
                Str *_t1752 = Str_lit(":", 1ULL);
                Array_set(_va20, &(U64){_t1751}, _t1752);
                ;
                U64 _t1753 = 2;
                Str *_t1754 = I64_to_str(&(I64){line});
                Array_set(_va20, &(U64){_t1753}, _t1754);
                ;
                U64 _t1755 = 3;
                Str *_t1756 = Str_lit(":", 1ULL);
                Array_set(_va20, &(U64){_t1755}, _t1756);
                ;
                U64 _t1757 = 4;
                Str *_t1758 = I64_to_str(&(I64){col});
                Array_set(_va20, &(U64){_t1757}, _t1758);
                ;
                U64 _t1759 = 5;
                Str *_t1760 = Str_lit(": error: unterminated string", 28ULL);
                Array_set(_va20, &(U64){_t1759}, _t1760);
                ;
                println(_va20);
                U64 _t1761 = U64_sub(DEREF(pos), start);
                I64 _t1762 = I64_clone(&(I64){col});
                Token *_t1763 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1763->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1761}); _t1763->text = *_ca; free(_ca); }
                _t1763->line = I64_clone(&(I64){line});
                _t1763->col = _t1762;
                ;
                ;
                Vec_push(tokens, _t1763);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1925 = 39;
        Bool _t1926 = U8_eq(DEREF(c), _t1925);
        ;
        if (_t1926) {
            U64 _t1796 = 1;
            U64 _t1797 = U64_add(DEREF(pos), _t1796);
            ;
            *pos = _t1797;
            ;
            U64 ch_start = U64_clone(pos);
            U8 *_t1798 = Str_get(source, pos);
            U8 _t1799 = 92;
            U64 _t1800 = 1;
            U64 _t1801 = U64_add(DEREF(pos), _t1800);
            ;
            Bool _t1802 = U8_eq(DEREF(_t1798), _t1799);
            ;
            Bool _t1803; { Bool *_hp = U64_lt(&(U64){_t1801}, &(U64){src_len}); _t1803 = *_hp; free(_hp); }
            ;
            Bool _t1804; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1804 = *_hp; free(_hp); }
            Bool _t1805 = Bool_and(_t1802, _t1803);
            ;
            ;
            Bool _t1806 = Bool_and(_t1804, _t1805);
            ;
            ;
            if (_t1806) {
                U64 _t1771 = 1;
                U64 _t1772 = U64_add(DEREF(pos), _t1771);
                ;
                *pos = _t1772;
                ;
            }
            ;
            U64 _t1807 = 1;
            U64 _t1808 = U64_add(DEREF(pos), _t1807);
            ;
            *pos = _t1808;
            ;
            U8 *_t1809 = Str_get(source, pos);
            U8 _t1810 = 39;
            Bool _t1811; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1811 = *_hp; free(_hp); }
            Bool _t1812 = U8_eq(DEREF(_t1809), _t1810);
            ;
            Bool _t1813 = Bool_and(_t1811, _t1812);
            ;
            ;
            if (_t1813) {
                U64 _t1773 = U64_sub(DEREF(pos), ch_start);
                I64 _t1774 = I64_clone(&(I64){col});
                Token *_t1775 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1775->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){ch_start}, &(U64){_t1773}); _t1775->text = *_ca; free(_ca); }
                _t1775->line = I64_clone(&(I64){line});
                _t1775->col = _t1774;
                ;
                ;
                Vec_push(tokens, _t1775);
                U64 _t1776 = 1;
                U64 _t1777 = U64_add(DEREF(pos), _t1776);
                ;
                *pos = _t1777;
                ;
            } else {
                Str *_t1778 = Str_lit("Str", 3ULL);
                U64 _t1779; { U64 *_hp = Str_size(); _t1779 = *_hp; free(_hp); }
                U64 _t1780 = 6;
                Array *_va21 = Array_new(_t1778, &(U64){_t1779}, &(U64){_t1780});
                Str_delete(_t1778, &(Bool){1});
                ;
                ;
                U64 _t1781 = 0;
                Str *_t1782 = Str_clone(path);
                Array_set(_va21, &(U64){_t1781}, _t1782);
                ;
                U64 _t1783 = 1;
                Str *_t1784 = Str_lit(":", 1ULL);
                Array_set(_va21, &(U64){_t1783}, _t1784);
                ;
                U64 _t1785 = 2;
                Str *_t1786 = I64_to_str(&(I64){line});
                Array_set(_va21, &(U64){_t1785}, _t1786);
                ;
                U64 _t1787 = 3;
                Str *_t1788 = Str_lit(":", 1ULL);
                Array_set(_va21, &(U64){_t1787}, _t1788);
                ;
                U64 _t1789 = 4;
                Str *_t1790 = I64_to_str(&(I64){col});
                Array_set(_va21, &(U64){_t1789}, _t1790);
                ;
                U64 _t1791 = 5;
                Str *_t1792 = Str_lit(": error: unterminated character literal", 39ULL);
                Array_set(_va21, &(U64){_t1791}, _t1792);
                ;
                println(_va21);
                U64 _t1793 = U64_sub(DEREF(pos), start);
                I64 _t1794 = I64_clone(&(I64){col});
                Token *_t1795 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1795->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1793}); _t1795->text = *_ca; free(_ca); }
                _t1795->line = I64_clone(&(I64){line});
                _t1795->col = _t1794;
                ;
                ;
                Vec_push(tokens, _t1795);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t1927 = 1;
        U64 _t1928 = U64_add(DEREF(pos), _t1927);
        ;
        Bool _t1929; { Bool *_hp = U64_lt(&(U64){_t1928}, &(U64){src_len}); _t1929 = *_hp; free(_hp); }
        ;
        if (_t1929) {
            U64 _t1845 = 1;
            U64 *_t1846 = malloc(sizeof(U64)); *_t1846 = U64_add(DEREF(pos), _t1845);
            ;
            U8 *c2 = Str_get(source, _t1846);
            TokenType *two = TokenType_clone(TokenType_Eof());
            U8 _t1847 = 58;
            U8 _t1848 = 61;
            Bool _t1849 = U8_eq(DEREF(c), _t1847);
            ;
            Bool _t1850 = U8_eq(DEREF(c2), _t1848);
            ;
            Bool _t1851 = Bool_and(_t1849, _t1850);
            ;
            ;
            if (_t1851) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t1834 = 61;
                U8 _t1835 = 61;
                Bool _t1836 = U8_eq(DEREF(c), _t1834);
                ;
                Bool _t1837 = U8_eq(DEREF(c2), _t1835);
                ;
                Bool _t1838 = Bool_and(_t1836, _t1837);
                ;
                ;
                if (_t1838) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t1829 = 33;
                    U8 _t1830 = 61;
                    Bool _t1831 = U8_eq(DEREF(c), _t1829);
                    ;
                    Bool _t1832 = U8_eq(DEREF(c2), _t1830);
                    ;
                    Bool _t1833 = Bool_and(_t1831, _t1832);
                    ;
                    ;
                    if (_t1833) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t1824 = 60;
                        U8 _t1825 = 61;
                        Bool _t1826 = U8_eq(DEREF(c), _t1824);
                        ;
                        Bool _t1827 = U8_eq(DEREF(c2), _t1825);
                        ;
                        Bool _t1828 = Bool_and(_t1826, _t1827);
                        ;
                        ;
                        if (_t1828) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t1819 = 62;
                            U8 _t1820 = 61;
                            Bool _t1821 = U8_eq(DEREF(c), _t1819);
                            ;
                            Bool _t1822 = U8_eq(DEREF(c2), _t1820);
                            ;
                            Bool _t1823 = Bool_and(_t1821, _t1822);
                            ;
                            ;
                            if (_t1823) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t1814 = 46;
                                U8 _t1815 = 46;
                                Bool _t1816 = U8_eq(DEREF(c), _t1814);
                                ;
                                Bool _t1817 = U8_eq(DEREF(c2), _t1815);
                                ;
                                Bool _t1818 = Bool_and(_t1816, _t1817);
                                ;
                                ;
                                if (_t1818) {
                                    two = TokenType_clone(TokenType_DotDot());
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            U64_delete(_t1846, &(Bool){1});
            ;
            Bool _t1852; { Bool *_hp = TokenType_eq(two, TokenType_Eof()); _t1852 = *_hp; free(_hp); }
            Bool _t1853 = Bool_not(_t1852);
            ;
            if (_t1853) {
                U64 _t1839 = 2;
                I64 _t1840 = I64_clone(&(I64){line});
                I64 _t1841 = I64_clone(&(I64){col});
                Token *_t1842 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1842->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1839}); _t1842->text = *_ca; free(_ca); }
                _t1842->line = _t1840;
                _t1842->col = _t1841;
                ;
                ;
                ;
                Vec_push(tokens, _t1842);
                U64 _t1843 = 2;
                U64 _t1844 = U64_add(DEREF(pos), _t1843);
                ;
                *pos = _t1844;
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
            U8 _sw1854 = U8_clone(c);
            U8 _t1889 = 40;
            Bool _t1890 = U8_eq(_sw1854, _t1889);
            ;
            if (_t1890) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1887 = 41;
                Bool _t1888 = U8_eq(_sw1854, _t1887);
                ;
                if (_t1888) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1885 = 123;
                    Bool _t1886 = U8_eq(_sw1854, _t1885);
                    ;
                    if (_t1886) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1883 = 125;
                        Bool _t1884 = U8_eq(_sw1854, _t1883);
                        ;
                        if (_t1884) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1881 = 91;
                            Bool _t1882 = U8_eq(_sw1854, _t1881);
                            ;
                            if (_t1882) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1879 = 93;
                                Bool _t1880 = U8_eq(_sw1854, _t1879);
                                ;
                                if (_t1880) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1877 = 44;
                                    Bool _t1878 = U8_eq(_sw1854, _t1877);
                                    ;
                                    if (_t1878) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1875 = 58;
                                        Bool _t1876 = U8_eq(_sw1854, _t1875);
                                        ;
                                        if (_t1876) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1873 = 46;
                                            Bool _t1874 = U8_eq(_sw1854, _t1873);
                                            ;
                                            if (_t1874) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1871 = 63;
                                                Bool _t1872 = U8_eq(_sw1854, _t1871);
                                                ;
                                                if (_t1872) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1869 = 33;
                                                    Bool _t1870 = U8_eq(_sw1854, _t1869);
                                                    ;
                                                    if (_t1870) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1867 = 43;
                                                        Bool _t1868 = U8_eq(_sw1854, _t1867);
                                                        ;
                                                        if (_t1868) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1865 = 45;
                                                            Bool _t1866 = U8_eq(_sw1854, _t1865);
                                                            ;
                                                            if (_t1866) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1863 = 42;
                                                                Bool _t1864 = U8_eq(_sw1854, _t1863);
                                                                ;
                                                                if (_t1864) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1861 = 47;
                                                                    Bool _t1862 = U8_eq(_sw1854, _t1861);
                                                                    ;
                                                                    if (_t1862) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1859 = 61;
                                                                        Bool _t1860 = U8_eq(_sw1854, _t1859);
                                                                        ;
                                                                        if (_t1860) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1857 = 60;
                                                                            Bool _t1858 = U8_eq(_sw1854, _t1857);
                                                                            ;
                                                                            if (_t1858) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1855 = 62;
                                                                                Bool _t1856 = U8_eq(_sw1854, _t1855);
                                                                                ;
                                                                                if (_t1856) {
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
        Bool _t1930; { Bool *_hp = TokenType_eq(single, TokenType_Eof()); _t1930 = *_hp; free(_hp); }
        Bool _t1931 = Bool_not(_t1930);
        ;
        if (_t1931) {
            U64 _t1891 = 1;
            I64 _t1892 = I64_clone(&(I64){line});
            I64 _t1893 = I64_clone(&(I64){col});
            Token *_t1894 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1894->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1891}); _t1894->text = *_ca; free(_ca); }
            _t1894->line = _t1892;
            _t1894->col = _t1893;
            ;
            ;
            ;
            Vec_push(tokens, _t1894);
            U64 _t1895 = 1;
            U64 _t1896 = U64_add(DEREF(pos), _t1895);
            ;
            *pos = _t1896;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t1932 = Str_lit("Str", 3ULL);
        U64 _t1933; { U64 *_hp = Str_size(); _t1933 = *_hp; free(_hp); }
        U64 _t1934 = 6;
        Array *_va22 = Array_new(_t1932, &(U64){_t1933}, &(U64){_t1934});
        Str_delete(_t1932, &(Bool){1});
        ;
        ;
        U64 _t1935 = 0;
        Str *_t1936 = Str_clone(path);
        Array_set(_va22, &(U64){_t1935}, _t1936);
        ;
        U64 _t1937 = 1;
        Str *_t1938 = Str_lit(":", 1ULL);
        Array_set(_va22, &(U64){_t1937}, _t1938);
        ;
        U64 _t1939 = 2;
        Str *_t1940 = I64_to_str(&(I64){line});
        Array_set(_va22, &(U64){_t1939}, _t1940);
        ;
        U64 _t1941 = 3;
        Str *_t1942 = Str_lit(":", 1ULL);
        Array_set(_va22, &(U64){_t1941}, _t1942);
        ;
        U64 _t1943 = 4;
        Str *_t1944 = I64_to_str(&(I64){col});
        Array_set(_va22, &(U64){_t1943}, _t1944);
        ;
        U64 _t1945 = 5;
        Str *_t1946 = Str_lit(": error: unexpected character", 29ULL);
        Array_set(_va22, &(U64){_t1945}, _t1946);
        ;
        println(_va22);
        U64 _t1947 = 1;
        I64 _t1948 = I64_clone(&(I64){col});
        ;
        Token *_t1949 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1949->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1947}); _t1949->text = *_ca; free(_ca); }
        _t1949->line = I64_clone(&(I64){line});
        _t1949->col = _t1948;
        ;
        ;
        ;
        Vec_push(tokens, _t1949);
        U64 _t1950 = 1;
        U64 _t1951 = U64_add(DEREF(pos), _t1950);
        ;
        *pos = _t1951;
        ;
    }
    ;
    U64 _t1954 = U64_sub(DEREF(pos), line_start);
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t1955 = 1;
    U64 _t1956 = U64_add(_t1954, _t1955);
    ;
    ;
    I64 col = U64_to_i64(_t1956);
    ;
    I64 _t1957 = I64_clone(&(I64){col});
    ;
    Token *_t1958 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t1958->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t1958->text = *_ca; free(_ca); }
    _t1958->line = I64_clone(&(I64){line});
    _t1958->col = _t1957;
    ;
    ;
    Vec_push(tokens, _t1958);
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
    _t1959 = malloc(sizeof(I64));
    *_t1959 = 0;
    _t1960 = malloc(sizeof(I64));
    *_t1960 = 1;
    _t1961 = malloc(sizeof(I64)); *_t1961 = I64_sub(DEREF(_t1959), DEREF(_t1960));
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t1961));
    _t1962 = malloc(sizeof(I64));
    *_t1962 = 0;
    _t1963 = malloc(sizeof(I64));
    *_t1963 = 2;
    _t1964 = malloc(sizeof(I64)); *_t1964 = I64_sub(DEREF(_t1962), DEREF(_t1963));
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t1964));
}

