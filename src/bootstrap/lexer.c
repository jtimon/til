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
void swap(void * a, void * b, U64 size);
void move(void * dest, void * src, U64 size);
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

static I64 *_t2016;
static I64 *_t2017;
static I64 *_t2018;
static U64 *CAP_LIT;
static I64 *_t2019;
static I64 *_t2020;
static I64 *_t2021;
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
        I32 _t136 = 0;
        (void)_t136;
        U64 _t137 = 1;
        (void)_t137;
        memset(_t135, _t136, _t137);
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
    I32 _t175 = 0;
    (void)_t175;
    U64 _t176 = 1;
    (void)_t176;
    memset(_t174, _t175, _t176);
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

void swap(void * a, void * b, U64 size) {
    (void)a;
    (void)b;
    (void)size;
    U8 *tmp = malloc(size);
    (void)tmp;
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

void move(void * dest, void * src, U64 size) {
    (void)dest;
    (void)src;
    (void)size;
    memcpy(dest, src, size);
    I32 _t265 = 0;
    (void)_t265;
    memset(src, _t265, size);
    ;
}

I64 * wait_cmd(I64 * pid) {
    (void)pid;
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        (void)status;
        I64 _t266 = 0;
        (void)_t266;
        I64 _t267 = 1;
        (void)_t267;
        I64 _t268 = I64_sub(_t266, _t267);
        (void)_t268;
        ;
        ;
        Bool _t269; { Bool *_hp = (Bool *)I64_neq(&(I64){status}, &(I64){_t268}); _t269 = *_hp; free(_hp); }
        (void)_t269;
        ;
        if (_t269) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t270 = 50;
        (void)_t270;
        sleep_ms(_t270);
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
        U64 _t276; { U64 *_hp = (U64 *)Array_len(args); _t276 = *_hp; free(_hp); }
        (void)_t276;
        Bool _wcond271; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t276}); _wcond271 = *_hp; free(_hp); }
        (void)_wcond271;
        ;
        if (_wcond271) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        (void)arg;
        U64 _t277 = 0;
        (void)_t277;
        Bool _t278; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t277}); _t278 = *_hp; free(_hp); }
        (void)_t278;
        ;
        if (_t278) {
            Str *_t272 = Str_lit(" '", 2ULL);
            (void)_t272;
            Str *_t273 = Str_concat(cmd, _t272);
            (void)_t273;
            Str_delete(_t272, &(Bool){1});
            Str *_t274 = Str_concat(_t273, arg);
            (void)_t274;
            Str_delete(_t273, &(Bool){1});
            Str *_t275 = Str_lit("'", 1ULL);
            (void)_t275;
            cmd = Str_concat(_t274, _t275);
            Str_delete(_t274, &(Bool){1});
            Str_delete(_t275, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t279 = 1;
        (void)_t279;
        U64 _t280 = U64_add(DEREF(i), _t279);
        (void)_t280;
        ;
        *i = _t280;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    (void)tmpf;
    Str *_t281 = Str_lit(" > ", 3ULL);
    (void)_t281;
    Str *_t282 = Str_concat(cmd, _t281);
    (void)_t282;
    Str_delete(_t281, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t283 = Str_concat(_t282, tmpf);
    (void)_t283;
    Str_delete(_t282, &(Bool){1});
    Str *_t284 = Str_lit(" 2>&1", 5ULL);
    (void)_t284;
    Str *_t285 = Str_concat(_t283, _t284);
    (void)_t285;
    Str_delete(_t283, &(Bool){1});
    Str_delete(_t284, &(Bool){1});
    I64 pid; { I64 *_hp = (I64 *)spawn_cmd(_t285); pid = *_hp; free(_hp); }
    (void)pid;
    Str_delete(_t285, &(Bool){1});
    I64 ec; { I64 *_hp = (I64 *)wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    (void)ec;
    ;
    Str *content = readfile(tmpf);
    (void)content;
    Str_delete(tmpf, &(Bool){1});
    U64 _t286; { U64 *_hp = (U64 *)Str_size(); _t286 = *_hp; free(_hp); }
    (void)_t286;
    memcpy(output, content, _t286);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t287 = Str_lit("Str", 3ULL);
    (void)_t287;
    U64 _t288; { U64 *_hp = (U64 *)Str_size(); _t288 = *_hp; free(_hp); }
    (void)_t288;
    U64 _t289 = 3;
    (void)_t289;
    Array *_va0 = Array_new(_t287, &(U64){_t288}, &(U64){_t289});
    (void)_va0;
    Str_delete(_t287, &(Bool){1});
    ;
    ;
    U64 _t290 = 0;
    (void)_t290;
    Str *_t291 = Str_clone(loc_str);
    (void)_t291;
    Array_set(_va0, &(U64){_t290}, _t291);
    ;
    U64 _t292 = 1;
    (void)_t292;
    Str *_t293 = Str_lit(": panic: ", 9ULL);
    (void)_t293;
    Array_set(_va0, &(U64){_t292}, _t293);
    ;
    U64 _t294 = 2;
    (void)_t294;
    Str *_t295 = format(parts);
    (void)_t295;
    Array_set(_va0, &(U64){_t294}, _t295);
    ;
    println(_va0);
    I64 _t296 = 1;
    (void)_t296;
    exit(_t296);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t297 = Str_lit("Str", 3ULL);
    (void)_t297;
    U64 _t298; { U64 *_hp = (U64 *)Str_size(); _t298 = *_hp; free(_hp); }
    (void)_t298;
    U64 _t299 = 2;
    (void)_t299;
    Array *_va1 = Array_new(_t297, &(U64){_t298}, &(U64){_t299});
    (void)_va1;
    Str_delete(_t297, &(Bool){1});
    ;
    ;
    U64 _t300 = 0;
    (void)_t300;
    Str *_t301 = Str_lit("TODO: ", 6ULL);
    (void)_t301;
    Array_set(_va1, &(U64){_t300}, _t301);
    ;
    U64 _t302 = 1;
    (void)_t302;
    Str *_t303 = format(parts);
    (void)_t303;
    Array_set(_va1, &(U64){_t302}, _t303);
    ;
    panic(loc_str, _va1);
}

void UNREACHABLE(Str * loc_str) {
    (void)loc_str;
    Str *_t304 = Str_lit("Str", 3ULL);
    (void)_t304;
    U64 _t305; { U64 *_hp = (U64 *)Str_size(); _t305 = *_hp; free(_hp); }
    (void)_t305;
    U64 _t306 = 1;
    (void)_t306;
    Array *_va2 = Array_new(_t304, &(U64){_t305}, &(U64){_t306});
    (void)_va2;
    Str_delete(_t304, &(Bool){1});
    ;
    ;
    U64 _t307 = 0;
    (void)_t307;
    Str *_t308 = Str_lit("unreachable", 11ULL);
    (void)_t308;
    Array_set(_va2, &(U64){_t307}, _t308);
    ;
    panic(loc_str, _va2);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Bool _t316 = Bool_not(DEREF(cond));
    (void)_t316;
    if (_t316) {
        Str *_t309 = Str_lit("Str", 3ULL);
        (void)_t309;
        U64 _t310; { U64 *_hp = (U64 *)Str_size(); _t310 = *_hp; free(_hp); }
        (void)_t310;
        U64 _t311 = 2;
        (void)_t311;
        Array *_va3 = Array_new(_t309, &(U64){_t310}, &(U64){_t311});
        (void)_va3;
        Str_delete(_t309, &(Bool){1});
        ;
        ;
        U64 _t312 = 0;
        (void)_t312;
        Str *_t313 = Str_lit("assert failed: ", 15ULL);
        (void)_t313;
        Array_set(_va3, &(U64){_t312}, _t313);
        ;
        U64 _t314 = 1;
        (void)_t314;
        Str *_t315 = format(parts);
        (void)_t315;
        Array_set(_va3, &(U64){_t314}, _t315);
        ;
        panic(loc_str, _va3);
    }
    ;
    Bool _t317 = 1;
    (void)_t317;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t317; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Str *_t318 = Str_lit("Str", 3ULL);
    (void)_t318;
    U64 _t319; { U64 *_hp = (U64 *)Str_size(); _t319 = *_hp; free(_hp); }
    (void)_t319;
    U64 _t320 = 0;
    (void)_t320;
    Array *_va4 = Array_new(_t318, &(U64){_t319}, &(U64){_t320});
    (void)_va4;
    Str_delete(_t318, &(Bool){1});
    ;
    ;
    Bool _t321; { Bool *_hp = (Bool *)assertm(loc_str, cond, _va4); _t321 = *_hp; free(_hp); }
    (void)_t321;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t321; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    (void)loc_str;
    (void)cond;
    (void)parts;
    Array *_t322 = Array_clone(parts);
    (void)_t322;
    Array_delete(parts, &(Bool){1});
    Bool _t323; { Bool *_hp = (Bool *)assertm(loc_str, cond, _t322); _t323 = *_hp; free(_hp); }
    (void)_t323;
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t337; { Bool *_hp = (Bool *)I64_neq(a, b); _t337 = *_hp; free(_hp); }
    (void)_t337;
    if (_t337) {
        Str *_t324 = Str_lit("Str", 3ULL);
        (void)_t324;
        U64 _t325; { U64 *_hp = (U64 *)Str_size(); _t325 = *_hp; free(_hp); }
        (void)_t325;
        U64 _t326 = 5;
        (void)_t326;
        Array *_va5 = Array_new(_t324, &(U64){_t325}, &(U64){_t326});
        (void)_va5;
        Str_delete(_t324, &(Bool){1});
        ;
        ;
        U64 _t327 = 0;
        (void)_t327;
        Str *_t328 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t328;
        Array_set(_va5, &(U64){_t327}, _t328);
        ;
        U64 _t329 = 1;
        (void)_t329;
        Str *_t330 = I64_to_str(a);
        (void)_t330;
        Array_set(_va5, &(U64){_t329}, _t330);
        ;
        U64 _t331 = 2;
        (void)_t331;
        Str *_t332 = Str_lit("', found '", 10ULL);
        (void)_t332;
        Array_set(_va5, &(U64){_t331}, _t332);
        ;
        U64 _t333 = 3;
        (void)_t333;
        Str *_t334 = I64_to_str(b);
        (void)_t334;
        Array_set(_va5, &(U64){_t333}, _t334);
        ;
        U64 _t335 = 4;
        (void)_t335;
        Str *_t336 = Str_lit("'", 1ULL);
        (void)_t336;
        Array_set(_va5, &(U64){_t335}, _t336);
        ;
        panic(loc_str, _va5);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t351; { Bool *_hp = (Bool *)Str_eq(a, b); _t351 = *_hp; free(_hp); }
    (void)_t351;
    Bool _t352 = Bool_not(_t351);
    (void)_t352;
    ;
    if (_t352) {
        Str *_t338 = Str_lit("Str", 3ULL);
        (void)_t338;
        U64 _t339; { U64 *_hp = (U64 *)Str_size(); _t339 = *_hp; free(_hp); }
        (void)_t339;
        U64 _t340 = 5;
        (void)_t340;
        Array *_va6 = Array_new(_t338, &(U64){_t339}, &(U64){_t340});
        (void)_va6;
        Str_delete(_t338, &(Bool){1});
        ;
        ;
        U64 _t341 = 0;
        (void)_t341;
        Str *_t342 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t342;
        Array_set(_va6, &(U64){_t341}, _t342);
        ;
        U64 _t343 = 1;
        (void)_t343;
        Str *_t344 = Str_clone(a);
        (void)_t344;
        Array_set(_va6, &(U64){_t343}, _t344);
        ;
        U64 _t345 = 2;
        (void)_t345;
        Str *_t346 = Str_lit("', found '", 10ULL);
        (void)_t346;
        Array_set(_va6, &(U64){_t345}, _t346);
        ;
        U64 _t347 = 3;
        (void)_t347;
        Str *_t348 = Str_clone(b);
        (void)_t348;
        Array_set(_va6, &(U64){_t347}, _t348);
        ;
        U64 _t349 = 4;
        (void)_t349;
        Str *_t350 = Str_lit("'", 1ULL);
        (void)_t350;
        Array_set(_va6, &(U64){_t349}, _t350);
        ;
        panic(loc_str, _va6);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    void *_t353 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t353;
    U64 _t354 = U64_clone(cap);
    (void)_t354;
    U64 _t355 = U64_clone(elem_size);
    (void)_t355;
    Array *_t356 = malloc(sizeof(Array));
    _t356->data = _t353;
    _t356->cap = _t354;
    _t356->elem_size = _t355;
    { Str *_ca = Str_clone(elem_type); _t356->elem_type = *_ca; free(_ca); }
    (void)_t356;
    ;
    ;
    return _t356;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t371; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t371 = *_hp; free(_hp); }
    (void)_t371;
    if (_t371) {
        Str *_t357 = Str_lit("Str", 3ULL);
        (void)_t357;
        U64 _t358; { U64 *_hp = (U64 *)Str_size(); _t358 = *_hp; free(_hp); }
        (void)_t358;
        U64 _t359 = 5;
        (void)_t359;
        Array *_va7 = Array_new(_t357, &(U64){_t358}, &(U64){_t359});
        (void)_va7;
        Str_delete(_t357, &(Bool){1});
        ;
        ;
        U64 _t360 = 0;
        (void)_t360;
        Str *_t361 = Str_lit("Array.get: index ", 17ULL);
        (void)_t361;
        Array_set(_va7, &(U64){_t360}, _t361);
        ;
        U64 _t362 = 1;
        (void)_t362;
        Str *_t363 = U64_to_str(DEREF(i));
        (void)_t363;
        Array_set(_va7, &(U64){_t362}, _t363);
        ;
        U64 _t364 = 2;
        (void)_t364;
        Str *_t365 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t365;
        Array_set(_va7, &(U64){_t364}, _t365);
        ;
        U64 _t366 = 3;
        (void)_t366;
        Str *_t367 = U64_to_str(self->cap);
        (void)_t367;
        Array_set(_va7, &(U64){_t366}, _t367);
        ;
        U64 _t368 = 4;
        (void)_t368;
        Str *_t369 = Str_lit(")", 1ULL);
        (void)_t369;
        Array_set(_va7, &(U64){_t368}, _t369);
        ;
        Str *_t370 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:19:19", 62ULL);
        (void)_t370;
        panic(_t370, _va7);
        Str_delete(_t370, &(Bool){1});
    }
    ;
    U64 *_t372 = malloc(sizeof(U64)); *_t372 = U64_mul(DEREF(i), self->elem_size);
    (void)_t372;
    void *_t373 = ptr_add(self->data, DEREF(_t372));
    (void)_t373;
    U64_delete(_t372, &(Bool){1});
    return _t373;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t388; { Bool *_hp = (Bool *)U64_gte(i, &self->cap); _t388 = *_hp; free(_hp); }
    (void)_t388;
    if (_t388) {
        Str *_t374 = Str_lit("Str", 3ULL);
        (void)_t374;
        U64 _t375; { U64 *_hp = (U64 *)Str_size(); _t375 = *_hp; free(_hp); }
        (void)_t375;
        U64 _t376 = 5;
        (void)_t376;
        Array *_va8 = Array_new(_t374, &(U64){_t375}, &(U64){_t376});
        (void)_va8;
        Str_delete(_t374, &(Bool){1});
        ;
        ;
        U64 _t377 = 0;
        (void)_t377;
        Str *_t378 = Str_lit("Array.set: index ", 17ULL);
        (void)_t378;
        Array_set(_va8, &(U64){_t377}, _t378);
        ;
        U64 _t379 = 1;
        (void)_t379;
        Str *_t380 = U64_to_str(DEREF(i));
        (void)_t380;
        Array_set(_va8, &(U64){_t379}, _t380);
        ;
        U64 _t381 = 2;
        (void)_t381;
        Str *_t382 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t382;
        Array_set(_va8, &(U64){_t381}, _t382);
        ;
        U64 _t383 = 3;
        (void)_t383;
        Str *_t384 = U64_to_str(self->cap);
        (void)_t384;
        Array_set(_va8, &(U64){_t383}, _t384);
        ;
        U64 _t385 = 4;
        (void)_t385;
        Str *_t386 = Str_lit(")", 1ULL);
        (void)_t386;
        Array_set(_va8, &(U64){_t385}, _t386);
        ;
        Str *_t387 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/array.til:27:19", 62ULL);
        (void)_t387;
        panic(_t387, _va8);
        Str_delete(_t387, &(Bool){1});
    }
    ;
    U64 *_t389 = malloc(sizeof(U64)); *_t389 = U64_mul(DEREF(i), self->elem_size);
    (void)_t389;
    void *_t390 = ptr_add(self->data, DEREF(_t389));
    (void)_t390;
    Bool _t391 = 0;
    (void)_t391;
    dyn_call_delete(&self->elem_type, _t390, &(Bool){_t391});
    U64_delete(_t389, &(Bool){1});
    ;
    U64 *_t392 = malloc(sizeof(U64)); *_t392 = U64_mul(DEREF(i), self->elem_size);
    (void)_t392;
    void *_t393 = ptr_add(self->data, DEREF(_t392));
    (void)_t393;
    memcpy(_t393, val, self->elem_size);
    U64_delete(_t392, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U64 _fi394 = 0;
        (void)_fi394;
        while (1) {
            U64 _t396 = 0;
            (void)_t396;
            Range *_t397 = Range_new(_t396, self->cap);
            (void)_t397;
            ;
            U64 _t398; { U64 *_hp = (U64 *)Range_len(_t397); _t398 = *_hp; free(_hp); }
            (void)_t398;
            Range_delete(_t397, &(Bool){1});
            Bool _wcond395; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi394}, &(U64){_t398}); _wcond395 = *_hp; free(_hp); }
            (void)_wcond395;
            ;
            if (_wcond395) {
            } else {
                ;
                break;
            }
            ;
            U64 _t399 = 0;
            (void)_t399;
            Range *_t400 = Range_new(_t399, self->cap);
            (void)_t400;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t400, _fi394); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t400, &(Bool){1});
            U64 _t401 = 1;
            (void)_t401;
            U64 _t402 = U64_add(_fi394, _t401);
            (void)_t402;
            ;
            _fi394 = _t402;
            ;
            U64 *_t403 = malloc(sizeof(U64)); *_t403 = U64_mul(i, self->elem_size);
            (void)_t403;
            ;
            void *_t404 = ptr_add(self->data, DEREF(_t403));
            (void)_t404;
            Bool _t405 = 0;
            (void)_t405;
            dyn_call_delete(&self->elem_type, _t404, &(Bool){_t405});
            U64_delete(_t403, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t406 = 0;
    (void)_t406;
    Str_delete(&self->elem_type, &(Bool){_t406});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t420 = U64_mul(self->cap, self->elem_size);
    (void)_t420;
    U8 *new_data = malloc(_t420);
    (void)new_data;
    ;
    {
        U64 _fi407 = 0;
        (void)_fi407;
        while (1) {
            U64 _t409 = 0;
            (void)_t409;
            Range *_t410 = Range_new(_t409, self->cap);
            (void)_t410;
            ;
            U64 _t411; { U64 *_hp = (U64 *)Range_len(_t410); _t411 = *_hp; free(_hp); }
            (void)_t411;
            Range_delete(_t410, &(Bool){1});
            Bool _wcond408; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi407}, &(U64){_t411}); _wcond408 = *_hp; free(_hp); }
            (void)_wcond408;
            ;
            if (_wcond408) {
            } else {
                ;
                break;
            }
            ;
            U64 _t412 = 0;
            (void)_t412;
            Range *_t413 = Range_new(_t412, self->cap);
            (void)_t413;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t413, _fi407); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t413, &(Bool){1});
            U64 _t414 = 1;
            (void)_t414;
            U64 _t415 = U64_add(_fi407, _t414);
            (void)_t415;
            ;
            _fi407 = _t415;
            ;
            U64 *_t416 = malloc(sizeof(U64)); *_t416 = U64_mul(i, self->elem_size);
            (void)_t416;
            void *_t417 = ptr_add(self->data, DEREF(_t416));
            (void)_t417;
            void *cloned = dyn_call_clone(&self->elem_type, _t417);
            (void)cloned;
            U64_delete(_t416, &(Bool){1});
            U64 *_t418 = malloc(sizeof(U64)); *_t418 = U64_mul(i, self->elem_size);
            (void)_t418;
            ;
            void *_t419 = ptr_add(new_data, DEREF(_t418));
            (void)_t419;
            memcpy(_t419, cloned, self->elem_size);
            U64_delete(_t418, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Array *_t421 = malloc(sizeof(Array));
    _t421->data = new_data;
    _t421->cap = self->cap;
    _t421->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t421->elem_type = *_ca; free(_ca); }
    (void)_t421;
    return _t421;
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
    Bool _t435; { Bool *_hp = (Bool *)Str_is_empty(key_type); _t435 = *_hp; free(_hp); }
    (void)_t435;
    Bool _t436 = Bool_not(_t435);
    (void)_t436;
    ;
    if (_t436) {
        Bool _t433 = dyn_has_cmp(key_type);
        (void)_t433;
        Bool _t434 = Bool_not(_t433);
        (void)_t434;
        ;
        if (_t434) {
            Str *_t423 = Str_lit("Str", 3ULL);
            (void)_t423;
            U64 _t424; { U64 *_hp = (U64 *)Str_size(); _t424 = *_hp; free(_hp); }
            (void)_t424;
            U64 _t425 = 3;
            (void)_t425;
            Array *_va9 = Array_new(_t423, &(U64){_t424}, &(U64){_t425});
            (void)_va9;
            Str_delete(_t423, &(Bool){1});
            ;
            ;
            U64 _t426 = 0;
            (void)_t426;
            Str *_t427 = Str_lit("Map.new: type ", 14ULL);
            (void)_t427;
            Array_set(_va9, &(U64){_t426}, _t427);
            ;
            U64 _t428 = 1;
            (void)_t428;
            Str *_t429 = Str_clone(key_type);
            (void)_t429;
            Array_set(_va9, &(U64){_t428}, _t429);
            ;
            U64 _t430 = 2;
            (void)_t430;
            Str *_t431 = Str_lit(" must implement cmp", 19ULL);
            (void)_t431;
            Array_set(_va9, &(U64){_t430}, _t431);
            ;
            Str *_t432 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:17:23", 60ULL);
            (void)_t432;
            panic(_t432, _va9);
            Str_delete(_t432, &(Bool){1});
        }
        ;
    }
    ;
    void *_t437 = malloc(DEREF(key_size));
    (void)_t437;
    void *_t438 = malloc(DEREF(val_size));
    (void)_t438;
    U64 _t439 = 0;
    (void)_t439;
    I64 _t440 = 1;
    (void)_t440;
    U64 _t441 = U64_clone(key_size);
    (void)_t441;
    U64 _t442 = U64_clone(val_size);
    (void)_t442;
    Map *_t443 = malloc(sizeof(Map));
    _t443->key_data = _t437;
    _t443->val_data = _t438;
    _t443->count = _t439;
    _t443->cap = _t440;
    _t443->key_size = _t441;
    { Str *_ca = Str_clone(key_type); _t443->key_type = *_ca; free(_ca); }
    _t443->val_size = _t442;
    { Str *_ca = Str_clone(val_type); _t443->val_type = *_ca; free(_ca); }
    (void)_t443;
    ;
    ;
    ;
    ;
    return _t443;
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
        Bool _wcond444; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond444 = *_hp; free(_hp); }
        (void)_wcond444;
        if (_wcond444) {
        } else {
            ;
            break;
        }
        ;
        U64 _t451 = U64_sub(hi, lo);
        (void)_t451;
        U64 _t452 = 2;
        (void)_t452;
        U64 _t453 = U64_div(_t451, _t452);
        (void)_t453;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t453);
        (void)mid;
        ;
        U64 *_t454 = malloc(sizeof(U64)); *_t454 = U64_mul(DEREF(mid), self->key_size);
        (void)_t454;
        void *_t455 = ptr_add(self->key_data, DEREF(_t454));
        (void)_t455;
        I64 *c = dyn_call_cmp(&self->key_type, _t455, key);
        (void)c;
        U64_delete(_t454, &(Bool){1});
        I64 _t456 = 0;
        (void)_t456;
        Bool _t457; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t456}); _t457 = *_hp; free(_hp); }
        (void)_t457;
        ;
        if (_t457) {
            U64 _t445 = 1;
            (void)_t445;
            U64 _t446 = U64_add(DEREF(mid), _t445);
            (void)_t446;
            ;
            lo = _t446;
            ;
        } else {
            I64 _t449 = 0;
            (void)_t449;
            Bool _t450; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t449}); _t450 = *_hp; free(_hp); }
            (void)_t450;
            ;
            if (_t450) {
                U64 _t447 = U64_clone(mid);
                (void)_t447;
                hi = _t447;
                ;
            } else {
                Bool _t448 = 1;
                (void)_t448;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t448; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t458 = 0;
    (void)_t458;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t458; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    (void)key;
    U64 lo = 0;
    (void)lo;
    U64 hi = self->count;
    (void)hi;
    while (1) {
        Bool _wcond459; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond459 = *_hp; free(_hp); }
        (void)_wcond459;
        if (_wcond459) {
        } else {
            ;
            break;
        }
        ;
        U64 _t467 = U64_sub(hi, lo);
        (void)_t467;
        U64 _t468 = 2;
        (void)_t468;
        U64 _t469 = U64_div(_t467, _t468);
        (void)_t469;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t469);
        (void)mid;
        ;
        U64 *_t470 = malloc(sizeof(U64)); *_t470 = U64_mul(DEREF(mid), self->key_size);
        (void)_t470;
        void *_t471 = ptr_add(self->key_data, DEREF(_t470));
        (void)_t471;
        I64 *c = dyn_call_cmp(&self->key_type, _t471, key);
        (void)c;
        U64_delete(_t470, &(Bool){1});
        I64 _t472 = 0;
        (void)_t472;
        Bool _t473; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t472}); _t473 = *_hp; free(_hp); }
        (void)_t473;
        ;
        if (_t473) {
            U64 _t460 = 1;
            (void)_t460;
            U64 _t461 = U64_add(DEREF(mid), _t460);
            (void)_t461;
            ;
            lo = _t461;
            ;
        } else {
            I64 _t465 = 0;
            (void)_t465;
            Bool _t466; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t465}); _t466 = *_hp; free(_hp); }
            (void)_t466;
            ;
            if (_t466) {
                U64 _t462 = U64_clone(mid);
                (void)_t462;
                hi = _t462;
                ;
            } else {
                U64 *_t463 = malloc(sizeof(U64)); *_t463 = U64_mul(DEREF(mid), self->val_size);
                (void)_t463;
                void *_t464 = ptr_add(self->val_data, DEREF(_t463));
                (void)_t464;
                U64_delete(_t463, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t464;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t474 = Str_lit("Str", 3ULL);
    (void)_t474;
    U64 _t475; { U64 *_hp = (U64 *)Str_size(); _t475 = *_hp; free(_hp); }
    (void)_t475;
    U64 _t476 = 1;
    (void)_t476;
    Array *_va10 = Array_new(_t474, &(U64){_t475}, &(U64){_t476});
    (void)_va10;
    Str_delete(_t474, &(Bool){1});
    ;
    ;
    U64 _t477 = 0;
    (void)_t477;
    Str *_t478 = Str_lit("Map.get: key not found", 22ULL);
    (void)_t478;
    Array_set(_va10, &(U64){_t477}, _t478);
    ;
    Str *_t479 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/map.til:56:15", 60ULL);
    (void)_t479;
    panic(_t479, _va10);
    Str_delete(_t479, &(Bool){1});
    U64 *_t480 = malloc(sizeof(U64));
    *_t480 = 0;
    (void)_t480;
    void *_t481 = ptr_add(self->val_data, DEREF(_t480));
    (void)_t481;
    U64_delete(_t480, &(Bool){1});
    return _t481;
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
        Bool _wcond482; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond482 = *_hp; free(_hp); }
        (void)_wcond482;
        if (_wcond482) {
        } else {
            ;
            break;
        }
        ;
        U64 _t491 = U64_sub(hi, lo);
        (void)_t491;
        U64 _t492 = 2;
        (void)_t492;
        U64 _t493 = U64_div(_t491, _t492);
        (void)_t493;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t493);
        (void)mid;
        ;
        U64 *_t494 = malloc(sizeof(U64)); *_t494 = U64_mul(DEREF(mid), self->key_size);
        (void)_t494;
        void *_t495 = ptr_add(self->key_data, DEREF(_t494));
        (void)_t495;
        I64 *c = dyn_call_cmp(&self->key_type, _t495, key);
        (void)c;
        U64_delete(_t494, &(Bool){1});
        I64 _t496 = 0;
        (void)_t496;
        Bool _t497; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t496}); _t497 = *_hp; free(_hp); }
        (void)_t497;
        ;
        if (_t497) {
            U64 _t483 = 1;
            (void)_t483;
            U64 _t484 = U64_add(DEREF(mid), _t483);
            (void)_t484;
            ;
            lo = _t484;
            ;
        } else {
            I64 _t489 = 0;
            (void)_t489;
            Bool _t490; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t489}); _t490 = *_hp; free(_hp); }
            (void)_t490;
            ;
            if (_t490) {
                U64 _t485 = U64_clone(mid);
                (void)_t485;
                hi = _t485;
                ;
            } else {
                Bool _t486 = 1;
                (void)_t486;
                found = _t486;
                ;
                U64 _t487 = U64_clone(mid);
                (void)_t487;
                lo = _t487;
                ;
                U64 _t488 = U64_clone(mid);
                (void)_t488;
                hi = _t488;
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
        Bool _t502; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t502 = *_hp; free(_hp); }
        (void)_t502;
        Bool _t503 = Bool_not(_t502);
        (void)_t503;
        ;
        if (_t503) {
            Bool _t498 = 0;
            (void)_t498;
            dyn_call_delete(&self->key_type, key, &(Bool){_t498});
            ;
        }
        ;
        free(key);
        Bool _t504; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t504 = *_hp; free(_hp); }
        (void)_t504;
        Bool _t505 = Bool_not(_t504);
        (void)_t505;
        ;
        if (_t505) {
            U64 *_t499 = malloc(sizeof(U64)); *_t499 = U64_mul(lo, self->val_size);
            (void)_t499;
            void *_t500 = ptr_add(self->val_data, DEREF(_t499));
            (void)_t500;
            Bool _t501 = 0;
            (void)_t501;
            dyn_call_delete(&self->val_type, _t500, &(Bool){_t501});
            U64_delete(_t499, &(Bool){1});
            ;
        }
        ;
        U64 *_t506 = malloc(sizeof(U64)); *_t506 = U64_mul(lo, self->val_size);
        (void)_t506;
        void *_t507 = ptr_add(self->val_data, DEREF(_t506));
        (void)_t507;
        memcpy(_t507, val, self->val_size);
        U64_delete(_t506, &(Bool){1});
        free(val);
    } else {
        Bool _t514 = U64_eq(self->count, self->cap);
        (void)_t514;
        if (_t514) {
            U64 _t508 = 2;
            (void)_t508;
            U64 new_cap = U64_mul(self->cap, _t508);
            (void)new_cap;
            ;
            U64 _t509 = U64_mul(new_cap, self->key_size);
            (void)_t509;
            void *_t510 = realloc(self->key_data, _t509);
            (void)_t510;
            ;
            self->key_data = _t510;
            U64 _t511 = U64_mul(new_cap, self->val_size);
            (void)_t511;
            void *_t512 = realloc(self->val_data, _t511);
            (void)_t512;
            ;
            self->val_data = _t512;
            U64 _t513 = U64_clone(&(U64){new_cap});
            (void)_t513;
            ;
            self->cap = _t513;
            ;
        }
        ;
        U64 _t515 = 1;
        (void)_t515;
        U64 _t516 = U64_add(lo, _t515);
        (void)_t516;
        ;
        U64 *_t517 = malloc(sizeof(U64)); *_t517 = U64_mul(_t516, self->key_size);
        (void)_t517;
        ;
        U64 *_t518 = malloc(sizeof(U64)); *_t518 = U64_mul(lo, self->key_size);
        (void)_t518;
        U64 _t519 = U64_sub(self->count, lo);
        (void)_t519;
        void *_t520 = ptr_add(self->key_data, DEREF(_t517));
        (void)_t520;
        void *_t521 = ptr_add(self->key_data, DEREF(_t518));
        (void)_t521;
        U64 _t522 = U64_mul(_t519, self->key_size);
        (void)_t522;
        ;
        memmove(_t520, _t521, _t522);
        U64_delete(_t517, &(Bool){1});
        U64_delete(_t518, &(Bool){1});
        ;
        U64 _t523 = 1;
        (void)_t523;
        U64 _t524 = U64_add(lo, _t523);
        (void)_t524;
        ;
        U64 *_t525 = malloc(sizeof(U64)); *_t525 = U64_mul(_t524, self->val_size);
        (void)_t525;
        ;
        U64 *_t526 = malloc(sizeof(U64)); *_t526 = U64_mul(lo, self->val_size);
        (void)_t526;
        U64 _t527 = U64_sub(self->count, lo);
        (void)_t527;
        void *_t528 = ptr_add(self->val_data, DEREF(_t525));
        (void)_t528;
        void *_t529 = ptr_add(self->val_data, DEREF(_t526));
        (void)_t529;
        U64 _t530 = U64_mul(_t527, self->val_size);
        (void)_t530;
        ;
        memmove(_t528, _t529, _t530);
        U64_delete(_t525, &(Bool){1});
        U64_delete(_t526, &(Bool){1});
        ;
        U64 *_t531 = malloc(sizeof(U64)); *_t531 = U64_mul(lo, self->key_size);
        (void)_t531;
        void *_t532 = ptr_add(self->key_data, DEREF(_t531));
        (void)_t532;
        memcpy(_t532, key, self->key_size);
        U64_delete(_t531, &(Bool){1});
        U64 *_t533 = malloc(sizeof(U64)); *_t533 = U64_mul(lo, self->val_size);
        (void)_t533;
        void *_t534 = ptr_add(self->val_data, DEREF(_t533));
        (void)_t534;
        memcpy(_t534, val, self->val_size);
        U64_delete(_t533, &(Bool){1});
        free(key);
        free(val);
        U64 _t535 = 1;
        (void)_t535;
        U64 _t536 = U64_add(self->count, _t535);
        (void)_t536;
        ;
        self->count = _t536;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t563; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t563 = *_hp; free(_hp); }
    (void)_t563;
    Bool _t564 = Bool_not(_t563);
    (void)_t564;
    ;
    if (_t564) {
        {
            U64 _fi537 = 0;
            (void)_fi537;
            while (1) {
                U64 _t539 = 0;
                (void)_t539;
                Range *_t540 = Range_new(_t539, self->count);
                (void)_t540;
                ;
                U64 _t541; { U64 *_hp = (U64 *)Range_len(_t540); _t541 = *_hp; free(_hp); }
                (void)_t541;
                Range_delete(_t540, &(Bool){1});
                Bool _wcond538; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi537}, &(U64){_t541}); _wcond538 = *_hp; free(_hp); }
                (void)_wcond538;
                ;
                if (_wcond538) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t542 = 0;
                (void)_t542;
                Range *_t543 = Range_new(_t542, self->count);
                (void)_t543;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t543, _fi537); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t543, &(Bool){1});
                U64 _t544 = 1;
                (void)_t544;
                U64 _t545 = U64_add(_fi537, _t544);
                (void)_t545;
                ;
                _fi537 = _t545;
                ;
                U64 *_t546 = malloc(sizeof(U64)); *_t546 = U64_mul(i, self->key_size);
                (void)_t546;
                ;
                void *_t547 = ptr_add(self->key_data, DEREF(_t546));
                (void)_t547;
                Bool _t548 = 0;
                (void)_t548;
                dyn_call_delete(&self->key_type, _t547, &(Bool){_t548});
                U64_delete(_t546, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t565; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t565 = *_hp; free(_hp); }
    (void)_t565;
    Bool _t566 = Bool_not(_t565);
    (void)_t566;
    ;
    if (_t566) {
        {
            U64 _fi549 = 0;
            (void)_fi549;
            while (1) {
                U64 _t551 = 0;
                (void)_t551;
                Range *_t552 = Range_new(_t551, self->count);
                (void)_t552;
                ;
                U64 _t553; { U64 *_hp = (U64 *)Range_len(_t552); _t553 = *_hp; free(_hp); }
                (void)_t553;
                Range_delete(_t552, &(Bool){1});
                Bool _wcond550; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi549}, &(U64){_t553}); _wcond550 = *_hp; free(_hp); }
                (void)_wcond550;
                ;
                if (_wcond550) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t554 = 0;
                (void)_t554;
                Range *_t555 = Range_new(_t554, self->count);
                (void)_t555;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t555, _fi549); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t555, &(Bool){1});
                U64 _t556 = 1;
                (void)_t556;
                U64 _t557 = U64_add(_fi549, _t556);
                (void)_t557;
                ;
                _fi549 = _t557;
                ;
                U64 *_t558 = malloc(sizeof(U64)); *_t558 = U64_mul(i, self->val_size);
                (void)_t558;
                ;
                void *_t559 = ptr_add(self->val_data, DEREF(_t558));
                (void)_t559;
                Bool _t560 = 0;
                (void)_t560;
                dyn_call_delete(&self->val_type, _t559, &(Bool){_t560});
                U64_delete(_t558, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t567; { Bool *_hp = (Bool *)Str_is_empty(&self->key_type); _t567 = *_hp; free(_hp); }
    (void)_t567;
    Bool _t568 = Bool_not(_t567);
    (void)_t568;
    ;
    if (_t568) {
        Bool _t561 = 0;
        (void)_t561;
        Str_delete(&self->key_type, &(Bool){_t561});
        ;
    }
    ;
    Bool _t569; { Bool *_hp = (Bool *)Str_is_empty(&self->val_type); _t569 = *_hp; free(_hp); }
    (void)_t569;
    Bool _t570 = Bool_not(_t569);
    (void)_t570;
    ;
    if (_t570) {
        Bool _t562 = 0;
        (void)_t562;
        Str_delete(&self->val_type, &(Bool){_t562});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t588 = U64_mul(self->cap, self->key_size);
    (void)_t588;
    U8 *new_keys = malloc(_t588);
    (void)new_keys;
    ;
    U64 _t589 = U64_mul(self->cap, self->val_size);
    (void)_t589;
    U8 *new_vals = malloc(_t589);
    (void)new_vals;
    ;
    {
        U64 _fi571 = 0;
        (void)_fi571;
        while (1) {
            U64 _t573 = 0;
            (void)_t573;
            Range *_t574 = Range_new(_t573, self->count);
            (void)_t574;
            ;
            U64 _t575; { U64 *_hp = (U64 *)Range_len(_t574); _t575 = *_hp; free(_hp); }
            (void)_t575;
            Range_delete(_t574, &(Bool){1});
            Bool _wcond572; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi571}, &(U64){_t575}); _wcond572 = *_hp; free(_hp); }
            (void)_wcond572;
            ;
            if (_wcond572) {
            } else {
                ;
                break;
            }
            ;
            U64 _t576 = 0;
            (void)_t576;
            Range *_t577 = Range_new(_t576, self->count);
            (void)_t577;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t577, _fi571); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t577, &(Bool){1});
            U64 _t578 = 1;
            (void)_t578;
            U64 _t579 = U64_add(_fi571, _t578);
            (void)_t579;
            ;
            _fi571 = _t579;
            ;
            U64 *_t580 = malloc(sizeof(U64)); *_t580 = U64_mul(i, self->key_size);
            (void)_t580;
            void *_t581 = ptr_add(self->key_data, DEREF(_t580));
            (void)_t581;
            void *ck = dyn_call_clone(&self->key_type, _t581);
            (void)ck;
            U64_delete(_t580, &(Bool){1});
            U64 *_t582 = malloc(sizeof(U64)); *_t582 = U64_mul(i, self->key_size);
            (void)_t582;
            void *_t583 = ptr_add(new_keys, DEREF(_t582));
            (void)_t583;
            memcpy(_t583, ck, self->key_size);
            U64_delete(_t582, &(Bool){1});
            free(ck);
            U64 *_t584 = malloc(sizeof(U64)); *_t584 = U64_mul(i, self->val_size);
            (void)_t584;
            void *_t585 = ptr_add(self->val_data, DEREF(_t584));
            (void)_t585;
            void *cv = dyn_call_clone(&self->val_type, _t585);
            (void)cv;
            U64_delete(_t584, &(Bool){1});
            U64 *_t586 = malloc(sizeof(U64)); *_t586 = U64_mul(i, self->val_size);
            (void)_t586;
            ;
            void *_t587 = ptr_add(new_vals, DEREF(_t586));
            (void)_t587;
            memcpy(_t587, cv, self->val_size);
            U64_delete(_t586, &(Bool){1});
            free(cv);
        }
        ;
    }
    Map *_t590 = malloc(sizeof(Map));
    _t590->key_data = new_keys;
    _t590->val_data = new_vals;
    _t590->count = self->count;
    _t590->cap = self->cap;
    _t590->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t590->key_type = *_ca; free(_ca); }
    _t590->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t590->val_type = *_ca; free(_ca); }
    (void)_t590;
    return _t590;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t604; { Bool *_hp = (Bool *)Str_is_empty(elem_type); _t604 = *_hp; free(_hp); }
    (void)_t604;
    Bool _t605 = Bool_not(_t604);
    (void)_t605;
    ;
    if (_t605) {
        Bool _t602 = dyn_has_cmp(elem_type);
        (void)_t602;
        Bool _t603 = Bool_not(_t602);
        (void)_t603;
        ;
        if (_t603) {
            Str *_t592 = Str_lit("Str", 3ULL);
            (void)_t592;
            U64 _t593; { U64 *_hp = (U64 *)Str_size(); _t593 = *_hp; free(_hp); }
            (void)_t593;
            U64 _t594 = 3;
            (void)_t594;
            Array *_va11 = Array_new(_t592, &(U64){_t593}, &(U64){_t594});
            (void)_va11;
            Str_delete(_t592, &(Bool){1});
            ;
            ;
            U64 _t595 = 0;
            (void)_t595;
            Str *_t596 = Str_lit("Set.new: type ", 14ULL);
            (void)_t596;
            Array_set(_va11, &(U64){_t595}, _t596);
            ;
            U64 _t597 = 1;
            (void)_t597;
            Str *_t598 = Str_clone(elem_type);
            (void)_t598;
            Array_set(_va11, &(U64){_t597}, _t598);
            ;
            U64 _t599 = 2;
            (void)_t599;
            Str *_t600 = Str_lit(" must implement cmp", 19ULL);
            (void)_t600;
            Array_set(_va11, &(U64){_t599}, _t600);
            ;
            Str *_t601 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/set.til:14:23", 60ULL);
            (void)_t601;
            panic(_t601, _va11);
            Str_delete(_t601, &(Bool){1});
        }
        ;
    }
    ;
    void *_t606 = malloc(DEREF(elem_size));
    (void)_t606;
    U64 _t607 = 0;
    (void)_t607;
    I64 _t608 = 1;
    (void)_t608;
    U64 _t609 = U64_clone(elem_size);
    (void)_t609;
    Set *_t610 = malloc(sizeof(Set));
    _t610->data = _t606;
    _t610->count = _t607;
    _t610->cap = _t608;
    _t610->elem_size = _t609;
    { Str *_ca = Str_clone(elem_type); _t610->elem_type = *_ca; free(_ca); }
    (void)_t610;
    ;
    ;
    ;
    return _t610;
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
        Bool _wcond611; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond611 = *_hp; free(_hp); }
        (void)_wcond611;
        if (_wcond611) {
        } else {
            ;
            break;
        }
        ;
        U64 _t618 = U64_sub(hi, lo);
        (void)_t618;
        U64 _t619 = 2;
        (void)_t619;
        U64 _t620 = U64_div(_t618, _t619);
        (void)_t620;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t620);
        (void)mid;
        ;
        U64 *_t621 = malloc(sizeof(U64)); *_t621 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t621;
        void *_t622 = ptr_add(self->data, DEREF(_t621));
        (void)_t622;
        I64 *c = dyn_call_cmp(&self->elem_type, _t622, val);
        (void)c;
        U64_delete(_t621, &(Bool){1});
        I64 _t623 = 0;
        (void)_t623;
        Bool _t624; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t623}); _t624 = *_hp; free(_hp); }
        (void)_t624;
        ;
        if (_t624) {
            U64 _t612 = 1;
            (void)_t612;
            U64 _t613 = U64_add(DEREF(mid), _t612);
            (void)_t613;
            ;
            lo = _t613;
            ;
        } else {
            I64 _t616 = 0;
            (void)_t616;
            Bool _t617; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t616}); _t617 = *_hp; free(_hp); }
            (void)_t617;
            ;
            if (_t617) {
                U64 _t614 = U64_clone(mid);
                (void)_t614;
                hi = _t614;
                ;
            } else {
                Bool _t615 = 1;
                (void)_t615;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t615; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t625 = 0;
    (void)_t625;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t625; return _r; }
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
        Bool _wcond626; { Bool *_hp = (Bool *)U64_lt(&(U64){lo}, &(U64){hi}); _wcond626 = *_hp; free(_hp); }
        (void)_wcond626;
        if (_wcond626) {
        } else {
            ;
            break;
        }
        ;
        U64 _t635 = U64_sub(hi, lo);
        (void)_t635;
        U64 _t636 = 2;
        (void)_t636;
        U64 _t637 = U64_div(_t635, _t636);
        (void)_t637;
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t637);
        (void)mid;
        ;
        U64 *_t638 = malloc(sizeof(U64)); *_t638 = U64_mul(DEREF(mid), self->elem_size);
        (void)_t638;
        void *_t639 = ptr_add(self->data, DEREF(_t638));
        (void)_t639;
        I64 *c = dyn_call_cmp(&self->elem_type, _t639, val);
        (void)c;
        U64_delete(_t638, &(Bool){1});
        I64 _t640 = 0;
        (void)_t640;
        Bool _t641; { Bool *_hp = (Bool *)I64_lt(c, &(I64){_t640}); _t641 = *_hp; free(_hp); }
        (void)_t641;
        ;
        if (_t641) {
            U64 _t627 = 1;
            (void)_t627;
            U64 _t628 = U64_add(DEREF(mid), _t627);
            (void)_t628;
            ;
            lo = _t628;
            ;
        } else {
            I64 _t633 = 0;
            (void)_t633;
            Bool _t634; { Bool *_hp = (Bool *)I64_gt(c, &(I64){_t633}); _t634 = *_hp; free(_hp); }
            (void)_t634;
            ;
            if (_t634) {
                U64 _t629 = U64_clone(mid);
                (void)_t629;
                hi = _t629;
                ;
            } else {
                Bool _t630 = 1;
                (void)_t630;
                found = _t630;
                ;
                U64 _t631 = U64_clone(mid);
                (void)_t631;
                lo = _t631;
                ;
                U64 _t632 = U64_clone(mid);
                (void)_t632;
                hi = _t632;
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
        Bool _t643; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t643 = *_hp; free(_hp); }
        (void)_t643;
        Bool _t644 = Bool_not(_t643);
        (void)_t644;
        ;
        if (_t644) {
            Bool _t642 = 0;
            (void)_t642;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t642});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t649 = U64_eq(self->count, self->cap);
        (void)_t649;
        if (_t649) {
            U64 _t645 = 2;
            (void)_t645;
            U64 new_cap = U64_mul(self->cap, _t645);
            (void)new_cap;
            ;
            U64 _t646 = U64_mul(new_cap, self->elem_size);
            (void)_t646;
            void *_t647 = realloc(self->data, _t646);
            (void)_t647;
            ;
            self->data = _t647;
            U64 _t648 = U64_clone(&(U64){new_cap});
            (void)_t648;
            ;
            self->cap = _t648;
            ;
        }
        ;
        U64 _t650 = 1;
        (void)_t650;
        U64 _t651 = U64_add(lo, _t650);
        (void)_t651;
        ;
        U64 *_t652 = malloc(sizeof(U64)); *_t652 = U64_mul(_t651, self->elem_size);
        (void)_t652;
        ;
        U64 *_t653 = malloc(sizeof(U64)); *_t653 = U64_mul(lo, self->elem_size);
        (void)_t653;
        U64 _t654 = U64_sub(self->count, lo);
        (void)_t654;
        void *_t655 = ptr_add(self->data, DEREF(_t652));
        (void)_t655;
        void *_t656 = ptr_add(self->data, DEREF(_t653));
        (void)_t656;
        U64 _t657 = U64_mul(_t654, self->elem_size);
        (void)_t657;
        ;
        memmove(_t655, _t656, _t657);
        U64_delete(_t652, &(Bool){1});
        U64_delete(_t653, &(Bool){1});
        ;
        U64 *_t658 = malloc(sizeof(U64)); *_t658 = U64_mul(lo, self->elem_size);
        (void)_t658;
        void *_t659 = ptr_add(self->data, DEREF(_t658));
        (void)_t659;
        memcpy(_t659, val, self->elem_size);
        U64_delete(_t658, &(Bool){1});
        free(val);
        U64 _t660 = 1;
        (void)_t660;
        U64 _t661 = U64_add(self->count, _t660);
        (void)_t661;
        ;
        self->count = _t661;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t675; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t675 = *_hp; free(_hp); }
    (void)_t675;
    Bool _t676 = Bool_not(_t675);
    (void)_t676;
    ;
    if (_t676) {
        {
            U64 _fi662 = 0;
            (void)_fi662;
            while (1) {
                U64 _t664 = 0;
                (void)_t664;
                Range *_t665 = Range_new(_t664, self->count);
                (void)_t665;
                ;
                U64 _t666; { U64 *_hp = (U64 *)Range_len(_t665); _t666 = *_hp; free(_hp); }
                (void)_t666;
                Range_delete(_t665, &(Bool){1});
                Bool _wcond663; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi662}, &(U64){_t666}); _wcond663 = *_hp; free(_hp); }
                (void)_wcond663;
                ;
                if (_wcond663) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t667 = 0;
                (void)_t667;
                Range *_t668 = Range_new(_t667, self->count);
                (void)_t668;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t668, _fi662); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t668, &(Bool){1});
                U64 _t669 = 1;
                (void)_t669;
                U64 _t670 = U64_add(_fi662, _t669);
                (void)_t670;
                ;
                _fi662 = _t670;
                ;
                U64 *_t671 = malloc(sizeof(U64)); *_t671 = U64_mul(i, self->elem_size);
                (void)_t671;
                ;
                void *_t672 = ptr_add(self->data, DEREF(_t671));
                (void)_t672;
                Bool _t673 = 0;
                (void)_t673;
                dyn_call_delete(&self->elem_type, _t672, &(Bool){_t673});
                U64_delete(_t671, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t677; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t677 = *_hp; free(_hp); }
    (void)_t677;
    Bool _t678 = Bool_not(_t677);
    (void)_t678;
    ;
    if (_t678) {
        Bool _t674 = 0;
        (void)_t674;
        Str_delete(&self->elem_type, &(Bool){_t674});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t692 = U64_mul(self->cap, self->elem_size);
    (void)_t692;
    U8 *new_data = malloc(_t692);
    (void)new_data;
    ;
    {
        U64 _fi679 = 0;
        (void)_fi679;
        while (1) {
            U64 _t681 = 0;
            (void)_t681;
            Range *_t682 = Range_new(_t681, self->count);
            (void)_t682;
            ;
            U64 _t683; { U64 *_hp = (U64 *)Range_len(_t682); _t683 = *_hp; free(_hp); }
            (void)_t683;
            Range_delete(_t682, &(Bool){1});
            Bool _wcond680; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi679}, &(U64){_t683}); _wcond680 = *_hp; free(_hp); }
            (void)_wcond680;
            ;
            if (_wcond680) {
            } else {
                ;
                break;
            }
            ;
            U64 _t684 = 0;
            (void)_t684;
            Range *_t685 = Range_new(_t684, self->count);
            (void)_t685;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t685, _fi679); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t685, &(Bool){1});
            U64 _t686 = 1;
            (void)_t686;
            U64 _t687 = U64_add(_fi679, _t686);
            (void)_t687;
            ;
            _fi679 = _t687;
            ;
            U64 *_t688 = malloc(sizeof(U64)); *_t688 = U64_mul(i, self->elem_size);
            (void)_t688;
            void *_t689 = ptr_add(self->data, DEREF(_t688));
            (void)_t689;
            void *cloned = dyn_call_clone(&self->elem_type, _t689);
            (void)cloned;
            U64_delete(_t688, &(Bool){1});
            U64 *_t690 = malloc(sizeof(U64)); *_t690 = U64_mul(i, self->elem_size);
            (void)_t690;
            ;
            void *_t691 = ptr_add(new_data, DEREF(_t690));
            (void)_t691;
            memcpy(_t691, cloned, self->elem_size);
            U64_delete(_t690, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Set *_t693 = malloc(sizeof(Set));
    _t693->data = new_data;
    _t693->count = self->count;
    _t693->cap = self->cap;
    _t693->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t693->elem_type = *_ca; free(_ca); }
    (void)_t693;
    return _t693;
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
    Bool _t701; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t701 = *_hp; free(_hp); }
    (void)_t701;
    if (_t701) {
        Str *_t695 = Str_lit("Str", 3ULL);
        (void)_t695;
        U64 _t696; { U64 *_hp = (U64 *)Str_size(); _t696 = *_hp; free(_hp); }
        (void)_t696;
        U64 _t697 = 1;
        (void)_t697;
        Array *_va12 = Array_new(_t695, &(U64){_t696}, &(U64){_t697});
        (void)_va12;
        Str_delete(_t695, &(Bool){1});
        ;
        ;
        U64 _t698 = 0;
        (void)_t698;
        Str *_t699 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t699;
        Array_set(_va12, &(U64){_t698}, _t699);
        ;
        Str *_t700 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:16:19", 60ULL);
        (void)_t700;
        panic(_t700, _va12);
        Str_delete(_t700, &(Bool){1});
    }
    ;
    void *_t702 = ptr_add(self->c_str, DEREF(i));
    (void)_t702;
    return _t702;
}

U8 * Str_byte_at(Str * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t703 = ptr_add(self->c_str, DEREF(i));
    (void)_t703;
    return _t703;
}

I64 * Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    U64 min_len = a->count;
    (void)min_len;
    Bool _t709; { Bool *_hp = (Bool *)U64_lt(&b->count, &a->count); _t709 = *_hp; free(_hp); }
    (void)_t709;
    if (_t709) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond704; { Bool *_hp = (Bool *)U64_lt(i, &(U64){min_len}); _wcond704 = *_hp; free(_hp); }
        (void)_wcond704;
        if (_wcond704) {
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
        I64 _t705 = 0;
        (void)_t705;
        Bool _t706; { Bool *_hp = (Bool *)I64_neq(c, &(I64){_t705}); _t706 = *_hp; free(_hp); }
        (void)_t706;
        ;
        if (_t706) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t707 = 1;
        (void)_t707;
        U64 _t708 = U64_add(DEREF(i), _t707);
        (void)_t708;
        ;
        *i = _t708;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t710 = U64_cmp(a->count, b->count);
    (void)_t710;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t710; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    (void)new_len;
    U64 _t711 = 1;
    (void)_t711;
    U64 _t712 = U64_add(DEREF(new_len), _t711);
    (void)_t712;
    ;
    U8 *new_data = malloc(_t712);
    (void)new_data;
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t713 = ptr_add(new_data, a->count);
    (void)_t713;
    memcpy(_t713, b->c_str, b->count);
    void *_t714 = ptr_add(new_data, DEREF(new_len));
    (void)_t714;
    I32 _t715 = 0;
    (void)_t715;
    U64 _t716 = 1;
    (void)_t716;
    memset(_t714, _t715, _t716);
    ;
    ;
    U64 _t717 = U64_clone(new_len);
    (void)_t717;
    U64 _t718 = U64_clone(new_len);
    (void)_t718;
    U64_delete(new_len, &(Bool){1});
    Str *_t719 = malloc(sizeof(Str));
    _t719->c_str = new_data;
    _t719->count = _t717;
    _t719->cap = _t718;
    (void)_t719;
    ;
    ;
    return _t719;
}

Str * Str_with_capacity(U64 * n) {
    (void)n;
    U64 _t720 = 1;
    (void)_t720;
    U64 _t721 = U64_add(DEREF(n), _t720);
    (void)_t721;
    ;
    U8 *buf = malloc(_t721);
    (void)buf;
    ;
    I32 _t722 = 0;
    (void)_t722;
    U64 _t723 = 1;
    (void)_t723;
    memset(buf, _t722, _t723);
    ;
    ;
    I64 _t724 = 0;
    (void)_t724;
    U64 _t725 = U64_clone(n);
    (void)_t725;
    Str *_t726 = malloc(sizeof(Str));
    _t726->c_str = buf;
    _t726->count = _t724;
    _t726->cap = _t725;
    (void)_t726;
    ;
    ;
    return _t726;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t739; { Bool *_hp = (Bool *)U64_gte(&self->cap, CAP_VIEW); _t739 = *_hp; free(_hp); }
    (void)_t739;
    if (_t739) {
        Str *_t727 = Str_lit("Str", 3ULL);
        (void)_t727;
        U64 _t728; { U64 *_hp = (U64 *)Str_size(); _t728 = *_hp; free(_hp); }
        (void)_t728;
        U64 _t729 = 1;
        (void)_t729;
        Array *_va13 = Array_new(_t727, &(U64){_t728}, &(U64){_t729});
        (void)_va13;
        Str_delete(_t727, &(Bool){1});
        ;
        ;
        U64 _t730 = 0;
        (void)_t730;
        Str *_t731 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t731;
        Array_set(_va13, &(U64){_t730}, _t731);
        ;
        Str *_t732 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:57:19", 60ULL);
        (void)_t732;
        panic(_t732, _va13);
        Str_delete(_t732, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    (void)new_len;
    Bool _t740; { Bool *_hp = (Bool *)U64_gt(new_len, &self->cap); _t740 = *_hp; free(_hp); }
    (void)_t740;
    if (_t740) {
        Str *_t733 = Str_lit("Str", 3ULL);
        (void)_t733;
        U64 _t734; { U64 *_hp = (U64 *)Str_size(); _t734 = *_hp; free(_hp); }
        (void)_t734;
        U64 _t735 = 1;
        (void)_t735;
        Array *_va14 = Array_new(_t733, &(U64){_t734}, &(U64){_t735});
        (void)_va14;
        Str_delete(_t733, &(Bool){1});
        ;
        ;
        U64 _t736 = 0;
        (void)_t736;
        Str *_t737 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t737;
        Array_set(_va14, &(U64){_t736}, _t737);
        ;
        Str *_t738 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:61:19", 60ULL);
        (void)_t738;
        panic(_t738, _va14);
        Str_delete(_t738, &(Bool){1});
    }
    ;
    void *_t741 = ptr_add(self->c_str, self->count);
    (void)_t741;
    memcpy(_t741, s->c_str, s->count);
    U64 _t742 = U64_clone(new_len);
    (void)_t742;
    self->count = _t742;
    ;
    void *_t743 = ptr_add(self->c_str, DEREF(new_len));
    (void)_t743;
    I32 _t744 = 0;
    (void)_t744;
    U64 _t745 = 1;
    (void)_t745;
    memset(_t743, _t744, _t745);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    (void)val;
    U64 _t746 = 1;
    (void)_t746;
    U64 _t747 = U64_add(val->count, _t746);
    (void)_t747;
    ;
    U8 *new_data = malloc(_t747);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t748 = ptr_add(new_data, val->count);
    (void)_t748;
    I32 _t749 = 0;
    (void)_t749;
    U64 _t750 = 1;
    (void)_t750;
    memset(_t748, _t749, _t750);
    ;
    ;
    Str *_t751 = malloc(sizeof(Str));
    _t751->c_str = new_data;
    _t751->count = val->count;
    _t751->cap = val->count;
    (void)_t751;
    return _t751;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t752; { Bool *_hp = (Bool *)U64_lt(&self->cap, CAP_VIEW); _t752 = *_hp; free(_hp); }
    (void)_t752;
    if (_t752) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t753 = Str_clone(val);
    (void)_t753;
    return _t753;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    (void)s;
    (void)start;
    (void)n;
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    (void)st;
    U64 ln = U64_clone(n);
    (void)ln;
    Bool _t755; { Bool *_hp = (Bool *)U64_gt(st, &s->count); _t755 = *_hp; free(_hp); }
    (void)_t755;
    if (_t755) {
        *st = s->count;
    }
    ;
    U64 _t756 = U64_add(DEREF(st), ln);
    (void)_t756;
    Bool _t757; { Bool *_hp = (Bool *)U64_gt(&(U64){_t756}, &s->count); _t757 = *_hp; free(_hp); }
    (void)_t757;
    ;
    if (_t757) {
        U64 _t754 = U64_sub(s->count, DEREF(st));
        (void)_t754;
        ln = _t754;
        ;
    }
    ;
    void *_t758 = ptr_add(s->c_str, DEREF(st));
    (void)_t758;
    U64 _t759 = U64_clone(&(U64){ln});
    (void)_t759;
    ;
    U64 _t760 = U64_clone(CAP_VIEW);
    (void)_t760;
    Str *_t761 = malloc(sizeof(Str));
    _t761->c_str = _t758;
    _t761->count = _t759;
    _t761->cap = _t760;
    (void)_t761;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t761;
}

Bool * Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U64 _t775 = 0;
    (void)_t775;
    Bool _t776 = U64_eq(b->count, _t775);
    (void)_t776;
    ;
    if (_t776) {
        Bool _t762 = 1;
        (void)_t762;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t762; return _r; }
    }
    ;
    Bool _t777; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t777 = *_hp; free(_hp); }
    (void)_t777;
    if (_t777) {
        Bool _t763 = 0;
        (void)_t763;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t763; return _r; }
    }
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t772 = U64_sub(a->count, b->count);
        (void)_t772;
        Bool _wcond764; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t772}); _wcond764 = *_hp; free(_hp); }
        (void)_wcond764;
        ;
        if (_wcond764) {
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
            Bool _wcond765; { Bool *_hp = (Bool *)U64_lt(j, &b->count); _wcond765 = *_hp; free(_hp); }
            (void)_wcond765;
            if (_wcond765) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t767 = malloc(sizeof(U64)); *_t767 = U64_add(i, DEREF(j));
            (void)_t767;
            U8 *ac = Str_get(a, _t767);
            (void)ac;
            U8 *bc = Str_get(b, j);
            (void)bc;
            Bool _t768; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t768 = *_hp; free(_hp); }
            (void)_t768;
            U64_delete(_t767, &(Bool){1});
            if (_t768) {
                Bool _t766 = 0;
                (void)_t766;
                found = _t766;
                ;
            }
            ;
            U64 _t769 = 1;
            (void)_t769;
            U64 _t770 = U64_add(DEREF(j), _t769);
            (void)_t770;
            ;
            *j = _t770;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t771 = 1;
            (void)_t771;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t771; return _r; }
        }
        ;
        U64 _t773 = 1;
        (void)_t773;
        U64 _t774 = U64_add(i, _t773);
        (void)_t774;
        ;
        i = _t774;
        ;
    }
    ;
    Bool _t778 = 0;
    (void)_t778;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t778; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t785; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t785 = *_hp; free(_hp); }
    (void)_t785;
    if (_t785) {
        Bool _t779 = 0;
        (void)_t779;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t779; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        Bool _wcond780; { Bool *_hp = (Bool *)U64_lt(i, &b->count); _wcond780 = *_hp; free(_hp); }
        (void)_wcond780;
        if (_wcond780) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        (void)ac;
        U8 *bc = Str_get(b, i);
        (void)bc;
        Bool _t782; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t782 = *_hp; free(_hp); }
        (void)_t782;
        if (_t782) {
            Bool _t781 = 0;
            (void)_t781;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t781; return _r; }
        }
        ;
        U64 _t783 = 1;
        (void)_t783;
        U64 _t784 = U64_add(DEREF(i), _t783);
        (void)_t784;
        ;
        *i = _t784;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t786 = 1;
    (void)_t786;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t786; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t794; { Bool *_hp = (Bool *)U64_gt(&b->count, &a->count); _t794 = *_hp; free(_hp); }
    (void)_t794;
    if (_t794) {
        Bool _t787 = 0;
        (void)_t787;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t787; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    (void)offset;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        Bool _wcond788; { Bool *_hp = (Bool *)U64_lt(i, &b->count); _wcond788 = *_hp; free(_hp); }
        (void)_wcond788;
        if (_wcond788) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t790 = malloc(sizeof(U64)); *_t790 = U64_add(offset, DEREF(i));
        (void)_t790;
        U8 *ac = Str_get(a, _t790);
        (void)ac;
        U8 *bc = Str_get(b, i);
        (void)bc;
        Bool _t791; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t791 = *_hp; free(_hp); }
        (void)_t791;
        U64_delete(_t790, &(Bool){1});
        if (_t791) {
            Bool _t789 = 0;
            (void)_t789;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t789; return _r; }
        }
        ;
        U64 _t792 = 1;
        (void)_t792;
        U64 _t793 = U64_add(DEREF(i), _t792);
        (void)_t793;
        ;
        *i = _t793;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t795 = 1;
    (void)_t795;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t795; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t796 = 0;
    (void)_t796;
    Bool _t797 = U64_eq(self->count, _t796);
    (void)_t797;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t797; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t815 = 0;
    (void)_t815;
    Bool _t816 = U64_eq(needle->count, _t815);
    (void)_t816;
    ;
    if (_t816) {
        I64 _t798 = 0;
        (void)_t798;
        I64 _t799 = 1;
        (void)_t799;
        I64 _t800 = I64_sub(_t798, _t799);
        (void)_t800;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t800; return _r; }
    }
    ;
    Bool _t817; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t817 = *_hp; free(_hp); }
    (void)_t817;
    if (_t817) {
        I64 _t801 = 0;
        (void)_t801;
        I64 _t802 = 1;
        (void)_t802;
        I64 _t803 = I64_sub(_t801, _t802);
        (void)_t803;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t803; return _r; }
    }
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t812 = U64_sub(self->count, needle->count);
        (void)_t812;
        Bool _wcond804; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t812}); _wcond804 = *_hp; free(_hp); }
        (void)_wcond804;
        ;
        if (_wcond804) {
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
            Bool _wcond805; { Bool *_hp = (Bool *)U64_lt(j, &needle->count); _wcond805 = *_hp; free(_hp); }
            (void)_wcond805;
            if (_wcond805) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t807 = malloc(sizeof(U64)); *_t807 = U64_add(i, DEREF(j));
            (void)_t807;
            U8 *ac = Str_get(self, _t807);
            (void)ac;
            U8 *bc = Str_get(needle, j);
            (void)bc;
            Bool _t808; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t808 = *_hp; free(_hp); }
            (void)_t808;
            U64_delete(_t807, &(Bool){1});
            if (_t808) {
                Bool _t806 = 0;
                (void)_t806;
                found = _t806;
                ;
            }
            ;
            U64 _t809 = 1;
            (void)_t809;
            U64 _t810 = U64_add(DEREF(j), _t809);
            (void)_t810;
            ;
            *j = _t810;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t811 = U64_to_i64(i);
            (void)_t811;
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t811; return _r; }
        }
        ;
        U64 _t813 = 1;
        (void)_t813;
        U64 _t814 = U64_add(i, _t813);
        (void)_t814;
        ;
        i = _t814;
        ;
    }
    ;
    I64 _t818 = 0;
    (void)_t818;
    I64 _t819 = 1;
    (void)_t819;
    I64 _t820 = I64_sub(_t818, _t819);
    (void)_t820;
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t820; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U64 _t838 = 0;
    (void)_t838;
    Bool _t839 = U64_eq(needle->count, _t838);
    (void)_t839;
    ;
    if (_t839) {
        I64 _t821 = 0;
        (void)_t821;
        I64 _t822 = 1;
        (void)_t822;
        I64 _t823 = I64_sub(_t821, _t822);
        (void)_t823;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t823; return _r; }
    }
    ;
    Bool _t840; { Bool *_hp = (Bool *)U64_gt(&needle->count, &self->count); _t840 = *_hp; free(_hp); }
    (void)_t840;
    if (_t840) {
        I64 _t824 = 0;
        (void)_t824;
        I64 _t825 = 1;
        (void)_t825;
        I64 _t826 = I64_sub(_t824, _t825);
        (void)_t826;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t826; return _r; }
    }
    ;
    I64 _t841 = 0;
    (void)_t841;
    I64 _t842 = 1;
    (void)_t842;
    I64 last = I64_sub(_t841, _t842);
    (void)last;
    ;
    ;
    U64 i = 0;
    (void)i;
    while (1) {
        U64 _t835 = U64_sub(self->count, needle->count);
        (void)_t835;
        Bool _wcond827; { Bool *_hp = (Bool *)U64_lte(&(U64){i}, &(U64){_t835}); _wcond827 = *_hp; free(_hp); }
        (void)_wcond827;
        ;
        if (_wcond827) {
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
            Bool _wcond828; { Bool *_hp = (Bool *)U64_lt(j, &needle->count); _wcond828 = *_hp; free(_hp); }
            (void)_wcond828;
            if (_wcond828) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t830 = malloc(sizeof(U64)); *_t830 = U64_add(i, DEREF(j));
            (void)_t830;
            U8 *ac = Str_get(self, _t830);
            (void)ac;
            U8 *bc = Str_get(needle, j);
            (void)bc;
            Bool _t831; { Bool *_hp = (Bool *)U8_neq(ac, bc); _t831 = *_hp; free(_hp); }
            (void)_t831;
            U64_delete(_t830, &(Bool){1});
            if (_t831) {
                Bool _t829 = 0;
                (void)_t829;
                found = _t829;
                ;
            }
            ;
            U64 _t832 = 1;
            (void)_t832;
            U64 _t833 = U64_add(DEREF(j), _t832);
            (void)_t833;
            ;
            *j = _t833;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t834 = U64_to_i64(i);
            (void)_t834;
            last = _t834;
            ;
        }
        ;
        U64 _t836 = 1;
        (void)_t836;
        U64 _t837 = U64_add(i, _t836);
        (void)_t837;
        ;
        i = _t837;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U64 _t858 = 0;
    (void)_t858;
    Bool _t859 = U64_eq(from->count, _t858);
    (void)_t859;
    ;
    if (_t859) {
        Str *_t843 = Str_clone(self);
        (void)_t843;
        ;
        return _t843;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 start = 0;
    (void)start;
    while (1) {
        U64 _t845 = U64_sub(self->count, from->count);
        (void)_t845;
        Bool _wcond844; { Bool *_hp = (Bool *)U64_lte(&(U64){start}, &(U64){_t845}); _wcond844 = *_hp; free(_hp); }
        (void)_wcond844;
        ;
        if (_wcond844) {
        } else {
            ;
            break;
        }
        ;
        U64 _t846 = U64_sub(self->count, start);
        (void)_t846;
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t846});
        (void)rest;
        ;
        I64 pos; { I64 *_hp = (I64 *)Str_find(rest, from); pos = *_hp; free(_hp); }
        (void)pos;
        I64 _t847 = 0;
        (void)_t847;
        I64 _t848 = 1;
        (void)_t848;
        I64 _t849 = I64_sub(_t847, _t848);
        (void)_t849;
        ;
        ;
        Bool _t850 = I64_eq(pos, _t849);
        (void)_t850;
        ;
        if (_t850) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t851 = I64_to_u64(pos);
        (void)_t851;
        Str *_t852 = Str_substr(self, &(U64){start}, &(U64){_t851});
        (void)_t852;
        ;
        result = Str_concat(result, _t852);
        Str_delete(_t852, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t853 = I64_to_u64(pos);
        (void)_t853;
        ;
        U64 _t854 = U64_add(start, _t853);
        (void)_t854;
        ;
        U64 _t855 = U64_add(_t854, from->count);
        (void)_t855;
        ;
        start = _t855;
        ;
    }
    Bool _t860; { Bool *_hp = (Bool *)U64_lt(&(U64){start}, &self->count); _t860 = *_hp; free(_hp); }
    (void)_t860;
    if (_t860) {
        U64 _t856 = U64_sub(self->count, start);
        (void)_t856;
        Str *_t857 = Str_substr(self, &(U64){start}, &(U64){_t856});
        (void)_t857;
        ;
        result = Str_concat(result, _t857);
        Str_delete(_t857, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t861 = 1;
    (void)_t861;
    Str *_t862 = Str_substr(self, i, &(U64){_t861});
    (void)_t862;
    ;
    return _t862;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t865; { Bool *_hp = (Bool *)Str_starts_with(self, prefix); _t865 = *_hp; free(_hp); }
    (void)_t865;
    if (_t865) {
        U64 _t863 = U64_sub(self->count, prefix->count);
        (void)_t863;
        Str *_t864 = Str_substr(self, &prefix->count, &(U64){_t863});
        (void)_t864;
        ;
        ;
        return _t864;
    }
    ;
    Str *_t866 = Str_clone(self);
    (void)_t866;
    return _t866;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t870; { Bool *_hp = (Bool *)Str_ends_with(self, suffix); _t870 = *_hp; free(_hp); }
    (void)_t870;
    if (_t870) {
        U64 _t867 = 0;
        (void)_t867;
        U64 _t868 = U64_sub(self->count, suffix->count);
        (void)_t868;
        Str *_t869 = Str_substr(self, &(U64){_t867}, &(U64){_t868});
        (void)_t869;
        ;
        ;
        ;
        return _t869;
    }
    ;
    Str *_t871 = Str_clone(self);
    (void)_t871;
    return _t871;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t872 = 2;
    (void)_t872;
    U8 *buf = malloc(_t872);
    (void)buf;
    ;
    U64 _t873 = 1;
    (void)_t873;
    memcpy(buf, byte, _t873);
    ;
    U64 *_t874 = malloc(sizeof(U64));
    *_t874 = 1;
    (void)_t874;
    void *_t875 = ptr_add(buf, DEREF(_t874));
    (void)_t875;
    I32 _t876 = 0;
    (void)_t876;
    U64 _t877 = 1;
    (void)_t877;
    memset(_t875, _t876, _t877);
    U64_delete(_t874, &(Bool){1});
    ;
    ;
    I64 _t878 = 1;
    (void)_t878;
    I64 _t879 = 1;
    (void)_t879;
    Str *_t880 = malloc(sizeof(Str));
    _t880->c_str = buf;
    _t880->count = _t878;
    _t880->cap = _t879;
    (void)_t880;
    ;
    ;
    return _t880;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t920 = 0;
    (void)_t920;
    Bool _t921 = U64_eq(self->count, _t920);
    (void)_t921;
    ;
    if (_t921) {
        Str *_t881 = Str_lit("Str", 3ULL);
        (void)_t881;
        U64 _t882; { U64 *_hp = (U64 *)Str_size(); _t882 = *_hp; free(_hp); }
        (void)_t882;
        U64 _t883 = 1;
        (void)_t883;
        Array *_va15 = Array_new(_t881, &(U64){_t882}, &(U64){_t883});
        (void)_va15;
        Str_delete(_t881, &(Bool){1});
        ;
        ;
        U64 _t884 = 0;
        (void)_t884;
        Str *_t885 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t885;
        Array_set(_va15, &(U64){_t884}, _t885);
        ;
        Str *_t886 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:224:37", 61ULL);
        (void)_t886;
        panic(_t886, _va15);
        Str_delete(_t886, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    Bool neg = 0;
    (void)neg;
    U64 *_t922 = malloc(sizeof(U64));
    *_t922 = 0;
    (void)_t922;
    U8 *first = Str_get(self, _t922);
    (void)first;
    U8 _t923 = 45;
    (void)_t923;
    Bool _t924 = U8_eq(DEREF(first), _t923);
    (void)_t924;
    U64_delete(_t922, &(Bool){1});
    ;
    if (_t924) {
        Bool _t887 = 1;
        (void)_t887;
        neg = _t887;
        ;
        U64 _t888 = 1;
        (void)_t888;
        *i = _t888;
        ;
    }
    ;
    Bool _t925 = U64_eq(DEREF(i), self->count);
    (void)_t925;
    if (_t925) {
        Str *_t889 = Str_lit("Str", 3ULL);
        (void)_t889;
        U64 _t890; { U64 *_hp = (U64 *)Str_size(); _t890 = *_hp; free(_hp); }
        (void)_t890;
        U64 _t891 = 1;
        (void)_t891;
        Array *_va16 = Array_new(_t889, &(U64){_t890}, &(U64){_t891});
        (void)_va16;
        Str_delete(_t889, &(Bool){1});
        ;
        ;
        U64 _t892 = 0;
        (void)_t892;
        Str *_t893 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t893;
        Array_set(_va16, &(U64){_t892}, _t893);
        ;
        Str *_t894 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:233:37", 61ULL);
        (void)_t894;
        panic(_t894, _va16);
        Str_delete(_t894, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond895; { Bool *_hp = (Bool *)U64_lt(i, &self->count); _wcond895 = *_hp; free(_hp); }
        (void)_wcond895;
        if (_wcond895) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        (void)ch;
        I64 _t906 = U8_to_i64(DEREF(ch));
        (void)_t906;
        I64 _t907 = 48;
        (void)_t907;
        I64 d = I64_sub(_t906, _t907);
        (void)d;
        ;
        ;
        I64 _t908 = 0;
        (void)_t908;
        I64 _t909 = 9;
        (void)_t909;
        Bool _t910; { Bool *_hp = (Bool *)I64_lt(&(I64){d}, &(I64){_t908}); _t910 = *_hp; free(_hp); }
        (void)_t910;
        ;
        Bool _t911; { Bool *_hp = (Bool *)I64_gt(&(I64){d}, &(I64){_t909}); _t911 = *_hp; free(_hp); }
        (void)_t911;
        ;
        Bool _t912 = Bool_or(_t910, _t911);
        (void)_t912;
        ;
        ;
        if (_t912) {
            Str *_t896 = Str_lit("Str", 3ULL);
            (void)_t896;
            U64 _t897; { U64 *_hp = (U64 *)Str_size(); _t897 = *_hp; free(_hp); }
            (void)_t897;
            U64 _t898 = 3;
            (void)_t898;
            Array *_va17 = Array_new(_t896, &(U64){_t897}, &(U64){_t898});
            (void)_va17;
            Str_delete(_t896, &(Bool){1});
            ;
            ;
            U64 _t899 = 0;
            (void)_t899;
            Str *_t900 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
            (void)_t900;
            Array_set(_va17, &(U64){_t899}, _t900);
            ;
            U64 _t901 = 1;
            (void)_t901;
            Str *_t902 = Str_clone(self);
            (void)_t902;
            Array_set(_va17, &(U64){_t901}, _t902);
            ;
            U64 _t903 = 2;
            (void)_t903;
            Str *_t904 = Str_lit("'", 1ULL);
            (void)_t904;
            Array_set(_va17, &(U64){_t903}, _t904);
            ;
            Str *_t905 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/str.til:238:23", 61ULL);
            (void)_t905;
            panic(_t905, _va17);
            Str_delete(_t905, &(Bool){1});
        }
        ;
        I64 _t913 = 10;
        (void)_t913;
        I64 _t914 = I64_mul(result, _t913);
        (void)_t914;
        ;
        I64 _t915 = I64_add(_t914, d);
        (void)_t915;
        ;
        ;
        result = _t915;
        ;
        U64 _t916 = 1;
        (void)_t916;
        U64 _t917 = U64_add(DEREF(i), _t916);
        (void)_t917;
        ;
        *i = _t917;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t918 = 0;
        (void)_t918;
        I64 _t919 = I64_sub(_t918, result);
        (void)_t919;
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t919; return _r; }
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
    I64 _t927; { I64 *_hp = (I64 *)Str_cmp(a, b); _t927 = *_hp; free(_hp); }
    (void)_t927;
    I64 _t928 = 0;
    (void)_t928;
    Bool _t929 = I64_eq(_t927, _t928);
    (void)_t929;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t929; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t930 = 0;
    (void)_t930;
    I64 _t931 = 1;
    (void)_t931;
    I64 _t932; { I64 *_hp = (I64 *)Str_cmp(a, b); _t932 = *_hp; free(_hp); }
    (void)_t932;
    I64 _t933 = I64_sub(_t930, _t931);
    (void)_t933;
    ;
    ;
    Bool _t934 = I64_eq(_t932, _t933);
    (void)_t934;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t934; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t935; { I64 *_hp = (I64 *)Str_cmp(a, b); _t935 = *_hp; free(_hp); }
    (void)_t935;
    I64 _t936 = 1;
    (void)_t936;
    Bool _t937 = I64_eq(_t935, _t936);
    (void)_t937;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t937; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t938; { Bool *_hp = (Bool *)Str_eq(a, b); _t938 = *_hp; free(_hp); }
    (void)_t938;
    Bool _t939 = Bool_not(_t938);
    (void)_t939;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t939; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t940; { Bool *_hp = (Bool *)Str_gt(a, b); _t940 = *_hp; free(_hp); }
    (void)_t940;
    Bool _t941 = Bool_not(_t940);
    (void)_t941;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t941; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t942; { Bool *_hp = (Bool *)Str_lt(a, b); _t942 = *_hp; free(_hp); }
    (void)_t942;
    Bool _t943 = Bool_not(_t942);
    (void)_t943;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t943; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    void *_t944 = malloc(DEREF(elem_size));
    (void)_t944;
    U64 _t945 = 0;
    (void)_t945;
    I64 _t946 = 1;
    (void)_t946;
    U64 _t947 = U64_clone(elem_size);
    (void)_t947;
    Vec *_t948 = malloc(sizeof(Vec));
    _t948->data = _t944;
    _t948->count = _t945;
    _t948->cap = _t946;
    _t948->elem_size = _t947;
    { Str *_ca = Str_clone(elem_type); _t948->elem_type = *_ca; free(_ca); }
    (void)_t948;
    ;
    ;
    ;
    return _t948;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t953 = U64_eq(self->count, self->cap);
    (void)_t953;
    if (_t953) {
        U64 _t949 = 2;
        (void)_t949;
        U64 new_cap = U64_mul(self->cap, _t949);
        (void)new_cap;
        ;
        U64 _t950 = U64_mul(new_cap, self->elem_size);
        (void)_t950;
        void *_t951 = realloc(self->data, _t950);
        (void)_t951;
        ;
        self->data = _t951;
        U64 _t952 = U64_clone(&(U64){new_cap});
        (void)_t952;
        ;
        self->cap = _t952;
        ;
    }
    ;
    U64 *_t954 = malloc(sizeof(U64)); *_t954 = U64_mul(self->count, self->elem_size);
    (void)_t954;
    void *_t955 = ptr_add(self->data, DEREF(_t954));
    (void)_t955;
    memcpy(_t955, val, self->elem_size);
    U64_delete(_t954, &(Bool){1});
    free(val);
    U64 _t956 = 1;
    (void)_t956;
    U64 _t957 = U64_add(self->count, _t956);
    (void)_t957;
    ;
    self->count = _t957;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    (void)i;
    Bool _t972; { Bool *_hp = (Bool *)U64_gte(i, &self->count); _t972 = *_hp; free(_hp); }
    (void)_t972;
    if (_t972) {
        Str *_t958 = Str_lit("Str", 3ULL);
        (void)_t958;
        U64 _t959; { U64 *_hp = (U64 *)Str_size(); _t959 = *_hp; free(_hp); }
        (void)_t959;
        U64 _t960 = 5;
        (void)_t960;
        Array *_va18 = Array_new(_t958, &(U64){_t959}, &(U64){_t960});
        (void)_va18;
        Str_delete(_t958, &(Bool){1});
        ;
        ;
        U64 _t961 = 0;
        (void)_t961;
        Str *_t962 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t962;
        Array_set(_va18, &(U64){_t961}, _t962);
        ;
        U64 _t963 = 1;
        (void)_t963;
        Str *_t964 = U64_to_str(DEREF(i));
        (void)_t964;
        Array_set(_va18, &(U64){_t963}, _t964);
        ;
        U64 _t965 = 2;
        (void)_t965;
        Str *_t966 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t966;
        Array_set(_va18, &(U64){_t965}, _t966);
        ;
        U64 _t967 = 3;
        (void)_t967;
        Str *_t968 = U64_to_str(self->count);
        (void)_t968;
        Array_set(_va18, &(U64){_t967}, _t968);
        ;
        U64 _t969 = 4;
        (void)_t969;
        Str *_t970 = Str_lit(")", 1ULL);
        (void)_t970;
        Array_set(_va18, &(U64){_t969}, _t970);
        ;
        Str *_t971 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/vec.til:31:19", 60ULL);
        (void)_t971;
        panic(_t971, _va18);
        Str_delete(_t971, &(Bool){1});
    }
    ;
    U64 *_t973 = malloc(sizeof(U64)); *_t973 = U64_mul(DEREF(i), self->elem_size);
    (void)_t973;
    void *_t974 = ptr_add(self->data, DEREF(_t973));
    (void)_t974;
    U64_delete(_t973, &(Bool){1});
    return _t974;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t988; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t988 = *_hp; free(_hp); }
    (void)_t988;
    Bool _t989 = Bool_not(_t988);
    (void)_t989;
    ;
    if (_t989) {
        {
            U64 _fi975 = 0;
            (void)_fi975;
            while (1) {
                U64 _t977 = 0;
                (void)_t977;
                Range *_t978 = Range_new(_t977, self->count);
                (void)_t978;
                ;
                U64 _t979; { U64 *_hp = (U64 *)Range_len(_t978); _t979 = *_hp; free(_hp); }
                (void)_t979;
                Range_delete(_t978, &(Bool){1});
                Bool _wcond976; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi975}, &(U64){_t979}); _wcond976 = *_hp; free(_hp); }
                (void)_wcond976;
                ;
                if (_wcond976) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t980 = 0;
                (void)_t980;
                Range *_t981 = Range_new(_t980, self->count);
                (void)_t981;
                ;
                U64 i; { U64 *_hp = (U64 *)Range_get(_t981, _fi975); i = *_hp; free(_hp); }
                (void)i;
                Range_delete(_t981, &(Bool){1});
                U64 _t982 = 1;
                (void)_t982;
                U64 _t983 = U64_add(_fi975, _t982);
                (void)_t983;
                ;
                _fi975 = _t983;
                ;
                U64 *_t984 = malloc(sizeof(U64)); *_t984 = U64_mul(i, self->elem_size);
                (void)_t984;
                ;
                void *_t985 = ptr_add(self->data, DEREF(_t984));
                (void)_t985;
                Bool _t986 = 0;
                (void)_t986;
                dyn_call_delete(&self->elem_type, _t985, &(Bool){_t986});
                U64_delete(_t984, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t990; { Bool *_hp = (Bool *)Str_is_empty(&self->elem_type); _t990 = *_hp; free(_hp); }
    (void)_t990;
    Bool _t991 = Bool_not(_t990);
    (void)_t991;
    ;
    if (_t991) {
        Bool _t987 = 0;
        (void)_t987;
        Str_delete(&self->elem_type, &(Bool){_t987});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1005 = U64_mul(self->cap, self->elem_size);
    (void)_t1005;
    U8 *new_data = malloc(_t1005);
    (void)new_data;
    ;
    {
        U64 _fi992 = 0;
        (void)_fi992;
        while (1) {
            U64 _t994 = 0;
            (void)_t994;
            Range *_t995 = Range_new(_t994, self->count);
            (void)_t995;
            ;
            U64 _t996; { U64 *_hp = (U64 *)Range_len(_t995); _t996 = *_hp; free(_hp); }
            (void)_t996;
            Range_delete(_t995, &(Bool){1});
            Bool _wcond993; { Bool *_hp = (Bool *)U64_lt(&(U64){_fi992}, &(U64){_t996}); _wcond993 = *_hp; free(_hp); }
            (void)_wcond993;
            ;
            if (_wcond993) {
            } else {
                ;
                break;
            }
            ;
            U64 _t997 = 0;
            (void)_t997;
            Range *_t998 = Range_new(_t997, self->count);
            (void)_t998;
            ;
            U64 i; { U64 *_hp = (U64 *)Range_get(_t998, _fi992); i = *_hp; free(_hp); }
            (void)i;
            Range_delete(_t998, &(Bool){1});
            U64 _t999 = 1;
            (void)_t999;
            U64 _t1000 = U64_add(_fi992, _t999);
            (void)_t1000;
            ;
            _fi992 = _t1000;
            ;
            U64 *_t1001 = malloc(sizeof(U64)); *_t1001 = U64_mul(i, self->elem_size);
            (void)_t1001;
            void *_t1002 = ptr_add(self->data, DEREF(_t1001));
            (void)_t1002;
            void *cloned = dyn_call_clone(&self->elem_type, _t1002);
            (void)cloned;
            U64_delete(_t1001, &(Bool){1});
            U64 *_t1003 = malloc(sizeof(U64)); *_t1003 = U64_mul(i, self->elem_size);
            (void)_t1003;
            ;
            void *_t1004 = ptr_add(new_data, DEREF(_t1003));
            (void)_t1004;
            memcpy(_t1004, cloned, self->elem_size);
            U64_delete(_t1003, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t1006 = malloc(sizeof(Vec));
    _t1006->data = new_data;
    _t1006->count = self->count;
    _t1006->cap = self->cap;
    _t1006->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t1006->elem_type = *_ca; free(_ca); }
    (void)_t1006;
    return _t1006;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    (void)s;
    (void)delim;
    Str *_t1024 = Str_lit("Str", 3ULL);
    (void)_t1024;
    U64 _t1025; { U64 *_hp = (U64 *)Str_size(); _t1025 = *_hp; free(_hp); }
    (void)_t1025;
    Vec *parts = Vec_new(_t1024, &(U64){_t1025});
    (void)parts;
    Str_delete(_t1024, &(Bool){1});
    ;
    U64 _t1026; { U64 *_hp = (U64 *)Str_len(delim); _t1026 = *_hp; free(_hp); }
    (void)_t1026;
    U64 _t1027 = 0;
    (void)_t1027;
    Bool _t1028 = U64_eq(_t1026, _t1027);
    (void)_t1028;
    ;
    ;
    if (_t1028) {
        Str *_t1008 = Str_clone(s);
        (void)_t1008;
        Vec_push(parts, _t1008);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    (void)start;
    U64 pos = 0;
    (void)pos;
    while (1) {
        U64 _t1018; { U64 *_hp = (U64 *)Str_len(s); _t1018 = *_hp; free(_hp); }
        (void)_t1018;
        U64 _t1019; { U64 *_hp = (U64 *)Str_len(delim); _t1019 = *_hp; free(_hp); }
        (void)_t1019;
        U64 _t1020 = U64_sub(_t1018, _t1019);
        (void)_t1020;
        ;
        ;
        Bool _wcond1009; { Bool *_hp = (Bool *)U64_lte(&(U64){pos}, &(U64){_t1020}); _wcond1009 = *_hp; free(_hp); }
        (void)_wcond1009;
        ;
        if (_wcond1009) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1021; { U64 *_hp = (U64 *)Str_len(delim); _t1021 = *_hp; free(_hp); }
        (void)_t1021;
        Str *_t1022 = Str_substr(s, &(U64){pos}, &(U64){_t1021});
        (void)_t1022;
        ;
        Bool _t1023; { Bool *_hp = (Bool *)Str_eq(_t1022, delim); _t1023 = *_hp; free(_hp); }
        (void)_t1023;
        Str_delete(_t1022, &(Bool){1});
        if (_t1023) {
            U64 _t1010 = U64_sub(pos, start);
            (void)_t1010;
            Str *_t1011 = Str_substr(s, &(U64){start}, &(U64){_t1010});
            (void)_t1011;
            ;
            Str *_t1012 = Str_clone(_t1011);
            (void)_t1012;
            Str_delete(_t1011, &(Bool){1});
            Vec_push(parts, _t1012);
            U64 _t1013; { U64 *_hp = (U64 *)Str_len(delim); _t1013 = *_hp; free(_hp); }
            (void)_t1013;
            U64 _t1014 = U64_add(pos, _t1013);
            (void)_t1014;
            ;
            start = _t1014;
            ;
            U64 _t1015 = U64_clone(&(U64){start});
            (void)_t1015;
            pos = _t1015;
            ;
        } else {
            U64 _t1016 = 1;
            (void)_t1016;
            U64 _t1017 = U64_add(pos, _t1016);
            (void)_t1017;
            ;
            pos = _t1017;
            ;
        }
        ;
    }
    ;
    U64 _t1029; { U64 *_hp = (U64 *)Str_len(s); _t1029 = *_hp; free(_hp); }
    (void)_t1029;
    U64 _t1030 = U64_sub(_t1029, start);
    (void)_t1030;
    ;
    Str *_t1031 = Str_substr(s, &(U64){start}, &(U64){_t1030});
    (void)_t1031;
    ;
    ;
    Str *_t1032 = Str_clone(_t1031);
    (void)_t1032;
    Str_delete(_t1031, &(Bool){1});
    Vec_push(parts, _t1032);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    (void)parts;
    (void)sep;
    U64 _t1040; { U64 *_hp = (U64 *)Vec_len(parts); _t1040 = *_hp; free(_hp); }
    (void)_t1040;
    U64 _t1041 = 0;
    (void)_t1041;
    Bool _t1042 = U64_eq(_t1040, _t1041);
    (void)_t1042;
    ;
    ;
    if (_t1042) {
        Str *_t1033 = Str_lit("", 0ULL);
        (void)_t1033;
        ;
        return _t1033;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    (void)i;
    while (1) {
        U64 _t1035; { U64 *_hp = (U64 *)Vec_len(parts); _t1035 = *_hp; free(_hp); }
        (void)_t1035;
        Bool _wcond1034; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1035}); _wcond1034 = *_hp; free(_hp); }
        (void)_wcond1034;
        ;
        if (_wcond1034) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1036 = 0;
        (void)_t1036;
        Bool _t1037; { Bool *_hp = (Bool *)U64_gt(i, &(U64){_t1036}); _t1037 = *_hp; free(_hp); }
        (void)_t1037;
        ;
        if (_t1037) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        (void)p;
        result = Str_concat(result, p);
        U64 _t1038 = 1;
        (void)_t1038;
        U64 _t1039 = U64_add(DEREF(i), _t1038);
        (void)_t1039;
        ;
        *i = _t1039;
        ;
    }
    U64_delete(i, &(Bool){1});
    return result;
}

Tuple * Tuple_new(void) {
    U64 _t1043 = 8;
    (void)_t1043;
    Str *_t1044 = Str_lit("Str", 3ULL);
    (void)_t1044;
    U64 _t1045; { U64 *_hp = (U64 *)Str_size(); _t1045 = *_hp; free(_hp); }
    (void)_t1045;
    Str *_t1046 = Str_lit("U64", 3ULL);
    (void)_t1046;
    U64 _t1047; { U64 *_hp = (U64 *)U64_size(); _t1047 = *_hp; free(_hp); }
    (void)_t1047;
    void *_t1048 = malloc(_t1043);
    (void)_t1048;
    ;
    U64 _t1049 = 0;
    (void)_t1049;
    I64 _t1050 = 8;
    (void)_t1050;
    Tuple *_t1051 = malloc(sizeof(Tuple));
    _t1051->data = _t1048;
    _t1051->total_size = _t1049;
    _t1051->cap = _t1050;
    { Vec *_ca = Vec_new(_t1044, &(U64){_t1045}); _t1051->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(_t1046, &(U64){_t1047}); _t1051->type_sizes = *_ca; free(_ca); }
    (void)_t1051;
    Str_delete(_t1044, &(Bool){1});
    ;
    Str_delete(_t1046, &(Bool){1});
    ;
    ;
    ;
    return _t1051;
}

U64 * Tuple_len(Tuple * self) {
    (void)self;
    U64 _t1052; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1052 = *_hp; free(_hp); }
    (void)_t1052;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t1052; return _r; }
}

void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val) {
    (void)self;
    (void)elem_type;
    (void)elem_size;
    (void)val;
    U64 new_total = U64_add(self->total_size, DEREF(elem_size));
    (void)new_total;
    Bool _t1059; { Bool *_hp = (Bool *)U64_gt(&(U64){new_total}, &self->cap); _t1059 = *_hp; free(_hp); }
    (void)_t1059;
    if (_t1059) {
        U64 _t1056 = 2;
        (void)_t1056;
        U64 new_cap = U64_mul(self->cap, _t1056);
        (void)new_cap;
        ;
        while (1) {
            Bool _wcond1053; { Bool *_hp = (Bool *)U64_lt(&(U64){new_cap}, &(U64){new_total}); _wcond1053 = *_hp; free(_hp); }
            (void)_wcond1053;
            if (_wcond1053) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1054 = 2;
            (void)_t1054;
            U64 _t1055 = U64_mul(new_cap, _t1054);
            (void)_t1055;
            ;
            new_cap = _t1055;
            ;
        }
        void *_t1057 = realloc(self->data, new_cap);
        (void)_t1057;
        self->data = _t1057;
        U64 _t1058 = U64_clone(&(U64){new_cap});
        (void)_t1058;
        ;
        self->cap = _t1058;
        ;
    }
    ;
    void *_t1060 = ptr_add(self->data, self->total_size);
    (void)_t1060;
    memcpy(_t1060, val, DEREF(elem_size));
    free(val);
    Str *_t1061 = Str_clone(elem_type);
    (void)_t1061;
    Vec_push(&self->type_names, _t1061);
    U64 _t1062 = U64_clone(elem_size);
    (void)_t1062;
    Vec_push(&self->type_sizes, ({ U64 *_oa = malloc(sizeof(U64)); *_oa = _t1062; _oa; }));
    U64 _t1063 = U64_clone(&(U64){new_total});
    (void)_t1063;
    ;
    self->total_size = _t1063;
    ;
}

void * Tuple_get(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    U64 _t1083; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1083 = *_hp; free(_hp); }
    (void)_t1083;
    Bool _t1084; { Bool *_hp = (Bool *)U64_gte(i, &(U64){_t1083}); _t1084 = *_hp; free(_hp); }
    (void)_t1084;
    ;
    if (_t1084) {
        Str *_t1064 = Str_lit("Str", 3ULL);
        (void)_t1064;
        U64 _t1065; { U64 *_hp = (U64 *)Str_size(); _t1065 = *_hp; free(_hp); }
        (void)_t1065;
        U64 _t1066 = 5;
        (void)_t1066;
        Array *_va19 = Array_new(_t1064, &(U64){_t1065}, &(U64){_t1066});
        (void)_va19;
        Str_delete(_t1064, &(Bool){1});
        ;
        ;
        U64 _t1067 = 0;
        (void)_t1067;
        Str *_t1068 = Str_lit("Tuple.get: index ", 17ULL);
        (void)_t1068;
        Array_set(_va19, &(U64){_t1067}, _t1068);
        ;
        U64 _t1069 = 1;
        (void)_t1069;
        Str *_t1070 = U64_to_str(DEREF(i));
        (void)_t1070;
        Array_set(_va19, &(U64){_t1069}, _t1070);
        ;
        U64 _t1071 = 2;
        (void)_t1071;
        Str *_t1072 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t1072;
        Array_set(_va19, &(U64){_t1071}, _t1072);
        ;
        U64 _t1073; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1073 = *_hp; free(_hp); }
        (void)_t1073;
        U64 _t1074 = 3;
        (void)_t1074;
        Str *_t1075 = U64_to_str(_t1073);
        (void)_t1075;
        ;
        Array_set(_va19, &(U64){_t1074}, _t1075);
        ;
        U64 _t1076 = 4;
        (void)_t1076;
        Str *_t1077 = Str_lit(")", 1ULL);
        (void)_t1077;
        Array_set(_va19, &(U64){_t1076}, _t1077);
        ;
        Str *_t1078 = Str_lit("/home/jt/sync/data_common/code/jt/til/src/core/tuple.til:36:19", 62ULL);
        (void)_t1078;
        panic(_t1078, _va19);
        Str_delete(_t1078, &(Bool){1});
    }
    ;
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    (void)offset;
    U64 *j = malloc(sizeof(U64));
    *j = 0;
    (void)j;
    while (1) {
        Bool _wcond1079; { Bool *_hp = (Bool *)U64_lt(j, i); _wcond1079 = *_hp; free(_hp); }
        (void)_wcond1079;
        if (_wcond1079) {
        } else {
            ;
            break;
        }
        ;
        U64 *sz = Vec_get(&self->type_sizes, j);
        (void)sz;
        U64 _t1080 = U64_add(DEREF(offset), DEREF(sz));
        (void)_t1080;
        *offset = _t1080;
        ;
        U64 _t1081 = 1;
        (void)_t1081;
        U64 _t1082 = U64_add(DEREF(j), _t1081);
        (void)_t1082;
        ;
        *j = _t1082;
        ;
    }
    U64_delete(j, &(Bool){1});
    void *_t1085 = ptr_add(self->data, DEREF(offset));
    (void)_t1085;
    U64_delete(offset, &(Bool){1});
    return _t1085;
}

Str * Tuple_type_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1086 = Vec_get(&self->type_names, i);
    (void)_t1086;
    return _t1086;
}

U64 * Tuple_size_at(Tuple * self, U64 * i) {
    (void)self;
    (void)i;
    void *_t1087 = Vec_get(&self->type_sizes, i);
    (void)_t1087;
    return _t1087;
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
        U64 _t1089; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1089 = *_hp; free(_hp); }
        (void)_t1089;
        Bool _wcond1088; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1089}); _wcond1088 = *_hp; free(_hp); }
        (void)_wcond1088;
        ;
        if (_wcond1088) {
        } else {
            ;
            break;
        }
        ;
        Str *tn = Vec_get(&self->type_names, i);
        (void)tn;
        U64 *ts = Vec_get(&self->type_sizes, i);
        (void)ts;
        void *_t1090 = ptr_add(self->data, DEREF(offset));
        (void)_t1090;
        Bool _t1091 = 0;
        (void)_t1091;
        dyn_call_delete(tn, _t1090, &(Bool){_t1091});
        ;
        U64 _t1092 = U64_add(DEREF(offset), DEREF(ts));
        (void)_t1092;
        *offset = _t1092;
        ;
        U64 _t1093 = 1;
        (void)_t1093;
        U64 _t1094 = U64_add(DEREF(i), _t1093);
        (void)_t1094;
        ;
        *i = _t1094;
        ;
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    free(self->data);
    Bool _t1095 = 0;
    (void)_t1095;
    Vec_delete(&self->type_names, &(Bool){_t1095});
    ;
    Bool _t1096 = 0;
    (void)_t1096;
    Vec_delete(&self->type_sizes, &(Bool){_t1096});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Tuple * Tuple_clone(Tuple * self) {
    (void)self;
    U64 new_cap = self->cap;
    (void)new_cap;
    U64 _t1106 = 0;
    (void)_t1106;
    Bool _t1107 = U64_eq(new_cap, _t1106);
    (void)_t1107;
    ;
    if (_t1107) {
        I64 _t1097 = 8;
        (void)_t1097;
        U64 _t1098; { U64 *_hp = (U64 *)U64_from_i64(&(I64){_t1097}); _t1098 = *_hp; free(_hp); }
        (void)_t1098;
        ;
        new_cap = _t1098;
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
        U64 _t1100; { U64 *_hp = (U64 *)Vec_len(&self->type_names); _t1100 = *_hp; free(_hp); }
        (void)_t1100;
        Bool _wcond1099; { Bool *_hp = (Bool *)U64_lt(i, &(U64){_t1100}); _wcond1099 = *_hp; free(_hp); }
        (void)_wcond1099;
        ;
        if (_wcond1099) {
        } else {
            ;
            break;
        }
        ;
        Str *tn = Vec_get(&self->type_names, i);
        (void)tn;
        U64 *ts = Vec_get(&self->type_sizes, i);
        (void)ts;
        void *_t1101 = ptr_add(self->data, DEREF(offset));
        (void)_t1101;
        void *cloned = dyn_call_clone(tn, _t1101);
        (void)cloned;
        void *_t1102 = ptr_add(new_data, DEREF(offset));
        (void)_t1102;
        memcpy(_t1102, cloned, DEREF(ts));
        free(cloned);
        U64 _t1103 = U64_add(DEREF(offset), DEREF(ts));
        (void)_t1103;
        *offset = _t1103;
        ;
        U64 _t1104 = 1;
        (void)_t1104;
        U64 _t1105 = U64_add(DEREF(i), _t1104);
        (void)_t1105;
        ;
        *i = _t1105;
        ;
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    U64 _t1108 = U64_clone(&(U64){new_cap});
    (void)_t1108;
    ;
    Vec *_t1109 = Vec_clone(&self->type_names);
    (void)_t1109;
    Vec *_t1110 = Vec_clone(&self->type_sizes);
    (void)_t1110;
    Tuple *_t1111 = malloc(sizeof(Tuple));
    _t1111->data = new_data;
    _t1111->total_size = self->total_size;
    _t1111->cap = _t1108;
    { Vec *_ca = Vec_clone(_t1109); _t1111->type_names = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(_t1110); _t1111->type_sizes = *_ca; free(_ca); }
    (void)_t1111;
    ;
    Vec_delete(_t1109, &(Bool){1});
    Vec_delete(_t1110, &(Bool){1});
    return _t1111;
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
    Bool _t1178; { Bool *_hp = (Bool *)TokenType_is_Eof(self); _t1178 = *_hp; free(_hp); }
    (void)_t1178;
    if (_t1178) {
        Bool _t1113; { Bool *_hp = (Bool *)TokenType_is_Eof(other); _t1113 = *_hp; free(_hp); }
        (void)_t1113;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1113; return _r; }
    }
    ;
    Bool _t1179; { Bool *_hp = (Bool *)TokenType_is_LParen(self); _t1179 = *_hp; free(_hp); }
    (void)_t1179;
    if (_t1179) {
        Bool _t1114; { Bool *_hp = (Bool *)TokenType_is_LParen(other); _t1114 = *_hp; free(_hp); }
        (void)_t1114;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1114; return _r; }
    }
    ;
    Bool _t1180; { Bool *_hp = (Bool *)TokenType_is_RParen(self); _t1180 = *_hp; free(_hp); }
    (void)_t1180;
    if (_t1180) {
        Bool _t1115; { Bool *_hp = (Bool *)TokenType_is_RParen(other); _t1115 = *_hp; free(_hp); }
        (void)_t1115;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1115; return _r; }
    }
    ;
    Bool _t1181; { Bool *_hp = (Bool *)TokenType_is_LBrace(self); _t1181 = *_hp; free(_hp); }
    (void)_t1181;
    if (_t1181) {
        Bool _t1116; { Bool *_hp = (Bool *)TokenType_is_LBrace(other); _t1116 = *_hp; free(_hp); }
        (void)_t1116;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1116; return _r; }
    }
    ;
    Bool _t1182; { Bool *_hp = (Bool *)TokenType_is_RBrace(self); _t1182 = *_hp; free(_hp); }
    (void)_t1182;
    if (_t1182) {
        Bool _t1117; { Bool *_hp = (Bool *)TokenType_is_RBrace(other); _t1117 = *_hp; free(_hp); }
        (void)_t1117;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1117; return _r; }
    }
    ;
    Bool _t1183; { Bool *_hp = (Bool *)TokenType_is_LBracket(self); _t1183 = *_hp; free(_hp); }
    (void)_t1183;
    if (_t1183) {
        Bool _t1118; { Bool *_hp = (Bool *)TokenType_is_LBracket(other); _t1118 = *_hp; free(_hp); }
        (void)_t1118;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1118; return _r; }
    }
    ;
    Bool _t1184; { Bool *_hp = (Bool *)TokenType_is_RBracket(self); _t1184 = *_hp; free(_hp); }
    (void)_t1184;
    if (_t1184) {
        Bool _t1119; { Bool *_hp = (Bool *)TokenType_is_RBracket(other); _t1119 = *_hp; free(_hp); }
        (void)_t1119;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1119; return _r; }
    }
    ;
    Bool _t1185; { Bool *_hp = (Bool *)TokenType_is_Comma(self); _t1185 = *_hp; free(_hp); }
    (void)_t1185;
    if (_t1185) {
        Bool _t1120; { Bool *_hp = (Bool *)TokenType_is_Comma(other); _t1120 = *_hp; free(_hp); }
        (void)_t1120;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1120; return _r; }
    }
    ;
    Bool _t1186; { Bool *_hp = (Bool *)TokenType_is_Colon(self); _t1186 = *_hp; free(_hp); }
    (void)_t1186;
    if (_t1186) {
        Bool _t1121; { Bool *_hp = (Bool *)TokenType_is_Colon(other); _t1121 = *_hp; free(_hp); }
        (void)_t1121;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1121; return _r; }
    }
    ;
    Bool _t1187; { Bool *_hp = (Bool *)TokenType_is_Question(self); _t1187 = *_hp; free(_hp); }
    (void)_t1187;
    if (_t1187) {
        Bool _t1122; { Bool *_hp = (Bool *)TokenType_is_Question(other); _t1122 = *_hp; free(_hp); }
        (void)_t1122;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1122; return _r; }
    }
    ;
    Bool _t1188; { Bool *_hp = (Bool *)TokenType_is_Bang(self); _t1188 = *_hp; free(_hp); }
    (void)_t1188;
    if (_t1188) {
        Bool _t1123; { Bool *_hp = (Bool *)TokenType_is_Bang(other); _t1123 = *_hp; free(_hp); }
        (void)_t1123;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1123; return _r; }
    }
    ;
    Bool _t1189; { Bool *_hp = (Bool *)TokenType_is_Minus(self); _t1189 = *_hp; free(_hp); }
    (void)_t1189;
    if (_t1189) {
        Bool _t1124; { Bool *_hp = (Bool *)TokenType_is_Minus(other); _t1124 = *_hp; free(_hp); }
        (void)_t1124;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1124; return _r; }
    }
    ;
    Bool _t1190; { Bool *_hp = (Bool *)TokenType_is_Plus(self); _t1190 = *_hp; free(_hp); }
    (void)_t1190;
    if (_t1190) {
        Bool _t1125; { Bool *_hp = (Bool *)TokenType_is_Plus(other); _t1125 = *_hp; free(_hp); }
        (void)_t1125;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1125; return _r; }
    }
    ;
    Bool _t1191; { Bool *_hp = (Bool *)TokenType_is_Star(self); _t1191 = *_hp; free(_hp); }
    (void)_t1191;
    if (_t1191) {
        Bool _t1126; { Bool *_hp = (Bool *)TokenType_is_Star(other); _t1126 = *_hp; free(_hp); }
        (void)_t1126;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1126; return _r; }
    }
    ;
    Bool _t1192; { Bool *_hp = (Bool *)TokenType_is_Slash(self); _t1192 = *_hp; free(_hp); }
    (void)_t1192;
    if (_t1192) {
        Bool _t1127; { Bool *_hp = (Bool *)TokenType_is_Slash(other); _t1127 = *_hp; free(_hp); }
        (void)_t1127;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1127; return _r; }
    }
    ;
    Bool _t1193; { Bool *_hp = (Bool *)TokenType_is_Dot(self); _t1193 = *_hp; free(_hp); }
    (void)_t1193;
    if (_t1193) {
        Bool _t1128; { Bool *_hp = (Bool *)TokenType_is_Dot(other); _t1128 = *_hp; free(_hp); }
        (void)_t1128;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1128; return _r; }
    }
    ;
    Bool _t1194; { Bool *_hp = (Bool *)TokenType_is_DotDot(self); _t1194 = *_hp; free(_hp); }
    (void)_t1194;
    if (_t1194) {
        Bool _t1129; { Bool *_hp = (Bool *)TokenType_is_DotDot(other); _t1129 = *_hp; free(_hp); }
        (void)_t1129;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1129; return _r; }
    }
    ;
    Bool _t1195; { Bool *_hp = (Bool *)TokenType_is_Eq(self); _t1195 = *_hp; free(_hp); }
    (void)_t1195;
    if (_t1195) {
        Bool _t1130; { Bool *_hp = (Bool *)TokenType_is_Eq(other); _t1130 = *_hp; free(_hp); }
        (void)_t1130;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1130; return _r; }
    }
    ;
    Bool _t1196; { Bool *_hp = (Bool *)TokenType_is_EqEq(self); _t1196 = *_hp; free(_hp); }
    (void)_t1196;
    if (_t1196) {
        Bool _t1131; { Bool *_hp = (Bool *)TokenType_is_EqEq(other); _t1131 = *_hp; free(_hp); }
        (void)_t1131;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1131; return _r; }
    }
    ;
    Bool _t1197; { Bool *_hp = (Bool *)TokenType_is_Neq(self); _t1197 = *_hp; free(_hp); }
    (void)_t1197;
    if (_t1197) {
        Bool _t1132; { Bool *_hp = (Bool *)TokenType_is_Neq(other); _t1132 = *_hp; free(_hp); }
        (void)_t1132;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1132; return _r; }
    }
    ;
    Bool _t1198; { Bool *_hp = (Bool *)TokenType_is_Lt(self); _t1198 = *_hp; free(_hp); }
    (void)_t1198;
    if (_t1198) {
        Bool _t1133; { Bool *_hp = (Bool *)TokenType_is_Lt(other); _t1133 = *_hp; free(_hp); }
        (void)_t1133;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1133; return _r; }
    }
    ;
    Bool _t1199; { Bool *_hp = (Bool *)TokenType_is_LtEq(self); _t1199 = *_hp; free(_hp); }
    (void)_t1199;
    if (_t1199) {
        Bool _t1134; { Bool *_hp = (Bool *)TokenType_is_LtEq(other); _t1134 = *_hp; free(_hp); }
        (void)_t1134;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1134; return _r; }
    }
    ;
    Bool _t1200; { Bool *_hp = (Bool *)TokenType_is_Gt(self); _t1200 = *_hp; free(_hp); }
    (void)_t1200;
    if (_t1200) {
        Bool _t1135; { Bool *_hp = (Bool *)TokenType_is_Gt(other); _t1135 = *_hp; free(_hp); }
        (void)_t1135;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1135; return _r; }
    }
    ;
    Bool _t1201; { Bool *_hp = (Bool *)TokenType_is_GtEq(self); _t1201 = *_hp; free(_hp); }
    (void)_t1201;
    if (_t1201) {
        Bool _t1136; { Bool *_hp = (Bool *)TokenType_is_GtEq(other); _t1136 = *_hp; free(_hp); }
        (void)_t1136;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1136; return _r; }
    }
    ;
    Bool _t1202; { Bool *_hp = (Bool *)TokenType_is_ColonEq(self); _t1202 = *_hp; free(_hp); }
    (void)_t1202;
    if (_t1202) {
        Bool _t1137; { Bool *_hp = (Bool *)TokenType_is_ColonEq(other); _t1137 = *_hp; free(_hp); }
        (void)_t1137;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1137; return _r; }
    }
    ;
    Bool _t1203; { Bool *_hp = (Bool *)TokenType_is_Ident(self); _t1203 = *_hp; free(_hp); }
    (void)_t1203;
    if (_t1203) {
        Bool _t1138; { Bool *_hp = (Bool *)TokenType_is_Ident(other); _t1138 = *_hp; free(_hp); }
        (void)_t1138;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1138; return _r; }
    }
    ;
    Bool _t1204; { Bool *_hp = (Bool *)TokenType_is_StringTok(self); _t1204 = *_hp; free(_hp); }
    (void)_t1204;
    if (_t1204) {
        Bool _t1139; { Bool *_hp = (Bool *)TokenType_is_StringTok(other); _t1139 = *_hp; free(_hp); }
        (void)_t1139;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1139; return _r; }
    }
    ;
    Bool _t1205; { Bool *_hp = (Bool *)TokenType_is_Number(self); _t1205 = *_hp; free(_hp); }
    (void)_t1205;
    if (_t1205) {
        Bool _t1140; { Bool *_hp = (Bool *)TokenType_is_Number(other); _t1140 = *_hp; free(_hp); }
        (void)_t1140;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1140; return _r; }
    }
    ;
    Bool _t1206; { Bool *_hp = (Bool *)TokenType_is_Char(self); _t1206 = *_hp; free(_hp); }
    (void)_t1206;
    if (_t1206) {
        Bool _t1141; { Bool *_hp = (Bool *)TokenType_is_Char(other); _t1141 = *_hp; free(_hp); }
        (void)_t1141;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1141; return _r; }
    }
    ;
    Bool _t1207; { Bool *_hp = (Bool *)TokenType_is_KwMode(self); _t1207 = *_hp; free(_hp); }
    (void)_t1207;
    if (_t1207) {
        Bool _t1142; { Bool *_hp = (Bool *)TokenType_is_KwMode(other); _t1142 = *_hp; free(_hp); }
        (void)_t1142;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1142; return _r; }
    }
    ;
    Bool _t1208; { Bool *_hp = (Bool *)TokenType_is_KwMut(self); _t1208 = *_hp; free(_hp); }
    (void)_t1208;
    if (_t1208) {
        Bool _t1143; { Bool *_hp = (Bool *)TokenType_is_KwMut(other); _t1143 = *_hp; free(_hp); }
        (void)_t1143;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1143; return _r; }
    }
    ;
    Bool _t1209; { Bool *_hp = (Bool *)TokenType_is_KwOwn(self); _t1209 = *_hp; free(_hp); }
    (void)_t1209;
    if (_t1209) {
        Bool _t1144; { Bool *_hp = (Bool *)TokenType_is_KwOwn(other); _t1144 = *_hp; free(_hp); }
        (void)_t1144;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1144; return _r; }
    }
    ;
    Bool _t1210; { Bool *_hp = (Bool *)TokenType_is_KwRef(self); _t1210 = *_hp; free(_hp); }
    (void)_t1210;
    if (_t1210) {
        Bool _t1145; { Bool *_hp = (Bool *)TokenType_is_KwRef(other); _t1145 = *_hp; free(_hp); }
        (void)_t1145;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1145; return _r; }
    }
    ;
    Bool _t1211; { Bool *_hp = (Bool *)TokenType_is_KwShallow(self); _t1211 = *_hp; free(_hp); }
    (void)_t1211;
    if (_t1211) {
        Bool _t1146; { Bool *_hp = (Bool *)TokenType_is_KwShallow(other); _t1146 = *_hp; free(_hp); }
        (void)_t1146;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1146; return _r; }
    }
    ;
    Bool _t1212; { Bool *_hp = (Bool *)TokenType_is_KwStruct(self); _t1212 = *_hp; free(_hp); }
    (void)_t1212;
    if (_t1212) {
        Bool _t1147; { Bool *_hp = (Bool *)TokenType_is_KwStruct(other); _t1147 = *_hp; free(_hp); }
        (void)_t1147;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1147; return _r; }
    }
    ;
    Bool _t1213; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(self); _t1213 = *_hp; free(_hp); }
    (void)_t1213;
    if (_t1213) {
        Bool _t1148; { Bool *_hp = (Bool *)TokenType_is_KwExtStruct(other); _t1148 = *_hp; free(_hp); }
        (void)_t1148;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1148; return _r; }
    }
    ;
    Bool _t1214; { Bool *_hp = (Bool *)TokenType_is_KwEnum(self); _t1214 = *_hp; free(_hp); }
    (void)_t1214;
    if (_t1214) {
        Bool _t1149; { Bool *_hp = (Bool *)TokenType_is_KwEnum(other); _t1149 = *_hp; free(_hp); }
        (void)_t1149;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1149; return _r; }
    }
    ;
    Bool _t1215; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(self); _t1215 = *_hp; free(_hp); }
    (void)_t1215;
    if (_t1215) {
        Bool _t1150; { Bool *_hp = (Bool *)TokenType_is_KwNamespace(other); _t1150 = *_hp; free(_hp); }
        (void)_t1150;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1150; return _r; }
    }
    ;
    Bool _t1216; { Bool *_hp = (Bool *)TokenType_is_KwFunc(self); _t1216 = *_hp; free(_hp); }
    (void)_t1216;
    if (_t1216) {
        Bool _t1151; { Bool *_hp = (Bool *)TokenType_is_KwFunc(other); _t1151 = *_hp; free(_hp); }
        (void)_t1151;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1151; return _r; }
    }
    ;
    Bool _t1217; { Bool *_hp = (Bool *)TokenType_is_KwProc(self); _t1217 = *_hp; free(_hp); }
    (void)_t1217;
    if (_t1217) {
        Bool _t1152; { Bool *_hp = (Bool *)TokenType_is_KwProc(other); _t1152 = *_hp; free(_hp); }
        (void)_t1152;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1152; return _r; }
    }
    ;
    Bool _t1218; { Bool *_hp = (Bool *)TokenType_is_KwTest(self); _t1218 = *_hp; free(_hp); }
    (void)_t1218;
    if (_t1218) {
        Bool _t1153; { Bool *_hp = (Bool *)TokenType_is_KwTest(other); _t1153 = *_hp; free(_hp); }
        (void)_t1153;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1153; return _r; }
    }
    ;
    Bool _t1219; { Bool *_hp = (Bool *)TokenType_is_KwMacro(self); _t1219 = *_hp; free(_hp); }
    (void)_t1219;
    if (_t1219) {
        Bool _t1154; { Bool *_hp = (Bool *)TokenType_is_KwMacro(other); _t1154 = *_hp; free(_hp); }
        (void)_t1154;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1154; return _r; }
    }
    ;
    Bool _t1220; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(self); _t1220 = *_hp; free(_hp); }
    (void)_t1220;
    if (_t1220) {
        Bool _t1155; { Bool *_hp = (Bool *)TokenType_is_KwExtFunc(other); _t1155 = *_hp; free(_hp); }
        (void)_t1155;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1155; return _r; }
    }
    ;
    Bool _t1221; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(self); _t1221 = *_hp; free(_hp); }
    (void)_t1221;
    if (_t1221) {
        Bool _t1156; { Bool *_hp = (Bool *)TokenType_is_KwExtProc(other); _t1156 = *_hp; free(_hp); }
        (void)_t1156;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1156; return _r; }
    }
    ;
    Bool _t1222; { Bool *_hp = (Bool *)TokenType_is_KwReturns(self); _t1222 = *_hp; free(_hp); }
    (void)_t1222;
    if (_t1222) {
        Bool _t1157; { Bool *_hp = (Bool *)TokenType_is_KwReturns(other); _t1157 = *_hp; free(_hp); }
        (void)_t1157;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1157; return _r; }
    }
    ;
    Bool _t1223; { Bool *_hp = (Bool *)TokenType_is_KwThrows(self); _t1223 = *_hp; free(_hp); }
    (void)_t1223;
    if (_t1223) {
        Bool _t1158; { Bool *_hp = (Bool *)TokenType_is_KwThrows(other); _t1158 = *_hp; free(_hp); }
        (void)_t1158;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1158; return _r; }
    }
    ;
    Bool _t1224; { Bool *_hp = (Bool *)TokenType_is_KwIf(self); _t1224 = *_hp; free(_hp); }
    (void)_t1224;
    if (_t1224) {
        Bool _t1159; { Bool *_hp = (Bool *)TokenType_is_KwIf(other); _t1159 = *_hp; free(_hp); }
        (void)_t1159;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1159; return _r; }
    }
    ;
    Bool _t1225; { Bool *_hp = (Bool *)TokenType_is_KwElse(self); _t1225 = *_hp; free(_hp); }
    (void)_t1225;
    if (_t1225) {
        Bool _t1160; { Bool *_hp = (Bool *)TokenType_is_KwElse(other); _t1160 = *_hp; free(_hp); }
        (void)_t1160;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1160; return _r; }
    }
    ;
    Bool _t1226; { Bool *_hp = (Bool *)TokenType_is_KwWhile(self); _t1226 = *_hp; free(_hp); }
    (void)_t1226;
    if (_t1226) {
        Bool _t1161; { Bool *_hp = (Bool *)TokenType_is_KwWhile(other); _t1161 = *_hp; free(_hp); }
        (void)_t1161;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1161; return _r; }
    }
    ;
    Bool _t1227; { Bool *_hp = (Bool *)TokenType_is_KwFor(self); _t1227 = *_hp; free(_hp); }
    (void)_t1227;
    if (_t1227) {
        Bool _t1162; { Bool *_hp = (Bool *)TokenType_is_KwFor(other); _t1162 = *_hp; free(_hp); }
        (void)_t1162;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1162; return _r; }
    }
    ;
    Bool _t1228; { Bool *_hp = (Bool *)TokenType_is_KwIn(self); _t1228 = *_hp; free(_hp); }
    (void)_t1228;
    if (_t1228) {
        Bool _t1163; { Bool *_hp = (Bool *)TokenType_is_KwIn(other); _t1163 = *_hp; free(_hp); }
        (void)_t1163;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1163; return _r; }
    }
    ;
    Bool _t1229; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(self); _t1229 = *_hp; free(_hp); }
    (void)_t1229;
    if (_t1229) {
        Bool _t1164; { Bool *_hp = (Bool *)TokenType_is_KwSwitch(other); _t1164 = *_hp; free(_hp); }
        (void)_t1164;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1164; return _r; }
    }
    ;
    Bool _t1230; { Bool *_hp = (Bool *)TokenType_is_KwMatch(self); _t1230 = *_hp; free(_hp); }
    (void)_t1230;
    if (_t1230) {
        Bool _t1165; { Bool *_hp = (Bool *)TokenType_is_KwMatch(other); _t1165 = *_hp; free(_hp); }
        (void)_t1165;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1165; return _r; }
    }
    ;
    Bool _t1231; { Bool *_hp = (Bool *)TokenType_is_KwCase(self); _t1231 = *_hp; free(_hp); }
    (void)_t1231;
    if (_t1231) {
        Bool _t1166; { Bool *_hp = (Bool *)TokenType_is_KwCase(other); _t1166 = *_hp; free(_hp); }
        (void)_t1166;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1166; return _r; }
    }
    ;
    Bool _t1232; { Bool *_hp = (Bool *)TokenType_is_KwDefault(self); _t1232 = *_hp; free(_hp); }
    (void)_t1232;
    if (_t1232) {
        Bool _t1167; { Bool *_hp = (Bool *)TokenType_is_KwDefault(other); _t1167 = *_hp; free(_hp); }
        (void)_t1167;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1167; return _r; }
    }
    ;
    Bool _t1233; { Bool *_hp = (Bool *)TokenType_is_KwReturn(self); _t1233 = *_hp; free(_hp); }
    (void)_t1233;
    if (_t1233) {
        Bool _t1168; { Bool *_hp = (Bool *)TokenType_is_KwReturn(other); _t1168 = *_hp; free(_hp); }
        (void)_t1168;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1168; return _r; }
    }
    ;
    Bool _t1234; { Bool *_hp = (Bool *)TokenType_is_KwThrow(self); _t1234 = *_hp; free(_hp); }
    (void)_t1234;
    if (_t1234) {
        Bool _t1169; { Bool *_hp = (Bool *)TokenType_is_KwThrow(other); _t1169 = *_hp; free(_hp); }
        (void)_t1169;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1169; return _r; }
    }
    ;
    Bool _t1235; { Bool *_hp = (Bool *)TokenType_is_KwCatch(self); _t1235 = *_hp; free(_hp); }
    (void)_t1235;
    if (_t1235) {
        Bool _t1170; { Bool *_hp = (Bool *)TokenType_is_KwCatch(other); _t1170 = *_hp; free(_hp); }
        (void)_t1170;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1170; return _r; }
    }
    ;
    Bool _t1236; { Bool *_hp = (Bool *)TokenType_is_KwBreak(self); _t1236 = *_hp; free(_hp); }
    (void)_t1236;
    if (_t1236) {
        Bool _t1171; { Bool *_hp = (Bool *)TokenType_is_KwBreak(other); _t1171 = *_hp; free(_hp); }
        (void)_t1171;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1171; return _r; }
    }
    ;
    Bool _t1237; { Bool *_hp = (Bool *)TokenType_is_KwContinue(self); _t1237 = *_hp; free(_hp); }
    (void)_t1237;
    if (_t1237) {
        Bool _t1172; { Bool *_hp = (Bool *)TokenType_is_KwContinue(other); _t1172 = *_hp; free(_hp); }
        (void)_t1172;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1172; return _r; }
    }
    ;
    Bool _t1238; { Bool *_hp = (Bool *)TokenType_is_KwDefer(self); _t1238 = *_hp; free(_hp); }
    (void)_t1238;
    if (_t1238) {
        Bool _t1173; { Bool *_hp = (Bool *)TokenType_is_KwDefer(other); _t1173 = *_hp; free(_hp); }
        (void)_t1173;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1173; return _r; }
    }
    ;
    Bool _t1239; { Bool *_hp = (Bool *)TokenType_is_KwTrue(self); _t1239 = *_hp; free(_hp); }
    (void)_t1239;
    if (_t1239) {
        Bool _t1174; { Bool *_hp = (Bool *)TokenType_is_KwTrue(other); _t1174 = *_hp; free(_hp); }
        (void)_t1174;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1174; return _r; }
    }
    ;
    Bool _t1240; { Bool *_hp = (Bool *)TokenType_is_KwFalse(self); _t1240 = *_hp; free(_hp); }
    (void)_t1240;
    if (_t1240) {
        Bool _t1175; { Bool *_hp = (Bool *)TokenType_is_KwFalse(other); _t1175 = *_hp; free(_hp); }
        (void)_t1175;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1175; return _r; }
    }
    ;
    Bool _t1241; { Bool *_hp = (Bool *)TokenType_is_KwNull(self); _t1241 = *_hp; free(_hp); }
    (void)_t1241;
    if (_t1241) {
        Bool _t1176; { Bool *_hp = (Bool *)TokenType_is_KwNull(other); _t1176 = *_hp; free(_hp); }
        (void)_t1176;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1176; return _r; }
    }
    ;
    Bool _t1242; { Bool *_hp = (Bool *)TokenType_is_Error(self); _t1242 = *_hp; free(_hp); }
    (void)_t1242;
    if (_t1242) {
        Bool _t1177; { Bool *_hp = (Bool *)TokenType_is_Error(other); _t1177 = *_hp; free(_hp); }
        (void)_t1177;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1177; return _r; }
    }
    ;
    Bool _t1243 = 0;
    (void)_t1243;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1243; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1244; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1244 = *_hp; free(_hp); }
    (void)_t1244;
    if (_t1244) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1245; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1245 = *_hp; free(_hp); }
    (void)_t1245;
    if (_t1245) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1246; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1246 = *_hp; free(_hp); }
    (void)_t1246;
    if (_t1246) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1247; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1247 = *_hp; free(_hp); }
    (void)_t1247;
    if (_t1247) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1248; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1248 = *_hp; free(_hp); }
    (void)_t1248;
    if (_t1248) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1249; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1249 = *_hp; free(_hp); }
    (void)_t1249;
    if (_t1249) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1250; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1250 = *_hp; free(_hp); }
    (void)_t1250;
    if (_t1250) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1251; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1251 = *_hp; free(_hp); }
    (void)_t1251;
    if (_t1251) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1252; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1252 = *_hp; free(_hp); }
    (void)_t1252;
    if (_t1252) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1253; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1253 = *_hp; free(_hp); }
    (void)_t1253;
    if (_t1253) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1254; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1254 = *_hp; free(_hp); }
    (void)_t1254;
    if (_t1254) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1255; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1255 = *_hp; free(_hp); }
    (void)_t1255;
    if (_t1255) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1256; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1256 = *_hp; free(_hp); }
    (void)_t1256;
    if (_t1256) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1257; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1257 = *_hp; free(_hp); }
    (void)_t1257;
    if (_t1257) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1258; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1258 = *_hp; free(_hp); }
    (void)_t1258;
    if (_t1258) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1259; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1259 = *_hp; free(_hp); }
    (void)_t1259;
    if (_t1259) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1260; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1260 = *_hp; free(_hp); }
    (void)_t1260;
    if (_t1260) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1261; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1261 = *_hp; free(_hp); }
    (void)_t1261;
    if (_t1261) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1262; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1262 = *_hp; free(_hp); }
    (void)_t1262;
    if (_t1262) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1263; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1263 = *_hp; free(_hp); }
    (void)_t1263;
    if (_t1263) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1264; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1264 = *_hp; free(_hp); }
    (void)_t1264;
    if (_t1264) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1265; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1265 = *_hp; free(_hp); }
    (void)_t1265;
    if (_t1265) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1266; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1266 = *_hp; free(_hp); }
    (void)_t1266;
    if (_t1266) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1267; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1267 = *_hp; free(_hp); }
    (void)_t1267;
    if (_t1267) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1268; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1268 = *_hp; free(_hp); }
    (void)_t1268;
    if (_t1268) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1269; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1269 = *_hp; free(_hp); }
    (void)_t1269;
    if (_t1269) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1270; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1270 = *_hp; free(_hp); }
    (void)_t1270;
    if (_t1270) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1271; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1271 = *_hp; free(_hp); }
    (void)_t1271;
    if (_t1271) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1272; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1272 = *_hp; free(_hp); }
    (void)_t1272;
    if (_t1272) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1273; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1273 = *_hp; free(_hp); }
    (void)_t1273;
    if (_t1273) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1274; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1274 = *_hp; free(_hp); }
    (void)_t1274;
    if (_t1274) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1275; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1275 = *_hp; free(_hp); }
    (void)_t1275;
    if (_t1275) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1276; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1276 = *_hp; free(_hp); }
    (void)_t1276;
    if (_t1276) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1277; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1277 = *_hp; free(_hp); }
    (void)_t1277;
    if (_t1277) {
        ;
        return TokenType_KwShallow();
    }
    ;
    Bool _t1278; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1278 = *_hp; free(_hp); }
    (void)_t1278;
    if (_t1278) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1279; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1279 = *_hp; free(_hp); }
    (void)_t1279;
    if (_t1279) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1280; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1280 = *_hp; free(_hp); }
    (void)_t1280;
    if (_t1280) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1281; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1281 = *_hp; free(_hp); }
    (void)_t1281;
    if (_t1281) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1282; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1282 = *_hp; free(_hp); }
    (void)_t1282;
    if (_t1282) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1283; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1283 = *_hp; free(_hp); }
    (void)_t1283;
    if (_t1283) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1284; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1284 = *_hp; free(_hp); }
    (void)_t1284;
    if (_t1284) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1285; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1285 = *_hp; free(_hp); }
    (void)_t1285;
    if (_t1285) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1286; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1286 = *_hp; free(_hp); }
    (void)_t1286;
    if (_t1286) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1287; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1287 = *_hp; free(_hp); }
    (void)_t1287;
    if (_t1287) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1288; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1288 = *_hp; free(_hp); }
    (void)_t1288;
    if (_t1288) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1289; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1289 = *_hp; free(_hp); }
    (void)_t1289;
    if (_t1289) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1290; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1290 = *_hp; free(_hp); }
    (void)_t1290;
    if (_t1290) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1291; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1291 = *_hp; free(_hp); }
    (void)_t1291;
    if (_t1291) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1292; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1292 = *_hp; free(_hp); }
    (void)_t1292;
    if (_t1292) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1293; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1293 = *_hp; free(_hp); }
    (void)_t1293;
    if (_t1293) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1294; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1294 = *_hp; free(_hp); }
    (void)_t1294;
    if (_t1294) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1295; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1295 = *_hp; free(_hp); }
    (void)_t1295;
    if (_t1295) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1296; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1296 = *_hp; free(_hp); }
    (void)_t1296;
    if (_t1296) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1297; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1297 = *_hp; free(_hp); }
    (void)_t1297;
    if (_t1297) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1298; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1298 = *_hp; free(_hp); }
    (void)_t1298;
    if (_t1298) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1299; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1299 = *_hp; free(_hp); }
    (void)_t1299;
    if (_t1299) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1300; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1300 = *_hp; free(_hp); }
    (void)_t1300;
    if (_t1300) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1301; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1301 = *_hp; free(_hp); }
    (void)_t1301;
    if (_t1301) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1302; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1302 = *_hp; free(_hp); }
    (void)_t1302;
    if (_t1302) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1303; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1303 = *_hp; free(_hp); }
    (void)_t1303;
    if (_t1303) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1304; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1304 = *_hp; free(_hp); }
    (void)_t1304;
    if (_t1304) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1305; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1305 = *_hp; free(_hp); }
    (void)_t1305;
    if (_t1305) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1306; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1306 = *_hp; free(_hp); }
    (void)_t1306;
    if (_t1306) {
        ;
        return TokenType_KwFalse();
    }
    ;
    Bool _t1307; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1307 = *_hp; free(_hp); }
    (void)_t1307;
    if (_t1307) {
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
    Bool _t1373; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eof()); _t1373 = *_hp; free(_hp); }
    (void)_t1373;
    if (_t1373) {
        Str *_t1308 = Str_lit("Eof", 3ULL);
        (void)_t1308;
        ;
        return _t1308;
    }
    ;
    Bool _t1374; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LParen()); _t1374 = *_hp; free(_hp); }
    (void)_t1374;
    if (_t1374) {
        Str *_t1309 = Str_lit("LParen", 6ULL);
        (void)_t1309;
        ;
        return _t1309;
    }
    ;
    Bool _t1375; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RParen()); _t1375 = *_hp; free(_hp); }
    (void)_t1375;
    if (_t1375) {
        Str *_t1310 = Str_lit("RParen", 6ULL);
        (void)_t1310;
        ;
        return _t1310;
    }
    ;
    Bool _t1376; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBrace()); _t1376 = *_hp; free(_hp); }
    (void)_t1376;
    if (_t1376) {
        Str *_t1311 = Str_lit("LBrace", 6ULL);
        (void)_t1311;
        ;
        return _t1311;
    }
    ;
    Bool _t1377; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBrace()); _t1377 = *_hp; free(_hp); }
    (void)_t1377;
    if (_t1377) {
        Str *_t1312 = Str_lit("RBrace", 6ULL);
        (void)_t1312;
        ;
        return _t1312;
    }
    ;
    Bool _t1378; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LBracket()); _t1378 = *_hp; free(_hp); }
    (void)_t1378;
    if (_t1378) {
        Str *_t1313 = Str_lit("LBracket", 8ULL);
        (void)_t1313;
        ;
        return _t1313;
    }
    ;
    Bool _t1379; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_RBracket()); _t1379 = *_hp; free(_hp); }
    (void)_t1379;
    if (_t1379) {
        Str *_t1314 = Str_lit("RBracket", 8ULL);
        (void)_t1314;
        ;
        return _t1314;
    }
    ;
    Bool _t1380; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Comma()); _t1380 = *_hp; free(_hp); }
    (void)_t1380;
    if (_t1380) {
        Str *_t1315 = Str_lit("Comma", 5ULL);
        (void)_t1315;
        ;
        return _t1315;
    }
    ;
    Bool _t1381; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Colon()); _t1381 = *_hp; free(_hp); }
    (void)_t1381;
    if (_t1381) {
        Str *_t1316 = Str_lit("Colon", 5ULL);
        (void)_t1316;
        ;
        return _t1316;
    }
    ;
    Bool _t1382; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Question()); _t1382 = *_hp; free(_hp); }
    (void)_t1382;
    if (_t1382) {
        Str *_t1317 = Str_lit("Question", 8ULL);
        (void)_t1317;
        ;
        return _t1317;
    }
    ;
    Bool _t1383; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Bang()); _t1383 = *_hp; free(_hp); }
    (void)_t1383;
    if (_t1383) {
        Str *_t1318 = Str_lit("Bang", 4ULL);
        (void)_t1318;
        ;
        return _t1318;
    }
    ;
    Bool _t1384; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Minus()); _t1384 = *_hp; free(_hp); }
    (void)_t1384;
    if (_t1384) {
        Str *_t1319 = Str_lit("Minus", 5ULL);
        (void)_t1319;
        ;
        return _t1319;
    }
    ;
    Bool _t1385; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Plus()); _t1385 = *_hp; free(_hp); }
    (void)_t1385;
    if (_t1385) {
        Str *_t1320 = Str_lit("Plus", 4ULL);
        (void)_t1320;
        ;
        return _t1320;
    }
    ;
    Bool _t1386; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Star()); _t1386 = *_hp; free(_hp); }
    (void)_t1386;
    if (_t1386) {
        Str *_t1321 = Str_lit("Star", 4ULL);
        (void)_t1321;
        ;
        return _t1321;
    }
    ;
    Bool _t1387; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Slash()); _t1387 = *_hp; free(_hp); }
    (void)_t1387;
    if (_t1387) {
        Str *_t1322 = Str_lit("Slash", 5ULL);
        (void)_t1322;
        ;
        return _t1322;
    }
    ;
    Bool _t1388; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Dot()); _t1388 = *_hp; free(_hp); }
    (void)_t1388;
    if (_t1388) {
        Str *_t1323 = Str_lit("Dot", 3ULL);
        (void)_t1323;
        ;
        return _t1323;
    }
    ;
    Bool _t1389; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_DotDot()); _t1389 = *_hp; free(_hp); }
    (void)_t1389;
    if (_t1389) {
        Str *_t1324 = Str_lit("DotDot", 6ULL);
        (void)_t1324;
        ;
        return _t1324;
    }
    ;
    Bool _t1390; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Eq()); _t1390 = *_hp; free(_hp); }
    (void)_t1390;
    if (_t1390) {
        Str *_t1325 = Str_lit("Eq", 2ULL);
        (void)_t1325;
        ;
        return _t1325;
    }
    ;
    Bool _t1391; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_EqEq()); _t1391 = *_hp; free(_hp); }
    (void)_t1391;
    if (_t1391) {
        Str *_t1326 = Str_lit("EqEq", 4ULL);
        (void)_t1326;
        ;
        return _t1326;
    }
    ;
    Bool _t1392; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Neq()); _t1392 = *_hp; free(_hp); }
    (void)_t1392;
    if (_t1392) {
        Str *_t1327 = Str_lit("Neq", 3ULL);
        (void)_t1327;
        ;
        return _t1327;
    }
    ;
    Bool _t1393; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Lt()); _t1393 = *_hp; free(_hp); }
    (void)_t1393;
    if (_t1393) {
        Str *_t1328 = Str_lit("Lt", 2ULL);
        (void)_t1328;
        ;
        return _t1328;
    }
    ;
    Bool _t1394; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_LtEq()); _t1394 = *_hp; free(_hp); }
    (void)_t1394;
    if (_t1394) {
        Str *_t1329 = Str_lit("LtEq", 4ULL);
        (void)_t1329;
        ;
        return _t1329;
    }
    ;
    Bool _t1395; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Gt()); _t1395 = *_hp; free(_hp); }
    (void)_t1395;
    if (_t1395) {
        Str *_t1330 = Str_lit("Gt", 2ULL);
        (void)_t1330;
        ;
        return _t1330;
    }
    ;
    Bool _t1396; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_GtEq()); _t1396 = *_hp; free(_hp); }
    (void)_t1396;
    if (_t1396) {
        Str *_t1331 = Str_lit("GtEq", 4ULL);
        (void)_t1331;
        ;
        return _t1331;
    }
    ;
    Bool _t1397; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_ColonEq()); _t1397 = *_hp; free(_hp); }
    (void)_t1397;
    if (_t1397) {
        Str *_t1332 = Str_lit("ColonEq", 7ULL);
        (void)_t1332;
        ;
        return _t1332;
    }
    ;
    Bool _t1398; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Ident()); _t1398 = *_hp; free(_hp); }
    (void)_t1398;
    if (_t1398) {
        Str *_t1333 = Str_lit("Ident", 5ULL);
        (void)_t1333;
        ;
        return _t1333;
    }
    ;
    Bool _t1399; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_StringTok()); _t1399 = *_hp; free(_hp); }
    (void)_t1399;
    if (_t1399) {
        Str *_t1334 = Str_lit("StringTok", 9ULL);
        (void)_t1334;
        ;
        return _t1334;
    }
    ;
    Bool _t1400; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Number()); _t1400 = *_hp; free(_hp); }
    (void)_t1400;
    if (_t1400) {
        Str *_t1335 = Str_lit("Number", 6ULL);
        (void)_t1335;
        ;
        return _t1335;
    }
    ;
    Bool _t1401; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Char()); _t1401 = *_hp; free(_hp); }
    (void)_t1401;
    if (_t1401) {
        Str *_t1336 = Str_lit("Char", 4ULL);
        (void)_t1336;
        ;
        return _t1336;
    }
    ;
    Bool _t1402; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMode()); _t1402 = *_hp; free(_hp); }
    (void)_t1402;
    if (_t1402) {
        Str *_t1337 = Str_lit("KwMode", 6ULL);
        (void)_t1337;
        ;
        return _t1337;
    }
    ;
    Bool _t1403; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMut()); _t1403 = *_hp; free(_hp); }
    (void)_t1403;
    if (_t1403) {
        Str *_t1338 = Str_lit("KwMut", 5ULL);
        (void)_t1338;
        ;
        return _t1338;
    }
    ;
    Bool _t1404; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwOwn()); _t1404 = *_hp; free(_hp); }
    (void)_t1404;
    if (_t1404) {
        Str *_t1339 = Str_lit("KwOwn", 5ULL);
        (void)_t1339;
        ;
        return _t1339;
    }
    ;
    Bool _t1405; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwRef()); _t1405 = *_hp; free(_hp); }
    (void)_t1405;
    if (_t1405) {
        Str *_t1340 = Str_lit("KwRef", 5ULL);
        (void)_t1340;
        ;
        return _t1340;
    }
    ;
    Bool _t1406; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwShallow()); _t1406 = *_hp; free(_hp); }
    (void)_t1406;
    if (_t1406) {
        Str *_t1341 = Str_lit("KwShallow", 9ULL);
        (void)_t1341;
        ;
        return _t1341;
    }
    ;
    Bool _t1407; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwStruct()); _t1407 = *_hp; free(_hp); }
    (void)_t1407;
    if (_t1407) {
        Str *_t1342 = Str_lit("KwStruct", 8ULL);
        (void)_t1342;
        ;
        return _t1342;
    }
    ;
    Bool _t1408; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtStruct()); _t1408 = *_hp; free(_hp); }
    (void)_t1408;
    if (_t1408) {
        Str *_t1343 = Str_lit("KwExtStruct", 11ULL);
        (void)_t1343;
        ;
        return _t1343;
    }
    ;
    Bool _t1409; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwEnum()); _t1409 = *_hp; free(_hp); }
    (void)_t1409;
    if (_t1409) {
        Str *_t1344 = Str_lit("KwEnum", 6ULL);
        (void)_t1344;
        ;
        return _t1344;
    }
    ;
    Bool _t1410; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNamespace()); _t1410 = *_hp; free(_hp); }
    (void)_t1410;
    if (_t1410) {
        Str *_t1345 = Str_lit("KwNamespace", 11ULL);
        (void)_t1345;
        ;
        return _t1345;
    }
    ;
    Bool _t1411; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFunc()); _t1411 = *_hp; free(_hp); }
    (void)_t1411;
    if (_t1411) {
        Str *_t1346 = Str_lit("KwFunc", 6ULL);
        (void)_t1346;
        ;
        return _t1346;
    }
    ;
    Bool _t1412; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwProc()); _t1412 = *_hp; free(_hp); }
    (void)_t1412;
    if (_t1412) {
        Str *_t1347 = Str_lit("KwProc", 6ULL);
        (void)_t1347;
        ;
        return _t1347;
    }
    ;
    Bool _t1413; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTest()); _t1413 = *_hp; free(_hp); }
    (void)_t1413;
    if (_t1413) {
        Str *_t1348 = Str_lit("KwTest", 6ULL);
        (void)_t1348;
        ;
        return _t1348;
    }
    ;
    Bool _t1414; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMacro()); _t1414 = *_hp; free(_hp); }
    (void)_t1414;
    if (_t1414) {
        Str *_t1349 = Str_lit("KwMacro", 7ULL);
        (void)_t1349;
        ;
        return _t1349;
    }
    ;
    Bool _t1415; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtFunc()); _t1415 = *_hp; free(_hp); }
    (void)_t1415;
    if (_t1415) {
        Str *_t1350 = Str_lit("KwExtFunc", 9ULL);
        (void)_t1350;
        ;
        return _t1350;
    }
    ;
    Bool _t1416; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwExtProc()); _t1416 = *_hp; free(_hp); }
    (void)_t1416;
    if (_t1416) {
        Str *_t1351 = Str_lit("KwExtProc", 9ULL);
        (void)_t1351;
        ;
        return _t1351;
    }
    ;
    Bool _t1417; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturns()); _t1417 = *_hp; free(_hp); }
    (void)_t1417;
    if (_t1417) {
        Str *_t1352 = Str_lit("KwReturns", 9ULL);
        (void)_t1352;
        ;
        return _t1352;
    }
    ;
    Bool _t1418; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrows()); _t1418 = *_hp; free(_hp); }
    (void)_t1418;
    if (_t1418) {
        Str *_t1353 = Str_lit("KwThrows", 8ULL);
        (void)_t1353;
        ;
        return _t1353;
    }
    ;
    Bool _t1419; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIf()); _t1419 = *_hp; free(_hp); }
    (void)_t1419;
    if (_t1419) {
        Str *_t1354 = Str_lit("KwIf", 4ULL);
        (void)_t1354;
        ;
        return _t1354;
    }
    ;
    Bool _t1420; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwElse()); _t1420 = *_hp; free(_hp); }
    (void)_t1420;
    if (_t1420) {
        Str *_t1355 = Str_lit("KwElse", 6ULL);
        (void)_t1355;
        ;
        return _t1355;
    }
    ;
    Bool _t1421; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwWhile()); _t1421 = *_hp; free(_hp); }
    (void)_t1421;
    if (_t1421) {
        Str *_t1356 = Str_lit("KwWhile", 7ULL);
        (void)_t1356;
        ;
        return _t1356;
    }
    ;
    Bool _t1422; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFor()); _t1422 = *_hp; free(_hp); }
    (void)_t1422;
    if (_t1422) {
        Str *_t1357 = Str_lit("KwFor", 5ULL);
        (void)_t1357;
        ;
        return _t1357;
    }
    ;
    Bool _t1423; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwIn()); _t1423 = *_hp; free(_hp); }
    (void)_t1423;
    if (_t1423) {
        Str *_t1358 = Str_lit("KwIn", 4ULL);
        (void)_t1358;
        ;
        return _t1358;
    }
    ;
    Bool _t1424; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwSwitch()); _t1424 = *_hp; free(_hp); }
    (void)_t1424;
    if (_t1424) {
        Str *_t1359 = Str_lit("KwSwitch", 8ULL);
        (void)_t1359;
        ;
        return _t1359;
    }
    ;
    Bool _t1425; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwMatch()); _t1425 = *_hp; free(_hp); }
    (void)_t1425;
    if (_t1425) {
        Str *_t1360 = Str_lit("KwMatch", 7ULL);
        (void)_t1360;
        ;
        return _t1360;
    }
    ;
    Bool _t1426; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCase()); _t1426 = *_hp; free(_hp); }
    (void)_t1426;
    if (_t1426) {
        Str *_t1361 = Str_lit("KwCase", 6ULL);
        (void)_t1361;
        ;
        return _t1361;
    }
    ;
    Bool _t1427; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefault()); _t1427 = *_hp; free(_hp); }
    (void)_t1427;
    if (_t1427) {
        Str *_t1362 = Str_lit("KwDefault", 9ULL);
        (void)_t1362;
        ;
        return _t1362;
    }
    ;
    Bool _t1428; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwReturn()); _t1428 = *_hp; free(_hp); }
    (void)_t1428;
    if (_t1428) {
        Str *_t1363 = Str_lit("KwReturn", 8ULL);
        (void)_t1363;
        ;
        return _t1363;
    }
    ;
    Bool _t1429; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwThrow()); _t1429 = *_hp; free(_hp); }
    (void)_t1429;
    if (_t1429) {
        Str *_t1364 = Str_lit("KwThrow", 7ULL);
        (void)_t1364;
        ;
        return _t1364;
    }
    ;
    Bool _t1430; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwCatch()); _t1430 = *_hp; free(_hp); }
    (void)_t1430;
    if (_t1430) {
        Str *_t1365 = Str_lit("KwCatch", 7ULL);
        (void)_t1365;
        ;
        return _t1365;
    }
    ;
    Bool _t1431; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwBreak()); _t1431 = *_hp; free(_hp); }
    (void)_t1431;
    if (_t1431) {
        Str *_t1366 = Str_lit("KwBreak", 7ULL);
        (void)_t1366;
        ;
        return _t1366;
    }
    ;
    Bool _t1432; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwContinue()); _t1432 = *_hp; free(_hp); }
    (void)_t1432;
    if (_t1432) {
        Str *_t1367 = Str_lit("KwContinue", 10ULL);
        (void)_t1367;
        ;
        return _t1367;
    }
    ;
    Bool _t1433; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwDefer()); _t1433 = *_hp; free(_hp); }
    (void)_t1433;
    if (_t1433) {
        Str *_t1368 = Str_lit("KwDefer", 7ULL);
        (void)_t1368;
        ;
        return _t1368;
    }
    ;
    Bool _t1434; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwTrue()); _t1434 = *_hp; free(_hp); }
    (void)_t1434;
    if (_t1434) {
        Str *_t1369 = Str_lit("KwTrue", 6ULL);
        (void)_t1369;
        ;
        return _t1369;
    }
    ;
    Bool _t1435; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwFalse()); _t1435 = *_hp; free(_hp); }
    (void)_t1435;
    if (_t1435) {
        Str *_t1370 = Str_lit("KwFalse", 7ULL);
        (void)_t1370;
        ;
        return _t1370;
    }
    ;
    Bool _t1436; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_KwNull()); _t1436 = *_hp; free(_hp); }
    (void)_t1436;
    if (_t1436) {
        Str *_t1371 = Str_lit("KwNull", 6ULL);
        (void)_t1371;
        ;
        return _t1371;
    }
    ;
    Bool _t1437; { Bool *_hp = (Bool *)TokenType_eq(self, TokenType_Error()); _t1437 = *_hp; free(_hp); }
    (void)_t1437;
    if (_t1437) {
        Str *_t1372 = Str_lit("Error", 5ULL);
        (void)_t1372;
        ;
        return _t1372;
    }
    ;
    Str *_t1438 = Str_lit("unknown", 7ULL);
    (void)_t1438;
    return _t1438;
}

U64 *TokenType_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(TokenType);
    return r;
}


Token * Token_clone(Token * self) {
    (void)self;
    I64 _t1440 = I64_clone(&self->line);
    (void)_t1440;
    I64 _t1441 = I64_clone(&self->col);
    (void)_t1441;
    Token *_t1442 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1442->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1442->text = *_ca; free(_ca); }
    _t1442->line = _t1440;
    _t1442->col = _t1441;
    (void)_t1442;
    ;
    ;
    return _t1442;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t1443 = 0;
    (void)_t1443;
    TokenType_delete(&self->type, &(Bool){_t1443});
    ;
    Bool _t1444 = 0;
    (void)_t1444;
    Str_delete(&self->text, &(Bool){_t1444});
    ;
    Bool _t1445 = 0;
    (void)_t1445;
    I64_delete(&self->line, &(Bool){_t1445});
    ;
    Bool _t1446 = 0;
    (void)_t1446;
    I64_delete(&self->col, &(Bool){_t1446});
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
    U8 _t1448 = 48;
    (void)_t1448;
    U8 _t1449 = 57;
    (void)_t1449;
    Bool _t1450; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1448}); _t1450 = *_hp; free(_hp); }
    (void)_t1450;
    ;
    Bool _t1451; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1449}); _t1451 = *_hp; free(_hp); }
    (void)_t1451;
    ;
    Bool _t1452 = Bool_and(_t1450, _t1451);
    (void)_t1452;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1452; return _r; }
}

Bool * is_alpha(U8 * c) {
    (void)c;
    U8 _t1453 = 97;
    (void)_t1453;
    U8 _t1454 = 122;
    (void)_t1454;
    Bool _t1455; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1453}); _t1455 = *_hp; free(_hp); }
    (void)_t1455;
    ;
    Bool _t1456; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1454}); _t1456 = *_hp; free(_hp); }
    (void)_t1456;
    ;
    U8 _t1457 = 65;
    (void)_t1457;
    U8 _t1458 = 90;
    (void)_t1458;
    Bool _t1459; { Bool *_hp = (Bool *)U8_gte(c, &(U8){_t1457}); _t1459 = *_hp; free(_hp); }
    (void)_t1459;
    ;
    Bool _t1460; { Bool *_hp = (Bool *)U8_lte(c, &(U8){_t1458}); _t1460 = *_hp; free(_hp); }
    (void)_t1460;
    ;
    Bool _t1461 = Bool_and(_t1455, _t1456);
    (void)_t1461;
    ;
    ;
    Bool _t1462 = Bool_and(_t1459, _t1460);
    (void)_t1462;
    ;
    ;
    U8 _t1463 = 95;
    (void)_t1463;
    Bool _t1464 = Bool_or(_t1461, _t1462);
    (void)_t1464;
    ;
    ;
    Bool _t1465 = U8_eq(DEREF(c), _t1463);
    (void)_t1465;
    ;
    Bool _t1466 = Bool_or(_t1464, _t1465);
    (void)_t1466;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1466; return _r; }
}

Bool * is_alnum(U8 * c) {
    (void)c;
    Bool _t1467; { Bool *_hp = (Bool *)is_alpha(c); _t1467 = *_hp; free(_hp); }
    (void)_t1467;
    Bool _t1468; { Bool *_hp = (Bool *)is_digit(c); _t1468 = *_hp; free(_hp); }
    (void)_t1468;
    Bool _t1469 = Bool_or(_t1467, _t1468);
    (void)_t1469;
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1469; return _r; }
}

Str * tok_name(TokenType * type) {
    (void)type;
    {
        TokenType *_sw1470 = TokenType_clone(type);
        (void)_sw1470;
        Bool _t1601; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Eof()); _t1601 = *_hp; free(_hp); }
        (void)_t1601;
        if (_t1601) {
            Str *_t1471 = Str_lit("eof", 3ULL);
            (void)_t1471;
            TokenType_delete(_sw1470, &(Bool){1});
            ;
            return _t1471;
        } else {
            Bool _t1600; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_LParen()); _t1600 = *_hp; free(_hp); }
            (void)_t1600;
            if (_t1600) {
                Str *_t1472 = Str_lit("(", 1ULL);
                (void)_t1472;
                ;
                TokenType_delete(_sw1470, &(Bool){1});
                ;
                return _t1472;
            } else {
                Bool _t1599; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_RParen()); _t1599 = *_hp; free(_hp); }
                (void)_t1599;
                if (_t1599) {
                    Str *_t1473 = Str_lit(")", 1ULL);
                    (void)_t1473;
                    ;
                    ;
                    TokenType_delete(_sw1470, &(Bool){1});
                    ;
                    return _t1473;
                } else {
                    Bool _t1598; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_LBrace()); _t1598 = *_hp; free(_hp); }
                    (void)_t1598;
                    if (_t1598) {
                        Str *_t1474 = Str_lit("{", 1ULL);
                        (void)_t1474;
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1470, &(Bool){1});
                        ;
                        return _t1474;
                    } else {
                        Bool _t1597; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_RBrace()); _t1597 = *_hp; free(_hp); }
                        (void)_t1597;
                        if (_t1597) {
                            Str *_t1475 = Str_lit("}", 1ULL);
                            (void)_t1475;
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1470, &(Bool){1});
                            ;
                            return _t1475;
                        } else {
                            Bool _t1596; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_LBracket()); _t1596 = *_hp; free(_hp); }
                            (void)_t1596;
                            if (_t1596) {
                                Str *_t1476 = Str_lit("[", 1ULL);
                                (void)_t1476;
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1470, &(Bool){1});
                                ;
                                return _t1476;
                            } else {
                                Bool _t1595; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_RBracket()); _t1595 = *_hp; free(_hp); }
                                (void)_t1595;
                                if (_t1595) {
                                    Str *_t1477 = Str_lit("]", 1ULL);
                                    (void)_t1477;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1470, &(Bool){1});
                                    ;
                                    return _t1477;
                                } else {
                                    Bool _t1594; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Comma()); _t1594 = *_hp; free(_hp); }
                                    (void)_t1594;
                                    if (_t1594) {
                                        Str *_t1478 = Str_lit(",", 1ULL);
                                        (void)_t1478;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1470, &(Bool){1});
                                        ;
                                        return _t1478;
                                    } else {
                                        Bool _t1593; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Colon()); _t1593 = *_hp; free(_hp); }
                                        (void)_t1593;
                                        if (_t1593) {
                                            Str *_t1479 = Str_lit(":", 1ULL);
                                            (void)_t1479;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1470, &(Bool){1});
                                            ;
                                            return _t1479;
                                        } else {
                                            Bool _t1592; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Question()); _t1592 = *_hp; free(_hp); }
                                            (void)_t1592;
                                            if (_t1592) {
                                                Str *_t1480 = Str_lit("?", 1ULL);
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
                                                TokenType_delete(_sw1470, &(Bool){1});
                                                ;
                                                return _t1480;
                                            } else {
                                                Bool _t1591; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Bang()); _t1591 = *_hp; free(_hp); }
                                                (void)_t1591;
                                                if (_t1591) {
                                                    Str *_t1481 = Str_lit("!", 1ULL);
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
                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                    ;
                                                    return _t1481;
                                                } else {
                                                    Bool _t1590; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Minus()); _t1590 = *_hp; free(_hp); }
                                                    (void)_t1590;
                                                    if (_t1590) {
                                                        Str *_t1482 = Str_lit("-", 1ULL);
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
                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                        ;
                                                        return _t1482;
                                                    } else {
                                                        Bool _t1589; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Plus()); _t1589 = *_hp; free(_hp); }
                                                        (void)_t1589;
                                                        if (_t1589) {
                                                            Str *_t1483 = Str_lit("+", 1ULL);
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
                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                            ;
                                                            return _t1483;
                                                        } else {
                                                            Bool _t1588; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Star()); _t1588 = *_hp; free(_hp); }
                                                            (void)_t1588;
                                                            if (_t1588) {
                                                                Str *_t1484 = Str_lit("*", 1ULL);
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
                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                ;
                                                                return _t1484;
                                                            } else {
                                                                Bool _t1587; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Slash()); _t1587 = *_hp; free(_hp); }
                                                                (void)_t1587;
                                                                if (_t1587) {
                                                                    Str *_t1485 = Str_lit("/", 1ULL);
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
                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                    ;
                                                                    return _t1485;
                                                                } else {
                                                                    Bool _t1586; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Dot()); _t1586 = *_hp; free(_hp); }
                                                                    (void)_t1586;
                                                                    if (_t1586) {
                                                                        Str *_t1486 = Str_lit(".", 1ULL);
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
                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                        ;
                                                                        return _t1486;
                                                                    } else {
                                                                        Bool _t1585; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_DotDot()); _t1585 = *_hp; free(_hp); }
                                                                        (void)_t1585;
                                                                        if (_t1585) {
                                                                            Str *_t1487 = Str_lit("..", 2ULL);
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
                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                            ;
                                                                            return _t1487;
                                                                        } else {
                                                                            Bool _t1584; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Eq()); _t1584 = *_hp; free(_hp); }
                                                                            (void)_t1584;
                                                                            if (_t1584) {
                                                                                Str *_t1488 = Str_lit("=", 1ULL);
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
                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                ;
                                                                                return _t1488;
                                                                            } else {
                                                                                Bool _t1583; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_EqEq()); _t1583 = *_hp; free(_hp); }
                                                                                (void)_t1583;
                                                                                if (_t1583) {
                                                                                    Str *_t1489 = Str_lit("==", 2ULL);
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
                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                    ;
                                                                                    return _t1489;
                                                                                } else {
                                                                                    Bool _t1582; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Neq()); _t1582 = *_hp; free(_hp); }
                                                                                    (void)_t1582;
                                                                                    if (_t1582) {
                                                                                        Str *_t1490 = Str_lit("!=", 2ULL);
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
                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                        ;
                                                                                        return _t1490;
                                                                                    } else {
                                                                                        Bool _t1581; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Lt()); _t1581 = *_hp; free(_hp); }
                                                                                        (void)_t1581;
                                                                                        if (_t1581) {
                                                                                            Str *_t1491 = Str_lit("<", 1ULL);
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
                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                            ;
                                                                                            return _t1491;
                                                                                        } else {
                                                                                            Bool _t1580; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_LtEq()); _t1580 = *_hp; free(_hp); }
                                                                                            (void)_t1580;
                                                                                            if (_t1580) {
                                                                                                Str *_t1492 = Str_lit("<=", 2ULL);
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
                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                ;
                                                                                                return _t1492;
                                                                                            } else {
                                                                                                Bool _t1579; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Gt()); _t1579 = *_hp; free(_hp); }
                                                                                                (void)_t1579;
                                                                                                if (_t1579) {
                                                                                                    Str *_t1493 = Str_lit(">", 1ULL);
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
                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1493;
                                                                                                } else {
                                                                                                    Bool _t1578; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_GtEq()); _t1578 = *_hp; free(_hp); }
                                                                                                    (void)_t1578;
                                                                                                    if (_t1578) {
                                                                                                        Str *_t1494 = Str_lit(">=", 2ULL);
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
                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1494;
                                                                                                    } else {
                                                                                                        Bool _t1577; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_ColonEq()); _t1577 = *_hp; free(_hp); }
                                                                                                        (void)_t1577;
                                                                                                        if (_t1577) {
                                                                                                            Str *_t1495 = Str_lit(":=", 2ULL);
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
                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1495;
                                                                                                        } else {
                                                                                                            Bool _t1576; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Ident()); _t1576 = *_hp; free(_hp); }
                                                                                                            (void)_t1576;
                                                                                                            if (_t1576) {
                                                                                                                Str *_t1496 = Str_lit("identifier", 10ULL);
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
                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1496;
                                                                                                            } else {
                                                                                                                Bool _t1575; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_StringTok()); _t1575 = *_hp; free(_hp); }
                                                                                                                (void)_t1575;
                                                                                                                if (_t1575) {
                                                                                                                    Str *_t1497 = Str_lit("string", 6ULL);
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
                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1497;
                                                                                                                } else {
                                                                                                                    Bool _t1574; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Number()); _t1574 = *_hp; free(_hp); }
                                                                                                                    (void)_t1574;
                                                                                                                    if (_t1574) {
                                                                                                                        Str *_t1498 = Str_lit("number", 6ULL);
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
                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1498;
                                                                                                                    } else {
                                                                                                                        Bool _t1573; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Char()); _t1573 = *_hp; free(_hp); }
                                                                                                                        (void)_t1573;
                                                                                                                        if (_t1573) {
                                                                                                                            Str *_t1499 = Str_lit("char", 4ULL);
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
                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1499;
                                                                                                                        } else {
                                                                                                                            Bool _t1572; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwMode()); _t1572 = *_hp; free(_hp); }
                                                                                                                            (void)_t1572;
                                                                                                                            if (_t1572) {
                                                                                                                                Str *_t1500 = Str_lit("mode", 4ULL);
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
                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1500;
                                                                                                                            } else {
                                                                                                                                Bool _t1571; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwMut()); _t1571 = *_hp; free(_hp); }
                                                                                                                                (void)_t1571;
                                                                                                                                if (_t1571) {
                                                                                                                                    Str *_t1501 = Str_lit("mut", 3ULL);
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
                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1501;
                                                                                                                                } else {
                                                                                                                                    Bool _t1570; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwOwn()); _t1570 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1570;
                                                                                                                                    if (_t1570) {
                                                                                                                                        Str *_t1502 = Str_lit("own", 3ULL);
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
                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1502;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1569; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwRef()); _t1569 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1569;
                                                                                                                                        if (_t1569) {
                                                                                                                                            Str *_t1503 = Str_lit("ref", 3ULL);
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
                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1503;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1568; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwShallow()); _t1568 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1568;
                                                                                                                                            if (_t1568) {
                                                                                                                                                Str *_t1504 = Str_lit("shallow", 7ULL);
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
                                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1504;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1567; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwStruct()); _t1567 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1567;
                                                                                                                                                if (_t1567) {
                                                                                                                                                    Str *_t1505 = Str_lit("struct", 6ULL);
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
                                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1505;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1566; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwExtStruct()); _t1566 = *_hp; free(_hp); }
                                                                                                                                                    (void)_t1566;
                                                                                                                                                    if (_t1566) {
                                                                                                                                                        Str *_t1506 = Str_lit("ext_struct", 10ULL);
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
                                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1506;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1565; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwEnum()); _t1565 = *_hp; free(_hp); }
                                                                                                                                                        (void)_t1565;
                                                                                                                                                        if (_t1565) {
                                                                                                                                                            Str *_t1507 = Str_lit("enum", 4ULL);
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
                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1507;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1564; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwNamespace()); _t1564 = *_hp; free(_hp); }
                                                                                                                                                            (void)_t1564;
                                                                                                                                                            if (_t1564) {
                                                                                                                                                                Str *_t1508 = Str_lit("namespace", 9ULL);
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
                                                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1508;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1563; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwFunc()); _t1563 = *_hp; free(_hp); }
                                                                                                                                                                (void)_t1563;
                                                                                                                                                                if (_t1563) {
                                                                                                                                                                    Str *_t1509 = Str_lit("func", 4ULL);
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
                                                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1509;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1562; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwProc()); _t1562 = *_hp; free(_hp); }
                                                                                                                                                                    (void)_t1562;
                                                                                                                                                                    if (_t1562) {
                                                                                                                                                                        Str *_t1510 = Str_lit("proc", 4ULL);
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
                                                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1510;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1561; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwTest()); _t1561 = *_hp; free(_hp); }
                                                                                                                                                                        (void)_t1561;
                                                                                                                                                                        if (_t1561) {
                                                                                                                                                                            Str *_t1511 = Str_lit("test", 4ULL);
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
                                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1511;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1560; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwMacro()); _t1560 = *_hp; free(_hp); }
                                                                                                                                                                            (void)_t1560;
                                                                                                                                                                            if (_t1560) {
                                                                                                                                                                                Str *_t1512 = Str_lit("macro", 5ULL);
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
                                                                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1512;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1559; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwExtFunc()); _t1559 = *_hp; free(_hp); }
                                                                                                                                                                                (void)_t1559;
                                                                                                                                                                                if (_t1559) {
                                                                                                                                                                                    Str *_t1513 = Str_lit("ext_func", 8ULL);
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
                                                                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1513;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1558; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwExtProc()); _t1558 = *_hp; free(_hp); }
                                                                                                                                                                                    (void)_t1558;
                                                                                                                                                                                    if (_t1558) {
                                                                                                                                                                                        Str *_t1514 = Str_lit("ext_proc", 8ULL);
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
                                                                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1514;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1557; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwReturns()); _t1557 = *_hp; free(_hp); }
                                                                                                                                                                                        (void)_t1557;
                                                                                                                                                                                        if (_t1557) {
                                                                                                                                                                                            Str *_t1515 = Str_lit("returns", 7ULL);
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
                                                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1515;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1556; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwThrows()); _t1556 = *_hp; free(_hp); }
                                                                                                                                                                                            (void)_t1556;
                                                                                                                                                                                            if (_t1556) {
                                                                                                                                                                                                Str *_t1516 = Str_lit("throws", 6ULL);
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
                                                                                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1516;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1555; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwIf()); _t1555 = *_hp; free(_hp); }
                                                                                                                                                                                                (void)_t1555;
                                                                                                                                                                                                if (_t1555) {
                                                                                                                                                                                                    Str *_t1517 = Str_lit("if", 2ULL);
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
                                                                                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1517;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1554; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwElse()); _t1554 = *_hp; free(_hp); }
                                                                                                                                                                                                    (void)_t1554;
                                                                                                                                                                                                    if (_t1554) {
                                                                                                                                                                                                        Str *_t1518 = Str_lit("else", 4ULL);
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
                                                                                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1518;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1553; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwWhile()); _t1553 = *_hp; free(_hp); }
                                                                                                                                                                                                        (void)_t1553;
                                                                                                                                                                                                        if (_t1553) {
                                                                                                                                                                                                            Str *_t1519 = Str_lit("while", 5ULL);
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
                                                                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1519;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1552; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwFor()); _t1552 = *_hp; free(_hp); }
                                                                                                                                                                                                            (void)_t1552;
                                                                                                                                                                                                            if (_t1552) {
                                                                                                                                                                                                                Str *_t1520 = Str_lit("for", 3ULL);
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
                                                                                                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1520;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1551; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwIn()); _t1551 = *_hp; free(_hp); }
                                                                                                                                                                                                                (void)_t1551;
                                                                                                                                                                                                                if (_t1551) {
                                                                                                                                                                                                                    Str *_t1521 = Str_lit("in", 2ULL);
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
                                                                                                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1521;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1550; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwSwitch()); _t1550 = *_hp; free(_hp); }
                                                                                                                                                                                                                    (void)_t1550;
                                                                                                                                                                                                                    if (_t1550) {
                                                                                                                                                                                                                        Str *_t1522 = Str_lit("switch", 6ULL);
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
                                                                                                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1522;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1549; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwMatch()); _t1549 = *_hp; free(_hp); }
                                                                                                                                                                                                                        (void)_t1549;
                                                                                                                                                                                                                        if (_t1549) {
                                                                                                                                                                                                                            Str *_t1523 = Str_lit("match", 5ULL);
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
                                                                                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1523;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1548; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwCase()); _t1548 = *_hp; free(_hp); }
                                                                                                                                                                                                                            (void)_t1548;
                                                                                                                                                                                                                            if (_t1548) {
                                                                                                                                                                                                                                Str *_t1524 = Str_lit("case", 4ULL);
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
                                                                                                                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1524;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1547; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwDefault()); _t1547 = *_hp; free(_hp); }
                                                                                                                                                                                                                                (void)_t1547;
                                                                                                                                                                                                                                if (_t1547) {
                                                                                                                                                                                                                                    Str *_t1525 = Str_lit("default", 7ULL);
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
                                                                                                                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1525;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1546; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwReturn()); _t1546 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    (void)_t1546;
                                                                                                                                                                                                                                    if (_t1546) {
                                                                                                                                                                                                                                        Str *_t1526 = Str_lit("return", 6ULL);
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
                                                                                                                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1526;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1545; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwThrow()); _t1545 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        (void)_t1545;
                                                                                                                                                                                                                                        if (_t1545) {
                                                                                                                                                                                                                                            Str *_t1527 = Str_lit("throw", 5ULL);
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
                                                                                                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1527;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1544; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwCatch()); _t1544 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            (void)_t1544;
                                                                                                                                                                                                                                            if (_t1544) {
                                                                                                                                                                                                                                                Str *_t1528 = Str_lit("catch", 5ULL);
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
                                                                                                                                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1528;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1543; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwBreak()); _t1543 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                (void)_t1543;
                                                                                                                                                                                                                                                if (_t1543) {
                                                                                                                                                                                                                                                    Str *_t1529 = Str_lit("break", 5ULL);
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
                                                                                                                                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1529;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1542; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwContinue()); _t1542 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    (void)_t1542;
                                                                                                                                                                                                                                                    if (_t1542) {
                                                                                                                                                                                                                                                        Str *_t1530 = Str_lit("continue", 8ULL);
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
                                                                                                                                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1530;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1541; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwDefer()); _t1541 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        (void)_t1541;
                                                                                                                                                                                                                                                        if (_t1541) {
                                                                                                                                                                                                                                                            Str *_t1531 = Str_lit("defer", 5ULL);
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
                                                                                                                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1531;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1540; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwTrue()); _t1540 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            (void)_t1540;
                                                                                                                                                                                                                                                            if (_t1540) {
                                                                                                                                                                                                                                                                Str *_t1532 = Str_lit("true", 4ULL);
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
                                                                                                                                                                                                                                                                TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1532;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1539; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwFalse()); _t1539 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                (void)_t1539;
                                                                                                                                                                                                                                                                if (_t1539) {
                                                                                                                                                                                                                                                                    Str *_t1533 = Str_lit("false", 5ULL);
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
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1533;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Bool _t1538; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_KwNull()); _t1538 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                    (void)_t1538;
                                                                                                                                                                                                                                                                    if (_t1538) {
                                                                                                                                                                                                                                                                        Str *_t1534 = Str_lit("NULL", 4ULL);
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
                                                                                                                                                                                                                                                                        TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                        return _t1534;
                                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                                        Bool _t1537; { Bool *_hp = (Bool *)TokenType_eq(_sw1470, TokenType_Error()); _t1537 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                        (void)_t1537;
                                                                                                                                                                                                                                                                        if (_t1537) {
                                                                                                                                                                                                                                                                            Str *_t1535 = Str_lit("error", 5ULL);
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
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1535;
                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                            Str *_t1536 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                            (void)_t1536;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            TokenType_delete(_sw1470, &(Bool){1});
                                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                                            return _t1536;
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1470, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    (void)word;
    {
        Str *_sw1602 = Str_clone(word);
        (void)_sw1602;
        Str *_t1671 = Str_lit("mode", 4ULL);
        (void)_t1671;
        Bool _t1672; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1671); _t1672 = *_hp; free(_hp); }
        (void)_t1672;
        Str_delete(_t1671, &(Bool){1});
        if (_t1672) {
            Str_delete(_sw1602, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1669 = Str_lit("mut", 3ULL);
            (void)_t1669;
            Bool _t1670; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1669); _t1670 = *_hp; free(_hp); }
            (void)_t1670;
            Str_delete(_t1669, &(Bool){1});
            if (_t1670) {
                ;
                Str_delete(_sw1602, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1667 = Str_lit("own", 3ULL);
                (void)_t1667;
                Bool _t1668; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1667); _t1668 = *_hp; free(_hp); }
                (void)_t1668;
                Str_delete(_t1667, &(Bool){1});
                if (_t1668) {
                    ;
                    ;
                    Str_delete(_sw1602, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1665 = Str_lit("ref", 3ULL);
                    (void)_t1665;
                    Bool _t1666; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1665); _t1666 = *_hp; free(_hp); }
                    (void)_t1666;
                    Str_delete(_t1665, &(Bool){1});
                    if (_t1666) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1602, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1663 = Str_lit("shallow", 7ULL);
                        (void)_t1663;
                        Bool _t1664; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1663); _t1664 = *_hp; free(_hp); }
                        (void)_t1664;
                        Str_delete(_t1663, &(Bool){1});
                        if (_t1664) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1602, &(Bool){1});
                            ;
                            return TokenType_KwShallow();
                        } else {
                            Str *_t1661 = Str_lit("struct", 6ULL);
                            (void)_t1661;
                            Bool _t1662; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1661); _t1662 = *_hp; free(_hp); }
                            (void)_t1662;
                            Str_delete(_t1661, &(Bool){1});
                            if (_t1662) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1602, &(Bool){1});
                                ;
                                return TokenType_KwStruct();
                            } else {
                                Str *_t1659 = Str_lit("ext_struct", 10ULL);
                                (void)_t1659;
                                Bool _t1660; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1659); _t1660 = *_hp; free(_hp); }
                                (void)_t1660;
                                Str_delete(_t1659, &(Bool){1});
                                if (_t1660) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1602, &(Bool){1});
                                    ;
                                    return TokenType_KwExtStruct();
                                } else {
                                    Str *_t1657 = Str_lit("enum", 4ULL);
                                    (void)_t1657;
                                    Bool _t1658; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1657); _t1658 = *_hp; free(_hp); }
                                    (void)_t1658;
                                    Str_delete(_t1657, &(Bool){1});
                                    if (_t1658) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1602, &(Bool){1});
                                        ;
                                        return TokenType_KwEnum();
                                    } else {
                                        Str *_t1655 = Str_lit("namespace", 9ULL);
                                        (void)_t1655;
                                        Bool _t1656; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1655); _t1656 = *_hp; free(_hp); }
                                        (void)_t1656;
                                        Str_delete(_t1655, &(Bool){1});
                                        if (_t1656) {
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            Str_delete(_sw1602, &(Bool){1});
                                            ;
                                            return TokenType_KwNamespace();
                                        } else {
                                            Str *_t1653 = Str_lit("func", 4ULL);
                                            (void)_t1653;
                                            Bool _t1654; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1653); _t1654 = *_hp; free(_hp); }
                                            (void)_t1654;
                                            Str_delete(_t1653, &(Bool){1});
                                            if (_t1654) {
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                Str_delete(_sw1602, &(Bool){1});
                                                ;
                                                return TokenType_KwFunc();
                                            } else {
                                                Str *_t1651 = Str_lit("proc", 4ULL);
                                                (void)_t1651;
                                                Bool _t1652; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1651); _t1652 = *_hp; free(_hp); }
                                                (void)_t1652;
                                                Str_delete(_t1651, &(Bool){1});
                                                if (_t1652) {
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    Str_delete(_sw1602, &(Bool){1});
                                                    ;
                                                    return TokenType_KwProc();
                                                } else {
                                                    Str *_t1649 = Str_lit("test", 4ULL);
                                                    (void)_t1649;
                                                    Bool _t1650; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1649); _t1650 = *_hp; free(_hp); }
                                                    (void)_t1650;
                                                    Str_delete(_t1649, &(Bool){1});
                                                    if (_t1650) {
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        Str_delete(_sw1602, &(Bool){1});
                                                        ;
                                                        return TokenType_KwTest();
                                                    } else {
                                                        Str *_t1647 = Str_lit("macro", 5ULL);
                                                        (void)_t1647;
                                                        Bool _t1648; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1647); _t1648 = *_hp; free(_hp); }
                                                        (void)_t1648;
                                                        Str_delete(_t1647, &(Bool){1});
                                                        if (_t1648) {
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            Str_delete(_sw1602, &(Bool){1});
                                                            ;
                                                            return TokenType_KwMacro();
                                                        } else {
                                                            Str *_t1645 = Str_lit("ext_func", 8ULL);
                                                            (void)_t1645;
                                                            Bool _t1646; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1645); _t1646 = *_hp; free(_hp); }
                                                            (void)_t1646;
                                                            Str_delete(_t1645, &(Bool){1});
                                                            if (_t1646) {
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                Str_delete(_sw1602, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtFunc();
                                                            } else {
                                                                Str *_t1643 = Str_lit("ext_proc", 8ULL);
                                                                (void)_t1643;
                                                                Bool _t1644; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1643); _t1644 = *_hp; free(_hp); }
                                                                (void)_t1644;
                                                                Str_delete(_t1643, &(Bool){1});
                                                                if (_t1644) {
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    Str_delete(_sw1602, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwExtProc();
                                                                } else {
                                                                    Str *_t1641 = Str_lit("returns", 7ULL);
                                                                    (void)_t1641;
                                                                    Bool _t1642; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1641); _t1642 = *_hp; free(_hp); }
                                                                    (void)_t1642;
                                                                    Str_delete(_t1641, &(Bool){1});
                                                                    if (_t1642) {
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        Str_delete(_sw1602, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwReturns();
                                                                    } else {
                                                                        Str *_t1639 = Str_lit("throws", 6ULL);
                                                                        (void)_t1639;
                                                                        Bool _t1640; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1639); _t1640 = *_hp; free(_hp); }
                                                                        (void)_t1640;
                                                                        Str_delete(_t1639, &(Bool){1});
                                                                        if (_t1640) {
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            Str_delete(_sw1602, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwThrows();
                                                                        } else {
                                                                            Str *_t1637 = Str_lit("if", 2ULL);
                                                                            (void)_t1637;
                                                                            Bool _t1638; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1637); _t1638 = *_hp; free(_hp); }
                                                                            (void)_t1638;
                                                                            Str_delete(_t1637, &(Bool){1});
                                                                            if (_t1638) {
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                Str_delete(_sw1602, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwIf();
                                                                            } else {
                                                                                Str *_t1635 = Str_lit("else", 4ULL);
                                                                                (void)_t1635;
                                                                                Bool _t1636; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1635); _t1636 = *_hp; free(_hp); }
                                                                                (void)_t1636;
                                                                                Str_delete(_t1635, &(Bool){1});
                                                                                if (_t1636) {
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    Str_delete(_sw1602, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwElse();
                                                                                } else {
                                                                                    Str *_t1633 = Str_lit("while", 5ULL);
                                                                                    (void)_t1633;
                                                                                    Bool _t1634; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1633); _t1634 = *_hp; free(_hp); }
                                                                                    (void)_t1634;
                                                                                    Str_delete(_t1633, &(Bool){1});
                                                                                    if (_t1634) {
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        Str_delete(_sw1602, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwWhile();
                                                                                    } else {
                                                                                        Str *_t1631 = Str_lit("for", 3ULL);
                                                                                        (void)_t1631;
                                                                                        Bool _t1632; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1631); _t1632 = *_hp; free(_hp); }
                                                                                        (void)_t1632;
                                                                                        Str_delete(_t1631, &(Bool){1});
                                                                                        if (_t1632) {
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            Str_delete(_sw1602, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwFor();
                                                                                        } else {
                                                                                            Str *_t1629 = Str_lit("in", 2ULL);
                                                                                            (void)_t1629;
                                                                                            Bool _t1630; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1629); _t1630 = *_hp; free(_hp); }
                                                                                            (void)_t1630;
                                                                                            Str_delete(_t1629, &(Bool){1});
                                                                                            if (_t1630) {
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1602, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwIn();
                                                                                            } else {
                                                                                                Str *_t1627 = Str_lit("switch", 6ULL);
                                                                                                (void)_t1627;
                                                                                                Bool _t1628; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1627); _t1628 = *_hp; free(_hp); }
                                                                                                (void)_t1628;
                                                                                                Str_delete(_t1627, &(Bool){1});
                                                                                                if (_t1628) {
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1602, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwSwitch();
                                                                                                } else {
                                                                                                    Str *_t1625 = Str_lit("match", 5ULL);
                                                                                                    (void)_t1625;
                                                                                                    Bool _t1626; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1625); _t1626 = *_hp; free(_hp); }
                                                                                                    (void)_t1626;
                                                                                                    Str_delete(_t1625, &(Bool){1});
                                                                                                    if (_t1626) {
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1602, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwMatch();
                                                                                                    } else {
                                                                                                        Str *_t1623 = Str_lit("case", 4ULL);
                                                                                                        (void)_t1623;
                                                                                                        Bool _t1624; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1623); _t1624 = *_hp; free(_hp); }
                                                                                                        (void)_t1624;
                                                                                                        Str_delete(_t1623, &(Bool){1});
                                                                                                        if (_t1624) {
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1602, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwCase();
                                                                                                        } else {
                                                                                                            Str *_t1621 = Str_lit("default", 7ULL);
                                                                                                            (void)_t1621;
                                                                                                            Bool _t1622; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1621); _t1622 = *_hp; free(_hp); }
                                                                                                            (void)_t1622;
                                                                                                            Str_delete(_t1621, &(Bool){1});
                                                                                                            if (_t1622) {
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1602, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwDefault();
                                                                                                            } else {
                                                                                                                Str *_t1619 = Str_lit("return", 6ULL);
                                                                                                                (void)_t1619;
                                                                                                                Bool _t1620; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1619); _t1620 = *_hp; free(_hp); }
                                                                                                                (void)_t1620;
                                                                                                                Str_delete(_t1619, &(Bool){1});
                                                                                                                if (_t1620) {
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1602, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwReturn();
                                                                                                                } else {
                                                                                                                    Str *_t1617 = Str_lit("throw", 5ULL);
                                                                                                                    (void)_t1617;
                                                                                                                    Bool _t1618; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1617); _t1618 = *_hp; free(_hp); }
                                                                                                                    (void)_t1618;
                                                                                                                    Str_delete(_t1617, &(Bool){1});
                                                                                                                    if (_t1618) {
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1602, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwThrow();
                                                                                                                    } else {
                                                                                                                        Str *_t1615 = Str_lit("catch", 5ULL);
                                                                                                                        (void)_t1615;
                                                                                                                        Bool _t1616; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1615); _t1616 = *_hp; free(_hp); }
                                                                                                                        (void)_t1616;
                                                                                                                        Str_delete(_t1615, &(Bool){1});
                                                                                                                        if (_t1616) {
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1602, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwCatch();
                                                                                                                        } else {
                                                                                                                            Str *_t1613 = Str_lit("break", 5ULL);
                                                                                                                            (void)_t1613;
                                                                                                                            Bool _t1614; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1613); _t1614 = *_hp; free(_hp); }
                                                                                                                            (void)_t1614;
                                                                                                                            Str_delete(_t1613, &(Bool){1});
                                                                                                                            if (_t1614) {
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1602, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwBreak();
                                                                                                                            } else {
                                                                                                                                Str *_t1611 = Str_lit("continue", 8ULL);
                                                                                                                                (void)_t1611;
                                                                                                                                Bool _t1612; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1611); _t1612 = *_hp; free(_hp); }
                                                                                                                                (void)_t1612;
                                                                                                                                Str_delete(_t1611, &(Bool){1});
                                                                                                                                if (_t1612) {
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1602, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwContinue();
                                                                                                                                } else {
                                                                                                                                    Str *_t1609 = Str_lit("defer", 5ULL);
                                                                                                                                    (void)_t1609;
                                                                                                                                    Bool _t1610; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1609); _t1610 = *_hp; free(_hp); }
                                                                                                                                    (void)_t1610;
                                                                                                                                    Str_delete(_t1609, &(Bool){1});
                                                                                                                                    if (_t1610) {
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1602, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwDefer();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1607 = Str_lit("true", 4ULL);
                                                                                                                                        (void)_t1607;
                                                                                                                                        Bool _t1608; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1607); _t1608 = *_hp; free(_hp); }
                                                                                                                                        (void)_t1608;
                                                                                                                                        Str_delete(_t1607, &(Bool){1});
                                                                                                                                        if (_t1608) {
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1602, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return TokenType_KwTrue();
                                                                                                                                        } else {
                                                                                                                                            Str *_t1605 = Str_lit("false", 5ULL);
                                                                                                                                            (void)_t1605;
                                                                                                                                            Bool _t1606; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1605); _t1606 = *_hp; free(_hp); }
                                                                                                                                            (void)_t1606;
                                                                                                                                            Str_delete(_t1605, &(Bool){1});
                                                                                                                                            if (_t1606) {
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                Str_delete(_sw1602, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return TokenType_KwFalse();
                                                                                                                                            } else {
                                                                                                                                                Str *_t1603 = Str_lit("NULL", 4ULL);
                                                                                                                                                (void)_t1603;
                                                                                                                                                Bool _t1604; { Bool *_hp = (Bool *)Str_eq(_sw1602, _t1603); _t1604 = *_hp; free(_hp); }
                                                                                                                                                (void)_t1604;
                                                                                                                                                Str_delete(_t1603, &(Bool){1});
                                                                                                                                                if (_t1604) {
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    Str_delete(_sw1602, &(Bool){1});
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
                                                                                                                                                    Str_delete(_sw1602, &(Bool){1});
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
        Str_delete(_sw1602, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * src, Str * path) {
    (void)src;
    (void)path;
    Str *_t2009 = Str_lit("Token", 5ULL);
    (void)_t2009;
    U64 _t2010; { U64 *_hp = (U64 *)Token_size(); _t2010 = *_hp; free(_hp); }
    (void)_t2010;
    Vec *tokens = Vec_new(_t2009, &(U64){_t2010});
    (void)tokens;
    Str_delete(_t2009, &(Bool){1});
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
        Bool _wcond1673; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1673 = *_hp; free(_hp); }
        (void)_wcond1673;
        if (_wcond1673) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_byte_at(src, pos);
        (void)c;
        U8 _t1955 = 32;
        (void)_t1955;
        U8 _t1956 = 9;
        (void)_t1956;
        Bool _t1957 = U8_eq(DEREF(c), _t1955);
        (void)_t1957;
        ;
        Bool _t1958 = U8_eq(DEREF(c), _t1956);
        (void)_t1958;
        ;
        U8 _t1959 = 13;
        (void)_t1959;
        Bool _t1960 = Bool_or(_t1957, _t1958);
        (void)_t1960;
        ;
        ;
        Bool _t1961 = U8_eq(DEREF(c), _t1959);
        (void)_t1961;
        ;
        U8 _t1962 = 59;
        (void)_t1962;
        Bool _t1963 = Bool_or(_t1960, _t1961);
        (void)_t1963;
        ;
        ;
        Bool _t1964 = U8_eq(DEREF(c), _t1962);
        (void)_t1964;
        ;
        Bool _t1965 = Bool_or(_t1963, _t1964);
        (void)_t1965;
        ;
        ;
        if (_t1965) {
            U64 _t1674 = U64_inc(DEREF(pos));
            (void)_t1674;
            *pos = _t1674;
            ;
            ;
            continue;
        }
        ;
        U8 _t1966 = 10;
        (void)_t1966;
        Bool _t1967 = U8_eq(DEREF(c), _t1966);
        (void)_t1967;
        ;
        if (_t1967) {
            U64 _t1675 = U64_inc(DEREF(pos));
            (void)_t1675;
            *pos = _t1675;
            ;
            I64 _t1676 = 1;
            (void)_t1676;
            I64 _t1677 = I64_add(line, _t1676);
            (void)_t1677;
            ;
            line = _t1677;
            ;
            U64 _t1678 = U64_clone(pos);
            (void)_t1678;
            line_start = _t1678;
            ;
            ;
            continue;
        }
        ;
        U64 _t1968 = U64_sub(DEREF(pos), line_start);
        (void)_t1968;
        U64 _t1969 = 1;
        (void)_t1969;
        U64 _t1970 = U64_add(_t1968, _t1969);
        (void)_t1970;
        ;
        ;
        I64 col = U64_to_i64(_t1970);
        (void)col;
        ;
        U64 start = U64_clone(pos);
        (void)start;
        U8 _t1971 = 35;
        (void)_t1971;
        Bool _t1972 = U8_eq(DEREF(c), _t1971);
        (void)_t1972;
        ;
        if (_t1972) {
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
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1973 = 47;
        (void)_t1973;
        U64 _t1974 = 1;
        (void)_t1974;
        U64 _t1975 = U64_add(DEREF(pos), _t1974);
        (void)_t1975;
        ;
        Bool _t1976 = U8_eq(DEREF(c), _t1973);
        (void)_t1976;
        ;
        Bool _t1977; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1975}, &(U64){src_len}); _t1977 = *_hp; free(_hp); }
        (void)_t1977;
        ;
        Bool _t1978 = Bool_and(_t1976, _t1977);
        (void)_t1978;
        ;
        ;
        if (_t1978) {
            U64 _t1742 = 1;
            (void)_t1742;
            U64 *_t1743 = malloc(sizeof(U64)); *_t1743 = U64_add(DEREF(pos), _t1742);
            (void)_t1743;
            ;
            U8 *c2 = Str_byte_at(src, _t1743);
            (void)c2;
            U8 _t1744 = 47;
            (void)_t1744;
            Bool _t1745 = U8_eq(DEREF(c2), _t1744);
            (void)_t1745;
            ;
            if (_t1745) {
                while (1) {
                    Bool _wcond1684; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1684 = *_hp; free(_hp); }
                    (void)_wcond1684;
                    if (_wcond1684) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1685 = Str_byte_at(src, pos);
                    (void)_t1685;
                    U8 _t1686 = 10;
                    (void)_t1686;
                    Bool _t1687 = U8_eq(DEREF(_t1685), _t1686);
                    (void)_t1687;
                    ;
                    if (_t1687) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1688 = U64_inc(DEREF(pos));
                    (void)_t1688;
                    *pos = _t1688;
                    ;
                }
                U64_delete(_t1743, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1746 = 42;
            (void)_t1746;
            Bool _t1747 = U8_eq(DEREF(c2), _t1746);
            (void)_t1747;
            U64_delete(_t1743, &(Bool){1});
            ;
            if (_t1747) {
                U64 _t1738 = 2;
                (void)_t1738;
                U64 _t1739 = U64_add(DEREF(pos), _t1738);
                (void)_t1739;
                ;
                *pos = _t1739;
                ;
                I64 depth = 1;
                (void)depth;
                while (1) {
                    Bool _wcond1689; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1689 = *_hp; free(_hp); }
                    (void)_wcond1689;
                    if (_wcond1689) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1714 = 0;
                    (void)_t1714;
                    Bool _t1715; { Bool *_hp = (Bool *)I64_lte(&(I64){depth}, &(I64){_t1714}); _t1715 = *_hp; free(_hp); }
                    (void)_t1715;
                    ;
                    if (_t1715) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1716 = 1;
                    (void)_t1716;
                    U64 _t1717 = U64_add(DEREF(pos), _t1716);
                    (void)_t1717;
                    ;
                    Bool _t1718; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1717}, &(U64){src_len}); _t1718 = *_hp; free(_hp); }
                    (void)_t1718;
                    ;
                    if (_t1718) {
                        U8 *b1 = Str_byte_at(src, pos);
                        (void)b1;
                        U64 _t1698 = 1;
                        (void)_t1698;
                        U64 *_t1699 = malloc(sizeof(U64)); *_t1699 = U64_add(DEREF(pos), _t1698);
                        (void)_t1699;
                        ;
                        U8 *b2 = Str_byte_at(src, _t1699);
                        (void)b2;
                        U8 _t1700 = 47;
                        (void)_t1700;
                        U8 _t1701 = 42;
                        (void)_t1701;
                        Bool _t1702 = U8_eq(DEREF(b1), _t1700);
                        (void)_t1702;
                        ;
                        Bool _t1703 = U8_eq(DEREF(b2), _t1701);
                        (void)_t1703;
                        ;
                        Bool _t1704 = Bool_and(_t1702, _t1703);
                        (void)_t1704;
                        ;
                        ;
                        if (_t1704) {
                            I64 _t1690 = 1;
                            (void)_t1690;
                            I64 _t1691 = I64_add(depth, _t1690);
                            (void)_t1691;
                            ;
                            depth = _t1691;
                            ;
                            U64 _t1692 = 2;
                            (void)_t1692;
                            U64 _t1693 = U64_add(DEREF(pos), _t1692);
                            (void)_t1693;
                            ;
                            *pos = _t1693;
                            ;
                            U64_delete(_t1699, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1705 = 42;
                        (void)_t1705;
                        U8 _t1706 = 47;
                        (void)_t1706;
                        Bool _t1707 = U8_eq(DEREF(b1), _t1705);
                        (void)_t1707;
                        ;
                        Bool _t1708 = U8_eq(DEREF(b2), _t1706);
                        (void)_t1708;
                        U64_delete(_t1699, &(Bool){1});
                        ;
                        Bool _t1709 = Bool_and(_t1707, _t1708);
                        (void)_t1709;
                        ;
                        ;
                        if (_t1709) {
                            I64 _t1694 = 1;
                            (void)_t1694;
                            I64 _t1695 = I64_sub(depth, _t1694);
                            (void)_t1695;
                            ;
                            depth = _t1695;
                            ;
                            U64 _t1696 = 2;
                            (void)_t1696;
                            U64 _t1697 = U64_add(DEREF(pos), _t1696);
                            (void)_t1697;
                            ;
                            *pos = _t1697;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1719 = Str_byte_at(src, pos);
                    (void)_t1719;
                    U8 _t1720 = 10;
                    (void)_t1720;
                    Bool _t1721 = U8_eq(DEREF(_t1719), _t1720);
                    (void)_t1721;
                    ;
                    if (_t1721) {
                        I64 _t1710 = 1;
                        (void)_t1710;
                        I64 _t1711 = I64_add(line, _t1710);
                        (void)_t1711;
                        ;
                        line = _t1711;
                        ;
                        U64 _t1712 = 1;
                        (void)_t1712;
                        U64 _t1713 = U64_add(DEREF(pos), _t1712);
                        (void)_t1713;
                        ;
                        line_start = _t1713;
                        ;
                    }
                    ;
                    U64 _t1722 = U64_inc(DEREF(pos));
                    (void)_t1722;
                    *pos = _t1722;
                    ;
                }
                I64 _t1740 = 0;
                (void)_t1740;
                Bool _t1741; { Bool *_hp = (Bool *)I64_gt(&(I64){depth}, &(I64){_t1740}); _t1741 = *_hp; free(_hp); }
                (void)_t1741;
                ;
                ;
                if (_t1741) {
                    Str *_t1723 = Str_lit("Str", 3ULL);
                    (void)_t1723;
                    U64 _t1724; { U64 *_hp = (U64 *)Str_size(); _t1724 = *_hp; free(_hp); }
                    (void)_t1724;
                    U64 _t1725 = 6;
                    (void)_t1725;
                    Array *_va20 = Array_new(_t1723, &(U64){_t1724}, &(U64){_t1725});
                    (void)_va20;
                    Str_delete(_t1723, &(Bool){1});
                    ;
                    ;
                    U64 _t1726 = 0;
                    (void)_t1726;
                    Str *_t1727 = Str_clone(path);
                    (void)_t1727;
                    Array_set(_va20, &(U64){_t1726}, _t1727);
                    ;
                    U64 _t1728 = 1;
                    (void)_t1728;
                    Str *_t1729 = Str_lit(":", 1ULL);
                    (void)_t1729;
                    Array_set(_va20, &(U64){_t1728}, _t1729);
                    ;
                    U64 _t1730 = 2;
                    (void)_t1730;
                    Str *_t1731 = I64_to_str(&(I64){line});
                    (void)_t1731;
                    Array_set(_va20, &(U64){_t1730}, _t1731);
                    ;
                    U64 _t1732 = 3;
                    (void)_t1732;
                    Str *_t1733 = Str_lit(":", 1ULL);
                    (void)_t1733;
                    Array_set(_va20, &(U64){_t1732}, _t1733);
                    ;
                    U64 _t1734 = 4;
                    (void)_t1734;
                    Str *_t1735 = I64_to_str(&(I64){col});
                    (void)_t1735;
                    Array_set(_va20, &(U64){_t1734}, _t1735);
                    ;
                    U64 _t1736 = 5;
                    (void)_t1736;
                    Str *_t1737 = Str_lit(": error: unterminated comment", 29ULL);
                    (void)_t1737;
                    Array_set(_va20, &(U64){_t1736}, _t1737);
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
        Bool _t1979; { Bool *_hp = (Bool *)is_digit(c); _t1979 = *_hp; free(_hp); }
        (void)_t1979;
        if (_t1979) {
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
            U64 _t1767 = 1;
            (void)_t1767;
            U64 _t1768 = U64_add(DEREF(pos), _t1767);
            (void)_t1768;
            ;
            Bool _t1769; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1768}, &(U64){src_len}); _t1769 = *_hp; free(_hp); }
            (void)_t1769;
            ;
            if (_t1769) {
                U8 *_t1759 = Str_byte_at(src, pos);
                (void)_t1759;
                U8 _t1760 = 46;
                (void)_t1760;
                U64 _t1761 = 1;
                (void)_t1761;
                U64 *_t1762 = malloc(sizeof(U64)); *_t1762 = U64_add(DEREF(pos), _t1761);
                (void)_t1762;
                ;
                U8 *_t1763 = Str_byte_at(src, _t1762);
                (void)_t1763;
                Bool _t1764 = U8_eq(DEREF(_t1759), _t1760);
                (void)_t1764;
                ;
                Bool _t1765; { Bool *_hp = (Bool *)is_digit(_t1763); _t1765 = *_hp; free(_hp); }
                (void)_t1765;
                U64_delete(_t1762, &(Bool){1});
                Bool _t1766 = Bool_and(_t1764, _t1765);
                (void)_t1766;
                ;
                ;
                if (_t1766) {
                    U64 _t1758 = U64_inc(DEREF(pos));
                    (void)_t1758;
                    *pos = _t1758;
                    ;
                    while (1) {
                        Bool _wcond1753; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1753 = *_hp; free(_hp); }
                        (void)_wcond1753;
                        if (_wcond1753) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1754 = Str_byte_at(src, pos);
                        (void)_t1754;
                        Bool _t1755; { Bool *_hp = (Bool *)is_digit(_t1754); _t1755 = *_hp; free(_hp); }
                        (void)_t1755;
                        Bool _t1756 = Bool_not(_t1755);
                        (void)_t1756;
                        ;
                        if (_t1756) {
                            ;
                            break;
                        }
                        ;
                        U64 _t1757 = U64_inc(DEREF(pos));
                        (void)_t1757;
                        *pos = _t1757;
                        ;
                    }
                }
                ;
            }
            ;
            U64 _t1770 = U64_sub(DEREF(pos), start);
            (void)_t1770;
            I64 _t1771 = I64_clone(&(I64){col});
            (void)_t1771;
            Token *_t1772 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1772->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1770}); _t1772->text = *_ca; free(_ca); }
            _t1772->line = I64_clone(&(I64){line});
            _t1772->col = _t1771;
            (void)_t1772;
            ;
            ;
            Vec_push(tokens, _t1772);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1980; { Bool *_hp = (Bool *)is_alpha(c); _t1980 = *_hp; free(_hp); }
        (void)_t1980;
        if (_t1980) {
            while (1) {
                Bool _wcond1773; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1773 = *_hp; free(_hp); }
                (void)_wcond1773;
                if (_wcond1773) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1774 = Str_byte_at(src, pos);
                (void)_t1774;
                Bool _t1775; { Bool *_hp = (Bool *)is_alnum(_t1774); _t1775 = *_hp; free(_hp); }
                (void)_t1775;
                Bool _t1776 = Bool_not(_t1775);
                (void)_t1776;
                ;
                if (_t1776) {
                    ;
                    break;
                }
                ;
                U64 _t1777 = U64_inc(DEREF(pos));
                (void)_t1777;
                *pos = _t1777;
                ;
            }
            U64 _t1778 = U64_sub(DEREF(pos), start);
            (void)_t1778;
            Str *word = Str_substr(src, &(U64){start}, &(U64){_t1778});
            (void)word;
            ;
            TokenType *type = lookup_keyword(word);
            (void)type;
            I64 _t1779 = I64_clone(&(I64){line});
            (void)_t1779;
            I64 _t1780 = I64_clone(&(I64){col});
            (void)_t1780;
            Token *_t1781 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1781->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1781->text = *_ca; free(_ca); }
            _t1781->line = _t1779;
            _t1781->col = _t1780;
            (void)_t1781;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1781);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1981 = 34;
        (void)_t1981;
        Bool _t1982 = U8_eq(DEREF(c), _t1981);
        (void)_t1982;
        ;
        if (_t1982) {
            U64 _t1828 = U64_inc(DEREF(pos));
            (void)_t1828;
            *pos = _t1828;
            ;
            while (1) {
                Bool _wcond1782; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _wcond1782 = *_hp; free(_hp); }
                (void)_wcond1782;
                if (_wcond1782) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1788 = Str_byte_at(src, pos);
                (void)_t1788;
                U8 _t1789 = 34;
                (void)_t1789;
                Bool _t1790 = U8_eq(DEREF(_t1788), _t1789);
                (void)_t1790;
                ;
                if (_t1790) {
                    ;
                    break;
                }
                ;
                U8 *_t1791 = Str_byte_at(src, pos);
                (void)_t1791;
                U8 _t1792 = 92;
                (void)_t1792;
                U64 _t1793 = 1;
                (void)_t1793;
                U64 _t1794 = U64_add(DEREF(pos), _t1793);
                (void)_t1794;
                ;
                Bool _t1795 = U8_eq(DEREF(_t1791), _t1792);
                (void)_t1795;
                ;
                Bool _t1796; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1794}, &(U64){src_len}); _t1796 = *_hp; free(_hp); }
                (void)_t1796;
                ;
                Bool _t1797 = Bool_and(_t1795, _t1796);
                (void)_t1797;
                ;
                ;
                if (_t1797) {
                    U64 _t1783 = U64_inc(DEREF(pos));
                    (void)_t1783;
                    *pos = _t1783;
                    ;
                }
                ;
                U8 *_t1798 = Str_byte_at(src, pos);
                (void)_t1798;
                U8 _t1799 = 10;
                (void)_t1799;
                Bool _t1800 = U8_eq(DEREF(_t1798), _t1799);
                (void)_t1800;
                ;
                if (_t1800) {
                    I64 _t1784 = 1;
                    (void)_t1784;
                    I64 _t1785 = I64_add(line, _t1784);
                    (void)_t1785;
                    ;
                    line = _t1785;
                    ;
                    U64 _t1786 = 1;
                    (void)_t1786;
                    U64 _t1787 = U64_add(DEREF(pos), _t1786);
                    (void)_t1787;
                    ;
                    line_start = _t1787;
                    ;
                }
                ;
                U64 _t1801 = U64_inc(DEREF(pos));
                (void)_t1801;
                *pos = _t1801;
                ;
            }
            U8 *_t1829 = Str_byte_at(src, pos);
            (void)_t1829;
            U8 _t1830 = 34;
            (void)_t1830;
            Bool _t1831; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1831 = *_hp; free(_hp); }
            (void)_t1831;
            Bool _t1832 = U8_eq(DEREF(_t1829), _t1830);
            (void)_t1832;
            ;
            Bool _t1833 = Bool_and(_t1831, _t1832);
            (void)_t1833;
            ;
            ;
            if (_t1833) {
                U64 _t1802 = U64_inc(DEREF(pos));
                (void)_t1802;
                *pos = _t1802;
                ;
                U64 _t1803 = 1;
                (void)_t1803;
                U64 _t1804 = U64_sub(DEREF(pos), start);
                (void)_t1804;
                U64 _t1805 = 2;
                (void)_t1805;
                U64 _t1806 = U64_add(start, _t1803);
                (void)_t1806;
                ;
                U64 _t1807 = U64_sub(_t1804, _t1805);
                (void)_t1807;
                ;
                ;
                I64 _t1808 = I64_clone(&(I64){col});
                (void)_t1808;
                Token *_t1809 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1809->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){_t1806}, &(U64){_t1807}); _t1809->text = *_ca; free(_ca); }
                _t1809->line = I64_clone(&(I64){line});
                _t1809->col = _t1808;
                (void)_t1809;
                ;
                ;
                ;
                Vec_push(tokens, _t1809);
            } else {
                Str *_t1810 = Str_lit("Str", 3ULL);
                (void)_t1810;
                U64 _t1811; { U64 *_hp = (U64 *)Str_size(); _t1811 = *_hp; free(_hp); }
                (void)_t1811;
                U64 _t1812 = 6;
                (void)_t1812;
                Array *_va21 = Array_new(_t1810, &(U64){_t1811}, &(U64){_t1812});
                (void)_va21;
                Str_delete(_t1810, &(Bool){1});
                ;
                ;
                U64 _t1813 = 0;
                (void)_t1813;
                Str *_t1814 = Str_clone(path);
                (void)_t1814;
                Array_set(_va21, &(U64){_t1813}, _t1814);
                ;
                U64 _t1815 = 1;
                (void)_t1815;
                Str *_t1816 = Str_lit(":", 1ULL);
                (void)_t1816;
                Array_set(_va21, &(U64){_t1815}, _t1816);
                ;
                U64 _t1817 = 2;
                (void)_t1817;
                Str *_t1818 = I64_to_str(&(I64){line});
                (void)_t1818;
                Array_set(_va21, &(U64){_t1817}, _t1818);
                ;
                U64 _t1819 = 3;
                (void)_t1819;
                Str *_t1820 = Str_lit(":", 1ULL);
                (void)_t1820;
                Array_set(_va21, &(U64){_t1819}, _t1820);
                ;
                U64 _t1821 = 4;
                (void)_t1821;
                Str *_t1822 = I64_to_str(&(I64){col});
                (void)_t1822;
                Array_set(_va21, &(U64){_t1821}, _t1822);
                ;
                U64 _t1823 = 5;
                (void)_t1823;
                Str *_t1824 = Str_lit(": error: unterminated string", 28ULL);
                (void)_t1824;
                Array_set(_va21, &(U64){_t1823}, _t1824);
                ;
                println(_va21);
                U64 _t1825 = U64_sub(DEREF(pos), start);
                (void)_t1825;
                I64 _t1826 = I64_clone(&(I64){col});
                (void)_t1826;
                Token *_t1827 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1827->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1825}); _t1827->text = *_ca; free(_ca); }
                _t1827->line = I64_clone(&(I64){line});
                _t1827->col = _t1826;
                (void)_t1827;
                ;
                ;
                Vec_push(tokens, _t1827);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1983 = 39;
        (void)_t1983;
        Bool _t1984 = U8_eq(DEREF(c), _t1983);
        (void)_t1984;
        ;
        if (_t1984) {
            U64 _t1857 = U64_inc(DEREF(pos));
            (void)_t1857;
            *pos = _t1857;
            ;
            U64 ch_start = U64_clone(pos);
            (void)ch_start;
            U8 *_t1858 = Str_byte_at(src, pos);
            (void)_t1858;
            U8 _t1859 = 92;
            (void)_t1859;
            U64 _t1860 = 1;
            (void)_t1860;
            U64 _t1861 = U64_add(DEREF(pos), _t1860);
            (void)_t1861;
            ;
            Bool _t1862 = U8_eq(DEREF(_t1858), _t1859);
            (void)_t1862;
            ;
            Bool _t1863; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1861}, &(U64){src_len}); _t1863 = *_hp; free(_hp); }
            (void)_t1863;
            ;
            Bool _t1864; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1864 = *_hp; free(_hp); }
            (void)_t1864;
            Bool _t1865 = Bool_and(_t1862, _t1863);
            (void)_t1865;
            ;
            ;
            Bool _t1866 = Bool_and(_t1864, _t1865);
            (void)_t1866;
            ;
            ;
            if (_t1866) {
                U64 _t1834 = U64_inc(DEREF(pos));
                (void)_t1834;
                *pos = _t1834;
                ;
            }
            ;
            U64 _t1867 = U64_inc(DEREF(pos));
            (void)_t1867;
            *pos = _t1867;
            ;
            U8 *_t1868 = Str_byte_at(src, pos);
            (void)_t1868;
            U8 _t1869 = 39;
            (void)_t1869;
            Bool _t1870; { Bool *_hp = (Bool *)U64_lt(pos, &(U64){src_len}); _t1870 = *_hp; free(_hp); }
            (void)_t1870;
            Bool _t1871 = U8_eq(DEREF(_t1868), _t1869);
            (void)_t1871;
            ;
            Bool _t1872 = Bool_and(_t1870, _t1871);
            (void)_t1872;
            ;
            ;
            if (_t1872) {
                U64 _t1835 = U64_sub(DEREF(pos), ch_start);
                (void)_t1835;
                I64 _t1836 = I64_clone(&(I64){col});
                (void)_t1836;
                Token *_t1837 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1837->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){ch_start}, &(U64){_t1835}); _t1837->text = *_ca; free(_ca); }
                _t1837->line = I64_clone(&(I64){line});
                _t1837->col = _t1836;
                (void)_t1837;
                ;
                ;
                Vec_push(tokens, _t1837);
                U64 _t1838 = U64_inc(DEREF(pos));
                (void)_t1838;
                *pos = _t1838;
                ;
            } else {
                Str *_t1839 = Str_lit("Str", 3ULL);
                (void)_t1839;
                U64 _t1840; { U64 *_hp = (U64 *)Str_size(); _t1840 = *_hp; free(_hp); }
                (void)_t1840;
                U64 _t1841 = 6;
                (void)_t1841;
                Array *_va22 = Array_new(_t1839, &(U64){_t1840}, &(U64){_t1841});
                (void)_va22;
                Str_delete(_t1839, &(Bool){1});
                ;
                ;
                U64 _t1842 = 0;
                (void)_t1842;
                Str *_t1843 = Str_clone(path);
                (void)_t1843;
                Array_set(_va22, &(U64){_t1842}, _t1843);
                ;
                U64 _t1844 = 1;
                (void)_t1844;
                Str *_t1845 = Str_lit(":", 1ULL);
                (void)_t1845;
                Array_set(_va22, &(U64){_t1844}, _t1845);
                ;
                U64 _t1846 = 2;
                (void)_t1846;
                Str *_t1847 = I64_to_str(&(I64){line});
                (void)_t1847;
                Array_set(_va22, &(U64){_t1846}, _t1847);
                ;
                U64 _t1848 = 3;
                (void)_t1848;
                Str *_t1849 = Str_lit(":", 1ULL);
                (void)_t1849;
                Array_set(_va22, &(U64){_t1848}, _t1849);
                ;
                U64 _t1850 = 4;
                (void)_t1850;
                Str *_t1851 = I64_to_str(&(I64){col});
                (void)_t1851;
                Array_set(_va22, &(U64){_t1850}, _t1851);
                ;
                U64 _t1852 = 5;
                (void)_t1852;
                Str *_t1853 = Str_lit(": error: unterminated character literal", 39ULL);
                (void)_t1853;
                Array_set(_va22, &(U64){_t1852}, _t1853);
                ;
                println(_va22);
                U64 _t1854 = U64_sub(DEREF(pos), start);
                (void)_t1854;
                I64 _t1855 = I64_clone(&(I64){col});
                (void)_t1855;
                Token *_t1856 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1856->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1854}); _t1856->text = *_ca; free(_ca); }
                _t1856->line = I64_clone(&(I64){line});
                _t1856->col = _t1855;
                (void)_t1856;
                ;
                ;
                Vec_push(tokens, _t1856);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t1985 = 1;
        (void)_t1985;
        U64 _t1986 = U64_add(DEREF(pos), _t1985);
        (void)_t1986;
        ;
        Bool _t1987; { Bool *_hp = (Bool *)U64_lt(&(U64){_t1986}, &(U64){src_len}); _t1987 = *_hp; free(_hp); }
        (void)_t1987;
        ;
        if (_t1987) {
            U64 _t1904 = 1;
            (void)_t1904;
            U64 *_t1905 = malloc(sizeof(U64)); *_t1905 = U64_add(DEREF(pos), _t1904);
            (void)_t1905;
            ;
            U8 *c2 = Str_byte_at(src, _t1905);
            (void)c2;
            TokenType *two = TokenType_clone(TokenType_Eof());
            (void)two;
            U8 _t1906 = 58;
            (void)_t1906;
            U8 _t1907 = 61;
            (void)_t1907;
            Bool _t1908 = U8_eq(DEREF(c), _t1906);
            (void)_t1908;
            ;
            Bool _t1909 = U8_eq(DEREF(c2), _t1907);
            (void)_t1909;
            ;
            Bool _t1910 = Bool_and(_t1908, _t1909);
            (void)_t1910;
            ;
            ;
            if (_t1910) {
                two = TokenType_clone(TokenType_ColonEq());
            } else {
                U8 _t1893 = 61;
                (void)_t1893;
                U8 _t1894 = 61;
                (void)_t1894;
                Bool _t1895 = U8_eq(DEREF(c), _t1893);
                (void)_t1895;
                ;
                Bool _t1896 = U8_eq(DEREF(c2), _t1894);
                (void)_t1896;
                ;
                Bool _t1897 = Bool_and(_t1895, _t1896);
                (void)_t1897;
                ;
                ;
                if (_t1897) {
                    two = TokenType_clone(TokenType_EqEq());
                } else {
                    U8 _t1888 = 33;
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
                        two = TokenType_clone(TokenType_Neq());
                    } else {
                        U8 _t1883 = 60;
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
                            two = TokenType_clone(TokenType_LtEq());
                        } else {
                            U8 _t1878 = 62;
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
                                two = TokenType_clone(TokenType_GtEq());
                            } else {
                                U8 _t1873 = 46;
                                (void)_t1873;
                                U8 _t1874 = 46;
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
            U64_delete(_t1905, &(Bool){1});
            ;
            Bool _t1911; { Bool *_hp = (Bool *)TokenType_eq(two, TokenType_Eof()); _t1911 = *_hp; free(_hp); }
            (void)_t1911;
            Bool _t1912 = Bool_not(_t1911);
            (void)_t1912;
            ;
            if (_t1912) {
                U64 _t1898 = 2;
                (void)_t1898;
                I64 _t1899 = I64_clone(&(I64){line});
                (void)_t1899;
                I64 _t1900 = I64_clone(&(I64){col});
                (void)_t1900;
                Token *_t1901 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1901->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1898}); _t1901->text = *_ca; free(_ca); }
                _t1901->line = _t1899;
                _t1901->col = _t1900;
                (void)_t1901;
                ;
                ;
                ;
                Vec_push(tokens, _t1901);
                U64 _t1902 = 2;
                (void)_t1902;
                U64 _t1903 = U64_add(DEREF(pos), _t1902);
                (void)_t1903;
                ;
                *pos = _t1903;
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
            U8 _sw1913 = U8_clone(c);
            (void)_sw1913;
            U8 _t1948 = 40;
            (void)_t1948;
            Bool _t1949 = U8_eq(_sw1913, _t1948);
            (void)_t1949;
            ;
            if (_t1949) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1946 = 41;
                (void)_t1946;
                Bool _t1947 = U8_eq(_sw1913, _t1946);
                (void)_t1947;
                ;
                if (_t1947) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1944 = 123;
                    (void)_t1944;
                    Bool _t1945 = U8_eq(_sw1913, _t1944);
                    (void)_t1945;
                    ;
                    if (_t1945) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1942 = 125;
                        (void)_t1942;
                        Bool _t1943 = U8_eq(_sw1913, _t1942);
                        (void)_t1943;
                        ;
                        if (_t1943) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1940 = 91;
                            (void)_t1940;
                            Bool _t1941 = U8_eq(_sw1913, _t1940);
                            (void)_t1941;
                            ;
                            if (_t1941) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1938 = 93;
                                (void)_t1938;
                                Bool _t1939 = U8_eq(_sw1913, _t1938);
                                (void)_t1939;
                                ;
                                if (_t1939) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1936 = 44;
                                    (void)_t1936;
                                    Bool _t1937 = U8_eq(_sw1913, _t1936);
                                    (void)_t1937;
                                    ;
                                    if (_t1937) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1934 = 58;
                                        (void)_t1934;
                                        Bool _t1935 = U8_eq(_sw1913, _t1934);
                                        (void)_t1935;
                                        ;
                                        if (_t1935) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1932 = 46;
                                            (void)_t1932;
                                            Bool _t1933 = U8_eq(_sw1913, _t1932);
                                            (void)_t1933;
                                            ;
                                            if (_t1933) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1930 = 63;
                                                (void)_t1930;
                                                Bool _t1931 = U8_eq(_sw1913, _t1930);
                                                (void)_t1931;
                                                ;
                                                if (_t1931) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1928 = 33;
                                                    (void)_t1928;
                                                    Bool _t1929 = U8_eq(_sw1913, _t1928);
                                                    (void)_t1929;
                                                    ;
                                                    if (_t1929) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1926 = 43;
                                                        (void)_t1926;
                                                        Bool _t1927 = U8_eq(_sw1913, _t1926);
                                                        (void)_t1927;
                                                        ;
                                                        if (_t1927) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1924 = 45;
                                                            (void)_t1924;
                                                            Bool _t1925 = U8_eq(_sw1913, _t1924);
                                                            (void)_t1925;
                                                            ;
                                                            if (_t1925) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1922 = 42;
                                                                (void)_t1922;
                                                                Bool _t1923 = U8_eq(_sw1913, _t1922);
                                                                (void)_t1923;
                                                                ;
                                                                if (_t1923) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1920 = 47;
                                                                    (void)_t1920;
                                                                    Bool _t1921 = U8_eq(_sw1913, _t1920);
                                                                    (void)_t1921;
                                                                    ;
                                                                    if (_t1921) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1918 = 61;
                                                                        (void)_t1918;
                                                                        Bool _t1919 = U8_eq(_sw1913, _t1918);
                                                                        (void)_t1919;
                                                                        ;
                                                                        if (_t1919) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1916 = 60;
                                                                            (void)_t1916;
                                                                            Bool _t1917 = U8_eq(_sw1913, _t1916);
                                                                            (void)_t1917;
                                                                            ;
                                                                            if (_t1917) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1914 = 62;
                                                                                (void)_t1914;
                                                                                Bool _t1915 = U8_eq(_sw1913, _t1914);
                                                                                (void)_t1915;
                                                                                ;
                                                                                if (_t1915) {
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
        Bool _t1988; { Bool *_hp = (Bool *)TokenType_eq(single, TokenType_Eof()); _t1988 = *_hp; free(_hp); }
        (void)_t1988;
        Bool _t1989 = Bool_not(_t1988);
        (void)_t1989;
        ;
        if (_t1989) {
            U64 _t1950 = 1;
            (void)_t1950;
            I64 _t1951 = I64_clone(&(I64){line});
            (void)_t1951;
            I64 _t1952 = I64_clone(&(I64){col});
            (void)_t1952;
            Token *_t1953 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1953->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t1950}); _t1953->text = *_ca; free(_ca); }
            _t1953->line = _t1951;
            _t1953->col = _t1952;
            (void)_t1953;
            ;
            ;
            ;
            Vec_push(tokens, _t1953);
            U64 _t1954 = U64_inc(DEREF(pos));
            (void)_t1954;
            *pos = _t1954;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t1990 = Str_lit("Str", 3ULL);
        (void)_t1990;
        U64 _t1991; { U64 *_hp = (U64 *)Str_size(); _t1991 = *_hp; free(_hp); }
        (void)_t1991;
        U64 _t1992 = 6;
        (void)_t1992;
        Array *_va23 = Array_new(_t1990, &(U64){_t1991}, &(U64){_t1992});
        (void)_va23;
        Str_delete(_t1990, &(Bool){1});
        ;
        ;
        U64 _t1993 = 0;
        (void)_t1993;
        Str *_t1994 = Str_clone(path);
        (void)_t1994;
        Array_set(_va23, &(U64){_t1993}, _t1994);
        ;
        U64 _t1995 = 1;
        (void)_t1995;
        Str *_t1996 = Str_lit(":", 1ULL);
        (void)_t1996;
        Array_set(_va23, &(U64){_t1995}, _t1996);
        ;
        U64 _t1997 = 2;
        (void)_t1997;
        Str *_t1998 = I64_to_str(&(I64){line});
        (void)_t1998;
        Array_set(_va23, &(U64){_t1997}, _t1998);
        ;
        U64 _t1999 = 3;
        (void)_t1999;
        Str *_t2000 = Str_lit(":", 1ULL);
        (void)_t2000;
        Array_set(_va23, &(U64){_t1999}, _t2000);
        ;
        U64 _t2001 = 4;
        (void)_t2001;
        Str *_t2002 = I64_to_str(&(I64){col});
        (void)_t2002;
        Array_set(_va23, &(U64){_t2001}, _t2002);
        ;
        U64 _t2003 = 5;
        (void)_t2003;
        Str *_t2004 = Str_lit(": error: unexpected character", 29ULL);
        (void)_t2004;
        Array_set(_va23, &(U64){_t2003}, _t2004);
        ;
        println(_va23);
        U64 _t2005 = 1;
        (void)_t2005;
        I64 _t2006 = I64_clone(&(I64){col});
        (void)_t2006;
        ;
        Token *_t2007 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t2007->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(src, &(U64){start}, &(U64){_t2005}); _t2007->text = *_ca; free(_ca); }
        _t2007->line = I64_clone(&(I64){line});
        _t2007->col = _t2006;
        (void)_t2007;
        ;
        ;
        ;
        Vec_push(tokens, _t2007);
        U64 _t2008 = U64_inc(DEREF(pos));
        (void)_t2008;
        *pos = _t2008;
        ;
    }
    ;
    U64 _t2011 = U64_sub(DEREF(pos), line_start);
    (void)_t2011;
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t2012 = 1;
    (void)_t2012;
    U64 _t2013 = U64_add(_t2011, _t2012);
    (void)_t2013;
    ;
    ;
    I64 col = U64_to_i64(_t2013);
    (void)col;
    ;
    I64 _t2014 = I64_clone(&(I64){col});
    (void)_t2014;
    ;
    Token *_t2015 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2015->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2015->text = *_ca; free(_ca); }
    _t2015->line = I64_clone(&(I64){line});
    _t2015->col = _t2014;
    (void)_t2015;
    ;
    ;
    Vec_push(tokens, _t2015);
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
    _t2016 = malloc(sizeof(I64));
    *_t2016 = 0;
    (void)_t2016;
    _t2017 = malloc(sizeof(I64));
    *_t2017 = 1;
    (void)_t2017;
    _t2018 = malloc(sizeof(I64)); *_t2018 = I64_sub(DEREF(_t2016), DEREF(_t2017));
    (void)_t2018;
    CAP_LIT = malloc(sizeof(U64)); *CAP_LIT = I64_to_u64(DEREF(_t2018));
    (void)CAP_LIT;
    _t2019 = malloc(sizeof(I64));
    *_t2019 = 0;
    (void)_t2019;
    _t2020 = malloc(sizeof(I64));
    *_t2020 = 2;
    (void)_t2020;
    _t2021 = malloc(sizeof(I64)); *_t2021 = I64_sub(DEREF(_t2019), DEREF(_t2020));
    (void)_t2021;
    CAP_VIEW = malloc(sizeof(U64)); *CAP_VIEW = I64_to_u64(DEREF(_t2021));
    (void)CAP_VIEW;
}

