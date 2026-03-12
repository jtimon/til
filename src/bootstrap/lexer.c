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
U64 U32_to_u64(U32 val);
static __attribute__((unused)) Str * U32_to_str(U32 * val);
static __attribute__((unused)) U64 * U32_size(void);
static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b);
U32 U64_to_u32(U64 val);
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

static I64 *_t2015;
static I64 *_t2016;
static I64 *_t2017;
static U64 *CAP_LIT;
static I64 *_t2018;
static I64 *_t2019;
static I64 *_t2020;
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

U64 U32_to_u64(U32 val) {
    (void)val;
    I64 _t93 = U32_to_i64(val);
    (void)_t93;
    U64 _t94 = I64_to_u64(_t93);
    (void)_t94;
    ;
    return _t94;
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t95 = U32_to_i64(DEREF(val));
    (void)_t95;
    Str *_t96 = I64_to_str(&(I64){_t95});
    (void)_t96;
    ;
    return _t96;
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t98 = 0;
    (void)_t98;
    I64 _t99 = 1;
    (void)_t99;
    I64 _t100 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t100;
    I64 _t101 = I64_sub(_t98, _t99);
    (void)_t101;
    ;
    ;
    Bool _t102 = I64_eq(_t100, _t101);
    (void)_t102;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t102; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t103 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t103;
    I64 _t104 = 1;
    (void)_t104;
    Bool _t105 = I64_eq(_t103, _t104);
    (void)_t105;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t105; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t106 = U32_eq(DEREF(a), DEREF(b));
    (void)_t106;
    Bool _t107 = Bool_not(_t106);
    (void)_t107;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t107; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t108; { Bool *_hp = (Bool *)U32_gt(a, b); _t108 = *_hp; free(_hp); }
    (void)_t108;
    Bool _t109 = Bool_not(_t108);
    (void)_t109;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t109; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t110; { Bool *_hp = (Bool *)U32_lt(a, b); _t110 = *_hp; free(_hp); }
    (void)_t110;
    Bool _t111 = Bool_not(_t110);
    (void)_t111;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t111; return _r; }
}

U32 U64_to_u32(U64 val) {
    (void)val;
    I64 _t112 = U64_to_i64(val);
    (void)_t112;
    U32 _t113 = I64_to_u32(_t112);
    (void)_t113;
    ;
    return _t113;
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t114 = U64_to_str_ext(val);
    (void)_t114;
    return _t114;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t115 = U64_from_i64_ext(val);
    (void)_t115;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t115; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t117 = 0;
    (void)_t117;
    I64 _t118 = 1;
    (void)_t118;
    I64 _t119 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t119;
    I64 _t120 = I64_sub(_t117, _t118);
    (void)_t120;
    ;
    ;
    Bool _t121 = I64_eq(_t119, _t120);
    (void)_t121;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t121; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t122 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t122;
    I64 _t123 = 1;
    (void)_t123;
    Bool _t124 = I64_eq(_t122, _t123);
    (void)_t124;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t124; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t125 = U64_eq(DEREF(a), DEREF(b));
    (void)_t125;
    Bool _t126 = Bool_not(_t125);
    (void)_t126;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t126; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t127; { Bool *_hp = (Bool *)U64_gt(a, b); _t127 = *_hp; free(_hp); }
    (void)_t127;
    Bool _t128 = Bool_not(_t127);
    (void)_t128;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t128; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t129; { Bool *_hp = (Bool *)U64_lt(a, b); _t129 = *_hp; free(_hp); }
    (void)_t129;
    Bool _t130 = Bool_not(_t129);
    (void)_t130;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t130; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t167 = 0;
    (void)_t167;
    Bool _t168 = I64_eq(DEREF(val), _t167);
    (void)_t168;
    ;
    if (_t168) {
        U64 _t131 = 2;
        (void)_t131;
        U8 *buf = malloc(_t131);
        (void)buf;
        ;
        I64 _t132 = 48;
        (void)_t132;
        U64 _t133 = 1;
        (void)_t133;
        memcpy(buf, &(I64){_t132}, _t133);
        ;
        ;
        U64 *_t134 = malloc(sizeof(U64));
        *_t134 = 1;
        (void)_t134;
        void *_t135 = ptr_add(buf, DEREF(_t134));
        (void)_t135;
        I64 _t136 = 0;
        (void)_t136;
        U64 _t137 = 1;
        (void)_t137;
        memcpy(_t135, &(I64){_t136}, _t137);
        U64_delete(_t134, &(Bool){1});
        ;
        ;
        I64 _t138 = 1;
        (void)_t138;
        I64 _t139 = 1;
        (void)_t139;
        Str *_t140 = malloc(sizeof(Str));
        _t140->c_str = buf;
        _t140->count = _t138;
        _t140->cap = _t139;
        (void)_t140;
        ;
        ;
        ;
        return _t140;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t169 = 0;
    (void)_t169;
    Bool _t170; { Bool *_hp = (Bool *)I64_lt(val, &(I64){_t169}); _t170 = *_hp; free(_hp); }
    (void)_t170;
    ;
    if (_t170) {
        Bool _t141 = 1;
        (void)_t141;
        is_neg = _t141;
        ;
        I64 _t142 = 0;
        (void)_t142;
        I64 _t143 = I64_sub(_t142, DEREF(val));
        (void)_t143;
        ;
        v = _t143;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&(I64){v});
    (void)tmp;
    while (1) {
        I64 _t145 = 0;
        (void)_t145;
        Bool _wcond144; { Bool *_hp = (Bool *)I64_gt(&(I64){tmp}, &(I64){_t145}); _wcond144 = *_hp; free(_hp); }
        (void)_wcond144;
        ;
        if (_wcond144) {
        } else {
            ;
            break;
        }
        ;
        U64 _t146 = 1;
        (void)_t146;
        U64 _t147 = U64_add(ndigits, _t146);
        (void)_t147;
        ;
        ndigits = _t147;
        ;
        I64 _t148 = 10;
        (void)_t148;
        I64 _t149 = I64_div(tmp, _t148);
        (void)_t149;
        ;
        tmp = _t149;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    (void)total;
    ;
    if (is_neg) {
        U64 _t150 = 1;
        (void)_t150;
        U64 _t151 = U64_add(DEREF(total), _t150);
        (void)_t151;
        ;
        *total = _t151;
        ;
    }
    U64 _t171 = 1;
    (void)_t171;
    U64 _t172 = U64_add(DEREF(total), _t171);
    (void)_t172;
    ;
    U8 *buf = malloc(_t172);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t152 = 45;
        (void)_t152;
        U64 _t153 = 1;
        (void)_t153;
        memcpy(buf, &(I64){_t152}, _t153);
        ;
        ;
    }
    ;
    U64 _t173 = 1;
    (void)_t173;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t173);
    (void)i;
    ;
    while (1) {
        I64 _t155 = 0;
        (void)_t155;
        Bool _wcond154; { Bool *_hp = (Bool *)I64_gt(&(I64){v}, &(I64){_t155}); _wcond154 = *_hp; free(_hp); }
        (void)_wcond154;
        ;
        if (_wcond154) {
        } else {
            ;
            break;
        }
        ;
        I64 _t156 = 10;
        (void)_t156;
        I64 _t157 = I64_mod(v, _t156);
        (void)_t157;
        ;
        I64 _t158 = 48;
        (void)_t158;
        I64 _t159 = I64_add(_t157, _t158);
        (void)_t159;
        ;
        ;
        void *_t160 = ptr_add(buf, DEREF(i));
        (void)_t160;
        U8 _t161 = I64_to_u8(_t159);
        (void)_t161;
        ;
        U64 _t162 = 1;
        (void)_t162;
        memcpy(_t160, &(U8){_t161}, _t162);
        ;
        ;
        I64 _t163 = 10;
        (void)_t163;
        I64 _t164 = I64_div(v, _t163);
        (void)_t164;
        ;
        v = _t164;
        ;
        U64 _t165 = 1;
        (void)_t165;
        U64 _t166 = U64_sub(DEREF(i), _t165);
        (void)_t166;
        ;
        *i = _t166;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t174 = ptr_add(buf, DEREF(total));
    (void)_t174;
    I64 _t175 = 0;
    (void)_t175;
    U64 _t176 = 1;
    (void)_t176;
    memcpy(_t174, &(I64){_t175}, _t176);
    ;
    ;
    U64 _t177 = U64_clone(total);
    (void)_t177;
    U64 _t178 = U64_clone(total);
    (void)_t178;
    U64_delete(total, &(Bool){1});
    Str *_t179 = malloc(sizeof(Str));
    _t179->c_str = buf;
    _t179->count = _t177;
    _t179->cap = _t178;
    (void)_t179;
    ;
    ;
    return _t179;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t180 = 0;
    (void)_t180;
    I64 _t181 = I64_sub(_t180, DEREF(a));
    (void)_t181;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t181; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t184 = 0;
    (void)_t184;
    Bool _t185; { Bool *_hp = (Bool *)I64_lt(a, &(I64){_t184}); _t185 = *_hp; free(_hp); }
    (void)_t185;
    ;
    if (_t185) {
        I64 _t182 = 0;
        (void)_t182;
        I64 _t183 = I64_sub(_t182, DEREF(a));
        (void)_t183;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t183; return _r; }
    }
    ;
    I64 _t186 = I64_clone(a);
    (void)_t186;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t186; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t188 = 0;
    (void)_t188;
    I64 _t189 = 1;
    (void)_t189;
    I64 _t190 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t190;
    I64 _t191 = I64_sub(_t188, _t189);
    (void)_t191;
    ;
    ;
    Bool _t192 = I64_eq(_t190, _t191);
    (void)_t192;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t192; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t193 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t193;
    I64 _t194 = 1;
    (void)_t194;
    Bool _t195 = I64_eq(_t193, _t194);
    (void)_t195;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t195; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t196 = I64_eq(DEREF(a), DEREF(b));
    (void)_t196;
    Bool _t197 = Bool_not(_t196);
    (void)_t197;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t197; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t198; { Bool *_hp = (Bool *)I64_gt(a, b); _t198 = *_hp; free(_hp); }
    (void)_t198;
    Bool _t199 = Bool_not(_t198);
    (void)_t199;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t199; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t200; { Bool *_hp = (Bool *)I64_lt(a, b); _t200 = *_hp; free(_hp); }
    (void)_t200;
    Bool _t201 = Bool_not(_t200);
    (void)_t201;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t201; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    (void)start;
    (void)end;
    U64 _t202 = U64_clone(&(U64){start});
    (void)_t202;
    U64 _t203 = U64_clone(&(U64){end});
    (void)_t203;
    Range *_t204 = malloc(sizeof(Range));
    _t204->start = _t202;
    _t204->end = _t203;
    (void)_t204;
    ;
    ;
    return _t204;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t206; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t206 = *_hp; free(_hp); }
    (void)_t206;
    if (_t206) {
        U64 _t205 = U64_sub(self->end, self->start);
        (void)_t205;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t205; return _r; }
    }
    ;
    U64 _t207 = U64_sub(self->start, self->end);
    (void)_t207;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t207; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    (void)i;
    Bool _t209; { Bool *_hp = (Bool *)U64_lte(&self->start, &self->end); _t209 = *_hp; free(_hp); }
    (void)_t209;
    if (_t209) {
        U64 _t208 = U64_add(self->start, i);
        (void)_t208;
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t208; return _r; }
    }
    ;
    U64 _t210 = U64_sub(self->start, i);
    (void)_t210;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t210; return _r; }
}

Range * Range_clone(Range * val) {
    (void)val;
    Range *_t211 = malloc(sizeof(Range));
    _t211->start = val->start;
    _t211->end = val->end;
    (void)_t211;
    return _t211;
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
        Str *_t213 = Str_lit("true", 4ULL);
        (void)_t213;
        return _t213;
    } else {
        Str *_t214 = Str_lit("false", 5ULL);
        (void)_t214;
        return _t214;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t219 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t219;
    if (_t219) {
        I64 _t215 = 0;
        (void)_t215;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t215; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t216 = 0;
        (void)_t216;
        I64 _t217 = 1;
        (void)_t217;
        I64 _t218 = I64_sub(_t216, _t217);
        (void)_t218;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t218; return _r; }
    }
    I64 _t220 = 1;
    (void)_t220;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t220; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t222 = 0;
    (void)_t222;
    I64 _t223 = 1;
    (void)_t223;
    I64 _t224; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t224 = *_hp; free(_hp); }
    (void)_t224;
    I64 _t225 = I64_sub(_t222, _t223);
    (void)_t225;
    ;
    ;
    Bool _t226 = I64_eq(_t224, _t225);
    (void)_t226;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t226; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t227; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t227 = *_hp; free(_hp); }
    (void)_t227;
    I64 _t228 = 1;
    (void)_t228;
    Bool _t229 = I64_eq(_t227, _t228);
    (void)_t229;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t229; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t230 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t230;
    Bool _t231 = Bool_not(_t230);
    (void)_t231;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t231; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t232; { Bool *_hp = (Bool *)Bool_gt(a, b); _t232 = *_hp; free(_hp); }
    (void)_t232;
    Bool _t233 = Bool_not(_t232);
    (void)_t233;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t233; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t234; { Bool *_hp = (Bool *)Bool_lt(a, b); _t234 = *_hp; free(_hp); }
    (void)_t234;
    Bool _t235 = Bool_not(_t234);
    (void)_t235;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t235; return _r; }
}

void println(Array * parts) {
    (void)parts;
    {
        U64 *_fi236 = malloc(sizeof(U64));
        *_fi236 = 0;
        (void)_fi236;
        while (1) {
            U64 _t238; { U64 *_hp = (U64 *)Array_len(parts); _t238 = *_hp; free(_hp); }
            (void)_t238;
            Bool _wcond237; { Bool *_hp = (Bool *)U64_lt(_fi236, &(U64){_t238}); _wcond237 = *_hp; free(_hp); }
            (void)_wcond237;
            ;
            if (_wcond237) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi236);
            (void)s;
            U64 _t239 = 1;
            (void)_t239;
            U64 _t240 = U64_add(DEREF(_fi236), _t239);
            (void)_t240;
            ;
            *_fi236 = _t240;
            ;
            print_single(s);
        }
        U64_delete(_fi236, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    (void)parts;
    {
        U64 *_fi241 = malloc(sizeof(U64));
        *_fi241 = 0;
        (void)_fi241;
        while (1) {
            U64 _t243; { U64 *_hp = (U64 *)Array_len(parts); _t243 = *_hp; free(_hp); }
            (void)_t243;
            Bool _wcond242; { Bool *_hp = (Bool *)U64_lt(_fi241, &(U64){_t243}); _wcond242 = *_hp; free(_hp); }
            (void)_wcond242;
            ;
            if (_wcond242) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi241);
            (void)s;
            U64 _t244 = 1;
            (void)_t244;
            U64 _t245 = U64_add(DEREF(_fi241), _t244);
            (void)_t245;
            ;
            *_fi241 = _t245;
            ;
            print_single(s);
        }
        U64_delete(_fi241, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    (void)parts;
    U64 total = 0;
    (void)total;
    {
        U64 *_fi246 = malloc(sizeof(U64));
        *_fi246 = 0;
        (void)_fi246;
        while (1) {
            U64 _t248; { U64 *_hp = (U64 *)Array_len(parts); _t248 = *_hp; free(_hp); }
            (void)_t248;
            Bool _wcond247; { Bool *_hp = (Bool *)U64_lt(_fi246, &(U64){_t248}); _wcond247 = *_hp; free(_hp); }
            (void)_wcond247;
            ;
            if (_wcond247) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi246);
            (void)s;
            U64 _t249 = 1;
            (void)_t249;
            U64 _t250 = U64_add(DEREF(_fi246), _t249);
            (void)_t250;
            ;
            *_fi246 = _t250;
            ;
            U64 _t251; { U64 *_hp = (U64 *)Str_len(s); _t251 = *_hp; free(_hp); }
            (void)_t251;
            U64 _t252 = U64_add(total, _t251);
            (void)_t252;
            ;
            total = _t252;
            ;
        }
        U64_delete(_fi246, &(Bool){1});
    }
    U8 *buf = malloc(total);
    (void)buf;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    {
        U64 *_fi253 = malloc(sizeof(U64));
        *_fi253 = 0;
        (void)_fi253;
        while (1) {
            U64 _t255; { U64 *_hp = (U64 *)Array_len(parts); _t255 = *_hp; free(_hp); }
            (void)_t255;
            Bool _wcond254; { Bool *_hp = (Bool *)U64_lt(_fi253, &(U64){_t255}); _wcond254 = *_hp; free(_hp); }
            (void)_wcond254;
            ;
            if (_wcond254) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi253);
            (void)s;
            U64 _t256 = 1;
            (void)_t256;
            U64 _t257 = U64_add(DEREF(_fi253), _t256);
            (void)_t257;
            ;
            *_fi253 = _t257;
            ;
            void *_t258 = ptr_add(buf, DEREF(offset));
            (void)_t258;
            U64 _t259; { U64 *_hp = (U64 *)Str_len(s); _t259 = *_hp; free(_hp); }
            (void)_t259;
            memcpy(_t258, s->c_str, _t259);
            ;
            U64 _t260; { U64 *_hp = (U64 *)Str_len(s); _t260 = *_hp; free(_hp); }
            (void)_t260;
            U64 _t261 = U64_add(DEREF(offset), _t260);
            (void)_t261;
            ;
            *offset = _t261;
            ;
        }
        U64_delete(_fi253, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t262 = U64_clone(&(U64){total});
    (void)_t262;
    U64 _t263 = U64_clone(&(U64){total});
    (void)_t263;
    ;
    Str *_t264 = malloc(sizeof(Str));
    _t264->c_str = buf;
    _t264->count = _t262;
    _t264->cap = _t263;
    (void)_t264;
    ;
    ;
    return _t264;
}

I64 * wait_cmd(I64 * pid) {
    (void)pid;
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        (void)status;
        I64 _t265 = 0;
        (void)_t265;
        I64 _t266 = 1;
        (void)_t266;
        I64 _t267 = I64_sub(_t265, _t266);
        (void)_t267;
        ;
        ;
        Bool _t268; { Bool *_hp = (Bool *)I64_neq(&(I64){status}, &(I64){_t267}); _t268 = *_hp; free(_hp); }
        (void)_t268;
        ;
        if (_t268) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t269 = 50;
        (void)_t269;
        sleep_ms(_t269);
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
        U64 _t275; { U64 *_hp = (U64 *)Array_len(args); _t275 = *_hp; free(_hp); }
        (void)_t275;
        Bool _wcond270; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t275}); _wcond270 = *_hp; free(_hp); }
        (void)_wcond270;
        ;
        if (_wcond270) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        (void)arg;
        U64 _t276 = 0;
        (void)_t276;
        Bool _t277; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t276}); _t277 = *_hp; free(_hp); }
        (void)_t277;
        ;
        if (_t277) {
            Str *_t271 = Str_lit(" '", 2ULL);
            (void)_t271;
            Str *_t272 = Str_concat(cmd, _t271);
            (void)_t272;
            Str_delete(_t271, &(Bool){1});
            Str *_t273 = Str_concat(_t272, arg);
            (void)_t273;
            Str_delete(_t272, &(Bool){1});
            Str *_t274 = Str_lit("'", 1ULL);
            (void)_t274;
            cmd = Str_concat(_t273, _t274);
            Str_delete(_t273, &(Bool){1});
            Str_delete(_t274, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t278 = 1;
        (void)_t278;
        U64 _t279 = U64_add(DEREF(i), _t278);
        (void)_t279;
        ;
        *i = _t279;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    (void)tmpf;
    Str *_t280 = Str_lit(" > ", 3ULL);
    (void)_t280;
    Str *_t281 = Str_concat(cmd, _t280);
    (void)_t281;
    Str_delete(_t280, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t282 = Str_concat(_t281, tmpf);
    (void)_t282;
    Str_delete(_t281, &(Bool){1});
    Str *_t283 = Str_lit(" 2>&1", 5ULL);
    (void)_t283;
    Str *_t284 = Str_concat(_t282, _t283);
    (void)_t284;
    Str_delete(_t282, &(Bool){1});
    Str_delete(_t283, &(Bool){1});
    I64 pid; { I64 *_hp = (I64 *)spawn_cmd(_t284); pid = *_hp; free(_hp); }
    (void)pid;
    Str_delete(_t284, &(Bool){1});
    I64 ec; { I64 *_hp = (I64 *)wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    (void)ec;
    ;
    Str *content = readfile(tmpf);
    (void)content;
    Str_delete(tmpf, &(Bool){1});
    U64 _t285; { U64 *_hp = (U64 *)Str_size(); _t285 = *_hp; free(_hp); }
    (void)_t285;
    memcpy(output, content, _t285);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t286 = Str_lit("Str", 3ULL);
    (void)_t286;
    U64 _t287; { U64 *_hp = (U64 *)Str_size(); _t287 = *_hp; free(_hp); }
    (void)_t287;
    U64 _t288 = 3;
    (void)_t288;
    Array *_va0 = Array_new(_t286, &(U64){_t287}, &(U64){_t288});
    (void)_va0;
    Str_delete(_t286, &(Bool){1});
    ;
    ;
    U64 _t289 = 0;
    (void)_t289;
    Str *_t290 = Str_clone(loc_str);
    (void)_t290;
    Array_set(_va0, &(U64){_t289}, _t290);
    ;
    U64 _t291 = 1;
    (void)_t291;
    Str *_t292 = Str_lit(": panic: ", 9ULL);
    (void)_t292;
    Array_set(_va0, &(U64){_t291}, _t292);
    ;
    U64 _t293 = 2;
    (void)_t293;
    Str *_t294 = format(parts);
    (void)_t294;
    Array_set(_va0, &(U64){_t293}, _t294);
    ;
    println(_va0);
    I64 _t295 = 1;
    (void)_t295;
    exit(_t295);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t296 = Str_lit("Str", 3ULL);
    (void)_t296;
    U64 _t297; { U64 *_hp = (U64 *)Str_size(); _t297 = *_hp; free(_hp); }
    (void)_t297;
    U64 _t298 = 2;
    (void)_t298;
    Array *_va1 = Array_new(_t296, &(U64){_t297}, &(U64){_t298});
    (void)_va1;
    Str_delete(_t296, &(Bool){1});
    ;
    ;
    U64 _t299 = 0;
    (void)_t299;
    Str *_t300 = Str_lit("TODO: ", 6ULL);
    (void)_t300;
    Array_set(_va1, &(U64){_t299}, _t300);
    ;
    U64 _t301 = 1;
    (void)_t301;
    Str *_t302 = format(parts);
    (void)_t302;
    Array_set(_va1, &(U64){_t301}, _t302);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    (void)loc_str;
    Str *_t303 = Str_lit("Str", 3ULL);
    (void)_t303;
    U64 _t304; { U64 *_hp = (U64 *)Str_size(); _t304 = *_hp; free(_hp); }
    (void)_t304;
    U64 _t305 = 1;
    (void)_t305;
    Array *_va2 = Array_new(_t303, &(U64){_t304}, &(U64){_t305});
    (void)_va2;
    Str_delete(_t303, &(Bool){1});
    ;
    ;
    U64 _t306 = 0;
    (void)_t306;
    Str *_t307 = Str_lit("unreachable", 11ULL);
    (void)_t307;
    Array_set(_va2, &(U64){_t306}, _t307);
    ;
    panic(loc_str, _va2);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Bool _t315 = Bool_not(DEREF(cond));
    (void)_t315;
    if (_t315) {
        Str *_t308 = Str_lit("Str", 3ULL);
        (void)_t308;
        U64 _t309; { U64 *_hp = (U64 *)Str_size(); _t309 = *_hp; free(_hp); }
        (void)_t309;
        U64 _t310 = 2;
        (void)_t310;
        Array *_va3 = Array_new(_t308, &(U64){_t309}, &(U64){_t310});
        (void)_va3;
        Str_delete(_t308, &(Bool){1});
        ;
        ;
        U64 _t311 = 0;
        (void)_t311;
        Str *_t312 = Str_lit("assert failed: ", 15ULL);
        (void)_t312;
        Array_set(_va3, &(U64){_t311}, _t312);
        ;
        U64 _t313 = 1;
        (void)_t313;
        Str *_t314 = format(parts);
        (void)_t314;
        Array_set(_va3, &(U64){_t313}, _t314);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t316 = 1;
    (void)_t316;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t316; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Str *_t317 = Str_lit("Str", 3ULL);
    (void)_t317;
    U64 _t318; { U64 *_hp = (U64 *)Str_size(); _t318 = *_hp; free(_hp); }
    (void)_t318;
    U64 _t319 = 0;
    (void)_t319;
    Array *_va4 = Array_new(_t317, &(U64){_t318}, &(U64){_t319});
    (void)_va4;
    Str_delete(_t317, &(Bool){1});
    ;
    ;
    Bool _t320; { Bool *_hp = (Bool *)assertm(loc_str, cond, _va4); _t320 = *_hp; free(_hp); }
    (void)_t320;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t320; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Array *_t321 = Array_clone(parts);
    (void)_t321;
    Array_delete(parts, &(Bool){1});
    Bool _t322; { Bool *_hp = (Bool *)assertm(loc_str, cond, _t321); _t322 = *_hp; free(_hp); }
    (void)_t322;
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t336; { Bool *_hp = (Bool *)I64_neq(a, b); _t336 = *_hp; free(_hp); }
    (void)_t336;
    if (_t336) {
        Str *_t323 = Str_lit("Str", 3ULL);
        (void)_t323;
        U64 _t324; { U64 *_hp = (U64 *)Str_size(); _t324 = *_hp; free(_hp); }
        (void)_t324;
        U64 _t325 = 5;
        (void)_t325;
        Array *_va5 = Array_new(_t323, &(U64){_t324}, &(U64){_t325});
        (void)_va5;
        Str_delete(_t323, &(Bool){1});
        ;
        ;
        U64 _t326 = 0;
        (void)_t326;
        Str *_t327 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t327;
        Array_set(_va5, &(U64){_t326}, _t327);
        ;
        U64 _t328 = 1;
        (void)_t328;
        Str *_t329 = I64_to_str(a);
        (void)_t329;
        Array_set(_va5, &(U64){_t328}, _t329);
        ;
        U64 _t330 = 2;
        (void)_t330;
        Str *_t331 = Str_lit("', found '", 10ULL);
        (void)_t331;
        Array_set(_va5, &(U64){_t330}, _t331);
        ;
        U64 _t332 = 3;
        (void)_t332;
        Str *_t333 = I64_to_str(b);
        (void)_t333;
        Array_set(_va5, &(U64){_t332}, _t333);
        ;
        U64 _t334 = 4;
        (void)_t334;
        Str *_t335 = Str_lit("'", 1ULL);
        (void)_t335;
        Array_set(_va5, &(U64){_t334}, _t335);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t350; { Bool *_hp = (Bool *)Str_eq(a, b); _t350 = *_hp; free(_hp); }
    (void)_t350;
    Bool _t351 = Bool_not(_t350);
    (void)_t351;
    ;
    if (_t351) {
        Str *_t337 = Str_lit("Str", 3ULL);
        (void)_t337;
        U64 _t338; { U64 *_hp = (U64 *)Str_size(); _t338 = *_hp; free(_hp); }
        (void)_t338;
        U64 _t339 = 5;
        (void)_t339;
        Array *_va6 = Array_new(_t337, &(U64){_t338}, &(U64){_t339});
        (void)_va6;
        Str_delete(_t337, &(Bool){1});
        ;
        ;
        U64 _t340 = 0;
        (void)_t340;
        Str *_t341 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t341;
        Array_set(_va6, &(U64){_t340}, _t341);
        ;
        U64 _t342 = 1;
        (void)_t342;
        Str *_t343 = Str_clone(a);
        (void)_t343;
        Array_set(_va6, &(U64){_t342}, _t343);
        ;
        U64 _t344 = 2;
        (void)_t344;
        Str *_t345 = Str_lit("', found '", 10ULL);
        (void)_t345;
        Array_set(_va6, &(U64){_t344}, _t345);
        ;
        U64 _t346 = 3;
        (void)_t346;
        Str *_t347 = Str_clone(b);
        (void)_t347;
        Array_set(_va6, &(U64){_t346}, _t347);
        ;
        U64 _t348 = 4;
        (void)_t348;
        Str *_t349 = Str_lit("'", 1ULL);
        (void)_t349;
        Array_set(_va6, &(U64){_t348}, _t349);
        ;
        panic(loc_str, _va6);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    void *_t352 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t352;
    U64 _t353 = U64_clone(cap);
    (void)_t353;
    U64 _t354 = U64_clone(elem_size);
    (void)_t354;
    Array *_t355 = malloc(sizeof(Array));
    _t355->data = _t352;
    _t355->cap = _t353;
    _t355->elem_size = _t354;
    { Str *_ca = Str_clone(elem_type); _t355->elem_type = *_ca; free(_ca); }
    (void)_t355;
    ;
    ;
    return _t355;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t370; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t370 = *_hp; free(_hp); }
    (void)_t370;
    if (_t370) {
        Str *_t356 = Str_lit("Str", 3ULL);
        (void)_t356;
        U64 _t357; { U64 *_hp = (U64 *)Str_size(); _t357 = *_hp; free(_hp); }
        (void)_t357;
        U64 _t358 = 5;
        (void)_t358;
        Array *_va7 = Array_new(_t356, &(U64){_t357}, &(U64){_t358});
        (void)_va7;
        Str_delete(_t356, &(Bool){1});
        ;
        ;
        U64 _t359 = 0;
        (void)_t359;
        Str *_t360 = Str_lit("Array.get: index ", 17ULL);
        (void)_t360;
        Array_set(_va7, &(U64){_t359}, _t360);
        ;
        U64 _t361 = 1;
        (void)_t361;
        Str *_t362 = U64_to_str(DEREF(i));
        (void)_t362;
        Array_set(_va7, &(U64){_t361}, _t362);
        ;
        U64 _t363 = 2;
        (void)_t363;
        Str *_t364 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t364;
        Array_set(_va7, &(U64){_t363}, _t364);
        ;
        U64 _t365 = 3;
        (void)_t365;
        Str *_t366 = U64_to_str(self->cap);
        (void)_t366;
        Array_set(_va7, &(U64){_t365}, _t366);
        ;
        U64 _t367 = 4;
        (void)_t367;
        Str *_t368 = Str_lit(")", 1ULL);
        (void)_t368;
        Array_set(_va7, &(U64){_t367}, _t368);
        ;
        Str *_t369 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:19:19", 62ULL);
        (void)_t369;
        panic(_t369, _va7);
        Str_delete(_t369, &(Bool){1});
    }
    ;
    U64 *_t371 = malloc(sizeof(U64)); *_t371 = U64_mul(DEREF(i), self->elem_size);
    (void)_t371;
    void *_t372 = ptr_add(self->data, DEREF(_t371));
    (void)_t372;
    U64_delete(_t371, &(Bool){1});
    return _t372;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t387; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t387 = *_hp; free(_hp); }
    (void)_t387;
    if (_t387) {
        Str *_t373 = Str_lit("Str", 3ULL);
        (void)_t373;
        U64 _t374; { U64 *_hp = (U64 *)Str_size(); _t374 = *_hp; free(_hp); }
        (void)_t374;
        U64 _t375 = 5;
        (void)_t375;
        Array *_va8 = Array_new(_t373, &(U64){_t374}, &(U64){_t375});
        (void)_va8;
        Str_delete(_t373, &(Bool){1});
        ;
        ;
        U64 _t376 = 0;
        (void)_t376;
        Str *_t377 = Str_lit("Array.set: index ", 17ULL);
        (void)_t377;
        Array_set(_va8, &(U64){_t376}, _t377);
        ;
        U64 _t378 = 1;
        (void)_t378;
        Str *_t379 = U64_to_str(DEREF(i));
        (void)_t379;
        Array_set(_va8, &(U64){_t378}, _t379);
        ;
        U64 _t380 = 2;
        (void)_t380;
        Str *_t381 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t381;
        Array_set(_va8, &(U64){_t380}, _t381);
        ;
        U64 _t382 = 3;
        (void)_t382;
        Str *_t383 = U64_to_str(self->cap);
        (void)_t383;
        Array_set(_va8, &(U64){_t382}, _t383);
        ;
        U64 _t384 = 4;
        (void)_t384;
        Str *_t385 = Str_lit(")", 1ULL);
        (void)_t385;
        Array_set(_va8, &(U64){_t384}, _t385);
        ;
        Str *_t386 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:27:19", 62ULL);
        (void)_t386;
        panic(_t386, _va8);
        Str_delete(_t386, &(Bool){1});
    }
    ;
    U64 *_t388 = malloc(sizeof(U64)); *_t388 = U64_mul(DEREF(i), self->elem_size);
    (void)_t388;
    void *_t389 = ptr_add(self->data, DEREF(_t388));
    (void)_t389;
    Bool _t390 = 0;
    (void)_t390;
    dyn_call_delete(&self->elem_type, _t389, &(Bool){_t390});
    U64_delete(_t388, &(Bool){1});
    ;
    U64 *_t391 = malloc(sizeof(U64)); *_t391 = U64_mul(DEREF(i), self->elem_size);
    (void)_t391;
    void *_t392 = ptr_add(self->data, DEREF(_t391));
    (void)_t392;
    memcpy(_t392, val, self->elem_size);
    U64_delete(_t391, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U64 _fi393 = 0;
        (void)_fi393;
        while (1) {
            U64 _t395 = 0;
            (void)_t395;
            Range *_t396 = Range_new(_t395, self->cap);
            (void)_t396;
            ;
            U64 _t397; { U64 *_hp = (U64 *)Range_len(_t396); _t397 = *_hp; free(_hp); }
            (void)_t397;
            Range_delete(_t396, &(Bool){1});
            Bool _wcond394; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi393}, &(U64){_t397}); _wcond394 = *_hp; free(_hp); }
            (void)_wcond394;
            ;
            if (_wcond394) {
            } else {
                ;
                break;
            }
            ;
            U64 _t398 = 0;
            (void)_t398;
            Range *_t399 = Range_new(_t398, self->cap);
            (void)_t399;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t399, _fi393); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t399, &(Bool){1});
            U64 _t400 = 1;
            (void)_t400;
            U64 _t401 = U64_add(_fi393, _t400);
            (void)_t401;
            ;
            _fi393 = _t401;
            ;
            U64 *_t402 = malloc(sizeof(U64)); *_t402 = U64_mul(i, self->elem_size);
            (void)_t402;
            ;
            void *_t403 = ptr_add(self->data, DEREF(_t402));
            (void)_t403;
            Bool _t404 = 0;
            (void)_t404;
            dyn_call_delete(&self->elem_type, _t403, &(Bool){_t404});
            U64_delete(_t402, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t405 = 0;
    (void)_t405;
    Str_delete(&self->elem_type, &(Bool){_t405});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t419 = U64_mul(self->cap, self->elem_size);
    (void)_t419;
    U8 *new_data = malloc(_t419);
    (void)new_data;
    ;
    {
        U64 _fi406 = 0;
        (void)_fi406;
        while (1) {
            U64 _t408 = 0;
            (void)_t408;
            Range *_t409 = Range_new(_t408, self->cap);
            (void)_t409;
            ;
            U64 _t410; { U64 *_hp = (U64 *)Range_len(_t409); _t410 = *_hp; free(_hp); }
            (void)_t410;
            Range_delete(_t409, &(Bool){1});
            Bool _wcond407; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi406}, &(U64){_t410}); _wcond407 = *_hp; free(_hp); }
            (void)_wcond407;
            ;
            if (_wcond407) {
            } else {
                ;
                break;
            }
            ;
            U64 _t411 = 0;
            (void)_t411;
            Range *_t412 = Range_new(_t411, self->cap);
            (void)_t412;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t412, _fi406); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t412, &(Bool){1});
            U64 _t413 = 1;
            (void)_t413;
            U64 _t414 = U64_add(_fi406, _t413);
            (void)_t414;
            ;
            _fi406 = _t414;
            ;
            U64 *_t415 = malloc(sizeof(U64)); *_t415 = U64_mul(i, self->elem_size);
            (void)_t415;
            void *_t416 = ptr_add(self->data, DEREF(_t415));
            (void)_t416;
            void *cloned = dyn_call_clone(&self->elem_type, _t416);
            (void)cloned;
            U64_delete(_t415, &(Bool){1});
            U64 *_t417 = malloc(sizeof(U64)); *_t417 = U64_mul(i, self->elem_size);
            (void)_t417;
            ;
            void *_t418 = ptr_add(new_data, DEREF(_t417));
            (void)_t418;
            memcpy(_t418, cloned, self->elem_size);
            U64_delete(_t417, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t420 = malloc(sizeof(Array));
    _t420->data = new_data;
    _t420->cap = self->cap;
    _t420->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t420->elem_type = *_ca; free(_ca); }
    (void)_t420;
    return _t420;
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
    Bool _t434; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t434 = *_hp; free(_hp); }
    (void)_t434;
    Bool _t435 = Bool_not(_t434);
    (void)_t435;
    ;
    if (_t435) {
        Bool _t432 = dyn_has_cmp(key_type);
        (void)_t432;
        Bool _t433 = Bool_not(_t432);
        (void)_t433;
        ;
        if (_t433) {
            Str *_t422 = Str_lit("Str", 3ULL);
            (void)_t422;
            U64 _t423; { U64 *_hp = (U64 *)Str_size(); _t423 = *_hp; free(_hp); }
            (void)_t423;
            U64 _t424 = 3;
            (void)_t424;
            Array *_va9 = Array_new(_t422, &(U64){_t423}, &(U64){_t424});
            (void)_va9;
            Str_delete(_t422, &(Bool){1});
            ;
            ;
            U64 _t425 = 0;
            (void)_t425;
            Str *_t426 = Str_lit("Map.new: type ", 14ULL);
            (void)_t426;
            Array_set(_va9, &(U64){_t425}, _t426);
            ;
            U64 _t427 = 1;
            (void)_t427;
            Str *_t428 = Str_clone(key_type);
            (void)_t428;
            Array_set(_va9, &(U64){_t427}, _t428);
            ;
            U64 _t429 = 2;
            (void)_t429;
            Str *_t430 = Str_lit(" must implement cmp", 19ULL);
            (void)_t430;
            Array_set(_va9, &(U64){_t429}, _t430);
            ;
            Str *_t431 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
            (void)_t431;
            panic(_t431, _va9);
            Str_delete(_t431, &(Bool){1});
        }
        ;
    }
    ;
    void *_t436 = malloc(DEREF(key_size));
    (void)_t436;
    void *_t437 = malloc(DEREF(val_size));
    (void)_t437;
    U64 _t438 = 0;
    (void)_t438;
    I64 _t439 = 1;
    (void)_t439;
    U64 _t440 = U64_clone(key_size);
    (void)_t440;
    U64 _t441 = U64_clone(val_size);
    (void)_t441;
    Map *_t442 = malloc(sizeof(Map));
    _t442->key_data = _t436;
    _t442->val_data = _t437;
    _t442->count = _t438;
    _t442->cap = _t439;
    _t442->key_size = _t440;
    { Str *_ca = Str_clone(key_type); _t442->key_type = *_ca; free(_ca); }
    _t442->val_size = _t441;
    { Str *_ca = Str_clone(val_type); _t442->val_type = *_ca; free(_ca); }
    (void)_t442;
    ;
    ;
    ;
    ;
    return _t442;
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
        Bool _wcond443; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond443 = *_hp; free(_hp); }
        (void)_wcond443;
        if (_wcond443) {
        } else {
            ;
            break;
        }
        ;
        U64 _t450 = U64_sub(hi, lo);
        (void)_t450;
        U64 _t451 = 2;
        (void)_t451;
        U64 _t452 = U64_div(_t450, _t451);
        (void)_t452;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t452);
        (void)mid;
        ;
        U64 *_t453 = malloc(sizeof(U64)); *_t453 = U64_mul(DEREF(mid), self->key_size);
        (void)_t453;
        void *_t454 = ptr_add(self->key_data, DEREF(_t453));
        (void)_t454;
        I64 *c = dyn_call_cmp(&self->key_type, _t454, key);
        (void)c;
        U64_delete(_t453, &(Bool){1});
        I64 _t455 = 0;
        (void)_t455;
        Bool _t456; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t455}); _t456 = *_hp; free(_hp); }
        (void)_t456;
        ;
        if (_t456) {
            U64 _t444 = 1;
            (void)_t444;
            U64 _t445 = U64_add(DEREF(mid), _t444);
            (void)_t445;
            ;
            lo = _t445;
            ;
        } else {
            I64 _t448 = 0;
            (void)_t448;
            Bool _t449; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t448}); _t449 = *_hp; free(_hp); }
            (void)_t449;
            ;
            if (_t449) {
                U64 _t446 = U64_clone(mid);
                (void)_t446;
                hi = _t446;
                ;
            } else {
                Bool _t447 = 1;
                (void)_t447;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t447; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t457 = 0;
    (void)_t457;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t457; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond458; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond458 = *_hp; free(_hp); }
        (void)_wcond458;
        if (_wcond458) {
        } else {
            ;
            break;
        }
        ;
        U64 _t466 = U64_sub(hi, lo);
        (void)_t466;
        U64 _t467 = 2;
        (void)_t467;
        U64 _t468 = U64_div(_t466, _t467);
        (void)_t468;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t468);
        (void)mid;
        ;
        U64 *_t469 = malloc(sizeof(U64)); *_t469 = U64_mul(DEREF(mid), self->key_size);
        (void)_t469;
        void *_t470 = ptr_add(self->key_data, DEREF(_t469));
        (void)_t470;
        I64 *c = dyn_call_cmp(&self->key_type, _t470, key);
        (void)c;
        U64_delete(_t469, &(Bool){1});
        I64 _t471 = 0;
        (void)_t471;
        Bool _t472; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t471}); _t472 = *_hp; free(_hp); }
        (void)_t472;
        ;
        if (_t472) {
            U64 _t459 = 1;
            (void)_t459;
            U64 _t460 = U64_add(DEREF(mid), _t459);
            (void)_t460;
            ;
            lo = _t460;
            ;
        } else {
            I64 _t464 = 0;
            (void)_t464;
            Bool _t465; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t464}); _t465 = *_hp; free(_hp); }
            (void)_t465;
            ;
            if (_t465) {
                U64 _t461 = U64_clone(mid);
                (void)_t461;
                hi = _t461;
                ;
            } else {
                U64 *_t462 = malloc(sizeof(U64)); *_t462 = U64_mul(DEREF(mid), self->val_size);
                (void)_t462;
                void *_t463 = ptr_add(self->val_data, DEREF(_t462));
                (void)_t463;
                U64_delete(_t462, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t463;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t473 = Str_lit("Str", 3ULL);
    (void)_t473;
    U64 _t474; { U64 *_hp = (U64 *)Str_size(); _t474 = *_hp; free(_hp); }
    (void)_t474;
    U64 _t475 = 1;
    (void)_t475;
    Array *_va10 = Array_new(_t473, &(U64){_t474}, &(U64){_t475});
    (void)_va10;
    Str_delete(_t473, &(Bool){1});
    ;
    ;
    U64 _t476 = 0;
    (void)_t476;
    Str *_t477 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t477;
    Array_set(_va10, &(U64){_t476}, _t477);
    ;
    Str *_t478 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
    (void)_t478;
    panic(_t478, _va10);
    Str_delete(_t478, &(Bool){1});
    U64 *_t479 = malloc(sizeof(U64));
    *_t479 = 0;
    (void)_t479;
    void *_t480 = ptr_add(self->val_data, DEREF(_t479));
    (void)_t480;
    U64_delete(_t479, &(Bool){1});
    return _t480;
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
        Bool _wcond481; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond481 = *_hp; free(_hp); }
        (void)_wcond481;
        if (_wcond481) {
        } else {
            ;
            break;
        }
        ;
        U64 _t490 = U64_sub(hi, lo);
        (void)_t490;
        U64 _t491 = 2;
        (void)_t491;
        U64 _t492 = U64_div(_t490, _t491);
        (void)_t492;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t492);
        (void)mid;
        ;
        U64 *_t493 = malloc(sizeof(U64)); *_t493 = U64_mul(DEREF(mid), self->key_size);
        (void)_t493;
        void *_t494 = ptr_add(self->key_data, DEREF(_t493));
        (void)_t494;
        I64 *c = dyn_call_cmp(&self->key_type, _t494, key);
        (void)c;
        U64_delete(_t493, &(Bool){1});
        I64 _t495 = 0;
        (void)_t495;
        Bool _t496; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t495}); _t496 = *_hp; free(_hp); }
        (void)_t496;
        ;
        if (_t496) {
            U64 _t482 = 1;
            (void)_t482;
            U64 _t483 = U64_add(DEREF(mid), _t482);
            (void)_t483;
            ;
            lo = _t483;
            ;
        } else {
            I64 _t488 = 0;
            (void)_t488;
            Bool _t489; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t488}); _t489 = *_hp; free(_hp); }
            (void)_t489;
            ;
            if (_t489) {
                U64 _t484 = U64_clone(mid);
                (void)_t484;
                hi = _t484;
                ;
            } else {
                Bool _t485 = 1;
                (void)_t485;
                found = _t485;
                ;
                U64 _t486 = U64_clone(mid);
                (void)_t486;
                lo = _t486;
                ;
                U64 _t487 = U64_clone(mid);
                (void)_t487;
                hi = _t487;
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
        Bool _t501; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t501 = *_hp; free(_hp); }
        (void)_t501;
        Bool _t502 = Bool_not(_t501);
        (void)_t502;
        ;
        if (_t502) {
            Bool _t497 = 0;
            (void)_t497;
            dyn_call_delete(&self->key_type, key, &(Bool){_t497});
            ;
        }
        ;
        free(key);
        Bool _t503; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t503 = *_hp; free(_hp); }
        (void)_t503;
        Bool _t504 = Bool_not(_t503);
        (void)_t504;
        ;
        if (_t504) {
            U64 *_t498 = malloc(sizeof(U64)); *_t498 = U64_mul(lo, self->val_size);
            (void)_t498;
            void *_t499 = ptr_add(self->val_data, DEREF(_t498));
            (void)_t499;
            Bool _t500 = 0;
            (void)_t500;
            dyn_call_delete(&self->val_type, _t499, &(Bool){_t500});
            U64_delete(_t498, &(Bool){1});
            ;
        }
        ;
        U64 *_t505 = malloc(sizeof(U64)); *_t505 = U64_mul(lo, self->val_size);
        (void)_t505;
        void *_t506 = ptr_add(self->val_data, DEREF(_t505));
        (void)_t506;
        memcpy(_t506, val, self->val_size);
        U64_delete(_t505, &(Bool){1});
        free(val);
    } else {
        Bool _t513 = U64_eq(self->count, self->cap);
        (void)_t513;
        if (_t513) {
            U64 _t507 = 2;
            (void)_t507;
            U64 new_cap = U64_mul(self->cap, _t507);
            (void)new_cap;
            ;
            U64 _t508 = U64_mul(new_cap, self->key_size);
            (void)_t508;
            void *_t509 = realloc(self->key_data, _t508);
            (void)_t509;
            ;
            self->key_data = _t509;
            U64 _t510 = U64_mul(new_cap, self->val_size);
            (void)_t510;
            void *_t511 = realloc(self->val_data, _t510);
            (void)_t511;
            ;
            self->val_data = _t511;
            U64 _t512 = U64_clone(&(U64){new_cap});
            (void)_t512;
            ;
            self->cap = _t512;
            ;
        }
        ;
        U64 _t514 = 1;
        (void)_t514;
        U64 _t515 = U64_add(lo, _t514);
        (void)_t515;
        ;
        U64 *_t516 = malloc(sizeof(U64)); *_t516 = U64_mul(_t515, self->key_size);
        (void)_t516;
        ;
        U64 *_t517 = malloc(sizeof(U64)); *_t517 = U64_mul(lo, self->key_size);
        (void)_t517;
        U64 _t518 = U64_sub(self->count, lo);
        (void)_t518;
        void *_t519 = ptr_add(self->key_data, DEREF(_t516));
        (void)_t519;
        void *_t520 = ptr_add(self->key_data, DEREF(_t517));
        (void)_t520;
        U64 _t521 = U64_mul(_t518, self->key_size);
        (void)_t521;
        ;
        memmove(_t519, _t520, _t521);
        U64_delete(_t516, &(Bool){1});
        U64_delete(_t517, &(Bool){1});
        ;
        U64 _t522 = 1;
        (void)_t522;
        U64 _t523 = U64_add(lo, _t522);
        (void)_t523;
        ;
        U64 *_t524 = malloc(sizeof(U64)); *_t524 = U64_mul(_t523, self->val_size);
        (void)_t524;
        ;
        U64 *_t525 = malloc(sizeof(U64)); *_t525 = U64_mul(lo, self->val_size);
        (void)_t525;
        U64 _t526 = U64_sub(self->count, lo);
        (void)_t526;
        void *_t527 = ptr_add(self->val_data, DEREF(_t524));
        (void)_t527;
        void *_t528 = ptr_add(self->val_data, DEREF(_t525));
        (void)_t528;
        U64 _t529 = U64_mul(_t526, self->val_size);
        (void)_t529;
        ;
        memmove(_t527, _t528, _t529);
        U64_delete(_t524, &(Bool){1});
        U64_delete(_t525, &(Bool){1});
        ;
        U64 *_t530 = malloc(sizeof(U64)); *_t530 = U64_mul(lo, self->key_size);
        (void)_t530;
        void *_t531 = ptr_add(self->key_data, DEREF(_t530));
        (void)_t531;
        memcpy(_t531, key, self->key_size);
        U64_delete(_t530, &(Bool){1});
        U64 *_t532 = malloc(sizeof(U64)); *_t532 = U64_mul(lo, self->val_size);
        (void)_t532;
        void *_t533 = ptr_add(self->val_data, DEREF(_t532));
        (void)_t533;
        memcpy(_t533, val, self->val_size);
        U64_delete(_t532, &(Bool){1});
        free(key);
        free(val);
        U64 _t534 = 1;
        (void)_t534;
        U64 _t535 = U64_add(self->count, _t534);
        (void)_t535;
        ;
        self->count = _t535;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t562; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t562 = *_hp; free(_hp); }
    (void)_t562;
    Bool _t563 = Bool_not(_t562);
    (void)_t563;
    ;
    if (_t563) {
        {
            U64 _fi536 = 0;
            (void)_fi536;
            while (1) {
                U64 _t538 = 0;
                (void)_t538;
                Range *_t539 = Range_new(_t538, self->count);
                (void)_t539;
                ;
                U64 _t540; { U64 *_hp = (U64 *)Range_len(_t539); _t540 = *_hp; free(_hp); }
                (void)_t540;
                Range_delete(_t539, &(Bool){1});
                Bool _wcond537; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi536}, &(U64){_t540}); _wcond537 = *_hp; free(_hp); }
                (void)_wcond537;
                ;
                if (_wcond537) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t541 = 0;
                (void)_t541;
                Range *_t542 = Range_new(_t541, self->count);
                (void)_t542;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t542, _fi536); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t542, &(Bool){1});
                U64 _t543 = 1;
                (void)_t543;
                U64 _t544 = U64_add(_fi536, _t543);
                (void)_t544;
                ;
                _fi536 = _t544;
                ;
                U64 *_t545 = malloc(sizeof(U64)); *_t545 = U64_mul(i, self->key_size);
                (void)_t545;
                ;
                void *_t546 = ptr_add(self->key_data, DEREF(_t545));
                (void)_t546;
                Bool _t547 = 0;
                (void)_t547;
                dyn_call_delete(&self->key_type, _t546, &(Bool){_t547});
                U64_delete(_t545, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t564; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t564 = *_hp; free(_hp); }
    (void)_t564;
    Bool _t565 = Bool_not(_t564);
    (void)_t565;
    ;
    if (_t565) {
        {
            U64 _fi548 = 0;
            (void)_fi548;
            while (1) {
                U64 _t550 = 0;
                (void)_t550;
                Range *_t551 = Range_new(_t550, self->count);
                (void)_t551;
                ;
                U64 _t552; { U64 *_hp = (U64 *)Range_len(_t551); _t552 = *_hp; free(_hp); }
                (void)_t552;
                Range_delete(_t551, &(Bool){1});
                Bool _wcond549; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi548}, &(U64){_t552}); _wcond549 = *_hp; free(_hp); }
                (void)_wcond549;
                ;
                if (_wcond549) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t553 = 0;
                (void)_t553;
                Range *_t554 = Range_new(_t553, self->count);
                (void)_t554;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t554, _fi548); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t554, &(Bool){1});
                U64 _t555 = 1;
                (void)_t555;
                U64 _t556 = U64_add(_fi548, _t555);
                (void)_t556;
                ;
                _fi548 = _t556;
                ;
                U64 *_t557 = malloc(sizeof(U64)); *_t557 = U64_mul(i, self->val_size);
                (void)_t557;
                ;
                void *_t558 = ptr_add(self->val_data, DEREF(_t557));
                (void)_t558;
                Bool _t559 = 0;
                (void)_t559;
                dyn_call_delete(&self->val_type, _t558, &(Bool){_t559});
                U64_delete(_t557, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t566; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t566 = *_hp; free(_hp); }
    (void)_t566;
    Bool _t567 = Bool_not(_t566);
    (void)_t567;
    ;
    if (_t567) {
        Bool _t560 = 0;
        (void)_t560;
        Str_delete(&self->key_type, &(Bool){_t560});
        ;
    }
    ;
    Bool _t568; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t568 = *_hp; free(_hp); }
    (void)_t568;
    Bool _t569 = Bool_not(_t568);
    (void)_t569;
    ;
    if (_t569) {
        Bool _t561 = 0;
        (void)_t561;
        Str_delete(&self->val_type, &(Bool){_t561});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t587 = U64_mul(self->cap, self->key_size);
    (void)_t587;
    U8 *new_keys = malloc(_t587);
    (void)new_keys;
    ;
    U64 _t588 = U64_mul(self->cap, self->val_size);
    (void)_t588;
    U8 *new_vals = malloc(_t588);
    (void)new_vals;
    ;
    {
        U64 _fi570 = 0;
        (void)_fi570;
        while (1) {
            U64 _t572 = 0;
            (void)_t572;
            Range *_t573 = Range_new(_t572, self->count);
            (void)_t573;
            ;
            U64 _t574; { U64 *_hp = (U64 *)Range_len(_t573); _t574 = *_hp; free(_hp); }
            (void)_t574;
            Range_delete(_t573, &(Bool){1});
            Bool _wcond571; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi570}, &(U64){_t574}); _wcond571 = *_hp; free(_hp); }
            (void)_wcond571;
            ;
            if (_wcond571) {
            } else {
                ;
                break;
            }
            ;
            U64 _t575 = 0;
            (void)_t575;
            Range *_t576 = Range_new(_t575, self->count);
            (void)_t576;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t576, _fi570); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t576, &(Bool){1});
            U64 _t577 = 1;
            (void)_t577;
            U64 _t578 = U64_add(_fi570, _t577);
            (void)_t578;
            ;
            _fi570 = _t578;
            ;
            U64 *_t579 = malloc(sizeof(U64)); *_t579 = U64_mul(i, self->key_size);
            (void)_t579;
            void *_t580 = ptr_add(self->key_data, DEREF(_t579));
            (void)_t580;
            void *ck = dyn_call_clone(&self->key_type, _t580);
            (void)ck;
            U64_delete(_t579, &(Bool){1});
            U64 *_t581 = malloc(sizeof(U64)); *_t581 = U64_mul(i, self->key_size);
            (void)_t581;
            void *_t582 = ptr_add(new_keys, DEREF(_t581));
            (void)_t582;
            memcpy(_t582, ck, self->key_size);
            U64_delete(_t581, &(Bool){1});
            free(ck);
            U64 *_t583 = malloc(sizeof(U64)); *_t583 = U64_mul(i, self->val_size);
            (void)_t583;
            void *_t584 = ptr_add(self->val_data, DEREF(_t583));
            (void)_t584;
            void *cv = dyn_call_clone(&self->val_type, _t584);
            (void)cv;
            U64_delete(_t583, &(Bool){1});
            U64 *_t585 = malloc(sizeof(U64)); *_t585 = U64_mul(i, self->val_size);
            (void)_t585;
            ;
            void *_t586 = ptr_add(new_vals, DEREF(_t585));
            (void)_t586;
            memcpy(_t586, cv, self->val_size);
            U64_delete(_t585, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t589 = malloc(sizeof(Map));
    _t589->key_data = new_keys;
    _t589->val_data = new_vals;
    _t589->count = self->count;
    _t589->cap = self->cap;
    _t589->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t589->key_type = *_ca; free(_ca); }
    _t589->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t589->val_type = *_ca; free(_ca); }
    (void)_t589;
    return _t589;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t603; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t603 = *_hp; free(_hp); }
    (void)_t603;
    Bool _t604 = Bool_not(_t603);
    (void)_t604;
    ;
    if (_t604) {
        Bool _t601 = dyn_has_cmp(elem_type);
        (void)_t601;
        Bool _t602 = Bool_not(_t601);
        (void)_t602;
        ;
        if (_t602) {
            Str *_t591 = Str_lit("Str", 3ULL);
            (void)_t591;
            U64 _t592; { U64 *_hp = (U64 *)Str_size(); _t592 = *_hp; free(_hp); }
            (void)_t592;
            U64 _t593 = 3;
            (void)_t593;
            Array *_va11 = Array_new(_t591, &(U64){_t592}, &(U64){_t593});
            (void)_va11;
            Str_delete(_t591, &(Bool){1});
            ;
            ;
            U64 _t594 = 0;
            (void)_t594;
            Str *_t595 = Str_lit("Set.new: type ", 14ULL);
            (void)_t595;
            Array_set(_va11, &(U64){_t594}, _t595);
            ;
            U64 _t596 = 1;
            (void)_t596;
            Str *_t597 = Str_clone(elem_type);
            (void)_t597;
            Array_set(_va11, &(U64){_t596}, _t597);
            ;
            U64 _t598 = 2;
            (void)_t598;
            Str *_t599 = Str_lit(" must implement cmp", 19ULL);
            (void)_t599;
            Array_set(_va11, &(U64){_t598}, _t599);
            ;
            Str *_t600 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
            (void)_t600;
            panic(_t600, _va11);
            Str_delete(_t600, &(Bool){1});
        }
        ;
    }
    ;
    void *_t605 = malloc(DEREF(elem_size));
    (void)_t605;
    U64 _t606 = 0;
    (void)_t606;
    I64 _t607 = 1;
    (void)_t607;
    U64 _t608 = U64_clone(elem_size);
    (void)_t608;
    Set *_t609 = malloc(sizeof(Set));
    _t609->data = _t605;
    _t609->count = _t606;
    _t609->cap = _t607;
    _t609->elem_size = _t608;
    { Str *_ca = Str_clone(elem_type); _t609->elem_type = *_ca; free(_ca); }
    (void)_t609;
    ;
    ;
    ;
    return _t609;
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
        Bool _wcond610; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond610 = *_hp; free(_hp); }
        (void)_wcond610;
        if (_wcond610) {
        } else {
            ;
            break;
        }
        ;
        U64 _t617 = U64_sub(hi, lo);
        (void)_t617;
        U64 _t618 = 2;
        (void)_t618;
        U64 _t619 = U64_div(_t617, _t618);
        (void)_t619;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t619);
        (void)mid;
        ;
        U64 *_t620 = malloc(sizeof(U64)); *_t620 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t620;
        void *_t621 = ptr_add(self->data, DEREF(_t620));
        (void)_t621;
        I64 *c = dyn_call_cmp(&self->elem_type, _t621, val);
        (void)c;
        U64_delete(_t620, &(Bool){1});
        I64 _t622 = 0;
        (void)_t622;
        Bool _t623; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t622}); _t623 = *_hp; free(_hp); }
        (void)_t623;
        ;
        if (_t623) {
            U64 _t611 = 1;
            (void)_t611;
            U64 _t612 = U64_add(DEREF(mid), _t611);
            (void)_t612;
            ;
            lo = _t612;
            ;
        } else {
            I64 _t615 = 0;
            (void)_t615;
            Bool _t616; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t615}); _t616 = *_hp; free(_hp); }
            (void)_t616;
            ;
            if (_t616) {
                U64 _t613 = U64_clone(mid);
                (void)_t613;
                hi = _t613;
                ;
            } else {
                Bool _t614 = 1;
                (void)_t614;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t614; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t624 = 0;
    (void)_t624;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t624; return _r; }
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
        Bool _wcond625; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond625 = *_hp; free(_hp); }
        (void)_wcond625;
        if (_wcond625) {
        } else {
            ;
            break;
        }
        ;
        U64 _t634 = U64_sub(hi, lo);
        (void)_t634;
        U64 _t635 = 2;
        (void)_t635;
        U64 _t636 = U64_div(_t634, _t635);
        (void)_t636;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t636);
        (void)mid;
        ;
        U64 *_t637 = malloc(sizeof(U64)); *_t637 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t637;
        void *_t638 = ptr_add(self->data, DEREF(_t637));
        (void)_t638;
        I64 *c = dyn_call_cmp(&self->elem_type, _t638, val);
        (void)c;
        U64_delete(_t637, &(Bool){1});
        I64 _t639 = 0;
        (void)_t639;
        Bool _t640; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t639}); _t640 = *_hp; free(_hp); }
        (void)_t640;
        ;
        if (_t640) {
            U64 _t626 = 1;
            (void)_t626;
            U64 _t627 = U64_add(DEREF(mid), _t626);
            (void)_t627;
            ;
            lo = _t627;
            ;
        } else {
            I64 _t632 = 0;
            (void)_t632;
            Bool _t633; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t632}); _t633 = *_hp; free(_hp); }
            (void)_t633;
            ;
            if (_t633) {
                U64 _t628 = U64_clone(mid);
                (void)_t628;
                hi = _t628;
                ;
            } else {
                Bool _t629 = 1;
                (void)_t629;
                found = _t629;
                ;
                U64 _t630 = U64_clone(mid);
                (void)_t630;
                lo = _t630;
                ;
                U64 _t631 = U64_clone(mid);
                (void)_t631;
                hi = _t631;
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
        Bool _t642; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t642 = *_hp; free(_hp); }
        (void)_t642;
        Bool _t643 = Bool_not(_t642);
        (void)_t643;
        ;
        if (_t643) {
            Bool _t641 = 0;
            (void)_t641;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t641});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t648 = U64_eq(self->count, self->cap);
        (void)_t648;
        if (_t648) {
            U64 _t644 = 2;
            (void)_t644;
            U64 new_cap = U64_mul(self->cap, _t644);
            (void)new_cap;
            ;
            U64 _t645 = U64_mul(new_cap, self->elem_size);
            (void)_t645;
            void *_t646 = realloc(self->data, _t645);
            (void)_t646;
            ;
            self->data = _t646;
            U64 _t647 = U64_clone(&(U64){new_cap});
            (void)_t647;
            ;
            self->cap = _t647;
            ;
        }
        ;
        U64 _t649 = 1;
        (void)_t649;
        U64 _t650 = U64_add(lo, _t649);
        (void)_t650;
        ;
        U64 *_t651 = malloc(sizeof(U64)); *_t651 = U64_mul(_t650, self->elem_size);
        (void)_t651;
        ;
        U64 *_t652 = malloc(sizeof(U64)); *_t652 = U64_mul(lo, self->elem_size);
        (void)_t652;
        U64 _t653 = U64_sub(self->count, lo);
        (void)_t653;
        void *_t654 = ptr_add(self->data, DEREF(_t651));
        (void)_t654;
        void *_t655 = ptr_add(self->data, DEREF(_t652));
        (void)_t655;
        U64 _t656 = U64_mul(_t653, self->elem_size);
        (void)_t656;
        ;
        memmove(_t654, _t655, _t656);
        U64_delete(_t651, &(Bool){1});
        U64_delete(_t652, &(Bool){1});
        ;
        U64 *_t657 = malloc(sizeof(U64)); *_t657 = U64_mul(lo, self->elem_size);
        (void)_t657;
        void *_t658 = ptr_add(self->data, DEREF(_t657));
        (void)_t658;
        memcpy(_t658, val, self->elem_size);
        U64_delete(_t657, &(Bool){1});
        free(val);
        U64 _t659 = 1;
        (void)_t659;
        U64 _t660 = U64_add(self->count, _t659);
        (void)_t660;
        ;
        self->count = _t660;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t674; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t674 = *_hp; free(_hp); }
    (void)_t674;
    Bool _t675 = Bool_not(_t674);
    (void)_t675;
    ;
    if (_t675) {
        {
            U64 _fi661 = 0;
            (void)_fi661;
            while (1) {
                U64 _t663 = 0;
                (void)_t663;
                Range *_t664 = Range_new(_t663, self->count);
                (void)_t664;
                ;
                U64 _t665; { U64 *_hp = (U64 *)Range_len(_t664); _t665 = *_hp; free(_hp); }
                (void)_t665;
                Range_delete(_t664, &(Bool){1});
                Bool _wcond662; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi661}, &(U64){_t665}); _wcond662 = *_hp; free(_hp); }
                (void)_wcond662;
                ;
                if (_wcond662) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t666 = 0;
                (void)_t666;
                Range *_t667 = Range_new(_t666, self->count);
                (void)_t667;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t667, _fi661); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t667, &(Bool){1});
                U64 _t668 = 1;
                (void)_t668;
                U64 _t669 = U64_add(_fi661, _t668);
                (void)_t669;
                ;
                _fi661 = _t669;
                ;
                U64 *_t670 = malloc(sizeof(U64)); *_t670 = U64_mul(i, self->elem_size);
                (void)_t670;
                ;
                void *_t671 = ptr_add(self->data, DEREF(_t670));
                (void)_t671;
                Bool _t672 = 0;
                (void)_t672;
                dyn_call_delete(&self->elem_type, _t671, &(Bool){_t672});
                U64_delete(_t670, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t676; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t676 = *_hp; free(_hp); }
    (void)_t676;
    Bool _t677 = Bool_not(_t676);
    (void)_t677;
    ;
    if (_t677) {
        Bool _t673 = 0;
        (void)_t673;
        Str_delete(&self->elem_type, &(Bool){_t673});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t691 = U64_mul(self->cap, self->elem_size);
    (void)_t691;
    U8 *new_data = malloc(_t691);
    (void)new_data;
    ;
    {
        U64 _fi678 = 0;
        (void)_fi678;
        while (1) {
            U64 _t680 = 0;
            (void)_t680;
            Range *_t681 = Range_new(_t680, self->count);
            (void)_t681;
            ;
            U64 _t682; { U64 *_hp = (U64 *)Range_len(_t681); _t682 = *_hp; free(_hp); }
            (void)_t682;
            Range_delete(_t681, &(Bool){1});
            Bool _wcond679; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi678}, &(U64){_t682}); _wcond679 = *_hp; free(_hp); }
            (void)_wcond679;
            ;
            if (_wcond679) {
            } else {
                ;
                break;
            }
            ;
            U64 _t683 = 0;
            (void)_t683;
            Range *_t684 = Range_new(_t683, self->count);
            (void)_t684;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t684, _fi678); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t684, &(Bool){1});
            U64 _t685 = 1;
            (void)_t685;
            U64 _t686 = U64_add(_fi678, _t685);
            (void)_t686;
            ;
            _fi678 = _t686;
            ;
            U64 *_t687 = malloc(sizeof(U64)); *_t687 = U64_mul(i, self->elem_size);
            (void)_t687;
            void *_t688 = ptr_add(self->data, DEREF(_t687));
            (void)_t688;
            void *cloned = dyn_call_clone(&self->elem_type, _t688);
            (void)cloned;
            U64_delete(_t687, &(Bool){1});
            U64 *_t689 = malloc(sizeof(U64)); *_t689 = U64_mul(i, self->elem_size);
            (void)_t689;
            ;
            void *_t690 = ptr_add(new_data, DEREF(_t689));
            (void)_t690;
            memcpy(_t690, cloned, self->elem_size);
            U64_delete(_t689, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t692 = malloc(sizeof(Set));
    _t692->data = new_data;
    _t692->count = self->count;
    _t692->cap = self->cap;
    _t692->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t692->elem_type = *_ca; free(_ca); }
    (void)_t692;
    return _t692;
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
    Bool _t700; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t700 = *_hp; free(_hp); }
    (void)_t700;
    if (_t700) {
        Str *_t694 = Str_lit("Str", 3ULL);
        (void)_t694;
        U64 _t695; { U64 *_hp = (U64 *)Str_size(); _t695 = *_hp; free(_hp); }
        (void)_t695;
        U64 _t696 = 1;
        (void)_t696;
        Array *_va12 = Array_new(_t694, &(U64){_t695}, &(U64){_t696});
        (void)_va12;
        Str_delete(_t694, &(Bool){1});
        ;
        ;
        U64 _t697 = 0;
        (void)_t697;
        Str *_t698 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t698;
        Array_set(_va12, &(U64){_t697}, _t698);
        ;
        Str *_t699 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t699;
        panic(_t699, _va12);
        Str_delete(_t699, &(Bool){1});
    }
    ;
    void *_t701 = ptr_add(self->c_str, DEREF(i));
    (void)_t701;
    return _t701;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t702 = ptr_add(self->c_str, DEREF(i));
    (void)_t702;
    return _t702;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t708; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t708 = *_hp; free(_hp); }
    (void)_t708;
    if (_t708) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond703; { Bool *_hp = (Bool *)U64_lt(i, &(U64){min_len}); _wcond703 = *_hp; free(_hp); }
        (void)_wcond703;
        if (_wcond703) {
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
        I64 _t704 = 0;
        (void)_t704;
        Bool _t705; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t704}); _t705 = *_hp; free(_hp); }
        (void)_t705;
        ;
        if (_t705) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t706 = 1;
        (void)_t706;
        U64 _t707 = U64_add(DEREF(i), _t706);
        (void)_t707;
        ;
        *i = _t707;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t709 = U64_cmp(a->count, b->count);
    (void)_t709;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t709; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t710 = 1;
    (void)_t710;
    U64 _t711 = U64_add(DEREF(new_len), _t710);
    (void)_t711;
    ;
    U8 *new_data = malloc(_t711);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t712 = ptr_add(new_data, a->count);
    (void)_t712;
    memcpy(_t712, b->c_str, b->count);
    void *_t713 = ptr_add(new_data, DEREF(new_len));
    (void)_t713;
    I64 _t714 = 0;
    (void)_t714;
    U64 _t715 = 1;
    (void)_t715;
    memcpy(_t713, &(I64){_t714}, _t715);
    ;
    ;
    U64 _t716 = U64_clone(new_len);
    (void)_t716;
    U64 _t717 = U64_clone(new_len);
    (void)_t717;
    U64_delete(new_len, &(Bool){1});
    Str *_t718 = malloc(sizeof(Str));
    _t718->c_str = new_data;
    _t718->count = _t716;
    _t718->cap = _t717;
    (void)_t718;
    ;
    ;
    return _t718;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t719 = 1;
    (void)_t719;
    U64 _t720 = U64_add(DEREF(n), _t719);
    (void)_t720;
    ;
    U8 *buf = malloc(_t720);
    (void)buf;
    ;
    I64 _t721 = 0;
    (void)_t721;
    U64 _t722 = 1;
    (void)_t722;
    memcpy(buf, &(I64){_t721}, _t722);
    ;
    ;
    I64 _t723 = 0;
    (void)_t723;
    U64 _t724 = U64_clone(n);
    (void)_t724;
    Str *_t725 = malloc(sizeof(Str));
    _t725->c_str = buf;
    _t725->count = _t723;
    _t725->cap = _t724;
    (void)_t725;
    ;
    ;
    return _t725;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t738; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t738 = *_hp; free(_hp); }
    (void)_t738;
    if (_t738) {
        Str *_t726 = Str_lit("Str", 3ULL);
        (void)_t726;
        U64 _t727; { U64 *_hp = (U64 *)Str_size(); _t727 = *_hp; free(_hp); }
        (void)_t727;
        U64 _t728 = 1;
        (void)_t728;
        Array *_va13 = Array_new(_t726, &(U64){_t727}, &(U64){_t728});
        (void)_va13;
        Str_delete(_t726, &(Bool){1});
        ;
        ;
        U64 _t729 = 0;
        (void)_t729;
        Str *_t730 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t730;
        Array_set(_va13, &(U64){_t729}, _t730);
        ;
        Str *_t731 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:57:19", 60ULL);
        (void)_t731;
        panic(_t731, _va13);
        Str_delete(_t731, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t739; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t739 = *_hp; free(_hp); }
    (void)_t739;
    if (_t739) {
        Str *_t732 = Str_lit("Str", 3ULL);
        (void)_t732;
        U64 _t733; { U64 *_hp = (U64 *)Str_size(); _t733 = *_hp; free(_hp); }
        (void)_t733;
        U64 _t734 = 1;
        (void)_t734;
        Array *_va14 = Array_new(_t732, &(U64){_t733}, &(U64){_t734});
        (void)_va14;
        Str_delete(_t732, &(Bool){1});
        ;
        ;
        U64 _t735 = 0;
        (void)_t735;
        Str *_t736 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t736;
        Array_set(_va14, &(U64){_t735}, _t736);
        ;
        Str *_t737 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:61:19", 60ULL);
        (void)_t737;
        panic(_t737, _va14);
        Str_delete(_t737, &(Bool){1});
    }
    ;
    void *_t740 = ptr_add(self->c_str, self->count);
    (void)_t740;
    memcpy(_t740, s->c_str, s->count);
    U64 _t741 = U64_clone(new_len);
    (void)_t741;
    self->count = _t741;
    ;
    void *_t742 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t742;
    I64 _t743 = 0;
    (void)_t743;
    U64 _t744 = 1;
    (void)_t744;
    memcpy(_t742, &(I64){_t743}, _t744);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t745 = 1;
    (void)_t745;
    U64 _t746 = U64_add(val->count, _t745);
    (void)_t746;
    ;
    U8 *new_data = malloc(_t746);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t747 = ptr_add(new_data, val->count);
    (void)_t747;
    I64 _t748 = 0;
    (void)_t748;
    U64 _t749 = 1;
    (void)_t749;
    memcpy(_t747, &(I64){_t748}, _t749);
    ;
    ;
    Str *_t750 = malloc(sizeof(Str));
    _t750->c_str = new_data;
    _t750->count = val->count;
    _t750->cap = val->count;
    (void)_t750;
    return _t750;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t751; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t751 = *_hp; free(_hp); }
    (void)_t751;
    if (_t751) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t752 = Str_clone(val);
    (void)_t752;
    return _t752;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t754; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t754 = *_hp; free(_hp); }
    (void)_t754;
    if (_t754) {
        *st = s->count;
    }
    ;
    U64 _t755 = U64_add(DEREF(st), ln);
    (void)_t755;
    Bool _t756; { Bool *_hp = (Bool *)U64_gt(&(U64){_t755}, &s->count); _t756 = *_hp; free(_hp); }
    (void)_t756;
    ;
    if (_t756) {
        U64 _t753 = U64_sub(s->count, DEREF(st));
        (void)_t753;
        ln = _t753;
        ;
    }
    ;
    void *_t757 = ptr_add(s->c_str, DEREF(st));
    (void)_t757;
    U64 _t758 = U64_clone(&(U64){ln});
    (void)_t758;
    ;
    U64 _t759 = U64_clone(CAP_VIEW);
    (void)_t759;
    Str *_t760 = malloc(sizeof(Str));
    _t760->c_str = _t757;
    _t760->count = _t758;
    _t760->cap = _t759;
    (void)_t760;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t760;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t774 = 0;
    (void)_t774;
    Bool _t775 = U64_eq(b->count, _t774);
    (void)_t775;
    ;
    if (_t775) {
        Bool _t761 = 1;
        (void)_t761;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t761; return _r; }
    }
    ;
    Bool _t776; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t776 = *_hp; free(_hp); }
    (void)_t776;
    if (_t776) {
        Bool _t762 = 0;
        (void)_t762;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t762; return _r; }
    }
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t771 = U64_sub(a->count, b->count);
        (void)_t771;
        Bool _wcond763; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t771}); _wcond763 = *_hp; free(_hp); }
        (void)_wcond763;
        ;
        if (_wcond763) {
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
            Bool _wcond764; { Bool *_hp = (Bool *)U64_lt(j, &b->count); _wcond764 = *_hp; free(_hp); }
            (void)_wcond764;
            if (_wcond764) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t766 = malloc(sizeof(U64)); *_t766 = U64_add(i, DEREF(j));
            (void)_t766;
            U8 *ac = Str_get(a, _t766);
            (void)ac;
            U8 *bc = Str_get(b, j);
            (void)bc;
            Bool _t767; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t767 = *_hp; free(_hp); }
            (void)_t767;
            U64_delete(_t766, &(Bool){1});
            if (_t767) {
                Bool _t765 = 0;
                (void)_t765;
                found = _t765;
                ;
            }
            ;
            U64 _t768 = 1;
            (void)_t768;
            U64 _t769 = U64_add(DEREF(j), _t768);
            (void)_t769;
            ;
            *j = _t769;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t770 = 1;
            (void)_t770;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t770; return _r; }
        }
        ;
        U64 _t772 = 1;
        (void)_t772;
        U64 _t773 = U64_add(i, _t772);
        (void)_t773;
        ;
        i = _t773;
        ;
    }
    ;
    Bool _t777 = 0;
    (void)_t777;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t777; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t784; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t784 = *_hp; free(_hp); }
    (void)_t784;
    if (_t784) {
        Bool _t778 = 0;
        (void)_t778;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t778; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        Bool _wcond779; { Bool *_hp = (Bool *)U64_lt(i, &b->count); _wcond779 = *_hp; free(_hp); }
        (void)_wcond779;
        if (_wcond779) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        (void)ac;
        U8 *bc = Str_get(b, i);
        (void)bc;
        Bool _t781; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t781 = *_hp; free(_hp); }
        (void)_t781;
        if (_t781) {
            Bool _t780 = 0;
            (void)_t780;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t780; return _r; }
        }
        ;
        U64 _t782 = 1;
        (void)_t782;
        U64 _t783 = U64_add(DEREF(i), _t782);
        (void)_t783;
        ;
        *i = _t783;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t785 = 1;
    (void)_t785;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t785; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t793; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t793 = *_hp; free(_hp); }
    (void)_t793;
    if (_t793) {
        Bool _t786 = 0;
        (void)_t786;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t786; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        Bool _wcond787; { Bool *_hp = (Bool *)U64_lt(i, &b->count); _wcond787 = *_hp; free(_hp); }
        (void)_wcond787;
        if (_wcond787) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t789 = malloc(sizeof(U64)); *_t789 = U64_add(offset, DEREF(i));
        (void)_t789;
        U8 *ac = Str_get(a, _t789);
        (void)ac;
        U8 *bc = Str_get(b, i);
        (void)bc;
        Bool _t790; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t790 = *_hp; free(_hp); }
        (void)_t790;
        U64_delete(_t789, &(Bool){1});
        if (_t790) {
            Bool _t788 = 0;
            (void)_t788;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t788; return _r; }
        }
        ;
        U64 _t791 = 1;
        (void)_t791;
        U64 _t792 = U64_add(DEREF(i), _t791);
        (void)_t792;
        ;
        *i = _t792;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t794 = 1;
    (void)_t794;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t794; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t795 = 0;
    (void)_t795;
    Bool _t796 = U64_eq(self->count, _t795);
    (void)_t796;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t796; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t814 = 0;
    (void)_t814;
    Bool _t815 = U64_eq(needle->count, _t814);
    (void)_t815;
    ;
    if (_t815) {
        I64 _t797 = 0;
        (void)_t797;
        I64 _t798 = 1;
        (void)_t798;
        I64 _t799 = I64_sub(_t797, _t798);
        (void)_t799;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t799; return _r; }
    }
    ;
    Bool _t816; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t816 = *_hp; free(_hp); }
    (void)_t816;
    if (_t816) {
        I64 _t800 = 0;
        (void)_t800;
        I64 _t801 = 1;
        (void)_t801;
        I64 _t802 = I64_sub(_t800, _t801);
        (void)_t802;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t802; return _r; }
    }
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t811 = U64_sub(self->count, needle->count);
        (void)_t811;
        Bool _wcond803; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t811}); _wcond803 = *_hp; free(_hp); }
        (void)_wcond803;
        ;
        if (_wcond803) {
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
            Bool _wcond804; { Bool *_hp = (Bool *)U64_lt(j, &needle->count); _wcond804 = *_hp; free(_hp); }
            (void)_wcond804;
            if (_wcond804) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t806 = malloc(sizeof(U64)); *_t806 = U64_add(i, DEREF(j));
            (void)_t806;
            U8 *ac = Str_get(self, _t806);
            (void)ac;
            U8 *bc = Str_get(needle, j);
            (void)bc;
            Bool _t807; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t807 = *_hp; free(_hp); }
            (void)_t807;
            U64_delete(_t806, &(Bool){1});
            if (_t807) {
                Bool _t805 = 0;
                (void)_t805;
                found = _t805;
                ;
            }
            ;
            U64 _t808 = 1;
            (void)_t808;
            U64 _t809 = U64_add(DEREF(j), _t808);
            (void)_t809;
            ;
            *j = _t809;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t810 = U64_to_i64(i);
            (void)_t810;
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t810; return _r; }
        }
        ;
        U64 _t812 = 1;
        (void)_t812;
        U64 _t813 = U64_add(i, _t812);
        (void)_t813;
        ;
        i = _t813;
        ;
    }
    ;
    I64 _t817 = 0;
    (void)_t817;
    I64 _t818 = 1;
    (void)_t818;
    I64 _t819 = I64_sub(_t817, _t818);
    (void)_t819;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t819; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t837 = 0;
    (void)_t837;
    Bool _t838 = U64_eq(needle->count, _t837);
    (void)_t838;
    ;
    if (_t838) {
        I64 _t820 = 0;
        (void)_t820;
        I64 _t821 = 1;
        (void)_t821;
        I64 _t822 = I64_sub(_t820, _t821);
        (void)_t822;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t822; return _r; }
    }
    ;
    Bool _t839; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t839 = *_hp; free(_hp); }
    (void)_t839;
    if (_t839) {
        I64 _t823 = 0;
        (void)_t823;
        I64 _t824 = 1;
        (void)_t824;
        I64 _t825 = I64_sub(_t823, _t824);
        (void)_t825;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t825; return _r; }
    }
    ;
    I64 _t840 = 0;
    (void)_t840;
    I64 _t841 = 1;
    (void)_t841;
    I64 last = I64_sub(_t840, _t841);
    (void)last;
    ;
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t834 = U64_sub(self->count, needle->count);
        (void)_t834;
        Bool _wcond826; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t834}); _wcond826 = *_hp; free(_hp); }
        (void)_wcond826;
        ;
        if (_wcond826) {
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
            Bool _wcond827; { Bool *_hp = (Bool *)U64_lt(j, &needle->count); _wcond827 = *_hp; free(_hp); }
            (void)_wcond827;
            if (_wcond827) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t829 = malloc(sizeof(U64)); *_t829 = U64_add(i, DEREF(j));
            (void)_t829;
            U8 *ac = Str_get(self, _t829);
            (void)ac;
            U8 *bc = Str_get(needle, j);
            (void)bc;
            Bool _t830; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t830 = *_hp; free(_hp); }
            (void)_t830;
            U64_delete(_t829, &(Bool){1});
            if (_t830) {
                Bool _t828 = 0;
                (void)_t828;
                found = _t828;
                ;
            }
            ;
            U64 _t831 = 1;
            (void)_t831;
            U64 _t832 = U64_add(DEREF(j), _t831);
            (void)_t832;
            ;
            *j = _t832;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t833 = U64_to_i64(i);
            (void)_t833;
            last = _t833;
            ;
        }
        ;
        U64 _t835 = 1;
        (void)_t835;
        U64 _t836 = U64_add(i, _t835);
        (void)_t836;
        ;
        i = _t836;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t857 = 0;
    (void)_t857;
    Bool _t858 = U64_eq(from->count, _t857);
    (void)_t858;
    ;
    if (_t858) {
        Str *_t842 = Str_clone(self);
        (void)_t842;
        ;
        return _t842;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t844 = U64_sub(self->count, from->count);
        (void)_t844;
        Bool _wcond843; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t844}); _wcond843 = *_hp; free(_hp); }
        (void)_wcond843;
        ;
        if (_wcond843) {
        } else {
            ;
            break;
        }
        ;
        U64 _t845 = U64_sub(self->count, start);
        (void)_t845;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t845});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t846 = 0;
        (void)_t846;
        I64 _t847 = 1;
        (void)_t847;
        I64 _t848 = I64_sub(_t846, _t847);
        (void)_t848;
        ;
        ;
        Bool _t849 = I64_eq(pos, _t848);
        (void)_t849;
        ;
        if (_t849) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t850 = I64_to_u64(pos);
        (void)_t850;
        Str *_t851 = Str_substr(self, &(U64){start}, &(U64){_t850});
        (void)_t851;
        ;
        result = Str_concat(result, _t851);
        Str_delete(_t851, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t852 = I64_to_u64(pos);
        (void)_t852;
        ;
        U64 _t853 = U64_add(start, _t852);
        (void)_t853;
        ;
        U64 _t854 = U64_add(_t853, from->count);
        (void)_t854;
        ;
        start = _t854;
        ;
    }
    Bool _t859; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t859 = *_hp; free(_hp); }
    (void)_t859;
    if (_t859) {
        U64 _t855 = U64_sub(self->count, start);
        (void)_t855;
        Str *_t856 = Str_substr(self, &(U64){start}, &(U64){_t855});
        (void)_t856;
        ;
        result = Str_concat(result, _t856);
        Str_delete(_t856, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t860 = 1;
    (void)_t860;
    Str *_t861 = Str_substr(self, i, &(U64){_t860});
    (void)_t861;
    ;
    return _t861;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t864; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t864 = *_hp; free(_hp); }
    (void)_t864;
    if (_t864) {
        U64 _t862 = U64_sub(self->count, prefix->count);
        (void)_t862;
        Str *_t863 = Str_substr(self, &prefix->count, &(U64){_t862});
        (void)_t863;
        ;
        ;
        return _t863;
    }
    ;
    Str *_t865 = Str_clone(self);
    (void)_t865;
    return _t865;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t869; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t869 = *_hp; free(_hp); }
    (void)_t869;
    if (_t869) {
        U64 _t866 = 0;
        (void)_t866;
        U64 _t867 = U64_sub(self->count, suffix->count);
        (void)_t867;
        Str *_t868 = Str_substr(self, &(U64){_t866}, &(U64){_t867});
        (void)_t868;
        ;
        ;
        ;
        return _t868;
    }
    ;
    Str *_t870 = Str_clone(self);
    (void)_t870;
    return _t870;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t871 = 2;
    (void)_t871;
    U8 *buf = malloc(_t871);
    (void)buf;
    ;
    U64 _t872 = 1;
    (void)_t872;
    memcpy(buf, byte, _t872);
    ;
    U64 *_t873 = malloc(sizeof(U64));
    *_t873 = 1;
    (void)_t873;
    void *_t874 = ptr_add(buf, DEREF(_t873));
    (void)_t874;
    I64 _t875 = 0;
    (void)_t875;
    U64 _t876 = 1;
    (void)_t876;
    memcpy(_t874, &(I64){_t875}, _t876);
    U64_delete(_t873, &(Bool){1});
    ;
    ;
    I64 _t877 = 1;
    (void)_t877;
    I64 _t878 = 1;
    (void)_t878;
    Str *_t879 = malloc(sizeof(Str));
    _t879->c_str = buf;
    _t879->count = _t877;
    _t879->cap = _t878;
    (void)_t879;
    ;
    ;
    return _t879;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t919 = 0;
    (void)_t919;
    Bool _t920 = U64_eq(self->count, _t919);
    (void)_t920;
    ;
    if (_t920) {
        Str *_t880 = Str_lit("Str", 3ULL);
        (void)_t880;
        U64 _t881; { U64 *_hp = (U64 *)Str_size(); _t881 = *_hp; free(_hp); }
        (void)_t881;
        U64 _t882 = 1;
        (void)_t882;
        Array *_va15 = Array_new(_t880, &(U64){_t881}, &(U64){_t882});
        (void)_va15;
        Str_delete(_t880, &(Bool){1});
        ;
        ;
        U64 _t883 = 0;
        (void)_t883;
        Str *_t884 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t884;
        Array_set(_va15, &(U64){_t883}, _t884);
        ;
        Str *_t885 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:224:37", 61ULL);
        (void)_t885;
        panic(_t885, _va15);
        Str_delete(_t885, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    Bool neg = 0;
    (void)neg;
    U64 *_t921 = malloc(sizeof(U64));
    *_t921 = 0;
    (void)_t921;
    U8 *first = Str_get(self, _t921);
    (void)first;
    U8 _t922 = 45;
    (void)_t922;
    Bool _t923 = U8_eq(DEREF(first), _t922);
    (void)_t923;
    U64_delete(_t921, &(Bool){1});
    ;
    if (_t923) {
        Bool _t886 = 1;
        (void)_t886;
        neg = _t886;
        ;
        U64 _t887 = 1;
        (void)_t887;
        *i = _t887;
        ;
    }
    ;
    Bool _t924 = U64_eq(DEREF(i), self->count);
    (void)_t924;
    if (_t924) {
        Str *_t888 = Str_lit("Str", 3ULL);
        (void)_t888;
        U64 _t889; { U64 *_hp = (U64 *)Str_size(); _t889 = *_hp; free(_hp); }
        (void)_t889;
        U64 _t890 = 1;
        (void)_t890;
        Array *_va16 = Array_new(_t888, &(U64){_t889}, &(U64){_t890});
        (void)_va16;
        Str_delete(_t888, &(Bool){1});
        ;
        ;
        U64 _t891 = 0;
        (void)_t891;
        Str *_t892 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t892;
        Array_set(_va16, &(U64){_t891}, _t892);
        ;
        Str *_t893 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:233:37", 61ULL);
        (void)_t893;
        panic(_t893, _va16);
        Str_delete(_t893, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond894; { Bool *_hp = (Bool *)U64_lt(i, &self->count); _wcond894 = *_hp; free(_hp); }
        (void)_wcond894;
        if (_wcond894) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        (void)ch;
        I64 _t905 = U8_to_i64(DEREF(ch));
        (void)_t905;
        I64 _t906 = 48;
        (void)_t906;
        I64 d = I64_sub(_t905, _t906);
        (void)d;
        ;
        ;
        I64 _t907 = 0;
        (void)_t907;
        I64 _t908 = 9;
        (void)_t908;
        Bool _t909; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t907}); _t909 = *_hp; free(_hp); }
        (void)_t909;
        ;
        Bool _t910; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t908}); _t910 = *_hp; free(_hp); }
        (void)_t910;
        ;
        Bool _t911 = Bool_or(_t909, _t910);
        (void)_t911;
        ;
        ;
        if (_t911) {
            Str *_t895 = Str_lit("Str", 3ULL);
            (void)_t895;
            U64 _t896; { U64 *_hp = (U64 *)Str_size(); _t896 = *_hp; free(_hp); }
            (void)_t896;
            U64 _t897 = 3;
            (void)_t897;
            Array *_va17 = Array_new(_t895, &(U64){_t896}, &(U64){_t897});
            (void)_va17;
            Str_delete(_t895, &(Bool){1});
            ;
            ;
            U64 _t898 = 0;
            (void)_t898;
            Str *_t899 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
            (void)_t899;
            Array_set(_va17, &(U64){_t898}, _t899);
            ;
            U64 _t900 = 1;
            (void)_t900;
            Str *_t901 = Str_clone(self);
            (void)_t901;
            Array_set(_va17, &(U64){_t900}, _t901);
            ;
            U64 _t902 = 2;
            (void)_t902;
            Str *_t903 = Str_lit("'", 1ULL);
            (void)_t903;
            Array_set(_va17, &(U64){_t902}, _t903);
            ;
            Str *_t904 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:238:23", 61ULL);
            (void)_t904;
            panic(_t904, _va17);
            Str_delete(_t904, &(Bool){1});
        }
        ;
        I64 _t912 = 10;
        (void)_t912;
        I64 _t913 = I64_mul(result, _t912);
        (void)_t913;
        ;
        I64 _t914 = I64_add(_t913, d);
        (void)_t914;
        ;
        ;
        result = _t914;
        ;
        U64 _t915 = 1;
        (void)_t915;
        U64 _t916 = U64_add(DEREF(i), _t915);
        (void)_t916;
        ;
        *i = _t916;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t917 = 0;
        (void)_t917;
        I64 _t918 = I64_sub(_t917, result);
        (void)_t918;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t918; return _r; }
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
    I64 _t926; { I64 *_hp = (I64 *)Str_cmp(a, b); _t926 = *_hp; free(_hp); }
    (void)_t926;
    I64 _t927 = 0;
    (void)_t927;
    Bool _t928 = I64_eq(_t926, _t927);
    (void)_t928;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t928; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t929 = 0;
    (void)_t929;
    I64 _t930 = 1;
    (void)_t930;
    I64 _t931; { I64 *_hp = (I64 *)Str_cmp(a, b); _t931 = *_hp; free(_hp); }
    (void)_t931;
    I64 _t932 = I64_sub(_t929, _t930);
    (void)_t932;
    ;
    ;
    Bool _t933 = I64_eq(_t931, _t932);
    (void)_t933;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t933; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t934; { I64 *_hp = (I64 *)Str_cmp(a, b); _t934 = *_hp; free(_hp); }
    (void)_t934;
    I64 _t935 = 1;
    (void)_t935;
    Bool _t936 = I64_eq(_t934, _t935);
    (void)_t936;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t936; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t937; { Bool *_hp = (Bool *)Str_eq(a, b); _t937 = *_hp; free(_hp); }
    (void)_t937;
    Bool _t938 = Bool_not(_t937);
    (void)_t938;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t938; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t939; { Bool *_hp = (Bool *)Str_gt(a, b); _t939 = *_hp; free(_hp); }
    (void)_t939;
    Bool _t940 = Bool_not(_t939);
    (void)_t940;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t940; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t941; { Bool *_hp = (Bool *)Str_lt(a, b); _t941 = *_hp; free(_hp); }
    (void)_t941;
    Bool _t942 = Bool_not(_t941);
    (void)_t942;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t942; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t943 = malloc(DEREF(elem_size));
    (void)_t943;
    U64 _t944 = 0;
    (void)_t944;
    I64 _t945 = 1;
    (void)_t945;
    U64 _t946 = U64_clone(elem_size);
    (void)_t946;
    Vec *_t947 = malloc(sizeof(Vec));
    _t947->data = _t943;
    _t947->count = _t944;
    _t947->cap = _t945;
    _t947->elem_size = _t946;
    { Str *_ca = Str_clone(elem_type); _t947->elem_type = *_ca; free(_ca); }
    (void)_t947;
    ;
    ;
    ;
    return _t947;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t952 = U64_eq(self->count, self->cap);
    (void)_t952;
    if (_t952) {
        U64 _t948 = 2;
        (void)_t948;
        U64 new_cap = U64_mul(self->cap, _t948);
        (void)new_cap;
        ;
        U64 _t949 = U64_mul(new_cap, self->elem_size);
        (void)_t949;
        void *_t950 = realloc(self->data, _t949);
        (void)_t950;
        ;
        self->data = _t950;
        U64 _t951 = U64_clone(&(U64){new_cap});
        (void)_t951;
        ;
        self->cap = _t951;
        ;
    }
    ;
    U64 *_t953 = malloc(sizeof(U64)); *_t953 = U64_mul(self->count, self->elem_size);
    (void)_t953;
    void *_t954 = ptr_add(self->data, DEREF(_t953));
    (void)_t954;
    memcpy(_t954, val, self->elem_size);
    U64_delete(_t953, &(Bool){1});
    free(val);
    U64 _t955 = 1;
    (void)_t955;
    U64 _t956 = U64_add(self->count, _t955);
    (void)_t956;
    ;
    self->count = _t956;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t971; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t971 = *_hp; free(_hp); }
    (void)_t971;
    if (_t971) {
        Str *_t957 = Str_lit("Str", 3ULL);
        (void)_t957;
        U64 _t958; { U64 *_hp = (U64 *)Str_size(); _t958 = *_hp; free(_hp); }
        (void)_t958;
        U64 _t959 = 5;
        (void)_t959;
        Array *_va18 = Array_new(_t957, &(U64){_t958}, &(U64){_t959});
        (void)_va18;
        Str_delete(_t957, &(Bool){1});
        ;
        ;
        U64 _t960 = 0;
        (void)_t960;
        Str *_t961 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t961;
        Array_set(_va18, &(U64){_t960}, _t961);
        ;
        U64 _t962 = 1;
        (void)_t962;
        Str *_t963 = U64_to_str(DEREF(i));
        (void)_t963;
        Array_set(_va18, &(U64){_t962}, _t963);
        ;
        U64 _t964 = 2;
        (void)_t964;
        Str *_t965 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t965;
        Array_set(_va18, &(U64){_t964}, _t965);
        ;
        U64 _t966 = 3;
        (void)_t966;
        Str *_t967 = U64_to_str(self->count);
        (void)_t967;
        Array_set(_va18, &(U64){_t966}, _t967);
        ;
        U64 _t968 = 4;
        (void)_t968;
        Str *_t969 = Str_lit(")", 1ULL);
        (void)_t969;
        Array_set(_va18, &(U64){_t968}, _t969);
        ;
        Str *_t970 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t970;
        panic(_t970, _va18);
        Str_delete(_t970, &(Bool){1});
    }
    ;
    U64 *_t972 = malloc(sizeof(U64)); *_t972 = U64_mul(DEREF(i), self->elem_size);
    (void)_t972;
    void *_t973 = ptr_add(self->data, DEREF(_t972));
    (void)_t973;
    U64_delete(_t972, &(Bool){1});
    return _t973;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t987; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t987 = *_hp; free(_hp); }
    (void)_t987;
    Bool _t988 = Bool_not(_t987);
    (void)_t988;
    ;
    if (_t988) {
        {
            U64 _fi974 = 0;
            (void)_fi974;
            while (1) {
                U64 _t976 = 0;
                (void)_t976;
                Range *_t977 = Range_new(_t976, self->count);
                (void)_t977;
                ;
                U64 _t978; { U64 *_hp = (U64 *)Range_len(_t977); _t978 = *_hp; free(_hp); }
                (void)_t978;
                Range_delete(_t977, &(Bool){1});
                Bool _wcond975; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi974}, &(U64){_t978}); _wcond975 = *_hp; free(_hp); }
                (void)_wcond975;
                ;
                if (_wcond975) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t979 = 0;
                (void)_t979;
                Range *_t980 = Range_new(_t979, self->count);
                (void)_t980;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t980, _fi974); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t980, &(Bool){1});
                U64 _t981 = 1;
                (void)_t981;
                U64 _t982 = U64_add(_fi974, _t981);
                (void)_t982;
                ;
                _fi974 = _t982;
                ;
                U64 *_t983 = malloc(sizeof(U64)); *_t983 = U64_mul(i, self->elem_size);
                (void)_t983;
                ;
                void *_t984 = ptr_add(self->data, DEREF(_t983));
                (void)_t984;
                Bool _t985 = 0;
                (void)_t985;
                dyn_call_delete(&self->elem_type, _t984, &(Bool){_t985});
                U64_delete(_t983, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t989; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t989 = *_hp; free(_hp); }
    (void)_t989;
    Bool _t990 = Bool_not(_t989);
    (void)_t990;
    ;
    if (_t990) {
        Bool _t986 = 0;
        (void)_t986;
        Str_delete(&self->elem_type, &(Bool){_t986});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1004 = U64_mul(self->cap, self->elem_size);
    (void)_t1004;
    U8 *new_data = malloc(_t1004);
    (void)new_data;
    ;
    {
        U64 _fi991 = 0;
        (void)_fi991;
        while (1) {
            U64 _t993 = 0;
            (void)_t993;
            Range *_t994 = Range_new(_t993, self->count);
            (void)_t994;
            ;
            U64 _t995; { U64 *_hp = (U64 *)Range_len(_t994); _t995 = *_hp; free(_hp); }
            (void)_t995;
            Range_delete(_t994, &(Bool){1});
            Bool _wcond992; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi991}, &(U64){_t995}); _wcond992 = *_hp; free(_hp); }
            (void)_wcond992;
            ;
            if (_wcond992) {
            } else {
                ;
                break;
            }
            ;
            U64 _t996 = 0;
            (void)_t996;
            Range *_t997 = Range_new(_t996, self->count);
            (void)_t997;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t997, _fi991); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t997, &(Bool){1});
            U64 _t998 = 1;
            (void)_t998;
            U64 _t999 = U64_add(_fi991, _t998);
            (void)_t999;
            ;
            _fi991 = _t999;
            ;
            U64 *_t1000 = malloc(sizeof(U64)); *_t1000 = U64_mul(i, self->elem_size);
            (void)_t1000;
            void *_t1001 = ptr_add(self->data, DEREF(_t1000));
            (void)_t1001;
            void *cloned = dyn_call_clone(&self->elem_type, _t1001);
            (void)cloned;
            U64_delete(_t1000, &(Bool){1});
            U64 *_t1002 = malloc(sizeof(U64)); *_t1002 = U64_mul(i, self->elem_size);
            (void)_t1002;
            ;
            void *_t1003 = ptr_add(new_data, DEREF(_t1002));
            (void)_t1003;
            memcpy(_t1003, cloned, self->elem_size);
            U64_delete(_t1002, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1005 = malloc(sizeof(Vec));
    _t1005->data = new_data;
    _t1005->count = self->count;
    _t1005->cap = self->cap;
    _t1005->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1005->elem_type = *_ca; free(_ca); }
    (void)_t1005;
    return _t1005;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    (void)s;
    (void)delim;
    Str *_t1023 = Str_lit("Str", 3ULL);
    (void)_t1023;
    U64 _t1024; { U64 *_hp = (U64 *)Str_size(); _t1024 = *_hp; free(_hp); }
    (void)_t1024;
    Vec *parts = Vec_new(_t1023, &(U64){_t1024});
    (void)parts;
    Str_delete(_t1023, &(Bool){1});
    ;
    U64 _t1025; { U64 *_hp = (U64 *)Str_len(delim); _t1025 = *_hp; free(_hp); }
    (void)_t1025;
    U64 _t1026 = 0;
    (void)_t1026;
    Bool _t1027 = U64_eq(_t1025, _t1026);
    (void)_t1027;
    ;
    ;
    if (_t1027) {
        Str *_t1007 = Str_clone(s);
        (void)_t1007;
        Vec_push(parts, _t1007);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1017; { U64 *_hp = (U64 *)Str_len(s); _t1017 = *_hp; free(_hp); }
        (void)_t1017;
        U64 _t1018; { U64 *_hp = (U64 *)Str_len(delim); _t1018 = *_hp; free(_hp); }
        (void)_t1018;
        U64 _t1019 = U64_sub(_t1017, _t1018);
        (void)_t1019;
        ;
        ;
        Bool _wcond1008; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1019}); _wcond1008 = *_hp; free(_hp); }
        (void)_wcond1008;
        ;
        if (_wcond1008) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1020; { U64 *_hp = (U64 *)Str_len(delim); _t1020 = *_hp; free(_hp); }
        (void)_t1020;
        Str *_t1021 = Str_substr(s, &(U64){pos}, &(U64){_t1020});
        (void)_t1021;
        ;
        Bool _t1022; { Bool *_hp = (Bool *)Str_eq(_t1021, delim); _t1022 = *_hp; free(_hp); }
        (void)_t1022;
        Str_delete(_t1021, &(Bool){1});
        if (_t1022) {
            U64 _t1009 = U64_sub(pos, start);
            (void)_t1009;
            Str *_t1010 = Str_substr(s, &(U64){start}, &(U64){_t1009});
            (void)_t1010;
            ;
            Str *_t1011 = Str_clone(_t1010);
            (void)_t1011;
            Str_delete(_t1010, &(Bool){1});
            Vec_push(parts, _t1011);
            U64 _t1012; { U64 *_hp = (U64 *)Str_len(delim); _t1012 = *_hp; free(_hp); }
            (void)_t1012;
            U64 _t1013 = U64_add(pos, _t1012);
            (void)_t1013;
            ;
            start = _t1013;
            ;
            U64 _t1014 = U64_clone(&(U64){start});
            (void)_t1014;
            pos = _t1014;
            ;
        } else {
            U64 _t1015 = 1;
            (void)_t1015;
            U64 _t1016 = U64_add(pos, _t1015);
            (void)_t1016;
            ;
            pos = _t1016;
            ;
        }
        ;
    }
    ;
    U64 _t1028; { U64 *_hp = (U64 *)Str_len(s); _t1028 = *_hp; free(_hp); }
    (void)_t1028;
    U64 _t1029 = U64_sub(_t1028, start);
    (void)_t1029;
    ;
    Str *_t1030 = Str_substr(s, &(U64){start}, &(U64){_t1029});
    (void)_t1030;
    ;
    ;
    Str *_t1031 = Str_clone(_t1030);
    (void)_t1031;
    Str_delete(_t1030, &(Bool){1});
    Vec_push(parts, _t1031);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1039; { U64 *_hp = (U64 *)Vec_len(parts); _t1039 = *_hp; free(_hp); }
    (void)_t1039;
    U64 _t1040 = 0;
    (void)_t1040;
    Bool _t1041 = U64_eq(_t1039, _t1040);
    (void)_t1041;
    ;
    ;
    if (_t1041) {
        Str *_t1032 = Str_lit("", 0ULL);
        (void)_t1032;
        ;
        return _t1032;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        U64 _t1034; { U64 *_hp = (U64 *)Vec_len(parts); _t1034 = *_hp; free(_hp); }
        (void)_t1034;
        Bool _wcond1033; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1034}); _wcond1033 = *_hp; free(_hp); }
        (void)_wcond1033;
        ;
        if (_wcond1033) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1035 = 0;
        (void)_t1035;
        Bool _t1036; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1035}); _t1036 = *_hp; free(_hp); }
        (void)_t1036;
        ;
        if (_t1036) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        (void)p;
        result = Str_concat(result, p);
        U64 _t1037 = 1;
        (void)_t1037;
        U64 _t1038 = U64_add(DEREF(i), _t1037);
        (void)_t1038;
        ;
        *i = _t1038;
        ;
    }
    U64_delete(i, &(Bool){1});
    return result;
}

Tuple * Tuple_new(void) {
    U64 _t1042 = 8;
    (void)_t1042;
    Str *_t1043 = Str_lit("Str", 3ULL);
    (void)_t1043;
    U64 _t1044; { U64 *_hp = (U64 *)Str_size(); _t1044 = *_hp; free(_hp); }
    (void)_t1044;
    Str *_t1045 = Str_lit("U64", 3ULL);
    (void)_t1045;
    U64 _t1046; { U64 *_hp = (U64 *)U64_size(); _t1046 = *_hp; free(_hp); }
    (void)_t1046;
    void *_t1047 = malloc(_t1042);
    (void)_t1047;
    ;
    U64 _t1048 = 0;
    (void)_t1048;
    I64 _t1049 = 8;
    (void)_t1049;
    Tuple *_t1050 = malloc(sizeof(Tuple));
    _t1050->data = _t1047;
    _t1050->total_size = _t1048;
    _t1050->cap = _t1049;
    { Vec *_ca = Vec_new(_t1043, &(U64){_t1044}); _t1050->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1045, &(U64){_t1046}); _t1050->type_sizes = *_ca; free(_ca); }
    (void)_t1050;
    Str_delete(_t1043, &(Bool){1});
    ;
    Str_delete(_t1045, &(Bool){1});
    ;
    ;
    ;
    return _t1050;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1051; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1051 = *_hp; free(_hp); }
    (void)_t1051;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1051; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1058; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1058 = *_hp; free(_hp); }
    (void)_t1058;
    if (_t1058) {
        U64 _t1055 = 2;
        (void)_t1055;
        U64 new_cap = U64_mul(self->cap, _t1055);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1052; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1052 = *_hp; free(_hp); }
            (void)_wcond1052;
            if (_wcond1052) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1053 = 2;
            (void)_t1053;
            U64 _t1054 = U64_mul(new_cap, _t1053);
            (void)_t1054;
            ;
            new_cap = _t1054;
            ;
        }
        void *_t1056 = realloc(self->data, new_cap);
        (void)_t1056;
        self->data = _t1056;
        U64 _t1057 = U64_clone(&(U64){new_cap});
        (void)_t1057;
        ;
        self->cap = _t1057;
        ;
    }
    ;
    void *_t1059 = ptr_add(self->data, self->total_size);
    (void)_t1059;
    memcpy(_t1059, val, DEREF(elem_size));
    free(val);
    Str *_t1060 = Str_clone(elem_type);
    (void)_t1060;
    Vec_push(&self->type_names, _t1060);
    U64 _t1061 = U64_clone(elem_size);
    (void)_t1061;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1061; _oa; }));
    U64 _t1062 = U64_clone(&(U64){new_total});
    (void)_t1062;
    ;
    self->total_size = _t1062;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1082; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1082 = *_hp; free(_hp); }
    (void)_t1082;
    Bool _t1083; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1082}); _t1083 = *_hp; free(_hp); }
    (void)_t1083;
    ;
    if (_t1083) {
        Str *_t1063 = Str_lit("Str", 3ULL);
        (void)_t1063;
        U64 _t1064; { U64 *_hp = (U64 *)Str_size(); _t1064 = *_hp; free(_hp); }
        (void)_t1064;
        U64 _t1065 = 5;
        (void)_t1065;
        Array *_va19 = Array_new(_t1063, &(U64){_t1064}, &(U64){_t1065});
        (void)_va19;
        Str_delete(_t1063, &(Bool){1});
        ;
        ;
        U64 _t1066 = 0;
        (void)_t1066;
        Str *_t1067 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1067;
        Array_set(_va19, &(U64){_t1066}, _t1067);
        ;
        U64 _t1068 = 1;
        (void)_t1068;
        Str *_t1069 = U64_to_str(DEREF(i));
        (void)_t1069;
        Array_set(_va19, &(U64){_t1068}, _t1069);
        ;
        U64 _t1070 = 2;
        (void)_t1070;
        Str *_t1071 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1071;
        Array_set(_va19, &(U64){_t1070}, _t1071);
        ;
        U64 _t1072; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1072 = *_hp; free(_hp); }
        (void)_t1072;
        U64 _t1073 = 3;
        (void)_t1073;
        Str *_t1074 = U64_to_str(_t1072);
        (void)_t1074;
        ;
        Array_set(_va19, &(U64){_t1073}, _t1074);
        ;
        U64 _t1075 = 4;
        (void)_t1075;
        Str *_t1076 = Str_lit(")", 1ULL);
        (void)_t1076;
        Array_set(_va19, &(U64){_t1075}, _t1076);
        ;
        Str *_t1077 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1077;
        panic(_t1077, _va19);
        Str_delete(_t1077, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    U64 *j = malloc(sizeof(U64));
    *j = 0;
    (void)j;
    while (1) {
        Bool _wcond1078; { Bool *_hp = (Bool *)U64_lt(j, i); _wcond1078 = *_hp; free(_hp); }
        (void)_wcond1078;
        if (_wcond1078) {
        } else {
            ;
            break;
        }
        ;
        U64 *sz = Vec_get(&self->type_sizes, j);
        (void)sz;
        U64 _t1079 = U64_add(DEREF(offset), DEREF(sz));
        (void)_t1079;
        *offset = _t1079;
        ;
        U64 _t1080 = 1;
        (void)_t1080;
        U64 _t1081 = U64_add(DEREF(j), _t1080);
        (void)_t1081;
        ;
        *j = _t1081;
        ;
    }
    U64_delete(j, &(Bool){1});
    void *_t1084 = ptr_add(self->data, DEREF(offset));
    (void)_t1084;
    U64_delete(offset, &(Bool){1});
    return _t1084;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1085 = Vec_get(&self->type_names, i);
    (void)_t1085;
    return _t1085;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1086 = Vec_get(&self->type_sizes, i);
    (void)_t1086;
    return _t1086;
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
        U64 _t1088; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1088 = *_hp; free(_hp); }
        (void)_t1088;
        Bool _wcond1087; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1088}); _wcond1087 = *_hp; free(_hp); }
        (void)_wcond1087;
        ;
        if (_wcond1087) {
        } else {
            ;
            break;
        }
        ;
        Str *tn = Vec_get(&self->type_names, i);
        (void)tn;
        U64 *ts = Vec_get(&self->type_sizes, i);
        (void)ts;
        void *_t1089 = ptr_add(self->data, DEREF(offset));
        (void)_t1089;
        Bool _t1090 = 0;
        (void)_t1090;
        dyn_call_delete(tn, _t1089, &(Bool){_t1090});
        ;
        U64 _t1091 = U64_add(DEREF(offset), DEREF(ts));
        (void)_t1091;
        *offset = _t1091;
        ;
        U64 _t1092 = 1;
        (void)_t1092;
        U64 _t1093 = U64_add(DEREF(i), _t1092);
        (void)_t1093;
        ;
        *i = _t1093;
        ;
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1094 = 0;
    (void)_t1094;
    Vec_delete(&self->type_names, &(Bool){_t1094});
    ;
    Bool _t1095 = 0;
    (void)_t1095;
    Vec_delete(&self->type_sizes, &(Bool){_t1095});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1105 = 0;
    (void)_t1105;
    Bool _t1106 = U64_eq(new_cap, _t1105);
    (void)_t1106;
    ;
    if (_t1106) {
        I64 _t1096 = 8;
        (void)_t1096;
        U64 _t1097; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1096}); _t1097 = *_hp; free(_hp); }
        (void)_t1097;
        ;
        new_cap = _t1097;
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
        U64 _t1099; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1099 = *_hp; free(_hp); }
        (void)_t1099;
        Bool _wcond1098; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1099}); _wcond1098 = *_hp; free(_hp); }
        (void)_wcond1098;
        ;
        if (_wcond1098) {
        } else {
            ;
            break;
        }
        ;
        Str *tn = Vec_get(&self->type_names, i);
        (void)tn;
        U64 *ts = Vec_get(&self->type_sizes, i);
        (void)ts;
        void *_t1100 = ptr_add(self->data, DEREF(offset));
        (void)_t1100;
        void *cloned = dyn_call_clone(tn, _t1100);
        (void)cloned;
        void *_t1101 = ptr_add(new_data, DEREF(offset));
        (void)_t1101;
        memcpy(_t1101, cloned, DEREF(ts));
        free(cloned);
        U64 _t1102 = U64_add(DEREF(offset), DEREF(ts));
        (void)_t1102;
        *offset = _t1102;
        ;
        U64 _t1103 = 1;
        (void)_t1103;
        U64 _t1104 = U64_add(DEREF(i), _t1103);
        (void)_t1104;
        ;
        *i = _t1104;
        ;
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    U64 _t1107 = U64_clone(&(U64){new_cap});
    (void)_t1107;
    ;
    Vec *_t1108 = Vec_clone(&self->type_names);
    (void)_t1108;
    Vec *_t1109 = Vec_clone(&self->type_sizes);
    (void)_t1109;
    Tuple *_t1110 = malloc(sizeof(Tuple));
    _t1110->data = new_data;
    _t1110->total_size = self->total_size;
    _t1110->cap = _t1107;
    { Vec *_ca = Vec_clone(_t1108); _t1110->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1109); _t1110->type_sizes = *_ca; free(_ca); }
    (void)_t1110;
    ;
    Vec_delete(_t1108, &(Bool){1});
    Vec_delete(_t1109, &(Bool){1});
    return _t1110;
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
    Bool _t1177; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t1177 = *_hp; free(_hp); }
    (void)_t1177;
    if (_t1177) {
        Bool _t1112; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t1112 = *_hp; free(_hp); }
        (void)_t1112;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1112; return _r; }
    }
    ;
    Bool _t1178; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t1178 = *_hp; free(_hp); }
    (void)_t1178;
    if (_t1178) {
        Bool _t1113; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t1113 = *_hp; free(_hp); }
        (void)_t1113;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1113; return _r; }
    }
    ;
    Bool _t1179; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t1179 = *_hp; free(_hp); }
    (void)_t1179;
    if (_t1179) {
        Bool _t1114; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t1114 = *_hp; free(_hp); }
        (void)_t1114;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1114; return _r; }
    }
    ;
    Bool _t1180; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t1180 = *_hp; free(_hp); }
    (void)_t1180;
    if (_t1180) {
        Bool _t1115; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t1115 = *_hp; free(_hp); }
        (void)_t1115;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1115; return _r; }
    }
    ;
    Bool _t1181; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t1181 = *_hp; free(_hp); }
    (void)_t1181;
    if (_t1181) {
        Bool _t1116; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t1116 = *_hp; free(_hp); }
        (void)_t1116;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1116; return _r; }
    }
    ;
    Bool _t1182; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t1182 = *_hp; free(_hp); }
    (void)_t1182;
    if (_t1182) {
        Bool _t1117; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t1117 = *_hp; free(_hp); }
        (void)_t1117;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1117; return _r; }
    }
    ;
    Bool _t1183; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t1183 = *_hp; free(_hp); }
    (void)_t1183;
    if (_t1183) {
        Bool _t1118; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t1118 = *_hp; free(_hp); }
        (void)_t1118;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1118; return _r; }
    }
    ;
    Bool _t1184; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t1184 = *_hp; free(_hp); }
    (void)_t1184;
    if (_t1184) {
        Bool _t1119; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t1119 = *_hp; free(_hp); }
        (void)_t1119;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1119; return _r; }
    }
    ;
    Bool _t1185; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t1185 = *_hp; free(_hp); }
    (void)_t1185;
    if (_t1185) {
        Bool _t1120; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t1120 = *_hp; free(_hp); }
        (void)_t1120;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1120; return _r; }
    }
    ;
    Bool _t1186; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t1186 = *_hp; free(_hp); }
    (void)_t1186;
    if (_t1186) {
        Bool _t1121; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t1121 = *_hp; free(_hp); }
        (void)_t1121;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1121; return _r; }
    }
    ;
    Bool _t1187; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t1187 = *_hp; free(_hp); }
    (void)_t1187;
    if (_t1187) {
        Bool _t1122; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t1122 = *_hp; free(_hp); }
        (void)_t1122;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1122; return _r; }
    }
    ;
    Bool _t1188; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t1188 = *_hp; free(_hp); }
    (void)_t1188;
    if (_t1188) {
        Bool _t1123; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t1123 = *_hp; free(_hp); }
        (void)_t1123;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1123; return _r; }
    }
    ;
    Bool _t1189; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t1189 = *_hp; free(_hp); }
    (void)_t1189;
    if (_t1189) {
        Bool _t1124; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t1124 = *_hp; free(_hp); }
        (void)_t1124;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1124; return _r; }
    }
    ;
    Bool _t1190; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t1190 = *_hp; free(_hp); }
    (void)_t1190;
    if (_t1190) {
        Bool _t1125; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t1125 = *_hp; free(_hp); }
        (void)_t1125;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1125; return _r; }
    }
    ;
    Bool _t1191; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t1191 = *_hp; free(_hp); }
    (void)_t1191;
    if (_t1191) {
        Bool _t1126; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t1126 = *_hp; free(_hp); }
        (void)_t1126;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1126; return _r; }
    }
    ;
    Bool _t1192; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t1192 = *_hp; free(_hp); }
    (void)_t1192;
    if (_t1192) {
        Bool _t1127; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t1127 = *_hp; free(_hp); }
        (void)_t1127;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1127; return _r; }
    }
    ;
    Bool _t1193; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t1193 = *_hp; free(_hp); }
    (void)_t1193;
    if (_t1193) {
        Bool _t1128; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t1128 = *_hp; free(_hp); }
        (void)_t1128;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1128; return _r; }
    }
    ;
    Bool _t1194; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t1194 = *_hp; free(_hp); }
    (void)_t1194;
    if (_t1194) {
        Bool _t1129; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t1129 = *_hp; free(_hp); }
        (void)_t1129;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1129; return _r; }
    }
    ;
    Bool _t1195; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t1195 = *_hp; free(_hp); }
    (void)_t1195;
    if (_t1195) {
        Bool _t1130; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t1130 = *_hp; free(_hp); }
        (void)_t1130;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1130; return _r; }
    }
    ;
    Bool _t1196; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t1196 = *_hp; free(_hp); }
    (void)_t1196;
    if (_t1196) {
        Bool _t1131; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t1131 = *_hp; free(_hp); }
        (void)_t1131;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1131; return _r; }
    }
    ;
    Bool _t1197; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t1197 = *_hp; free(_hp); }
    (void)_t1197;
    if (_t1197) {
        Bool _t1132; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t1132 = *_hp; free(_hp); }
        (void)_t1132;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1132; return _r; }
    }
    ;
    Bool _t1198; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t1198 = *_hp; free(_hp); }
    (void)_t1198;
    if (_t1198) {
        Bool _t1133; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t1133 = *_hp; free(_hp); }
        (void)_t1133;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1133; return _r; }
    }
    ;
    Bool _t1199; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t1199 = *_hp; free(_hp); }
    (void)_t1199;
    if (_t1199) {
        Bool _t1134; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t1134 = *_hp; free(_hp); }
        (void)_t1134;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1134; return _r; }
    }
    ;
    Bool _t1200; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t1200 = *_hp; free(_hp); }
    (void)_t1200;
    if (_t1200) {
        Bool _t1135; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t1135 = *_hp; free(_hp); }
        (void)_t1135;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1135; return _r; }
    }
    ;
    Bool _t1201; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t1201 = *_hp; free(_hp); }
    (void)_t1201;
    if (_t1201) {
        Bool _t1136; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t1136 = *_hp; free(_hp); }
        (void)_t1136;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1136; return _r; }
    }
    ;
    Bool _t1202; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t1202 = *_hp; free(_hp); }
    (void)_t1202;
    if (_t1202) {
        Bool _t1137; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t1137 = *_hp; free(_hp); }
        (void)_t1137;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1137; return _r; }
    }
    ;
    Bool _t1203; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t1203 = *_hp; free(_hp); }
    (void)_t1203;
    if (_t1203) {
        Bool _t1138; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t1138 = *_hp; free(_hp); }
        (void)_t1138;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1138; return _r; }
    }
    ;
    Bool _t1204; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t1204 = *_hp; free(_hp); }
    (void)_t1204;
    if (_t1204) {
        Bool _t1139; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t1139 = *_hp; free(_hp); }
        (void)_t1139;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1139; return _r; }
    }
    ;
    Bool _t1205; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t1205 = *_hp; free(_hp); }
    (void)_t1205;
    if (_t1205) {
        Bool _t1140; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t1140 = *_hp; free(_hp); }
        (void)_t1140;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1140; return _r; }
    }
    ;
    Bool _t1206; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t1206 = *_hp; free(_hp); }
    (void)_t1206;
    if (_t1206) {
        Bool _t1141; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t1141 = *_hp; free(_hp); }
        (void)_t1141;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1141; return _r; }
    }
    ;
    Bool _t1207; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t1207 = *_hp; free(_hp); }
    (void)_t1207;
    if (_t1207) {
        Bool _t1142; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t1142 = *_hp; free(_hp); }
        (void)_t1142;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1142; return _r; }
    }
    ;
    Bool _t1208; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t1208 = *_hp; free(_hp); }
    (void)_t1208;
    if (_t1208) {
        Bool _t1143; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t1143 = *_hp; free(_hp); }
        (void)_t1143;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1143; return _r; }
    }
    ;
    Bool _t1209; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t1209 = *_hp; free(_hp); }
    (void)_t1209;
    if (_t1209) {
        Bool _t1144; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t1144 = *_hp; free(_hp); }
        (void)_t1144;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1144; return _r; }
    }
    ;
    Bool _t1210; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t1210 = *_hp; free(_hp); }
    (void)_t1210;
    if (_t1210) {
        Bool _t1145; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t1145 = *_hp; free(_hp); }
        (void)_t1145;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1145; return _r; }
    }
    ;
    Bool _t1211; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t1211 = *_hp; free(_hp); }
    (void)_t1211;
    if (_t1211) {
        Bool _t1146; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t1146 = *_hp; free(_hp); }
        (void)_t1146;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1146; return _r; }
    }
    ;
    Bool _t1212; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t1212 = *_hp; free(_hp); }
    (void)_t1212;
    if (_t1212) {
        Bool _t1147; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t1147 = *_hp; free(_hp); }
        (void)_t1147;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1147; return _r; }
    }
    ;
    Bool _t1213; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t1213 = *_hp; free(_hp); }
    (void)_t1213;
    if (_t1213) {
        Bool _t1148; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t1148 = *_hp; free(_hp); }
        (void)_t1148;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1148; return _r; }
    }
    ;
    Bool _t1214; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t1214 = *_hp; free(_hp); }
    (void)_t1214;
    if (_t1214) {
        Bool _t1149; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t1149 = *_hp; free(_hp); }
        (void)_t1149;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1149; return _r; }
    }
    ;
    Bool _t1215; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t1215 = *_hp; free(_hp); }
    (void)_t1215;
    if (_t1215) {
        Bool _t1150; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t1150 = *_hp; free(_hp); }
        (void)_t1150;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1150; return _r; }
    }
    ;
    Bool _t1216; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t1216 = *_hp; free(_hp); }
    (void)_t1216;
    if (_t1216) {
        Bool _t1151; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t1151 = *_hp; free(_hp); }
        (void)_t1151;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1151; return _r; }
    }
    ;
    Bool _t1217; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t1217 = *_hp; free(_hp); }
    (void)_t1217;
    if (_t1217) {
        Bool _t1152; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t1152 = *_hp; free(_hp); }
        (void)_t1152;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1152; return _r; }
    }
    ;
    Bool _t1218; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t1218 = *_hp; free(_hp); }
    (void)_t1218;
    if (_t1218) {
        Bool _t1153; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t1153 = *_hp; free(_hp); }
        (void)_t1153;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1153; return _r; }
    }
    ;
    Bool _t1219; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t1219 = *_hp; free(_hp); }
    (void)_t1219;
    if (_t1219) {
        Bool _t1154; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t1154 = *_hp; free(_hp); }
        (void)_t1154;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1154; return _r; }
    }
    ;
    Bool _t1220; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t1220 = *_hp; free(_hp); }
    (void)_t1220;
    if (_t1220) {
        Bool _t1155; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t1155 = *_hp; free(_hp); }
        (void)_t1155;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1155; return _r; }
    }
    ;
    Bool _t1221; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t1221 = *_hp; free(_hp); }
    (void)_t1221;
    if (_t1221) {
        Bool _t1156; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t1156 = *_hp; free(_hp); }
        (void)_t1156;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1156; return _r; }
    }
    ;
    Bool _t1222; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t1222 = *_hp; free(_hp); }
    (void)_t1222;
    if (_t1222) {
        Bool _t1157; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t1157 = *_hp; free(_hp); }
        (void)_t1157;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1157; return _r; }
    }
    ;
    Bool _t1223; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t1223 = *_hp; free(_hp); }
    (void)_t1223;
    if (_t1223) {
        Bool _t1158; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t1158 = *_hp; free(_hp); }
        (void)_t1158;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1158; return _r; }
    }
    ;
    Bool _t1224; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t1224 = *_hp; free(_hp); }
    (void)_t1224;
    if (_t1224) {
        Bool _t1159; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t1159 = *_hp; free(_hp); }
        (void)_t1159;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1159; return _r; }
    }
    ;
    Bool _t1225; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t1225 = *_hp; free(_hp); }
    (void)_t1225;
    if (_t1225) {
        Bool _t1160; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t1160 = *_hp; free(_hp); }
        (void)_t1160;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1160; return _r; }
    }
    ;
    Bool _t1226; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t1226 = *_hp; free(_hp); }
    (void)_t1226;
    if (_t1226) {
        Bool _t1161; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t1161 = *_hp; free(_hp); }
        (void)_t1161;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1161; return _r; }
    }
    ;
    Bool _t1227; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t1227 = *_hp; free(_hp); }
    (void)_t1227;
    if (_t1227) {
        Bool _t1162; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t1162 = *_hp; free(_hp); }
        (void)_t1162;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1162; return _r; }
    }
    ;
    Bool _t1228; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t1228 = *_hp; free(_hp); }
    (void)_t1228;
    if (_t1228) {
        Bool _t1163; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t1163 = *_hp; free(_hp); }
        (void)_t1163;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1163; return _r; }
    }
    ;
    Bool _t1229; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t1229 = *_hp; free(_hp); }
    (void)_t1229;
    if (_t1229) {
        Bool _t1164; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t1164 = *_hp; free(_hp); }
        (void)_t1164;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1164; return _r; }
    }
    ;
    Bool _t1230; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t1230 = *_hp; free(_hp); }
    (void)_t1230;
    if (_t1230) {
        Bool _t1165; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t1165 = *_hp; free(_hp); }
        (void)_t1165;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1165; return _r; }
    }
    ;
    Bool _t1231; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t1231 = *_hp; free(_hp); }
    (void)_t1231;
    if (_t1231) {
        Bool _t1166; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t1166 = *_hp; free(_hp); }
        (void)_t1166;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1166; return _r; }
    }
    ;
    Bool _t1232; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t1232 = *_hp; free(_hp); }
    (void)_t1232;
    if (_t1232) {
        Bool _t1167; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t1167 = *_hp; free(_hp); }
        (void)_t1167;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1167; return _r; }
    }
    ;
    Bool _t1233; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t1233 = *_hp; free(_hp); }
    (void)_t1233;
    if (_t1233) {
        Bool _t1168; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t1168 = *_hp; free(_hp); }
        (void)_t1168;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1168; return _r; }
    }
    ;
    Bool _t1234; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t1234 = *_hp; free(_hp); }
    (void)_t1234;
    if (_t1234) {
        Bool _t1169; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t1169 = *_hp; free(_hp); }
        (void)_t1169;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1169; return _r; }
    }
    ;
    Bool _t1235; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t1235 = *_hp; free(_hp); }
    (void)_t1235;
    if (_t1235) {
        Bool _t1170; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t1170 = *_hp; free(_hp); }
        (void)_t1170;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1170; return _r; }
    }
    ;
    Bool _t1236; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t1236 = *_hp; free(_hp); }
    (void)_t1236;
    if (_t1236) {
        Bool _t1171; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t1171 = *_hp; free(_hp); }
        (void)_t1171;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1171; return _r; }
    }
    ;
    Bool _t1237; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t1237 = *_hp; free(_hp); }
    (void)_t1237;
    if (_t1237) {
        Bool _t1172; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t1172 = *_hp; free(_hp); }
        (void)_t1172;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1172; return _r; }
    }
    ;
    Bool _t1238; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t1238 = *_hp; free(_hp); }
    (void)_t1238;
    if (_t1238) {
        Bool _t1173; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t1173 = *_hp; free(_hp); }
        (void)_t1173;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1173; return _r; }
    }
    ;
    Bool _t1239; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t1239 = *_hp; free(_hp); }
    (void)_t1239;
    if (_t1239) {
        Bool _t1174; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t1174 = *_hp; free(_hp); }
        (void)_t1174;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1174; return _r; }
    }
    ;
    Bool _t1240; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t1240 = *_hp; free(_hp); }
    (void)_t1240;
    if (_t1240) {
        Bool _t1175; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t1175 = *_hp; free(_hp); }
        (void)_t1175;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1175; return _r; }
    }
    ;
    Bool _t1241; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t1241 = *_hp; free(_hp); }
    (void)_t1241;
    if (_t1241) {
        Bool _t1176; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t1176 = *_hp; free(_hp); }
        (void)_t1176;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1176; return _r; }
    }
    ;
    Bool _t1242 = 0;
    (void)_t1242;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1242; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1243; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1243 = *_hp; free(_hp); }
    (void)_t1243;
    if (_t1243) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1244; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1244 = *_hp; free(_hp); }
    (void)_t1244;
    if (_t1244) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1245; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1245 = *_hp; free(_hp); }
    (void)_t1245;
    if (_t1245) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1246; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1246 = *_hp; free(_hp); }
    (void)_t1246;
    if (_t1246) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1247; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1247 = *_hp; free(_hp); }
    (void)_t1247;
    if (_t1247) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1248; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1248 = *_hp; free(_hp); }
    (void)_t1248;
    if (_t1248) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1249; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1249 = *_hp; free(_hp); }
    (void)_t1249;
    if (_t1249) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1250; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1250 = *_hp; free(_hp); }
    (void)_t1250;
    if (_t1250) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1251; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1251 = *_hp; free(_hp); }
    (void)_t1251;
    if (_t1251) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1252; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1252 = *_hp; free(_hp); }
    (void)_t1252;
    if (_t1252) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1253; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1253 = *_hp; free(_hp); }
    (void)_t1253;
    if (_t1253) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1254; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1254 = *_hp; free(_hp); }
    (void)_t1254;
    if (_t1254) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1255; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1255 = *_hp; free(_hp); }
    (void)_t1255;
    if (_t1255) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1256; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1256 = *_hp; free(_hp); }
    (void)_t1256;
    if (_t1256) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1257; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1257 = *_hp; free(_hp); }
    (void)_t1257;
    if (_t1257) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1258; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1258 = *_hp; free(_hp); }
    (void)_t1258;
    if (_t1258) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1259; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1259 = *_hp; free(_hp); }
    (void)_t1259;
    if (_t1259) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1260; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1260 = *_hp; free(_hp); }
    (void)_t1260;
    if (_t1260) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1261; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1261 = *_hp; free(_hp); }
    (void)_t1261;
    if (_t1261) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1262; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1262 = *_hp; free(_hp); }
    (void)_t1262;
    if (_t1262) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1263; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1263 = *_hp; free(_hp); }
    (void)_t1263;
    if (_t1263) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1264; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1264 = *_hp; free(_hp); }
    (void)_t1264;
    if (_t1264) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1265; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1265 = *_hp; free(_hp); }
    (void)_t1265;
    if (_t1265) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1266; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1266 = *_hp; free(_hp); }
    (void)_t1266;
    if (_t1266) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1267; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1267 = *_hp; free(_hp); }
    (void)_t1267;
    if (_t1267) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1268; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1268 = *_hp; free(_hp); }
    (void)_t1268;
    if (_t1268) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1269; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1269 = *_hp; free(_hp); }
    (void)_t1269;
    if (_t1269) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1270; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1270 = *_hp; free(_hp); }
    (void)_t1270;
    if (_t1270) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1271; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1271 = *_hp; free(_hp); }
    (void)_t1271;
    if (_t1271) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1272; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1272 = *_hp; free(_hp); }
    (void)_t1272;
    if (_t1272) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1273; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1273 = *_hp; free(_hp); }
    (void)_t1273;
    if (_t1273) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1274; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1274 = *_hp; free(_hp); }
    (void)_t1274;
    if (_t1274) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1275; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1275 = *_hp; free(_hp); }
    (void)_t1275;
    if (_t1275) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1276; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1276 = *_hp; free(_hp); }
    (void)_t1276;
    if (_t1276) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t1277; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1277 = *_hp; free(_hp); }
    (void)_t1277;
    if (_t1277) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1278; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1278 = *_hp; free(_hp); }
    (void)_t1278;
    if (_t1278) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1279; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1279 = *_hp; free(_hp); }
    (void)_t1279;
    if (_t1279) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1280; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1280 = *_hp; free(_hp); }
    (void)_t1280;
    if (_t1280) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1281; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1281 = *_hp; free(_hp); }
    (void)_t1281;
    if (_t1281) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1282; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1282 = *_hp; free(_hp); }
    (void)_t1282;
    if (_t1282) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1283; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1283 = *_hp; free(_hp); }
    (void)_t1283;
    if (_t1283) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1284; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1284 = *_hp; free(_hp); }
    (void)_t1284;
    if (_t1284) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1285; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1285 = *_hp; free(_hp); }
    (void)_t1285;
    if (_t1285) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1286; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1286 = *_hp; free(_hp); }
    (void)_t1286;
    if (_t1286) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1287; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1287 = *_hp; free(_hp); }
    (void)_t1287;
    if (_t1287) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1288; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1288 = *_hp; free(_hp); }
    (void)_t1288;
    if (_t1288) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1289; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1289 = *_hp; free(_hp); }
    (void)_t1289;
    if (_t1289) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1290; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1290 = *_hp; free(_hp); }
    (void)_t1290;
    if (_t1290) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1291; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1291 = *_hp; free(_hp); }
    (void)_t1291;
    if (_t1291) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1292; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1292 = *_hp; free(_hp); }
    (void)_t1292;
    if (_t1292) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1293; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1293 = *_hp; free(_hp); }
    (void)_t1293;
    if (_t1293) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1294; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1294 = *_hp; free(_hp); }
    (void)_t1294;
    if (_t1294) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1295; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1295 = *_hp; free(_hp); }
    (void)_t1295;
    if (_t1295) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1296; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1296 = *_hp; free(_hp); }
    (void)_t1296;
    if (_t1296) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1297; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1297 = *_hp; free(_hp); }
    (void)_t1297;
    if (_t1297) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1298; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1298 = *_hp; free(_hp); }
    (void)_t1298;
    if (_t1298) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1299; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1299 = *_hp; free(_hp); }
    (void)_t1299;
    if (_t1299) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1300; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1300 = *_hp; free(_hp); }
    (void)_t1300;
    if (_t1300) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1301; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1301 = *_hp; free(_hp); }
    (void)_t1301;
    if (_t1301) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1302; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1302 = *_hp; free(_hp); }
    (void)_t1302;
    if (_t1302) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1303; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1303 = *_hp; free(_hp); }
    (void)_t1303;
    if (_t1303) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1304; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1304 = *_hp; free(_hp); }
    (void)_t1304;
    if (_t1304) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1305; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1305 = *_hp; free(_hp); }
    (void)_t1305;
    if (_t1305) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t1306; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1306 = *_hp; free(_hp); }
    (void)_t1306;
    if (_t1306) {
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
    Bool _t1372; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1372 = *_hp; free(_hp); }
    (void)_t1372;
    if (_t1372) {
        Str *_t1307 = Str_lit("Eof", 3ULL);
        (void)_t1307;
        ;
        return _t1307;
    }
    ;
    Bool _t1373; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1373 = *_hp; free(_hp); }
    (void)_t1373;
    if (_t1373) {
        Str *_t1308 = Str_lit("LParen", 6ULL);
        (void)_t1308;
        ;
        return _t1308;
    }
    ;
    Bool _t1374; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1374 = *_hp; free(_hp); }
    (void)_t1374;
    if (_t1374) {
        Str *_t1309 = Str_lit("RParen", 6ULL);
        (void)_t1309;
        ;
        return _t1309;
    }
    ;
    Bool _t1375; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1375 = *_hp; free(_hp); }
    (void)_t1375;
    if (_t1375) {
        Str *_t1310 = Str_lit("LBrace", 6ULL);
        (void)_t1310;
        ;
        return _t1310;
    }
    ;
    Bool _t1376; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        Str *_t1311 = Str_lit("RBrace", 6ULL);
        (void)_t1311;
        ;
        return _t1311;
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        Str *_t1312 = Str_lit("LBracket", 8ULL);
        (void)_t1312;
        ;
        return _t1312;
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        Str *_t1313 = Str_lit("RBracket", 8ULL);
        (void)_t1313;
        ;
        return _t1313;
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        Str *_t1314 = Str_lit("Comma", 5ULL);
        (void)_t1314;
        ;
        return _t1314;
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        Str *_t1315 = Str_lit("Colon", 5ULL);
        (void)_t1315;
        ;
        return _t1315;
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        Str *_t1316 = Str_lit("Question", 8ULL);
        (void)_t1316;
        ;
        return _t1316;
    }
    ;
    Bool _t1382; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    if (_t1382) {
        Str *_t1317 = Str_lit("Bang", 4ULL);
        (void)_t1317;
        ;
        return _t1317;
    }
    ;
    Bool _t1383; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1383 = *_hp; free(_hp); }
    (void)_t1383;
    if (_t1383) {
        Str *_t1318 = Str_lit("Minus", 5ULL);
        (void)_t1318;
        ;
        return _t1318;
    }
    ;
    Bool _t1384; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1384 = *_hp; free(_hp); }
    (void)_t1384;
    if (_t1384) {
        Str *_t1319 = Str_lit("Plus", 4ULL);
        (void)_t1319;
        ;
        return _t1319;
    }
    ;
    Bool _t1385; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1385 = *_hp; free(_hp); }
    (void)_t1385;
    if (_t1385) {
        Str *_t1320 = Str_lit("Star", 4ULL);
        (void)_t1320;
        ;
        return _t1320;
    }
    ;
    Bool _t1386; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1386 = *_hp; free(_hp); }
    (void)_t1386;
    if (_t1386) {
        Str *_t1321 = Str_lit("Slash", 5ULL);
        (void)_t1321;
        ;
        return _t1321;
    }
    ;
    Bool _t1387; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    if (_t1387) {
        Str *_t1322 = Str_lit("Dot", 3ULL);
        (void)_t1322;
        ;
        return _t1322;
    }
    ;
    Bool _t1388; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1388 = *_hp; free(_hp); }
    (void)_t1388;
    if (_t1388) {
        Str *_t1323 = Str_lit("DotDot", 6ULL);
        (void)_t1323;
        ;
        return _t1323;
    }
    ;
    Bool _t1389; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1389 = *_hp; free(_hp); }
    (void)_t1389;
    if (_t1389) {
        Str *_t1324 = Str_lit("Eq", 2ULL);
        (void)_t1324;
        ;
        return _t1324;
    }
    ;
    Bool _t1390; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1390 = *_hp; free(_hp); }
    (void)_t1390;
    if (_t1390) {
        Str *_t1325 = Str_lit("EqEq", 4ULL);
        (void)_t1325;
        ;
        return _t1325;
    }
    ;
    Bool _t1391; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1391 = *_hp; free(_hp); }
    (void)_t1391;
    if (_t1391) {
        Str *_t1326 = Str_lit("Neq", 3ULL);
        (void)_t1326;
        ;
        return _t1326;
    }
    ;
    Bool _t1392; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    if (_t1392) {
        Str *_t1327 = Str_lit("Lt", 2ULL);
        (void)_t1327;
        ;
        return _t1327;
    }
    ;
    Bool _t1393; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        Str *_t1328 = Str_lit("LtEq", 4ULL);
        (void)_t1328;
        ;
        return _t1328;
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        Str *_t1329 = Str_lit("Gt", 2ULL);
        (void)_t1329;
        ;
        return _t1329;
    }
    ;
    Bool _t1395; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1395 = *_hp; free(_hp); }
    (void)_t1395;
    if (_t1395) {
        Str *_t1330 = Str_lit("GtEq", 4ULL);
        (void)_t1330;
        ;
        return _t1330;
    }
    ;
    Bool _t1396; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        Str *_t1331 = Str_lit("ColonEq", 7ULL);
        (void)_t1331;
        ;
        return _t1331;
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        Str *_t1332 = Str_lit("Ident", 5ULL);
        (void)_t1332;
        ;
        return _t1332;
    }
    ;
    Bool _t1398; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1398 = *_hp; free(_hp); }
    (void)_t1398;
    if (_t1398) {
        Str *_t1333 = Str_lit("StringTok", 9ULL);
        (void)_t1333;
        ;
        return _t1333;
    }
    ;
    Bool _t1399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1399 = *_hp; free(_hp); }
    (void)_t1399;
    if (_t1399) {
        Str *_t1334 = Str_lit("Number", 6ULL);
        (void)_t1334;
        ;
        return _t1334;
    }
    ;
    Bool _t1400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        Str *_t1335 = Str_lit("Char", 4ULL);
        (void)_t1335;
        ;
        return _t1335;
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        Str *_t1336 = Str_lit("KwMode", 6ULL);
        (void)_t1336;
        ;
        return _t1336;
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        Str *_t1337 = Str_lit("KwMut", 5ULL);
        (void)_t1337;
        ;
        return _t1337;
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        Str *_t1338 = Str_lit("KwOwn", 5ULL);
        (void)_t1338;
        ;
        return _t1338;
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
        Str *_t1339 = Str_lit("KwRef", 5ULL);
        (void)_t1339;
        ;
        return _t1339;
    }
    ;
    Bool _t1405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1405 = *_hp; free(_hp); }
    (void)_t1405;
    if (_t1405) {
        Str *_t1340 = Str_lit("KwShallow", 9ULL);
        (void)_t1340;
        ;
        return _t1340;
    }
    ;
    Bool _t1406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1406 = *_hp; free(_hp); }
    (void)_t1406;
    if (_t1406) {
        Str *_t1341 = Str_lit("KwStruct", 8ULL);
        (void)_t1341;
        ;
        return _t1341;
    }
    ;
    Bool _t1407; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1407 = *_hp; free(_hp); }
    (void)_t1407;
    if (_t1407) {
        Str *_t1342 = Str_lit("KwExtStruct", 11ULL);
        (void)_t1342;
        ;
        return _t1342;
    }
    ;
    Bool _t1408; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1408 = *_hp; free(_hp); }
    (void)_t1408;
    if (_t1408) {
        Str *_t1343 = Str_lit("KwEnum", 6ULL);
        (void)_t1343;
        ;
        return _t1343;
    }
    ;
    Bool _t1409; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1409 = *_hp; free(_hp); }
    (void)_t1409;
    if (_t1409) {
        Str *_t1344 = Str_lit("KwNamespace", 11ULL);
        (void)_t1344;
        ;
        return _t1344;
    }
    ;
    Bool _t1410; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1410 = *_hp; free(_hp); }
    (void)_t1410;
    if (_t1410) {
        Str *_t1345 = Str_lit("KwFunc", 6ULL);
        (void)_t1345;
        ;
        return _t1345;
    }
    ;
    Bool _t1411; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1411 = *_hp; free(_hp); }
    (void)_t1411;
    if (_t1411) {
        Str *_t1346 = Str_lit("KwProc", 6ULL);
        (void)_t1346;
        ;
        return _t1346;
    }
    ;
    Bool _t1412; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1412 = *_hp; free(_hp); }
    (void)_t1412;
    if (_t1412) {
        Str *_t1347 = Str_lit("KwTest", 6ULL);
        (void)_t1347;
        ;
        return _t1347;
    }
    ;
    Bool _t1413; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1413 = *_hp; free(_hp); }
    (void)_t1413;
    if (_t1413) {
        Str *_t1348 = Str_lit("KwMacro", 7ULL);
        (void)_t1348;
        ;
        return _t1348;
    }
    ;
    Bool _t1414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1414 = *_hp; free(_hp); }
    (void)_t1414;
    if (_t1414) {
        Str *_t1349 = Str_lit("KwExtFunc", 9ULL);
        (void)_t1349;
        ;
        return _t1349;
    }
    ;
    Bool _t1415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1415 = *_hp; free(_hp); }
    (void)_t1415;
    if (_t1415) {
        Str *_t1350 = Str_lit("KwExtProc", 9ULL);
        (void)_t1350;
        ;
        return _t1350;
    }
    ;
    Bool _t1416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1416 = *_hp; free(_hp); }
    (void)_t1416;
    if (_t1416) {
        Str *_t1351 = Str_lit("KwReturns", 9ULL);
        (void)_t1351;
        ;
        return _t1351;
    }
    ;
    Bool _t1417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1417 = *_hp; free(_hp); }
    (void)_t1417;
    if (_t1417) {
        Str *_t1352 = Str_lit("KwThrows", 8ULL);
        (void)_t1352;
        ;
        return _t1352;
    }
    ;
    Bool _t1418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1418 = *_hp; free(_hp); }
    (void)_t1418;
    if (_t1418) {
        Str *_t1353 = Str_lit("KwIf", 4ULL);
        (void)_t1353;
        ;
        return _t1353;
    }
    ;
    Bool _t1419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1419 = *_hp; free(_hp); }
    (void)_t1419;
    if (_t1419) {
        Str *_t1354 = Str_lit("KwElse", 6ULL);
        (void)_t1354;
        ;
        return _t1354;
    }
    ;
    Bool _t1420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1420 = *_hp; free(_hp); }
    (void)_t1420;
    if (_t1420) {
        Str *_t1355 = Str_lit("KwWhile", 7ULL);
        (void)_t1355;
        ;
        return _t1355;
    }
    ;
    Bool _t1421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1421 = *_hp; free(_hp); }
    (void)_t1421;
    if (_t1421) {
        Str *_t1356 = Str_lit("KwFor", 5ULL);
        (void)_t1356;
        ;
        return _t1356;
    }
    ;
    Bool _t1422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1422 = *_hp; free(_hp); }
    (void)_t1422;
    if (_t1422) {
        Str *_t1357 = Str_lit("KwIn", 4ULL);
        (void)_t1357;
        ;
        return _t1357;
    }
    ;
    Bool _t1423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1423 = *_hp; free(_hp); }
    (void)_t1423;
    if (_t1423) {
        Str *_t1358 = Str_lit("KwSwitch", 8ULL);
        (void)_t1358;
        ;
        return _t1358;
    }
    ;
    Bool _t1424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1424 = *_hp; free(_hp); }
    (void)_t1424;
    if (_t1424) {
        Str *_t1359 = Str_lit("KwMatch", 7ULL);
        (void)_t1359;
        ;
        return _t1359;
    }
    ;
    Bool _t1425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1425 = *_hp; free(_hp); }
    (void)_t1425;
    if (_t1425) {
        Str *_t1360 = Str_lit("KwCase", 6ULL);
        (void)_t1360;
        ;
        return _t1360;
    }
    ;
    Bool _t1426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1426 = *_hp; free(_hp); }
    (void)_t1426;
    if (_t1426) {
        Str *_t1361 = Str_lit("KwDefault", 9ULL);
        (void)_t1361;
        ;
        return _t1361;
    }
    ;
    Bool _t1427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1427 = *_hp; free(_hp); }
    (void)_t1427;
    if (_t1427) {
        Str *_t1362 = Str_lit("KwReturn", 8ULL);
        (void)_t1362;
        ;
        return _t1362;
    }
    ;
    Bool _t1428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1428 = *_hp; free(_hp); }
    (void)_t1428;
    if (_t1428) {
        Str *_t1363 = Str_lit("KwThrow", 7ULL);
        (void)_t1363;
        ;
        return _t1363;
    }
    ;
    Bool _t1429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1429 = *_hp; free(_hp); }
    (void)_t1429;
    if (_t1429) {
        Str *_t1364 = Str_lit("KwCatch", 7ULL);
        (void)_t1364;
        ;
        return _t1364;
    }
    ;
    Bool _t1430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1430 = *_hp; free(_hp); }
    (void)_t1430;
    if (_t1430) {
        Str *_t1365 = Str_lit("KwBreak", 7ULL);
        (void)_t1365;
        ;
        return _t1365;
    }
    ;
    Bool _t1431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1431 = *_hp; free(_hp); }
    (void)_t1431;
    if (_t1431) {
        Str *_t1366 = Str_lit("KwContinue", 10ULL);
        (void)_t1366;
        ;
        return _t1366;
    }
    ;
    Bool _t1432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1432 = *_hp; free(_hp); }
    (void)_t1432;
    if (_t1432) {
        Str *_t1367 = Str_lit("KwDefer", 7ULL);
        (void)_t1367;
        ;
        return _t1367;
    }
    ;
    Bool _t1433; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1433 = *_hp; free(_hp); }
    (void)_t1433;
    if (_t1433) {
        Str *_t1368 = Str_lit("KwTrue", 6ULL);
        (void)_t1368;
        ;
        return _t1368;
    }
    ;
    Bool _t1434; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1434 = *_hp; free(_hp); }
    (void)_t1434;
    if (_t1434) {
        Str *_t1369 = Str_lit("KwFalse", 7ULL);
        (void)_t1369;
        ;
        return _t1369;
    }
    ;
    Bool _t1435; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1435 = *_hp; free(_hp); }
    (void)_t1435;
    if (_t1435) {
        Str *_t1370 = Str_lit("KwNull", 6ULL);
        (void)_t1370;
        ;
        return _t1370;
    }
    ;
    Bool _t1436; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t1436 = *_hp; free(_hp); }
    (void)_t1436;
    if (_t1436) {
        Str *_t1371 = Str_lit("Error", 5ULL);
        (void)_t1371;
        ;
        return _t1371;
    }
    ;
    Str *_t1437 = Str_lit("unknown", 7ULL);
    (void)_t1437;
    return _t1437;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1439 = I64_clone(&self->line);
    (void)_t1439;
    I64 _t1440 = I64_clone(&self->col);
    (void)_t1440;
    Token *_t1441 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1441->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1441->text = *_ca; free(_ca); }
    _t1441->line = _t1439;
    _t1441->col = _t1440;
    (void)_t1441;
    ;
    ;
    return _t1441;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1442 = 0;
    (void)_t1442;
    TokenType_delete(&self->type, &(Bool){_t1442});
    ;
    Bool _t1443 = 0;
    (void)_t1443;
    Str_delete(&self->text, &(Bool){_t1443});
    ;
    Bool _t1444 = 0;
    (void)_t1444;
    I64_delete(&self->line, &(Bool){_t1444});
    ;
    Bool _t1445 = 0;
    (void)_t1445;
    I64_delete(&self->col, &(Bool){_t1445});
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
    U8 _t1447 = 48;
    (void)_t1447;
    U8 _t1448 = 57;
    (void)_t1448;
    Bool _t1449; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1447}); _t1449 = *_hp; free(_hp); }
    (void)_t1449;
    ;
    Bool _t1450; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1448}); _t1450 = *_hp; free(_hp); }
    (void)_t1450;
    ;
    Bool _t1451 = Bool_and(_t1449, _t1450);
    (void)_t1451;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1451; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t1452 = 97;
    (void)_t1452;
    U8 _t1453 = 122;
    (void)_t1453;
    Bool _t1454; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1452}); _t1454 = *_hp; free(_hp); }
    (void)_t1454;
    ;
    Bool _t1455; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1453}); _t1455 = *_hp; free(_hp); }
    (void)_t1455;
    ;
    U8 _t1456 = 65;
    (void)_t1456;
    U8 _t1457 = 90;
    (void)_t1457;
    Bool _t1458; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1456}); _t1458 = *_hp; free(_hp); }
    (void)_t1458;
    ;
    Bool _t1459; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1457}); _t1459 = *_hp; free(_hp); }
    (void)_t1459;
    ;
    Bool _t1460 = Bool_and(_t1454, _t1455);
    (void)_t1460;
    ;
    ;
    Bool _t1461 = Bool_and(_t1458, _t1459);
    (void)_t1461;
    ;
    ;
    U8 _t1462 = 95;
    (void)_t1462;
    Bool _t1463 = Bool_or(_t1460, _t1461);
    (void)_t1463;
    ;
    ;
    Bool _t1464 = U8_eq(DEREF(c), _t1462);
    (void)_t1464;
    ;
    Bool _t1465 = Bool_or(_t1463, _t1464);
    (void)_t1465;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1465; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t1466; { Bool *_hp = (Bool *)is_alpha(c); _t1466 = *_hp; free(_hp); }
    (void)_t1466;
    Bool _t1467; { Bool *_hp = (Bool *)is_digit(c); _t1467 = *_hp; free(_hp); }
    (void)_t1467;
    Bool _t1468 = Bool_or(_t1466, _t1467);
    (void)_t1468;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1468; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw1469 = TokenType_clone(type);
        (void)_sw1469;
        Bool _t1600; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Eof()); _t1600 = *_hp; free(_hp); }
        (void)_t1600;
        if (_t1600) {
            Str *_t1470 = Str_lit("eof", 3ULL);
            (void)_t1470;
            TokenType_delete(_sw1469, &(Bool){1});
            ;
            return _t1470;
        } else {
            Bool _t1599; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_LParen()); _t1599 = *_hp; free(_hp); }
            (void)_t1599;
            if (_t1599) {
                Str *_t1471 = Str_lit("(", 1ULL);
                (void)_t1471;
                ;
                TokenType_delete(_sw1469, &(Bool){1});
                ;
                return _t1471;
            } else {
                Bool _t1598; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_RParen()); _t1598 = *_hp; free(_hp); }
                (void)_t1598;
                if (_t1598) {
                    Str *_t1472 = Str_lit(")", 1ULL);
                    (void)_t1472;
                    ;
                    ;
                    TokenType_delete(_sw1469, &(Bool){1});
                    ;
                    return _t1472;
                } else {
                    Bool _t1597; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_LBrace()); _t1597 = *_hp; free(_hp); }
                    (void)_t1597;
                    if (_t1597) {
                        Str *_t1473 = Str_lit("{", 1ULL);
                        (void)_t1473;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1469, &(Bool){1});
                        ;
                        return _t1473;
                    } else {
                        Bool _t1596; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_RBrace()); _t1596 = *_hp; free(_hp); }
                        (void)_t1596;
                        if (_t1596) {
                            Str *_t1474 = Str_lit("}", 1ULL);
                            (void)_t1474;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1469, &(Bool){1});
                            ;
                            return _t1474;
                        } else {
                            Bool _t1595; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_LBracket()); _t1595 = *_hp; free(_hp); }
                            (void)_t1595;
                            if (_t1595) {
                                Str *_t1475 = Str_lit("[", 1ULL);
                                (void)_t1475;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1469, &(Bool){1});
                                ;
                                return _t1475;
                            } else {
                                Bool _t1594; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_RBracket()); _t1594 = *_hp; free(_hp); }
                                (void)_t1594;
                                if (_t1594) {
                                    Str *_t1476 = Str_lit("]", 1ULL);
                                    (void)_t1476;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1469, &(Bool){1});
                                    ;
                                    return _t1476;
                                } else {
                                    Bool _t1593; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Comma()); _t1593 = *_hp; free(_hp); }
                                    (void)_t1593;
                                    if (_t1593) {
                                        Str *_t1477 = Str_lit(",", 1ULL);
                                        (void)_t1477;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1469, &(Bool){1});
                                        ;
                                        return _t1477;
                                    } else {
                                        Bool _t1592; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Colon()); _t1592 = *_hp; free(_hp); }
                                        (void)_t1592;
                                        if (_t1592) {
                                            Str *_t1478 = Str_lit(":", 1ULL);
                                            (void)_t1478;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1469, &(Bool){1});
                                            ;
                                            return _t1478;
                                        } else {
                                            Bool _t1591; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Question()); _t1591 = *_hp; free(_hp); }
                                            (void)_t1591;
                                            if (_t1591) {
                                                Str *_t1479 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw1469, &(Bool){1});
                                                ;
                                                return _t1479;
                                            } else {
                                                Bool _t1590; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Bang()); _t1590 = *_hp; free(_hp); }
                                                (void)_t1590;
                                                if (_t1590) {
                                                    Str *_t1480 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                    ;
                                                    return _t1480;
                                                } else {
                                                    Bool _t1589; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Minus()); _t1589 = *_hp; free(_hp); }
                                                    (void)_t1589;
                                                    if (_t1589) {
                                                        Str *_t1481 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                        ;
                                                        return _t1481;
                                                    } else {
                                                        Bool _t1588; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Plus()); _t1588 = *_hp; free(_hp); }
                                                        (void)_t1588;
                                                        if (_t1588) {
                                                            Str *_t1482 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                            ;
                                                            return _t1482;
                                                        } else {
                                                            Bool _t1587; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Star()); _t1587 = *_hp; free(_hp); }
                                                            (void)_t1587;
                                                            if (_t1587) {
                                                                Str *_t1483 = Str_lit("*", 1ULL);
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
                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                ;
                                                                return _t1483;
                                                            } else {
                                                                Bool _t1586; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Slash()); _t1586 = *_hp; free(_hp); }
                                                                (void)_t1586;
                                                                if (_t1586) {
                                                                    Str *_t1484 = Str_lit("/", 1ULL);
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
                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                    ;
                                                                    return _t1484;
                                                                } else {
                                                                    Bool _t1585; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Dot()); _t1585 = *_hp; free(_hp); }
                                                                    (void)_t1585;
                                                                    if (_t1585) {
                                                                        Str *_t1485 = Str_lit(".", 1ULL);
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
                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                        ;
                                                                        return _t1485;
                                                                    } else {
                                                                        Bool _t1584; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_DotDot()); _t1584 = *_hp; free(_hp); }
                                                                        (void)_t1584;
                                                                        if (_t1584) {
                                                                            Str *_t1486 = Str_lit("..", 2ULL);
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
                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                            ;
                                                                            return _t1486;
                                                                        } else {
                                                                            Bool _t1583; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Eq()); _t1583 = *_hp; free(_hp); }
                                                                            (void)_t1583;
                                                                            if (_t1583) {
                                                                                Str *_t1487 = Str_lit("=", 1ULL);
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
                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                ;
                                                                                return _t1487;
                                                                            } else {
                                                                                Bool _t1582; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_EqEq()); _t1582 = *_hp; free(_hp); }
                                                                                (void)_t1582;
                                                                                if (_t1582) {
                                                                                    Str *_t1488 = Str_lit("==", 2ULL);
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
                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                    ;
                                                                                    return _t1488;
                                                                                } else {
                                                                                    Bool _t1581; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Neq()); _t1581 = *_hp; free(_hp); }
                                                                                    (void)_t1581;
                                                                                    if (_t1581) {
                                                                                        Str *_t1489 = Str_lit("!=", 2ULL);
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
                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                        ;
                                                                                        return _t1489;
                                                                                    } else {
                                                                                        Bool _t1580; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Lt()); _t1580 = *_hp; free(_hp); }
                                                                                        (void)_t1580;
                                                                                        if (_t1580) {
                                                                                            Str *_t1490 = Str_lit("<", 1ULL);
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
                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                            ;
                                                                                            return _t1490;
                                                                                        } else {
                                                                                            Bool _t1579; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_LtEq()); _t1579 = *_hp; free(_hp); }
                                                                                            (void)_t1579;
                                                                                            if (_t1579) {
                                                                                                Str *_t1491 = Str_lit("<=", 2ULL);
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
                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                ;
                                                                                                return _t1491;
                                                                                            } else {
                                                                                                Bool _t1578; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Gt()); _t1578 = *_hp; free(_hp); }
                                                                                                (void)_t1578;
                                                                                                if (_t1578) {
                                                                                                    Str *_t1492 = Str_lit(">", 1ULL);
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
                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1492;
                                                                                                } else {
                                                                                                    Bool _t1577; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_GtEq()); _t1577 = *_hp; free(_hp); }
                                                                                                    (void)_t1577;
                                                                                                    if (_t1577) {
                                                                                                        Str *_t1493 = Str_lit(">=", 2ULL);
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
                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1493;
                                                                                                    } else {
                                                                                                        Bool _t1576; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_ColonEq()); _t1576 = *_hp; free(_hp); }
                                                                                                        (void)_t1576;
                                                                                                        if (_t1576) {
                                                                                                            Str *_t1494 = Str_lit(":=", 2ULL);
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
                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1494;
                                                                                                        } else {
                                                                                                            Bool _t1575; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Ident()); _t1575 = *_hp; free(_hp); }
                                                                                                            (void)_t1575;
                                                                                                            if (_t1575) {
                                                                                                                Str *_t1495 = Str_lit("identifier", 10ULL);
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
                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1495;
                                                                                                            } else {
                                                                                                                Bool _t1574; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_StringTok()); _t1574 = *_hp; free(_hp); }
                                                                                                                (void)_t1574;
                                                                                                                if (_t1574) {
                                                                                                                    Str *_t1496 = Str_lit("string", 6ULL);
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
                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1496;
                                                                                                                } else {
                                                                                                                    Bool _t1573; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Number()); _t1573 = *_hp; free(_hp); }
                                                                                                                    (void)_t1573;
                                                                                                                    if (_t1573) {
                                                                                                                        Str *_t1497 = Str_lit("number", 6ULL);
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
                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1497;
                                                                                                                    } else {
                                                                                                                        Bool _t1572; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Char()); _t1572 = *_hp; free(_hp); }
                                                                                                                        (void)_t1572;
                                                                                                                        if (_t1572) {
                                                                                                                            Str *_t1498 = Str_lit("char", 4ULL);
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
                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1498;
                                                                                                                        } else {
                                                                                                                            Bool _t1571; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwMode()); _t1571 = *_hp; free(_hp); }
                                                                                                                            (void)_t1571;
                                                                                                                            if (_t1571) {
                                                                                                                                Str *_t1499 = Str_lit("mode", 4ULL);
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
                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1499;
                                                                                                                            } else {
                                                                                                                                Bool _t1570; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwMut()); _t1570 = *_hp; free(_hp); }
                                                                                                                                (void)_t1570;
                                                                                                                                if (_t1570) {
                                                                                                                                    Str *_t1500 = Str_lit("mut", 3ULL);
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
                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1500;
                                                                                                                                } else {
                                                                                                                                    Bool _t1569; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwOwn()); _t1569 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1569;
                                                                                                                                    if (_t1569) {
                                                                                                                                        Str *_t1501 = Str_lit("own", 3ULL);
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
                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1501;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1568; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwRef()); _t1568 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1568;
                                                                                                                                        if (_t1568) {
                                                                                                                                            Str *_t1502 = Str_lit("ref", 3ULL);
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
                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1502;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1567; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwShallow()); _t1567 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1567;
                                                                                                                                            if (_t1567) {
                                                                                                                                                Str *_t1503 = Str_lit("shallow", 7ULL);
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
                                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1503;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1566; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwStruct()); _t1566 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1566;
                                                                                                                                                if (_t1566) {
                                                                                                                                                    Str *_t1504 = Str_lit("struct", 6ULL);
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
                                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1504;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1565; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwExtStruct()); _t1565 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t1565;
                                                                                                                                                    if (_t1565) {
                                                                                                                                                        Str *_t1505 = Str_lit("ext_struct", 10ULL);
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
                                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1505;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1564; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwEnum()); _t1564 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t1564;
                                                                                                                                                        if (_t1564) {
                                                                                                                                                            Str *_t1506 = Str_lit("enum", 4ULL);
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
                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1506;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1563; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwNamespace()); _t1563 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t1563;
                                                                                                                                                            if (_t1563) {
                                                                                                                                                                Str *_t1507 = Str_lit("namespace", 9ULL);
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
                                                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1507;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1562; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwFunc()); _t1562 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t1562;
                                                                                                                                                                if (_t1562) {
                                                                                                                                                                    Str *_t1508 = Str_lit("func", 4ULL);
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
                                                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1508;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1561; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwProc()); _t1561 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t1561;
                                                                                                                                                                    if (_t1561) {
                                                                                                                                                                        Str *_t1509 = Str_lit("proc", 4ULL);
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
                                                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1509;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1560; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwTest()); _t1560 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t1560;
                                                                                                                                                                        if (_t1560) {
                                                                                                                                                                            Str *_t1510 = Str_lit("test", 4ULL);
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
                                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1510;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1559; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwMacro()); _t1559 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t1559;
                                                                                                                                                                            if (_t1559) {
                                                                                                                                                                                Str *_t1511 = Str_lit("macro", 5ULL);
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
                                                                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1511;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1558; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwExtFunc()); _t1558 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t1558;
                                                                                                                                                                                if (_t1558) {
                                                                                                                                                                                    Str *_t1512 = Str_lit("ext_func", 8ULL);
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
                                                                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1512;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1557; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwExtProc()); _t1557 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t1557;
                                                                                                                                                                                    if (_t1557) {
                                                                                                                                                                                        Str *_t1513 = Str_lit("ext_proc", 8ULL);
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
                                                                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1513;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1556; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwReturns()); _t1556 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t1556;
                                                                                                                                                                                        if (_t1556) {
                                                                                                                                                                                            Str *_t1514 = Str_lit("returns", 7ULL);
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
                                                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1514;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1555; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwThrows()); _t1555 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t1555;
                                                                                                                                                                                            if (_t1555) {
                                                                                                                                                                                                Str *_t1515 = Str_lit("throws", 6ULL);
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
                                                                                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1515;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1554; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwIf()); _t1554 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t1554;
                                                                                                                                                                                                if (_t1554) {
                                                                                                                                                                                                    Str *_t1516 = Str_lit("if", 2ULL);
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
                                                                                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1516;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1553; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwElse()); _t1553 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t1553;
                                                                                                                                                                                                    if (_t1553) {
                                                                                                                                                                                                        Str *_t1517 = Str_lit("else", 4ULL);
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
                                                                                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1517;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1552; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwWhile()); _t1552 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t1552;
                                                                                                                                                                                                        if (_t1552) {
                                                                                                                                                                                                            Str *_t1518 = Str_lit("while", 5ULL);
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
                                                                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1518;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1551; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwFor()); _t1551 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t1551;
                                                                                                                                                                                                            if (_t1551) {
                                                                                                                                                                                                                Str *_t1519 = Str_lit("for", 3ULL);
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
                                                                                                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1519;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1550; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwIn()); _t1550 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t1550;
                                                                                                                                                                                                                if (_t1550) {
                                                                                                                                                                                                                    Str *_t1520 = Str_lit("in", 2ULL);
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
                                                                                                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1520;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1549; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwSwitch()); _t1549 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t1549;
                                                                                                                                                                                                                    if (_t1549) {
                                                                                                                                                                                                                        Str *_t1521 = Str_lit("switch", 6ULL);
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
                                                                                                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1521;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1548; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwMatch()); _t1548 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t1548;
                                                                                                                                                                                                                        if (_t1548) {
                                                                                                                                                                                                                            Str *_t1522 = Str_lit("match", 5ULL);
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
                                                                                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1522;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1547; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwCase()); _t1547 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t1547;
                                                                                                                                                                                                                            if (_t1547) {
                                                                                                                                                                                                                                Str *_t1523 = Str_lit("case", 4ULL);
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
                                                                                                                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1523;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1546; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwDefault()); _t1546 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t1546;
                                                                                                                                                                                                                                if (_t1546) {
                                                                                                                                                                                                                                    Str *_t1524 = Str_lit("default", 7ULL);
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
                                                                                                                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1524;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1545; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwReturn()); _t1545 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t1545;
                                                                                                                                                                                                                                    if (_t1545) {
                                                                                                                                                                                                                                        Str *_t1525 = Str_lit("return", 6ULL);
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
                                                                                                                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1525;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1544; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwThrow()); _t1544 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t1544;
                                                                                                                                                                                                                                        if (_t1544) {
                                                                                                                                                                                                                                            Str *_t1526 = Str_lit("throw", 5ULL);
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
                                                                                                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1526;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1543; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwCatch()); _t1543 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t1543;
                                                                                                                                                                                                                                            if (_t1543) {
                                                                                                                                                                                                                                                Str *_t1527 = Str_lit("catch", 5ULL);
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
                                                                                                                                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1527;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1542; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwBreak()); _t1542 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t1542;
                                                                                                                                                                                                                                                if (_t1542) {
                                                                                                                                                                                                                                                    Str *_t1528 = Str_lit("break", 5ULL);
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
                                                                                                                                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1528;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1541; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwContinue()); _t1541 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t1541;
                                                                                                                                                                                                                                                    if (_t1541) {
                                                                                                                                                                                                                                                        Str *_t1529 = Str_lit("continue", 8ULL);
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
                                                                                                                                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1529;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1540; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwDefer()); _t1540 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t1540;
                                                                                                                                                                                                                                                        if (_t1540) {
                                                                                                                                                                                                                                                            Str *_t1530 = Str_lit("defer", 5ULL);
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
                                                                                                                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1530;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1539; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwTrue()); _t1539 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t1539;
                                                                                                                                                                                                                                                            if (_t1539) {
                                                                                                                                                                                                                                                                Str *_t1531 = Str_lit("true", 4ULL);
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
                                                                                                                                                                                                                                                                TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1531;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1538; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwFalse()); _t1538 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t1538;
                                                                                                                                                                                                                                                                if (_t1538) {
                                                                                                                                                                                                                                                                    Str *_t1532 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                    (void)_t1532;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1532;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1537; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_KwNull()); _t1537 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t1537;
                                                                                                                                                                                                                                                                    if (_t1537) {
                                                                                                                                                                                                                                                                        Str *_t1533 = Str_lit("NULL", 4ULL);
                                                                                                                                                                                                                                                                        (void)_t1533;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1533;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1536; { Bool *_hp = (Bool *)TokenType_eq(_sw1469, TokenType_Error()); _t1536 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t1536;
                                                                                                                                                                                                                                                                        if (_t1536) {
                                                                                                                                                                                                                                                                            Str *_t1534 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                            (void)_t1534;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1534;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Str *_t1535 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                            (void)_t1535;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1469, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1535;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1469, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw1601 = Str_clone(word);
        (void)_sw1601;
        Str *_t1670 = Str_lit("mode", 4ULL);
        (void)_t1670;
        Bool _t1671; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1670); _t1671 = *_hp; free(_hp); }
        (void)_t1671;
        Str_delete(_t1670, &(Bool){1});
        if (_t1671) {
            Str_delete(_sw1601, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1668 = Str_lit("mut", 3ULL);
            (void)_t1668;
            Bool _t1669; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1668); _t1669 = *_hp; free(_hp); }
            (void)_t1669;
            Str_delete(_t1668, &(Bool){1});
            if (_t1669) {
                ;
                Str_delete(_sw1601, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1666 = Str_lit("own", 3ULL);
                (void)_t1666;
                Bool _t1667; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1666); _t1667 = *_hp; free(_hp); }
                (void)_t1667;
                Str_delete(_t1666, &(Bool){1});
                if (_t1667) {
                    ;
                    ;
                    Str_delete(_sw1601, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1664 = Str_lit("ref", 3ULL);
                    (void)_t1664;
                    Bool _t1665; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1664); _t1665 = *_hp; free(_hp); }
                    (void)_t1665;
                    Str_delete(_t1664, &(Bool){1});
                    if (_t1665) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1601, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1662 = Str_lit("shallow", 7ULL);
                        (void)_t1662;
                        Bool _t1663; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1662); _t1663 = *_hp; free(_hp); }
                        (void)_t1663;
                        Str_delete(_t1662, &(Bool){1});
                        if (_t1663) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1601, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1660 = Str_lit("struct", 6ULL);
                            (void)_t1660;
                            Bool _t1661; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1660); _t1661 = *_hp; free(_hp); }
                            (void)_t1661;
                            Str_delete(_t1660, &(Bool){1});
                            if (_t1661) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1601, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1658 = Str_lit("ext_struct", 10ULL);
                                (void)_t1658;
                                Bool _t1659; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1658); _t1659 = *_hp; free(_hp); }
                                (void)_t1659;
                                Str_delete(_t1658, &(Bool){1});
                                if (_t1659) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1601, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1656 = Str_lit("enum", 4ULL);
                                    (void)_t1656;
                                    Bool _t1657; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1656); _t1657 = *_hp; free(_hp); }
                                    (void)_t1657;
                                    Str_delete(_t1656, &(Bool){1});
                                    if (_t1657) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1601, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1654 = Str_lit("namespace", 9ULL);
                                        (void)_t1654;
                                        Bool _t1655; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1654); _t1655 = *_hp; free(_hp); }
                                        (void)_t1655;
                                        Str_delete(_t1654, &(Bool){1});
                                        if (_t1655) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1601, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1652 = Str_lit("func", 4ULL);
                                            (void)_t1652;
                                            Bool _t1653; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1652); _t1653 = *_hp; free(_hp); }
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
                                                ;
                                                ;
                                                Str_delete(_sw1601, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1650 = Str_lit("proc", 4ULL);
                                                (void)_t1650;
                                                Bool _t1651; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1650); _t1651 = *_hp; free(_hp); }
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
                                                    ;
                                                    ;
                                                    Str_delete(_sw1601, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1648 = Str_lit("test", 4ULL);
                                                    (void)_t1648;
                                                    Bool _t1649; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1648); _t1649 = *_hp; free(_hp); }
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
                                                        ;
                                                        ;
                                                        Str_delete(_sw1601, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1646 = Str_lit("macro", 5ULL);
                                                        (void)_t1646;
                                                        Bool _t1647; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1646); _t1647 = *_hp; free(_hp); }
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
                                                            ;
                                                            ;
                                                            Str_delete(_sw1601, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1644 = Str_lit("ext_func", 8ULL);
                                                            (void)_t1644;
                                                            Bool _t1645; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1644); _t1645 = *_hp; free(_hp); }
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
                                                                ;
                                                                ;
                                                                Str_delete(_sw1601, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1642 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t1642;
                                                                Bool _t1643; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1642); _t1643 = *_hp; free(_hp); }
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
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1601, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1640 = Str_lit("returns", 7ULL);
                                                                    (void)_t1640;
                                                                    Bool _t1641; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1640); _t1641 = *_hp; free(_hp); }
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
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1601, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1638 = Str_lit("throws", 6ULL);
                                                                        (void)_t1638;
                                                                        Bool _t1639; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1638); _t1639 = *_hp; free(_hp); }
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
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1601, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1636 = Str_lit("if", 2ULL);
                                                                            (void)_t1636;
                                                                            Bool _t1637; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1636); _t1637 = *_hp; free(_hp); }
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
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1601, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1634 = Str_lit("else", 4ULL);
                                                                                (void)_t1634;
                                                                                Bool _t1635; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1634); _t1635 = *_hp; free(_hp); }
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
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1601, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1632 = Str_lit("while", 5ULL);
                                                                                    (void)_t1632;
                                                                                    Bool _t1633; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1632); _t1633 = *_hp; free(_hp); }
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
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1601, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1630 = Str_lit("for", 3ULL);
                                                                                        (void)_t1630;
                                                                                        Bool _t1631; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1630); _t1631 = *_hp; free(_hp); }
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
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1601, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1628 = Str_lit("in", 2ULL);
                                                                                            (void)_t1628;
                                                                                            Bool _t1629; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1628); _t1629 = *_hp; free(_hp); }
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
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1601, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1626 = Str_lit("switch", 6ULL);
                                                                                                (void)_t1626;
                                                                                                Bool _t1627; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1626); _t1627 = *_hp; free(_hp); }
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1601, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1624 = Str_lit("match", 5ULL);
                                                                                                    (void)_t1624;
                                                                                                    Bool _t1625; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1624); _t1625 = *_hp; free(_hp); }
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1601, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1622 = Str_lit("case", 4ULL);
                                                                                                        (void)_t1622;
                                                                                                        Bool _t1623; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1622); _t1623 = *_hp; free(_hp); }
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1601, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1620 = Str_lit("default", 7ULL);
                                                                                                            (void)_t1620;
                                                                                                            Bool _t1621; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1620); _t1621 = *_hp; free(_hp); }
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
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1601, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1618 = Str_lit("return", 6ULL);
                                                                                                                (void)_t1618;
                                                                                                                Bool _t1619; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1618); _t1619 = *_hp; free(_hp); }
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
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1601, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1616 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t1616;
                                                                                                                    Bool _t1617; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1616); _t1617 = *_hp; free(_hp); }
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1601, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1614 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t1614;
                                                                                                                        Bool _t1615; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1614); _t1615 = *_hp; free(_hp); }
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1601, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1612 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t1612;
                                                                                                                            Bool _t1613; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1612); _t1613 = *_hp; free(_hp); }
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1601, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1610 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t1610;
                                                                                                                                Bool _t1611; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1610); _t1611 = *_hp; free(_hp); }
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1601, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1608 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t1608;
                                                                                                                                    Bool _t1609; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1608); _t1609 = *_hp; free(_hp); }
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1601, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1606 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t1606;
                                                                                                                                        Bool _t1607; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1606); _t1607 = *_hp; free(_hp); }
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1601, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1604 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t1604;
                                                                                                                                            Bool _t1605; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1604); _t1605 = *_hp; free(_hp); }
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
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1601, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1602 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t1602;
                                                                                                                                                Bool _t1603; { Bool *_hp = (Bool *)Str_eq(_sw1601, _t1602); _t1603 = *_hp; free(_hp); }
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
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1601, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw1601, &(Bool){1});
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
        Str_delete(_sw1601, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2008 = Str_lit("Token", 5ULL);
    (void)_t2008;
    U64 _t2009; { U64 *_hp = (U64 *)Token_size(); _t2009 = *_hp; free(_hp); }
    (void)_t2009;
    Vec *tokens = Vec_new(_t2008, &(U64){_t2009});
    (void)tokens;
    Str_delete(_t2008, &(Bool){1});
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
        Bool _wcond1672; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1672 = *_hp; free(_hp); }
        (void)_wcond1672;
        if (_wcond1672) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t1954 = 32;
        (void)_t1954;
        U8 _t1955 = 9;
        (void)_t1955;
        Bool _t1956 = U8_eq(DEREF(c), _t1954);
        (void)_t1956;
        ;
        Bool _t1957 = U8_eq(DEREF(c), _t1955);
        (void)_t1957;
        ;
        U8 _t1958 = 13;
        (void)_t1958;
        Bool _t1959 = Bool_or(_t1956, _t1957);
        (void)_t1959;
        ;
        ;
        Bool _t1960 = U8_eq(DEREF(c), _t1958);
        (void)_t1960;
        ;
        U8 _t1961 = 59;
        (void)_t1961;
        Bool _t1962 = Bool_or(_t1959, _t1960);
        (void)_t1962;
        ;
        ;
        Bool _t1963 = U8_eq(DEREF(c), _t1961);
        (void)_t1963;
        ;
        Bool _t1964 = Bool_or(_t1962, _t1963);
        (void)_t1964;
        ;
        ;
        if (_t1964) {
            U64 _t1673 = U64_inc(DEREF(pos));
            (void)_t1673;
            *pos = _t1673;
            ;
            ;
            continue;
        }
        ;
        U8 _t1965 = 10;
        (void)_t1965;
        Bool _t1966 = U8_eq(DEREF(c), _t1965);
        (void)_t1966;
        ;
        if (_t1966) {
            U64 _t1674 = U64_inc(DEREF(pos));
            (void)_t1674;
            *pos = _t1674;
            ;
            I64 _t1675 = 1;
            (void)_t1675;
            I64 _t1676 = I64_add(line, _t1675);
            (void)_t1676;
            ;
            line = _t1676;
            ;
            U64 _t1677 = U64_clone(pos);
            (void)_t1677;
            line_start = _t1677;
            ;
            ;
            continue;
        }
        ;
        U64 _t1967 = U64_sub(DEREF(pos), line_start);
        (void)_t1967;
        U64 _t1968 = 1;
        (void)_t1968;
        U64 _t1969 = U64_add(_t1967, _t1968);
        (void)_t1969;
        ;
        ;
        I64 col = U64_to_i64(_t1969);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t1970 = 35;
        (void)_t1970;
        Bool _t1971 = U8_eq(DEREF(c), _t1970);
        (void)_t1971;
        ;
        if (_t1971) {
            while (1) {
                Bool _wcond1678; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1678 = *_hp; free(_hp); }
                (void)_wcond1678;
                if (_wcond1678) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1679 = Str_byte_at(src, pos);
                (void)_t1679;
                U8 _t1680 = 10;
                (void)_t1680;
                Bool _t1681 = U8_eq(DEREF(_t1679), _t1680);
                (void)_t1681;
                ;
                if (_t1681) {
                    ;
                    break;
                }
                ;
                U64 _t1682 = U64_inc(DEREF(pos));
                (void)_t1682;
                *pos = _t1682;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1972 = 47;
        (void)_t1972;
        U64 _t1973 = 1;
        (void)_t1973;
        U64 _t1974 = U64_add(DEREF(pos), _t1973);
        (void)_t1974;
        ;
        Bool _t1975 = U8_eq(DEREF(c), _t1972);
        (void)_t1975;
        ;
        Bool _t1976; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1974}, &(U64){src_len}); _t1976 = *_hp; free(_hp); }
        (void)_t1976;
        ;
        Bool _t1977 = Bool_and(_t1975, _t1976);
        (void)_t1977;
        ;
        ;
        if (_t1977) {
            U64 _t1741 = 1;
            (void)_t1741;
            U64 *_t1742 = malloc(sizeof(U64)); *_t1742 = U64_add(DEREF(pos), _t1741);
            (void)_t1742;
            ;
            U8 *c2 = Str_byte_at(src, _t1742);
            (void)c2;
            U8 _t1743 = 47;
            (void)_t1743;
            Bool _t1744 = U8_eq(DEREF(c2), _t1743);
            (void)_t1744;
            ;
            if (_t1744) {
                while (1) {
                    Bool _wcond1683; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1683 = *_hp; free(_hp); }
                    (void)_wcond1683;
                    if (_wcond1683) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1684 = Str_byte_at(src, pos);
                    (void)_t1684;
                    U8 _t1685 = 10;
                    (void)_t1685;
                    Bool _t1686 = U8_eq(DEREF(_t1684), _t1685);
                    (void)_t1686;
                    ;
                    if (_t1686) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1687 = U64_inc(DEREF(pos));
                    (void)_t1687;
                    *pos = _t1687;
                    ;
                }
                U64_delete(_t1742, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1745 = 42;
            (void)_t1745;
            Bool _t1746 = U8_eq(DEREF(c2), _t1745);
            (void)_t1746;
            U64_delete(_t1742, &(Bool){1});
            ;
            if (_t1746) {
                U64 _t1737 = 2;
                (void)_t1737;
                U64 _t1738 = U64_add(DEREF(pos), _t1737);
                (void)_t1738;
                ;
                *pos = _t1738;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond1688; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1688 = *_hp; free(_hp); }
                    (void)_wcond1688;
                    if (_wcond1688) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1713 = 0;
                    (void)_t1713;
                    Bool _t1714; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t1713}); _t1714 = *_hp; free(_hp); }
                    (void)_t1714;
                    ;
                    if (_t1714) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1715 = 1;
                    (void)_t1715;
                    U64 _t1716 = U64_add(DEREF(pos), _t1715);
                    (void)_t1716;
                    ;
                    Bool _t1717; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1716}, &(U64){src_len}); _t1717 = *_hp; free(_hp); }
                    (void)_t1717;
                    ;
                    if (_t1717) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t1697 = 1;
                        (void)_t1697;
                        U64 *_t1698 = malloc(sizeof(U64)); *_t1698 = U64_add(DEREF(pos), _t1697);
                        (void)_t1698;
                        ;
                        U8 *b2 = Str_byte_at(src, _t1698);
                        (void)b2;
                        U8 _t1699 = 47;
                        (void)_t1699;
                        U8 _t1700 = 42;
                        (void)_t1700;
                        Bool _t1701 = U8_eq(DEREF(b1), _t1699);
                        (void)_t1701;
                        ;
                        Bool _t1702 = U8_eq(DEREF(b2), _t1700);
                        (void)_t1702;
                        ;
                        Bool _t1703 = Bool_and(_t1701, _t1702);
                        (void)_t1703;
                        ;
                        ;
                        if (_t1703) {
                            I64 _t1689 = 1;
                            (void)_t1689;
                            I64 _t1690 = I64_add(depth, _t1689);
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
                            U64_delete(_t1698, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1704 = 42;
                        (void)_t1704;
                        U8 _t1705 = 47;
                        (void)_t1705;
                        Bool _t1706 = U8_eq(DEREF(b1), _t1704);
                        (void)_t1706;
                        ;
                        Bool _t1707 = U8_eq(DEREF(b2), _t1705);
                        (void)_t1707;
                        U64_delete(_t1698, &(Bool){1});
                        ;
                        Bool _t1708 = Bool_and(_t1706, _t1707);
                        (void)_t1708;
                        ;
                        ;
                        if (_t1708) {
                            I64 _t1693 = 1;
                            (void)_t1693;
                            I64 _t1694 = I64_sub(depth, _t1693);
                            (void)_t1694;
                            ;
                            depth = _t1694;
                            ;
                            U64 _t1695 = 2;
                            (void)_t1695;
                            U64 _t1696 = U64_add(DEREF(pos), _t1695);
                            (void)_t1696;
                            ;
                            *pos = _t1696;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1718 = Str_byte_at(src, pos);
                    (void)_t1718;
                    U8 _t1719 = 10;
                    (void)_t1719;
                    Bool _t1720 = U8_eq(DEREF(_t1718), _t1719);
                    (void)_t1720;
                    ;
                    if (_t1720) {
                        I64 _t1709 = 1;
                        (void)_t1709;
                        I64 _t1710 = I64_add(line, _t1709);
                        (void)_t1710;
                        ;
                        line = _t1710;
                        ;
                        U64 _t1711 = 1;
                        (void)_t1711;
                        U64 _t1712 = U64_add(DEREF(pos), _t1711);
                        (void)_t1712;
                        ;
                        line_start = _t1712;
                        ;
                    }
                    ;
                    U64 _t1721 = U64_inc(DEREF(pos));
                    (void)_t1721;
                    *pos = _t1721;
                    ;
                }
                I64 _t1739 = 0;
                (void)_t1739;
                Bool _t1740; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t1739}); _t1740 = *_hp; free(_hp); }
                (void)_t1740;
                ;
                ;
                if (_t1740) {
                    Str *_t1722 = Str_lit("Str", 3ULL);
                    (void)_t1722;
                    U64 _t1723; { U64 *_hp = (U64 *)Str_size(); _t1723 = *_hp; free(_hp); }
                    (void)_t1723;
                    U64 _t1724 = 6;
                    (void)_t1724;
                    Array *_va20 = Array_new(_t1722, &(U64){_t1723}, &(U64){_t1724});
                    (void)_va20;
                    Str_delete(_t1722, &(Bool){1});
                    ;
                    ;
                    U64 _t1725 = 0;
                    (void)_t1725;
                    Str *_t1726 = Str_clone(path);
                    (void)_t1726;
                    Array_set(_va20, &(U64){_t1725}, _t1726);
                    ;
                    U64 _t1727 = 1;
                    (void)_t1727;
                    Str *_t1728 = Str_lit(":", 1ULL);
                    (void)_t1728;
                    Array_set(_va20, &(U64){_t1727}, _t1728);
                    ;
                    U64 _t1729 = 2;
                    (void)_t1729;
                    Str *_t1730 = I64_to_str(&(I64){line});
                    (void)_t1730;
                    Array_set(_va20, &(U64){_t1729}, _t1730);
                    ;
                    U64 _t1731 = 3;
                    (void)_t1731;
                    Str *_t1732 = Str_lit(":", 1ULL);
                    (void)_t1732;
                    Array_set(_va20, &(U64){_t1731}, _t1732);
                    ;
                    U64 _t1733 = 4;
                    (void)_t1733;
                    Str *_t1734 = I64_to_str(&(I64){col});
                    (void)_t1734;
                    Array_set(_va20, &(U64){_t1733}, _t1734);
                    ;
                    U64 _t1735 = 5;
                    (void)_t1735;
                    Str *_t1736 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t1736;
                    Array_set(_va20, &(U64){_t1735}, _t1736);
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
        Bool _t1978; { Bool *_hp = (Bool *)is_digit(c); _t1978 = *_hp; free(_hp); }
        (void)_t1978;
        if (_t1978) {
            while (1) {
                Bool _wcond1747; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1747 = *_hp; free(_hp); }
                (void)_wcond1747;
                if (_wcond1747) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1748 = Str_byte_at(src, pos);
                (void)_t1748;
                Bool _t1749; { Bool *_hp = (Bool *)is_digit(_t1748); _t1749 = *_hp; free(_hp); }
                (void)_t1749;
                Bool _t1750 = Bool_not(_t1749);
                (void)_t1750;
                ;
                if (_t1750) {
                    ;
                    break;
                }
                ;
                U64 _t1751 = U64_inc(DEREF(pos));
                (void)_t1751;
                *pos = _t1751;
                ;
            }
            U64 _t1766 = 1;
            (void)_t1766;
            U64 _t1767 = U64_add(DEREF(pos), _t1766);
            (void)_t1767;
            ;
            Bool _t1768; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1767}, &(U64){src_len}); _t1768 = *_hp; free(_hp); }
            (void)_t1768;
            ;
            if (_t1768) {
                U8 *_t1758 = Str_byte_at(src, pos);
                (void)_t1758;
                U8 _t1759 = 46;
                (void)_t1759;
                U64 _t1760 = 1;
                (void)_t1760;
                U64 *_t1761 = malloc(sizeof(U64)); *_t1761 = U64_add(DEREF(pos), _t1760);
                (void)_t1761;
                ;
                U8 *_t1762 = Str_byte_at(src, _t1761);
                (void)_t1762;
                Bool _t1763 = U8_eq(DEREF(_t1758), _t1759);
                (void)_t1763;
                ;
                Bool _t1764; { Bool *_hp = (Bool *)is_digit(_t1762); _t1764 = *_hp; free(_hp); }
                (void)_t1764;
                U64_delete(_t1761, &(Bool){1});
                Bool _t1765 = Bool_and(_t1763, _t1764);
                (void)_t1765;
                ;
                ;
                if (_t1765) {
                    U64 _t1757 = U64_inc(DEREF(pos));
                    (void)_t1757;
                    *pos = _t1757;
                    ;
                    while (1) {
                        Bool _wcond1752; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1752 = *_hp; free(_hp); }
                        (void)_wcond1752;
                        if (_wcond1752) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1753 = Str_byte_at(src, pos);
                        (void)_t1753;
                        Bool _t1754; { Bool *_hp = (Bool *)is_digit(_t1753); _t1754 = *_hp; free(_hp); }
                        (void)_t1754;
                        Bool _t1755 = Bool_not(_t1754);
                        (void)_t1755;
                        ;
                        if (_t1755) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1756 = U64_inc(DEREF(pos));
                        (void)_t1756;
                        *pos = _t1756;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1769 = U64_sub(DEREF(pos), start);
            (void)_t1769;
            I64 _t1770 = I64_clone(&(I64){col});
            (void)_t1770;
            Token *_t1771 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1771->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1769}); _t1771->text = *_ca; free(_ca); }
            _t1771->line = I64_clone(&(I64){line});
            _t1771->col = _t1770;
            (void)_t1771;
            ;
            ;
            Vec_push(tokens, _t1771);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1979; { Bool *_hp = (Bool *)is_alpha(c); _t1979 = *_hp; free(_hp); }
        (void)_t1979;
        if (_t1979) {
            while (1) {
                Bool _wcond1772; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1772 = *_hp; free(_hp); }
                (void)_wcond1772;
                if (_wcond1772) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1773 = Str_byte_at(src, pos);
                (void)_t1773;
                Bool _t1774; { Bool *_hp = (Bool *)is_alnum(_t1773); _t1774 = *_hp; free(_hp); }
                (void)_t1774;
                Bool _t1775 = Bool_not(_t1774);
                (void)_t1775;
                ;
                if (_t1775) {
                    ;
                    break;
                }
                ;
                U64 _t1776 = U64_inc(DEREF(pos));
                (void)_t1776;
                *pos = _t1776;
                ;
            }
            U64 _t1777 = U64_sub(DEREF(pos), start);
            (void)_t1777;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1777});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            I64 _t1778 = I64_clone(&(I64){line});
            (void)_t1778;
            I64 _t1779 = I64_clone(&(I64){col});
            (void)_t1779;
            Token *_t1780 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1780->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1780->text = *_ca; free(_ca); }
            _t1780->line = _t1778;
            _t1780->col = _t1779;
            (void)_t1780;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1780);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1980 = 34;
        (void)_t1980;
        Bool _t1981 = U8_eq(DEREF(c), _t1980);
        (void)_t1981;
        ;
        if (_t1981) {
            U64 _t1827 = U64_inc(DEREF(pos));
            (void)_t1827;
            *pos = _t1827;
            ;
            while (1) {
                Bool _wcond1781; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1781 = *_hp; free(_hp); }
                (void)_wcond1781;
                if (_wcond1781) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1787 = Str_byte_at(src, pos);
                (void)_t1787;
                U8 _t1788 = 34;
                (void)_t1788;
                Bool _t1789 = U8_eq(DEREF(_t1787), _t1788);
                (void)_t1789;
                ;
                if (_t1789) {
                    ;
                    break;
                }
                ;
                U8 *_t1790 = Str_byte_at(src, pos);
                (void)_t1790;
                U8 _t1791 = 92;
                (void)_t1791;
                U64 _t1792 = 1;
                (void)_t1792;
                U64 _t1793 = U64_add(DEREF(pos), _t1792);
                (void)_t1793;
                ;
                Bool _t1794 = U8_eq(DEREF(_t1790), _t1791);
                (void)_t1794;
                ;
                Bool _t1795; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1793}, &(U64){src_len}); _t1795 = *_hp; free(_hp); }
                (void)_t1795;
                ;
                Bool _t1796 = Bool_and(_t1794, _t1795);
                (void)_t1796;
                ;
                ;
                if (_t1796) {
                    U64 _t1782 = U64_inc(DEREF(pos));
                    (void)_t1782;
                    *pos = _t1782;
                    ;
                }
                ;
                U8 *_t1797 = Str_byte_at(src, pos);
                (void)_t1797;
                U8 _t1798 = 10;
                (void)_t1798;
                Bool _t1799 = U8_eq(DEREF(_t1797), _t1798);
                (void)_t1799;
                ;
                if (_t1799) {
                    I64 _t1783 = 1;
                    (void)_t1783;
                    I64 _t1784 = I64_add(line, _t1783);
                    (void)_t1784;
                    ;
                    line = _t1784;
                    ;
                    U64 _t1785 = 1;
                    (void)_t1785;
                    U64 _t1786 = U64_add(DEREF(pos), _t1785);
                    (void)_t1786;
                    ;
                    line_start = _t1786;
                    ;
                }
                ;
                U64 _t1800 = U64_inc(DEREF(pos));
                (void)_t1800;
                *pos = _t1800;
                ;
            }
            U8 *_t1828 = Str_byte_at(src, pos);
            (void)_t1828;
            U8 _t1829 = 34;
            (void)_t1829;
            Bool _t1830; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1830 = *_hp; free(_hp); }
            (void)_t1830;
            Bool _t1831 = U8_eq(DEREF(_t1828), _t1829);
            (void)_t1831;
            ;
            Bool _t1832 = Bool_and(_t1830, _t1831);
            (void)_t1832;
            ;
            ;
            if (_t1832) {
                U64 _t1801 = U64_inc(DEREF(pos));
                (void)_t1801;
                *pos = _t1801;
                ;
                U64 _t1802 = 1;
                (void)_t1802;
                U64 _t1803 = U64_sub(DEREF(pos), start);
                (void)_t1803;
                U64 _t1804 = 2;
                (void)_t1804;
                U64 _t1805 = U64_add(start, _t1802);
                (void)_t1805;
                ;
                U64 _t1806 = U64_sub(_t1803, _t1804);
                (void)_t1806;
                ;
                ;
                I64 _t1807 = I64_clone(&(I64){col});
                (void)_t1807;
                Token *_t1808 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1808->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){_t1805}, &(U64){_t1806}); _t1808->text = *_ca; free(_ca); }
                _t1808->line = I64_clone(&(I64){line});
                _t1808->col = _t1807;
                (void)_t1808;
                ;
                ;
                ;
                Vec_push(tokens, _t1808);
            } else {
                Str *_t1809 = Str_lit("Str", 3ULL);
                (void)_t1809;
                U64 _t1810; { U64 *_hp = (U64 *)Str_size(); _t1810 = *_hp; free(_hp); }
                (void)_t1810;
                U64 _t1811 = 6;
                (void)_t1811;
                Array *_va21 = Array_new(_t1809, &(U64){_t1810}, &(U64){_t1811});
                (void)_va21;
                Str_delete(_t1809, &(Bool){1});
                ;
                ;
                U64 _t1812 = 0;
                (void)_t1812;
                Str *_t1813 = Str_clone(path);
                (void)_t1813;
                Array_set(_va21, &(U64){_t1812}, _t1813);
                ;
                U64 _t1814 = 1;
                (void)_t1814;
                Str *_t1815 = Str_lit(":", 1ULL);
                (void)_t1815;
                Array_set(_va21, &(U64){_t1814}, _t1815);
                ;
                U64 _t1816 = 2;
                (void)_t1816;
                Str *_t1817 = I64_to_str(&(I64){line});
                (void)_t1817;
                Array_set(_va21, &(U64){_t1816}, _t1817);
                ;
                U64 _t1818 = 3;
                (void)_t1818;
                Str *_t1819 = Str_lit(":", 1ULL);
                (void)_t1819;
                Array_set(_va21, &(U64){_t1818}, _t1819);
                ;
                U64 _t1820 = 4;
                (void)_t1820;
                Str *_t1821 = I64_to_str(&(I64){col});
                (void)_t1821;
                Array_set(_va21, &(U64){_t1820}, _t1821);
                ;
                U64 _t1822 = 5;
                (void)_t1822;
                Str *_t1823 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1823;
                Array_set(_va21, &(U64){_t1822}, _t1823);
                ;
                println(_va21);
                U64 _t1824 = U64_sub(DEREF(pos), start);
                (void)_t1824;
                I64 _t1825 = I64_clone(&(I64){col});
                (void)_t1825;
                Token *_t1826 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1826->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1824}); _t1826->text = *_ca; free(_ca); }
                _t1826->line = I64_clone(&(I64){line});
                _t1826->col = _t1825;
                (void)_t1826;
                ;
                ;
                Vec_push(tokens, _t1826);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1982 = 39;
        (void)_t1982;
        Bool _t1983 = U8_eq(DEREF(c), _t1982);
        (void)_t1983;
        ;
        if (_t1983) {
            U64 _t1856 = U64_inc(DEREF(pos));
            (void)_t1856;
            *pos = _t1856;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t1857 = Str_byte_at(src, pos);
            (void)_t1857;
            U8 _t1858 = 92;
            (void)_t1858;
            U64 _t1859 = 1;
            (void)_t1859;
            U64 _t1860 = U64_add(DEREF(pos), _t1859);
            (void)_t1860;
            ;
            Bool _t1861 = U8_eq(DEREF(_t1857), _t1858);
            (void)_t1861;
            ;
            Bool _t1862; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1860}, &(U64){src_len}); _t1862 = *_hp; free(_hp); }
            (void)_t1862;
            ;
            Bool _t1863; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1863 = *_hp; free(_hp); }
            (void)_t1863;
            Bool _t1864 = Bool_and(_t1861, _t1862);
            (void)_t1864;
            ;
            ;
            Bool _t1865 = Bool_and(_t1863, _t1864);
            (void)_t1865;
            ;
            ;
            if (_t1865) {
                U64 _t1833 = U64_inc(DEREF(pos));
                (void)_t1833;
                *pos = _t1833;
                ;
            }
            ;
            U64 _t1866 = U64_inc(DEREF(pos));
            (void)_t1866;
            *pos = _t1866;
            ;
            U8 *_t1867 = Str_byte_at(src, pos);
            (void)_t1867;
            U8 _t1868 = 39;
            (void)_t1868;
            Bool _t1869; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1869 = *_hp; free(_hp); }
            (void)_t1869;
            Bool _t1870 = U8_eq(DEREF(_t1867), _t1868);
            (void)_t1870;
            ;
            Bool _t1871 = Bool_and(_t1869, _t1870);
            (void)_t1871;
            ;
            ;
            if (_t1871) {
                U64 _t1834 = U64_sub(DEREF(pos), ch_start);
                (void)_t1834;
                I64 _t1835 = I64_clone(&(I64){col});
                (void)_t1835;
                Token *_t1836 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1836->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){ch_start}, &(U64){_t1834}); _t1836->text = *_ca; free(_ca); }
                _t1836->line = I64_clone(&(I64){line});
                _t1836->col = _t1835;
                (void)_t1836;
                ;
                ;
                Vec_push(tokens, _t1836);
                U64 _t1837 = U64_inc(DEREF(pos));
                (void)_t1837;
                *pos = _t1837;
                ;
            } else {
                Str *_t1838 = Str_lit("Str", 3ULL);
                (void)_t1838;
                U64 _t1839; { U64 *_hp = (U64 *)Str_size(); _t1839 = *_hp; free(_hp); }
                (void)_t1839;
                U64 _t1840 = 6;
                (void)_t1840;
                Array *_va22 = Array_new(_t1838, &(U64){_t1839}, &(U64){_t1840});
                (void)_va22;
                Str_delete(_t1838, &(Bool){1});
                ;
                ;
                U64 _t1841 = 0;
                (void)_t1841;
                Str *_t1842 = Str_clone(path);
                (void)_t1842;
                Array_set(_va22, &(U64){_t1841}, _t1842);
                ;
                U64 _t1843 = 1;
                (void)_t1843;
                Str *_t1844 = Str_lit(":", 1ULL);
                (void)_t1844;
                Array_set(_va22, &(U64){_t1843}, _t1844);
                ;
                U64 _t1845 = 2;
                (void)_t1845;
                Str *_t1846 = I64_to_str(&(I64){line});
                (void)_t1846;
                Array_set(_va22, &(U64){_t1845}, _t1846);
                ;
                U64 _t1847 = 3;
                (void)_t1847;
                Str *_t1848 = Str_lit(":", 1ULL);
                (void)_t1848;
                Array_set(_va22, &(U64){_t1847}, _t1848);
                ;
                U64 _t1849 = 4;
                (void)_t1849;
                Str *_t1850 = I64_to_str(&(I64){col});
                (void)_t1850;
                Array_set(_va22, &(U64){_t1849}, _t1850);
                ;
                U64 _t1851 = 5;
                (void)_t1851;
                Str *_t1852 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t1852;
                Array_set(_va22, &(U64){_t1851}, _t1852);
                ;
                println(_va22);
                U64 _t1853 = U64_sub(DEREF(pos), start);
                (void)_t1853;
                I64 _t1854 = I64_clone(&(I64){col});
                (void)_t1854;
                Token *_t1855 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1855->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1853}); _t1855->text = *_ca; free(_ca); }
                _t1855->line = I64_clone(&(I64){line});
                _t1855->col = _t1854;
                (void)_t1855;
                ;
                ;
                Vec_push(tokens, _t1855);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t1984 = 1;
        (void)_t1984;
        U64 _t1985 = U64_add(DEREF(pos), _t1984);
        (void)_t1985;
        ;
        Bool _t1986; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1985}, &(U64){src_len}); _t1986 = *_hp; free(_hp); }
        (void)_t1986;
        ;
        if (_t1986) {
            U64 _t1903 = 1;
            (void)_t1903;
            U64 *_t1904 = malloc(sizeof(U64)); *_t1904 = U64_add(DEREF(pos), _t1903);
            (void)_t1904;
            ;
            U8 *c2 = Str_byte_at(src, _t1904);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t1905 = 58;
            (void)_t1905;
            U8 _t1906 = 61;
            (void)_t1906;
            Bool _t1907 = U8_eq(DEREF(c), _t1905);
            (void)_t1907;
            ;
            Bool _t1908 = U8_eq(DEREF(c2), _t1906);
            (void)_t1908;
            ;
            Bool _t1909 = Bool_and(_t1907, _t1908);
            (void)_t1909;
            ;
            ;
            if (_t1909) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t1892 = 61;
                (void)_t1892;
                U8 _t1893 = 61;
                (void)_t1893;
                Bool _t1894 = U8_eq(DEREF(c), _t1892);
                (void)_t1894;
                ;
                Bool _t1895 = U8_eq(DEREF(c2), _t1893);
                (void)_t1895;
                ;
                Bool _t1896 = Bool_and(_t1894, _t1895);
                (void)_t1896;
                ;
                ;
                if (_t1896) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t1887 = 33;
                    (void)_t1887;
                    U8 _t1888 = 61;
                    (void)_t1888;
                    Bool _t1889 = U8_eq(DEREF(c), _t1887);
                    (void)_t1889;
                    ;
                    Bool _t1890 = U8_eq(DEREF(c2), _t1888);
                    (void)_t1890;
                    ;
                    Bool _t1891 = Bool_and(_t1889, _t1890);
                    (void)_t1891;
                    ;
                    ;
                    if (_t1891) {
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t1882 = 60;
                        (void)_t1882;
                        U8 _t1883 = 61;
                        (void)_t1883;
                        Bool _t1884 = U8_eq(DEREF(c), _t1882);
                        (void)_t1884;
                        ;
                        Bool _t1885 = U8_eq(DEREF(c2), _t1883);
                        (void)_t1885;
                        ;
                        Bool _t1886 = Bool_and(_t1884, _t1885);
                        (void)_t1886;
                        ;
                        ;
                        if (_t1886) {
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t1877 = 62;
                            (void)_t1877;
                            U8 _t1878 = 61;
                            (void)_t1878;
                            Bool _t1879 = U8_eq(DEREF(c), _t1877);
                            (void)_t1879;
                            ;
                            Bool _t1880 = U8_eq(DEREF(c2), _t1878);
                            (void)_t1880;
                            ;
                            Bool _t1881 = Bool_and(_t1879, _t1880);
                            (void)_t1881;
                            ;
                            ;
                            if (_t1881) {
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t1872 = 46;
                                (void)_t1872;
                                U8 _t1873 = 46;
                                (void)_t1873;
                                Bool _t1874 = U8_eq(DEREF(c), _t1872);
                                (void)_t1874;
                                ;
                                Bool _t1875 = U8_eq(DEREF(c2), _t1873);
                                (void)_t1875;
                                ;
                                Bool _t1876 = Bool_and(_t1874, _t1875);
                                (void)_t1876;
                                ;
                                ;
                                if (_t1876) {
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
            U64_delete(_t1904, &(Bool){1});
            ;
            Bool _t1910; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t1910 = *_hp; free(_hp); }
            (void)_t1910;
            Bool _t1911 = Bool_not(_t1910);
            (void)_t1911;
            ;
            if (_t1911) {
                U64 _t1897 = 2;
                (void)_t1897;
                I64 _t1898 = I64_clone(&(I64){line});
                (void)_t1898;
                I64 _t1899 = I64_clone(&(I64){col});
                (void)_t1899;
                Token *_t1900 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1900->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1897}); _t1900->text = *_ca; free(_ca); }
                _t1900->line = _t1898;
                _t1900->col = _t1899;
                (void)_t1900;
                ;
                ;
                ;
                Vec_push(tokens, _t1900);
                U64 _t1901 = 2;
                (void)_t1901;
                U64 _t1902 = U64_add(DEREF(pos), _t1901);
                (void)_t1902;
                ;
                *pos = _t1902;
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
            U8 _sw1912 = U8_clone(c);
            (void)_sw1912;
            U8 _t1947 = 40;
            (void)_t1947;
            Bool _t1948 = U8_eq(_sw1912, _t1947);
            (void)_t1948;
            ;
            if (_t1948) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1945 = 41;
                (void)_t1945;
                Bool _t1946 = U8_eq(_sw1912, _t1945);
                (void)_t1946;
                ;
                if (_t1946) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1943 = 123;
                    (void)_t1943;
                    Bool _t1944 = U8_eq(_sw1912, _t1943);
                    (void)_t1944;
                    ;
                    if (_t1944) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1941 = 125;
                        (void)_t1941;
                        Bool _t1942 = U8_eq(_sw1912, _t1941);
                        (void)_t1942;
                        ;
                        if (_t1942) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1939 = 91;
                            (void)_t1939;
                            Bool _t1940 = U8_eq(_sw1912, _t1939);
                            (void)_t1940;
                            ;
                            if (_t1940) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1937 = 93;
                                (void)_t1937;
                                Bool _t1938 = U8_eq(_sw1912, _t1937);
                                (void)_t1938;
                                ;
                                if (_t1938) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1935 = 44;
                                    (void)_t1935;
                                    Bool _t1936 = U8_eq(_sw1912, _t1935);
                                    (void)_t1936;
                                    ;
                                    if (_t1936) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1933 = 58;
                                        (void)_t1933;
                                        Bool _t1934 = U8_eq(_sw1912, _t1933);
                                        (void)_t1934;
                                        ;
                                        if (_t1934) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1931 = 46;
                                            (void)_t1931;
                                            Bool _t1932 = U8_eq(_sw1912, _t1931);
                                            (void)_t1932;
                                            ;
                                            if (_t1932) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1929 = 63;
                                                (void)_t1929;
                                                Bool _t1930 = U8_eq(_sw1912, _t1929);
                                                (void)_t1930;
                                                ;
                                                if (_t1930) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1927 = 33;
                                                    (void)_t1927;
                                                    Bool _t1928 = U8_eq(_sw1912, _t1927);
                                                    (void)_t1928;
                                                    ;
                                                    if (_t1928) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1925 = 43;
                                                        (void)_t1925;
                                                        Bool _t1926 = U8_eq(_sw1912, _t1925);
                                                        (void)_t1926;
                                                        ;
                                                        if (_t1926) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1923 = 45;
                                                            (void)_t1923;
                                                            Bool _t1924 = U8_eq(_sw1912, _t1923);
                                                            (void)_t1924;
                                                            ;
                                                            if (_t1924) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1921 = 42;
                                                                (void)_t1921;
                                                                Bool _t1922 = U8_eq(_sw1912, _t1921);
                                                                (void)_t1922;
                                                                ;
                                                                if (_t1922) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1919 = 47;
                                                                    (void)_t1919;
                                                                    Bool _t1920 = U8_eq(_sw1912, _t1919);
                                                                    (void)_t1920;
                                                                    ;
                                                                    if (_t1920) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1917 = 61;
                                                                        (void)_t1917;
                                                                        Bool _t1918 = U8_eq(_sw1912, _t1917);
                                                                        (void)_t1918;
                                                                        ;
                                                                        if (_t1918) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1915 = 60;
                                                                            (void)_t1915;
                                                                            Bool _t1916 = U8_eq(_sw1912, _t1915);
                                                                            (void)_t1916;
                                                                            ;
                                                                            if (_t1916) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1913 = 62;
                                                                                (void)_t1913;
                                                                                Bool _t1914 = U8_eq(_sw1912, _t1913);
                                                                                (void)_t1914;
                                                                                ;
                                                                                if (_t1914) {
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
        Bool _t1987; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t1987 = *_hp; free(_hp); }
        (void)_t1987;
        Bool _t1988 = Bool_not(_t1987);
        (void)_t1988;
        ;
        if (_t1988) {
            U64 _t1949 = 1;
            (void)_t1949;
            I64 _t1950 = I64_clone(&(I64){line});
            (void)_t1950;
            I64 _t1951 = I64_clone(&(I64){col});
            (void)_t1951;
            Token *_t1952 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1952->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1949}); _t1952->text = *_ca; free(_ca); }
            _t1952->line = _t1950;
            _t1952->col = _t1951;
            (void)_t1952;
            ;
            ;
            ;
            Vec_push(tokens, _t1952);
            U64 _t1953 = U64_inc(DEREF(pos));
            (void)_t1953;
            *pos = _t1953;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t1989 = Str_lit("Str", 3ULL);
        (void)_t1989;
        U64 _t1990; { U64 *_hp = (U64 *)Str_size(); _t1990 = *_hp; free(_hp); }
        (void)_t1990;
        U64 _t1991 = 6;
        (void)_t1991;
        Array *_va23 = Array_new(_t1989, &(U64){_t1990}, &(U64){_t1991});
        (void)_va23;
        Str_delete(_t1989, &(Bool){1});
        ;
        ;
        U64 _t1992 = 0;
        (void)_t1992;
        Str *_t1993 = Str_clone(path);
        (void)_t1993;
        Array_set(_va23, &(U64){_t1992}, _t1993);
        ;
        U64 _t1994 = 1;
        (void)_t1994;
        Str *_t1995 = Str_lit(":", 1ULL);
        (void)_t1995;
        Array_set(_va23, &(U64){_t1994}, _t1995);
        ;
        U64 _t1996 = 2;
        (void)_t1996;
        Str *_t1997 = I64_to_str(&(I64){line});
        (void)_t1997;
        Array_set(_va23, &(U64){_t1996}, _t1997);
        ;
        U64 _t1998 = 3;
        (void)_t1998;
        Str *_t1999 = Str_lit(":", 1ULL);
        (void)_t1999;
        Array_set(_va23, &(U64){_t1998}, _t1999);
        ;
        U64 _t2000 = 4;
        (void)_t2000;
        Str *_t2001 = I64_to_str(&(I64){col});
        (void)_t2001;
        Array_set(_va23, &(U64){_t2000}, _t2001);
        ;
        U64 _t2002 = 5;
        (void)_t2002;
        Str *_t2003 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2003;
        Array_set(_va23, &(U64){_t2002}, _t2003);
        ;
        println(_va23);
        U64 _t2004 = 1;
        (void)_t2004;
        I64 _t2005 = I64_clone(&(I64){col});
        (void)_t2005;
        ;
        Token *_t2006 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2006->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2004}); _t2006->text = *_ca; free(_ca); }
        _t2006->line = I64_clone(&(I64){line});
        _t2006->col = _t2005;
        (void)_t2006;
        ;
        ;
        ;
        Vec_push(tokens, _t2006);
        U64 _t2007 = U64_inc(DEREF(pos));
        (void)_t2007;
        *pos = _t2007;
        ;
    }
    ;
    U64 _t2010 = U64_sub(DEREF(pos), line_start);
    (void)_t2010;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2011 = 1;
    (void)_t2011;
    U64 _t2012 = U64_add(_t2010, _t2011);
    (void)_t2012;
    ;
    ;
    I64 col = U64_to_i64(_t2012);
    (void)col;
    ;
    I64 _t2013 = I64_clone(&(I64){col});
    (void)_t2013;
    ;
    Token *_t2014 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2014->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2014->text = *_ca; free(_ca); }
    _t2014->line = I64_clone(&(I64){line});
    _t2014->col = _t2013;
    (void)_t2014;
    ;
    ;
    Vec_push(tokens, _t2014);
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
    (void)type_name; (void)val;
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
    _t2015 = malloc(sizeof(I64));
    *_t2015 = 0;
    (void)_t2015;
    _t2016 = malloc(sizeof(I64));
    *_t2016 = 1;
    (void)_t2016;
    _t2017 = malloc(sizeof(I64)); *_t2017 = I64_sub(DEREF(_t2015), DEREF(_t2016));
    (void)_t2017;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2017));
    (void)CAP_LIT;
    _t2018 = malloc(sizeof(I64));
    *_t2018 = 0;
    (void)_t2018;
    _t2019 = malloc(sizeof(I64));
    *_t2019 = 2;
    (void)_t2019;
    _t2020 = malloc(sizeof(I64)); *_t2020 = I64_sub(DEREF(_t2018), DEREF(_t2019));
    (void)_t2020;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2020));
    (void)CAP_VIEW;
}

