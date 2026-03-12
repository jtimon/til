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
typedef struct Tuple Tuple;
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
U8 * Str_byte_at(Str * self, U64 * i);
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
Tuple * Tuple_new(void);
U64 * Tuple_len(Tuple * self);
void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val);
void * Tuple_get(Tuple * self, U64 * i);
Str * Tuple_type_at(Tuple * self, U64 * i);
U64 * Tuple_size_at(Tuple * self, U64 * i);
void Tuple_delete(Tuple * self, Bool * call_free);
Tuple * Tuple_clone(Tuple * self);
U64 * Tuple_size(void);
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
Vec * tokenize(Str * src, Str * path);
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


typedef struct Tuple {
    U8 *data;
    U64 total_size;
    U64 cap;
    Vec type_names;
    Vec type_sizes;
} Tuple;


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

static I64 *_t2011;
static I64 *_t2012;
static I64 *_t2013;
static U64 *CAP_LIT;
static I64 *_t2014;
static I64 *_t2015;
static I64 *_t2016;
static U64 *CAP_VIEW;

EnumDef * EnumDef_clone(EnumDef * self) {
    (void)self;
    EnumDef *_t0 = malloc(sizeof(EnumDef));
    (void)_t0;
    return _t0;
}

void EnumDef_delete(EnumDef * self, Bool * call_free) {
    (void)self;
    (void)call_free;
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
    (void)val;
    I64 _t2 = U8_to_i64(DEREF(val));
    (void)_t2;
    Str *_t3 = I64_to_str(&(I64){_t2});
    (void)_t3;
    ;
    return _t3;
}

static U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t5 = 0;
    (void)_t5;
    I64 _t6 = 1;
    (void)_t6;
    I64 _t7 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t7;
    I64 _t8 = I64_sub(_t5, _t6);
    (void)_t8;
    ;
    ;
    Bool _t9 = I64_eq(_t7, _t8);
    (void)_t9;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t9; return _r; }
}

static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t10 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t10;
    I64 _t11 = 1;
    (void)_t11;
    Bool _t12 = I64_eq(_t10, _t11);
    (void)_t12;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t12; return _r; }
}

static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t13 = U8_eq(DEREF(a), DEREF(b));
    (void)_t13;
    Bool _t14 = Bool_not(_t13);
    (void)_t14;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t14; return _r; }
}

static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t15; { Bool *_hp = (Bool *)U8_gt(a, b); _t15 = *_hp; free(_hp); }
    (void)_t15;
    Bool _t16 = Bool_not(_t15);
    (void)_t16;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t16; return _r; }
}

static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t17; { Bool *_hp = (Bool *)U8_lt(a, b); _t17 = *_hp; free(_hp); }
    (void)_t17;
    Bool _t18 = Bool_not(_t17);
    (void)_t18;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t18; return _r; }
}

static __attribute__((unused)) Str * I16_to_str(I16 * val) {
    (void)val;
    I64 _t19 = I16_to_i64(DEREF(val));
    (void)_t19;
    Str *_t20 = I64_to_str(&(I64){_t19});
    (void)_t20;
    ;
    return _t20;
}

static __attribute__((unused)) I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t21 = 0;
    (void)_t21;
    I64 _t22 = I16_to_i64(DEREF(a));
    (void)_t22;
    I64 _t23 = I64_sub(_t21, _t22);
    (void)_t23;
    ;
    ;
    I16 _t24 = I64_to_i16(_t23);
    (void)_t24;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t24; return _r; }
}

static __attribute__((unused)) I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t29 = I16_to_i64(DEREF(a));
    (void)_t29;
    I64 _t30 = 0;
    (void)_t30;
    Bool _t31; { Bool *_hp = (Bool *)I64_lt(&(I64){_t29}, &(I64){_t30}); _t31 = *_hp; free(_hp); }
    (void)_t31;
    ;
    ;
    if (_t31) {
        I64 _t25 = 0;
        (void)_t25;
        I64 _t26 = I16_to_i64(DEREF(a));
        (void)_t26;
        I64 _t27 = I64_sub(_t25, _t26);
        (void)_t27;
        ;
        ;
        I16 _t28 = I64_to_i16(_t27);
        (void)_t28;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t28; return _r; }
    }
    ;
    I16 _t32 = I16_clone(a);
    (void)_t32;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t32; return _r; }
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t34 = 0;
    (void)_t34;
    I64 _t35 = 1;
    (void)_t35;
    I64 _t36 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t36;
    I64 _t37 = I64_sub(_t34, _t35);
    (void)_t37;
    ;
    ;
    Bool _t38 = I64_eq(_t36, _t37);
    (void)_t38;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t38; return _r; }
}

static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t39 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t39;
    I64 _t40 = 1;
    (void)_t40;
    Bool _t41 = I64_eq(_t39, _t40);
    (void)_t41;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t41; return _r; }
}

static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t42 = I16_eq(DEREF(a), DEREF(b));
    (void)_t42;
    Bool _t43 = Bool_not(_t42);
    (void)_t43;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t43; return _r; }
}

static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t44; { Bool *_hp = (Bool *)I16_gt(a, b); _t44 = *_hp; free(_hp); }
    (void)_t44;
    Bool _t45 = Bool_not(_t44);
    (void)_t45;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t45; return _r; }
}

static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t46; { Bool *_hp = (Bool *)I16_lt(a, b); _t46 = *_hp; free(_hp); }
    (void)_t46;
    Bool _t47 = Bool_not(_t46);
    (void)_t47;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t47; return _r; }
}

static __attribute__((unused)) Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t48 = I32_to_i64(DEREF(val));
    (void)_t48;
    Str *_t49 = I64_to_str(&(I64){_t48});
    (void)_t49;
    ;
    return _t49;
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    (void)a;
    I64 _t50 = 0;
    (void)_t50;
    I64 _t51 = I32_to_i64(DEREF(a));
    (void)_t51;
    I64 _t52 = I64_sub(_t50, _t51);
    (void)_t52;
    ;
    ;
    I32 _t53 = I64_to_i32(_t52);
    (void)_t53;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t53; return _r; }
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    (void)a;
    I64 _t58 = I32_to_i64(DEREF(a));
    (void)_t58;
    I64 _t59 = 0;
    (void)_t59;
    Bool _t60; { Bool *_hp = (Bool *)I64_lt(&(I64){_t58}, &(I64){_t59}); _t60 = *_hp; free(_hp); }
    (void)_t60;
    ;
    ;
    if (_t60) {
        I64 _t54 = 0;
        (void)_t54;
        I64 _t55 = I32_to_i64(DEREF(a));
        (void)_t55;
        I64 _t56 = I64_sub(_t54, _t55);
        (void)_t56;
        ;
        ;
        I32 _t57 = I64_to_i32(_t56);
        (void)_t57;
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t57; return _r; }
    }
    ;
    I32 _t61 = I32_clone(a);
    (void)_t61;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t61; return _r; }
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t63 = 0;
    (void)_t63;
    I64 _t64 = 1;
    (void)_t64;
    I64 _t65 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t65;
    I64 _t66 = I64_sub(_t63, _t64);
    (void)_t66;
    ;
    ;
    Bool _t67 = I64_eq(_t65, _t66);
    (void)_t67;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t67; return _r; }
}

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t68 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t68;
    I64 _t69 = 1;
    (void)_t69;
    Bool _t70 = I64_eq(_t68, _t69);
    (void)_t70;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t70; return _r; }
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t71 = I32_eq(DEREF(a), DEREF(b));
    (void)_t71;
    Bool _t72 = Bool_not(_t71);
    (void)_t72;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t72; return _r; }
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t73; { Bool *_hp = (Bool *)I32_gt(a, b); _t73 = *_hp; free(_hp); }
    (void)_t73;
    Bool _t74 = Bool_not(_t73);
    (void)_t74;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t74; return _r; }
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t75; { Bool *_hp = (Bool *)I32_lt(a, b); _t75 = *_hp; free(_hp); }
    (void)_t75;
    Bool _t76 = Bool_not(_t75);
    (void)_t76;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t76; return _r; }
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func F32_from_i64_ext */
    F32 _t77 = F32_from_i64_ext(val);
    (void)_t77;
    { F32 *_r = malloc(sizeof(F32)); *_r = _t77; return _r; }
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t79 = 0;
    (void)_t79;
    I64 _t80 = 1;
    (void)_t80;
    I64 _t81 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t81;
    I64 _t82 = I64_sub(_t79, _t80);
    (void)_t82;
    ;
    ;
    Bool _t83 = I64_eq(_t81, _t82);
    (void)_t83;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t83; return _r; }
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t84 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t84;
    I64 _t85 = 1;
    (void)_t85;
    Bool _t86 = I64_eq(_t84, _t85);
    (void)_t86;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t86; return _r; }
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t87 = F32_eq(DEREF(a), DEREF(b));
    (void)_t87;
    Bool _t88 = Bool_not(_t87);
    (void)_t88;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t88; return _r; }
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t89; { Bool *_hp = (Bool *)F32_gt(a, b); _t89 = *_hp; free(_hp); }
    (void)_t89;
    Bool _t90 = Bool_not(_t89);
    (void)_t90;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t90; return _r; }
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t91; { Bool *_hp = (Bool *)F32_lt(a, b); _t91 = *_hp; free(_hp); }
    (void)_t91;
    Bool _t92 = Bool_not(_t91);
    (void)_t92;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t92; return _r; }
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t93 = U32_to_i64(DEREF(val));
    (void)_t93;
    Str *_t94 = I64_to_str(&(I64){_t93});
    (void)_t94;
    ;
    return _t94;
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t96 = 0;
    (void)_t96;
    I64 _t97 = 1;
    (void)_t97;
    I64 _t98 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t98;
    I64 _t99 = I64_sub(_t96, _t97);
    (void)_t99;
    ;
    ;
    Bool _t100 = I64_eq(_t98, _t99);
    (void)_t100;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t100; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t101 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t101;
    I64 _t102 = 1;
    (void)_t102;
    Bool _t103 = I64_eq(_t101, _t102);
    (void)_t103;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t103; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t104 = U32_eq(DEREF(a), DEREF(b));
    (void)_t104;
    Bool _t105 = Bool_not(_t104);
    (void)_t105;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t105; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t106; { Bool *_hp = (Bool *)U32_gt(a, b); _t106 = *_hp; free(_hp); }
    (void)_t106;
    Bool _t107 = Bool_not(_t106);
    (void)_t107;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t107; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t108; { Bool *_hp = (Bool *)U32_lt(a, b); _t108 = *_hp; free(_hp); }
    (void)_t108;
    Bool _t109 = Bool_not(_t108);
    (void)_t109;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t109; return _r; }
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t110 = U64_to_str_ext(val);
    (void)_t110;
    return _t110;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t111 = U64_from_i64_ext(val);
    (void)_t111;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t111; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t113 = 0;
    (void)_t113;
    I64 _t114 = 1;
    (void)_t114;
    I64 _t115 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t115;
    I64 _t116 = I64_sub(_t113, _t114);
    (void)_t116;
    ;
    ;
    Bool _t117 = I64_eq(_t115, _t116);
    (void)_t117;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t117; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t118 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t118;
    I64 _t119 = 1;
    (void)_t119;
    Bool _t120 = I64_eq(_t118, _t119);
    (void)_t120;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t120; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t121 = U64_eq(DEREF(a), DEREF(b));
    (void)_t121;
    Bool _t122 = Bool_not(_t121);
    (void)_t122;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t122; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t123; { Bool *_hp = (Bool *)U64_gt(a, b); _t123 = *_hp; free(_hp); }
    (void)_t123;
    Bool _t124 = Bool_not(_t123);
    (void)_t124;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t124; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t125; { Bool *_hp = (Bool *)U64_lt(a, b); _t125 = *_hp; free(_hp); }
    (void)_t125;
    Bool _t126 = Bool_not(_t125);
    (void)_t126;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t126; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t163 = 0;
    (void)_t163;
    Bool _t164 = I64_eq(DEREF(val), _t163);
    (void)_t164;
    ;
    if (_t164) {
        U64 _t127 = 2;
        (void)_t127;
        U8 *buf = malloc(_t127);
        (void)buf;
        ;
        I64 _t128 = 48;
        (void)_t128;
        U64 _t129 = 1;
        (void)_t129;
        memcpy(buf, &(I64){_t128}, _t129);
        ;
        ;
        U64 *_t130 = malloc(sizeof(U64));
        *_t130 = 1;
        (void)_t130;
        void *_t131 = ptr_add(buf, DEREF(_t130));
        (void)_t131;
        I64 _t132 = 0;
        (void)_t132;
        U64 _t133 = 1;
        (void)_t133;
        memcpy(_t131, &(I64){_t132}, _t133);
        U64_delete(_t130, &(Bool){1});
        ;
        ;
        I64 _t134 = 1;
        (void)_t134;
        I64 _t135 = 1;
        (void)_t135;
        Str *_t136 = malloc(sizeof(Str));
        _t136->c_str = buf;
        _t136->count = _t134;
        _t136->cap = _t135;
        (void)_t136;
        ;
        ;
        ;
        return _t136;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t165 = 0;
    (void)_t165;
    Bool _t166; { Bool *_hp = (Bool *)I64_lt(val, &(I64){_t165}); _t166 = *_hp; free(_hp); }
    (void)_t166;
    ;
    if (_t166) {
        Bool _t137 = 1;
        (void)_t137;
        is_neg = _t137;
        ;
        I64 _t138 = 0;
        (void)_t138;
        I64 _t139 = I64_sub(_t138, DEREF(val));
        (void)_t139;
        ;
        v = _t139;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&(I64){v});
    (void)tmp;
    while (1) {
        I64 _t141 = 0;
        (void)_t141;
        Bool _wcond140; { Bool *_hp = (Bool *)I64_gt(&(I64){tmp}, &(I64){_t141}); _wcond140 = *_hp; free(_hp); }
        (void)_wcond140;
        ;
        if (_wcond140) {
        } else {
            ;
            break;
        }
        ;
        U64 _t142 = 1;
        (void)_t142;
        U64 _t143 = U64_add(ndigits, _t142);
        (void)_t143;
        ;
        ndigits = _t143;
        ;
        I64 _t144 = 10;
        (void)_t144;
        I64 _t145 = I64_div(tmp, _t144);
        (void)_t145;
        ;
        tmp = _t145;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    (void)total;
    ;
    if (is_neg) {
        U64 _t146 = 1;
        (void)_t146;
        U64 _t147 = U64_add(DEREF(total), _t146);
        (void)_t147;
        ;
        *total = _t147;
        ;
    }
    U64 _t167 = 1;
    (void)_t167;
    U64 _t168 = U64_add(DEREF(total), _t167);
    (void)_t168;
    ;
    U8 *buf = malloc(_t168);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t148 = 45;
        (void)_t148;
        U64 _t149 = 1;
        (void)_t149;
        memcpy(buf, &(I64){_t148}, _t149);
        ;
        ;
    }
    ;
    U64 _t169 = 1;
    (void)_t169;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t169);
    (void)i;
    ;
    while (1) {
        I64 _t151 = 0;
        (void)_t151;
        Bool _wcond150; { Bool *_hp = (Bool *)I64_gt(&(I64){v}, &(I64){_t151}); _wcond150 = *_hp; free(_hp); }
        (void)_wcond150;
        ;
        if (_wcond150) {
        } else {
            ;
            break;
        }
        ;
        I64 _t152 = 10;
        (void)_t152;
        I64 _t153 = I64_mod(v, _t152);
        (void)_t153;
        ;
        I64 _t154 = 48;
        (void)_t154;
        I64 _t155 = I64_add(_t153, _t154);
        (void)_t155;
        ;
        ;
        void *_t156 = ptr_add(buf, DEREF(i));
        (void)_t156;
        U8 _t157 = I64_to_u8(_t155);
        (void)_t157;
        ;
        U64 _t158 = 1;
        (void)_t158;
        memcpy(_t156, &(U8){_t157}, _t158);
        ;
        ;
        I64 _t159 = 10;
        (void)_t159;
        I64 _t160 = I64_div(v, _t159);
        (void)_t160;
        ;
        v = _t160;
        ;
        U64 _t161 = 1;
        (void)_t161;
        U64 _t162 = U64_sub(DEREF(i), _t161);
        (void)_t162;
        ;
        *i = _t162;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t170 = ptr_add(buf, DEREF(total));
    (void)_t170;
    I64 _t171 = 0;
    (void)_t171;
    U64 _t172 = 1;
    (void)_t172;
    memcpy(_t170, &(I64){_t171}, _t172);
    ;
    ;
    U64 _t173 = U64_clone(total);
    (void)_t173;
    U64 _t174 = U64_clone(total);
    (void)_t174;
    U64_delete(total, &(Bool){1});
    Str *_t175 = malloc(sizeof(Str));
    _t175->c_str = buf;
    _t175->count = _t173;
    _t175->cap = _t174;
    (void)_t175;
    ;
    ;
    return _t175;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t176 = 0;
    (void)_t176;
    I64 _t177 = I64_sub(_t176, DEREF(a));
    (void)_t177;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t177; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t180 = 0;
    (void)_t180;
    Bool _t181; { Bool *_hp = (Bool *)I64_lt(a, &(I64){_t180}); _t181 = *_hp; free(_hp); }
    (void)_t181;
    ;
    if (_t181) {
        I64 _t178 = 0;
        (void)_t178;
        I64 _t179 = I64_sub(_t178, DEREF(a));
        (void)_t179;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t179; return _r; }
    }
    ;
    I64 _t182 = I64_clone(a);
    (void)_t182;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t182; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t184 = 0;
    (void)_t184;
    I64 _t185 = 1;
    (void)_t185;
    I64 _t186 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t186;
    I64 _t187 = I64_sub(_t184, _t185);
    (void)_t187;
    ;
    ;
    Bool _t188 = I64_eq(_t186, _t187);
    (void)_t188;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t188; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t189 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t189;
    I64 _t190 = 1;
    (void)_t190;
    Bool _t191 = I64_eq(_t189, _t190);
    (void)_t191;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t191; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t192 = I64_eq(DEREF(a), DEREF(b));
    (void)_t192;
    Bool _t193 = Bool_not(_t192);
    (void)_t193;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t193; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t194; { Bool *_hp = (Bool *)I64_gt(a, b); _t194 = *_hp; free(_hp); }
    (void)_t194;
    Bool _t195 = Bool_not(_t194);
    (void)_t195;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t195; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t196; { Bool *_hp = (Bool *)I64_lt(a, b); _t196 = *_hp; free(_hp); }
    (void)_t196;
    Bool _t197 = Bool_not(_t196);
    (void)_t197;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t197; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    (void)start;
    (void)end;
    U64 _t198 = U64_clone(&(U64){start});
    (void)_t198;
    U64 _t199 = U64_clone(&(U64){end});
    (void)_t199;
    Range *_t200 = malloc(sizeof(Range));
    _t200->start = _t198;
    _t200->end = _t199;
    (void)_t200;
    ;
    ;
    return _t200;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t202; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t202 = *_hp; free(_hp); }
    (void)_t202;
    if (_t202) {
        U64 _t201 = U64_sub(self->end, self->start);
        (void)_t201;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t201; return _r; }
    }
    ;
    U64 _t203 = U64_sub(self->start, self->end);
    (void)_t203;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t203; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    (void)i;
    Bool _t205; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t205 = *_hp; free(_hp); }
    (void)_t205;
    if (_t205) {
        U64 _t204 = U64_add(self->start, i);
        (void)_t204;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t204; return _r; }
    }
    ;
    U64 _t206 = U64_sub(self->start, i);
    (void)_t206;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t206; return _r; }
}

Range * Range_clone(Range * val) {
    (void)val;
    Range *_t207 = malloc(sizeof(Range));
    _t207->start = val->start;
    _t207->end = val->end;
    (void)_t207;
    return _t207;
}

void Range_delete(Range * self, Bool * call_free) {
    (void)self;
    (void)call_free;
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
    (void)b;
    if (DEREF(b)) {
        Str *_t209 = Str_lit("true", 4ULL);
        (void)_t209;
        return _t209;
    } else {
        Str *_t210 = Str_lit("false", 5ULL);
        (void)_t210;
        return _t210;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t215 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t215;
    if (_t215) {
        I64 _t211 = 0;
        (void)_t211;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t211; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t212 = 0;
        (void)_t212;
        I64 _t213 = 1;
        (void)_t213;
        I64 _t214 = I64_sub(_t212, _t213);
        (void)_t214;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t214; return _r; }
    }
    I64 _t216 = 1;
    (void)_t216;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t216; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t218 = 0;
    (void)_t218;
    I64 _t219 = 1;
    (void)_t219;
    I64 _t220; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t220 = *_hp; free(_hp); }
    (void)_t220;
    I64 _t221 = I64_sub(_t218, _t219);
    (void)_t221;
    ;
    ;
    Bool _t222 = I64_eq(_t220, _t221);
    (void)_t222;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t222; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t223; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t223 = *_hp; free(_hp); }
    (void)_t223;
    I64 _t224 = 1;
    (void)_t224;
    Bool _t225 = I64_eq(_t223, _t224);
    (void)_t225;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t225; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t226 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t226;
    Bool _t227 = Bool_not(_t226);
    (void)_t227;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t227; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t228; { Bool *_hp = (Bool *)Bool_gt(a, b); _t228 = *_hp; free(_hp); }
    (void)_t228;
    Bool _t229 = Bool_not(_t228);
    (void)_t229;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t229; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t230; { Bool *_hp = (Bool *)Bool_lt(a, b); _t230 = *_hp; free(_hp); }
    (void)_t230;
    Bool _t231 = Bool_not(_t230);
    (void)_t231;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t231; return _r; }
}

void println(Array * parts) {
    (void)parts;
    {
        U64 *_fi232 = malloc(sizeof(U64));
        *_fi232 = 0;
        (void)_fi232;
        while (1) {
            U64 _t234; { U64 *_hp = (U64 *)Array_len(parts); _t234 = *_hp; free(_hp); }
            (void)_t234;
            Bool _wcond233; { Bool *_hp = (Bool *)U64_lt(_fi232, &(U64){_t234}); _wcond233 = *_hp; free(_hp); }
            (void)_wcond233;
            ;
            if (_wcond233) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi232);
            (void)s;
            U64 _t235 = 1;
            (void)_t235;
            U64 _t236 = U64_add(DEREF(_fi232), _t235);
            (void)_t236;
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
    (void)parts;
    {
        U64 *_fi237 = malloc(sizeof(U64));
        *_fi237 = 0;
        (void)_fi237;
        while (1) {
            U64 _t239; { U64 *_hp = (U64 *)Array_len(parts); _t239 = *_hp; free(_hp); }
            (void)_t239;
            Bool _wcond238; { Bool *_hp = (Bool *)U64_lt(_fi237, &(U64){_t239}); _wcond238 = *_hp; free(_hp); }
            (void)_wcond238;
            ;
            if (_wcond238) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi237);
            (void)s;
            U64 _t240 = 1;
            (void)_t240;
            U64 _t241 = U64_add(DEREF(_fi237), _t240);
            (void)_t241;
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
    (void)parts;
    U64 total = 0;
    (void)total;
    {
        U64 *_fi242 = malloc(sizeof(U64));
        *_fi242 = 0;
        (void)_fi242;
        while (1) {
            U64 _t244; { U64 *_hp = (U64 *)Array_len(parts); _t244 = *_hp; free(_hp); }
            (void)_t244;
            Bool _wcond243; { Bool *_hp = (Bool *)U64_lt(_fi242, &(U64){_t244}); _wcond243 = *_hp; free(_hp); }
            (void)_wcond243;
            ;
            if (_wcond243) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi242);
            (void)s;
            U64 _t245 = 1;
            (void)_t245;
            U64 _t246 = U64_add(DEREF(_fi242), _t245);
            (void)_t246;
            ;
            *_fi242 = _t246;
            ;
            U64 _t247; { U64 *_hp = (U64 *)Str_len(s); _t247 = *_hp; free(_hp); }
            (void)_t247;
            U64 _t248 = U64_add(total, _t247);
            (void)_t248;
            ;
            total = _t248;
            ;
        }
        U64_delete(_fi242, &(Bool){1});
    }
    U8 *buf = malloc(total);
    (void)buf;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 *_fi249 = malloc(sizeof(U64));
        *_fi249 = 0;
        (void)_fi249;
        while (1) {
            U64 _t251; { U64 *_hp = (U64 *)Array_len(parts); _t251 = *_hp; free(_hp); }
            (void)_t251;
            Bool _wcond250; { Bool *_hp = (Bool *)U64_lt(_fi249, &(U64){_t251}); _wcond250 = *_hp; free(_hp); }
            (void)_wcond250;
            ;
            if (_wcond250) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi249);
            (void)s;
            U64 _t252 = 1;
            (void)_t252;
            U64 _t253 = U64_add(DEREF(_fi249), _t252);
            (void)_t253;
            ;
            *_fi249 = _t253;
            ;
            void *_t254 = ptr_add(buf, DEREF(offset));
            (void)_t254;
            U64 _t255; { U64 *_hp = (U64 *)Str_len(s); _t255 = *_hp; free(_hp); }
            (void)_t255;
            memcpy(_t254, s->c_str, _t255);
            ;
            U64 _t256; { U64 *_hp = (U64 *)Str_len(s); _t256 = *_hp; free(_hp); }
            (void)_t256;
            U64 _t257 = U64_add(DEREF(offset), _t256);
            (void)_t257;
            ;
            *offset = _t257;
            ;
        }
        U64_delete(_fi249, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t258 = U64_clone(&(U64){total});
    (void)_t258;
    U64 _t259 = U64_clone(&(U64){total});
    (void)_t259;
    ;
    Str *_t260 = malloc(sizeof(Str));
    _t260->c_str = buf;
    _t260->count = _t258;
    _t260->cap = _t259;
    (void)_t260;
    ;
    ;
    return _t260;
}

I64 * wait_cmd(I64 * pid) {
    (void)pid;
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        (void)status;
        I64 _t261 = 0;
        (void)_t261;
        I64 _t262 = 1;
        (void)_t262;
        I64 _t263 = I64_sub(_t261, _t262);
        (void)_t263;
        ;
        ;
        Bool _t264; { Bool *_hp = (Bool *)I64_neq(&(I64){status}, &(I64){_t263}); _t264 = *_hp; free(_hp); }
        (void)_t264;
        ;
        if (_t264) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t265 = 50;
        (void)_t265;
        sleep_ms(_t265);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    (void)output;
    (void)args;
    Str *cmd = Str_lit("", 0ULL);
    (void)cmd;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        U64 _t271; { U64 *_hp = (U64 *)Array_len(args); _t271 = *_hp; free(_hp); }
        (void)_t271;
        Bool _wcond266; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t271}); _wcond266 = *_hp; free(_hp); }
        (void)_wcond266;
        ;
        if (_wcond266) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        (void)arg;
        U64 _t272 = 0;
        (void)_t272;
        Bool _t273; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t272}); _t273 = *_hp; free(_hp); }
        (void)_t273;
        ;
        if (_t273) {
            Str *_t267 = Str_lit(" '", 2ULL);
            (void)_t267;
            Str *_t268 = Str_concat(cmd, _t267);
            (void)_t268;
            Str_delete(_t267, &(Bool){1});
            Str *_t269 = Str_concat(_t268, arg);
            (void)_t269;
            Str_delete(_t268, &(Bool){1});
            Str *_t270 = Str_lit("'", 1ULL);
            (void)_t270;
            cmd = Str_concat(_t269, _t270);
            Str_delete(_t269, &(Bool){1});
            Str_delete(_t270, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t274 = 1;
        (void)_t274;
        U64 _t275 = U64_add(DEREF(i), _t274);
        (void)_t275;
        ;
        *i = _t275;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    (void)tmpf;
    Str *_t276 = Str_lit(" > ", 3ULL);
    (void)_t276;
    Str *_t277 = Str_concat(cmd, _t276);
    (void)_t277;
    Str_delete(_t276, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t278 = Str_concat(_t277, tmpf);
    (void)_t278;
    Str_delete(_t277, &(Bool){1});
    Str *_t279 = Str_lit(" 2>&1", 5ULL);
    (void)_t279;
    Str *_t280 = Str_concat(_t278, _t279);
    (void)_t280;
    Str_delete(_t278, &(Bool){1});
    Str_delete(_t279, &(Bool){1});
    I64 pid; { I64 *_hp = (I64 *)spawn_cmd(_t280); pid = *_hp; free(_hp); }
    (void)pid;
    Str_delete(_t280, &(Bool){1});
    I64 ec; { I64 *_hp = (I64 *)wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    (void)ec;
    ;
    Str *content = readfile(tmpf);
    (void)content;
    Str_delete(tmpf, &(Bool){1});
    U64 _t281; { U64 *_hp = (U64 *)Str_size(); _t281 = *_hp; free(_hp); }
    (void)_t281;
    memcpy(output, content, _t281);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t282 = Str_lit("Str", 3ULL);
    (void)_t282;
    U64 _t283; { U64 *_hp = (U64 *)Str_size(); _t283 = *_hp; free(_hp); }
    (void)_t283;
    U64 _t284 = 3;
    (void)_t284;
    Array *_va0 = Array_new(_t282, &(U64){_t283}, &(U64){_t284});
    (void)_va0;
    Str_delete(_t282, &(Bool){1});
    ;
    ;
    U64 _t285 = 0;
    (void)_t285;
    Str *_t286 = Str_clone(loc_str);
    (void)_t286;
    Array_set(_va0, &(U64){_t285}, _t286);
    ;
    U64 _t287 = 1;
    (void)_t287;
    Str *_t288 = Str_lit(": panic: ", 9ULL);
    (void)_t288;
    Array_set(_va0, &(U64){_t287}, _t288);
    ;
    U64 _t289 = 2;
    (void)_t289;
    Str *_t290 = format(parts);
    (void)_t290;
    Array_set(_va0, &(U64){_t289}, _t290);
    ;
    println(_va0);
    I64 _t291 = 1;
    (void)_t291;
    exit(_t291);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t292 = Str_lit("Str", 3ULL);
    (void)_t292;
    U64 _t293; { U64 *_hp = (U64 *)Str_size(); _t293 = *_hp; free(_hp); }
    (void)_t293;
    U64 _t294 = 2;
    (void)_t294;
    Array *_va1 = Array_new(_t292, &(U64){_t293}, &(U64){_t294});
    (void)_va1;
    Str_delete(_t292, &(Bool){1});
    ;
    ;
    U64 _t295 = 0;
    (void)_t295;
    Str *_t296 = Str_lit("TODO: ", 6ULL);
    (void)_t296;
    Array_set(_va1, &(U64){_t295}, _t296);
    ;
    U64 _t297 = 1;
    (void)_t297;
    Str *_t298 = format(parts);
    (void)_t298;
    Array_set(_va1, &(U64){_t297}, _t298);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    (void)loc_str;
    Str *_t299 = Str_lit("Str", 3ULL);
    (void)_t299;
    U64 _t300; { U64 *_hp = (U64 *)Str_size(); _t300 = *_hp; free(_hp); }
    (void)_t300;
    U64 _t301 = 1;
    (void)_t301;
    Array *_va2 = Array_new(_t299, &(U64){_t300}, &(U64){_t301});
    (void)_va2;
    Str_delete(_t299, &(Bool){1});
    ;
    ;
    U64 _t302 = 0;
    (void)_t302;
    Str *_t303 = Str_lit("unreachable", 11ULL);
    (void)_t303;
    Array_set(_va2, &(U64){_t302}, _t303);
    ;
    panic(loc_str, _va2);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Bool _t311 = Bool_not(DEREF(cond));
    (void)_t311;
    if (_t311) {
        Str *_t304 = Str_lit("Str", 3ULL);
        (void)_t304;
        U64 _t305; { U64 *_hp = (U64 *)Str_size(); _t305 = *_hp; free(_hp); }
        (void)_t305;
        U64 _t306 = 2;
        (void)_t306;
        Array *_va3 = Array_new(_t304, &(U64){_t305}, &(U64){_t306});
        (void)_va3;
        Str_delete(_t304, &(Bool){1});
        ;
        ;
        U64 _t307 = 0;
        (void)_t307;
        Str *_t308 = Str_lit("assert failed: ", 15ULL);
        (void)_t308;
        Array_set(_va3, &(U64){_t307}, _t308);
        ;
        U64 _t309 = 1;
        (void)_t309;
        Str *_t310 = format(parts);
        (void)_t310;
        Array_set(_va3, &(U64){_t309}, _t310);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t312 = 1;
    (void)_t312;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t312; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Str *_t313 = Str_lit("Str", 3ULL);
    (void)_t313;
    U64 _t314; { U64 *_hp = (U64 *)Str_size(); _t314 = *_hp; free(_hp); }
    (void)_t314;
    U64 _t315 = 0;
    (void)_t315;
    Array *_va4 = Array_new(_t313, &(U64){_t314}, &(U64){_t315});
    (void)_va4;
    Str_delete(_t313, &(Bool){1});
    ;
    ;
    Bool _t316; { Bool *_hp = (Bool *)assertm(loc_str, cond, _va4); _t316 = *_hp; free(_hp); }
    (void)_t316;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t316; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Array *_t317 = Array_clone(parts);
    (void)_t317;
    Array_delete(parts, &(Bool){1});
    Bool _t318; { Bool *_hp = (Bool *)assertm(loc_str, cond, _t317); _t318 = *_hp; free(_hp); }
    (void)_t318;
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t332; { Bool *_hp = (Bool *)I64_neq(a, b); _t332 = *_hp; free(_hp); }
    (void)_t332;
    if (_t332) {
        Str *_t319 = Str_lit("Str", 3ULL);
        (void)_t319;
        U64 _t320; { U64 *_hp = (U64 *)Str_size(); _t320 = *_hp; free(_hp); }
        (void)_t320;
        U64 _t321 = 5;
        (void)_t321;
        Array *_va5 = Array_new(_t319, &(U64){_t320}, &(U64){_t321});
        (void)_va5;
        Str_delete(_t319, &(Bool){1});
        ;
        ;
        U64 _t322 = 0;
        (void)_t322;
        Str *_t323 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t323;
        Array_set(_va5, &(U64){_t322}, _t323);
        ;
        U64 _t324 = 1;
        (void)_t324;
        Str *_t325 = I64_to_str(a);
        (void)_t325;
        Array_set(_va5, &(U64){_t324}, _t325);
        ;
        U64 _t326 = 2;
        (void)_t326;
        Str *_t327 = Str_lit("', found '", 10ULL);
        (void)_t327;
        Array_set(_va5, &(U64){_t326}, _t327);
        ;
        U64 _t328 = 3;
        (void)_t328;
        Str *_t329 = I64_to_str(b);
        (void)_t329;
        Array_set(_va5, &(U64){_t328}, _t329);
        ;
        U64 _t330 = 4;
        (void)_t330;
        Str *_t331 = Str_lit("'", 1ULL);
        (void)_t331;
        Array_set(_va5, &(U64){_t330}, _t331);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t346; { Bool *_hp = (Bool *)Str_eq(a, b); _t346 = *_hp; free(_hp); }
    (void)_t346;
    Bool _t347 = Bool_not(_t346);
    (void)_t347;
    ;
    if (_t347) {
        Str *_t333 = Str_lit("Str", 3ULL);
        (void)_t333;
        U64 _t334; { U64 *_hp = (U64 *)Str_size(); _t334 = *_hp; free(_hp); }
        (void)_t334;
        U64 _t335 = 5;
        (void)_t335;
        Array *_va6 = Array_new(_t333, &(U64){_t334}, &(U64){_t335});
        (void)_va6;
        Str_delete(_t333, &(Bool){1});
        ;
        ;
        U64 _t336 = 0;
        (void)_t336;
        Str *_t337 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t337;
        Array_set(_va6, &(U64){_t336}, _t337);
        ;
        U64 _t338 = 1;
        (void)_t338;
        Str *_t339 = Str_clone(a);
        (void)_t339;
        Array_set(_va6, &(U64){_t338}, _t339);
        ;
        U64 _t340 = 2;
        (void)_t340;
        Str *_t341 = Str_lit("', found '", 10ULL);
        (void)_t341;
        Array_set(_va6, &(U64){_t340}, _t341);
        ;
        U64 _t342 = 3;
        (void)_t342;
        Str *_t343 = Str_clone(b);
        (void)_t343;
        Array_set(_va6, &(U64){_t342}, _t343);
        ;
        U64 _t344 = 4;
        (void)_t344;
        Str *_t345 = Str_lit("'", 1ULL);
        (void)_t345;
        Array_set(_va6, &(U64){_t344}, _t345);
        ;
        panic(loc_str, _va6);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    void *_t348 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t348;
    U64 _t349 = U64_clone(cap);
    (void)_t349;
    U64 _t350 = U64_clone(elem_size);
    (void)_t350;
    Array *_t351 = malloc(sizeof(Array));
    _t351->data = _t348;
    _t351->cap = _t349;
    _t351->elem_size = _t350;
    { Str *_ca = Str_clone(elem_type); _t351->elem_type = *_ca; free(_ca); }
    (void)_t351;
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
    (void)i;
    Bool _t366; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t366 = *_hp; free(_hp); }
    (void)_t366;
    if (_t366) {
        Str *_t352 = Str_lit("Str", 3ULL);
        (void)_t352;
        U64 _t353; { U64 *_hp = (U64 *)Str_size(); _t353 = *_hp; free(_hp); }
        (void)_t353;
        U64 _t354 = 5;
        (void)_t354;
        Array *_va7 = Array_new(_t352, &(U64){_t353}, &(U64){_t354});
        (void)_va7;
        Str_delete(_t352, &(Bool){1});
        ;
        ;
        U64 _t355 = 0;
        (void)_t355;
        Str *_t356 = Str_lit("Array.get: index ", 17ULL);
        (void)_t356;
        Array_set(_va7, &(U64){_t355}, _t356);
        ;
        U64 _t357 = 1;
        (void)_t357;
        Str *_t358 = U64_to_str(DEREF(i));
        (void)_t358;
        Array_set(_va7, &(U64){_t357}, _t358);
        ;
        U64 _t359 = 2;
        (void)_t359;
        Str *_t360 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t360;
        Array_set(_va7, &(U64){_t359}, _t360);
        ;
        U64 _t361 = 3;
        (void)_t361;
        Str *_t362 = U64_to_str(self->cap);
        (void)_t362;
        Array_set(_va7, &(U64){_t361}, _t362);
        ;
        U64 _t363 = 4;
        (void)_t363;
        Str *_t364 = Str_lit(")", 1ULL);
        (void)_t364;
        Array_set(_va7, &(U64){_t363}, _t364);
        ;
        Str *_t365 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:19:19", 62ULL);
        (void)_t365;
        panic(_t365, _va7);
        Str_delete(_t365, &(Bool){1});
    }
    ;
    U64 *_t367 = malloc(sizeof(U64)); *_t367 = U64_mul(DEREF(i), self->elem_size);
    (void)_t367;
    void *_t368 = ptr_add(self->data, DEREF(_t367));
    (void)_t368;
    U64_delete(_t367, &(Bool){1});
    return _t368;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t383; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t383 = *_hp; free(_hp); }
    (void)_t383;
    if (_t383) {
        Str *_t369 = Str_lit("Str", 3ULL);
        (void)_t369;
        U64 _t370; { U64 *_hp = (U64 *)Str_size(); _t370 = *_hp; free(_hp); }
        (void)_t370;
        U64 _t371 = 5;
        (void)_t371;
        Array *_va8 = Array_new(_t369, &(U64){_t370}, &(U64){_t371});
        (void)_va8;
        Str_delete(_t369, &(Bool){1});
        ;
        ;
        U64 _t372 = 0;
        (void)_t372;
        Str *_t373 = Str_lit("Array.set: index ", 17ULL);
        (void)_t373;
        Array_set(_va8, &(U64){_t372}, _t373);
        ;
        U64 _t374 = 1;
        (void)_t374;
        Str *_t375 = U64_to_str(DEREF(i));
        (void)_t375;
        Array_set(_va8, &(U64){_t374}, _t375);
        ;
        U64 _t376 = 2;
        (void)_t376;
        Str *_t377 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t377;
        Array_set(_va8, &(U64){_t376}, _t377);
        ;
        U64 _t378 = 3;
        (void)_t378;
        Str *_t379 = U64_to_str(self->cap);
        (void)_t379;
        Array_set(_va8, &(U64){_t378}, _t379);
        ;
        U64 _t380 = 4;
        (void)_t380;
        Str *_t381 = Str_lit(")", 1ULL);
        (void)_t381;
        Array_set(_va8, &(U64){_t380}, _t381);
        ;
        Str *_t382 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:27:19", 62ULL);
        (void)_t382;
        panic(_t382, _va8);
        Str_delete(_t382, &(Bool){1});
    }
    ;
    U64 *_t384 = malloc(sizeof(U64)); *_t384 = U64_mul(DEREF(i), self->elem_size);
    (void)_t384;
    void *_t385 = ptr_add(self->data, DEREF(_t384));
    (void)_t385;
    Bool _t386 = 0;
    (void)_t386;
    dyn_call_delete(&self->elem_type, _t385, &(Bool){_t386});
    U64_delete(_t384, &(Bool){1});
    ;
    U64 *_t387 = malloc(sizeof(U64)); *_t387 = U64_mul(DEREF(i), self->elem_size);
    (void)_t387;
    void *_t388 = ptr_add(self->data, DEREF(_t387));
    (void)_t388;
    memcpy(_t388, val, self->elem_size);
    U64_delete(_t387, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U64 _fi389 = 0;
        (void)_fi389;
        while (1) {
            U64 _t391 = 0;
            (void)_t391;
            Range *_t392 = Range_new(_t391, self->cap);
            (void)_t392;
            ;
            U64 _t393; { U64 *_hp = (U64 *)Range_len(_t392); _t393 = *_hp; free(_hp); }
            (void)_t393;
            Range_delete(_t392, &(Bool){1});
            Bool _wcond390; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi389}, &(U64){_t393}); _wcond390 = *_hp; free(_hp); }
            (void)_wcond390;
            ;
            if (_wcond390) {
            } else {
                ;
                break;
            }
            ;
            U64 _t394 = 0;
            (void)_t394;
            Range *_t395 = Range_new(_t394, self->cap);
            (void)_t395;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t395, _fi389); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t395, &(Bool){1});
            U64 _t396 = 1;
            (void)_t396;
            U64 _t397 = U64_add(_fi389, _t396);
            (void)_t397;
            ;
            _fi389 = _t397;
            ;
            U64 *_t398 = malloc(sizeof(U64)); *_t398 = U64_mul(i, self->elem_size);
            (void)_t398;
            ;
            void *_t399 = ptr_add(self->data, DEREF(_t398));
            (void)_t399;
            Bool _t400 = 0;
            (void)_t400;
            dyn_call_delete(&self->elem_type, _t399, &(Bool){_t400});
            U64_delete(_t398, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t401 = 0;
    (void)_t401;
    Str_delete(&self->elem_type, &(Bool){_t401});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t415 = U64_mul(self->cap, self->elem_size);
    (void)_t415;
    U8 *new_data = malloc(_t415);
    (void)new_data;
    ;
    {
        U64 _fi402 = 0;
        (void)_fi402;
        while (1) {
            U64 _t404 = 0;
            (void)_t404;
            Range *_t405 = Range_new(_t404, self->cap);
            (void)_t405;
            ;
            U64 _t406; { U64 *_hp = (U64 *)Range_len(_t405); _t406 = *_hp; free(_hp); }
            (void)_t406;
            Range_delete(_t405, &(Bool){1});
            Bool _wcond403; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi402}, &(U64){_t406}); _wcond403 = *_hp; free(_hp); }
            (void)_wcond403;
            ;
            if (_wcond403) {
            } else {
                ;
                break;
            }
            ;
            U64 _t407 = 0;
            (void)_t407;
            Range *_t408 = Range_new(_t407, self->cap);
            (void)_t408;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t408, _fi402); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t408, &(Bool){1});
            U64 _t409 = 1;
            (void)_t409;
            U64 _t410 = U64_add(_fi402, _t409);
            (void)_t410;
            ;
            _fi402 = _t410;
            ;
            U64 *_t411 = malloc(sizeof(U64)); *_t411 = U64_mul(i, self->elem_size);
            (void)_t411;
            void *_t412 = ptr_add(self->data, DEREF(_t411));
            (void)_t412;
            void *cloned = dyn_call_clone(&self->elem_type, _t412);
            (void)cloned;
            U64_delete(_t411, &(Bool){1});
            U64 *_t413 = malloc(sizeof(U64)); *_t413 = U64_mul(i, self->elem_size);
            (void)_t413;
            ;
            void *_t414 = ptr_add(new_data, DEREF(_t413));
            (void)_t414;
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
    (void)_t416;
    return _t416;
}

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    (void)key_type;
    (void)key_size;
    (void)val_type;
    (void)val_size;
    Bool _t430; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t430 = *_hp; free(_hp); }
    (void)_t430;
    Bool _t431 = Bool_not(_t430);
    (void)_t431;
    ;
    if (_t431) {
        Bool _t428 = dyn_has_cmp(key_type);
        (void)_t428;
        Bool _t429 = Bool_not(_t428);
        (void)_t429;
        ;
        if (_t429) {
            Str *_t418 = Str_lit("Str", 3ULL);
            (void)_t418;
            U64 _t419; { U64 *_hp = (U64 *)Str_size(); _t419 = *_hp; free(_hp); }
            (void)_t419;
            U64 _t420 = 3;
            (void)_t420;
            Array *_va9 = Array_new(_t418, &(U64){_t419}, &(U64){_t420});
            (void)_va9;
            Str_delete(_t418, &(Bool){1});
            ;
            ;
            U64 _t421 = 0;
            (void)_t421;
            Str *_t422 = Str_lit("Map.new: type ", 14ULL);
            (void)_t422;
            Array_set(_va9, &(U64){_t421}, _t422);
            ;
            U64 _t423 = 1;
            (void)_t423;
            Str *_t424 = Str_clone(key_type);
            (void)_t424;
            Array_set(_va9, &(U64){_t423}, _t424);
            ;
            U64 _t425 = 2;
            (void)_t425;
            Str *_t426 = Str_lit(" must implement cmp", 19ULL);
            (void)_t426;
            Array_set(_va9, &(U64){_t425}, _t426);
            ;
            Str *_t427 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
            (void)_t427;
            panic(_t427, _va9);
            Str_delete(_t427, &(Bool){1});
        }
        ;
    }
    ;
    void *_t432 = malloc(DEREF(key_size));
    (void)_t432;
    void *_t433 = malloc(DEREF(val_size));
    (void)_t433;
    U64 _t434 = 0;
    (void)_t434;
    I64 _t435 = 1;
    (void)_t435;
    U64 _t436 = U64_clone(key_size);
    (void)_t436;
    U64 _t437 = U64_clone(val_size);
    (void)_t437;
    Map *_t438 = malloc(sizeof(Map));
    _t438->key_data = _t432;
    _t438->val_data = _t433;
    _t438->count = _t434;
    _t438->cap = _t435;
    _t438->key_size = _t436;
    { Str *_ca = Str_clone(key_type); _t438->key_type = *_ca; free(_ca); }
    _t438->val_size = _t437;
    { Str *_ca = Str_clone(val_type); _t438->val_type = *_ca; free(_ca); }
    (void)_t438;
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
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond439; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond439 = *_hp; free(_hp); }
        (void)_wcond439;
        if (_wcond439) {
        } else {
            ;
            break;
        }
        ;
        U64 _t446 = U64_sub(hi, lo);
        (void)_t446;
        U64 _t447 = 2;
        (void)_t447;
        U64 _t448 = U64_div(_t446, _t447);
        (void)_t448;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t448);
        (void)mid;
        ;
        U64 *_t449 = malloc(sizeof(U64)); *_t449 = U64_mul(DEREF(mid), self->key_size);
        (void)_t449;
        void *_t450 = ptr_add(self->key_data, DEREF(_t449));
        (void)_t450;
        I64 *c = dyn_call_cmp(&self->key_type, _t450, key);
        (void)c;
        U64_delete(_t449, &(Bool){1});
        I64 _t451 = 0;
        (void)_t451;
        Bool _t452; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t451}); _t452 = *_hp; free(_hp); }
        (void)_t452;
        ;
        if (_t452) {
            U64 _t440 = 1;
            (void)_t440;
            U64 _t441 = U64_add(DEREF(mid), _t440);
            (void)_t441;
            ;
            lo = _t441;
            ;
        } else {
            I64 _t444 = 0;
            (void)_t444;
            Bool _t445; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t444}); _t445 = *_hp; free(_hp); }
            (void)_t445;
            ;
            if (_t445) {
                U64 _t442 = U64_clone(mid);
                (void)_t442;
                hi = _t442;
                ;
            } else {
                Bool _t443 = 1;
                (void)_t443;
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
    (void)_t453;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t453; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond454; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond454 = *_hp; free(_hp); }
        (void)_wcond454;
        if (_wcond454) {
        } else {
            ;
            break;
        }
        ;
        U64 _t462 = U64_sub(hi, lo);
        (void)_t462;
        U64 _t463 = 2;
        (void)_t463;
        U64 _t464 = U64_div(_t462, _t463);
        (void)_t464;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t464);
        (void)mid;
        ;
        U64 *_t465 = malloc(sizeof(U64)); *_t465 = U64_mul(DEREF(mid), self->key_size);
        (void)_t465;
        void *_t466 = ptr_add(self->key_data, DEREF(_t465));
        (void)_t466;
        I64 *c = dyn_call_cmp(&self->key_type, _t466, key);
        (void)c;
        U64_delete(_t465, &(Bool){1});
        I64 _t467 = 0;
        (void)_t467;
        Bool _t468; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t467}); _t468 = *_hp; free(_hp); }
        (void)_t468;
        ;
        if (_t468) {
            U64 _t455 = 1;
            (void)_t455;
            U64 _t456 = U64_add(DEREF(mid), _t455);
            (void)_t456;
            ;
            lo = _t456;
            ;
        } else {
            I64 _t460 = 0;
            (void)_t460;
            Bool _t461; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t460}); _t461 = *_hp; free(_hp); }
            (void)_t461;
            ;
            if (_t461) {
                U64 _t457 = U64_clone(mid);
                (void)_t457;
                hi = _t457;
                ;
            } else {
                U64 *_t458 = malloc(sizeof(U64)); *_t458 = U64_mul(DEREF(mid), self->val_size);
                (void)_t458;
                void *_t459 = ptr_add(self->val_data, DEREF(_t458));
                (void)_t459;
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
    (void)_t469;
    U64 _t470; { U64 *_hp = (U64 *)Str_size(); _t470 = *_hp; free(_hp); }
    (void)_t470;
    U64 _t471 = 1;
    (void)_t471;
    Array *_va10 = Array_new(_t469, &(U64){_t470}, &(U64){_t471});
    (void)_va10;
    Str_delete(_t469, &(Bool){1});
    ;
    ;
    U64 _t472 = 0;
    (void)_t472;
    Str *_t473 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t473;
    Array_set(_va10, &(U64){_t472}, _t473);
    ;
    Str *_t474 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
    (void)_t474;
    panic(_t474, _va10);
    Str_delete(_t474, &(Bool){1});
    U64 *_t475 = malloc(sizeof(U64));
    *_t475 = 0;
    (void)_t475;
    void *_t476 = ptr_add(self->val_data, DEREF(_t475));
    (void)_t476;
    U64_delete(_t475, &(Bool){1});
    return _t476;
}

void Map_set(Map * self, void * key, void * val) {
    (void)self;
    (void)key;
    (void)val;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    Bool found = 0;
    (void)found;
    while (1) {
        Bool _wcond477; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond477 = *_hp; free(_hp); }
        (void)_wcond477;
        if (_wcond477) {
        } else {
            ;
            break;
        }
        ;
        U64 _t486 = U64_sub(hi, lo);
        (void)_t486;
        U64 _t487 = 2;
        (void)_t487;
        U64 _t488 = U64_div(_t486, _t487);
        (void)_t488;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t488);
        (void)mid;
        ;
        U64 *_t489 = malloc(sizeof(U64)); *_t489 = U64_mul(DEREF(mid), self->key_size);
        (void)_t489;
        void *_t490 = ptr_add(self->key_data, DEREF(_t489));
        (void)_t490;
        I64 *c = dyn_call_cmp(&self->key_type, _t490, key);
        (void)c;
        U64_delete(_t489, &(Bool){1});
        I64 _t491 = 0;
        (void)_t491;
        Bool _t492; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t491}); _t492 = *_hp; free(_hp); }
        (void)_t492;
        ;
        if (_t492) {
            U64 _t478 = 1;
            (void)_t478;
            U64 _t479 = U64_add(DEREF(mid), _t478);
            (void)_t479;
            ;
            lo = _t479;
            ;
        } else {
            I64 _t484 = 0;
            (void)_t484;
            Bool _t485; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t484}); _t485 = *_hp; free(_hp); }
            (void)_t485;
            ;
            if (_t485) {
                U64 _t480 = U64_clone(mid);
                (void)_t480;
                hi = _t480;
                ;
            } else {
                Bool _t481 = 1;
                (void)_t481;
                found = _t481;
                ;
                U64 _t482 = U64_clone(mid);
                (void)_t482;
                lo = _t482;
                ;
                U64 _t483 = U64_clone(mid);
                (void)_t483;
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
        Bool _t497; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t497 = *_hp; free(_hp); }
        (void)_t497;
        Bool _t498 = Bool_not(_t497);
        (void)_t498;
        ;
        if (_t498) {
            Bool _t493 = 0;
            (void)_t493;
            dyn_call_delete(&self->key_type, key, &(Bool){_t493});
            ;
        }
        ;
        free(key);
        Bool _t499; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t499 = *_hp; free(_hp); }
        (void)_t499;
        Bool _t500 = Bool_not(_t499);
        (void)_t500;
        ;
        if (_t500) {
            U64 *_t494 = malloc(sizeof(U64)); *_t494 = U64_mul(lo, self->val_size);
            (void)_t494;
            void *_t495 = ptr_add(self->val_data, DEREF(_t494));
            (void)_t495;
            Bool _t496 = 0;
            (void)_t496;
            dyn_call_delete(&self->val_type, _t495, &(Bool){_t496});
            U64_delete(_t494, &(Bool){1});
            ;
        }
        ;
        U64 *_t501 = malloc(sizeof(U64)); *_t501 = U64_mul(lo, self->val_size);
        (void)_t501;
        void *_t502 = ptr_add(self->val_data, DEREF(_t501));
        (void)_t502;
        memcpy(_t502, val, self->val_size);
        U64_delete(_t501, &(Bool){1});
        free(val);
    } else {
        Bool _t509 = U64_eq(self->count, self->cap);
        (void)_t509;
        if (_t509) {
            U64 _t503 = 2;
            (void)_t503;
            U64 new_cap = U64_mul(self->cap, _t503);
            (void)new_cap;
            ;
            U64 _t504 = U64_mul(new_cap, self->key_size);
            (void)_t504;
            void *_t505 = realloc(self->key_data, _t504);
            (void)_t505;
            ;
            self->key_data = _t505;
            U64 _t506 = U64_mul(new_cap, self->val_size);
            (void)_t506;
            void *_t507 = realloc(self->val_data, _t506);
            (void)_t507;
            ;
            self->val_data = _t507;
            U64 _t508 = U64_clone(&(U64){new_cap});
            (void)_t508;
            ;
            self->cap = _t508;
            ;
        }
        ;
        U64 _t510 = 1;
        (void)_t510;
        U64 _t511 = U64_add(lo, _t510);
        (void)_t511;
        ;
        U64 *_t512 = malloc(sizeof(U64)); *_t512 = U64_mul(_t511, self->key_size);
        (void)_t512;
        ;
        U64 *_t513 = malloc(sizeof(U64)); *_t513 = U64_mul(lo, self->key_size);
        (void)_t513;
        U64 _t514 = U64_sub(self->count, lo);
        (void)_t514;
        void *_t515 = ptr_add(self->key_data, DEREF(_t512));
        (void)_t515;
        void *_t516 = ptr_add(self->key_data, DEREF(_t513));
        (void)_t516;
        U64 _t517 = U64_mul(_t514, self->key_size);
        (void)_t517;
        ;
        memmove(_t515, _t516, _t517);
        U64_delete(_t512, &(Bool){1});
        U64_delete(_t513, &(Bool){1});
        ;
        U64 _t518 = 1;
        (void)_t518;
        U64 _t519 = U64_add(lo, _t518);
        (void)_t519;
        ;
        U64 *_t520 = malloc(sizeof(U64)); *_t520 = U64_mul(_t519, self->val_size);
        (void)_t520;
        ;
        U64 *_t521 = malloc(sizeof(U64)); *_t521 = U64_mul(lo, self->val_size);
        (void)_t521;
        U64 _t522 = U64_sub(self->count, lo);
        (void)_t522;
        void *_t523 = ptr_add(self->val_data, DEREF(_t520));
        (void)_t523;
        void *_t524 = ptr_add(self->val_data, DEREF(_t521));
        (void)_t524;
        U64 _t525 = U64_mul(_t522, self->val_size);
        (void)_t525;
        ;
        memmove(_t523, _t524, _t525);
        U64_delete(_t520, &(Bool){1});
        U64_delete(_t521, &(Bool){1});
        ;
        U64 *_t526 = malloc(sizeof(U64)); *_t526 = U64_mul(lo, self->key_size);
        (void)_t526;
        void *_t527 = ptr_add(self->key_data, DEREF(_t526));
        (void)_t527;
        memcpy(_t527, key, self->key_size);
        U64_delete(_t526, &(Bool){1});
        U64 *_t528 = malloc(sizeof(U64)); *_t528 = U64_mul(lo, self->val_size);
        (void)_t528;
        void *_t529 = ptr_add(self->val_data, DEREF(_t528));
        (void)_t529;
        memcpy(_t529, val, self->val_size);
        U64_delete(_t528, &(Bool){1});
        free(key);
        free(val);
        U64 _t530 = 1;
        (void)_t530;
        U64 _t531 = U64_add(self->count, _t530);
        (void)_t531;
        ;
        self->count = _t531;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t558; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t558 = *_hp; free(_hp); }
    (void)_t558;
    Bool _t559 = Bool_not(_t558);
    (void)_t559;
    ;
    if (_t559) {
        {
            U64 _fi532 = 0;
            (void)_fi532;
            while (1) {
                U64 _t534 = 0;
                (void)_t534;
                Range *_t535 = Range_new(_t534, self->count);
                (void)_t535;
                ;
                U64 _t536; { U64 *_hp = (U64 *)Range_len(_t535); _t536 = *_hp; free(_hp); }
                (void)_t536;
                Range_delete(_t535, &(Bool){1});
                Bool _wcond533; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi532}, &(U64){_t536}); _wcond533 = *_hp; free(_hp); }
                (void)_wcond533;
                ;
                if (_wcond533) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t537 = 0;
                (void)_t537;
                Range *_t538 = Range_new(_t537, self->count);
                (void)_t538;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t538, _fi532); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t538, &(Bool){1});
                U64 _t539 = 1;
                (void)_t539;
                U64 _t540 = U64_add(_fi532, _t539);
                (void)_t540;
                ;
                _fi532 = _t540;
                ;
                U64 *_t541 = malloc(sizeof(U64)); *_t541 = U64_mul(i, self->key_size);
                (void)_t541;
                ;
                void *_t542 = ptr_add(self->key_data, DEREF(_t541));
                (void)_t542;
                Bool _t543 = 0;
                (void)_t543;
                dyn_call_delete(&self->key_type, _t542, &(Bool){_t543});
                U64_delete(_t541, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t560; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t560 = *_hp; free(_hp); }
    (void)_t560;
    Bool _t561 = Bool_not(_t560);
    (void)_t561;
    ;
    if (_t561) {
        {
            U64 _fi544 = 0;
            (void)_fi544;
            while (1) {
                U64 _t546 = 0;
                (void)_t546;
                Range *_t547 = Range_new(_t546, self->count);
                (void)_t547;
                ;
                U64 _t548; { U64 *_hp = (U64 *)Range_len(_t547); _t548 = *_hp; free(_hp); }
                (void)_t548;
                Range_delete(_t547, &(Bool){1});
                Bool _wcond545; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi544}, &(U64){_t548}); _wcond545 = *_hp; free(_hp); }
                (void)_wcond545;
                ;
                if (_wcond545) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t549 = 0;
                (void)_t549;
                Range *_t550 = Range_new(_t549, self->count);
                (void)_t550;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t550, _fi544); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t550, &(Bool){1});
                U64 _t551 = 1;
                (void)_t551;
                U64 _t552 = U64_add(_fi544, _t551);
                (void)_t552;
                ;
                _fi544 = _t552;
                ;
                U64 *_t553 = malloc(sizeof(U64)); *_t553 = U64_mul(i, self->val_size);
                (void)_t553;
                ;
                void *_t554 = ptr_add(self->val_data, DEREF(_t553));
                (void)_t554;
                Bool _t555 = 0;
                (void)_t555;
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
    Bool _t562; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t562 = *_hp; free(_hp); }
    (void)_t562;
    Bool _t563 = Bool_not(_t562);
    (void)_t563;
    ;
    if (_t563) {
        Bool _t556 = 0;
        (void)_t556;
        Str_delete(&self->key_type, &(Bool){_t556});
        ;
    }
    ;
    Bool _t564; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t564 = *_hp; free(_hp); }
    (void)_t564;
    Bool _t565 = Bool_not(_t564);
    (void)_t565;
    ;
    if (_t565) {
        Bool _t557 = 0;
        (void)_t557;
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
    (void)_t583;
    U8 *new_keys = malloc(_t583);
    (void)new_keys;
    ;
    U64 _t584 = U64_mul(self->cap, self->val_size);
    (void)_t584;
    U8 *new_vals = malloc(_t584);
    (void)new_vals;
    ;
    {
        U64 _fi566 = 0;
        (void)_fi566;
        while (1) {
            U64 _t568 = 0;
            (void)_t568;
            Range *_t569 = Range_new(_t568, self->count);
            (void)_t569;
            ;
            U64 _t570; { U64 *_hp = (U64 *)Range_len(_t569); _t570 = *_hp; free(_hp); }
            (void)_t570;
            Range_delete(_t569, &(Bool){1});
            Bool _wcond567; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi566}, &(U64){_t570}); _wcond567 = *_hp; free(_hp); }
            (void)_wcond567;
            ;
            if (_wcond567) {
            } else {
                ;
                break;
            }
            ;
            U64 _t571 = 0;
            (void)_t571;
            Range *_t572 = Range_new(_t571, self->count);
            (void)_t572;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t572, _fi566); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t572, &(Bool){1});
            U64 _t573 = 1;
            (void)_t573;
            U64 _t574 = U64_add(_fi566, _t573);
            (void)_t574;
            ;
            _fi566 = _t574;
            ;
            U64 *_t575 = malloc(sizeof(U64)); *_t575 = U64_mul(i, self->key_size);
            (void)_t575;
            void *_t576 = ptr_add(self->key_data, DEREF(_t575));
            (void)_t576;
            void *ck = dyn_call_clone(&self->key_type, _t576);
            (void)ck;
            U64_delete(_t575, &(Bool){1});
            U64 *_t577 = malloc(sizeof(U64)); *_t577 = U64_mul(i, self->key_size);
            (void)_t577;
            void *_t578 = ptr_add(new_keys, DEREF(_t577));
            (void)_t578;
            memcpy(_t578, ck, self->key_size);
            U64_delete(_t577, &(Bool){1});
            free(ck);
            U64 *_t579 = malloc(sizeof(U64)); *_t579 = U64_mul(i, self->val_size);
            (void)_t579;
            void *_t580 = ptr_add(self->val_data, DEREF(_t579));
            (void)_t580;
            void *cv = dyn_call_clone(&self->val_type, _t580);
            (void)cv;
            U64_delete(_t579, &(Bool){1});
            U64 *_t581 = malloc(sizeof(U64)); *_t581 = U64_mul(i, self->val_size);
            (void)_t581;
            ;
            void *_t582 = ptr_add(new_vals, DEREF(_t581));
            (void)_t582;
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
    (void)_t585;
    return _t585;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t599; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t599 = *_hp; free(_hp); }
    (void)_t599;
    Bool _t600 = Bool_not(_t599);
    (void)_t600;
    ;
    if (_t600) {
        Bool _t597 = dyn_has_cmp(elem_type);
        (void)_t597;
        Bool _t598 = Bool_not(_t597);
        (void)_t598;
        ;
        if (_t598) {
            Str *_t587 = Str_lit("Str", 3ULL);
            (void)_t587;
            U64 _t588; { U64 *_hp = (U64 *)Str_size(); _t588 = *_hp; free(_hp); }
            (void)_t588;
            U64 _t589 = 3;
            (void)_t589;
            Array *_va11 = Array_new(_t587, &(U64){_t588}, &(U64){_t589});
            (void)_va11;
            Str_delete(_t587, &(Bool){1});
            ;
            ;
            U64 _t590 = 0;
            (void)_t590;
            Str *_t591 = Str_lit("Set.new: type ", 14ULL);
            (void)_t591;
            Array_set(_va11, &(U64){_t590}, _t591);
            ;
            U64 _t592 = 1;
            (void)_t592;
            Str *_t593 = Str_clone(elem_type);
            (void)_t593;
            Array_set(_va11, &(U64){_t592}, _t593);
            ;
            U64 _t594 = 2;
            (void)_t594;
            Str *_t595 = Str_lit(" must implement cmp", 19ULL);
            (void)_t595;
            Array_set(_va11, &(U64){_t594}, _t595);
            ;
            Str *_t596 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
            (void)_t596;
            panic(_t596, _va11);
            Str_delete(_t596, &(Bool){1});
        }
        ;
    }
    ;
    void *_t601 = malloc(DEREF(elem_size));
    (void)_t601;
    U64 _t602 = 0;
    (void)_t602;
    I64 _t603 = 1;
    (void)_t603;
    U64 _t604 = U64_clone(elem_size);
    (void)_t604;
    Set *_t605 = malloc(sizeof(Set));
    _t605->data = _t601;
    _t605->count = _t602;
    _t605->cap = _t603;
    _t605->elem_size = _t604;
    { Str *_ca = Str_clone(elem_type); _t605->elem_type = *_ca; free(_ca); }
    (void)_t605;
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
    (void)val;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond606; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond606 = *_hp; free(_hp); }
        (void)_wcond606;
        if (_wcond606) {
        } else {
            ;
            break;
        }
        ;
        U64 _t613 = U64_sub(hi, lo);
        (void)_t613;
        U64 _t614 = 2;
        (void)_t614;
        U64 _t615 = U64_div(_t613, _t614);
        (void)_t615;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t615);
        (void)mid;
        ;
        U64 *_t616 = malloc(sizeof(U64)); *_t616 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t616;
        void *_t617 = ptr_add(self->data, DEREF(_t616));
        (void)_t617;
        I64 *c = dyn_call_cmp(&self->elem_type, _t617, val);
        (void)c;
        U64_delete(_t616, &(Bool){1});
        I64 _t618 = 0;
        (void)_t618;
        Bool _t619; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t618}); _t619 = *_hp; free(_hp); }
        (void)_t619;
        ;
        if (_t619) {
            U64 _t607 = 1;
            (void)_t607;
            U64 _t608 = U64_add(DEREF(mid), _t607);
            (void)_t608;
            ;
            lo = _t608;
            ;
        } else {
            I64 _t611 = 0;
            (void)_t611;
            Bool _t612; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t611}); _t612 = *_hp; free(_hp); }
            (void)_t612;
            ;
            if (_t612) {
                U64 _t609 = U64_clone(mid);
                (void)_t609;
                hi = _t609;
                ;
            } else {
                Bool _t610 = 1;
                (void)_t610;
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
    (void)_t620;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t620; return _r; }
}

void Set_add(Set * self, void * val) {
    (void)self;
    (void)val;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    Bool found = 0;
    (void)found;
    while (1) {
        Bool _wcond621; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond621 = *_hp; free(_hp); }
        (void)_wcond621;
        if (_wcond621) {
        } else {
            ;
            break;
        }
        ;
        U64 _t630 = U64_sub(hi, lo);
        (void)_t630;
        U64 _t631 = 2;
        (void)_t631;
        U64 _t632 = U64_div(_t630, _t631);
        (void)_t632;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t632);
        (void)mid;
        ;
        U64 *_t633 = malloc(sizeof(U64)); *_t633 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t633;
        void *_t634 = ptr_add(self->data, DEREF(_t633));
        (void)_t634;
        I64 *c = dyn_call_cmp(&self->elem_type, _t634, val);
        (void)c;
        U64_delete(_t633, &(Bool){1});
        I64 _t635 = 0;
        (void)_t635;
        Bool _t636; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t635}); _t636 = *_hp; free(_hp); }
        (void)_t636;
        ;
        if (_t636) {
            U64 _t622 = 1;
            (void)_t622;
            U64 _t623 = U64_add(DEREF(mid), _t622);
            (void)_t623;
            ;
            lo = _t623;
            ;
        } else {
            I64 _t628 = 0;
            (void)_t628;
            Bool _t629; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t628}); _t629 = *_hp; free(_hp); }
            (void)_t629;
            ;
            if (_t629) {
                U64 _t624 = U64_clone(mid);
                (void)_t624;
                hi = _t624;
                ;
            } else {
                Bool _t625 = 1;
                (void)_t625;
                found = _t625;
                ;
                U64 _t626 = U64_clone(mid);
                (void)_t626;
                lo = _t626;
                ;
                U64 _t627 = U64_clone(mid);
                (void)_t627;
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
        Bool _t638; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t638 = *_hp; free(_hp); }
        (void)_t638;
        Bool _t639 = Bool_not(_t638);
        (void)_t639;
        ;
        if (_t639) {
            Bool _t637 = 0;
            (void)_t637;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t637});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t644 = U64_eq(self->count, self->cap);
        (void)_t644;
        if (_t644) {
            U64 _t640 = 2;
            (void)_t640;
            U64 new_cap = U64_mul(self->cap, _t640);
            (void)new_cap;
            ;
            U64 _t641 = U64_mul(new_cap, self->elem_size);
            (void)_t641;
            void *_t642 = realloc(self->data, _t641);
            (void)_t642;
            ;
            self->data = _t642;
            U64 _t643 = U64_clone(&(U64){new_cap});
            (void)_t643;
            ;
            self->cap = _t643;
            ;
        }
        ;
        U64 _t645 = 1;
        (void)_t645;
        U64 _t646 = U64_add(lo, _t645);
        (void)_t646;
        ;
        U64 *_t647 = malloc(sizeof(U64)); *_t647 = U64_mul(_t646, self->elem_size);
        (void)_t647;
        ;
        U64 *_t648 = malloc(sizeof(U64)); *_t648 = U64_mul(lo, self->elem_size);
        (void)_t648;
        U64 _t649 = U64_sub(self->count, lo);
        (void)_t649;
        void *_t650 = ptr_add(self->data, DEREF(_t647));
        (void)_t650;
        void *_t651 = ptr_add(self->data, DEREF(_t648));
        (void)_t651;
        U64 _t652 = U64_mul(_t649, self->elem_size);
        (void)_t652;
        ;
        memmove(_t650, _t651, _t652);
        U64_delete(_t647, &(Bool){1});
        U64_delete(_t648, &(Bool){1});
        ;
        U64 *_t653 = malloc(sizeof(U64)); *_t653 = U64_mul(lo, self->elem_size);
        (void)_t653;
        void *_t654 = ptr_add(self->data, DEREF(_t653));
        (void)_t654;
        memcpy(_t654, val, self->elem_size);
        U64_delete(_t653, &(Bool){1});
        free(val);
        U64 _t655 = 1;
        (void)_t655;
        U64 _t656 = U64_add(self->count, _t655);
        (void)_t656;
        ;
        self->count = _t656;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t670; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t670 = *_hp; free(_hp); }
    (void)_t670;
    Bool _t671 = Bool_not(_t670);
    (void)_t671;
    ;
    if (_t671) {
        {
            U64 _fi657 = 0;
            (void)_fi657;
            while (1) {
                U64 _t659 = 0;
                (void)_t659;
                Range *_t660 = Range_new(_t659, self->count);
                (void)_t660;
                ;
                U64 _t661; { U64 *_hp = (U64 *)Range_len(_t660); _t661 = *_hp; free(_hp); }
                (void)_t661;
                Range_delete(_t660, &(Bool){1});
                Bool _wcond658; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi657}, &(U64){_t661}); _wcond658 = *_hp; free(_hp); }
                (void)_wcond658;
                ;
                if (_wcond658) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t662 = 0;
                (void)_t662;
                Range *_t663 = Range_new(_t662, self->count);
                (void)_t663;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t663, _fi657); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t663, &(Bool){1});
                U64 _t664 = 1;
                (void)_t664;
                U64 _t665 = U64_add(_fi657, _t664);
                (void)_t665;
                ;
                _fi657 = _t665;
                ;
                U64 *_t666 = malloc(sizeof(U64)); *_t666 = U64_mul(i, self->elem_size);
                (void)_t666;
                ;
                void *_t667 = ptr_add(self->data, DEREF(_t666));
                (void)_t667;
                Bool _t668 = 0;
                (void)_t668;
                dyn_call_delete(&self->elem_type, _t667, &(Bool){_t668});
                U64_delete(_t666, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t672; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t672 = *_hp; free(_hp); }
    (void)_t672;
    Bool _t673 = Bool_not(_t672);
    (void)_t673;
    ;
    if (_t673) {
        Bool _t669 = 0;
        (void)_t669;
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
    (void)_t687;
    U8 *new_data = malloc(_t687);
    (void)new_data;
    ;
    {
        U64 _fi674 = 0;
        (void)_fi674;
        while (1) {
            U64 _t676 = 0;
            (void)_t676;
            Range *_t677 = Range_new(_t676, self->count);
            (void)_t677;
            ;
            U64 _t678; { U64 *_hp = (U64 *)Range_len(_t677); _t678 = *_hp; free(_hp); }
            (void)_t678;
            Range_delete(_t677, &(Bool){1});
            Bool _wcond675; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi674}, &(U64){_t678}); _wcond675 = *_hp; free(_hp); }
            (void)_wcond675;
            ;
            if (_wcond675) {
            } else {
                ;
                break;
            }
            ;
            U64 _t679 = 0;
            (void)_t679;
            Range *_t680 = Range_new(_t679, self->count);
            (void)_t680;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t680, _fi674); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t680, &(Bool){1});
            U64 _t681 = 1;
            (void)_t681;
            U64 _t682 = U64_add(_fi674, _t681);
            (void)_t682;
            ;
            _fi674 = _t682;
            ;
            U64 *_t683 = malloc(sizeof(U64)); *_t683 = U64_mul(i, self->elem_size);
            (void)_t683;
            void *_t684 = ptr_add(self->data, DEREF(_t683));
            (void)_t684;
            void *cloned = dyn_call_clone(&self->elem_type, _t684);
            (void)cloned;
            U64_delete(_t683, &(Bool){1});
            U64 *_t685 = malloc(sizeof(U64)); *_t685 = U64_mul(i, self->elem_size);
            (void)_t685;
            ;
            void *_t686 = ptr_add(new_data, DEREF(_t685));
            (void)_t686;
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
    (void)_t688;
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
    (void)i;
    Bool _t696; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t696 = *_hp; free(_hp); }
    (void)_t696;
    if (_t696) {
        Str *_t690 = Str_lit("Str", 3ULL);
        (void)_t690;
        U64 _t691; { U64 *_hp = (U64 *)Str_size(); _t691 = *_hp; free(_hp); }
        (void)_t691;
        U64 _t692 = 1;
        (void)_t692;
        Array *_va12 = Array_new(_t690, &(U64){_t691}, &(U64){_t692});
        (void)_va12;
        Str_delete(_t690, &(Bool){1});
        ;
        ;
        U64 _t693 = 0;
        (void)_t693;
        Str *_t694 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t694;
        Array_set(_va12, &(U64){_t693}, _t694);
        ;
        Str *_t695 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t695;
        panic(_t695, _va12);
        Str_delete(_t695, &(Bool){1});
    }
    ;
    void *_t697 = ptr_add(self->c_str, DEREF(i));
    (void)_t697;
    return _t697;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t698 = ptr_add(self->c_str, DEREF(i));
    (void)_t698;
    return _t698;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t704; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t704 = *_hp; free(_hp); }
    (void)_t704;
    if (_t704) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond699; { Bool *_hp = (Bool *)U64_lt(i, &(U64){min_len}); _wcond699 = *_hp; free(_hp); }
        (void)_wcond699;
        if (_wcond699) {
        } else {
            ;
            break;
        }
        ;
        U8 *ab = Str_get(a, i);
        (void)ab;
        U8 *bb = Str_get(b, i);
        (void)bb;
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        (void)c;
        I64 _t700 = 0;
        (void)_t700;
        Bool _t701; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t700}); _t701 = *_hp; free(_hp); }
        (void)_t701;
        ;
        if (_t701) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t702 = 1;
        (void)_t702;
        U64 _t703 = U64_add(DEREF(i), _t702);
        (void)_t703;
        ;
        *i = _t703;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t705 = U64_cmp(a->count, b->count);
    (void)_t705;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t705; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t706 = 1;
    (void)_t706;
    U64 _t707 = U64_add(DEREF(new_len), _t706);
    (void)_t707;
    ;
    U8 *new_data = malloc(_t707);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t708 = ptr_add(new_data, a->count);
    (void)_t708;
    memcpy(_t708, b->c_str, b->count);
    void *_t709 = ptr_add(new_data, DEREF(new_len));
    (void)_t709;
    I64 _t710 = 0;
    (void)_t710;
    U64 _t711 = 1;
    (void)_t711;
    memcpy(_t709, &(I64){_t710}, _t711);
    ;
    ;
    U64 _t712 = U64_clone(new_len);
    (void)_t712;
    U64 _t713 = U64_clone(new_len);
    (void)_t713;
    U64_delete(new_len, &(Bool){1});
    Str *_t714 = malloc(sizeof(Str));
    _t714->c_str = new_data;
    _t714->count = _t712;
    _t714->cap = _t713;
    (void)_t714;
    ;
    ;
    return _t714;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t715 = 1;
    (void)_t715;
    U64 _t716 = U64_add(DEREF(n), _t715);
    (void)_t716;
    ;
    U8 *buf = malloc(_t716);
    (void)buf;
    ;
    I64 _t717 = 0;
    (void)_t717;
    U64 _t718 = 1;
    (void)_t718;
    memcpy(buf, &(I64){_t717}, _t718);
    ;
    ;
    I64 _t719 = 0;
    (void)_t719;
    U64 _t720 = U64_clone(n);
    (void)_t720;
    Str *_t721 = malloc(sizeof(Str));
    _t721->c_str = buf;
    _t721->count = _t719;
    _t721->cap = _t720;
    (void)_t721;
    ;
    ;
    return _t721;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t734; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t734 = *_hp; free(_hp); }
    (void)_t734;
    if (_t734) {
        Str *_t722 = Str_lit("Str", 3ULL);
        (void)_t722;
        U64 _t723; { U64 *_hp = (U64 *)Str_size(); _t723 = *_hp; free(_hp); }
        (void)_t723;
        U64 _t724 = 1;
        (void)_t724;
        Array *_va13 = Array_new(_t722, &(U64){_t723}, &(U64){_t724});
        (void)_va13;
        Str_delete(_t722, &(Bool){1});
        ;
        ;
        U64 _t725 = 0;
        (void)_t725;
        Str *_t726 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t726;
        Array_set(_va13, &(U64){_t725}, _t726);
        ;
        Str *_t727 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:57:19", 60ULL);
        (void)_t727;
        panic(_t727, _va13);
        Str_delete(_t727, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t735; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t735 = *_hp; free(_hp); }
    (void)_t735;
    if (_t735) {
        Str *_t728 = Str_lit("Str", 3ULL);
        (void)_t728;
        U64 _t729; { U64 *_hp = (U64 *)Str_size(); _t729 = *_hp; free(_hp); }
        (void)_t729;
        U64 _t730 = 1;
        (void)_t730;
        Array *_va14 = Array_new(_t728, &(U64){_t729}, &(U64){_t730});
        (void)_va14;
        Str_delete(_t728, &(Bool){1});
        ;
        ;
        U64 _t731 = 0;
        (void)_t731;
        Str *_t732 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t732;
        Array_set(_va14, &(U64){_t731}, _t732);
        ;
        Str *_t733 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:61:19", 60ULL);
        (void)_t733;
        panic(_t733, _va14);
        Str_delete(_t733, &(Bool){1});
    }
    ;
    void *_t736 = ptr_add(self->c_str, self->count);
    (void)_t736;
    memcpy(_t736, s->c_str, s->count);
    U64 _t737 = U64_clone(new_len);
    (void)_t737;
    self->count = _t737;
    ;
    void *_t738 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t738;
    I64 _t739 = 0;
    (void)_t739;
    U64 _t740 = 1;
    (void)_t740;
    memcpy(_t738, &(I64){_t739}, _t740);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t741 = 1;
    (void)_t741;
    U64 _t742 = U64_add(val->count, _t741);
    (void)_t742;
    ;
    U8 *new_data = malloc(_t742);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t743 = ptr_add(new_data, val->count);
    (void)_t743;
    I64 _t744 = 0;
    (void)_t744;
    U64 _t745 = 1;
    (void)_t745;
    memcpy(_t743, &(I64){_t744}, _t745);
    ;
    ;
    Str *_t746 = malloc(sizeof(Str));
    _t746->c_str = new_data;
    _t746->count = val->count;
    _t746->cap = val->count;
    (void)_t746;
    return _t746;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t747; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t747 = *_hp; free(_hp); }
    (void)_t747;
    if (_t747) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t748 = Str_clone(val);
    (void)_t748;
    return _t748;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t750; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t750 = *_hp; free(_hp); }
    (void)_t750;
    if (_t750) {
        *st = s->count;
    }
    ;
    U64 _t751 = U64_add(DEREF(st), ln);
    (void)_t751;
    Bool _t752; { Bool *_hp = (Bool *)U64_gt(&(U64){_t751}, &s->count); _t752 = *_hp; free(_hp); }
    (void)_t752;
    ;
    if (_t752) {
        U64 _t749 = U64_sub(s->count, DEREF(st));
        (void)_t749;
        ln = _t749;
        ;
    }
    ;
    void *_t753 = ptr_add(s->c_str, DEREF(st));
    (void)_t753;
    U64 _t754 = U64_clone(&(U64){ln});
    (void)_t754;
    ;
    U64 _t755 = U64_clone(CAP_VIEW);
    (void)_t755;
    Str *_t756 = malloc(sizeof(Str));
    _t756->c_str = _t753;
    _t756->count = _t754;
    _t756->cap = _t755;
    (void)_t756;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t756;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t770 = 0;
    (void)_t770;
    Bool _t771 = U64_eq(b->count, _t770);
    (void)_t771;
    ;
    if (_t771) {
        Bool _t757 = 1;
        (void)_t757;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t757; return _r; }
    }
    ;
    Bool _t772; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t772 = *_hp; free(_hp); }
    (void)_t772;
    if (_t772) {
        Bool _t758 = 0;
        (void)_t758;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t758; return _r; }
    }
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t767 = U64_sub(a->count, b->count);
        (void)_t767;
        Bool _wcond759; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t767}); _wcond759 = *_hp; free(_hp); }
        (void)_wcond759;
        ;
        if (_wcond759) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        (void)j;
        Bool found = 1;
        (void)found;
        while (1) {
            Bool _wcond760; { Bool *_hp = (Bool *)U64_lt(j, &b->count); _wcond760 = *_hp; free(_hp); }
            (void)_wcond760;
            if (_wcond760) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t762 = malloc(sizeof(U64)); *_t762 = U64_add(i, DEREF(j));
            (void)_t762;
            U8 *ac = Str_get(a, _t762);
            (void)ac;
            U8 *bc = Str_get(b, j);
            (void)bc;
            Bool _t763; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t763 = *_hp; free(_hp); }
            (void)_t763;
            U64_delete(_t762, &(Bool){1});
            if (_t763) {
                Bool _t761 = 0;
                (void)_t761;
                found = _t761;
                ;
            }
            ;
            U64 _t764 = 1;
            (void)_t764;
            U64 _t765 = U64_add(DEREF(j), _t764);
            (void)_t765;
            ;
            *j = _t765;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t766 = 1;
            (void)_t766;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t766; return _r; }
        }
        ;
        U64 _t768 = 1;
        (void)_t768;
        U64 _t769 = U64_add(i, _t768);
        (void)_t769;
        ;
        i = _t769;
        ;
    }
    ;
    Bool _t773 = 0;
    (void)_t773;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t773; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t780; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t780 = *_hp; free(_hp); }
    (void)_t780;
    if (_t780) {
        Bool _t774 = 0;
        (void)_t774;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t774; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        Bool _wcond775; { Bool *_hp = (Bool *)U64_lt(i, &b->count); _wcond775 = *_hp; free(_hp); }
        (void)_wcond775;
        if (_wcond775) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        (void)ac;
        U8 *bc = Str_get(b, i);
        (void)bc;
        Bool _t777; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t777 = *_hp; free(_hp); }
        (void)_t777;
        if (_t777) {
            Bool _t776 = 0;
            (void)_t776;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t776; return _r; }
        }
        ;
        U64 _t778 = 1;
        (void)_t778;
        U64 _t779 = U64_add(DEREF(i), _t778);
        (void)_t779;
        ;
        *i = _t779;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t781 = 1;
    (void)_t781;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t781; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t789; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t789 = *_hp; free(_hp); }
    (void)_t789;
    if (_t789) {
        Bool _t782 = 0;
        (void)_t782;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t782; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        Bool _wcond783; { Bool *_hp = (Bool *)U64_lt(i, &b->count); _wcond783 = *_hp; free(_hp); }
        (void)_wcond783;
        if (_wcond783) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t785 = malloc(sizeof(U64)); *_t785 = U64_add(offset, DEREF(i));
        (void)_t785;
        U8 *ac = Str_get(a, _t785);
        (void)ac;
        U8 *bc = Str_get(b, i);
        (void)bc;
        Bool _t786; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t786 = *_hp; free(_hp); }
        (void)_t786;
        U64_delete(_t785, &(Bool){1});
        if (_t786) {
            Bool _t784 = 0;
            (void)_t784;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t784; return _r; }
        }
        ;
        U64 _t787 = 1;
        (void)_t787;
        U64 _t788 = U64_add(DEREF(i), _t787);
        (void)_t788;
        ;
        *i = _t788;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t790 = 1;
    (void)_t790;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t790; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t791 = 0;
    (void)_t791;
    Bool _t792 = U64_eq(self->count, _t791);
    (void)_t792;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t792; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t810 = 0;
    (void)_t810;
    Bool _t811 = U64_eq(needle->count, _t810);
    (void)_t811;
    ;
    if (_t811) {
        I64 _t793 = 0;
        (void)_t793;
        I64 _t794 = 1;
        (void)_t794;
        I64 _t795 = I64_sub(_t793, _t794);
        (void)_t795;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t795; return _r; }
    }
    ;
    Bool _t812; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t812 = *_hp; free(_hp); }
    (void)_t812;
    if (_t812) {
        I64 _t796 = 0;
        (void)_t796;
        I64 _t797 = 1;
        (void)_t797;
        I64 _t798 = I64_sub(_t796, _t797);
        (void)_t798;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t798; return _r; }
    }
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t807 = U64_sub(self->count, needle->count);
        (void)_t807;
        Bool _wcond799; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t807}); _wcond799 = *_hp; free(_hp); }
        (void)_wcond799;
        ;
        if (_wcond799) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        (void)j;
        Bool found = 1;
        (void)found;
        while (1) {
            Bool _wcond800; { Bool *_hp = (Bool *)U64_lt(j, &needle->count); _wcond800 = *_hp; free(_hp); }
            (void)_wcond800;
            if (_wcond800) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t802 = malloc(sizeof(U64)); *_t802 = U64_add(i, DEREF(j));
            (void)_t802;
            U8 *ac = Str_get(self, _t802);
            (void)ac;
            U8 *bc = Str_get(needle, j);
            (void)bc;
            Bool _t803; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t803 = *_hp; free(_hp); }
            (void)_t803;
            U64_delete(_t802, &(Bool){1});
            if (_t803) {
                Bool _t801 = 0;
                (void)_t801;
                found = _t801;
                ;
            }
            ;
            U64 _t804 = 1;
            (void)_t804;
            U64 _t805 = U64_add(DEREF(j), _t804);
            (void)_t805;
            ;
            *j = _t805;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t806 = U64_to_i64(i);
            (void)_t806;
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t806; return _r; }
        }
        ;
        U64 _t808 = 1;
        (void)_t808;
        U64 _t809 = U64_add(i, _t808);
        (void)_t809;
        ;
        i = _t809;
        ;
    }
    ;
    I64 _t813 = 0;
    (void)_t813;
    I64 _t814 = 1;
    (void)_t814;
    I64 _t815 = I64_sub(_t813, _t814);
    (void)_t815;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t815; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t833 = 0;
    (void)_t833;
    Bool _t834 = U64_eq(needle->count, _t833);
    (void)_t834;
    ;
    if (_t834) {
        I64 _t816 = 0;
        (void)_t816;
        I64 _t817 = 1;
        (void)_t817;
        I64 _t818 = I64_sub(_t816, _t817);
        (void)_t818;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t818; return _r; }
    }
    ;
    Bool _t835; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t835 = *_hp; free(_hp); }
    (void)_t835;
    if (_t835) {
        I64 _t819 = 0;
        (void)_t819;
        I64 _t820 = 1;
        (void)_t820;
        I64 _t821 = I64_sub(_t819, _t820);
        (void)_t821;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t821; return _r; }
    }
    ;
    I64 _t836 = 0;
    (void)_t836;
    I64 _t837 = 1;
    (void)_t837;
    I64 last = I64_sub(_t836, _t837);
    (void)last;
    ;
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t830 = U64_sub(self->count, needle->count);
        (void)_t830;
        Bool _wcond822; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t830}); _wcond822 = *_hp; free(_hp); }
        (void)_wcond822;
        ;
        if (_wcond822) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        (void)j;
        Bool found = 1;
        (void)found;
        while (1) {
            Bool _wcond823; { Bool *_hp = (Bool *)U64_lt(j, &needle->count); _wcond823 = *_hp; free(_hp); }
            (void)_wcond823;
            if (_wcond823) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t825 = malloc(sizeof(U64)); *_t825 = U64_add(i, DEREF(j));
            (void)_t825;
            U8 *ac = Str_get(self, _t825);
            (void)ac;
            U8 *bc = Str_get(needle, j);
            (void)bc;
            Bool _t826; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t826 = *_hp; free(_hp); }
            (void)_t826;
            U64_delete(_t825, &(Bool){1});
            if (_t826) {
                Bool _t824 = 0;
                (void)_t824;
                found = _t824;
                ;
            }
            ;
            U64 _t827 = 1;
            (void)_t827;
            U64 _t828 = U64_add(DEREF(j), _t827);
            (void)_t828;
            ;
            *j = _t828;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t829 = U64_to_i64(i);
            (void)_t829;
            last = _t829;
            ;
        }
        ;
        U64 _t831 = 1;
        (void)_t831;
        U64 _t832 = U64_add(i, _t831);
        (void)_t832;
        ;
        i = _t832;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t853 = 0;
    (void)_t853;
    Bool _t854 = U64_eq(from->count, _t853);
    (void)_t854;
    ;
    if (_t854) {
        Str *_t838 = Str_clone(self);
        (void)_t838;
        ;
        return _t838;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t840 = U64_sub(self->count, from->count);
        (void)_t840;
        Bool _wcond839; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t840}); _wcond839 = *_hp; free(_hp); }
        (void)_wcond839;
        ;
        if (_wcond839) {
        } else {
            ;
            break;
        }
        ;
        U64 _t841 = U64_sub(self->count, start);
        (void)_t841;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t841});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t842 = 0;
        (void)_t842;
        I64 _t843 = 1;
        (void)_t843;
        I64 _t844 = I64_sub(_t842, _t843);
        (void)_t844;
        ;
        ;
        Bool _t845 = I64_eq(pos, _t844);
        (void)_t845;
        ;
        if (_t845) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t846 = I64_to_u64(pos);
        (void)_t846;
        Str *_t847 = Str_substr(self, &(U64){start}, &(U64){_t846});
        (void)_t847;
        ;
        result = Str_concat(result, _t847);
        Str_delete(_t847, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t848 = I64_to_u64(pos);
        (void)_t848;
        ;
        U64 _t849 = U64_add(start, _t848);
        (void)_t849;
        ;
        U64 _t850 = U64_add(_t849, from->count);
        (void)_t850;
        ;
        start = _t850;
        ;
    }
    Bool _t855; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t855 = *_hp; free(_hp); }
    (void)_t855;
    if (_t855) {
        U64 _t851 = U64_sub(self->count, start);
        (void)_t851;
        Str *_t852 = Str_substr(self, &(U64){start}, &(U64){_t851});
        (void)_t852;
        ;
        result = Str_concat(result, _t852);
        Str_delete(_t852, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t856 = 1;
    (void)_t856;
    Str *_t857 = Str_substr(self, i, &(U64){_t856});
    (void)_t857;
    ;
    return _t857;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t860; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t860 = *_hp; free(_hp); }
    (void)_t860;
    if (_t860) {
        U64 _t858 = U64_sub(self->count, prefix->count);
        (void)_t858;
        Str *_t859 = Str_substr(self, &prefix->count, &(U64){_t858});
        (void)_t859;
        ;
        ;
        return _t859;
    }
    ;
    Str *_t861 = Str_clone(self);
    (void)_t861;
    return _t861;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t865; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t865 = *_hp; free(_hp); }
    (void)_t865;
    if (_t865) {
        U64 _t862 = 0;
        (void)_t862;
        U64 _t863 = U64_sub(self->count, suffix->count);
        (void)_t863;
        Str *_t864 = Str_substr(self, &(U64){_t862}, &(U64){_t863});
        (void)_t864;
        ;
        ;
        ;
        return _t864;
    }
    ;
    Str *_t866 = Str_clone(self);
    (void)_t866;
    return _t866;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t867 = 2;
    (void)_t867;
    U8 *buf = malloc(_t867);
    (void)buf;
    ;
    U64 _t868 = 1;
    (void)_t868;
    memcpy(buf, byte, _t868);
    ;
    U64 *_t869 = malloc(sizeof(U64));
    *_t869 = 1;
    (void)_t869;
    void *_t870 = ptr_add(buf, DEREF(_t869));
    (void)_t870;
    I64 _t871 = 0;
    (void)_t871;
    U64 _t872 = 1;
    (void)_t872;
    memcpy(_t870, &(I64){_t871}, _t872);
    U64_delete(_t869, &(Bool){1});
    ;
    ;
    I64 _t873 = 1;
    (void)_t873;
    I64 _t874 = 1;
    (void)_t874;
    Str *_t875 = malloc(sizeof(Str));
    _t875->c_str = buf;
    _t875->count = _t873;
    _t875->cap = _t874;
    (void)_t875;
    ;
    ;
    return _t875;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t915 = 0;
    (void)_t915;
    Bool _t916 = U64_eq(self->count, _t915);
    (void)_t916;
    ;
    if (_t916) {
        Str *_t876 = Str_lit("Str", 3ULL);
        (void)_t876;
        U64 _t877; { U64 *_hp = (U64 *)Str_size(); _t877 = *_hp; free(_hp); }
        (void)_t877;
        U64 _t878 = 1;
        (void)_t878;
        Array *_va15 = Array_new(_t876, &(U64){_t877}, &(U64){_t878});
        (void)_va15;
        Str_delete(_t876, &(Bool){1});
        ;
        ;
        U64 _t879 = 0;
        (void)_t879;
        Str *_t880 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t880;
        Array_set(_va15, &(U64){_t879}, _t880);
        ;
        Str *_t881 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:224:37", 61ULL);
        (void)_t881;
        panic(_t881, _va15);
        Str_delete(_t881, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    Bool neg = 0;
    (void)neg;
    U64 *_t917 = malloc(sizeof(U64));
    *_t917 = 0;
    (void)_t917;
    U8 *first = Str_get(self, _t917);
    (void)first;
    U8 _t918 = 45;
    (void)_t918;
    Bool _t919 = U8_eq(DEREF(first), _t918);
    (void)_t919;
    U64_delete(_t917, &(Bool){1});
    ;
    if (_t919) {
        Bool _t882 = 1;
        (void)_t882;
        neg = _t882;
        ;
        U64 _t883 = 1;
        (void)_t883;
        *i = _t883;
        ;
    }
    ;
    Bool _t920 = U64_eq(DEREF(i), self->count);
    (void)_t920;
    if (_t920) {
        Str *_t884 = Str_lit("Str", 3ULL);
        (void)_t884;
        U64 _t885; { U64 *_hp = (U64 *)Str_size(); _t885 = *_hp; free(_hp); }
        (void)_t885;
        U64 _t886 = 1;
        (void)_t886;
        Array *_va16 = Array_new(_t884, &(U64){_t885}, &(U64){_t886});
        (void)_va16;
        Str_delete(_t884, &(Bool){1});
        ;
        ;
        U64 _t887 = 0;
        (void)_t887;
        Str *_t888 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t888;
        Array_set(_va16, &(U64){_t887}, _t888);
        ;
        Str *_t889 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:233:37", 61ULL);
        (void)_t889;
        panic(_t889, _va16);
        Str_delete(_t889, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond890; { Bool *_hp = (Bool *)U64_lt(i, &self->count); _wcond890 = *_hp; free(_hp); }
        (void)_wcond890;
        if (_wcond890) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        (void)ch;
        I64 _t901 = U8_to_i64(DEREF(ch));
        (void)_t901;
        I64 _t902 = 48;
        (void)_t902;
        I64 d = I64_sub(_t901, _t902);
        (void)d;
        ;
        ;
        I64 _t903 = 0;
        (void)_t903;
        I64 _t904 = 9;
        (void)_t904;
        Bool _t905; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t903}); _t905 = *_hp; free(_hp); }
        (void)_t905;
        ;
        Bool _t906; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t904}); _t906 = *_hp; free(_hp); }
        (void)_t906;
        ;
        Bool _t907 = Bool_or(_t905, _t906);
        (void)_t907;
        ;
        ;
        if (_t907) {
            Str *_t891 = Str_lit("Str", 3ULL);
            (void)_t891;
            U64 _t892; { U64 *_hp = (U64 *)Str_size(); _t892 = *_hp; free(_hp); }
            (void)_t892;
            U64 _t893 = 3;
            (void)_t893;
            Array *_va17 = Array_new(_t891, &(U64){_t892}, &(U64){_t893});
            (void)_va17;
            Str_delete(_t891, &(Bool){1});
            ;
            ;
            U64 _t894 = 0;
            (void)_t894;
            Str *_t895 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
            (void)_t895;
            Array_set(_va17, &(U64){_t894}, _t895);
            ;
            U64 _t896 = 1;
            (void)_t896;
            Str *_t897 = Str_clone(self);
            (void)_t897;
            Array_set(_va17, &(U64){_t896}, _t897);
            ;
            U64 _t898 = 2;
            (void)_t898;
            Str *_t899 = Str_lit("'", 1ULL);
            (void)_t899;
            Array_set(_va17, &(U64){_t898}, _t899);
            ;
            Str *_t900 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:238:23", 61ULL);
            (void)_t900;
            panic(_t900, _va17);
            Str_delete(_t900, &(Bool){1});
        }
        ;
        I64 _t908 = 10;
        (void)_t908;
        I64 _t909 = I64_mul(result, _t908);
        (void)_t909;
        ;
        I64 _t910 = I64_add(_t909, d);
        (void)_t910;
        ;
        ;
        result = _t910;
        ;
        U64 _t911 = 1;
        (void)_t911;
        U64 _t912 = U64_add(DEREF(i), _t911);
        (void)_t912;
        ;
        *i = _t912;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t913 = 0;
        (void)_t913;
        I64 _t914 = I64_sub(_t913, result);
        (void)_t914;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t914; return _r; }
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
    (void)a;
    (void)b;
    I64 _t922; { I64 *_hp = (I64 *)Str_cmp(a, b); _t922 = *_hp; free(_hp); }
    (void)_t922;
    I64 _t923 = 0;
    (void)_t923;
    Bool _t924 = I64_eq(_t922, _t923);
    (void)_t924;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t924; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t925 = 0;
    (void)_t925;
    I64 _t926 = 1;
    (void)_t926;
    I64 _t927; { I64 *_hp = (I64 *)Str_cmp(a, b); _t927 = *_hp; free(_hp); }
    (void)_t927;
    I64 _t928 = I64_sub(_t925, _t926);
    (void)_t928;
    ;
    ;
    Bool _t929 = I64_eq(_t927, _t928);
    (void)_t929;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t929; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t930; { I64 *_hp = (I64 *)Str_cmp(a, b); _t930 = *_hp; free(_hp); }
    (void)_t930;
    I64 _t931 = 1;
    (void)_t931;
    Bool _t932 = I64_eq(_t930, _t931);
    (void)_t932;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t932; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t933; { Bool *_hp = (Bool *)Str_eq(a, b); _t933 = *_hp; free(_hp); }
    (void)_t933;
    Bool _t934 = Bool_not(_t933);
    (void)_t934;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t934; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t935; { Bool *_hp = (Bool *)Str_gt(a, b); _t935 = *_hp; free(_hp); }
    (void)_t935;
    Bool _t936 = Bool_not(_t935);
    (void)_t936;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t936; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t937; { Bool *_hp = (Bool *)Str_lt(a, b); _t937 = *_hp; free(_hp); }
    (void)_t937;
    Bool _t938 = Bool_not(_t937);
    (void)_t938;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t938; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t939 = malloc(DEREF(elem_size));
    (void)_t939;
    U64 _t940 = 0;
    (void)_t940;
    I64 _t941 = 1;
    (void)_t941;
    U64 _t942 = U64_clone(elem_size);
    (void)_t942;
    Vec *_t943 = malloc(sizeof(Vec));
    _t943->data = _t939;
    _t943->count = _t940;
    _t943->cap = _t941;
    _t943->elem_size = _t942;
    { Str *_ca = Str_clone(elem_type); _t943->elem_type = *_ca; free(_ca); }
    (void)_t943;
    ;
    ;
    ;
    return _t943;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t948 = U64_eq(self->count, self->cap);
    (void)_t948;
    if (_t948) {
        U64 _t944 = 2;
        (void)_t944;
        U64 new_cap = U64_mul(self->cap, _t944);
        (void)new_cap;
        ;
        U64 _t945 = U64_mul(new_cap, self->elem_size);
        (void)_t945;
        void *_t946 = realloc(self->data, _t945);
        (void)_t946;
        ;
        self->data = _t946;
        U64 _t947 = U64_clone(&(U64){new_cap});
        (void)_t947;
        ;
        self->cap = _t947;
        ;
    }
    ;
    U64 *_t949 = malloc(sizeof(U64)); *_t949 = U64_mul(self->count, self->elem_size);
    (void)_t949;
    void *_t950 = ptr_add(self->data, DEREF(_t949));
    (void)_t950;
    memcpy(_t950, val, self->elem_size);
    U64_delete(_t949, &(Bool){1});
    free(val);
    U64 _t951 = 1;
    (void)_t951;
    U64 _t952 = U64_add(self->count, _t951);
    (void)_t952;
    ;
    self->count = _t952;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t967; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t967 = *_hp; free(_hp); }
    (void)_t967;
    if (_t967) {
        Str *_t953 = Str_lit("Str", 3ULL);
        (void)_t953;
        U64 _t954; { U64 *_hp = (U64 *)Str_size(); _t954 = *_hp; free(_hp); }
        (void)_t954;
        U64 _t955 = 5;
        (void)_t955;
        Array *_va18 = Array_new(_t953, &(U64){_t954}, &(U64){_t955});
        (void)_va18;
        Str_delete(_t953, &(Bool){1});
        ;
        ;
        U64 _t956 = 0;
        (void)_t956;
        Str *_t957 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t957;
        Array_set(_va18, &(U64){_t956}, _t957);
        ;
        U64 _t958 = 1;
        (void)_t958;
        Str *_t959 = U64_to_str(DEREF(i));
        (void)_t959;
        Array_set(_va18, &(U64){_t958}, _t959);
        ;
        U64 _t960 = 2;
        (void)_t960;
        Str *_t961 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t961;
        Array_set(_va18, &(U64){_t960}, _t961);
        ;
        U64 _t962 = 3;
        (void)_t962;
        Str *_t963 = U64_to_str(self->count);
        (void)_t963;
        Array_set(_va18, &(U64){_t962}, _t963);
        ;
        U64 _t964 = 4;
        (void)_t964;
        Str *_t965 = Str_lit(")", 1ULL);
        (void)_t965;
        Array_set(_va18, &(U64){_t964}, _t965);
        ;
        Str *_t966 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t966;
        panic(_t966, _va18);
        Str_delete(_t966, &(Bool){1});
    }
    ;
    U64 *_t968 = malloc(sizeof(U64)); *_t968 = U64_mul(DEREF(i), self->elem_size);
    (void)_t968;
    void *_t969 = ptr_add(self->data, DEREF(_t968));
    (void)_t969;
    U64_delete(_t968, &(Bool){1});
    return _t969;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t983; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t983 = *_hp; free(_hp); }
    (void)_t983;
    Bool _t984 = Bool_not(_t983);
    (void)_t984;
    ;
    if (_t984) {
        {
            U64 _fi970 = 0;
            (void)_fi970;
            while (1) {
                U64 _t972 = 0;
                (void)_t972;
                Range *_t973 = Range_new(_t972, self->count);
                (void)_t973;
                ;
                U64 _t974; { U64 *_hp = (U64 *)Range_len(_t973); _t974 = *_hp; free(_hp); }
                (void)_t974;
                Range_delete(_t973, &(Bool){1});
                Bool _wcond971; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi970}, &(U64){_t974}); _wcond971 = *_hp; free(_hp); }
                (void)_wcond971;
                ;
                if (_wcond971) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t975 = 0;
                (void)_t975;
                Range *_t976 = Range_new(_t975, self->count);
                (void)_t976;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t976, _fi970); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t976, &(Bool){1});
                U64 _t977 = 1;
                (void)_t977;
                U64 _t978 = U64_add(_fi970, _t977);
                (void)_t978;
                ;
                _fi970 = _t978;
                ;
                U64 *_t979 = malloc(sizeof(U64)); *_t979 = U64_mul(i, self->elem_size);
                (void)_t979;
                ;
                void *_t980 = ptr_add(self->data, DEREF(_t979));
                (void)_t980;
                Bool _t981 = 0;
                (void)_t981;
                dyn_call_delete(&self->elem_type, _t980, &(Bool){_t981});
                U64_delete(_t979, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t985; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t985 = *_hp; free(_hp); }
    (void)_t985;
    Bool _t986 = Bool_not(_t985);
    (void)_t986;
    ;
    if (_t986) {
        Bool _t982 = 0;
        (void)_t982;
        Str_delete(&self->elem_type, &(Bool){_t982});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1000 = U64_mul(self->cap, self->elem_size);
    (void)_t1000;
    U8 *new_data = malloc(_t1000);
    (void)new_data;
    ;
    {
        U64 _fi987 = 0;
        (void)_fi987;
        while (1) {
            U64 _t989 = 0;
            (void)_t989;
            Range *_t990 = Range_new(_t989, self->count);
            (void)_t990;
            ;
            U64 _t991; { U64 *_hp = (U64 *)Range_len(_t990); _t991 = *_hp; free(_hp); }
            (void)_t991;
            Range_delete(_t990, &(Bool){1});
            Bool _wcond988; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi987}, &(U64){_t991}); _wcond988 = *_hp; free(_hp); }
            (void)_wcond988;
            ;
            if (_wcond988) {
            } else {
                ;
                break;
            }
            ;
            U64 _t992 = 0;
            (void)_t992;
            Range *_t993 = Range_new(_t992, self->count);
            (void)_t993;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t993, _fi987); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t993, &(Bool){1});
            U64 _t994 = 1;
            (void)_t994;
            U64 _t995 = U64_add(_fi987, _t994);
            (void)_t995;
            ;
            _fi987 = _t995;
            ;
            U64 *_t996 = malloc(sizeof(U64)); *_t996 = U64_mul(i, self->elem_size);
            (void)_t996;
            void *_t997 = ptr_add(self->data, DEREF(_t996));
            (void)_t997;
            void *cloned = dyn_call_clone(&self->elem_type, _t997);
            (void)cloned;
            U64_delete(_t996, &(Bool){1});
            U64 *_t998 = malloc(sizeof(U64)); *_t998 = U64_mul(i, self->elem_size);
            (void)_t998;
            ;
            void *_t999 = ptr_add(new_data, DEREF(_t998));
            (void)_t999;
            memcpy(_t999, cloned, self->elem_size);
            U64_delete(_t998, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1001 = malloc(sizeof(Vec));
    _t1001->data = new_data;
    _t1001->count = self->count;
    _t1001->cap = self->cap;
    _t1001->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1001->elem_type = *_ca; free(_ca); }
    (void)_t1001;
    return _t1001;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    (void)s;
    (void)delim;
    Str *_t1019 = Str_lit("Str", 3ULL);
    (void)_t1019;
    U64 _t1020; { U64 *_hp = (U64 *)Str_size(); _t1020 = *_hp; free(_hp); }
    (void)_t1020;
    Vec *parts = Vec_new(_t1019, &(U64){_t1020});
    (void)parts;
    Str_delete(_t1019, &(Bool){1});
    ;
    U64 _t1021; { U64 *_hp = (U64 *)Str_len(delim); _t1021 = *_hp; free(_hp); }
    (void)_t1021;
    U64 _t1022 = 0;
    (void)_t1022;
    Bool _t1023 = U64_eq(_t1021, _t1022);
    (void)_t1023;
    ;
    ;
    if (_t1023) {
        Str *_t1003 = Str_clone(s);
        (void)_t1003;
        Vec_push(parts, _t1003);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1013; { U64 *_hp = (U64 *)Str_len(s); _t1013 = *_hp; free(_hp); }
        (void)_t1013;
        U64 _t1014; { U64 *_hp = (U64 *)Str_len(delim); _t1014 = *_hp; free(_hp); }
        (void)_t1014;
        U64 _t1015 = U64_sub(_t1013, _t1014);
        (void)_t1015;
        ;
        ;
        Bool _wcond1004; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1015}); _wcond1004 = *_hp; free(_hp); }
        (void)_wcond1004;
        ;
        if (_wcond1004) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1016; { U64 *_hp = (U64 *)Str_len(delim); _t1016 = *_hp; free(_hp); }
        (void)_t1016;
        Str *_t1017 = Str_substr(s, &(U64){pos}, &(U64){_t1016});
        (void)_t1017;
        ;
        Bool _t1018; { Bool *_hp = (Bool *)Str_eq(_t1017, delim); _t1018 = *_hp; free(_hp); }
        (void)_t1018;
        Str_delete(_t1017, &(Bool){1});
        if (_t1018) {
            U64 _t1005 = U64_sub(pos, start);
            (void)_t1005;
            Str *_t1006 = Str_substr(s, &(U64){start}, &(U64){_t1005});
            (void)_t1006;
            ;
            Str *_t1007 = Str_clone(_t1006);
            (void)_t1007;
            Str_delete(_t1006, &(Bool){1});
            Vec_push(parts, _t1007);
            U64 _t1008; { U64 *_hp = (U64 *)Str_len(delim); _t1008 = *_hp; free(_hp); }
            (void)_t1008;
            U64 _t1009 = U64_add(pos, _t1008);
            (void)_t1009;
            ;
            start = _t1009;
            ;
            U64 _t1010 = U64_clone(&(U64){start});
            (void)_t1010;
            pos = _t1010;
            ;
        } else {
            U64 _t1011 = 1;
            (void)_t1011;
            U64 _t1012 = U64_add(pos, _t1011);
            (void)_t1012;
            ;
            pos = _t1012;
            ;
        }
        ;
    }
    ;
    U64 _t1024; { U64 *_hp = (U64 *)Str_len(s); _t1024 = *_hp; free(_hp); }
    (void)_t1024;
    U64 _t1025 = U64_sub(_t1024, start);
    (void)_t1025;
    ;
    Str *_t1026 = Str_substr(s, &(U64){start}, &(U64){_t1025});
    (void)_t1026;
    ;
    ;
    Str *_t1027 = Str_clone(_t1026);
    (void)_t1027;
    Str_delete(_t1026, &(Bool){1});
    Vec_push(parts, _t1027);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1035; { U64 *_hp = (U64 *)Vec_len(parts); _t1035 = *_hp; free(_hp); }
    (void)_t1035;
    U64 _t1036 = 0;
    (void)_t1036;
    Bool _t1037 = U64_eq(_t1035, _t1036);
    (void)_t1037;
    ;
    ;
    if (_t1037) {
        Str *_t1028 = Str_lit("", 0ULL);
        (void)_t1028;
        ;
        return _t1028;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        U64 _t1030; { U64 *_hp = (U64 *)Vec_len(parts); _t1030 = *_hp; free(_hp); }
        (void)_t1030;
        Bool _wcond1029; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1030}); _wcond1029 = *_hp; free(_hp); }
        (void)_wcond1029;
        ;
        if (_wcond1029) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1031 = 0;
        (void)_t1031;
        Bool _t1032; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1031}); _t1032 = *_hp; free(_hp); }
        (void)_t1032;
        ;
        if (_t1032) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        (void)p;
        result = Str_concat(result, p);
        U64 _t1033 = 1;
        (void)_t1033;
        U64 _t1034 = U64_add(DEREF(i), _t1033);
        (void)_t1034;
        ;
        *i = _t1034;
        ;
    }
    U64_delete(i, &(Bool){1});
    return result;
}

Tuple * Tuple_new(void) {
    U64 _t1038 = 8;
    (void)_t1038;
    Str *_t1039 = Str_lit("Str", 3ULL);
    (void)_t1039;
    U64 _t1040; { U64 *_hp = (U64 *)Str_size(); _t1040 = *_hp; free(_hp); }
    (void)_t1040;
    Str *_t1041 = Str_lit("U64", 3ULL);
    (void)_t1041;
    U64 _t1042; { U64 *_hp = (U64 *)U64_size(); _t1042 = *_hp; free(_hp); }
    (void)_t1042;
    void *_t1043 = malloc(_t1038);
    (void)_t1043;
    ;
    U64 _t1044 = 0;
    (void)_t1044;
    I64 _t1045 = 8;
    (void)_t1045;
    Tuple *_t1046 = malloc(sizeof(Tuple));
    _t1046->data = _t1043;
    _t1046->total_size = _t1044;
    _t1046->cap = _t1045;
    { Vec *_ca = Vec_new(_t1039, &(U64){_t1040}); _t1046->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1041, &(U64){_t1042}); _t1046->type_sizes = *_ca; free(_ca); }
    (void)_t1046;
    Str_delete(_t1039, &(Bool){1});
    ;
    Str_delete(_t1041, &(Bool){1});
    ;
    ;
    ;
    return _t1046;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1047; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1047 = *_hp; free(_hp); }
    (void)_t1047;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1047; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1054; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1054 = *_hp; free(_hp); }
    (void)_t1054;
    if (_t1054) {
        U64 _t1051 = 2;
        (void)_t1051;
        U64 new_cap = U64_mul(self->cap, _t1051);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1048; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1048 = *_hp; free(_hp); }
            (void)_wcond1048;
            if (_wcond1048) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1049 = 2;
            (void)_t1049;
            U64 _t1050 = U64_mul(new_cap, _t1049);
            (void)_t1050;
            ;
            new_cap = _t1050;
            ;
        }
        void *_t1052 = realloc(self->data, new_cap);
        (void)_t1052;
        self->data = _t1052;
        U64 _t1053 = U64_clone(&(U64){new_cap});
        (void)_t1053;
        ;
        self->cap = _t1053;
        ;
    }
    ;
    void *_t1055 = ptr_add(self->data, self->total_size);
    (void)_t1055;
    memcpy(_t1055, val, DEREF(elem_size));
    free(val);
    Str *_t1056 = Str_clone(elem_type);
    (void)_t1056;
    Vec_push(&self->type_names, _t1056);
    U64 _t1057 = U64_clone(elem_size);
    (void)_t1057;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1057; _oa; }));
    U64 _t1058 = U64_clone(&(U64){new_total});
    (void)_t1058;
    ;
    self->total_size = _t1058;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1078; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1078 = *_hp; free(_hp); }
    (void)_t1078;
    Bool _t1079; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1078}); _t1079 = *_hp; free(_hp); }
    (void)_t1079;
    ;
    if (_t1079) {
        Str *_t1059 = Str_lit("Str", 3ULL);
        (void)_t1059;
        U64 _t1060; { U64 *_hp = (U64 *)Str_size(); _t1060 = *_hp; free(_hp); }
        (void)_t1060;
        U64 _t1061 = 5;
        (void)_t1061;
        Array *_va19 = Array_new(_t1059, &(U64){_t1060}, &(U64){_t1061});
        (void)_va19;
        Str_delete(_t1059, &(Bool){1});
        ;
        ;
        U64 _t1062 = 0;
        (void)_t1062;
        Str *_t1063 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1063;
        Array_set(_va19, &(U64){_t1062}, _t1063);
        ;
        U64 _t1064 = 1;
        (void)_t1064;
        Str *_t1065 = U64_to_str(DEREF(i));
        (void)_t1065;
        Array_set(_va19, &(U64){_t1064}, _t1065);
        ;
        U64 _t1066 = 2;
        (void)_t1066;
        Str *_t1067 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1067;
        Array_set(_va19, &(U64){_t1066}, _t1067);
        ;
        U64 _t1068; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1068 = *_hp; free(_hp); }
        (void)_t1068;
        U64 _t1069 = 3;
        (void)_t1069;
        Str *_t1070 = U64_to_str(_t1068);
        (void)_t1070;
        ;
        Array_set(_va19, &(U64){_t1069}, _t1070);
        ;
        U64 _t1071 = 4;
        (void)_t1071;
        Str *_t1072 = Str_lit(")", 1ULL);
        (void)_t1072;
        Array_set(_va19, &(U64){_t1071}, _t1072);
        ;
        Str *_t1073 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1073;
        panic(_t1073, _va19);
        Str_delete(_t1073, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    U64 *j = malloc(sizeof(U64));
    *j = 0;
    (void)j;
    while (1) {
        Bool _wcond1074; { Bool *_hp = (Bool *)U64_lt(j, i); _wcond1074 = *_hp; free(_hp); }
        (void)_wcond1074;
        if (_wcond1074) {
        } else {
            ;
            break;
        }
        ;
        U64 *sz = Vec_get(&self->type_sizes, j);
        (void)sz;
        U64 _t1075 = U64_add(DEREF(offset), DEREF(sz));
        (void)_t1075;
        *offset = _t1075;
        ;
        U64 _t1076 = 1;
        (void)_t1076;
        U64 _t1077 = U64_add(DEREF(j), _t1076);
        (void)_t1077;
        ;
        *j = _t1077;
        ;
    }
    U64_delete(j, &(Bool){1});
    void *_t1080 = ptr_add(self->data, DEREF(offset));
    (void)_t1080;
    U64_delete(offset, &(Bool){1});
    return _t1080;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1081 = Vec_get(&self->type_names, i);
    (void)_t1081;
    return _t1081;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1082 = Vec_get(&self->type_sizes, i);
    (void)_t1082;
    return _t1082;
}

void Tuple_delete(Tuple * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        U64 _t1084; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1084 = *_hp; free(_hp); }
        (void)_t1084;
        Bool _wcond1083; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1084}); _wcond1083 = *_hp; free(_hp); }
        (void)_wcond1083;
        ;
        if (_wcond1083) {
        } else {
            ;
            break;
        }
        ;
        Str *tn = Vec_get(&self->type_names, i);
        (void)tn;
        U64 *ts = Vec_get(&self->type_sizes, i);
        (void)ts;
        void *_t1085 = ptr_add(self->data, DEREF(offset));
        (void)_t1085;
        Bool _t1086 = 0;
        (void)_t1086;
        dyn_call_delete(tn, _t1085, &(Bool){_t1086});
        ;
        U64 _t1087 = U64_add(DEREF(offset), DEREF(ts));
        (void)_t1087;
        *offset = _t1087;
        ;
        U64 _t1088 = 1;
        (void)_t1088;
        U64 _t1089 = U64_add(DEREF(i), _t1088);
        (void)_t1089;
        ;
        *i = _t1089;
        ;
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1090 = 0;
    (void)_t1090;
    Vec_delete(&self->type_names, &(Bool){_t1090});
    ;
    Bool _t1091 = 0;
    (void)_t1091;
    Vec_delete(&self->type_sizes, &(Bool){_t1091});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1101 = 0;
    (void)_t1101;
    Bool _t1102 = U64_eq(new_cap, _t1101);
    (void)_t1102;
    ;
    if (_t1102) {
        I64 _t1092 = 8;
        (void)_t1092;
        U64 _t1093; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1092}); _t1093 = *_hp; free(_hp); }
        (void)_t1093;
        ;
        new_cap = _t1093;
        ;
    }
    ;
    U8 *new_data = malloc(new_cap);
    (void)new_data;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        U64 _t1095; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1095 = *_hp; free(_hp); }
        (void)_t1095;
        Bool _wcond1094; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1095}); _wcond1094 = *_hp; free(_hp); }
        (void)_wcond1094;
        ;
        if (_wcond1094) {
        } else {
            ;
            break;
        }
        ;
        Str *tn = Vec_get(&self->type_names, i);
        (void)tn;
        U64 *ts = Vec_get(&self->type_sizes, i);
        (void)ts;
        void *_t1096 = ptr_add(self->data, DEREF(offset));
        (void)_t1096;
        void *cloned = dyn_call_clone(tn, _t1096);
        (void)cloned;
        void *_t1097 = ptr_add(new_data, DEREF(offset));
        (void)_t1097;
        memcpy(_t1097, cloned, DEREF(ts));
        free(cloned);
        U64 _t1098 = U64_add(DEREF(offset), DEREF(ts));
        (void)_t1098;
        *offset = _t1098;
        ;
        U64 _t1099 = 1;
        (void)_t1099;
        U64 _t1100 = U64_add(DEREF(i), _t1099);
        (void)_t1100;
        ;
        *i = _t1100;
        ;
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    U64 _t1103 = U64_clone(&(U64){new_cap});
    (void)_t1103;
    ;
    Vec *_t1104 = Vec_clone(&self->type_names);
    (void)_t1104;
    Vec *_t1105 = Vec_clone(&self->type_sizes);
    (void)_t1105;
    Tuple *_t1106 = malloc(sizeof(Tuple));
    _t1106->data = new_data;
    _t1106->total_size = self->total_size;
    _t1106->cap = _t1103;
    { Vec *_ca = Vec_clone(_t1104); _t1106->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1105); _t1106->type_sizes = *_ca; free(_ca); }
    (void)_t1106;
    ;
    Vec_delete(_t1104, &(Bool){1});
    Vec_delete(_t1105, &(Bool){1});
    return _t1106;
}

U64 *Tuple_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Tuple);
    return r;
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
    (void)other;
    Bool _t1173; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t1173 = *_hp; free(_hp); }
    (void)_t1173;
    if (_t1173) {
        Bool _t1108; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t1108 = *_hp; free(_hp); }
        (void)_t1108;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1108; return _r; }
    }
    ;
    Bool _t1174; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t1174 = *_hp; free(_hp); }
    (void)_t1174;
    if (_t1174) {
        Bool _t1109; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t1109 = *_hp; free(_hp); }
        (void)_t1109;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1109; return _r; }
    }
    ;
    Bool _t1175; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t1175 = *_hp; free(_hp); }
    (void)_t1175;
    if (_t1175) {
        Bool _t1110; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t1110 = *_hp; free(_hp); }
        (void)_t1110;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1110; return _r; }
    }
    ;
    Bool _t1176; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t1176 = *_hp; free(_hp); }
    (void)_t1176;
    if (_t1176) {
        Bool _t1111; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t1111 = *_hp; free(_hp); }
        (void)_t1111;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1111; return _r; }
    }
    ;
    Bool _t1177; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t1177 = *_hp; free(_hp); }
    (void)_t1177;
    if (_t1177) {
        Bool _t1112; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t1112 = *_hp; free(_hp); }
        (void)_t1112;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1112; return _r; }
    }
    ;
    Bool _t1178; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t1178 = *_hp; free(_hp); }
    (void)_t1178;
    if (_t1178) {
        Bool _t1113; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t1113 = *_hp; free(_hp); }
        (void)_t1113;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1113; return _r; }
    }
    ;
    Bool _t1179; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t1179 = *_hp; free(_hp); }
    (void)_t1179;
    if (_t1179) {
        Bool _t1114; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t1114 = *_hp; free(_hp); }
        (void)_t1114;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1114; return _r; }
    }
    ;
    Bool _t1180; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t1180 = *_hp; free(_hp); }
    (void)_t1180;
    if (_t1180) {
        Bool _t1115; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t1115 = *_hp; free(_hp); }
        (void)_t1115;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1115; return _r; }
    }
    ;
    Bool _t1181; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t1181 = *_hp; free(_hp); }
    (void)_t1181;
    if (_t1181) {
        Bool _t1116; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t1116 = *_hp; free(_hp); }
        (void)_t1116;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1116; return _r; }
    }
    ;
    Bool _t1182; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t1182 = *_hp; free(_hp); }
    (void)_t1182;
    if (_t1182) {
        Bool _t1117; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t1117 = *_hp; free(_hp); }
        (void)_t1117;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1117; return _r; }
    }
    ;
    Bool _t1183; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t1183 = *_hp; free(_hp); }
    (void)_t1183;
    if (_t1183) {
        Bool _t1118; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t1118 = *_hp; free(_hp); }
        (void)_t1118;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1118; return _r; }
    }
    ;
    Bool _t1184; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t1184 = *_hp; free(_hp); }
    (void)_t1184;
    if (_t1184) {
        Bool _t1119; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t1119 = *_hp; free(_hp); }
        (void)_t1119;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1119; return _r; }
    }
    ;
    Bool _t1185; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t1185 = *_hp; free(_hp); }
    (void)_t1185;
    if (_t1185) {
        Bool _t1120; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t1120 = *_hp; free(_hp); }
        (void)_t1120;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1120; return _r; }
    }
    ;
    Bool _t1186; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t1186 = *_hp; free(_hp); }
    (void)_t1186;
    if (_t1186) {
        Bool _t1121; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t1121 = *_hp; free(_hp); }
        (void)_t1121;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1121; return _r; }
    }
    ;
    Bool _t1187; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t1187 = *_hp; free(_hp); }
    (void)_t1187;
    if (_t1187) {
        Bool _t1122; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t1122 = *_hp; free(_hp); }
        (void)_t1122;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1122; return _r; }
    }
    ;
    Bool _t1188; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t1188 = *_hp; free(_hp); }
    (void)_t1188;
    if (_t1188) {
        Bool _t1123; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t1123 = *_hp; free(_hp); }
        (void)_t1123;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1123; return _r; }
    }
    ;
    Bool _t1189; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t1189 = *_hp; free(_hp); }
    (void)_t1189;
    if (_t1189) {
        Bool _t1124; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t1124 = *_hp; free(_hp); }
        (void)_t1124;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1124; return _r; }
    }
    ;
    Bool _t1190; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t1190 = *_hp; free(_hp); }
    (void)_t1190;
    if (_t1190) {
        Bool _t1125; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t1125 = *_hp; free(_hp); }
        (void)_t1125;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1125; return _r; }
    }
    ;
    Bool _t1191; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t1191 = *_hp; free(_hp); }
    (void)_t1191;
    if (_t1191) {
        Bool _t1126; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t1126 = *_hp; free(_hp); }
        (void)_t1126;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1126; return _r; }
    }
    ;
    Bool _t1192; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t1192 = *_hp; free(_hp); }
    (void)_t1192;
    if (_t1192) {
        Bool _t1127; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t1127 = *_hp; free(_hp); }
        (void)_t1127;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1127; return _r; }
    }
    ;
    Bool _t1193; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t1193 = *_hp; free(_hp); }
    (void)_t1193;
    if (_t1193) {
        Bool _t1128; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t1128 = *_hp; free(_hp); }
        (void)_t1128;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1128; return _r; }
    }
    ;
    Bool _t1194; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t1194 = *_hp; free(_hp); }
    (void)_t1194;
    if (_t1194) {
        Bool _t1129; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t1129 = *_hp; free(_hp); }
        (void)_t1129;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1129; return _r; }
    }
    ;
    Bool _t1195; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t1195 = *_hp; free(_hp); }
    (void)_t1195;
    if (_t1195) {
        Bool _t1130; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t1130 = *_hp; free(_hp); }
        (void)_t1130;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1130; return _r; }
    }
    ;
    Bool _t1196; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t1196 = *_hp; free(_hp); }
    (void)_t1196;
    if (_t1196) {
        Bool _t1131; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t1131 = *_hp; free(_hp); }
        (void)_t1131;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1131; return _r; }
    }
    ;
    Bool _t1197; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t1197 = *_hp; free(_hp); }
    (void)_t1197;
    if (_t1197) {
        Bool _t1132; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t1132 = *_hp; free(_hp); }
        (void)_t1132;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1132; return _r; }
    }
    ;
    Bool _t1198; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t1198 = *_hp; free(_hp); }
    (void)_t1198;
    if (_t1198) {
        Bool _t1133; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t1133 = *_hp; free(_hp); }
        (void)_t1133;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1133; return _r; }
    }
    ;
    Bool _t1199; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t1199 = *_hp; free(_hp); }
    (void)_t1199;
    if (_t1199) {
        Bool _t1134; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t1134 = *_hp; free(_hp); }
        (void)_t1134;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1134; return _r; }
    }
    ;
    Bool _t1200; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t1200 = *_hp; free(_hp); }
    (void)_t1200;
    if (_t1200) {
        Bool _t1135; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t1135 = *_hp; free(_hp); }
        (void)_t1135;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1135; return _r; }
    }
    ;
    Bool _t1201; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t1201 = *_hp; free(_hp); }
    (void)_t1201;
    if (_t1201) {
        Bool _t1136; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t1136 = *_hp; free(_hp); }
        (void)_t1136;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1136; return _r; }
    }
    ;
    Bool _t1202; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t1202 = *_hp; free(_hp); }
    (void)_t1202;
    if (_t1202) {
        Bool _t1137; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t1137 = *_hp; free(_hp); }
        (void)_t1137;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1137; return _r; }
    }
    ;
    Bool _t1203; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t1203 = *_hp; free(_hp); }
    (void)_t1203;
    if (_t1203) {
        Bool _t1138; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t1138 = *_hp; free(_hp); }
        (void)_t1138;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1138; return _r; }
    }
    ;
    Bool _t1204; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t1204 = *_hp; free(_hp); }
    (void)_t1204;
    if (_t1204) {
        Bool _t1139; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t1139 = *_hp; free(_hp); }
        (void)_t1139;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1139; return _r; }
    }
    ;
    Bool _t1205; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t1205 = *_hp; free(_hp); }
    (void)_t1205;
    if (_t1205) {
        Bool _t1140; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t1140 = *_hp; free(_hp); }
        (void)_t1140;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1140; return _r; }
    }
    ;
    Bool _t1206; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t1206 = *_hp; free(_hp); }
    (void)_t1206;
    if (_t1206) {
        Bool _t1141; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t1141 = *_hp; free(_hp); }
        (void)_t1141;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1141; return _r; }
    }
    ;
    Bool _t1207; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t1207 = *_hp; free(_hp); }
    (void)_t1207;
    if (_t1207) {
        Bool _t1142; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t1142 = *_hp; free(_hp); }
        (void)_t1142;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1142; return _r; }
    }
    ;
    Bool _t1208; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t1208 = *_hp; free(_hp); }
    (void)_t1208;
    if (_t1208) {
        Bool _t1143; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t1143 = *_hp; free(_hp); }
        (void)_t1143;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1143; return _r; }
    }
    ;
    Bool _t1209; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t1209 = *_hp; free(_hp); }
    (void)_t1209;
    if (_t1209) {
        Bool _t1144; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t1144 = *_hp; free(_hp); }
        (void)_t1144;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1144; return _r; }
    }
    ;
    Bool _t1210; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t1210 = *_hp; free(_hp); }
    (void)_t1210;
    if (_t1210) {
        Bool _t1145; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t1145 = *_hp; free(_hp); }
        (void)_t1145;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1145; return _r; }
    }
    ;
    Bool _t1211; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t1211 = *_hp; free(_hp); }
    (void)_t1211;
    if (_t1211) {
        Bool _t1146; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t1146 = *_hp; free(_hp); }
        (void)_t1146;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1146; return _r; }
    }
    ;
    Bool _t1212; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t1212 = *_hp; free(_hp); }
    (void)_t1212;
    if (_t1212) {
        Bool _t1147; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t1147 = *_hp; free(_hp); }
        (void)_t1147;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1147; return _r; }
    }
    ;
    Bool _t1213; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t1213 = *_hp; free(_hp); }
    (void)_t1213;
    if (_t1213) {
        Bool _t1148; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t1148 = *_hp; free(_hp); }
        (void)_t1148;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1148; return _r; }
    }
    ;
    Bool _t1214; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t1214 = *_hp; free(_hp); }
    (void)_t1214;
    if (_t1214) {
        Bool _t1149; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t1149 = *_hp; free(_hp); }
        (void)_t1149;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1149; return _r; }
    }
    ;
    Bool _t1215; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t1215 = *_hp; free(_hp); }
    (void)_t1215;
    if (_t1215) {
        Bool _t1150; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t1150 = *_hp; free(_hp); }
        (void)_t1150;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1150; return _r; }
    }
    ;
    Bool _t1216; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t1216 = *_hp; free(_hp); }
    (void)_t1216;
    if (_t1216) {
        Bool _t1151; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t1151 = *_hp; free(_hp); }
        (void)_t1151;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1151; return _r; }
    }
    ;
    Bool _t1217; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t1217 = *_hp; free(_hp); }
    (void)_t1217;
    if (_t1217) {
        Bool _t1152; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t1152 = *_hp; free(_hp); }
        (void)_t1152;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1152; return _r; }
    }
    ;
    Bool _t1218; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t1218 = *_hp; free(_hp); }
    (void)_t1218;
    if (_t1218) {
        Bool _t1153; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t1153 = *_hp; free(_hp); }
        (void)_t1153;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1153; return _r; }
    }
    ;
    Bool _t1219; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t1219 = *_hp; free(_hp); }
    (void)_t1219;
    if (_t1219) {
        Bool _t1154; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t1154 = *_hp; free(_hp); }
        (void)_t1154;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1154; return _r; }
    }
    ;
    Bool _t1220; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t1220 = *_hp; free(_hp); }
    (void)_t1220;
    if (_t1220) {
        Bool _t1155; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t1155 = *_hp; free(_hp); }
        (void)_t1155;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1155; return _r; }
    }
    ;
    Bool _t1221; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t1221 = *_hp; free(_hp); }
    (void)_t1221;
    if (_t1221) {
        Bool _t1156; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t1156 = *_hp; free(_hp); }
        (void)_t1156;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1156; return _r; }
    }
    ;
    Bool _t1222; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t1222 = *_hp; free(_hp); }
    (void)_t1222;
    if (_t1222) {
        Bool _t1157; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t1157 = *_hp; free(_hp); }
        (void)_t1157;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1157; return _r; }
    }
    ;
    Bool _t1223; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t1223 = *_hp; free(_hp); }
    (void)_t1223;
    if (_t1223) {
        Bool _t1158; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t1158 = *_hp; free(_hp); }
        (void)_t1158;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1158; return _r; }
    }
    ;
    Bool _t1224; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t1224 = *_hp; free(_hp); }
    (void)_t1224;
    if (_t1224) {
        Bool _t1159; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t1159 = *_hp; free(_hp); }
        (void)_t1159;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1159; return _r; }
    }
    ;
    Bool _t1225; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t1225 = *_hp; free(_hp); }
    (void)_t1225;
    if (_t1225) {
        Bool _t1160; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t1160 = *_hp; free(_hp); }
        (void)_t1160;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1160; return _r; }
    }
    ;
    Bool _t1226; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t1226 = *_hp; free(_hp); }
    (void)_t1226;
    if (_t1226) {
        Bool _t1161; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t1161 = *_hp; free(_hp); }
        (void)_t1161;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1161; return _r; }
    }
    ;
    Bool _t1227; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t1227 = *_hp; free(_hp); }
    (void)_t1227;
    if (_t1227) {
        Bool _t1162; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t1162 = *_hp; free(_hp); }
        (void)_t1162;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1162; return _r; }
    }
    ;
    Bool _t1228; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t1228 = *_hp; free(_hp); }
    (void)_t1228;
    if (_t1228) {
        Bool _t1163; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t1163 = *_hp; free(_hp); }
        (void)_t1163;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1163; return _r; }
    }
    ;
    Bool _t1229; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t1229 = *_hp; free(_hp); }
    (void)_t1229;
    if (_t1229) {
        Bool _t1164; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t1164 = *_hp; free(_hp); }
        (void)_t1164;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1164; return _r; }
    }
    ;
    Bool _t1230; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t1230 = *_hp; free(_hp); }
    (void)_t1230;
    if (_t1230) {
        Bool _t1165; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t1165 = *_hp; free(_hp); }
        (void)_t1165;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1165; return _r; }
    }
    ;
    Bool _t1231; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t1231 = *_hp; free(_hp); }
    (void)_t1231;
    if (_t1231) {
        Bool _t1166; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t1166 = *_hp; free(_hp); }
        (void)_t1166;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1166; return _r; }
    }
    ;
    Bool _t1232; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t1232 = *_hp; free(_hp); }
    (void)_t1232;
    if (_t1232) {
        Bool _t1167; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t1167 = *_hp; free(_hp); }
        (void)_t1167;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1167; return _r; }
    }
    ;
    Bool _t1233; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t1233 = *_hp; free(_hp); }
    (void)_t1233;
    if (_t1233) {
        Bool _t1168; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t1168 = *_hp; free(_hp); }
        (void)_t1168;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1168; return _r; }
    }
    ;
    Bool _t1234; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t1234 = *_hp; free(_hp); }
    (void)_t1234;
    if (_t1234) {
        Bool _t1169; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t1169 = *_hp; free(_hp); }
        (void)_t1169;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1169; return _r; }
    }
    ;
    Bool _t1235; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t1235 = *_hp; free(_hp); }
    (void)_t1235;
    if (_t1235) {
        Bool _t1170; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t1170 = *_hp; free(_hp); }
        (void)_t1170;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1170; return _r; }
    }
    ;
    Bool _t1236; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t1236 = *_hp; free(_hp); }
    (void)_t1236;
    if (_t1236) {
        Bool _t1171; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t1171 = *_hp; free(_hp); }
        (void)_t1171;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1171; return _r; }
    }
    ;
    Bool _t1237; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t1237 = *_hp; free(_hp); }
    (void)_t1237;
    if (_t1237) {
        Bool _t1172; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t1172 = *_hp; free(_hp); }
        (void)_t1172;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1172; return _r; }
    }
    ;
    Bool _t1238 = 0;
    (void)_t1238;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1238; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1239; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1239 = *_hp; free(_hp); }
    (void)_t1239;
    if (_t1239) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1240; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1240 = *_hp; free(_hp); }
    (void)_t1240;
    if (_t1240) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1241; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1241 = *_hp; free(_hp); }
    (void)_t1241;
    if (_t1241) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1242; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1242 = *_hp; free(_hp); }
    (void)_t1242;
    if (_t1242) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1243; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1243 = *_hp; free(_hp); }
    (void)_t1243;
    if (_t1243) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1244; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1244 = *_hp; free(_hp); }
    (void)_t1244;
    if (_t1244) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1245; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1245 = *_hp; free(_hp); }
    (void)_t1245;
    if (_t1245) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1246; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1246 = *_hp; free(_hp); }
    (void)_t1246;
    if (_t1246) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1247; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1247 = *_hp; free(_hp); }
    (void)_t1247;
    if (_t1247) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1248; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1248 = *_hp; free(_hp); }
    (void)_t1248;
    if (_t1248) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1249; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1249 = *_hp; free(_hp); }
    (void)_t1249;
    if (_t1249) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1250; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1250 = *_hp; free(_hp); }
    (void)_t1250;
    if (_t1250) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1251; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1251 = *_hp; free(_hp); }
    (void)_t1251;
    if (_t1251) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1252; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1252 = *_hp; free(_hp); }
    (void)_t1252;
    if (_t1252) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1253; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1253 = *_hp; free(_hp); }
    (void)_t1253;
    if (_t1253) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1254; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1254 = *_hp; free(_hp); }
    (void)_t1254;
    if (_t1254) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1255; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1255 = *_hp; free(_hp); }
    (void)_t1255;
    if (_t1255) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1256; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1256 = *_hp; free(_hp); }
    (void)_t1256;
    if (_t1256) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1257; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1257 = *_hp; free(_hp); }
    (void)_t1257;
    if (_t1257) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1258; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1258 = *_hp; free(_hp); }
    (void)_t1258;
    if (_t1258) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1259; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1259 = *_hp; free(_hp); }
    (void)_t1259;
    if (_t1259) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1260; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1260 = *_hp; free(_hp); }
    (void)_t1260;
    if (_t1260) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1261; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1261 = *_hp; free(_hp); }
    (void)_t1261;
    if (_t1261) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1262; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1262 = *_hp; free(_hp); }
    (void)_t1262;
    if (_t1262) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1263; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1263 = *_hp; free(_hp); }
    (void)_t1263;
    if (_t1263) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1264; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1264 = *_hp; free(_hp); }
    (void)_t1264;
    if (_t1264) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1265; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1265 = *_hp; free(_hp); }
    (void)_t1265;
    if (_t1265) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1266; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1266 = *_hp; free(_hp); }
    (void)_t1266;
    if (_t1266) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1267; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1267 = *_hp; free(_hp); }
    (void)_t1267;
    if (_t1267) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1268; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1268 = *_hp; free(_hp); }
    (void)_t1268;
    if (_t1268) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1269; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1269 = *_hp; free(_hp); }
    (void)_t1269;
    if (_t1269) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1270; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1270 = *_hp; free(_hp); }
    (void)_t1270;
    if (_t1270) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1271; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1271 = *_hp; free(_hp); }
    (void)_t1271;
    if (_t1271) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1272; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1272 = *_hp; free(_hp); }
    (void)_t1272;
    if (_t1272) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t1273; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1273 = *_hp; free(_hp); }
    (void)_t1273;
    if (_t1273) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1274; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1274 = *_hp; free(_hp); }
    (void)_t1274;
    if (_t1274) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1275; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1275 = *_hp; free(_hp); }
    (void)_t1275;
    if (_t1275) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1276; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1276 = *_hp; free(_hp); }
    (void)_t1276;
    if (_t1276) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1277; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1277 = *_hp; free(_hp); }
    (void)_t1277;
    if (_t1277) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1278; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1278 = *_hp; free(_hp); }
    (void)_t1278;
    if (_t1278) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1279; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1279 = *_hp; free(_hp); }
    (void)_t1279;
    if (_t1279) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1280; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1280 = *_hp; free(_hp); }
    (void)_t1280;
    if (_t1280) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1281; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1281 = *_hp; free(_hp); }
    (void)_t1281;
    if (_t1281) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1282; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1282 = *_hp; free(_hp); }
    (void)_t1282;
    if (_t1282) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1283; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1283 = *_hp; free(_hp); }
    (void)_t1283;
    if (_t1283) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1284; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1284 = *_hp; free(_hp); }
    (void)_t1284;
    if (_t1284) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1285; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1285 = *_hp; free(_hp); }
    (void)_t1285;
    if (_t1285) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1286; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1286 = *_hp; free(_hp); }
    (void)_t1286;
    if (_t1286) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1287; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1287 = *_hp; free(_hp); }
    (void)_t1287;
    if (_t1287) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1288; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1288 = *_hp; free(_hp); }
    (void)_t1288;
    if (_t1288) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1289; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1289 = *_hp; free(_hp); }
    (void)_t1289;
    if (_t1289) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1290; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1290 = *_hp; free(_hp); }
    (void)_t1290;
    if (_t1290) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1291; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1291 = *_hp; free(_hp); }
    (void)_t1291;
    if (_t1291) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1292; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1292 = *_hp; free(_hp); }
    (void)_t1292;
    if (_t1292) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1293; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1293 = *_hp; free(_hp); }
    (void)_t1293;
    if (_t1293) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1294; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1294 = *_hp; free(_hp); }
    (void)_t1294;
    if (_t1294) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1295; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1295 = *_hp; free(_hp); }
    (void)_t1295;
    if (_t1295) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1296; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1296 = *_hp; free(_hp); }
    (void)_t1296;
    if (_t1296) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1297; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1297 = *_hp; free(_hp); }
    (void)_t1297;
    if (_t1297) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1298; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1298 = *_hp; free(_hp); }
    (void)_t1298;
    if (_t1298) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1299; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1299 = *_hp; free(_hp); }
    (void)_t1299;
    if (_t1299) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1300; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1300 = *_hp; free(_hp); }
    (void)_t1300;
    if (_t1300) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1301; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1301 = *_hp; free(_hp); }
    (void)_t1301;
    if (_t1301) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t1302; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1302 = *_hp; free(_hp); }
    (void)_t1302;
    if (_t1302) {
        ;
        return TokenType_KwNull();
    }
    ;
    return TokenType_Error();
}

void TokenType_delete(TokenType * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * TokenType_to_str(TokenType * self) {
    (void)self;
    Bool _t1368; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1368 = *_hp; free(_hp); }
    (void)_t1368;
    if (_t1368) {
        Str *_t1303 = Str_lit("Eof", 3ULL);
        (void)_t1303;
        ;
        return _t1303;
    }
    ;
    Bool _t1369; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1369 = *_hp; free(_hp); }
    (void)_t1369;
    if (_t1369) {
        Str *_t1304 = Str_lit("LParen", 6ULL);
        (void)_t1304;
        ;
        return _t1304;
    }
    ;
    Bool _t1370; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1370 = *_hp; free(_hp); }
    (void)_t1370;
    if (_t1370) {
        Str *_t1305 = Str_lit("RParen", 6ULL);
        (void)_t1305;
        ;
        return _t1305;
    }
    ;
    Bool _t1371; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1371 = *_hp; free(_hp); }
    (void)_t1371;
    if (_t1371) {
        Str *_t1306 = Str_lit("LBrace", 6ULL);
        (void)_t1306;
        ;
        return _t1306;
    }
    ;
    Bool _t1372; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1372 = *_hp; free(_hp); }
    (void)_t1372;
    if (_t1372) {
        Str *_t1307 = Str_lit("RBrace", 6ULL);
        (void)_t1307;
        ;
        return _t1307;
    }
    ;
    Bool _t1373; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1373 = *_hp; free(_hp); }
    (void)_t1373;
    if (_t1373) {
        Str *_t1308 = Str_lit("LBracket", 8ULL);
        (void)_t1308;
        ;
        return _t1308;
    }
    ;
    Bool _t1374; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1374 = *_hp; free(_hp); }
    (void)_t1374;
    if (_t1374) {
        Str *_t1309 = Str_lit("RBracket", 8ULL);
        (void)_t1309;
        ;
        return _t1309;
    }
    ;
    Bool _t1375; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1375 = *_hp; free(_hp); }
    (void)_t1375;
    if (_t1375) {
        Str *_t1310 = Str_lit("Comma", 5ULL);
        (void)_t1310;
        ;
        return _t1310;
    }
    ;
    Bool _t1376; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        Str *_t1311 = Str_lit("Colon", 5ULL);
        (void)_t1311;
        ;
        return _t1311;
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        Str *_t1312 = Str_lit("Question", 8ULL);
        (void)_t1312;
        ;
        return _t1312;
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        Str *_t1313 = Str_lit("Bang", 4ULL);
        (void)_t1313;
        ;
        return _t1313;
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        Str *_t1314 = Str_lit("Minus", 5ULL);
        (void)_t1314;
        ;
        return _t1314;
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        Str *_t1315 = Str_lit("Plus", 4ULL);
        (void)_t1315;
        ;
        return _t1315;
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        Str *_t1316 = Str_lit("Star", 4ULL);
        (void)_t1316;
        ;
        return _t1316;
    }
    ;
    Bool _t1382; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    if (_t1382) {
        Str *_t1317 = Str_lit("Slash", 5ULL);
        (void)_t1317;
        ;
        return _t1317;
    }
    ;
    Bool _t1383; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1383 = *_hp; free(_hp); }
    (void)_t1383;
    if (_t1383) {
        Str *_t1318 = Str_lit("Dot", 3ULL);
        (void)_t1318;
        ;
        return _t1318;
    }
    ;
    Bool _t1384; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1384 = *_hp; free(_hp); }
    (void)_t1384;
    if (_t1384) {
        Str *_t1319 = Str_lit("DotDot", 6ULL);
        (void)_t1319;
        ;
        return _t1319;
    }
    ;
    Bool _t1385; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1385 = *_hp; free(_hp); }
    (void)_t1385;
    if (_t1385) {
        Str *_t1320 = Str_lit("Eq", 2ULL);
        (void)_t1320;
        ;
        return _t1320;
    }
    ;
    Bool _t1386; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1386 = *_hp; free(_hp); }
    (void)_t1386;
    if (_t1386) {
        Str *_t1321 = Str_lit("EqEq", 4ULL);
        (void)_t1321;
        ;
        return _t1321;
    }
    ;
    Bool _t1387; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    if (_t1387) {
        Str *_t1322 = Str_lit("Neq", 3ULL);
        (void)_t1322;
        ;
        return _t1322;
    }
    ;
    Bool _t1388; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1388 = *_hp; free(_hp); }
    (void)_t1388;
    if (_t1388) {
        Str *_t1323 = Str_lit("Lt", 2ULL);
        (void)_t1323;
        ;
        return _t1323;
    }
    ;
    Bool _t1389; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1389 = *_hp; free(_hp); }
    (void)_t1389;
    if (_t1389) {
        Str *_t1324 = Str_lit("LtEq", 4ULL);
        (void)_t1324;
        ;
        return _t1324;
    }
    ;
    Bool _t1390; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1390 = *_hp; free(_hp); }
    (void)_t1390;
    if (_t1390) {
        Str *_t1325 = Str_lit("Gt", 2ULL);
        (void)_t1325;
        ;
        return _t1325;
    }
    ;
    Bool _t1391; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1391 = *_hp; free(_hp); }
    (void)_t1391;
    if (_t1391) {
        Str *_t1326 = Str_lit("GtEq", 4ULL);
        (void)_t1326;
        ;
        return _t1326;
    }
    ;
    Bool _t1392; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    if (_t1392) {
        Str *_t1327 = Str_lit("ColonEq", 7ULL);
        (void)_t1327;
        ;
        return _t1327;
    }
    ;
    Bool _t1393; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        Str *_t1328 = Str_lit("Ident", 5ULL);
        (void)_t1328;
        ;
        return _t1328;
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        Str *_t1329 = Str_lit("StringTok", 9ULL);
        (void)_t1329;
        ;
        return _t1329;
    }
    ;
    Bool _t1395; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1395 = *_hp; free(_hp); }
    (void)_t1395;
    if (_t1395) {
        Str *_t1330 = Str_lit("Number", 6ULL);
        (void)_t1330;
        ;
        return _t1330;
    }
    ;
    Bool _t1396; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        Str *_t1331 = Str_lit("Char", 4ULL);
        (void)_t1331;
        ;
        return _t1331;
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        Str *_t1332 = Str_lit("KwMode", 6ULL);
        (void)_t1332;
        ;
        return _t1332;
    }
    ;
    Bool _t1398; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1398 = *_hp; free(_hp); }
    (void)_t1398;
    if (_t1398) {
        Str *_t1333 = Str_lit("KwMut", 5ULL);
        (void)_t1333;
        ;
        return _t1333;
    }
    ;
    Bool _t1399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1399 = *_hp; free(_hp); }
    (void)_t1399;
    if (_t1399) {
        Str *_t1334 = Str_lit("KwOwn", 5ULL);
        (void)_t1334;
        ;
        return _t1334;
    }
    ;
    Bool _t1400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        Str *_t1335 = Str_lit("KwRef", 5ULL);
        (void)_t1335;
        ;
        return _t1335;
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        Str *_t1336 = Str_lit("KwShallow", 9ULL);
        (void)_t1336;
        ;
        return _t1336;
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        Str *_t1337 = Str_lit("KwStruct", 8ULL);
        (void)_t1337;
        ;
        return _t1337;
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        Str *_t1338 = Str_lit("KwExtStruct", 11ULL);
        (void)_t1338;
        ;
        return _t1338;
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
        Str *_t1339 = Str_lit("KwEnum", 6ULL);
        (void)_t1339;
        ;
        return _t1339;
    }
    ;
    Bool _t1405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1405 = *_hp; free(_hp); }
    (void)_t1405;
    if (_t1405) {
        Str *_t1340 = Str_lit("KwNamespace", 11ULL);
        (void)_t1340;
        ;
        return _t1340;
    }
    ;
    Bool _t1406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1406 = *_hp; free(_hp); }
    (void)_t1406;
    if (_t1406) {
        Str *_t1341 = Str_lit("KwFunc", 6ULL);
        (void)_t1341;
        ;
        return _t1341;
    }
    ;
    Bool _t1407; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1407 = *_hp; free(_hp); }
    (void)_t1407;
    if (_t1407) {
        Str *_t1342 = Str_lit("KwProc", 6ULL);
        (void)_t1342;
        ;
        return _t1342;
    }
    ;
    Bool _t1408; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1408 = *_hp; free(_hp); }
    (void)_t1408;
    if (_t1408) {
        Str *_t1343 = Str_lit("KwTest", 6ULL);
        (void)_t1343;
        ;
        return _t1343;
    }
    ;
    Bool _t1409; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1409 = *_hp; free(_hp); }
    (void)_t1409;
    if (_t1409) {
        Str *_t1344 = Str_lit("KwMacro", 7ULL);
        (void)_t1344;
        ;
        return _t1344;
    }
    ;
    Bool _t1410; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1410 = *_hp; free(_hp); }
    (void)_t1410;
    if (_t1410) {
        Str *_t1345 = Str_lit("KwExtFunc", 9ULL);
        (void)_t1345;
        ;
        return _t1345;
    }
    ;
    Bool _t1411; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1411 = *_hp; free(_hp); }
    (void)_t1411;
    if (_t1411) {
        Str *_t1346 = Str_lit("KwExtProc", 9ULL);
        (void)_t1346;
        ;
        return _t1346;
    }
    ;
    Bool _t1412; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1412 = *_hp; free(_hp); }
    (void)_t1412;
    if (_t1412) {
        Str *_t1347 = Str_lit("KwReturns", 9ULL);
        (void)_t1347;
        ;
        return _t1347;
    }
    ;
    Bool _t1413; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1413 = *_hp; free(_hp); }
    (void)_t1413;
    if (_t1413) {
        Str *_t1348 = Str_lit("KwThrows", 8ULL);
        (void)_t1348;
        ;
        return _t1348;
    }
    ;
    Bool _t1414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1414 = *_hp; free(_hp); }
    (void)_t1414;
    if (_t1414) {
        Str *_t1349 = Str_lit("KwIf", 4ULL);
        (void)_t1349;
        ;
        return _t1349;
    }
    ;
    Bool _t1415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1415 = *_hp; free(_hp); }
    (void)_t1415;
    if (_t1415) {
        Str *_t1350 = Str_lit("KwElse", 6ULL);
        (void)_t1350;
        ;
        return _t1350;
    }
    ;
    Bool _t1416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1416 = *_hp; free(_hp); }
    (void)_t1416;
    if (_t1416) {
        Str *_t1351 = Str_lit("KwWhile", 7ULL);
        (void)_t1351;
        ;
        return _t1351;
    }
    ;
    Bool _t1417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1417 = *_hp; free(_hp); }
    (void)_t1417;
    if (_t1417) {
        Str *_t1352 = Str_lit("KwFor", 5ULL);
        (void)_t1352;
        ;
        return _t1352;
    }
    ;
    Bool _t1418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1418 = *_hp; free(_hp); }
    (void)_t1418;
    if (_t1418) {
        Str *_t1353 = Str_lit("KwIn", 4ULL);
        (void)_t1353;
        ;
        return _t1353;
    }
    ;
    Bool _t1419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1419 = *_hp; free(_hp); }
    (void)_t1419;
    if (_t1419) {
        Str *_t1354 = Str_lit("KwSwitch", 8ULL);
        (void)_t1354;
        ;
        return _t1354;
    }
    ;
    Bool _t1420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1420 = *_hp; free(_hp); }
    (void)_t1420;
    if (_t1420) {
        Str *_t1355 = Str_lit("KwMatch", 7ULL);
        (void)_t1355;
        ;
        return _t1355;
    }
    ;
    Bool _t1421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1421 = *_hp; free(_hp); }
    (void)_t1421;
    if (_t1421) {
        Str *_t1356 = Str_lit("KwCase", 6ULL);
        (void)_t1356;
        ;
        return _t1356;
    }
    ;
    Bool _t1422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1422 = *_hp; free(_hp); }
    (void)_t1422;
    if (_t1422) {
        Str *_t1357 = Str_lit("KwDefault", 9ULL);
        (void)_t1357;
        ;
        return _t1357;
    }
    ;
    Bool _t1423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1423 = *_hp; free(_hp); }
    (void)_t1423;
    if (_t1423) {
        Str *_t1358 = Str_lit("KwReturn", 8ULL);
        (void)_t1358;
        ;
        return _t1358;
    }
    ;
    Bool _t1424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1424 = *_hp; free(_hp); }
    (void)_t1424;
    if (_t1424) {
        Str *_t1359 = Str_lit("KwThrow", 7ULL);
        (void)_t1359;
        ;
        return _t1359;
    }
    ;
    Bool _t1425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1425 = *_hp; free(_hp); }
    (void)_t1425;
    if (_t1425) {
        Str *_t1360 = Str_lit("KwCatch", 7ULL);
        (void)_t1360;
        ;
        return _t1360;
    }
    ;
    Bool _t1426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1426 = *_hp; free(_hp); }
    (void)_t1426;
    if (_t1426) {
        Str *_t1361 = Str_lit("KwBreak", 7ULL);
        (void)_t1361;
        ;
        return _t1361;
    }
    ;
    Bool _t1427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1427 = *_hp; free(_hp); }
    (void)_t1427;
    if (_t1427) {
        Str *_t1362 = Str_lit("KwContinue", 10ULL);
        (void)_t1362;
        ;
        return _t1362;
    }
    ;
    Bool _t1428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1428 = *_hp; free(_hp); }
    (void)_t1428;
    if (_t1428) {
        Str *_t1363 = Str_lit("KwDefer", 7ULL);
        (void)_t1363;
        ;
        return _t1363;
    }
    ;
    Bool _t1429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1429 = *_hp; free(_hp); }
    (void)_t1429;
    if (_t1429) {
        Str *_t1364 = Str_lit("KwTrue", 6ULL);
        (void)_t1364;
        ;
        return _t1364;
    }
    ;
    Bool _t1430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1430 = *_hp; free(_hp); }
    (void)_t1430;
    if (_t1430) {
        Str *_t1365 = Str_lit("KwFalse", 7ULL);
        (void)_t1365;
        ;
        return _t1365;
    }
    ;
    Bool _t1431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1431 = *_hp; free(_hp); }
    (void)_t1431;
    if (_t1431) {
        Str *_t1366 = Str_lit("KwNull", 6ULL);
        (void)_t1366;
        ;
        return _t1366;
    }
    ;
    Bool _t1432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t1432 = *_hp; free(_hp); }
    (void)_t1432;
    if (_t1432) {
        Str *_t1367 = Str_lit("Error", 5ULL);
        (void)_t1367;
        ;
        return _t1367;
    }
    ;
    Str *_t1433 = Str_lit("unknown", 7ULL);
    (void)_t1433;
    return _t1433;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1435 = I64_clone(&self->line);
    (void)_t1435;
    I64 _t1436 = I64_clone(&self->col);
    (void)_t1436;
    Token *_t1437 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1437->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1437->text = *_ca; free(_ca); }
    _t1437->line = _t1435;
    _t1437->col = _t1436;
    (void)_t1437;
    ;
    ;
    return _t1437;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1438 = 0;
    (void)_t1438;
    TokenType_delete(&self->type, &(Bool){_t1438});
    ;
    Bool _t1439 = 0;
    (void)_t1439;
    Str_delete(&self->text, &(Bool){_t1439});
    ;
    Bool _t1440 = 0;
    (void)_t1440;
    I64_delete(&self->line, &(Bool){_t1440});
    ;
    Bool _t1441 = 0;
    (void)_t1441;
    I64_delete(&self->col, &(Bool){_t1441});
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
    (void)c;
    U8 _t1443 = 48;
    (void)_t1443;
    U8 _t1444 = 57;
    (void)_t1444;
    Bool _t1445; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1443}); _t1445 = *_hp; free(_hp); }
    (void)_t1445;
    ;
    Bool _t1446; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1444}); _t1446 = *_hp; free(_hp); }
    (void)_t1446;
    ;
    Bool _t1447 = Bool_and(_t1445, _t1446);
    (void)_t1447;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1447; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t1448 = 97;
    (void)_t1448;
    U8 _t1449 = 122;
    (void)_t1449;
    Bool _t1450; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1448}); _t1450 = *_hp; free(_hp); }
    (void)_t1450;
    ;
    Bool _t1451; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1449}); _t1451 = *_hp; free(_hp); }
    (void)_t1451;
    ;
    U8 _t1452 = 65;
    (void)_t1452;
    U8 _t1453 = 90;
    (void)_t1453;
    Bool _t1454; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1452}); _t1454 = *_hp; free(_hp); }
    (void)_t1454;
    ;
    Bool _t1455; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1453}); _t1455 = *_hp; free(_hp); }
    (void)_t1455;
    ;
    Bool _t1456 = Bool_and(_t1450, _t1451);
    (void)_t1456;
    ;
    ;
    Bool _t1457 = Bool_and(_t1454, _t1455);
    (void)_t1457;
    ;
    ;
    U8 _t1458 = 95;
    (void)_t1458;
    Bool _t1459 = Bool_or(_t1456, _t1457);
    (void)_t1459;
    ;
    ;
    Bool _t1460 = U8_eq(DEREF(c), _t1458);
    (void)_t1460;
    ;
    Bool _t1461 = Bool_or(_t1459, _t1460);
    (void)_t1461;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1461; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t1462; { Bool *_hp = (Bool *)is_alpha(c); _t1462 = *_hp; free(_hp); }
    (void)_t1462;
    Bool _t1463; { Bool *_hp = (Bool *)is_digit(c); _t1463 = *_hp; free(_hp); }
    (void)_t1463;
    Bool _t1464 = Bool_or(_t1462, _t1463);
    (void)_t1464;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1464; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw1465 = TokenType_clone(type);
        (void)_sw1465;
        Bool _t1596; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Eof()); _t1596 = *_hp; free(_hp); }
        (void)_t1596;
        if (_t1596) {
            Str *_t1466 = Str_lit("eof", 3ULL);
            (void)_t1466;
            TokenType_delete(_sw1465, &(Bool){1});
            ;
            return _t1466;
        } else {
            Bool _t1595; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_LParen()); _t1595 = *_hp; free(_hp); }
            (void)_t1595;
            if (_t1595) {
                Str *_t1467 = Str_lit("(", 1ULL);
                (void)_t1467;
                ;
                TokenType_delete(_sw1465, &(Bool){1});
                ;
                return _t1467;
            } else {
                Bool _t1594; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_RParen()); _t1594 = *_hp; free(_hp); }
                (void)_t1594;
                if (_t1594) {
                    Str *_t1468 = Str_lit(")", 1ULL);
                    (void)_t1468;
                    ;
                    ;
                    TokenType_delete(_sw1465, &(Bool){1});
                    ;
                    return _t1468;
                } else {
                    Bool _t1593; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_LBrace()); _t1593 = *_hp; free(_hp); }
                    (void)_t1593;
                    if (_t1593) {
                        Str *_t1469 = Str_lit("{", 1ULL);
                        (void)_t1469;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1465, &(Bool){1});
                        ;
                        return _t1469;
                    } else {
                        Bool _t1592; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_RBrace()); _t1592 = *_hp; free(_hp); }
                        (void)_t1592;
                        if (_t1592) {
                            Str *_t1470 = Str_lit("}", 1ULL);
                            (void)_t1470;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1465, &(Bool){1});
                            ;
                            return _t1470;
                        } else {
                            Bool _t1591; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_LBracket()); _t1591 = *_hp; free(_hp); }
                            (void)_t1591;
                            if (_t1591) {
                                Str *_t1471 = Str_lit("[", 1ULL);
                                (void)_t1471;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1465, &(Bool){1});
                                ;
                                return _t1471;
                            } else {
                                Bool _t1590; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_RBracket()); _t1590 = *_hp; free(_hp); }
                                (void)_t1590;
                                if (_t1590) {
                                    Str *_t1472 = Str_lit("]", 1ULL);
                                    (void)_t1472;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1465, &(Bool){1});
                                    ;
                                    return _t1472;
                                } else {
                                    Bool _t1589; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Comma()); _t1589 = *_hp; free(_hp); }
                                    (void)_t1589;
                                    if (_t1589) {
                                        Str *_t1473 = Str_lit(",", 1ULL);
                                        (void)_t1473;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1465, &(Bool){1});
                                        ;
                                        return _t1473;
                                    } else {
                                        Bool _t1588; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Colon()); _t1588 = *_hp; free(_hp); }
                                        (void)_t1588;
                                        if (_t1588) {
                                            Str *_t1474 = Str_lit(":", 1ULL);
                                            (void)_t1474;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1465, &(Bool){1});
                                            ;
                                            return _t1474;
                                        } else {
                                            Bool _t1587; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Question()); _t1587 = *_hp; free(_hp); }
                                            (void)_t1587;
                                            if (_t1587) {
                                                Str *_t1475 = Str_lit("?", 1ULL);
                                                (void)_t1475;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1465, &(Bool){1});
                                                ;
                                                return _t1475;
                                            } else {
                                                Bool _t1586; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Bang()); _t1586 = *_hp; free(_hp); }
                                                (void)_t1586;
                                                if (_t1586) {
                                                    Str *_t1476 = Str_lit("!", 1ULL);
                                                    (void)_t1476;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                    ;
                                                    return _t1476;
                                                } else {
                                                    Bool _t1585; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Minus()); _t1585 = *_hp; free(_hp); }
                                                    (void)_t1585;
                                                    if (_t1585) {
                                                        Str *_t1477 = Str_lit("-", 1ULL);
                                                        (void)_t1477;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                        ;
                                                        return _t1477;
                                                    } else {
                                                        Bool _t1584; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Plus()); _t1584 = *_hp; free(_hp); }
                                                        (void)_t1584;
                                                        if (_t1584) {
                                                            Str *_t1478 = Str_lit("+", 1ULL);
                                                            (void)_t1478;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                            ;
                                                            return _t1478;
                                                        } else {
                                                            Bool _t1583; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Star()); _t1583 = *_hp; free(_hp); }
                                                            (void)_t1583;
                                                            if (_t1583) {
                                                                Str *_t1479 = Str_lit("*", 1ULL);
                                                                (void)_t1479;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                ;
                                                                return _t1479;
                                                            } else {
                                                                Bool _t1582; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Slash()); _t1582 = *_hp; free(_hp); }
                                                                (void)_t1582;
                                                                if (_t1582) {
                                                                    Str *_t1480 = Str_lit("/", 1ULL);
                                                                    (void)_t1480;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                    ;
                                                                    return _t1480;
                                                                } else {
                                                                    Bool _t1581; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Dot()); _t1581 = *_hp; free(_hp); }
                                                                    (void)_t1581;
                                                                    if (_t1581) {
                                                                        Str *_t1481 = Str_lit(".", 1ULL);
                                                                        (void)_t1481;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                        ;
                                                                        return _t1481;
                                                                    } else {
                                                                        Bool _t1580; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_DotDot()); _t1580 = *_hp; free(_hp); }
                                                                        (void)_t1580;
                                                                        if (_t1580) {
                                                                            Str *_t1482 = Str_lit("..", 2ULL);
                                                                            (void)_t1482;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                            ;
                                                                            return _t1482;
                                                                        } else {
                                                                            Bool _t1579; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Eq()); _t1579 = *_hp; free(_hp); }
                                                                            (void)_t1579;
                                                                            if (_t1579) {
                                                                                Str *_t1483 = Str_lit("=", 1ULL);
                                                                                (void)_t1483;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                ;
                                                                                return _t1483;
                                                                            } else {
                                                                                Bool _t1578; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_EqEq()); _t1578 = *_hp; free(_hp); }
                                                                                (void)_t1578;
                                                                                if (_t1578) {
                                                                                    Str *_t1484 = Str_lit("==", 2ULL);
                                                                                    (void)_t1484;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                    ;
                                                                                    return _t1484;
                                                                                } else {
                                                                                    Bool _t1577; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Neq()); _t1577 = *_hp; free(_hp); }
                                                                                    (void)_t1577;
                                                                                    if (_t1577) {
                                                                                        Str *_t1485 = Str_lit("!=", 2ULL);
                                                                                        (void)_t1485;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                        ;
                                                                                        return _t1485;
                                                                                    } else {
                                                                                        Bool _t1576; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Lt()); _t1576 = *_hp; free(_hp); }
                                                                                        (void)_t1576;
                                                                                        if (_t1576) {
                                                                                            Str *_t1486 = Str_lit("<", 1ULL);
                                                                                            (void)_t1486;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                            ;
                                                                                            return _t1486;
                                                                                        } else {
                                                                                            Bool _t1575; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_LtEq()); _t1575 = *_hp; free(_hp); }
                                                                                            (void)_t1575;
                                                                                            if (_t1575) {
                                                                                                Str *_t1487 = Str_lit("<=", 2ULL);
                                                                                                (void)_t1487;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                ;
                                                                                                return _t1487;
                                                                                            } else {
                                                                                                Bool _t1574; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Gt()); _t1574 = *_hp; free(_hp); }
                                                                                                (void)_t1574;
                                                                                                if (_t1574) {
                                                                                                    Str *_t1488 = Str_lit(">", 1ULL);
                                                                                                    (void)_t1488;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1488;
                                                                                                } else {
                                                                                                    Bool _t1573; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_GtEq()); _t1573 = *_hp; free(_hp); }
                                                                                                    (void)_t1573;
                                                                                                    if (_t1573) {
                                                                                                        Str *_t1489 = Str_lit(">=", 2ULL);
                                                                                                        (void)_t1489;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1489;
                                                                                                    } else {
                                                                                                        Bool _t1572; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_ColonEq()); _t1572 = *_hp; free(_hp); }
                                                                                                        (void)_t1572;
                                                                                                        if (_t1572) {
                                                                                                            Str *_t1490 = Str_lit(":=", 2ULL);
                                                                                                            (void)_t1490;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1490;
                                                                                                        } else {
                                                                                                            Bool _t1571; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Ident()); _t1571 = *_hp; free(_hp); }
                                                                                                            (void)_t1571;
                                                                                                            if (_t1571) {
                                                                                                                Str *_t1491 = Str_lit("identifier", 10ULL);
                                                                                                                (void)_t1491;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1491;
                                                                                                            } else {
                                                                                                                Bool _t1570; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_StringTok()); _t1570 = *_hp; free(_hp); }
                                                                                                                (void)_t1570;
                                                                                                                if (_t1570) {
                                                                                                                    Str *_t1492 = Str_lit("string", 6ULL);
                                                                                                                    (void)_t1492;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1492;
                                                                                                                } else {
                                                                                                                    Bool _t1569; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Number()); _t1569 = *_hp; free(_hp); }
                                                                                                                    (void)_t1569;
                                                                                                                    if (_t1569) {
                                                                                                                        Str *_t1493 = Str_lit("number", 6ULL);
                                                                                                                        (void)_t1493;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1493;
                                                                                                                    } else {
                                                                                                                        Bool _t1568; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Char()); _t1568 = *_hp; free(_hp); }
                                                                                                                        (void)_t1568;
                                                                                                                        if (_t1568) {
                                                                                                                            Str *_t1494 = Str_lit("char", 4ULL);
                                                                                                                            (void)_t1494;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1494;
                                                                                                                        } else {
                                                                                                                            Bool _t1567; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwMode()); _t1567 = *_hp; free(_hp); }
                                                                                                                            (void)_t1567;
                                                                                                                            if (_t1567) {
                                                                                                                                Str *_t1495 = Str_lit("mode", 4ULL);
                                                                                                                                (void)_t1495;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1495;
                                                                                                                            } else {
                                                                                                                                Bool _t1566; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwMut()); _t1566 = *_hp; free(_hp); }
                                                                                                                                (void)_t1566;
                                                                                                                                if (_t1566) {
                                                                                                                                    Str *_t1496 = Str_lit("mut", 3ULL);
                                                                                                                                    (void)_t1496;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1496;
                                                                                                                                } else {
                                                                                                                                    Bool _t1565; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwOwn()); _t1565 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1565;
                                                                                                                                    if (_t1565) {
                                                                                                                                        Str *_t1497 = Str_lit("own", 3ULL);
                                                                                                                                        (void)_t1497;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1497;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1564; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwRef()); _t1564 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1564;
                                                                                                                                        if (_t1564) {
                                                                                                                                            Str *_t1498 = Str_lit("ref", 3ULL);
                                                                                                                                            (void)_t1498;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1498;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1563; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwShallow()); _t1563 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1563;
                                                                                                                                            if (_t1563) {
                                                                                                                                                Str *_t1499 = Str_lit("shallow", 7ULL);
                                                                                                                                                (void)_t1499;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1499;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1562; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwStruct()); _t1562 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1562;
                                                                                                                                                if (_t1562) {
                                                                                                                                                    Str *_t1500 = Str_lit("struct", 6ULL);
                                                                                                                                                    (void)_t1500;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1500;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1561; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwExtStruct()); _t1561 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t1561;
                                                                                                                                                    if (_t1561) {
                                                                                                                                                        Str *_t1501 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                        (void)_t1501;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1501;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1560; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwEnum()); _t1560 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t1560;
                                                                                                                                                        if (_t1560) {
                                                                                                                                                            Str *_t1502 = Str_lit("enum", 4ULL);
                                                                                                                                                            (void)_t1502;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1502;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1559; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwNamespace()); _t1559 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t1559;
                                                                                                                                                            if (_t1559) {
                                                                                                                                                                Str *_t1503 = Str_lit("namespace", 9ULL);
                                                                                                                                                                (void)_t1503;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1503;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1558; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwFunc()); _t1558 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t1558;
                                                                                                                                                                if (_t1558) {
                                                                                                                                                                    Str *_t1504 = Str_lit("func", 4ULL);
                                                                                                                                                                    (void)_t1504;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1504;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1557; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwProc()); _t1557 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t1557;
                                                                                                                                                                    if (_t1557) {
                                                                                                                                                                        Str *_t1505 = Str_lit("proc", 4ULL);
                                                                                                                                                                        (void)_t1505;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1505;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1556; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwTest()); _t1556 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t1556;
                                                                                                                                                                        if (_t1556) {
                                                                                                                                                                            Str *_t1506 = Str_lit("test", 4ULL);
                                                                                                                                                                            (void)_t1506;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1506;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1555; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwMacro()); _t1555 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t1555;
                                                                                                                                                                            if (_t1555) {
                                                                                                                                                                                Str *_t1507 = Str_lit("macro", 5ULL);
                                                                                                                                                                                (void)_t1507;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1507;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1554; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwExtFunc()); _t1554 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t1554;
                                                                                                                                                                                if (_t1554) {
                                                                                                                                                                                    Str *_t1508 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                    (void)_t1508;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1508;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1553; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwExtProc()); _t1553 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t1553;
                                                                                                                                                                                    if (_t1553) {
                                                                                                                                                                                        Str *_t1509 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                        (void)_t1509;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1509;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1552; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwReturns()); _t1552 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t1552;
                                                                                                                                                                                        if (_t1552) {
                                                                                                                                                                                            Str *_t1510 = Str_lit("returns", 7ULL);
                                                                                                                                                                                            (void)_t1510;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1510;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1551; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwThrows()); _t1551 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t1551;
                                                                                                                                                                                            if (_t1551) {
                                                                                                                                                                                                Str *_t1511 = Str_lit("throws", 6ULL);
                                                                                                                                                                                                (void)_t1511;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1511;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1550; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwIf()); _t1550 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t1550;
                                                                                                                                                                                                if (_t1550) {
                                                                                                                                                                                                    Str *_t1512 = Str_lit("if", 2ULL);
                                                                                                                                                                                                    (void)_t1512;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1512;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1549; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwElse()); _t1549 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t1549;
                                                                                                                                                                                                    if (_t1549) {
                                                                                                                                                                                                        Str *_t1513 = Str_lit("else", 4ULL);
                                                                                                                                                                                                        (void)_t1513;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1513;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1548; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwWhile()); _t1548 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t1548;
                                                                                                                                                                                                        if (_t1548) {
                                                                                                                                                                                                            Str *_t1514 = Str_lit("while", 5ULL);
                                                                                                                                                                                                            (void)_t1514;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1514;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1547; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwFor()); _t1547 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t1547;
                                                                                                                                                                                                            if (_t1547) {
                                                                                                                                                                                                                Str *_t1515 = Str_lit("for", 3ULL);
                                                                                                                                                                                                                (void)_t1515;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1515;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1546; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwIn()); _t1546 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t1546;
                                                                                                                                                                                                                if (_t1546) {
                                                                                                                                                                                                                    Str *_t1516 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                    (void)_t1516;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1516;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1545; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwSwitch()); _t1545 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t1545;
                                                                                                                                                                                                                    if (_t1545) {
                                                                                                                                                                                                                        Str *_t1517 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                        (void)_t1517;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1517;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1544; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwMatch()); _t1544 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t1544;
                                                                                                                                                                                                                        if (_t1544) {
                                                                                                                                                                                                                            Str *_t1518 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                            (void)_t1518;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1518;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1543; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwCase()); _t1543 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t1543;
                                                                                                                                                                                                                            if (_t1543) {
                                                                                                                                                                                                                                Str *_t1519 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                                (void)_t1519;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1519;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1542; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwDefault()); _t1542 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t1542;
                                                                                                                                                                                                                                if (_t1542) {
                                                                                                                                                                                                                                    Str *_t1520 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                    (void)_t1520;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1520;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1541; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwReturn()); _t1541 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t1541;
                                                                                                                                                                                                                                    if (_t1541) {
                                                                                                                                                                                                                                        Str *_t1521 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                        (void)_t1521;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1521;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1540; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwThrow()); _t1540 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t1540;
                                                                                                                                                                                                                                        if (_t1540) {
                                                                                                                                                                                                                                            Str *_t1522 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                            (void)_t1522;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1522;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1539; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwCatch()); _t1539 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t1539;
                                                                                                                                                                                                                                            if (_t1539) {
                                                                                                                                                                                                                                                Str *_t1523 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                                (void)_t1523;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1523;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1538; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwBreak()); _t1538 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t1538;
                                                                                                                                                                                                                                                if (_t1538) {
                                                                                                                                                                                                                                                    Str *_t1524 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                    (void)_t1524;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1524;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1537; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwContinue()); _t1537 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t1537;
                                                                                                                                                                                                                                                    if (_t1537) {
                                                                                                                                                                                                                                                        Str *_t1525 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                        (void)_t1525;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1525;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1536; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwDefer()); _t1536 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t1536;
                                                                                                                                                                                                                                                        if (_t1536) {
                                                                                                                                                                                                                                                            Str *_t1526 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                            (void)_t1526;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1526;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1535; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwTrue()); _t1535 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t1535;
                                                                                                                                                                                                                                                            if (_t1535) {
                                                                                                                                                                                                                                                                Str *_t1527 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                                (void)_t1527;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1527;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1534; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwFalse()); _t1534 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t1534;
                                                                                                                                                                                                                                                                if (_t1534) {
                                                                                                                                                                                                                                                                    Str *_t1528 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                    (void)_t1528;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1528;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1533; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_KwNull()); _t1533 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t1533;
                                                                                                                                                                                                                                                                    if (_t1533) {
                                                                                                                                                                                                                                                                        Str *_t1529 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                        (void)_t1529;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1529;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1532; { Bool *_hp = (Bool *)TokenType_eq(_sw1465, TokenType_Error()); _t1532 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t1532;
                                                                                                                                                                                                                                                                        if (_t1532) {
                                                                                                                                                                                                                                                                            Str *_t1530 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                            (void)_t1530;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1530;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Str *_t1531 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                            (void)_t1531;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1465, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1531;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1465, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw1597 = Str_clone(word);
        (void)_sw1597;
        Str *_t1666 = Str_lit("mode", 4ULL);
        (void)_t1666;
        Bool _t1667; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1666); _t1667 = *_hp; free(_hp); }
        (void)_t1667;
        Str_delete(_t1666, &(Bool){1});
        if (_t1667) {
            Str_delete(_sw1597, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1664 = Str_lit("mut", 3ULL);
            (void)_t1664;
            Bool _t1665; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1664); _t1665 = *_hp; free(_hp); }
            (void)_t1665;
            Str_delete(_t1664, &(Bool){1});
            if (_t1665) {
                ;
                Str_delete(_sw1597, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1662 = Str_lit("own", 3ULL);
                (void)_t1662;
                Bool _t1663; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1662); _t1663 = *_hp; free(_hp); }
                (void)_t1663;
                Str_delete(_t1662, &(Bool){1});
                if (_t1663) {
                    ;
                    ;
                    Str_delete(_sw1597, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1660 = Str_lit("ref", 3ULL);
                    (void)_t1660;
                    Bool _t1661; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1660); _t1661 = *_hp; free(_hp); }
                    (void)_t1661;
                    Str_delete(_t1660, &(Bool){1});
                    if (_t1661) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1597, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1658 = Str_lit("shallow", 7ULL);
                        (void)_t1658;
                        Bool _t1659; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1658); _t1659 = *_hp; free(_hp); }
                        (void)_t1659;
                        Str_delete(_t1658, &(Bool){1});
                        if (_t1659) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1597, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1656 = Str_lit("struct", 6ULL);
                            (void)_t1656;
                            Bool _t1657; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1656); _t1657 = *_hp; free(_hp); }
                            (void)_t1657;
                            Str_delete(_t1656, &(Bool){1});
                            if (_t1657) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1597, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1654 = Str_lit("ext_struct", 10ULL);
                                (void)_t1654;
                                Bool _t1655; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1654); _t1655 = *_hp; free(_hp); }
                                (void)_t1655;
                                Str_delete(_t1654, &(Bool){1});
                                if (_t1655) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1597, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1652 = Str_lit("enum", 4ULL);
                                    (void)_t1652;
                                    Bool _t1653; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1652); _t1653 = *_hp; free(_hp); }
                                    (void)_t1653;
                                    Str_delete(_t1652, &(Bool){1});
                                    if (_t1653) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1597, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1650 = Str_lit("namespace", 9ULL);
                                        (void)_t1650;
                                        Bool _t1651; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1650); _t1651 = *_hp; free(_hp); }
                                        (void)_t1651;
                                        Str_delete(_t1650, &(Bool){1});
                                        if (_t1651) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1597, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1648 = Str_lit("func", 4ULL);
                                            (void)_t1648;
                                            Bool _t1649; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1648); _t1649 = *_hp; free(_hp); }
                                            (void)_t1649;
                                            Str_delete(_t1648, &(Bool){1});
                                            if (_t1649) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw1597, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1646 = Str_lit("proc", 4ULL);
                                                (void)_t1646;
                                                Bool _t1647; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1646); _t1647 = *_hp; free(_hp); }
                                                (void)_t1647;
                                                Str_delete(_t1646, &(Bool){1});
                                                if (_t1647) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw1597, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1644 = Str_lit("test", 4ULL);
                                                    (void)_t1644;
                                                    Bool _t1645; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1644); _t1645 = *_hp; free(_hp); }
                                                    (void)_t1645;
                                                    Str_delete(_t1644, &(Bool){1});
                                                    if (_t1645) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw1597, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1642 = Str_lit("macro", 5ULL);
                                                        (void)_t1642;
                                                        Bool _t1643; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1642); _t1643 = *_hp; free(_hp); }
                                                        (void)_t1643;
                                                        Str_delete(_t1642, &(Bool){1});
                                                        if (_t1643) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw1597, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1640 = Str_lit("ext_func", 8ULL);
                                                            (void)_t1640;
                                                            Bool _t1641; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1640); _t1641 = *_hp; free(_hp); }
                                                            (void)_t1641;
                                                            Str_delete(_t1640, &(Bool){1});
                                                            if (_t1641) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw1597, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1638 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t1638;
                                                                Bool _t1639; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1638); _t1639 = *_hp; free(_hp); }
                                                                (void)_t1639;
                                                                Str_delete(_t1638, &(Bool){1});
                                                                if (_t1639) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1597, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1636 = Str_lit("returns", 7ULL);
                                                                    (void)_t1636;
                                                                    Bool _t1637; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1636); _t1637 = *_hp; free(_hp); }
                                                                    (void)_t1637;
                                                                    Str_delete(_t1636, &(Bool){1});
                                                                    if (_t1637) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1597, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1634 = Str_lit("throws", 6ULL);
                                                                        (void)_t1634;
                                                                        Bool _t1635; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1634); _t1635 = *_hp; free(_hp); }
                                                                        (void)_t1635;
                                                                        Str_delete(_t1634, &(Bool){1});
                                                                        if (_t1635) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1597, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1632 = Str_lit("if", 2ULL);
                                                                            (void)_t1632;
                                                                            Bool _t1633; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1632); _t1633 = *_hp; free(_hp); }
                                                                            (void)_t1633;
                                                                            Str_delete(_t1632, &(Bool){1});
                                                                            if (_t1633) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1597, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1630 = Str_lit("else", 4ULL);
                                                                                (void)_t1630;
                                                                                Bool _t1631; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1630); _t1631 = *_hp; free(_hp); }
                                                                                (void)_t1631;
                                                                                Str_delete(_t1630, &(Bool){1});
                                                                                if (_t1631) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1597, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1628 = Str_lit("while", 5ULL);
                                                                                    (void)_t1628;
                                                                                    Bool _t1629; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1628); _t1629 = *_hp; free(_hp); }
                                                                                    (void)_t1629;
                                                                                    Str_delete(_t1628, &(Bool){1});
                                                                                    if (_t1629) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1597, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1626 = Str_lit("for", 3ULL);
                                                                                        (void)_t1626;
                                                                                        Bool _t1627; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1626); _t1627 = *_hp; free(_hp); }
                                                                                        (void)_t1627;
                                                                                        Str_delete(_t1626, &(Bool){1});
                                                                                        if (_t1627) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1597, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1624 = Str_lit("in", 2ULL);
                                                                                            (void)_t1624;
                                                                                            Bool _t1625; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1624); _t1625 = *_hp; free(_hp); }
                                                                                            (void)_t1625;
                                                                                            Str_delete(_t1624, &(Bool){1});
                                                                                            if (_t1625) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1597, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1622 = Str_lit("switch", 6ULL);
                                                                                                (void)_t1622;
                                                                                                Bool _t1623; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1622); _t1623 = *_hp; free(_hp); }
                                                                                                (void)_t1623;
                                                                                                Str_delete(_t1622, &(Bool){1});
                                                                                                if (_t1623) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1597, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1620 = Str_lit("match", 5ULL);
                                                                                                    (void)_t1620;
                                                                                                    Bool _t1621; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1620); _t1621 = *_hp; free(_hp); }
                                                                                                    (void)_t1621;
                                                                                                    Str_delete(_t1620, &(Bool){1});
                                                                                                    if (_t1621) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1597, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1618 = Str_lit("case", 4ULL);
                                                                                                        (void)_t1618;
                                                                                                        Bool _t1619; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1618); _t1619 = *_hp; free(_hp); }
                                                                                                        (void)_t1619;
                                                                                                        Str_delete(_t1618, &(Bool){1});
                                                                                                        if (_t1619) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1597, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1616 = Str_lit("default", 7ULL);
                                                                                                            (void)_t1616;
                                                                                                            Bool _t1617; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1616); _t1617 = *_hp; free(_hp); }
                                                                                                            (void)_t1617;
                                                                                                            Str_delete(_t1616, &(Bool){1});
                                                                                                            if (_t1617) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1597, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1614 = Str_lit("return", 6ULL);
                                                                                                                (void)_t1614;
                                                                                                                Bool _t1615; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1614); _t1615 = *_hp; free(_hp); }
                                                                                                                (void)_t1615;
                                                                                                                Str_delete(_t1614, &(Bool){1});
                                                                                                                if (_t1615) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1597, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1612 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t1612;
                                                                                                                    Bool _t1613; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1612); _t1613 = *_hp; free(_hp); }
                                                                                                                    (void)_t1613;
                                                                                                                    Str_delete(_t1612, &(Bool){1});
                                                                                                                    if (_t1613) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1597, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1610 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t1610;
                                                                                                                        Bool _t1611; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1610); _t1611 = *_hp; free(_hp); }
                                                                                                                        (void)_t1611;
                                                                                                                        Str_delete(_t1610, &(Bool){1});
                                                                                                                        if (_t1611) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1597, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1608 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t1608;
                                                                                                                            Bool _t1609; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1608); _t1609 = *_hp; free(_hp); }
                                                                                                                            (void)_t1609;
                                                                                                                            Str_delete(_t1608, &(Bool){1});
                                                                                                                            if (_t1609) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1597, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1606 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t1606;
                                                                                                                                Bool _t1607; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1606); _t1607 = *_hp; free(_hp); }
                                                                                                                                (void)_t1607;
                                                                                                                                Str_delete(_t1606, &(Bool){1});
                                                                                                                                if (_t1607) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1597, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1604 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t1604;
                                                                                                                                    Bool _t1605; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1604); _t1605 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1605;
                                                                                                                                    Str_delete(_t1604, &(Bool){1});
                                                                                                                                    if (_t1605) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1597, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1602 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t1602;
                                                                                                                                        Bool _t1603; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1602); _t1603 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1603;
                                                                                                                                        Str_delete(_t1602, &(Bool){1});
                                                                                                                                        if (_t1603) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1597, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1600 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t1600;
                                                                                                                                            Bool _t1601; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1600); _t1601 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1601;
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1597, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1598 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t1598;
                                                                                                                                                Bool _t1599; { Bool *_hp = (Bool *)Str_eq(_sw1597, _t1598); _t1599 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1599;
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1597, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw1597, &(Bool){1});
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
        Str_delete(_sw1597, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2004 = Str_lit("Token", 5ULL);
    (void)_t2004;
    U64 _t2005; { U64 *_hp = (U64 *)Token_size(); _t2005 = *_hp; free(_hp); }
    (void)_t2005;
    Vec *tokens = Vec_new(_t2004, &(U64){_t2005});
    (void)tokens;
    Str_delete(_t2004, &(Bool){1});
    ;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    (void)pos;
    I64 line = 1;
    (void)line;
    U64 line_start = 0;
    (void)line_start;
    U64 src_len; { U64 *_hp = (U64 *)Str_len(src); src_len = *_hp; free(_hp); }
    (void)src_len;
    while (1) {
        Bool _wcond1668; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1668 = *_hp; free(_hp); }
        (void)_wcond1668;
        if (_wcond1668) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t1950 = 32;
        (void)_t1950;
        U8 _t1951 = 9;
        (void)_t1951;
        Bool _t1952 = U8_eq(DEREF(c), _t1950);
        (void)_t1952;
        ;
        Bool _t1953 = U8_eq(DEREF(c), _t1951);
        (void)_t1953;
        ;
        U8 _t1954 = 13;
        (void)_t1954;
        Bool _t1955 = Bool_or(_t1952, _t1953);
        (void)_t1955;
        ;
        ;
        Bool _t1956 = U8_eq(DEREF(c), _t1954);
        (void)_t1956;
        ;
        U8 _t1957 = 59;
        (void)_t1957;
        Bool _t1958 = Bool_or(_t1955, _t1956);
        (void)_t1958;
        ;
        ;
        Bool _t1959 = U8_eq(DEREF(c), _t1957);
        (void)_t1959;
        ;
        Bool _t1960 = Bool_or(_t1958, _t1959);
        (void)_t1960;
        ;
        ;
        if (_t1960) {
            U64 _t1669 = U64_inc(DEREF(pos));
            (void)_t1669;
            *pos = _t1669;
            ;
            ;
            continue;
        }
        ;
        U8 _t1961 = 10;
        (void)_t1961;
        Bool _t1962 = U8_eq(DEREF(c), _t1961);
        (void)_t1962;
        ;
        if (_t1962) {
            U64 _t1670 = U64_inc(DEREF(pos));
            (void)_t1670;
            *pos = _t1670;
            ;
            I64 _t1671 = 1;
            (void)_t1671;
            I64 _t1672 = I64_add(line, _t1671);
            (void)_t1672;
            ;
            line = _t1672;
            ;
            U64 _t1673 = U64_clone(pos);
            (void)_t1673;
            line_start = _t1673;
            ;
            ;
            continue;
        }
        ;
        U64 _t1963 = U64_sub(DEREF(pos), line_start);
        (void)_t1963;
        U64 _t1964 = 1;
        (void)_t1964;
        U64 _t1965 = U64_add(_t1963, _t1964);
        (void)_t1965;
        ;
        ;
        I64 col = U64_to_i64(_t1965);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t1966 = 35;
        (void)_t1966;
        Bool _t1967 = U8_eq(DEREF(c), _t1966);
        (void)_t1967;
        ;
        if (_t1967) {
            while (1) {
                Bool _wcond1674; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1674 = *_hp; free(_hp); }
                (void)_wcond1674;
                if (_wcond1674) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1675 = Str_byte_at(src, pos);
                (void)_t1675;
                U8 _t1676 = 10;
                (void)_t1676;
                Bool _t1677 = U8_eq(DEREF(_t1675), _t1676);
                (void)_t1677;
                ;
                if (_t1677) {
                    ;
                    break;
                }
                ;
                U64 _t1678 = U64_inc(DEREF(pos));
                (void)_t1678;
                *pos = _t1678;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1968 = 47;
        (void)_t1968;
        U64 _t1969 = 1;
        (void)_t1969;
        U64 _t1970 = U64_add(DEREF(pos), _t1969);
        (void)_t1970;
        ;
        Bool _t1971 = U8_eq(DEREF(c), _t1968);
        (void)_t1971;
        ;
        Bool _t1972; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1970}, &(U64){src_len}); _t1972 = *_hp; free(_hp); }
        (void)_t1972;
        ;
        Bool _t1973 = Bool_and(_t1971, _t1972);
        (void)_t1973;
        ;
        ;
        if (_t1973) {
            U64 _t1737 = 1;
            (void)_t1737;
            U64 *_t1738 = malloc(sizeof(U64)); *_t1738 = U64_add(DEREF(pos), _t1737);
            (void)_t1738;
            ;
            U8 *c2 = Str_byte_at(src, _t1738);
            (void)c2;
            U8 _t1739 = 47;
            (void)_t1739;
            Bool _t1740 = U8_eq(DEREF(c2), _t1739);
            (void)_t1740;
            ;
            if (_t1740) {
                while (1) {
                    Bool _wcond1679; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1679 = *_hp; free(_hp); }
                    (void)_wcond1679;
                    if (_wcond1679) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1680 = Str_byte_at(src, pos);
                    (void)_t1680;
                    U8 _t1681 = 10;
                    (void)_t1681;
                    Bool _t1682 = U8_eq(DEREF(_t1680), _t1681);
                    (void)_t1682;
                    ;
                    if (_t1682) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1683 = U64_inc(DEREF(pos));
                    (void)_t1683;
                    *pos = _t1683;
                    ;
                }
                U64_delete(_t1738, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1741 = 42;
            (void)_t1741;
            Bool _t1742 = U8_eq(DEREF(c2), _t1741);
            (void)_t1742;
            U64_delete(_t1738, &(Bool){1});
            ;
            if (_t1742) {
                U64 _t1733 = 2;
                (void)_t1733;
                U64 _t1734 = U64_add(DEREF(pos), _t1733);
                (void)_t1734;
                ;
                *pos = _t1734;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond1684; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1684 = *_hp; free(_hp); }
                    (void)_wcond1684;
                    if (_wcond1684) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1709 = 0;
                    (void)_t1709;
                    Bool _t1710; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t1709}); _t1710 = *_hp; free(_hp); }
                    (void)_t1710;
                    ;
                    if (_t1710) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1711 = 1;
                    (void)_t1711;
                    U64 _t1712 = U64_add(DEREF(pos), _t1711);
                    (void)_t1712;
                    ;
                    Bool _t1713; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1712}, &(U64){src_len}); _t1713 = *_hp; free(_hp); }
                    (void)_t1713;
                    ;
                    if (_t1713) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t1693 = 1;
                        (void)_t1693;
                        U64 *_t1694 = malloc(sizeof(U64)); *_t1694 = U64_add(DEREF(pos), _t1693);
                        (void)_t1694;
                        ;
                        U8 *b2 = Str_byte_at(src, _t1694);
                        (void)b2;
                        U8 _t1695 = 47;
                        (void)_t1695;
                        U8 _t1696 = 42;
                        (void)_t1696;
                        Bool _t1697 = U8_eq(DEREF(b1), _t1695);
                        (void)_t1697;
                        ;
                        Bool _t1698 = U8_eq(DEREF(b2), _t1696);
                        (void)_t1698;
                        ;
                        Bool _t1699 = Bool_and(_t1697, _t1698);
                        (void)_t1699;
                        ;
                        ;
                        if (_t1699) {
                            I64 _t1685 = 1;
                            (void)_t1685;
                            I64 _t1686 = I64_add(depth, _t1685);
                            (void)_t1686;
                            ;
                            depth = _t1686;
                            ;
                            U64 _t1687 = 2;
                            (void)_t1687;
                            U64 _t1688 = U64_add(DEREF(pos), _t1687);
                            (void)_t1688;
                            ;
                            *pos = _t1688;
                            ;
                            U64_delete(_t1694, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1700 = 42;
                        (void)_t1700;
                        U8 _t1701 = 47;
                        (void)_t1701;
                        Bool _t1702 = U8_eq(DEREF(b1), _t1700);
                        (void)_t1702;
                        ;
                        Bool _t1703 = U8_eq(DEREF(b2), _t1701);
                        (void)_t1703;
                        U64_delete(_t1694, &(Bool){1});
                        ;
                        Bool _t1704 = Bool_and(_t1702, _t1703);
                        (void)_t1704;
                        ;
                        ;
                        if (_t1704) {
                            I64 _t1689 = 1;
                            (void)_t1689;
                            I64 _t1690 = I64_sub(depth, _t1689);
                            (void)_t1690;
                            ;
                            depth = _t1690;
                            ;
                            U64 _t1691 = 2;
                            (void)_t1691;
                            U64 _t1692 = U64_add(DEREF(pos), _t1691);
                            (void)_t1692;
                            ;
                            *pos = _t1692;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1714 = Str_byte_at(src, pos);
                    (void)_t1714;
                    U8 _t1715 = 10;
                    (void)_t1715;
                    Bool _t1716 = U8_eq(DEREF(_t1714), _t1715);
                    (void)_t1716;
                    ;
                    if (_t1716) {
                        I64 _t1705 = 1;
                        (void)_t1705;
                        I64 _t1706 = I64_add(line, _t1705);
                        (void)_t1706;
                        ;
                        line = _t1706;
                        ;
                        U64 _t1707 = 1;
                        (void)_t1707;
                        U64 _t1708 = U64_add(DEREF(pos), _t1707);
                        (void)_t1708;
                        ;
                        line_start = _t1708;
                        ;
                    }
                    ;
                    U64 _t1717 = U64_inc(DEREF(pos));
                    (void)_t1717;
                    *pos = _t1717;
                    ;
                }
                I64 _t1735 = 0;
                (void)_t1735;
                Bool _t1736; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t1735}); _t1736 = *_hp; free(_hp); }
                (void)_t1736;
                ;
                ;
                if (_t1736) {
                    Str *_t1718 = Str_lit("Str", 3ULL);
                    (void)_t1718;
                    U64 _t1719; { U64 *_hp = (U64 *)Str_size(); _t1719 = *_hp; free(_hp); }
                    (void)_t1719;
                    U64 _t1720 = 6;
                    (void)_t1720;
                    Array *_va20 = Array_new(_t1718, &(U64){_t1719}, &(U64){_t1720});
                    (void)_va20;
                    Str_delete(_t1718, &(Bool){1});
                    ;
                    ;
                    U64 _t1721 = 0;
                    (void)_t1721;
                    Str *_t1722 = Str_clone(path);
                    (void)_t1722;
                    Array_set(_va20, &(U64){_t1721}, _t1722);
                    ;
                    U64 _t1723 = 1;
                    (void)_t1723;
                    Str *_t1724 = Str_lit(":", 1ULL);
                    (void)_t1724;
                    Array_set(_va20, &(U64){_t1723}, _t1724);
                    ;
                    U64 _t1725 = 2;
                    (void)_t1725;
                    Str *_t1726 = I64_to_str(&(I64){line});
                    (void)_t1726;
                    Array_set(_va20, &(U64){_t1725}, _t1726);
                    ;
                    U64 _t1727 = 3;
                    (void)_t1727;
                    Str *_t1728 = Str_lit(":", 1ULL);
                    (void)_t1728;
                    Array_set(_va20, &(U64){_t1727}, _t1728);
                    ;
                    U64 _t1729 = 4;
                    (void)_t1729;
                    Str *_t1730 = I64_to_str(&(I64){col});
                    (void)_t1730;
                    Array_set(_va20, &(U64){_t1729}, _t1730);
                    ;
                    U64 _t1731 = 5;
                    (void)_t1731;
                    Str *_t1732 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t1732;
                    Array_set(_va20, &(U64){_t1731}, _t1732);
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
        Bool _t1974; { Bool *_hp = (Bool *)is_digit(c); _t1974 = *_hp; free(_hp); }
        (void)_t1974;
        if (_t1974) {
            while (1) {
                Bool _wcond1743; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1743 = *_hp; free(_hp); }
                (void)_wcond1743;
                if (_wcond1743) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1744 = Str_byte_at(src, pos);
                (void)_t1744;
                Bool _t1745; { Bool *_hp = (Bool *)is_digit(_t1744); _t1745 = *_hp; free(_hp); }
                (void)_t1745;
                Bool _t1746 = Bool_not(_t1745);
                (void)_t1746;
                ;
                if (_t1746) {
                    ;
                    break;
                }
                ;
                U64 _t1747 = U64_inc(DEREF(pos));
                (void)_t1747;
                *pos = _t1747;
                ;
            }
            U64 _t1762 = 1;
            (void)_t1762;
            U64 _t1763 = U64_add(DEREF(pos), _t1762);
            (void)_t1763;
            ;
            Bool _t1764; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1763}, &(U64){src_len}); _t1764 = *_hp; free(_hp); }
            (void)_t1764;
            ;
            if (_t1764) {
                U8 *_t1754 = Str_byte_at(src, pos);
                (void)_t1754;
                U8 _t1755 = 46;
                (void)_t1755;
                U64 _t1756 = 1;
                (void)_t1756;
                U64 *_t1757 = malloc(sizeof(U64)); *_t1757 = U64_add(DEREF(pos), _t1756);
                (void)_t1757;
                ;
                U8 *_t1758 = Str_byte_at(src, _t1757);
                (void)_t1758;
                Bool _t1759 = U8_eq(DEREF(_t1754), _t1755);
                (void)_t1759;
                ;
                Bool _t1760; { Bool *_hp = (Bool *)is_digit(_t1758); _t1760 = *_hp; free(_hp); }
                (void)_t1760;
                U64_delete(_t1757, &(Bool){1});
                Bool _t1761 = Bool_and(_t1759, _t1760);
                (void)_t1761;
                ;
                ;
                if (_t1761) {
                    U64 _t1753 = U64_inc(DEREF(pos));
                    (void)_t1753;
                    *pos = _t1753;
                    ;
                    while (1) {
                        Bool _wcond1748; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1748 = *_hp; free(_hp); }
                        (void)_wcond1748;
                        if (_wcond1748) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1749 = Str_byte_at(src, pos);
                        (void)_t1749;
                        Bool _t1750; { Bool *_hp = (Bool *)is_digit(_t1749); _t1750 = *_hp; free(_hp); }
                        (void)_t1750;
                        Bool _t1751 = Bool_not(_t1750);
                        (void)_t1751;
                        ;
                        if (_t1751) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1752 = U64_inc(DEREF(pos));
                        (void)_t1752;
                        *pos = _t1752;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1765 = U64_sub(DEREF(pos), start);
            (void)_t1765;
            I64 _t1766 = I64_clone(&(I64){col});
            (void)_t1766;
            Token *_t1767 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1767->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1765}); _t1767->text = *_ca; free(_ca); }
            _t1767->line = I64_clone(&(I64){line});
            _t1767->col = _t1766;
            (void)_t1767;
            ;
            ;
            Vec_push(tokens, _t1767);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1975; { Bool *_hp = (Bool *)is_alpha(c); _t1975 = *_hp; free(_hp); }
        (void)_t1975;
        if (_t1975) {
            while (1) {
                Bool _wcond1768; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1768 = *_hp; free(_hp); }
                (void)_wcond1768;
                if (_wcond1768) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1769 = Str_byte_at(src, pos);
                (void)_t1769;
                Bool _t1770; { Bool *_hp = (Bool *)is_alnum(_t1769); _t1770 = *_hp; free(_hp); }
                (void)_t1770;
                Bool _t1771 = Bool_not(_t1770);
                (void)_t1771;
                ;
                if (_t1771) {
                    ;
                    break;
                }
                ;
                U64 _t1772 = U64_inc(DEREF(pos));
                (void)_t1772;
                *pos = _t1772;
                ;
            }
            U64 _t1773 = U64_sub(DEREF(pos), start);
            (void)_t1773;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1773});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            I64 _t1774 = I64_clone(&(I64){line});
            (void)_t1774;
            I64 _t1775 = I64_clone(&(I64){col});
            (void)_t1775;
            Token *_t1776 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1776->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1776->text = *_ca; free(_ca); }
            _t1776->line = _t1774;
            _t1776->col = _t1775;
            (void)_t1776;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1776);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1976 = 34;
        (void)_t1976;
        Bool _t1977 = U8_eq(DEREF(c), _t1976);
        (void)_t1977;
        ;
        if (_t1977) {
            U64 _t1823 = U64_inc(DEREF(pos));
            (void)_t1823;
            *pos = _t1823;
            ;
            while (1) {
                Bool _wcond1777; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1777 = *_hp; free(_hp); }
                (void)_wcond1777;
                if (_wcond1777) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1783 = Str_byte_at(src, pos);
                (void)_t1783;
                U8 _t1784 = 34;
                (void)_t1784;
                Bool _t1785 = U8_eq(DEREF(_t1783), _t1784);
                (void)_t1785;
                ;
                if (_t1785) {
                    ;
                    break;
                }
                ;
                U8 *_t1786 = Str_byte_at(src, pos);
                (void)_t1786;
                U8 _t1787 = 92;
                (void)_t1787;
                U64 _t1788 = 1;
                (void)_t1788;
                U64 _t1789 = U64_add(DEREF(pos), _t1788);
                (void)_t1789;
                ;
                Bool _t1790 = U8_eq(DEREF(_t1786), _t1787);
                (void)_t1790;
                ;
                Bool _t1791; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1789}, &(U64){src_len}); _t1791 = *_hp; free(_hp); }
                (void)_t1791;
                ;
                Bool _t1792 = Bool_and(_t1790, _t1791);
                (void)_t1792;
                ;
                ;
                if (_t1792) {
                    U64 _t1778 = U64_inc(DEREF(pos));
                    (void)_t1778;
                    *pos = _t1778;
                    ;
                }
                ;
                U8 *_t1793 = Str_byte_at(src, pos);
                (void)_t1793;
                U8 _t1794 = 10;
                (void)_t1794;
                Bool _t1795 = U8_eq(DEREF(_t1793), _t1794);
                (void)_t1795;
                ;
                if (_t1795) {
                    I64 _t1779 = 1;
                    (void)_t1779;
                    I64 _t1780 = I64_add(line, _t1779);
                    (void)_t1780;
                    ;
                    line = _t1780;
                    ;
                    U64 _t1781 = 1;
                    (void)_t1781;
                    U64 _t1782 = U64_add(DEREF(pos), _t1781);
                    (void)_t1782;
                    ;
                    line_start = _t1782;
                    ;
                }
                ;
                U64 _t1796 = U64_inc(DEREF(pos));
                (void)_t1796;
                *pos = _t1796;
                ;
            }
            U8 *_t1824 = Str_byte_at(src, pos);
            (void)_t1824;
            U8 _t1825 = 34;
            (void)_t1825;
            Bool _t1826; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1826 = *_hp; free(_hp); }
            (void)_t1826;
            Bool _t1827 = U8_eq(DEREF(_t1824), _t1825);
            (void)_t1827;
            ;
            Bool _t1828 = Bool_and(_t1826, _t1827);
            (void)_t1828;
            ;
            ;
            if (_t1828) {
                U64 _t1797 = U64_inc(DEREF(pos));
                (void)_t1797;
                *pos = _t1797;
                ;
                U64 _t1798 = 1;
                (void)_t1798;
                U64 _t1799 = U64_sub(DEREF(pos), start);
                (void)_t1799;
                U64 _t1800 = 2;
                (void)_t1800;
                U64 _t1801 = U64_add(start, _t1798);
                (void)_t1801;
                ;
                U64 _t1802 = U64_sub(_t1799, _t1800);
                (void)_t1802;
                ;
                ;
                I64 _t1803 = I64_clone(&(I64){col});
                (void)_t1803;
                Token *_t1804 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1804->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){_t1801}, &(U64){_t1802}); _t1804->text = *_ca; free(_ca); }
                _t1804->line = I64_clone(&(I64){line});
                _t1804->col = _t1803;
                (void)_t1804;
                ;
                ;
                ;
                Vec_push(tokens, _t1804);
            } else {
                Str *_t1805 = Str_lit("Str", 3ULL);
                (void)_t1805;
                U64 _t1806; { U64 *_hp = (U64 *)Str_size(); _t1806 = *_hp; free(_hp); }
                (void)_t1806;
                U64 _t1807 = 6;
                (void)_t1807;
                Array *_va21 = Array_new(_t1805, &(U64){_t1806}, &(U64){_t1807});
                (void)_va21;
                Str_delete(_t1805, &(Bool){1});
                ;
                ;
                U64 _t1808 = 0;
                (void)_t1808;
                Str *_t1809 = Str_clone(path);
                (void)_t1809;
                Array_set(_va21, &(U64){_t1808}, _t1809);
                ;
                U64 _t1810 = 1;
                (void)_t1810;
                Str *_t1811 = Str_lit(":", 1ULL);
                (void)_t1811;
                Array_set(_va21, &(U64){_t1810}, _t1811);
                ;
                U64 _t1812 = 2;
                (void)_t1812;
                Str *_t1813 = I64_to_str(&(I64){line});
                (void)_t1813;
                Array_set(_va21, &(U64){_t1812}, _t1813);
                ;
                U64 _t1814 = 3;
                (void)_t1814;
                Str *_t1815 = Str_lit(":", 1ULL);
                (void)_t1815;
                Array_set(_va21, &(U64){_t1814}, _t1815);
                ;
                U64 _t1816 = 4;
                (void)_t1816;
                Str *_t1817 = I64_to_str(&(I64){col});
                (void)_t1817;
                Array_set(_va21, &(U64){_t1816}, _t1817);
                ;
                U64 _t1818 = 5;
                (void)_t1818;
                Str *_t1819 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1819;
                Array_set(_va21, &(U64){_t1818}, _t1819);
                ;
                println(_va21);
                U64 _t1820 = U64_sub(DEREF(pos), start);
                (void)_t1820;
                I64 _t1821 = I64_clone(&(I64){col});
                (void)_t1821;
                Token *_t1822 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1822->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1820}); _t1822->text = *_ca; free(_ca); }
                _t1822->line = I64_clone(&(I64){line});
                _t1822->col = _t1821;
                (void)_t1822;
                ;
                ;
                Vec_push(tokens, _t1822);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1978 = 39;
        (void)_t1978;
        Bool _t1979 = U8_eq(DEREF(c), _t1978);
        (void)_t1979;
        ;
        if (_t1979) {
            U64 _t1852 = U64_inc(DEREF(pos));
            (void)_t1852;
            *pos = _t1852;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t1853 = Str_byte_at(src, pos);
            (void)_t1853;
            U8 _t1854 = 92;
            (void)_t1854;
            U64 _t1855 = 1;
            (void)_t1855;
            U64 _t1856 = U64_add(DEREF(pos), _t1855);
            (void)_t1856;
            ;
            Bool _t1857 = U8_eq(DEREF(_t1853), _t1854);
            (void)_t1857;
            ;
            Bool _t1858; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1856}, &(U64){src_len}); _t1858 = *_hp; free(_hp); }
            (void)_t1858;
            ;
            Bool _t1859; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1859 = *_hp; free(_hp); }
            (void)_t1859;
            Bool _t1860 = Bool_and(_t1857, _t1858);
            (void)_t1860;
            ;
            ;
            Bool _t1861 = Bool_and(_t1859, _t1860);
            (void)_t1861;
            ;
            ;
            if (_t1861) {
                U64 _t1829 = U64_inc(DEREF(pos));
                (void)_t1829;
                *pos = _t1829;
                ;
            }
            ;
            U64 _t1862 = U64_inc(DEREF(pos));
            (void)_t1862;
            *pos = _t1862;
            ;
            U8 *_t1863 = Str_byte_at(src, pos);
            (void)_t1863;
            U8 _t1864 = 39;
            (void)_t1864;
            Bool _t1865; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1865 = *_hp; free(_hp); }
            (void)_t1865;
            Bool _t1866 = U8_eq(DEREF(_t1863), _t1864);
            (void)_t1866;
            ;
            Bool _t1867 = Bool_and(_t1865, _t1866);
            (void)_t1867;
            ;
            ;
            if (_t1867) {
                U64 _t1830 = U64_sub(DEREF(pos), ch_start);
                (void)_t1830;
                I64 _t1831 = I64_clone(&(I64){col});
                (void)_t1831;
                Token *_t1832 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1832->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){ch_start}, &(U64){_t1830}); _t1832->text = *_ca; free(_ca); }
                _t1832->line = I64_clone(&(I64){line});
                _t1832->col = _t1831;
                (void)_t1832;
                ;
                ;
                Vec_push(tokens, _t1832);
                U64 _t1833 = U64_inc(DEREF(pos));
                (void)_t1833;
                *pos = _t1833;
                ;
            } else {
                Str *_t1834 = Str_lit("Str", 3ULL);
                (void)_t1834;
                U64 _t1835; { U64 *_hp = (U64 *)Str_size(); _t1835 = *_hp; free(_hp); }
                (void)_t1835;
                U64 _t1836 = 6;
                (void)_t1836;
                Array *_va22 = Array_new(_t1834, &(U64){_t1835}, &(U64){_t1836});
                (void)_va22;
                Str_delete(_t1834, &(Bool){1});
                ;
                ;
                U64 _t1837 = 0;
                (void)_t1837;
                Str *_t1838 = Str_clone(path);
                (void)_t1838;
                Array_set(_va22, &(U64){_t1837}, _t1838);
                ;
                U64 _t1839 = 1;
                (void)_t1839;
                Str *_t1840 = Str_lit(":", 1ULL);
                (void)_t1840;
                Array_set(_va22, &(U64){_t1839}, _t1840);
                ;
                U64 _t1841 = 2;
                (void)_t1841;
                Str *_t1842 = I64_to_str(&(I64){line});
                (void)_t1842;
                Array_set(_va22, &(U64){_t1841}, _t1842);
                ;
                U64 _t1843 = 3;
                (void)_t1843;
                Str *_t1844 = Str_lit(":", 1ULL);
                (void)_t1844;
                Array_set(_va22, &(U64){_t1843}, _t1844);
                ;
                U64 _t1845 = 4;
                (void)_t1845;
                Str *_t1846 = I64_to_str(&(I64){col});
                (void)_t1846;
                Array_set(_va22, &(U64){_t1845}, _t1846);
                ;
                U64 _t1847 = 5;
                (void)_t1847;
                Str *_t1848 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t1848;
                Array_set(_va22, &(U64){_t1847}, _t1848);
                ;
                println(_va22);
                U64 _t1849 = U64_sub(DEREF(pos), start);
                (void)_t1849;
                I64 _t1850 = I64_clone(&(I64){col});
                (void)_t1850;
                Token *_t1851 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1851->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1849}); _t1851->text = *_ca; free(_ca); }
                _t1851->line = I64_clone(&(I64){line});
                _t1851->col = _t1850;
                (void)_t1851;
                ;
                ;
                Vec_push(tokens, _t1851);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t1980 = 1;
        (void)_t1980;
        U64 _t1981 = U64_add(DEREF(pos), _t1980);
        (void)_t1981;
        ;
        Bool _t1982; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1981}, &(U64){src_len}); _t1982 = *_hp; free(_hp); }
        (void)_t1982;
        ;
        if (_t1982) {
            U64 _t1899 = 1;
            (void)_t1899;
            U64 *_t1900 = malloc(sizeof(U64)); *_t1900 = U64_add(DEREF(pos), _t1899);
            (void)_t1900;
            ;
            U8 *c2 = Str_byte_at(src, _t1900);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t1901 = 58;
            (void)_t1901;
            U8 _t1902 = 61;
            (void)_t1902;
            Bool _t1903 = U8_eq(DEREF(c), _t1901);
            (void)_t1903;
            ;
            Bool _t1904 = U8_eq(DEREF(c2), _t1902);
            (void)_t1904;
            ;
            Bool _t1905 = Bool_and(_t1903, _t1904);
            (void)_t1905;
            ;
            ;
            if (_t1905) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t1888 = 61;
                (void)_t1888;
                U8 _t1889 = 61;
                (void)_t1889;
                Bool _t1890 = U8_eq(DEREF(c), _t1888);
                (void)_t1890;
                ;
                Bool _t1891 = U8_eq(DEREF(c2), _t1889);
                (void)_t1891;
                ;
                Bool _t1892 = Bool_and(_t1890, _t1891);
                (void)_t1892;
                ;
                ;
                if (_t1892) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t1883 = 33;
                    (void)_t1883;
                    U8 _t1884 = 61;
                    (void)_t1884;
                    Bool _t1885 = U8_eq(DEREF(c), _t1883);
                    (void)_t1885;
                    ;
                    Bool _t1886 = U8_eq(DEREF(c2), _t1884);
                    (void)_t1886;
                    ;
                    Bool _t1887 = Bool_and(_t1885, _t1886);
                    (void)_t1887;
                    ;
                    ;
                    if (_t1887) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t1878 = 60;
                        (void)_t1878;
                        U8 _t1879 = 61;
                        (void)_t1879;
                        Bool _t1880 = U8_eq(DEREF(c), _t1878);
                        (void)_t1880;
                        ;
                        Bool _t1881 = U8_eq(DEREF(c2), _t1879);
                        (void)_t1881;
                        ;
                        Bool _t1882 = Bool_and(_t1880, _t1881);
                        (void)_t1882;
                        ;
                        ;
                        if (_t1882) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t1873 = 62;
                            (void)_t1873;
                            U8 _t1874 = 61;
                            (void)_t1874;
                            Bool _t1875 = U8_eq(DEREF(c), _t1873);
                            (void)_t1875;
                            ;
                            Bool _t1876 = U8_eq(DEREF(c2), _t1874);
                            (void)_t1876;
                            ;
                            Bool _t1877 = Bool_and(_t1875, _t1876);
                            (void)_t1877;
                            ;
                            ;
                            if (_t1877) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t1868 = 46;
                                (void)_t1868;
                                U8 _t1869 = 46;
                                (void)_t1869;
                                Bool _t1870 = U8_eq(DEREF(c), _t1868);
                                (void)_t1870;
                                ;
                                Bool _t1871 = U8_eq(DEREF(c2), _t1869);
                                (void)_t1871;
                                ;
                                Bool _t1872 = Bool_and(_t1870, _t1871);
                                (void)_t1872;
                                ;
                                ;
                                if (_t1872) {
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
            U64_delete(_t1900, &(Bool){1});
            ;
            Bool _t1906; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t1906 = *_hp; free(_hp); }
            (void)_t1906;
            Bool _t1907 = Bool_not(_t1906);
            (void)_t1907;
            ;
            if (_t1907) {
                U64 _t1893 = 2;
                (void)_t1893;
                I64 _t1894 = I64_clone(&(I64){line});
                (void)_t1894;
                I64 _t1895 = I64_clone(&(I64){col});
                (void)_t1895;
                Token *_t1896 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1896->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1893}); _t1896->text = *_ca; free(_ca); }
                _t1896->line = _t1894;
                _t1896->col = _t1895;
                (void)_t1896;
                ;
                ;
                ;
                Vec_push(tokens, _t1896);
                U64 _t1897 = 2;
                (void)_t1897;
                U64 _t1898 = U64_add(DEREF(pos), _t1897);
                (void)_t1898;
                ;
                *pos = _t1898;
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
        (void)single;
        {
            U8 _sw1908 = U8_clone(c);
            (void)_sw1908;
            U8 _t1943 = 40;
            (void)_t1943;
            Bool _t1944 = U8_eq(_sw1908, _t1943);
            (void)_t1944;
            ;
            if (_t1944) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1941 = 41;
                (void)_t1941;
                Bool _t1942 = U8_eq(_sw1908, _t1941);
                (void)_t1942;
                ;
                if (_t1942) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1939 = 123;
                    (void)_t1939;
                    Bool _t1940 = U8_eq(_sw1908, _t1939);
                    (void)_t1940;
                    ;
                    if (_t1940) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1937 = 125;
                        (void)_t1937;
                        Bool _t1938 = U8_eq(_sw1908, _t1937);
                        (void)_t1938;
                        ;
                        if (_t1938) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1935 = 91;
                            (void)_t1935;
                            Bool _t1936 = U8_eq(_sw1908, _t1935);
                            (void)_t1936;
                            ;
                            if (_t1936) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1933 = 93;
                                (void)_t1933;
                                Bool _t1934 = U8_eq(_sw1908, _t1933);
                                (void)_t1934;
                                ;
                                if (_t1934) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1931 = 44;
                                    (void)_t1931;
                                    Bool _t1932 = U8_eq(_sw1908, _t1931);
                                    (void)_t1932;
                                    ;
                                    if (_t1932) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1929 = 58;
                                        (void)_t1929;
                                        Bool _t1930 = U8_eq(_sw1908, _t1929);
                                        (void)_t1930;
                                        ;
                                        if (_t1930) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1927 = 46;
                                            (void)_t1927;
                                            Bool _t1928 = U8_eq(_sw1908, _t1927);
                                            (void)_t1928;
                                            ;
                                            if (_t1928) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1925 = 63;
                                                (void)_t1925;
                                                Bool _t1926 = U8_eq(_sw1908, _t1925);
                                                (void)_t1926;
                                                ;
                                                if (_t1926) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1923 = 33;
                                                    (void)_t1923;
                                                    Bool _t1924 = U8_eq(_sw1908, _t1923);
                                                    (void)_t1924;
                                                    ;
                                                    if (_t1924) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1921 = 43;
                                                        (void)_t1921;
                                                        Bool _t1922 = U8_eq(_sw1908, _t1921);
                                                        (void)_t1922;
                                                        ;
                                                        if (_t1922) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1919 = 45;
                                                            (void)_t1919;
                                                            Bool _t1920 = U8_eq(_sw1908, _t1919);
                                                            (void)_t1920;
                                                            ;
                                                            if (_t1920) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1917 = 42;
                                                                (void)_t1917;
                                                                Bool _t1918 = U8_eq(_sw1908, _t1917);
                                                                (void)_t1918;
                                                                ;
                                                                if (_t1918) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1915 = 47;
                                                                    (void)_t1915;
                                                                    Bool _t1916 = U8_eq(_sw1908, _t1915);
                                                                    (void)_t1916;
                                                                    ;
                                                                    if (_t1916) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1913 = 61;
                                                                        (void)_t1913;
                                                                        Bool _t1914 = U8_eq(_sw1908, _t1913);
                                                                        (void)_t1914;
                                                                        ;
                                                                        if (_t1914) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1911 = 60;
                                                                            (void)_t1911;
                                                                            Bool _t1912 = U8_eq(_sw1908, _t1911);
                                                                            (void)_t1912;
                                                                            ;
                                                                            if (_t1912) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1909 = 62;
                                                                                (void)_t1909;
                                                                                Bool _t1910 = U8_eq(_sw1908, _t1909);
                                                                                (void)_t1910;
                                                                                ;
                                                                                if (_t1910) {
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
        Bool _t1983; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t1983 = *_hp; free(_hp); }
        (void)_t1983;
        Bool _t1984 = Bool_not(_t1983);
        (void)_t1984;
        ;
        if (_t1984) {
            U64 _t1945 = 1;
            (void)_t1945;
            I64 _t1946 = I64_clone(&(I64){line});
            (void)_t1946;
            I64 _t1947 = I64_clone(&(I64){col});
            (void)_t1947;
            Token *_t1948 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1948->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1945}); _t1948->text = *_ca; free(_ca); }
            _t1948->line = _t1946;
            _t1948->col = _t1947;
            (void)_t1948;
            ;
            ;
            ;
            Vec_push(tokens, _t1948);
            U64 _t1949 = U64_inc(DEREF(pos));
            (void)_t1949;
            *pos = _t1949;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t1985 = Str_lit("Str", 3ULL);
        (void)_t1985;
        U64 _t1986; { U64 *_hp = (U64 *)Str_size(); _t1986 = *_hp; free(_hp); }
        (void)_t1986;
        U64 _t1987 = 6;
        (void)_t1987;
        Array *_va23 = Array_new(_t1985, &(U64){_t1986}, &(U64){_t1987});
        (void)_va23;
        Str_delete(_t1985, &(Bool){1});
        ;
        ;
        U64 _t1988 = 0;
        (void)_t1988;
        Str *_t1989 = Str_clone(path);
        (void)_t1989;
        Array_set(_va23, &(U64){_t1988}, _t1989);
        ;
        U64 _t1990 = 1;
        (void)_t1990;
        Str *_t1991 = Str_lit(":", 1ULL);
        (void)_t1991;
        Array_set(_va23, &(U64){_t1990}, _t1991);
        ;
        U64 _t1992 = 2;
        (void)_t1992;
        Str *_t1993 = I64_to_str(&(I64){line});
        (void)_t1993;
        Array_set(_va23, &(U64){_t1992}, _t1993);
        ;
        U64 _t1994 = 3;
        (void)_t1994;
        Str *_t1995 = Str_lit(":", 1ULL);
        (void)_t1995;
        Array_set(_va23, &(U64){_t1994}, _t1995);
        ;
        U64 _t1996 = 4;
        (void)_t1996;
        Str *_t1997 = I64_to_str(&(I64){col});
        (void)_t1997;
        Array_set(_va23, &(U64){_t1996}, _t1997);
        ;
        U64 _t1998 = 5;
        (void)_t1998;
        Str *_t1999 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t1999;
        Array_set(_va23, &(U64){_t1998}, _t1999);
        ;
        println(_va23);
        U64 _t2000 = 1;
        (void)_t2000;
        I64 _t2001 = I64_clone(&(I64){col});
        (void)_t2001;
        ;
        Token *_t2002 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2002->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2000}); _t2002->text = *_ca; free(_ca); }
        _t2002->line = I64_clone(&(I64){line});
        _t2002->col = _t2001;
        (void)_t2002;
        ;
        ;
        ;
        Vec_push(tokens, _t2002);
        U64 _t2003 = U64_inc(DEREF(pos));
        (void)_t2003;
        *pos = _t2003;
        ;
    }
    ;
    U64 _t2006 = U64_sub(DEREF(pos), line_start);
    (void)_t2006;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2007 = 1;
    (void)_t2007;
    U64 _t2008 = U64_add(_t2006, _t2007);
    (void)_t2008;
    ;
    ;
    I64 col = U64_to_i64(_t2008);
    (void)col;
    ;
    I64 _t2009 = I64_clone(&(I64){col});
    (void)_t2009;
    ;
    Token *_t2010 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2010->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2010->text = *_ca; free(_ca); }
    _t2010->line = I64_clone(&(I64){line});
    _t2010->col = _t2009;
    (void)_t2010;
    ;
    ;
    Vec_push(tokens, _t2010);
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
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0) { Tuple_delete(val, arg2); return; }
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
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Tuple", 5ULL) == 0) return (void *)Tuple_clone(val);
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
    _t2011 = malloc(sizeof(I64));
    *_t2011 = 0;
    (void)_t2011;
    _t2012 = malloc(sizeof(I64));
    *_t2012 = 1;
    (void)_t2012;
    _t2013 = malloc(sizeof(I64)); *_t2013 = I64_sub(DEREF(_t2011), DEREF(_t2012));
    (void)_t2013;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2013));
    (void)CAP_LIT;
    _t2014 = malloc(sizeof(I64));
    *_t2014 = 0;
    (void)_t2014;
    _t2015 = malloc(sizeof(I64));
    *_t2015 = 2;
    (void)_t2015;
    _t2016 = malloc(sizeof(I64)); *_t2016 = I64_sub(DEREF(_t2014), DEREF(_t2015));
    (void)_t2016;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2016));
    (void)CAP_VIEW;
}

