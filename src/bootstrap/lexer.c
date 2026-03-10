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
    I64 _t2 = U8_to_i64(DEREF(val));
    Str *_t3 = I64_to_str(&(I64){_t2});
    ;
    return _t3;
}

static __attribute__((unused)) U8 * U8_from_i64(I64 * val) {
    I64 _t10 = 0;
    I64 _t11 = 255;
    Bool _t12; { Bool *_hp = I64_lt(val, &(I64){_t10}); _t12 = *_hp; free(_hp); }
    ;
    Bool _t13; { Bool *_hp = I64_gt(val, &(I64){_t11}); _t13 = *_hp; free(_hp); }
    ;
    Bool _t14 = Bool_or(_t12, _t13);
    ;
    ;
    if (_t14) {
        Str *_t4 = Str_lit("Str", 3ULL);
        U64 _t5; { U64 *_hp = Str_size(); _t5 = *_hp; free(_hp); }
        U64 _t6 = 1;
        Array *_va0 = Array_new(_t4, &(U64){_t5}, &(U64){_t6});
        Str_delete(_t4, &(Bool){1});
        ;
        ;
        U64 _t7 = 0;
        Str *_t8 = Str_lit("value out of range (0-255)", 26ULL);
        Array_set(_va0, &(U64){_t7}, _t8);
        ;
        Str *_t9 = Str_lit("U8.from_i64", 11ULL);
        panic(_t9, _va0);
        Str_delete(_t9, &(Bool){1});
        Array_delete(_va0, &(Bool){1});
    }
    ;
    /* TODO: nested func U8_from_i64_ext */
    U8 _t15 = U8_from_i64_ext(val);
    { U8 *_r = malloc(sizeof(U8)); *_r = _t15; return _r; }
}

static U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b) {
    I64 _t17 = 0;
    I64 _t18 = 1;
    I64 _t19 = U8_cmp(DEREF(a), DEREF(b));
    I64 _t20 = I64_sub(_t17, _t18);
    ;
    ;
    Bool _t21 = I64_eq(_t19, _t20);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t21; return _r; }
}

static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b) {
    I64 _t22 = U8_cmp(DEREF(a), DEREF(b));
    I64 _t23 = 1;
    Bool _t24 = I64_eq(_t22, _t23);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t24; return _r; }
}

static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b) {
    Bool _t25 = U8_eq(DEREF(a), DEREF(b));
    Bool _t26 = Bool_not(_t25);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t26; return _r; }
}

static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b) {
    Bool _t27; { Bool *_hp = U8_gt(a, b); _t27 = *_hp; free(_hp); }
    Bool _t28 = Bool_not(_t27);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t28; return _r; }
}

static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b) {
    Bool _t29; { Bool *_hp = U8_lt(a, b); _t29 = *_hp; free(_hp); }
    Bool _t30 = Bool_not(_t29);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t30; return _r; }
}

static __attribute__((unused)) Str * I16_to_str(I16 * val) {
    I64 _t31 = I16_to_i64(DEREF(val));
    Str *_t32 = I64_to_str(&(I64){_t31});
    ;
    return _t32;
}

static __attribute__((unused)) I16 * I16_from_i64(I64 * val) {
    I64 _t39 = 32768;
    I64 _t40; { I64 *_hp = I64_neg(&(I64){_t39}); _t40 = *_hp; free(_hp); }
    ;
    I64 _t41 = 32767;
    Bool _t42; { Bool *_hp = I64_lt(val, &(I64){_t40}); _t42 = *_hp; free(_hp); }
    ;
    Bool _t43; { Bool *_hp = I64_gt(val, &(I64){_t41}); _t43 = *_hp; free(_hp); }
    ;
    Bool _t44 = Bool_or(_t42, _t43);
    ;
    ;
    if (_t44) {
        Str *_t33 = Str_lit("Str", 3ULL);
        U64 _t34; { U64 *_hp = Str_size(); _t34 = *_hp; free(_hp); }
        U64 _t35 = 1;
        Array *_va1 = Array_new(_t33, &(U64){_t34}, &(U64){_t35});
        Str_delete(_t33, &(Bool){1});
        ;
        ;
        U64 _t36 = 0;
        Str *_t37 = Str_lit("value out of range (-32768 to 32767)", 36ULL);
        Array_set(_va1, &(U64){_t36}, _t37);
        ;
        Str *_t38 = Str_lit("I16.from_i64", 12ULL);
        panic(_t38, _va1);
        Str_delete(_t38, &(Bool){1});
        Array_delete(_va1, &(Bool){1});
    }
    ;
    /* TODO: nested func I16_from_i64_ext */
    I16 _t45 = I16_from_i64_ext(val);
    { I16 *_r = malloc(sizeof(I16)); *_r = _t45; return _r; }
}

static __attribute__((unused)) I16 * I16_neg(I16 * a) {
    I64 _t46 = 0;
    I64 _t47 = I16_to_i64(DEREF(a));
    I64 _t48 = I64_sub(_t46, _t47);
    ;
    ;
    I16 _t49; { I16 *_hp = I16_from_i64(&(I64){_t48}); _t49 = *_hp; free(_hp); }
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t49; return _r; }
}

static __attribute__((unused)) I16 * I16_abs(I16 * a) {
    I64 _t54 = I16_to_i64(DEREF(a));
    I64 _t55 = 0;
    Bool _t56; { Bool *_hp = I64_lt(&(I64){_t54}, &(I64){_t55}); _t56 = *_hp; free(_hp); }
    ;
    ;
    if (_t56) {
        I64 _t50 = 0;
        I64 _t51 = I16_to_i64(DEREF(a));
        I64 _t52 = I64_sub(_t50, _t51);
        ;
        ;
        I16 _t53; { I16 *_hp = I16_from_i64(&(I64){_t52}); _t53 = *_hp; free(_hp); }
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t53; return _r; }
    }
    ;
    I16 _t57 = I16_clone(a);
    { I16 *_r = malloc(sizeof(I16)); *_r = _t57; return _r; }
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b) {
    I64 _t59 = 0;
    I64 _t60 = 1;
    I64 _t61 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t62 = I64_sub(_t59, _t60);
    ;
    ;
    Bool _t63 = I64_eq(_t61, _t62);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t63; return _r; }
}

static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b) {
    I64 _t64 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t65 = 1;
    Bool _t66 = I64_eq(_t64, _t65);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t66; return _r; }
}

static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b) {
    Bool _t67 = I16_eq(DEREF(a), DEREF(b));
    Bool _t68 = Bool_not(_t67);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t68; return _r; }
}

static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b) {
    Bool _t69; { Bool *_hp = I16_gt(a, b); _t69 = *_hp; free(_hp); }
    Bool _t70 = Bool_not(_t69);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t70; return _r; }
}

static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b) {
    Bool _t71; { Bool *_hp = I16_lt(a, b); _t71 = *_hp; free(_hp); }
    Bool _t72 = Bool_not(_t71);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t72; return _r; }
}

static __attribute__((unused)) Str * I32_to_str(I32 * val) {
    I64 _t73 = I32_to_i64(DEREF(val));
    Str *_t74 = I64_to_str(&(I64){_t73});
    ;
    return _t74;
}

static __attribute__((unused)) I32 * I32_from_i64(I64 * val) {
    I64 _t81 = 2147483648;
    I64 _t82; { I64 *_hp = I64_neg(&(I64){_t81}); _t82 = *_hp; free(_hp); }
    ;
    I64 _t83 = 2147483647;
    Bool _t84; { Bool *_hp = I64_lt(val, &(I64){_t82}); _t84 = *_hp; free(_hp); }
    ;
    Bool _t85; { Bool *_hp = I64_gt(val, &(I64){_t83}); _t85 = *_hp; free(_hp); }
    ;
    Bool _t86 = Bool_or(_t84, _t85);
    ;
    ;
    if (_t86) {
        Str *_t75 = Str_lit("Str", 3ULL);
        U64 _t76; { U64 *_hp = Str_size(); _t76 = *_hp; free(_hp); }
        U64 _t77 = 1;
        Array *_va2 = Array_new(_t75, &(U64){_t76}, &(U64){_t77});
        Str_delete(_t75, &(Bool){1});
        ;
        ;
        U64 _t78 = 0;
        Str *_t79 = Str_lit("value out of range (-2147483648 to 2147483647)", 46ULL);
        Array_set(_va2, &(U64){_t78}, _t79);
        ;
        Str *_t80 = Str_lit("I32.from_i64", 12ULL);
        panic(_t80, _va2);
        Str_delete(_t80, &(Bool){1});
        Array_delete(_va2, &(Bool){1});
    }
    ;
    /* TODO: nested func I32_from_i64_ext */
    I32 _t87 = I32_from_i64_ext(val);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t87; return _r; }
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    I64 _t88 = 0;
    I64 _t89 = I32_to_i64(DEREF(a));
    I64 _t90 = I64_sub(_t88, _t89);
    ;
    ;
    I32 _t91; { I32 *_hp = I32_from_i64(&(I64){_t90}); _t91 = *_hp; free(_hp); }
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t91; return _r; }
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    I64 _t96 = I32_to_i64(DEREF(a));
    I64 _t97 = 0;
    Bool _t98; { Bool *_hp = I64_lt(&(I64){_t96}, &(I64){_t97}); _t98 = *_hp; free(_hp); }
    ;
    ;
    if (_t98) {
        I64 _t92 = 0;
        I64 _t93 = I32_to_i64(DEREF(a));
        I64 _t94 = I64_sub(_t92, _t93);
        ;
        ;
        I32 _t95; { I32 *_hp = I32_from_i64(&(I64){_t94}); _t95 = *_hp; free(_hp); }
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t95; return _r; }
    }
    ;
    I32 _t99 = I32_clone(a);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t99; return _r; }
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    I64 _t101 = 0;
    I64 _t102 = 1;
    I64 _t103 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t104 = I64_sub(_t101, _t102);
    ;
    ;
    Bool _t105 = I64_eq(_t103, _t104);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t105; return _r; }
}

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    I64 _t106 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t107 = 1;
    Bool _t108 = I64_eq(_t106, _t107);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t108; return _r; }
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    Bool _t109 = I32_eq(DEREF(a), DEREF(b));
    Bool _t110 = Bool_not(_t109);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t110; return _r; }
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    Bool _t111; { Bool *_hp = I32_gt(a, b); _t111 = *_hp; free(_hp); }
    Bool _t112 = Bool_not(_t111);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t112; return _r; }
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    Bool _t113; { Bool *_hp = I32_lt(a, b); _t113 = *_hp; free(_hp); }
    Bool _t114 = Bool_not(_t113);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t114; return _r; }
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 _t115 = F32_from_i64_ext(val);
    { F32 *_r = malloc(sizeof(F32)); *_r = _t115; return _r; }
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    I64 _t117 = 0;
    I64 _t118 = 1;
    I64 _t119 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t120 = I64_sub(_t117, _t118);
    ;
    ;
    Bool _t121 = I64_eq(_t119, _t120);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t121; return _r; }
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    I64 _t122 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t123 = 1;
    Bool _t124 = I64_eq(_t122, _t123);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t124; return _r; }
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    Bool _t125 = F32_eq(DEREF(a), DEREF(b));
    Bool _t126 = Bool_not(_t125);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t126; return _r; }
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    Bool _t127; { Bool *_hp = F32_gt(a, b); _t127 = *_hp; free(_hp); }
    Bool _t128 = Bool_not(_t127);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t128; return _r; }
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    Bool _t129; { Bool *_hp = F32_lt(a, b); _t129 = *_hp; free(_hp); }
    Bool _t130 = Bool_not(_t129);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t130; return _r; }
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    I64 _t131 = U32_to_i64(DEREF(val));
    Str *_t132 = I64_to_str(&(I64){_t131});
    ;
    return _t132;
}

static __attribute__((unused)) U32 * U32_from_i64(I64 * val) {
    I64 _t139 = 0;
    I64 _t140 = 4294967295;
    Bool _t141; { Bool *_hp = I64_lt(val, &(I64){_t139}); _t141 = *_hp; free(_hp); }
    ;
    Bool _t142; { Bool *_hp = I64_gt(val, &(I64){_t140}); _t142 = *_hp; free(_hp); }
    ;
    Bool _t143 = Bool_or(_t141, _t142);
    ;
    ;
    if (_t143) {
        Str *_t133 = Str_lit("Str", 3ULL);
        U64 _t134; { U64 *_hp = Str_size(); _t134 = *_hp; free(_hp); }
        U64 _t135 = 1;
        Array *_va3 = Array_new(_t133, &(U64){_t134}, &(U64){_t135});
        Str_delete(_t133, &(Bool){1});
        ;
        ;
        U64 _t136 = 0;
        Str *_t137 = Str_lit("value out of range (0-4294967295)", 33ULL);
        Array_set(_va3, &(U64){_t136}, _t137);
        ;
        Str *_t138 = Str_lit("U32.from_i64", 12ULL);
        panic(_t138, _va3);
        Str_delete(_t138, &(Bool){1});
        Array_delete(_va3, &(Bool){1});
    }
    ;
    /* TODO: nested func U32_from_i64_ext */
    U32 _t144 = U32_from_i64_ext(val);
    { U32 *_r = malloc(sizeof(U32)); *_r = _t144; return _r; }
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    I64 _t146 = 0;
    I64 _t147 = 1;
    I64 _t148 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t149 = I64_sub(_t146, _t147);
    ;
    ;
    Bool _t150 = I64_eq(_t148, _t149);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t150; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    I64 _t151 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t152 = 1;
    Bool _t153 = I64_eq(_t151, _t152);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t153; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    Bool _t154 = U32_eq(DEREF(a), DEREF(b));
    Bool _t155 = Bool_not(_t154);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t155; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    Bool _t156; { Bool *_hp = U32_gt(a, b); _t156 = *_hp; free(_hp); }
    Bool _t157 = Bool_not(_t156);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t157; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    Bool _t158; { Bool *_hp = U32_lt(a, b); _t158 = *_hp; free(_hp); }
    Bool _t159 = Bool_not(_t158);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t159; return _r; }
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t160 = U64_to_str_ext(val);
    return _t160;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 _t161 = U64_from_i64_ext(val);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t161; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    I64 _t163 = 0;
    I64 _t164 = 1;
    I64 _t165 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t166 = I64_sub(_t163, _t164);
    ;
    ;
    Bool _t167 = I64_eq(_t165, _t166);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t167; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    I64 _t168 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t169 = 1;
    Bool _t170 = I64_eq(_t168, _t169);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t170; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    Bool _t171 = U64_eq(DEREF(a), DEREF(b));
    Bool _t172 = Bool_not(_t171);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t172; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    Bool _t173; { Bool *_hp = U64_gt(a, b); _t173 = *_hp; free(_hp); }
    Bool _t174 = Bool_not(_t173);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t174; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    Bool _t175; { Bool *_hp = U64_lt(a, b); _t175 = *_hp; free(_hp); }
    Bool _t176 = Bool_not(_t175);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t176; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    I64 _t216 = 0;
    Bool _t217 = I64_eq(DEREF(val), _t216);
    ;
    if (_t217) {
        U64 _t177 = 2;
        U8 *buf = malloc(_t177);
        ;
        I64 _t178 = 48;
        U8 _t179; { U8 *_hp = U8_from_i64(&(I64){_t178}); _t179 = *_hp; free(_hp); }
        ;
        U64 _t180 = 1;
        memcpy(buf, &(U8){_t179}, _t180);
        ;
        ;
        U64 *_t181 = malloc(sizeof(U64));
        *_t181 = 1;
        I64 _t182 = 0;
        void *_t183 = ptr_add(buf, DEREF(_t181));
        U8 _t184; { U8 *_hp = U8_from_i64(&(I64){_t182}); _t184 = *_hp; free(_hp); }
        ;
        U64 _t185 = 1;
        memcpy(_t183, &(U8){_t184}, _t185);
        U64_delete(_t181, &(Bool){1});
        ;
        ;
        I64 _t186 = 1;
        I64 _t187 = 1;
        Str *_t188 = malloc(sizeof(Str));
        _t188->c_str = buf;
        _t188->count = _t186;
        _t188->cap = _t187;
        ;
        ;
        ;
        return _t188;
    }
    ;
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 _t218 = 0;
    Bool _t219; { Bool *_hp = I64_lt(val, &(I64){_t218}); _t219 = *_hp; free(_hp); }
    ;
    if (_t219) {
        Bool _t189 = 1;
        is_neg = _t189;
        ;
        I64 _t190 = 0;
        I64 _t191 = I64_sub(_t190, DEREF(val));
        ;
        v = _t191;
        ;
    }
    ;
    U64 ndigits = 0;
    I64 tmp = I64_clone(&(I64){v});
    while (1) {
        I64 _t193 = 0;
        Bool _wcond192; { Bool *_hp = I64_gt(&(I64){tmp}, &(I64){_t193}); _wcond192 = *_hp; free(_hp); }
        ;
        if (_wcond192) {
        } else {
            ;
            break;
        }
        ;
        U64 _t194 = 1;
        U64 _t195 = U64_add(ndigits, _t194);
        ;
        ndigits = _t195;
        ;
        I64 _t196 = 10;
        I64 _t197 = I64_div(tmp, _t196);
        ;
        tmp = _t197;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    ;
    if (is_neg) {
        U64 _t198 = 1;
        U64 _t199 = U64_add(DEREF(total), _t198);
        ;
        *total = _t199;
        ;
    }
    U64 _t220 = 1;
    U64 _t221 = U64_add(DEREF(total), _t220);
    ;
    U8 *buf = malloc(_t221);
    ;
    if (is_neg) {
        I64 _t200 = 45;
        U8 _t201; { U8 *_hp = U8_from_i64(&(I64){_t200}); _t201 = *_hp; free(_hp); }
        ;
        U64 _t202 = 1;
        memcpy(buf, &(U8){_t201}, _t202);
        ;
        ;
    }
    ;
    U64 _t222 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t222);
    ;
    while (1) {
        I64 _t204 = 0;
        Bool _wcond203; { Bool *_hp = I64_gt(&(I64){v}, &(I64){_t204}); _wcond203 = *_hp; free(_hp); }
        ;
        if (_wcond203) {
        } else {
            ;
            break;
        }
        ;
        I64 _t205 = 10;
        I64 _t206 = I64_mod(v, _t205);
        ;
        I64 _t207 = 48;
        I64 _t208 = I64_add(_t206, _t207);
        ;
        ;
        void *_t209 = ptr_add(buf, DEREF(i));
        U8 _t210; { U8 *_hp = U8_from_i64(&(I64){_t208}); _t210 = *_hp; free(_hp); }
        ;
        U64 _t211 = 1;
        memcpy(_t209, &(U8){_t210}, _t211);
        ;
        ;
        I64 _t212 = 10;
        I64 _t213 = I64_div(v, _t212);
        ;
        v = _t213;
        ;
        U64 _t214 = 1;
        U64 _t215 = U64_sub(DEREF(i), _t214);
        ;
        *i = _t215;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t223 = 0;
    void *_t224 = ptr_add(buf, DEREF(total));
    U8 _t225; { U8 *_hp = U8_from_i64(&(I64){_t223}); _t225 = *_hp; free(_hp); }
    ;
    U64 _t226 = 1;
    memcpy(_t224, &(U8){_t225}, _t226);
    ;
    ;
    U64 _t227 = U64_clone(total);
    U64 _t228 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t229 = malloc(sizeof(Str));
    _t229->c_str = buf;
    _t229->count = _t227;
    _t229->cap = _t228;
    ;
    ;
    return _t229;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    I64 _t230 = 0;
    I64 _t231 = I64_sub(_t230, DEREF(a));
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t231; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    I64 _t234 = 0;
    Bool _t235; { Bool *_hp = I64_lt(a, &(I64){_t234}); _t235 = *_hp; free(_hp); }
    ;
    if (_t235) {
        I64 _t232 = 0;
        I64 _t233 = I64_sub(_t232, DEREF(a));
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t233; return _r; }
    }
    ;
    I64 _t236 = I64_clone(a);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t236; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    I64 _t238 = 0;
    I64 _t239 = 1;
    I64 _t240 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t241 = I64_sub(_t238, _t239);
    ;
    ;
    Bool _t242 = I64_eq(_t240, _t241);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t242; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    I64 _t243 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t244 = 1;
    Bool _t245 = I64_eq(_t243, _t244);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t245; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    Bool _t246 = I64_eq(DEREF(a), DEREF(b));
    Bool _t247 = Bool_not(_t246);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t247; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    Bool _t248; { Bool *_hp = I64_gt(a, b); _t248 = *_hp; free(_hp); }
    Bool _t249 = Bool_not(_t248);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t249; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    Bool _t250; { Bool *_hp = I64_lt(a, b); _t250 = *_hp; free(_hp); }
    Bool _t251 = Bool_not(_t250);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t251; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    U64 _t252 = U64_clone(&(U64){start});
    U64 _t253 = U64_clone(&(U64){end});
    Range *_t254 = malloc(sizeof(Range));
    _t254->start = _t252;
    _t254->end = _t253;
    ;
    ;
    return _t254;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t256; { Bool *_hp = U64_lte(&self->start, &self->end); _t256 = *_hp; free(_hp); }
    if (_t256) {
        U64 _t255 = U64_sub(self->end, self->start);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t255; return _r; }
    }
    ;
    U64 _t257 = U64_sub(self->start, self->end);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t257; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    Bool _t259; { Bool *_hp = U64_lte(&self->start, &self->end); _t259 = *_hp; free(_hp); }
    if (_t259) {
        U64 _t258 = U64_add(self->start, i);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t258; return _r; }
    }
    ;
    U64 _t260 = U64_sub(self->start, i);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t260; return _r; }
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
    Bool _t269 = Bool_eq(DEREF(a), DEREF(b));
    if (_t269) {
        I64 _t265 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t265; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t266 = 0;
        I64 _t267 = 1;
        I64 _t268 = I64_sub(_t266, _t267);
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t268; return _r; }
    }
    I64 _t270 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t270; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    I64 _t272 = 0;
    I64 _t273 = 1;
    I64 _t274; { I64 *_hp = Bool_cmp(a, b); _t274 = *_hp; free(_hp); }
    I64 _t275 = I64_sub(_t272, _t273);
    ;
    ;
    Bool _t276 = I64_eq(_t274, _t275);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t276; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    I64 _t277; { I64 *_hp = Bool_cmp(a, b); _t277 = *_hp; free(_hp); }
    I64 _t278 = 1;
    Bool _t279 = I64_eq(_t277, _t278);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t279; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    Bool _t280 = Bool_eq(DEREF(a), DEREF(b));
    Bool _t281 = Bool_not(_t280);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t281; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    Bool _t282; { Bool *_hp = Bool_gt(a, b); _t282 = *_hp; free(_hp); }
    Bool _t283 = Bool_not(_t282);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t283; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    Bool _t284; { Bool *_hp = Bool_lt(a, b); _t284 = *_hp; free(_hp); }
    Bool _t285 = Bool_not(_t284);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t285; return _r; }
}

void println(Array * parts) {
    {
        U64 *_fi286 = malloc(sizeof(U64));
        *_fi286 = 0;
        while (1) {
            U64 _t288; { U64 *_hp = Array_len(parts); _t288 = *_hp; free(_hp); }
            Bool _wcond287; { Bool *_hp = U64_lt(_fi286, &(U64){_t288}); _wcond287 = *_hp; free(_hp); }
            ;
            if (_wcond287) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi286);
            U64 _t289 = 1;
            U64 _t290 = U64_add(DEREF(_fi286), _t289);
            ;
            *_fi286 = _t290;
            ;
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
            U64 _t293; { U64 *_hp = Array_len(parts); _t293 = *_hp; free(_hp); }
            Bool _wcond292; { Bool *_hp = U64_lt(_fi291, &(U64){_t293}); _wcond292 = *_hp; free(_hp); }
            ;
            if (_wcond292) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi291);
            U64 _t294 = 1;
            U64 _t295 = U64_add(DEREF(_fi291), _t294);
            ;
            *_fi291 = _t295;
            ;
            print_single(s);
        }
        U64_delete(_fi291, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 total = 0;
    {
        U64 *_fi296 = malloc(sizeof(U64));
        *_fi296 = 0;
        while (1) {
            U64 _t298; { U64 *_hp = Array_len(parts); _t298 = *_hp; free(_hp); }
            Bool _wcond297; { Bool *_hp = U64_lt(_fi296, &(U64){_t298}); _wcond297 = *_hp; free(_hp); }
            ;
            if (_wcond297) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi296);
            U64 _t299 = 1;
            U64 _t300 = U64_add(DEREF(_fi296), _t299);
            ;
            *_fi296 = _t300;
            ;
            U64 _t301; { U64 *_hp = Str_len(s); _t301 = *_hp; free(_hp); }
            U64 _t302 = U64_add(total, _t301);
            ;
            total = _t302;
            ;
        }
        U64_delete(_fi296, &(Bool){1});
    }
    U8 *buf = malloc(total);
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi303 = malloc(sizeof(U64));
        *_fi303 = 0;
        while (1) {
            U64 _t305; { U64 *_hp = Array_len(parts); _t305 = *_hp; free(_hp); }
            Bool _wcond304; { Bool *_hp = U64_lt(_fi303, &(U64){_t305}); _wcond304 = *_hp; free(_hp); }
            ;
            if (_wcond304) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi303);
            U64 _t306 = 1;
            U64 _t307 = U64_add(DEREF(_fi303), _t306);
            ;
            *_fi303 = _t307;
            ;
            void *_t308 = ptr_add(buf, DEREF(offset));
            U64 _t309; { U64 *_hp = Str_len(s); _t309 = *_hp; free(_hp); }
            memcpy(_t308, s->c_str, _t309);
            ;
            U64 _t310; { U64 *_hp = Str_len(s); _t310 = *_hp; free(_hp); }
            U64 _t311 = U64_add(DEREF(offset), _t310);
            ;
            *offset = _t311;
            ;
        }
        U64_delete(_fi303, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t312 = U64_clone(&(U64){total});
    U64 _t313 = U64_clone(&(U64){total});
    ;
    Str *_t314 = malloc(sizeof(Str));
    _t314->c_str = buf;
    _t314->count = _t312;
    _t314->cap = _t313;
    ;
    ;
    return _t314;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        I64 _t315 = 0;
        I64 _t316 = 1;
        I64 _t317 = I64_sub(_t315, _t316);
        ;
        ;
        Bool _t318; { Bool *_hp = I64_neq(&(I64){status}, &(I64){_t317}); _t318 = *_hp; free(_hp); }
        ;
        if (_t318) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t319 = 50;
        sleep_ms(_t319);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t325; { U64 *_hp = Array_len(args); _t325 = *_hp; free(_hp); }
        Bool _wcond320; { Bool *_hp = U64_lt(i, &(U64){_t325}); _wcond320 = *_hp; free(_hp); }
        ;
        if (_wcond320) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        U64 _t326 = 0;
        Bool _t327; { Bool *_hp = U64_gt(i, &(U64){_t326}); _t327 = *_hp; free(_hp); }
        ;
        if (_t327) {
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
        ;
        U64 _t328 = 1;
        U64 _t329 = U64_add(DEREF(i), _t328);
        ;
        *i = _t329;
        ;
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
    I64 pid; { I64 *_hp = spawn_cmd(_t334); pid = *_hp; free(_hp); }
    Str_delete(_t334, &(Bool){1});
    I64 ec; { I64 *_hp = wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    ;
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 _t335; { U64 *_hp = Str_size(); _t335 = *_hp; free(_hp); }
    memcpy(output, content, _t335);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    Str *_t336 = Str_lit("Str", 3ULL);
    U64 _t337; { U64 *_hp = Str_size(); _t337 = *_hp; free(_hp); }
    U64 _t338 = 3;
    Array *_va4 = Array_new(_t336, &(U64){_t337}, &(U64){_t338});
    Str_delete(_t336, &(Bool){1});
    ;
    ;
    U64 _t339 = 0;
    Str *_t340 = Str_clone(loc_str);
    Array_set(_va4, &(U64){_t339}, _t340);
    ;
    U64 _t341 = 1;
    Str *_t342 = Str_lit(": panic: ", 9ULL);
    Array_set(_va4, &(U64){_t341}, _t342);
    ;
    U64 _t343 = 2;
    Str *_t344 = format(parts);
    Array_set(_va4, &(U64){_t343}, _t344);
    ;
    println(_va4);
    I64 _t345 = 1;
    exit(_t345);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t346 = Str_lit("Str", 3ULL);
    U64 _t347; { U64 *_hp = Str_size(); _t347 = *_hp; free(_hp); }
    U64 _t348 = 2;
    Array *_va5 = Array_new(_t346, &(U64){_t347}, &(U64){_t348});
    Str_delete(_t346, &(Bool){1});
    ;
    ;
    U64 _t349 = 0;
    Str *_t350 = Str_lit("TODO: ", 6ULL);
    Array_set(_va5, &(U64){_t349}, _t350);
    ;
    U64 _t351 = 1;
    Str *_t352 = format(parts);
    Array_set(_va5, &(U64){_t351}, _t352);
    ;
    panic(loc_str, _va5);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t353 = Str_lit("Str", 3ULL);
    U64 _t354; { U64 *_hp = Str_size(); _t354 = *_hp; free(_hp); }
    U64 _t355 = 1;
    Array *_va6 = Array_new(_t353, &(U64){_t354}, &(U64){_t355});
    Str_delete(_t353, &(Bool){1});
    ;
    ;
    U64 _t356 = 0;
    Str *_t357 = Str_lit("unreachable", 11ULL);
    Array_set(_va6, &(U64){_t356}, _t357);
    ;
    panic(loc_str, _va6);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool _t365 = Bool_not(DEREF(cond));
    if (_t365) {
        Str *_t358 = Str_lit("Str", 3ULL);
        U64 _t359; { U64 *_hp = Str_size(); _t359 = *_hp; free(_hp); }
        U64 _t360 = 2;
        Array *_va7 = Array_new(_t358, &(U64){_t359}, &(U64){_t360});
        Str_delete(_t358, &(Bool){1});
        ;
        ;
        U64 _t361 = 0;
        Str *_t362 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va7, &(U64){_t361}, _t362);
        ;
        U64 _t363 = 1;
        Str *_t364 = format(parts);
        Array_set(_va7, &(U64){_t363}, _t364);
        ;
        panic(loc_str, _va7);
    }
    ;
    Bool _t366 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t366; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t367 = Str_lit("Str", 3ULL);
    U64 _t368; { U64 *_hp = Str_size(); _t368 = *_hp; free(_hp); }
    U64 _t369 = 0;
    Array *_va8 = Array_new(_t367, &(U64){_t368}, &(U64){_t369});
    Str_delete(_t367, &(Bool){1});
    ;
    ;
    Bool _t370; { Bool *_hp = assertm(loc_str, cond, _va8); _t370 = *_hp; free(_hp); }
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t370; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t371 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool _t372; { Bool *_hp = assertm(loc_str, cond, _t371); _t372 = *_hp; free(_hp); }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool _t386; { Bool *_hp = I64_neq(a, b); _t386 = *_hp; free(_hp); }
    if (_t386) {
        Str *_t373 = Str_lit("Str", 3ULL);
        U64 _t374; { U64 *_hp = Str_size(); _t374 = *_hp; free(_hp); }
        U64 _t375 = 5;
        Array *_va9 = Array_new(_t373, &(U64){_t374}, &(U64){_t375});
        Str_delete(_t373, &(Bool){1});
        ;
        ;
        U64 _t376 = 0;
        Str *_t377 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va9, &(U64){_t376}, _t377);
        ;
        U64 _t378 = 1;
        Str *_t379 = I64_to_str(a);
        Array_set(_va9, &(U64){_t378}, _t379);
        ;
        U64 _t380 = 2;
        Str *_t381 = Str_lit("', found '", 10ULL);
        Array_set(_va9, &(U64){_t380}, _t381);
        ;
        U64 _t382 = 3;
        Str *_t383 = I64_to_str(b);
        Array_set(_va9, &(U64){_t382}, _t383);
        ;
        U64 _t384 = 4;
        Str *_t385 = Str_lit("'", 1ULL);
        Array_set(_va9, &(U64){_t384}, _t385);
        ;
        panic(loc_str, _va9);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool _t400; { Bool *_hp = Str_eq(a, b); _t400 = *_hp; free(_hp); }
    Bool _t401 = Bool_not(_t400);
    ;
    if (_t401) {
        Str *_t387 = Str_lit("Str", 3ULL);
        U64 _t388; { U64 *_hp = Str_size(); _t388 = *_hp; free(_hp); }
        U64 _t389 = 5;
        Array *_va10 = Array_new(_t387, &(U64){_t388}, &(U64){_t389});
        Str_delete(_t387, &(Bool){1});
        ;
        ;
        U64 _t390 = 0;
        Str *_t391 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va10, &(U64){_t390}, _t391);
        ;
        U64 _t392 = 1;
        Str *_t393 = Str_clone(a);
        Array_set(_va10, &(U64){_t392}, _t393);
        ;
        U64 _t394 = 2;
        Str *_t395 = Str_lit("', found '", 10ULL);
        Array_set(_va10, &(U64){_t394}, _t395);
        ;
        U64 _t396 = 3;
        Str *_t397 = Str_clone(b);
        Array_set(_va10, &(U64){_t396}, _t397);
        ;
        U64 _t398 = 4;
        Str *_t399 = Str_lit("'", 1ULL);
        Array_set(_va10, &(U64){_t398}, _t399);
        ;
        panic(loc_str, _va10);
    }
    ;
}

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    void *_t402 = calloc(DEREF(cap), DEREF(elem_size));
    U64 _t403 = U64_clone(cap);
    U64 _t404 = U64_clone(elem_size);
    Array *_t405 = malloc(sizeof(Array));
    _t405->data = _t402;
    _t405->cap = _t403;
    _t405->elem_size = _t404;
    { Str *_ca = Str_clone(elem_type); _t405->elem_type = *_ca; free(_ca); }
    ;
    ;
    return _t405;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    Bool _t420; { Bool *_hp = U64_gte(i, &self->cap); _t420 = *_hp; free(_hp); }
    if (_t420) {
        Str *_t406 = Str_lit("Str", 3ULL);
        U64 _t407; { U64 *_hp = Str_size(); _t407 = *_hp; free(_hp); }
        U64 _t408 = 5;
        Array *_va11 = Array_new(_t406, &(U64){_t407}, &(U64){_t408});
        Str_delete(_t406, &(Bool){1});
        ;
        ;
        U64 _t409 = 0;
        Str *_t410 = Str_lit("index ", 6ULL);
        Array_set(_va11, &(U64){_t409}, _t410);
        ;
        U64 _t411 = 1;
        Str *_t412 = U64_to_str(DEREF(i));
        Array_set(_va11, &(U64){_t411}, _t412);
        ;
        U64 _t413 = 2;
        Str *_t414 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va11, &(U64){_t413}, _t414);
        ;
        U64 _t415 = 3;
        Str *_t416 = U64_to_str(self->cap);
        Array_set(_va11, &(U64){_t415}, _t416);
        ;
        U64 _t417 = 4;
        Str *_t418 = Str_lit(")", 1ULL);
        Array_set(_va11, &(U64){_t417}, _t418);
        ;
        Str *_t419 = Str_lit("Array.get", 9ULL);
        panic(_t419, _va11);
        Str_delete(_t419, &(Bool){1});
    }
    ;
    U64 *_t421 = malloc(sizeof(U64)); *_t421 = U64_mul(DEREF(i), self->elem_size);
    void *_t422 = ptr_add(self->data, DEREF(_t421));
    U64_delete(_t421, &(Bool){1});
    return _t422;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    Bool _t437; { Bool *_hp = U64_gte(i, &self->cap); _t437 = *_hp; free(_hp); }
    if (_t437) {
        Str *_t423 = Str_lit("Str", 3ULL);
        U64 _t424; { U64 *_hp = Str_size(); _t424 = *_hp; free(_hp); }
        U64 _t425 = 5;
        Array *_va12 = Array_new(_t423, &(U64){_t424}, &(U64){_t425});
        Str_delete(_t423, &(Bool){1});
        ;
        ;
        U64 _t426 = 0;
        Str *_t427 = Str_lit("index ", 6ULL);
        Array_set(_va12, &(U64){_t426}, _t427);
        ;
        U64 _t428 = 1;
        Str *_t429 = U64_to_str(DEREF(i));
        Array_set(_va12, &(U64){_t428}, _t429);
        ;
        U64 _t430 = 2;
        Str *_t431 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va12, &(U64){_t430}, _t431);
        ;
        U64 _t432 = 3;
        Str *_t433 = U64_to_str(self->cap);
        Array_set(_va12, &(U64){_t432}, _t433);
        ;
        U64 _t434 = 4;
        Str *_t435 = Str_lit(")", 1ULL);
        Array_set(_va12, &(U64){_t434}, _t435);
        ;
        Str *_t436 = Str_lit("Array.set", 9ULL);
        panic(_t436, _va12);
        Str_delete(_t436, &(Bool){1});
    }
    ;
    U64 *_t438 = malloc(sizeof(U64)); *_t438 = U64_mul(DEREF(i), self->elem_size);
    void *_t439 = ptr_add(self->data, DEREF(_t438));
    Bool _t440 = 0;
    dyn_call_delete(&self->elem_type, _t439, &(Bool){_t440});
    U64_delete(_t438, &(Bool){1});
    ;
    U64 *_t441 = malloc(sizeof(U64)); *_t441 = U64_mul(DEREF(i), self->elem_size);
    void *_t442 = ptr_add(self->data, DEREF(_t441));
    memcpy(_t442, val, self->elem_size);
    U64_delete(_t441, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    {
        U64 _fi443 = 0;
        while (1) {
            U64 _t445 = 0;
            Range *_t446 = Range_new(_t445, self->cap);
            ;
            U64 _t447; { U64 *_hp = Range_len(_t446); _t447 = *_hp; free(_hp); }
            Range_delete(_t446, &(Bool){1});
            Bool _wcond444; { Bool *_hp = U64_lt(&(U64){_fi443}, &(U64){_t447}); _wcond444 = *_hp; free(_hp); }
            ;
            if (_wcond444) {
            } else {
                ;
                break;
            }
            ;
            U64 _t448 = 0;
            Range *_t449 = Range_new(_t448, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t449, _fi443); i = *_hp; free(_hp); }
            Range_delete(_t449, &(Bool){1});
            U64 _t450 = 1;
            U64 _t451 = U64_add(_fi443, _t450);
            ;
            _fi443 = _t451;
            ;
            U64 *_t452 = malloc(sizeof(U64)); *_t452 = U64_mul(i, self->elem_size);
            ;
            void *_t453 = ptr_add(self->data, DEREF(_t452));
            Bool _t454 = 0;
            dyn_call_delete(&self->elem_type, _t453, &(Bool){_t454});
            U64_delete(_t452, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t455 = 0;
    Str_delete(&self->elem_type, &(Bool){_t455});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t469 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t469);
    ;
    {
        U64 _fi456 = 0;
        while (1) {
            U64 _t458 = 0;
            Range *_t459 = Range_new(_t458, self->cap);
            ;
            U64 _t460; { U64 *_hp = Range_len(_t459); _t460 = *_hp; free(_hp); }
            Range_delete(_t459, &(Bool){1});
            Bool _wcond457; { Bool *_hp = U64_lt(&(U64){_fi456}, &(U64){_t460}); _wcond457 = *_hp; free(_hp); }
            ;
            if (_wcond457) {
            } else {
                ;
                break;
            }
            ;
            U64 _t461 = 0;
            Range *_t462 = Range_new(_t461, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t462, _fi456); i = *_hp; free(_hp); }
            Range_delete(_t462, &(Bool){1});
            U64 _t463 = 1;
            U64 _t464 = U64_add(_fi456, _t463);
            ;
            _fi456 = _t464;
            ;
            U64 *_t465 = malloc(sizeof(U64)); *_t465 = U64_mul(i, self->elem_size);
            void *_t466 = ptr_add(self->data, DEREF(_t465));
            void *cloned = dyn_call_clone(&self->elem_type, _t466);
            U64_delete(_t465, &(Bool){1});
            U64 *_t467 = malloc(sizeof(U64)); *_t467 = U64_mul(i, self->elem_size);
            ;
            void *_t468 = ptr_add(new_data, DEREF(_t467));
            memcpy(_t468, cloned, self->elem_size);
            U64_delete(_t467, &(Bool){1});
            free(cloned);
        }
        ;
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
    Bool _t484; { Bool *_hp = Str_is_empty(key_type); _t484 = *_hp; free(_hp); }
    Bool _t485 = Bool_not(_t484);
    ;
    if (_t485) {
        Bool _t482 = dyn_has_cmp(key_type);
        Bool _t483 = Bool_not(_t482);
        ;
        if (_t483) {
            Str *_t472 = Str_lit("Str", 3ULL);
            U64 _t473; { U64 *_hp = Str_size(); _t473 = *_hp; free(_hp); }
            U64 _t474 = 3;
            Array *_va13 = Array_new(_t472, &(U64){_t473}, &(U64){_t474});
            Str_delete(_t472, &(Bool){1});
            ;
            ;
            U64 _t475 = 0;
            Str *_t476 = Str_lit("type ", 5ULL);
            Array_set(_va13, &(U64){_t475}, _t476);
            ;
            U64 _t477 = 1;
            Str *_t478 = Str_clone(key_type);
            Array_set(_va13, &(U64){_t477}, _t478);
            ;
            U64 _t479 = 2;
            Str *_t480 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va13, &(U64){_t479}, _t480);
            ;
            Str *_t481 = Str_lit("Map.new", 7ULL);
            panic(_t481, _va13);
            Str_delete(_t481, &(Bool){1});
        }
        ;
    }
    ;
    void *_t486 = malloc(DEREF(key_size));
    void *_t487 = malloc(DEREF(val_size));
    U64 _t488 = 0;
    I64 _t489 = 1;
    U64 _t490 = U64_clone(key_size);
    U64 _t491 = U64_clone(val_size);
    Map *_t492 = malloc(sizeof(Map));
    _t492->key_data = _t486;
    _t492->val_data = _t487;
    _t492->count = _t488;
    _t492->cap = _t489;
    _t492->key_size = _t490;
    { Str *_ca = Str_clone(key_type); _t492->key_type = *_ca; free(_ca); }
    _t492->val_size = _t491;
    { Str *_ca = Str_clone(val_type); _t492->val_type = *_ca; free(_ca); }
    ;
    ;
    ;
    ;
    return _t492;
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
        Bool _wcond493; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond493 = *_hp; free(_hp); }
        if (_wcond493) {
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
            U64 _t494 = 1;
            U64 _t495 = U64_add(DEREF(mid), _t494);
            ;
            lo = _t495;
            ;
        } else {
            I64 _t498 = 0;
            Bool _t499; { Bool *_hp = I64_gt(c, &(I64){_t498}); _t499 = *_hp; free(_hp); }
            ;
            if (_t499) {
                U64 _t496 = U64_clone(mid);
                hi = _t496;
                ;
            } else {
                Bool _t497 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t497; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t507 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t507; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond508; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond508 = *_hp; free(_hp); }
        if (_wcond508) {
        } else {
            ;
            break;
        }
        ;
        U64 _t516 = U64_sub(hi, lo);
        U64 _t517 = 2;
        U64 _t518 = U64_div(_t516, _t517);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t518);
        ;
        U64 *_t519 = malloc(sizeof(U64)); *_t519 = U64_mul(DEREF(mid), self->key_size);
        void *_t520 = ptr_add(self->key_data, DEREF(_t519));
        I64 *c = dyn_call_cmp(&self->key_type, _t520, key);
        U64_delete(_t519, &(Bool){1});
        I64 _t521 = 0;
        Bool _t522; { Bool *_hp = I64_lt(c, &(I64){_t521}); _t522 = *_hp; free(_hp); }
        ;
        if (_t522) {
            U64 _t509 = 1;
            U64 _t510 = U64_add(DEREF(mid), _t509);
            ;
            lo = _t510;
            ;
        } else {
            I64 _t514 = 0;
            Bool _t515; { Bool *_hp = I64_gt(c, &(I64){_t514}); _t515 = *_hp; free(_hp); }
            ;
            if (_t515) {
                U64 _t511 = U64_clone(mid);
                hi = _t511;
                ;
            } else {
                U64 *_t512 = malloc(sizeof(U64)); *_t512 = U64_mul(DEREF(mid), self->val_size);
                void *_t513 = ptr_add(self->val_data, DEREF(_t512));
                U64_delete(_t512, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t513;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t523 = Str_lit("Str", 3ULL);
    U64 _t524; { U64 *_hp = Str_size(); _t524 = *_hp; free(_hp); }
    U64 _t525 = 1;
    Array *_va14 = Array_new(_t523, &(U64){_t524}, &(U64){_t525});
    Str_delete(_t523, &(Bool){1});
    ;
    ;
    U64 _t526 = 0;
    Str *_t527 = Str_lit("key not found", 13ULL);
    Array_set(_va14, &(U64){_t526}, _t527);
    ;
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
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond531; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond531 = *_hp; free(_hp); }
        if (_wcond531) {
        } else {
            ;
            break;
        }
        ;
        U64 _t540 = U64_sub(hi, lo);
        U64 _t541 = 2;
        U64 _t542 = U64_div(_t540, _t541);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t542);
        ;
        U64 *_t543 = malloc(sizeof(U64)); *_t543 = U64_mul(DEREF(mid), self->key_size);
        void *_t544 = ptr_add(self->key_data, DEREF(_t543));
        I64 *c = dyn_call_cmp(&self->key_type, _t544, key);
        U64_delete(_t543, &(Bool){1});
        I64 _t545 = 0;
        Bool _t546; { Bool *_hp = I64_lt(c, &(I64){_t545}); _t546 = *_hp; free(_hp); }
        ;
        if (_t546) {
            U64 _t532 = 1;
            U64 _t533 = U64_add(DEREF(mid), _t532);
            ;
            lo = _t533;
            ;
        } else {
            I64 _t538 = 0;
            Bool _t539; { Bool *_hp = I64_gt(c, &(I64){_t538}); _t539 = *_hp; free(_hp); }
            ;
            if (_t539) {
                U64 _t534 = U64_clone(mid);
                hi = _t534;
                ;
            } else {
                Bool _t535 = 1;
                found = _t535;
                ;
                U64 _t536 = U64_clone(mid);
                lo = _t536;
                ;
                U64 _t537 = U64_clone(mid);
                hi = _t537;
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
        Bool _t551; { Bool *_hp = Str_is_empty(&self->key_type); _t551 = *_hp; free(_hp); }
        Bool _t552 = Bool_not(_t551);
        ;
        if (_t552) {
            Bool _t547 = 0;
            dyn_call_delete(&self->key_type, key, &(Bool){_t547});
            ;
        }
        ;
        free(key);
        Bool _t553; { Bool *_hp = Str_is_empty(&self->val_type); _t553 = *_hp; free(_hp); }
        Bool _t554 = Bool_not(_t553);
        ;
        if (_t554) {
            U64 *_t548 = malloc(sizeof(U64)); *_t548 = U64_mul(lo, self->val_size);
            void *_t549 = ptr_add(self->val_data, DEREF(_t548));
            Bool _t550 = 0;
            dyn_call_delete(&self->val_type, _t549, &(Bool){_t550});
            U64_delete(_t548, &(Bool){1});
            ;
        }
        ;
        U64 *_t555 = malloc(sizeof(U64)); *_t555 = U64_mul(lo, self->val_size);
        void *_t556 = ptr_add(self->val_data, DEREF(_t555));
        memcpy(_t556, val, self->val_size);
        U64_delete(_t555, &(Bool){1});
        free(val);
    } else {
        Bool _t563 = U64_eq(self->count, self->cap);
        if (_t563) {
            U64 _t557 = 2;
            U64 new_cap = U64_mul(self->cap, _t557);
            ;
            U64 _t558 = U64_mul(new_cap, self->key_size);
            void *_t559 = realloc(self->key_data, _t558);
            ;
            self->key_data = _t559;
            U64 _t560 = U64_mul(new_cap, self->val_size);
            void *_t561 = realloc(self->val_data, _t560);
            ;
            self->val_data = _t561;
            U64 _t562 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t562;
            ;
        }
        ;
        U64 _t564 = 1;
        U64 _t565 = U64_add(lo, _t564);
        ;
        U64 *_t566 = malloc(sizeof(U64)); *_t566 = U64_mul(_t565, self->key_size);
        ;
        U64 *_t567 = malloc(sizeof(U64)); *_t567 = U64_mul(lo, self->key_size);
        U64 _t568 = U64_sub(self->count, lo);
        void *_t569 = ptr_add(self->key_data, DEREF(_t566));
        void *_t570 = ptr_add(self->key_data, DEREF(_t567));
        U64 _t571 = U64_mul(_t568, self->key_size);
        ;
        memmove(_t569, _t570, _t571);
        U64_delete(_t566, &(Bool){1});
        U64_delete(_t567, &(Bool){1});
        ;
        U64 _t572 = 1;
        U64 _t573 = U64_add(lo, _t572);
        ;
        U64 *_t574 = malloc(sizeof(U64)); *_t574 = U64_mul(_t573, self->val_size);
        ;
        U64 *_t575 = malloc(sizeof(U64)); *_t575 = U64_mul(lo, self->val_size);
        U64 _t576 = U64_sub(self->count, lo);
        void *_t577 = ptr_add(self->val_data, DEREF(_t574));
        void *_t578 = ptr_add(self->val_data, DEREF(_t575));
        U64 _t579 = U64_mul(_t576, self->val_size);
        ;
        memmove(_t577, _t578, _t579);
        U64_delete(_t574, &(Bool){1});
        U64_delete(_t575, &(Bool){1});
        ;
        U64 *_t580 = malloc(sizeof(U64)); *_t580 = U64_mul(lo, self->key_size);
        void *_t581 = ptr_add(self->key_data, DEREF(_t580));
        memcpy(_t581, key, self->key_size);
        U64_delete(_t580, &(Bool){1});
        U64 *_t582 = malloc(sizeof(U64)); *_t582 = U64_mul(lo, self->val_size);
        void *_t583 = ptr_add(self->val_data, DEREF(_t582));
        memcpy(_t583, val, self->val_size);
        U64_delete(_t582, &(Bool){1});
        free(key);
        free(val);
        U64 _t584 = 1;
        U64 _t585 = U64_add(self->count, _t584);
        ;
        self->count = _t585;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    Bool _t612; { Bool *_hp = Str_is_empty(&self->key_type); _t612 = *_hp; free(_hp); }
    Bool _t613 = Bool_not(_t612);
    ;
    if (_t613) {
        {
            U64 _fi586 = 0;
            while (1) {
                U64 _t588 = 0;
                Range *_t589 = Range_new(_t588, self->count);
                ;
                U64 _t590; { U64 *_hp = Range_len(_t589); _t590 = *_hp; free(_hp); }
                Range_delete(_t589, &(Bool){1});
                Bool _wcond587; { Bool *_hp = U64_lt(&(U64){_fi586}, &(U64){_t590}); _wcond587 = *_hp; free(_hp); }
                ;
                if (_wcond587) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t591 = 0;
                Range *_t592 = Range_new(_t591, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t592, _fi586); i = *_hp; free(_hp); }
                Range_delete(_t592, &(Bool){1});
                U64 _t593 = 1;
                U64 _t594 = U64_add(_fi586, _t593);
                ;
                _fi586 = _t594;
                ;
                U64 *_t595 = malloc(sizeof(U64)); *_t595 = U64_mul(i, self->key_size);
                ;
                void *_t596 = ptr_add(self->key_data, DEREF(_t595));
                Bool _t597 = 0;
                dyn_call_delete(&self->key_type, _t596, &(Bool){_t597});
                U64_delete(_t595, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t614; { Bool *_hp = Str_is_empty(&self->val_type); _t614 = *_hp; free(_hp); }
    Bool _t615 = Bool_not(_t614);
    ;
    if (_t615) {
        {
            U64 _fi598 = 0;
            while (1) {
                U64 _t600 = 0;
                Range *_t601 = Range_new(_t600, self->count);
                ;
                U64 _t602; { U64 *_hp = Range_len(_t601); _t602 = *_hp; free(_hp); }
                Range_delete(_t601, &(Bool){1});
                Bool _wcond599; { Bool *_hp = U64_lt(&(U64){_fi598}, &(U64){_t602}); _wcond599 = *_hp; free(_hp); }
                ;
                if (_wcond599) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t603 = 0;
                Range *_t604 = Range_new(_t603, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t604, _fi598); i = *_hp; free(_hp); }
                Range_delete(_t604, &(Bool){1});
                U64 _t605 = 1;
                U64 _t606 = U64_add(_fi598, _t605);
                ;
                _fi598 = _t606;
                ;
                U64 *_t607 = malloc(sizeof(U64)); *_t607 = U64_mul(i, self->val_size);
                ;
                void *_t608 = ptr_add(self->val_data, DEREF(_t607));
                Bool _t609 = 0;
                dyn_call_delete(&self->val_type, _t608, &(Bool){_t609});
                U64_delete(_t607, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t616; { Bool *_hp = Str_is_empty(&self->key_type); _t616 = *_hp; free(_hp); }
    Bool _t617 = Bool_not(_t616);
    ;
    if (_t617) {
        Bool _t610 = 0;
        Str_delete(&self->key_type, &(Bool){_t610});
        ;
    }
    ;
    Bool _t618; { Bool *_hp = Str_is_empty(&self->val_type); _t618 = *_hp; free(_hp); }
    Bool _t619 = Bool_not(_t618);
    ;
    if (_t619) {
        Bool _t611 = 0;
        Str_delete(&self->val_type, &(Bool){_t611});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t637 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(_t637);
    ;
    U64 _t638 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(_t638);
    ;
    {
        U64 _fi620 = 0;
        while (1) {
            U64 _t622 = 0;
            Range *_t623 = Range_new(_t622, self->count);
            ;
            U64 _t624; { U64 *_hp = Range_len(_t623); _t624 = *_hp; free(_hp); }
            Range_delete(_t623, &(Bool){1});
            Bool _wcond621; { Bool *_hp = U64_lt(&(U64){_fi620}, &(U64){_t624}); _wcond621 = *_hp; free(_hp); }
            ;
            if (_wcond621) {
            } else {
                ;
                break;
            }
            ;
            U64 _t625 = 0;
            Range *_t626 = Range_new(_t625, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t626, _fi620); i = *_hp; free(_hp); }
            Range_delete(_t626, &(Bool){1});
            U64 _t627 = 1;
            U64 _t628 = U64_add(_fi620, _t627);
            ;
            _fi620 = _t628;
            ;
            U64 *_t629 = malloc(sizeof(U64)); *_t629 = U64_mul(i, self->key_size);
            void *_t630 = ptr_add(self->key_data, DEREF(_t629));
            void *ck = dyn_call_clone(&self->key_type, _t630);
            U64_delete(_t629, &(Bool){1});
            U64 *_t631 = malloc(sizeof(U64)); *_t631 = U64_mul(i, self->key_size);
            void *_t632 = ptr_add(new_keys, DEREF(_t631));
            memcpy(_t632, ck, self->key_size);
            U64_delete(_t631, &(Bool){1});
            free(ck);
            U64 *_t633 = malloc(sizeof(U64)); *_t633 = U64_mul(i, self->val_size);
            void *_t634 = ptr_add(self->val_data, DEREF(_t633));
            void *cv = dyn_call_clone(&self->val_type, _t634);
            U64_delete(_t633, &(Bool){1});
            U64 *_t635 = malloc(sizeof(U64)); *_t635 = U64_mul(i, self->val_size);
            ;
            void *_t636 = ptr_add(new_vals, DEREF(_t635));
            memcpy(_t636, cv, self->val_size);
            U64_delete(_t635, &(Bool){1});
            free(cv);
        }
        ;
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
    Bool _t653; { Bool *_hp = Str_is_empty(elem_type); _t653 = *_hp; free(_hp); }
    Bool _t654 = Bool_not(_t653);
    ;
    if (_t654) {
        Bool _t651 = dyn_has_cmp(elem_type);
        Bool _t652 = Bool_not(_t651);
        ;
        if (_t652) {
            Str *_t641 = Str_lit("Str", 3ULL);
            U64 _t642; { U64 *_hp = Str_size(); _t642 = *_hp; free(_hp); }
            U64 _t643 = 3;
            Array *_va15 = Array_new(_t641, &(U64){_t642}, &(U64){_t643});
            Str_delete(_t641, &(Bool){1});
            ;
            ;
            U64 _t644 = 0;
            Str *_t645 = Str_lit("type ", 5ULL);
            Array_set(_va15, &(U64){_t644}, _t645);
            ;
            U64 _t646 = 1;
            Str *_t647 = Str_clone(elem_type);
            Array_set(_va15, &(U64){_t646}, _t647);
            ;
            U64 _t648 = 2;
            Str *_t649 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va15, &(U64){_t648}, _t649);
            ;
            Str *_t650 = Str_lit("Set.new", 7ULL);
            panic(_t650, _va15);
            Str_delete(_t650, &(Bool){1});
        }
        ;
    }
    ;
    void *_t655 = malloc(DEREF(elem_size));
    U64 _t656 = 0;
    I64 _t657 = 1;
    U64 _t658 = U64_clone(elem_size);
    Set *_t659 = malloc(sizeof(Set));
    _t659->data = _t655;
    _t659->count = _t656;
    _t659->cap = _t657;
    _t659->elem_size = _t658;
    { Str *_ca = Str_clone(elem_type); _t659->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t659;
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
        Bool _wcond660; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond660 = *_hp; free(_hp); }
        if (_wcond660) {
        } else {
            ;
            break;
        }
        ;
        U64 _t667 = U64_sub(hi, lo);
        U64 _t668 = 2;
        U64 _t669 = U64_div(_t667, _t668);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t669);
        ;
        U64 *_t670 = malloc(sizeof(U64)); *_t670 = U64_mul(DEREF(mid), self->elem_size);
        void *_t671 = ptr_add(self->data, DEREF(_t670));
        I64 *c = dyn_call_cmp(&self->elem_type, _t671, val);
        U64_delete(_t670, &(Bool){1});
        I64 _t672 = 0;
        Bool _t673; { Bool *_hp = I64_lt(c, &(I64){_t672}); _t673 = *_hp; free(_hp); }
        ;
        if (_t673) {
            U64 _t661 = 1;
            U64 _t662 = U64_add(DEREF(mid), _t661);
            ;
            lo = _t662;
            ;
        } else {
            I64 _t665 = 0;
            Bool _t666; { Bool *_hp = I64_gt(c, &(I64){_t665}); _t666 = *_hp; free(_hp); }
            ;
            if (_t666) {
                U64 _t663 = U64_clone(mid);
                hi = _t663;
                ;
            } else {
                Bool _t664 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t664; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t674 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t674; return _r; }
}

void Set_add(Set * self, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond675; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond675 = *_hp; free(_hp); }
        if (_wcond675) {
        } else {
            ;
            break;
        }
        ;
        U64 _t684 = U64_sub(hi, lo);
        U64 _t685 = 2;
        U64 _t686 = U64_div(_t684, _t685);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t686);
        ;
        U64 *_t687 = malloc(sizeof(U64)); *_t687 = U64_mul(DEREF(mid), self->elem_size);
        void *_t688 = ptr_add(self->data, DEREF(_t687));
        I64 *c = dyn_call_cmp(&self->elem_type, _t688, val);
        U64_delete(_t687, &(Bool){1});
        I64 _t689 = 0;
        Bool _t690; { Bool *_hp = I64_lt(c, &(I64){_t689}); _t690 = *_hp; free(_hp); }
        ;
        if (_t690) {
            U64 _t676 = 1;
            U64 _t677 = U64_add(DEREF(mid), _t676);
            ;
            lo = _t677;
            ;
        } else {
            I64 _t682 = 0;
            Bool _t683; { Bool *_hp = I64_gt(c, &(I64){_t682}); _t683 = *_hp; free(_hp); }
            ;
            if (_t683) {
                U64 _t678 = U64_clone(mid);
                hi = _t678;
                ;
            } else {
                Bool _t679 = 1;
                found = _t679;
                ;
                U64 _t680 = U64_clone(mid);
                lo = _t680;
                ;
                U64 _t681 = U64_clone(mid);
                hi = _t681;
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
        Bool _t692; { Bool *_hp = Str_is_empty(&self->elem_type); _t692 = *_hp; free(_hp); }
        Bool _t693 = Bool_not(_t692);
        ;
        if (_t693) {
            Bool _t691 = 0;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t691});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t698 = U64_eq(self->count, self->cap);
        if (_t698) {
            U64 _t694 = 2;
            U64 new_cap = U64_mul(self->cap, _t694);
            ;
            U64 _t695 = U64_mul(new_cap, self->elem_size);
            void *_t696 = realloc(self->data, _t695);
            ;
            self->data = _t696;
            U64 _t697 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t697;
            ;
        }
        ;
        U64 _t699 = 1;
        U64 _t700 = U64_add(lo, _t699);
        ;
        U64 *_t701 = malloc(sizeof(U64)); *_t701 = U64_mul(_t700, self->elem_size);
        ;
        U64 *_t702 = malloc(sizeof(U64)); *_t702 = U64_mul(lo, self->elem_size);
        U64 _t703 = U64_sub(self->count, lo);
        void *_t704 = ptr_add(self->data, DEREF(_t701));
        void *_t705 = ptr_add(self->data, DEREF(_t702));
        U64 _t706 = U64_mul(_t703, self->elem_size);
        ;
        memmove(_t704, _t705, _t706);
        U64_delete(_t701, &(Bool){1});
        U64_delete(_t702, &(Bool){1});
        ;
        U64 *_t707 = malloc(sizeof(U64)); *_t707 = U64_mul(lo, self->elem_size);
        void *_t708 = ptr_add(self->data, DEREF(_t707));
        memcpy(_t708, val, self->elem_size);
        U64_delete(_t707, &(Bool){1});
        free(val);
        U64 _t709 = 1;
        U64 _t710 = U64_add(self->count, _t709);
        ;
        self->count = _t710;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    Bool _t724; { Bool *_hp = Str_is_empty(&self->elem_type); _t724 = *_hp; free(_hp); }
    Bool _t725 = Bool_not(_t724);
    ;
    if (_t725) {
        {
            U64 _fi711 = 0;
            while (1) {
                U64 _t713 = 0;
                Range *_t714 = Range_new(_t713, self->count);
                ;
                U64 _t715; { U64 *_hp = Range_len(_t714); _t715 = *_hp; free(_hp); }
                Range_delete(_t714, &(Bool){1});
                Bool _wcond712; { Bool *_hp = U64_lt(&(U64){_fi711}, &(U64){_t715}); _wcond712 = *_hp; free(_hp); }
                ;
                if (_wcond712) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t716 = 0;
                Range *_t717 = Range_new(_t716, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t717, _fi711); i = *_hp; free(_hp); }
                Range_delete(_t717, &(Bool){1});
                U64 _t718 = 1;
                U64 _t719 = U64_add(_fi711, _t718);
                ;
                _fi711 = _t719;
                ;
                U64 *_t720 = malloc(sizeof(U64)); *_t720 = U64_mul(i, self->elem_size);
                ;
                void *_t721 = ptr_add(self->data, DEREF(_t720));
                Bool _t722 = 0;
                dyn_call_delete(&self->elem_type, _t721, &(Bool){_t722});
                U64_delete(_t720, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t726; { Bool *_hp = Str_is_empty(&self->elem_type); _t726 = *_hp; free(_hp); }
    Bool _t727 = Bool_not(_t726);
    ;
    if (_t727) {
        Bool _t723 = 0;
        Str_delete(&self->elem_type, &(Bool){_t723});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t741 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t741);
    ;
    {
        U64 _fi728 = 0;
        while (1) {
            U64 _t730 = 0;
            Range *_t731 = Range_new(_t730, self->count);
            ;
            U64 _t732; { U64 *_hp = Range_len(_t731); _t732 = *_hp; free(_hp); }
            Range_delete(_t731, &(Bool){1});
            Bool _wcond729; { Bool *_hp = U64_lt(&(U64){_fi728}, &(U64){_t732}); _wcond729 = *_hp; free(_hp); }
            ;
            if (_wcond729) {
            } else {
                ;
                break;
            }
            ;
            U64 _t733 = 0;
            Range *_t734 = Range_new(_t733, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t734, _fi728); i = *_hp; free(_hp); }
            Range_delete(_t734, &(Bool){1});
            U64 _t735 = 1;
            U64 _t736 = U64_add(_fi728, _t735);
            ;
            _fi728 = _t736;
            ;
            U64 *_t737 = malloc(sizeof(U64)); *_t737 = U64_mul(i, self->elem_size);
            void *_t738 = ptr_add(self->data, DEREF(_t737));
            void *cloned = dyn_call_clone(&self->elem_type, _t738);
            U64_delete(_t737, &(Bool){1});
            U64 *_t739 = malloc(sizeof(U64)); *_t739 = U64_mul(i, self->elem_size);
            ;
            void *_t740 = ptr_add(new_data, DEREF(_t739));
            memcpy(_t740, cloned, self->elem_size);
            U64_delete(_t739, &(Bool){1});
            free(cloned);
        }
        ;
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
    Bool _t750; { Bool *_hp = U64_gte(i, &self->count); _t750 = *_hp; free(_hp); }
    if (_t750) {
        Str *_t744 = Str_lit("Str", 3ULL);
        U64 _t745; { U64 *_hp = Str_size(); _t745 = *_hp; free(_hp); }
        U64 _t746 = 1;
        Array *_va16 = Array_new(_t744, &(U64){_t745}, &(U64){_t746});
        Str_delete(_t744, &(Bool){1});
        ;
        ;
        U64 _t747 = 0;
        Str *_t748 = Str_lit("index out of bounds", 19ULL);
        Array_set(_va16, &(U64){_t747}, _t748);
        ;
        Str *_t749 = Str_lit("Str.get", 7ULL);
        panic(_t749, _va16);
        Str_delete(_t749, &(Bool){1});
    }
    ;
    void *_t751 = ptr_add(self->c_str, DEREF(i));
    return _t751;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 min_len = a->count;
    Bool _t757; { Bool *_hp = U64_lt(&b->count, &a->count); _t757 = *_hp; free(_hp); }
    if (_t757) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond752; { Bool *_hp = U64_lt(i, &(U64){min_len}); _wcond752 = *_hp; free(_hp); }
        if (_wcond752) {
        } else {
            ;
            break;
        }
        ;
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 _t753 = 0;
        Bool _t754; { Bool *_hp = I64_neq(c, &(I64){_t753}); _t754 = *_hp; free(_hp); }
        ;
        if (_t754) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t755 = 1;
        U64 _t756 = U64_add(DEREF(i), _t755);
        ;
        *i = _t756;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t758 = U64_cmp(a->count, b->count);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t758; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    U64 _t759 = 1;
    U64 _t760 = U64_add(DEREF(new_len), _t759);
    ;
    U8 *new_data = malloc(_t760);
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t761 = ptr_add(new_data, a->count);
    memcpy(_t761, b->c_str, b->count);
    I64 _t762 = 0;
    void *_t763 = ptr_add(new_data, DEREF(new_len));
    U8 _t764; { U8 *_hp = U8_from_i64(&(I64){_t762}); _t764 = *_hp; free(_hp); }
    ;
    U64 _t765 = 1;
    memcpy(_t763, &(U8){_t764}, _t765);
    ;
    ;
    U64 _t766 = U64_clone(new_len);
    U64 _t767 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t768 = malloc(sizeof(Str));
    _t768->c_str = new_data;
    _t768->count = _t766;
    _t768->cap = _t767;
    ;
    ;
    return _t768;
}

Str * Str_with_capacity(U64 * n) {
    U64 _t769 = 1;
    U64 _t770 = U64_add(DEREF(n), _t769);
    ;
    U8 *buf = malloc(_t770);
    ;
    I64 _t771 = 0;
    U8 _t772; { U8 *_hp = U8_from_i64(&(I64){_t771}); _t772 = *_hp; free(_hp); }
    ;
    U64 _t773 = 1;
    memcpy(buf, &(U8){_t772}, _t773);
    ;
    ;
    I64 _t774 = 0;
    U64 _t775 = U64_clone(n);
    Str *_t776 = malloc(sizeof(Str));
    _t776->c_str = buf;
    _t776->count = _t774;
    _t776->cap = _t775;
    ;
    ;
    return _t776;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    Bool _t789; { Bool *_hp = U64_gte(&self->cap, CAP_VIEW); _t789 = *_hp; free(_hp); }
    if (_t789) {
        Str *_t777 = Str_lit("Str", 3ULL);
        U64 _t778; { U64 *_hp = Str_size(); _t778 = *_hp; free(_hp); }
        U64 _t779 = 1;
        Array *_va17 = Array_new(_t777, &(U64){_t778}, &(U64){_t779});
        Str_delete(_t777, &(Bool){1});
        ;
        ;
        U64 _t780 = 0;
        Str *_t781 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va17, &(U64){_t780}, _t781);
        ;
        Str *_t782 = Str_lit("Str.push_str", 12ULL);
        panic(_t782, _va17);
        Str_delete(_t782, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool _t790; { Bool *_hp = U64_gt(new_len, &self->cap); _t790 = *_hp; free(_hp); }
    if (_t790) {
        Str *_t783 = Str_lit("Str", 3ULL);
        U64 _t784; { U64 *_hp = Str_size(); _t784 = *_hp; free(_hp); }
        U64 _t785 = 1;
        Array *_va18 = Array_new(_t783, &(U64){_t784}, &(U64){_t785});
        Str_delete(_t783, &(Bool){1});
        ;
        ;
        U64 _t786 = 0;
        Str *_t787 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va18, &(U64){_t786}, _t787);
        ;
        Str *_t788 = Str_lit("Str.push_str", 12ULL);
        panic(_t788, _va18);
        Str_delete(_t788, &(Bool){1});
    }
    ;
    void *_t791 = ptr_add(self->c_str, self->count);
    memcpy(_t791, s->c_str, s->count);
    U64 _t792 = U64_clone(new_len);
    self->count = _t792;
    ;
    I64 _t793 = 0;
    void *_t794 = ptr_add(self->c_str, DEREF(new_len));
    U8 _t795; { U8 *_hp = U8_from_i64(&(I64){_t793}); _t795 = *_hp; free(_hp); }
    ;
    U64 _t796 = 1;
    memcpy(_t794, &(U8){_t795}, _t796);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    U64 _t797 = 1;
    U64 _t798 = U64_add(val->count, _t797);
    ;
    U8 *new_data = malloc(_t798);
    ;
    memcpy(new_data, val->c_str, val->count);
    I64 _t799 = 0;
    void *_t800 = ptr_add(new_data, val->count);
    U8 _t801; { U8 *_hp = U8_from_i64(&(I64){_t799}); _t801 = *_hp; free(_hp); }
    ;
    U64 _t802 = 1;
    memcpy(_t800, &(U8){_t801}, _t802);
    ;
    ;
    Str *_t803 = malloc(sizeof(Str));
    _t803->c_str = new_data;
    _t803->count = val->count;
    _t803->cap = val->count;
    return _t803;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    Bool _t804; { Bool *_hp = U64_lt(&self->cap, CAP_VIEW); _t804 = *_hp; free(_hp); }
    if (_t804) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t805 = Str_clone(val);
    return _t805;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    U64 ln = U64_clone(n);
    Bool _t807; { Bool *_hp = U64_gt(st, &s->count); _t807 = *_hp; free(_hp); }
    if (_t807) {
        *st = s->count;
    }
    ;
    U64 _t808 = U64_add(DEREF(st), ln);
    Bool _t809; { Bool *_hp = U64_gt(&(U64){_t808}, &s->count); _t809 = *_hp; free(_hp); }
    ;
    if (_t809) {
        U64 _t806 = U64_sub(s->count, DEREF(st));
        ln = _t806;
        ;
    }
    ;
    void *_t810 = ptr_add(s->c_str, DEREF(st));
    U64 _t811 = U64_clone(&(U64){ln});
    ;
    U64 _t812 = U64_clone(CAP_VIEW);
    Str *_t813 = malloc(sizeof(Str));
    _t813->c_str = _t810;
    _t813->count = _t811;
    _t813->cap = _t812;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t813;
}

Bool * Str_contains(Str * a, Str * b) {
    U64 _t827 = 0;
    Bool _t828 = U64_eq(b->count, _t827);
    ;
    if (_t828) {
        Bool _t814 = 1;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t814; return _r; }
    }
    ;
    Bool _t829; { Bool *_hp = U64_gt(&b->count, &a->count); _t829 = *_hp; free(_hp); }
    if (_t829) {
        Bool _t815 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t815; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t824 = U64_sub(a->count, b->count);
        Bool _wcond816; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t824}); _wcond816 = *_hp; free(_hp); }
        ;
        if (_wcond816) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond817; { Bool *_hp = U64_lt(j, &b->count); _wcond817 = *_hp; free(_hp); }
            if (_wcond817) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t819 = malloc(sizeof(U64)); *_t819 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(a, _t819);
            U8 *bc = Str_get(b, j);
            Bool _t820; { Bool *_hp = U8_neq(ac, bc); _t820 = *_hp; free(_hp); }
            U64_delete(_t819, &(Bool){1});
            if (_t820) {
                Bool _t818 = 0;
                found = _t818;
                ;
            }
            ;
            U64 _t821 = 1;
            U64 _t822 = U64_add(DEREF(j), _t821);
            ;
            *j = _t822;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t823 = 1;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t823; return _r; }
        }
        ;
        U64 _t825 = 1;
        U64 _t826 = U64_add(i, _t825);
        ;
        i = _t826;
        ;
    }
    ;
    Bool _t830 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t830; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool _t837; { Bool *_hp = U64_gt(&b->count, &a->count); _t837 = *_hp; free(_hp); }
    if (_t837) {
        Bool _t831 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t831; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond832; { Bool *_hp = U64_lt(i, &b->count); _wcond832 = *_hp; free(_hp); }
        if (_wcond832) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool _t834; { Bool *_hp = U8_neq(ac, bc); _t834 = *_hp; free(_hp); }
        if (_t834) {
            Bool _t833 = 0;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t833; return _r; }
        }
        ;
        U64 _t835 = 1;
        U64 _t836 = U64_add(DEREF(i), _t835);
        ;
        *i = _t836;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t838 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t838; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool _t846; { Bool *_hp = U64_gt(&b->count, &a->count); _t846 = *_hp; free(_hp); }
    if (_t846) {
        Bool _t839 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t839; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond840; { Bool *_hp = U64_lt(i, &b->count); _wcond840 = *_hp; free(_hp); }
        if (_wcond840) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t842 = malloc(sizeof(U64)); *_t842 = U64_add(offset, DEREF(i));
        U8 *ac = Str_get(a, _t842);
        U8 *bc = Str_get(b, i);
        Bool _t843; { Bool *_hp = U8_neq(ac, bc); _t843 = *_hp; free(_hp); }
        U64_delete(_t842, &(Bool){1});
        if (_t843) {
            Bool _t841 = 0;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t841; return _r; }
        }
        ;
        U64 _t844 = 1;
        U64 _t845 = U64_add(DEREF(i), _t844);
        ;
        *i = _t845;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t847 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t847; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t848 = 0;
    Bool _t849 = U64_eq(self->count, _t848);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t849; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    U64 _t867 = 0;
    Bool _t868 = U64_eq(needle->count, _t867);
    ;
    if (_t868) {
        I64 _t850 = 0;
        I64 _t851 = 1;
        I64 _t852 = I64_sub(_t850, _t851);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t852; return _r; }
    }
    ;
    Bool _t869; { Bool *_hp = U64_gt(&needle->count, &self->count); _t869 = *_hp; free(_hp); }
    if (_t869) {
        I64 _t853 = 0;
        I64 _t854 = 1;
        I64 _t855 = I64_sub(_t853, _t854);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t855; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t864 = U64_sub(self->count, needle->count);
        Bool _wcond856; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t864}); _wcond856 = *_hp; free(_hp); }
        ;
        if (_wcond856) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond857; { Bool *_hp = U64_lt(j, &needle->count); _wcond857 = *_hp; free(_hp); }
            if (_wcond857) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t859 = malloc(sizeof(U64)); *_t859 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t859);
            U8 *bc = Str_get(needle, j);
            Bool _t860; { Bool *_hp = U8_neq(ac, bc); _t860 = *_hp; free(_hp); }
            U64_delete(_t859, &(Bool){1});
            if (_t860) {
                Bool _t858 = 0;
                found = _t858;
                ;
            }
            ;
            U64 _t861 = 1;
            U64 _t862 = U64_add(DEREF(j), _t861);
            ;
            *j = _t862;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t863 = U64_to_i64(i);
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t863; return _r; }
        }
        ;
        U64 _t865 = 1;
        U64 _t866 = U64_add(i, _t865);
        ;
        i = _t866;
        ;
    }
    ;
    I64 _t870 = 0;
    I64 _t871 = 1;
    I64 _t872 = I64_sub(_t870, _t871);
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t872; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    U64 _t890 = 0;
    Bool _t891 = U64_eq(needle->count, _t890);
    ;
    if (_t891) {
        I64 _t873 = 0;
        I64 _t874 = 1;
        I64 _t875 = I64_sub(_t873, _t874);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t875; return _r; }
    }
    ;
    Bool _t892; { Bool *_hp = U64_gt(&needle->count, &self->count); _t892 = *_hp; free(_hp); }
    if (_t892) {
        I64 _t876 = 0;
        I64 _t877 = 1;
        I64 _t878 = I64_sub(_t876, _t877);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t878; return _r; }
    }
    ;
    I64 _t893 = 0;
    I64 _t894 = 1;
    I64 last = I64_sub(_t893, _t894);
    ;
    ;
    U64 i = 0;
    while (1) {
        U64 _t887 = U64_sub(self->count, needle->count);
        Bool _wcond879; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t887}); _wcond879 = *_hp; free(_hp); }
        ;
        if (_wcond879) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond880; { Bool *_hp = U64_lt(j, &needle->count); _wcond880 = *_hp; free(_hp); }
            if (_wcond880) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t882 = malloc(sizeof(U64)); *_t882 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t882);
            U8 *bc = Str_get(needle, j);
            Bool _t883; { Bool *_hp = U8_neq(ac, bc); _t883 = *_hp; free(_hp); }
            U64_delete(_t882, &(Bool){1});
            if (_t883) {
                Bool _t881 = 0;
                found = _t881;
                ;
            }
            ;
            U64 _t884 = 1;
            U64 _t885 = U64_add(DEREF(j), _t884);
            ;
            *j = _t885;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t886 = U64_to_i64(i);
            last = _t886;
            ;
        }
        ;
        U64 _t888 = 1;
        U64 _t889 = U64_add(i, _t888);
        ;
        i = _t889;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    U64 _t910 = 0;
    Bool _t911 = U64_eq(from->count, _t910);
    ;
    if (_t911) {
        Str *_t895 = Str_clone(self);
        ;
        return _t895;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 start = 0;
    while (1) {
        U64 _t897 = U64_sub(self->count, from->count);
        Bool _wcond896; { Bool *_hp = U64_lte(&(U64){start}, &(U64){_t897}); _wcond896 = *_hp; free(_hp); }
        ;
        if (_wcond896) {
        } else {
            ;
            break;
        }
        ;
        U64 _t898 = U64_sub(self->count, start);
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t898});
        ;
        I64 pos; { I64 *_hp = Str_find(rest, from); pos = *_hp; free(_hp); }
        I64 _t899 = 0;
        I64 _t900 = 1;
        I64 _t901 = I64_sub(_t899, _t900);
        ;
        ;
        Bool _t902 = I64_eq(pos, _t901);
        ;
        if (_t902) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t903; { U64 *_hp = U64_from_i64(&(I64){pos}); _t903 = *_hp; free(_hp); }
        Str *_t904 = Str_substr(self, &(U64){start}, &(U64){_t903});
        ;
        result = Str_concat(result, _t904);
        Str_delete(_t904, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t905; { U64 *_hp = U64_from_i64(&(I64){pos}); _t905 = *_hp; free(_hp); }
        ;
        U64 _t906 = U64_add(start, _t905);
        ;
        U64 _t907 = U64_add(_t906, from->count);
        ;
        start = _t907;
        ;
    }
    Bool _t912; { Bool *_hp = U64_lt(&(U64){start}, &self->count); _t912 = *_hp; free(_hp); }
    if (_t912) {
        U64 _t908 = U64_sub(self->count, start);
        Str *_t909 = Str_substr(self, &(U64){start}, &(U64){_t908});
        ;
        result = Str_concat(result, _t909);
        Str_delete(_t909, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    U64 _t913 = 1;
    Str *_t914 = Str_substr(self, i, &(U64){_t913});
    ;
    return _t914;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    Bool _t917; { Bool *_hp = Str_starts_with(self, prefix); _t917 = *_hp; free(_hp); }
    if (_t917) {
        U64 _t915 = U64_sub(self->count, prefix->count);
        Str *_t916 = Str_substr(self, &prefix->count, &(U64){_t915});
        ;
        ;
        return _t916;
    }
    ;
    Str *_t918 = Str_clone(self);
    return _t918;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    Bool _t922; { Bool *_hp = Str_ends_with(self, suffix); _t922 = *_hp; free(_hp); }
    if (_t922) {
        U64 _t919 = 0;
        U64 _t920 = U64_sub(self->count, suffix->count);
        Str *_t921 = Str_substr(self, &(U64){_t919}, &(U64){_t920});
        ;
        ;
        ;
        return _t921;
    }
    ;
    Str *_t923 = Str_clone(self);
    return _t923;
}

Str * Str_from_byte(U8 * byte) {
    U64 _t924 = 2;
    U8 *buf = malloc(_t924);
    ;
    U64 _t925 = 1;
    memcpy(buf, byte, _t925);
    ;
    U64 *_t926 = malloc(sizeof(U64));
    *_t926 = 1;
    I64 _t927 = 0;
    void *_t928 = ptr_add(buf, DEREF(_t926));
    U8 _t929; { U8 *_hp = U8_from_i64(&(I64){_t927}); _t929 = *_hp; free(_hp); }
    ;
    U64 _t930 = 1;
    memcpy(_t928, &(U8){_t929}, _t930);
    U64_delete(_t926, &(Bool){1});
    ;
    ;
    I64 _t931 = 1;
    I64 _t932 = 1;
    Str *_t933 = malloc(sizeof(Str));
    _t933->c_str = buf;
    _t933->count = _t931;
    _t933->cap = _t932;
    ;
    ;
    return _t933;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t974 = 0;
    Bool _t975 = U64_eq(self->count, _t974);
    ;
    if (_t975) {
        Str *_t934 = Str_lit("Str", 3ULL);
        U64 _t935; { U64 *_hp = Str_size(); _t935 = *_hp; free(_hp); }
        U64 _t936 = 1;
        Array *_va19 = Array_new(_t934, &(U64){_t935}, &(U64){_t936});
        Str_delete(_t934, &(Bool){1});
        ;
        ;
        U64 _t937 = 0;
        Str *_t938 = Str_lit("empty string", 12ULL);
        Array_set(_va19, &(U64){_t937}, _t938);
        ;
        Str *_t939 = Str_lit("Str.to_i64", 10ULL);
        panic(_t939, _va19);
        Str_delete(_t939, &(Bool){1});
    }
    ;
    I64 result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool neg = 0;
    U64 *_t976 = malloc(sizeof(U64));
    *_t976 = 0;
    U8 *first = Str_get(self, _t976);
    I64 _t977 = 45;
    U8 _t978; { U8 *_hp = U8_from_i64(&(I64){_t977}); _t978 = *_hp; free(_hp); }
    ;
    Bool _t979 = U8_eq(DEREF(first), _t978);
    U64_delete(_t976, &(Bool){1});
    ;
    if (_t979) {
        Bool _t940 = 1;
        neg = _t940;
        ;
        I64 _t941 = 1;
        U64 _t942; { U64 *_hp = U64_from_i64(&(I64){_t941}); _t942 = *_hp; free(_hp); }
        ;
        *i = _t942;
        ;
    }
    ;
    Bool _t980 = U64_eq(DEREF(i), self->count);
    if (_t980) {
        Str *_t943 = Str_lit("Str", 3ULL);
        U64 _t944; { U64 *_hp = Str_size(); _t944 = *_hp; free(_hp); }
        U64 _t945 = 1;
        Array *_va20 = Array_new(_t943, &(U64){_t944}, &(U64){_t945});
        Str_delete(_t943, &(Bool){1});
        ;
        ;
        U64 _t946 = 0;
        Str *_t947 = Str_lit("no digits", 9ULL);
        Array_set(_va20, &(U64){_t946}, _t947);
        ;
        Str *_t948 = Str_lit("Str.to_i64", 10ULL);
        panic(_t948, _va20);
        Str_delete(_t948, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond949; { Bool *_hp = U64_lt(i, &self->count); _wcond949 = *_hp; free(_hp); }
        if (_wcond949) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        I64 _t960 = U8_to_i64(DEREF(ch));
        I64 _t961 = 48;
        I64 d = I64_sub(_t960, _t961);
        ;
        ;
        I64 _t962 = 0;
        I64 _t963 = 9;
        Bool _t964; { Bool *_hp = I64_lt(&(I64){d}, &(I64){_t962}); _t964 = *_hp; free(_hp); }
        ;
        Bool _t965; { Bool *_hp = I64_gt(&(I64){d}, &(I64){_t963}); _t965 = *_hp; free(_hp); }
        ;
        Bool _t966 = Bool_or(_t964, _t965);
        ;
        ;
        if (_t966) {
            Str *_t950 = Str_lit("Str", 3ULL);
            U64 _t951; { U64 *_hp = Str_size(); _t951 = *_hp; free(_hp); }
            U64 _t952 = 3;
            Array *_va21 = Array_new(_t950, &(U64){_t951}, &(U64){_t952});
            Str_delete(_t950, &(Bool){1});
            ;
            ;
            U64 _t953 = 0;
            Str *_t954 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va21, &(U64){_t953}, _t954);
            ;
            U64 _t955 = 1;
            Str *_t956 = Str_clone(self);
            Array_set(_va21, &(U64){_t955}, _t956);
            ;
            U64 _t957 = 2;
            Str *_t958 = Str_lit("'", 1ULL);
            Array_set(_va21, &(U64){_t957}, _t958);
            ;
            Str *_t959 = Str_lit("Str.to_i64", 10ULL);
            panic(_t959, _va21);
            Str_delete(_t959, &(Bool){1});
        }
        ;
        I64 _t967 = 10;
        I64 _t968 = I64_mul(result, _t967);
        ;
        I64 _t969 = I64_add(_t968, d);
        ;
        ;
        result = _t969;
        ;
        U64 _t970 = 1;
        U64 _t971 = U64_add(DEREF(i), _t970);
        ;
        *i = _t971;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t972 = 0;
        I64 _t973 = I64_sub(_t972, result);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t973; return _r; }
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
    I64 _t982; { I64 *_hp = Str_cmp(a, b); _t982 = *_hp; free(_hp); }
    I64 _t983 = 0;
    Bool _t984 = I64_eq(_t982, _t983);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t984; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    I64 _t985 = 0;
    I64 _t986 = 1;
    I64 _t987; { I64 *_hp = Str_cmp(a, b); _t987 = *_hp; free(_hp); }
    I64 _t988 = I64_sub(_t985, _t986);
    ;
    ;
    Bool _t989 = I64_eq(_t987, _t988);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t989; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    I64 _t990; { I64 *_hp = Str_cmp(a, b); _t990 = *_hp; free(_hp); }
    I64 _t991 = 1;
    Bool _t992 = I64_eq(_t990, _t991);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t992; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    Bool _t993; { Bool *_hp = Str_eq(a, b); _t993 = *_hp; free(_hp); }
    Bool _t994 = Bool_not(_t993);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t994; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    Bool _t995; { Bool *_hp = Str_gt(a, b); _t995 = *_hp; free(_hp); }
    Bool _t996 = Bool_not(_t995);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t996; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    Bool _t997; { Bool *_hp = Str_lt(a, b); _t997 = *_hp; free(_hp); }
    Bool _t998 = Bool_not(_t997);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t998; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t999 = malloc(DEREF(elem_size));
    U64 _t1000 = 0;
    I64 _t1001 = 1;
    U64 _t1002 = U64_clone(elem_size);
    Vec *_t1003 = malloc(sizeof(Vec));
    _t1003->data = _t999;
    _t1003->count = _t1000;
    _t1003->cap = _t1001;
    _t1003->elem_size = _t1002;
    { Str *_ca = Str_clone(elem_type); _t1003->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t1003;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    Bool _t1008 = U64_eq(self->count, self->cap);
    if (_t1008) {
        U64 _t1004 = 2;
        U64 new_cap = U64_mul(self->cap, _t1004);
        ;
        U64 _t1005 = U64_mul(new_cap, self->elem_size);
        void *_t1006 = realloc(self->data, _t1005);
        ;
        self->data = _t1006;
        U64 _t1007 = U64_clone(&(U64){new_cap});
        ;
        self->cap = _t1007;
        ;
    }
    ;
    U64 *_t1009 = malloc(sizeof(U64)); *_t1009 = U64_mul(self->count, self->elem_size);
    void *_t1010 = ptr_add(self->data, DEREF(_t1009));
    memcpy(_t1010, val, self->elem_size);
    U64_delete(_t1009, &(Bool){1});
    free(val);
    U64 _t1011 = 1;
    U64 _t1012 = U64_add(self->count, _t1011);
    ;
    self->count = _t1012;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    Bool _t1027; { Bool *_hp = U64_gte(i, &self->count); _t1027 = *_hp; free(_hp); }
    if (_t1027) {
        Str *_t1013 = Str_lit("Str", 3ULL);
        U64 _t1014; { U64 *_hp = Str_size(); _t1014 = *_hp; free(_hp); }
        U64 _t1015 = 5;
        Array *_va22 = Array_new(_t1013, &(U64){_t1014}, &(U64){_t1015});
        Str_delete(_t1013, &(Bool){1});
        ;
        ;
        U64 _t1016 = 0;
        Str *_t1017 = Str_lit("index ", 6ULL);
        Array_set(_va22, &(U64){_t1016}, _t1017);
        ;
        U64 _t1018 = 1;
        Str *_t1019 = U64_to_str(DEREF(i));
        Array_set(_va22, &(U64){_t1018}, _t1019);
        ;
        U64 _t1020 = 2;
        Str *_t1021 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va22, &(U64){_t1020}, _t1021);
        ;
        U64 _t1022 = 3;
        Str *_t1023 = U64_to_str(self->count);
        Array_set(_va22, &(U64){_t1022}, _t1023);
        ;
        U64 _t1024 = 4;
        Str *_t1025 = Str_lit(")", 1ULL);
        Array_set(_va22, &(U64){_t1024}, _t1025);
        ;
        Str *_t1026 = Str_lit("Vec.get", 7ULL);
        panic(_t1026, _va22);
        Str_delete(_t1026, &(Bool){1});
    }
    ;
    U64 *_t1028 = malloc(sizeof(U64)); *_t1028 = U64_mul(DEREF(i), self->elem_size);
    void *_t1029 = ptr_add(self->data, DEREF(_t1028));
    U64_delete(_t1028, &(Bool){1});
    return _t1029;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    Bool _t1043; { Bool *_hp = Str_is_empty(&self->elem_type); _t1043 = *_hp; free(_hp); }
    Bool _t1044 = Bool_not(_t1043);
    ;
    if (_t1044) {
        {
            U64 _fi1030 = 0;
            while (1) {
                U64 _t1032 = 0;
                Range *_t1033 = Range_new(_t1032, self->count);
                ;
                U64 _t1034; { U64 *_hp = Range_len(_t1033); _t1034 = *_hp; free(_hp); }
                Range_delete(_t1033, &(Bool){1});
                Bool _wcond1031; { Bool *_hp = U64_lt(&(U64){_fi1030}, &(U64){_t1034}); _wcond1031 = *_hp; free(_hp); }
                ;
                if (_wcond1031) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t1035 = 0;
                Range *_t1036 = Range_new(_t1035, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t1036, _fi1030); i = *_hp; free(_hp); }
                Range_delete(_t1036, &(Bool){1});
                U64 _t1037 = 1;
                U64 _t1038 = U64_add(_fi1030, _t1037);
                ;
                _fi1030 = _t1038;
                ;
                U64 *_t1039 = malloc(sizeof(U64)); *_t1039 = U64_mul(i, self->elem_size);
                ;
                void *_t1040 = ptr_add(self->data, DEREF(_t1039));
                Bool _t1041 = 0;
                dyn_call_delete(&self->elem_type, _t1040, &(Bool){_t1041});
                U64_delete(_t1039, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t1045; { Bool *_hp = Str_is_empty(&self->elem_type); _t1045 = *_hp; free(_hp); }
    Bool _t1046 = Bool_not(_t1045);
    ;
    if (_t1046) {
        Bool _t1042 = 0;
        Str_delete(&self->elem_type, &(Bool){_t1042});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t1060 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t1060);
    ;
    {
        U64 _fi1047 = 0;
        while (1) {
            U64 _t1049 = 0;
            Range *_t1050 = Range_new(_t1049, self->count);
            ;
            U64 _t1051; { U64 *_hp = Range_len(_t1050); _t1051 = *_hp; free(_hp); }
            Range_delete(_t1050, &(Bool){1});
            Bool _wcond1048; { Bool *_hp = U64_lt(&(U64){_fi1047}, &(U64){_t1051}); _wcond1048 = *_hp; free(_hp); }
            ;
            if (_wcond1048) {
            } else {
                ;
                break;
            }
            ;
            U64 _t1052 = 0;
            Range *_t1053 = Range_new(_t1052, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t1053, _fi1047); i = *_hp; free(_hp); }
            Range_delete(_t1053, &(Bool){1});
            U64 _t1054 = 1;
            U64 _t1055 = U64_add(_fi1047, _t1054);
            ;
            _fi1047 = _t1055;
            ;
            U64 *_t1056 = malloc(sizeof(U64)); *_t1056 = U64_mul(i, self->elem_size);
            void *_t1057 = ptr_add(self->data, DEREF(_t1056));
            void *cloned = dyn_call_clone(&self->elem_type, _t1057);
            U64_delete(_t1056, &(Bool){1});
            U64 *_t1058 = malloc(sizeof(U64)); *_t1058 = U64_mul(i, self->elem_size);
            ;
            void *_t1059 = ptr_add(new_data, DEREF(_t1058));
            memcpy(_t1059, cloned, self->elem_size);
            U64_delete(_t1058, &(Bool){1});
            free(cloned);
        }
        ;
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
    U64 _t1080; { U64 *_hp = Str_size(); _t1080 = *_hp; free(_hp); }
    Vec *parts = Vec_new(_t1079, &(U64){_t1080});
    Str_delete(_t1079, &(Bool){1});
    ;
    U64 _t1081; { U64 *_hp = Str_len(delim); _t1081 = *_hp; free(_hp); }
    U64 _t1082 = 0;
    Bool _t1083 = U64_eq(_t1081, _t1082);
    ;
    ;
    if (_t1083) {
        Str *_t1063 = Str_clone(s);
        Vec_push(parts, _t1063);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    U64 pos = 0;
    while (1) {
        U64 _t1073; { U64 *_hp = Str_len(s); _t1073 = *_hp; free(_hp); }
        U64 _t1074; { U64 *_hp = Str_len(delim); _t1074 = *_hp; free(_hp); }
        U64 _t1075 = U64_sub(_t1073, _t1074);
        ;
        ;
        Bool _wcond1064; { Bool *_hp = U64_lte(&(U64){pos}, &(U64){_t1075}); _wcond1064 = *_hp; free(_hp); }
        ;
        if (_wcond1064) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1076; { U64 *_hp = Str_len(delim); _t1076 = *_hp; free(_hp); }
        Str *_t1077 = Str_substr(s, &(U64){pos}, &(U64){_t1076});
        ;
        Bool _t1078; { Bool *_hp = Str_eq(_t1077, delim); _t1078 = *_hp; free(_hp); }
        Str_delete(_t1077, &(Bool){1});
        if (_t1078) {
            U64 _t1065 = U64_sub(pos, start);
            Str *_t1066 = Str_substr(s, &(U64){start}, &(U64){_t1065});
            ;
            Str *_t1067 = Str_clone(_t1066);
            Str_delete(_t1066, &(Bool){1});
            Vec_push(parts, _t1067);
            U64 _t1068; { U64 *_hp = Str_len(delim); _t1068 = *_hp; free(_hp); }
            U64 _t1069 = U64_add(pos, _t1068);
            ;
            start = _t1069;
            ;
            U64 _t1070 = U64_clone(&(U64){start});
            pos = _t1070;
            ;
        } else {
            U64 _t1071 = 1;
            U64 _t1072 = U64_add(pos, _t1071);
            ;
            pos = _t1072;
            ;
        }
        ;
    }
    ;
    U64 _t1084; { U64 *_hp = Str_len(s); _t1084 = *_hp; free(_hp); }
    U64 _t1085 = U64_sub(_t1084, start);
    ;
    Str *_t1086 = Str_substr(s, &(U64){start}, &(U64){_t1085});
    ;
    ;
    Str *_t1087 = Str_clone(_t1086);
    Str_delete(_t1086, &(Bool){1});
    Vec_push(parts, _t1087);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 _t1095; { U64 *_hp = Vec_len(parts); _t1095 = *_hp; free(_hp); }
    U64 _t1096 = 0;
    Bool _t1097 = U64_eq(_t1095, _t1096);
    ;
    ;
    if (_t1097) {
        Str *_t1088 = Str_lit("", 0ULL);
        ;
        return _t1088;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t1090; { U64 *_hp = Vec_len(parts); _t1090 = *_hp; free(_hp); }
        Bool _wcond1089; { Bool *_hp = U64_lt(i, &(U64){_t1090}); _wcond1089 = *_hp; free(_hp); }
        ;
        if (_wcond1089) {
        } else {
            ;
            break;
        }
        ;
        U64 _t1091 = 0;
        Bool _t1092; { Bool *_hp = U64_gt(i, &(U64){_t1091}); _t1092 = *_hp; free(_hp); }
        ;
        if (_t1092) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        U64 _t1093 = 1;
        U64 _t1094 = U64_add(DEREF(i), _t1093);
        ;
        *i = _t1094;
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
    Bool _t1161; { Bool *_hp = TokenType_is_Eof(self); _t1161 = *_hp; free(_hp); }
    if (_t1161) {
        Bool _t1098; { Bool *_hp = TokenType_is_Eof(other); _t1098 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1098; return _r; }
    }
    ;
    Bool _t1162; { Bool *_hp = TokenType_is_LParen(self); _t1162 = *_hp; free(_hp); }
    if (_t1162) {
        Bool _t1099; { Bool *_hp = TokenType_is_LParen(other); _t1099 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1099; return _r; }
    }
    ;
    Bool _t1163; { Bool *_hp = TokenType_is_RParen(self); _t1163 = *_hp; free(_hp); }
    if (_t1163) {
        Bool _t1100; { Bool *_hp = TokenType_is_RParen(other); _t1100 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1100; return _r; }
    }
    ;
    Bool _t1164; { Bool *_hp = TokenType_is_LBrace(self); _t1164 = *_hp; free(_hp); }
    if (_t1164) {
        Bool _t1101; { Bool *_hp = TokenType_is_LBrace(other); _t1101 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1101; return _r; }
    }
    ;
    Bool _t1165; { Bool *_hp = TokenType_is_RBrace(self); _t1165 = *_hp; free(_hp); }
    if (_t1165) {
        Bool _t1102; { Bool *_hp = TokenType_is_RBrace(other); _t1102 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1102; return _r; }
    }
    ;
    Bool _t1166; { Bool *_hp = TokenType_is_LBracket(self); _t1166 = *_hp; free(_hp); }
    if (_t1166) {
        Bool _t1103; { Bool *_hp = TokenType_is_LBracket(other); _t1103 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1103; return _r; }
    }
    ;
    Bool _t1167; { Bool *_hp = TokenType_is_RBracket(self); _t1167 = *_hp; free(_hp); }
    if (_t1167) {
        Bool _t1104; { Bool *_hp = TokenType_is_RBracket(other); _t1104 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1104; return _r; }
    }
    ;
    Bool _t1168; { Bool *_hp = TokenType_is_Comma(self); _t1168 = *_hp; free(_hp); }
    if (_t1168) {
        Bool _t1105; { Bool *_hp = TokenType_is_Comma(other); _t1105 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1105; return _r; }
    }
    ;
    Bool _t1169; { Bool *_hp = TokenType_is_Colon(self); _t1169 = *_hp; free(_hp); }
    if (_t1169) {
        Bool _t1106; { Bool *_hp = TokenType_is_Colon(other); _t1106 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1106; return _r; }
    }
    ;
    Bool _t1170; { Bool *_hp = TokenType_is_Question(self); _t1170 = *_hp; free(_hp); }
    if (_t1170) {
        Bool _t1107; { Bool *_hp = TokenType_is_Question(other); _t1107 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1107; return _r; }
    }
    ;
    Bool _t1171; { Bool *_hp = TokenType_is_Bang(self); _t1171 = *_hp; free(_hp); }
    if (_t1171) {
        Bool _t1108; { Bool *_hp = TokenType_is_Bang(other); _t1108 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1108; return _r; }
    }
    ;
    Bool _t1172; { Bool *_hp = TokenType_is_Minus(self); _t1172 = *_hp; free(_hp); }
    if (_t1172) {
        Bool _t1109; { Bool *_hp = TokenType_is_Minus(other); _t1109 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1109; return _r; }
    }
    ;
    Bool _t1173; { Bool *_hp = TokenType_is_Plus(self); _t1173 = *_hp; free(_hp); }
    if (_t1173) {
        Bool _t1110; { Bool *_hp = TokenType_is_Plus(other); _t1110 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1110; return _r; }
    }
    ;
    Bool _t1174; { Bool *_hp = TokenType_is_Star(self); _t1174 = *_hp; free(_hp); }
    if (_t1174) {
        Bool _t1111; { Bool *_hp = TokenType_is_Star(other); _t1111 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1111; return _r; }
    }
    ;
    Bool _t1175; { Bool *_hp = TokenType_is_Slash(self); _t1175 = *_hp; free(_hp); }
    if (_t1175) {
        Bool _t1112; { Bool *_hp = TokenType_is_Slash(other); _t1112 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1112; return _r; }
    }
    ;
    Bool _t1176; { Bool *_hp = TokenType_is_Dot(self); _t1176 = *_hp; free(_hp); }
    if (_t1176) {
        Bool _t1113; { Bool *_hp = TokenType_is_Dot(other); _t1113 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1113; return _r; }
    }
    ;
    Bool _t1177; { Bool *_hp = TokenType_is_DotDot(self); _t1177 = *_hp; free(_hp); }
    if (_t1177) {
        Bool _t1114; { Bool *_hp = TokenType_is_DotDot(other); _t1114 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1114; return _r; }
    }
    ;
    Bool _t1178; { Bool *_hp = TokenType_is_Eq(self); _t1178 = *_hp; free(_hp); }
    if (_t1178) {
        Bool _t1115; { Bool *_hp = TokenType_is_Eq(other); _t1115 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1115; return _r; }
    }
    ;
    Bool _t1179; { Bool *_hp = TokenType_is_EqEq(self); _t1179 = *_hp; free(_hp); }
    if (_t1179) {
        Bool _t1116; { Bool *_hp = TokenType_is_EqEq(other); _t1116 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1116; return _r; }
    }
    ;
    Bool _t1180; { Bool *_hp = TokenType_is_Neq(self); _t1180 = *_hp; free(_hp); }
    if (_t1180) {
        Bool _t1117; { Bool *_hp = TokenType_is_Neq(other); _t1117 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1117; return _r; }
    }
    ;
    Bool _t1181; { Bool *_hp = TokenType_is_Lt(self); _t1181 = *_hp; free(_hp); }
    if (_t1181) {
        Bool _t1118; { Bool *_hp = TokenType_is_Lt(other); _t1118 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1118; return _r; }
    }
    ;
    Bool _t1182; { Bool *_hp = TokenType_is_LtEq(self); _t1182 = *_hp; free(_hp); }
    if (_t1182) {
        Bool _t1119; { Bool *_hp = TokenType_is_LtEq(other); _t1119 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1119; return _r; }
    }
    ;
    Bool _t1183; { Bool *_hp = TokenType_is_Gt(self); _t1183 = *_hp; free(_hp); }
    if (_t1183) {
        Bool _t1120; { Bool *_hp = TokenType_is_Gt(other); _t1120 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1120; return _r; }
    }
    ;
    Bool _t1184; { Bool *_hp = TokenType_is_GtEq(self); _t1184 = *_hp; free(_hp); }
    if (_t1184) {
        Bool _t1121; { Bool *_hp = TokenType_is_GtEq(other); _t1121 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1121; return _r; }
    }
    ;
    Bool _t1185; { Bool *_hp = TokenType_is_ColonEq(self); _t1185 = *_hp; free(_hp); }
    if (_t1185) {
        Bool _t1122; { Bool *_hp = TokenType_is_ColonEq(other); _t1122 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1122; return _r; }
    }
    ;
    Bool _t1186; { Bool *_hp = TokenType_is_Ident(self); _t1186 = *_hp; free(_hp); }
    if (_t1186) {
        Bool _t1123; { Bool *_hp = TokenType_is_Ident(other); _t1123 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1123; return _r; }
    }
    ;
    Bool _t1187; { Bool *_hp = TokenType_is_StringTok(self); _t1187 = *_hp; free(_hp); }
    if (_t1187) {
        Bool _t1124; { Bool *_hp = TokenType_is_StringTok(other); _t1124 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1124; return _r; }
    }
    ;
    Bool _t1188; { Bool *_hp = TokenType_is_Number(self); _t1188 = *_hp; free(_hp); }
    if (_t1188) {
        Bool _t1125; { Bool *_hp = TokenType_is_Number(other); _t1125 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1125; return _r; }
    }
    ;
    Bool _t1189; { Bool *_hp = TokenType_is_Char(self); _t1189 = *_hp; free(_hp); }
    if (_t1189) {
        Bool _t1126; { Bool *_hp = TokenType_is_Char(other); _t1126 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1126; return _r; }
    }
    ;
    Bool _t1190; { Bool *_hp = TokenType_is_KwMode(self); _t1190 = *_hp; free(_hp); }
    if (_t1190) {
        Bool _t1127; { Bool *_hp = TokenType_is_KwMode(other); _t1127 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1127; return _r; }
    }
    ;
    Bool _t1191; { Bool *_hp = TokenType_is_KwMut(self); _t1191 = *_hp; free(_hp); }
    if (_t1191) {
        Bool _t1128; { Bool *_hp = TokenType_is_KwMut(other); _t1128 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1128; return _r; }
    }
    ;
    Bool _t1192; { Bool *_hp = TokenType_is_KwOwn(self); _t1192 = *_hp; free(_hp); }
    if (_t1192) {
        Bool _t1129; { Bool *_hp = TokenType_is_KwOwn(other); _t1129 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1129; return _r; }
    }
    ;
    Bool _t1193; { Bool *_hp = TokenType_is_KwRef(self); _t1193 = *_hp; free(_hp); }
    if (_t1193) {
        Bool _t1130; { Bool *_hp = TokenType_is_KwRef(other); _t1130 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1130; return _r; }
    }
    ;
    Bool _t1194; { Bool *_hp = TokenType_is_KwStruct(self); _t1194 = *_hp; free(_hp); }
    if (_t1194) {
        Bool _t1131; { Bool *_hp = TokenType_is_KwStruct(other); _t1131 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1131; return _r; }
    }
    ;
    Bool _t1195; { Bool *_hp = TokenType_is_KwExtStruct(self); _t1195 = *_hp; free(_hp); }
    if (_t1195) {
        Bool _t1132; { Bool *_hp = TokenType_is_KwExtStruct(other); _t1132 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1132; return _r; }
    }
    ;
    Bool _t1196; { Bool *_hp = TokenType_is_KwEnum(self); _t1196 = *_hp; free(_hp); }
    if (_t1196) {
        Bool _t1133; { Bool *_hp = TokenType_is_KwEnum(other); _t1133 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1133; return _r; }
    }
    ;
    Bool _t1197; { Bool *_hp = TokenType_is_KwNamespace(self); _t1197 = *_hp; free(_hp); }
    if (_t1197) {
        Bool _t1134; { Bool *_hp = TokenType_is_KwNamespace(other); _t1134 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1134; return _r; }
    }
    ;
    Bool _t1198; { Bool *_hp = TokenType_is_KwFunc(self); _t1198 = *_hp; free(_hp); }
    if (_t1198) {
        Bool _t1135; { Bool *_hp = TokenType_is_KwFunc(other); _t1135 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1135; return _r; }
    }
    ;
    Bool _t1199; { Bool *_hp = TokenType_is_KwProc(self); _t1199 = *_hp; free(_hp); }
    if (_t1199) {
        Bool _t1136; { Bool *_hp = TokenType_is_KwProc(other); _t1136 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1136; return _r; }
    }
    ;
    Bool _t1200; { Bool *_hp = TokenType_is_KwTest(self); _t1200 = *_hp; free(_hp); }
    if (_t1200) {
        Bool _t1137; { Bool *_hp = TokenType_is_KwTest(other); _t1137 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1137; return _r; }
    }
    ;
    Bool _t1201; { Bool *_hp = TokenType_is_KwMacro(self); _t1201 = *_hp; free(_hp); }
    if (_t1201) {
        Bool _t1138; { Bool *_hp = TokenType_is_KwMacro(other); _t1138 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1138; return _r; }
    }
    ;
    Bool _t1202; { Bool *_hp = TokenType_is_KwExtFunc(self); _t1202 = *_hp; free(_hp); }
    if (_t1202) {
        Bool _t1139; { Bool *_hp = TokenType_is_KwExtFunc(other); _t1139 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1139; return _r; }
    }
    ;
    Bool _t1203; { Bool *_hp = TokenType_is_KwExtProc(self); _t1203 = *_hp; free(_hp); }
    if (_t1203) {
        Bool _t1140; { Bool *_hp = TokenType_is_KwExtProc(other); _t1140 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1140; return _r; }
    }
    ;
    Bool _t1204; { Bool *_hp = TokenType_is_KwReturns(self); _t1204 = *_hp; free(_hp); }
    if (_t1204) {
        Bool _t1141; { Bool *_hp = TokenType_is_KwReturns(other); _t1141 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1141; return _r; }
    }
    ;
    Bool _t1205; { Bool *_hp = TokenType_is_KwThrows(self); _t1205 = *_hp; free(_hp); }
    if (_t1205) {
        Bool _t1142; { Bool *_hp = TokenType_is_KwThrows(other); _t1142 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1142; return _r; }
    }
    ;
    Bool _t1206; { Bool *_hp = TokenType_is_KwIf(self); _t1206 = *_hp; free(_hp); }
    if (_t1206) {
        Bool _t1143; { Bool *_hp = TokenType_is_KwIf(other); _t1143 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1143; return _r; }
    }
    ;
    Bool _t1207; { Bool *_hp = TokenType_is_KwElse(self); _t1207 = *_hp; free(_hp); }
    if (_t1207) {
        Bool _t1144; { Bool *_hp = TokenType_is_KwElse(other); _t1144 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1144; return _r; }
    }
    ;
    Bool _t1208; { Bool *_hp = TokenType_is_KwWhile(self); _t1208 = *_hp; free(_hp); }
    if (_t1208) {
        Bool _t1145; { Bool *_hp = TokenType_is_KwWhile(other); _t1145 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1145; return _r; }
    }
    ;
    Bool _t1209; { Bool *_hp = TokenType_is_KwFor(self); _t1209 = *_hp; free(_hp); }
    if (_t1209) {
        Bool _t1146; { Bool *_hp = TokenType_is_KwFor(other); _t1146 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1146; return _r; }
    }
    ;
    Bool _t1210; { Bool *_hp = TokenType_is_KwIn(self); _t1210 = *_hp; free(_hp); }
    if (_t1210) {
        Bool _t1147; { Bool *_hp = TokenType_is_KwIn(other); _t1147 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1147; return _r; }
    }
    ;
    Bool _t1211; { Bool *_hp = TokenType_is_KwSwitch(self); _t1211 = *_hp; free(_hp); }
    if (_t1211) {
        Bool _t1148; { Bool *_hp = TokenType_is_KwSwitch(other); _t1148 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1148; return _r; }
    }
    ;
    Bool _t1212; { Bool *_hp = TokenType_is_KwMatch(self); _t1212 = *_hp; free(_hp); }
    if (_t1212) {
        Bool _t1149; { Bool *_hp = TokenType_is_KwMatch(other); _t1149 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1149; return _r; }
    }
    ;
    Bool _t1213; { Bool *_hp = TokenType_is_KwCase(self); _t1213 = *_hp; free(_hp); }
    if (_t1213) {
        Bool _t1150; { Bool *_hp = TokenType_is_KwCase(other); _t1150 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1150; return _r; }
    }
    ;
    Bool _t1214; { Bool *_hp = TokenType_is_KwDefault(self); _t1214 = *_hp; free(_hp); }
    if (_t1214) {
        Bool _t1151; { Bool *_hp = TokenType_is_KwDefault(other); _t1151 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1151; return _r; }
    }
    ;
    Bool _t1215; { Bool *_hp = TokenType_is_KwReturn(self); _t1215 = *_hp; free(_hp); }
    if (_t1215) {
        Bool _t1152; { Bool *_hp = TokenType_is_KwReturn(other); _t1152 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1152; return _r; }
    }
    ;
    Bool _t1216; { Bool *_hp = TokenType_is_KwThrow(self); _t1216 = *_hp; free(_hp); }
    if (_t1216) {
        Bool _t1153; { Bool *_hp = TokenType_is_KwThrow(other); _t1153 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1153; return _r; }
    }
    ;
    Bool _t1217; { Bool *_hp = TokenType_is_KwCatch(self); _t1217 = *_hp; free(_hp); }
    if (_t1217) {
        Bool _t1154; { Bool *_hp = TokenType_is_KwCatch(other); _t1154 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1154; return _r; }
    }
    ;
    Bool _t1218; { Bool *_hp = TokenType_is_KwBreak(self); _t1218 = *_hp; free(_hp); }
    if (_t1218) {
        Bool _t1155; { Bool *_hp = TokenType_is_KwBreak(other); _t1155 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1155; return _r; }
    }
    ;
    Bool _t1219; { Bool *_hp = TokenType_is_KwContinue(self); _t1219 = *_hp; free(_hp); }
    if (_t1219) {
        Bool _t1156; { Bool *_hp = TokenType_is_KwContinue(other); _t1156 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1156; return _r; }
    }
    ;
    Bool _t1220; { Bool *_hp = TokenType_is_KwDefer(self); _t1220 = *_hp; free(_hp); }
    if (_t1220) {
        Bool _t1157; { Bool *_hp = TokenType_is_KwDefer(other); _t1157 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1157; return _r; }
    }
    ;
    Bool _t1221; { Bool *_hp = TokenType_is_KwTrue(self); _t1221 = *_hp; free(_hp); }
    if (_t1221) {
        Bool _t1158; { Bool *_hp = TokenType_is_KwTrue(other); _t1158 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1158; return _r; }
    }
    ;
    Bool _t1222; { Bool *_hp = TokenType_is_KwFalse(self); _t1222 = *_hp; free(_hp); }
    if (_t1222) {
        Bool _t1159; { Bool *_hp = TokenType_is_KwFalse(other); _t1159 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1159; return _r; }
    }
    ;
    Bool _t1223; { Bool *_hp = TokenType_is_Error(self); _t1223 = *_hp; free(_hp); }
    if (_t1223) {
        Bool _t1160; { Bool *_hp = TokenType_is_Error(other); _t1160 = *_hp; free(_hp); }
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t1160; return _r; }
    }
    ;
    Bool _t1224 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1224; return _r; }
}

TokenType * TokenType_clone(TokenType * self) {
    (void)self;
    Bool _t1225; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1225 = *_hp; free(_hp); }
    if (_t1225) {
        ;
        return TokenType_Eof();
    }
    ;
    Bool _t1226; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1226 = *_hp; free(_hp); }
    if (_t1226) {
        ;
        return TokenType_LParen();
    }
    ;
    Bool _t1227; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1227 = *_hp; free(_hp); }
    if (_t1227) {
        ;
        return TokenType_RParen();
    }
    ;
    Bool _t1228; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1228 = *_hp; free(_hp); }
    if (_t1228) {
        ;
        return TokenType_LBrace();
    }
    ;
    Bool _t1229; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1229 = *_hp; free(_hp); }
    if (_t1229) {
        ;
        return TokenType_RBrace();
    }
    ;
    Bool _t1230; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1230 = *_hp; free(_hp); }
    if (_t1230) {
        ;
        return TokenType_LBracket();
    }
    ;
    Bool _t1231; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1231 = *_hp; free(_hp); }
    if (_t1231) {
        ;
        return TokenType_RBracket();
    }
    ;
    Bool _t1232; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1232 = *_hp; free(_hp); }
    if (_t1232) {
        ;
        return TokenType_Comma();
    }
    ;
    Bool _t1233; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1233 = *_hp; free(_hp); }
    if (_t1233) {
        ;
        return TokenType_Colon();
    }
    ;
    Bool _t1234; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1234 = *_hp; free(_hp); }
    if (_t1234) {
        ;
        return TokenType_Question();
    }
    ;
    Bool _t1235; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1235 = *_hp; free(_hp); }
    if (_t1235) {
        ;
        return TokenType_Bang();
    }
    ;
    Bool _t1236; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1236 = *_hp; free(_hp); }
    if (_t1236) {
        ;
        return TokenType_Minus();
    }
    ;
    Bool _t1237; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1237 = *_hp; free(_hp); }
    if (_t1237) {
        ;
        return TokenType_Plus();
    }
    ;
    Bool _t1238; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1238 = *_hp; free(_hp); }
    if (_t1238) {
        ;
        return TokenType_Star();
    }
    ;
    Bool _t1239; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1239 = *_hp; free(_hp); }
    if (_t1239) {
        ;
        return TokenType_Slash();
    }
    ;
    Bool _t1240; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1240 = *_hp; free(_hp); }
    if (_t1240) {
        ;
        return TokenType_Dot();
    }
    ;
    Bool _t1241; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1241 = *_hp; free(_hp); }
    if (_t1241) {
        ;
        return TokenType_DotDot();
    }
    ;
    Bool _t1242; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1242 = *_hp; free(_hp); }
    if (_t1242) {
        ;
        return TokenType_Eq();
    }
    ;
    Bool _t1243; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1243 = *_hp; free(_hp); }
    if (_t1243) {
        ;
        return TokenType_EqEq();
    }
    ;
    Bool _t1244; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1244 = *_hp; free(_hp); }
    if (_t1244) {
        ;
        return TokenType_Neq();
    }
    ;
    Bool _t1245; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1245 = *_hp; free(_hp); }
    if (_t1245) {
        ;
        return TokenType_Lt();
    }
    ;
    Bool _t1246; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1246 = *_hp; free(_hp); }
    if (_t1246) {
        ;
        return TokenType_LtEq();
    }
    ;
    Bool _t1247; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1247 = *_hp; free(_hp); }
    if (_t1247) {
        ;
        return TokenType_Gt();
    }
    ;
    Bool _t1248; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1248 = *_hp; free(_hp); }
    if (_t1248) {
        ;
        return TokenType_GtEq();
    }
    ;
    Bool _t1249; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1249 = *_hp; free(_hp); }
    if (_t1249) {
        ;
        return TokenType_ColonEq();
    }
    ;
    Bool _t1250; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1250 = *_hp; free(_hp); }
    if (_t1250) {
        ;
        return TokenType_Ident();
    }
    ;
    Bool _t1251; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1251 = *_hp; free(_hp); }
    if (_t1251) {
        ;
        return TokenType_StringTok();
    }
    ;
    Bool _t1252; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1252 = *_hp; free(_hp); }
    if (_t1252) {
        ;
        return TokenType_Number();
    }
    ;
    Bool _t1253; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1253 = *_hp; free(_hp); }
    if (_t1253) {
        ;
        return TokenType_Char();
    }
    ;
    Bool _t1254; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1254 = *_hp; free(_hp); }
    if (_t1254) {
        ;
        return TokenType_KwMode();
    }
    ;
    Bool _t1255; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1255 = *_hp; free(_hp); }
    if (_t1255) {
        ;
        return TokenType_KwMut();
    }
    ;
    Bool _t1256; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1256 = *_hp; free(_hp); }
    if (_t1256) {
        ;
        return TokenType_KwOwn();
    }
    ;
    Bool _t1257; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1257 = *_hp; free(_hp); }
    if (_t1257) {
        ;
        return TokenType_KwRef();
    }
    ;
    Bool _t1258; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1258 = *_hp; free(_hp); }
    if (_t1258) {
        ;
        return TokenType_KwStruct();
    }
    ;
    Bool _t1259; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1259 = *_hp; free(_hp); }
    if (_t1259) {
        ;
        return TokenType_KwExtStruct();
    }
    ;
    Bool _t1260; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1260 = *_hp; free(_hp); }
    if (_t1260) {
        ;
        return TokenType_KwEnum();
    }
    ;
    Bool _t1261; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1261 = *_hp; free(_hp); }
    if (_t1261) {
        ;
        return TokenType_KwNamespace();
    }
    ;
    Bool _t1262; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1262 = *_hp; free(_hp); }
    if (_t1262) {
        ;
        return TokenType_KwFunc();
    }
    ;
    Bool _t1263; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1263 = *_hp; free(_hp); }
    if (_t1263) {
        ;
        return TokenType_KwProc();
    }
    ;
    Bool _t1264; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1264 = *_hp; free(_hp); }
    if (_t1264) {
        ;
        return TokenType_KwTest();
    }
    ;
    Bool _t1265; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1265 = *_hp; free(_hp); }
    if (_t1265) {
        ;
        return TokenType_KwMacro();
    }
    ;
    Bool _t1266; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1266 = *_hp; free(_hp); }
    if (_t1266) {
        ;
        return TokenType_KwExtFunc();
    }
    ;
    Bool _t1267; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1267 = *_hp; free(_hp); }
    if (_t1267) {
        ;
        return TokenType_KwExtProc();
    }
    ;
    Bool _t1268; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1268 = *_hp; free(_hp); }
    if (_t1268) {
        ;
        return TokenType_KwReturns();
    }
    ;
    Bool _t1269; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1269 = *_hp; free(_hp); }
    if (_t1269) {
        ;
        return TokenType_KwThrows();
    }
    ;
    Bool _t1270; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1270 = *_hp; free(_hp); }
    if (_t1270) {
        ;
        return TokenType_KwIf();
    }
    ;
    Bool _t1271; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1271 = *_hp; free(_hp); }
    if (_t1271) {
        ;
        return TokenType_KwElse();
    }
    ;
    Bool _t1272; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1272 = *_hp; free(_hp); }
    if (_t1272) {
        ;
        return TokenType_KwWhile();
    }
    ;
    Bool _t1273; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1273 = *_hp; free(_hp); }
    if (_t1273) {
        ;
        return TokenType_KwFor();
    }
    ;
    Bool _t1274; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1274 = *_hp; free(_hp); }
    if (_t1274) {
        ;
        return TokenType_KwIn();
    }
    ;
    Bool _t1275; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1275 = *_hp; free(_hp); }
    if (_t1275) {
        ;
        return TokenType_KwSwitch();
    }
    ;
    Bool _t1276; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1276 = *_hp; free(_hp); }
    if (_t1276) {
        ;
        return TokenType_KwMatch();
    }
    ;
    Bool _t1277; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1277 = *_hp; free(_hp); }
    if (_t1277) {
        ;
        return TokenType_KwCase();
    }
    ;
    Bool _t1278; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1278 = *_hp; free(_hp); }
    if (_t1278) {
        ;
        return TokenType_KwDefault();
    }
    ;
    Bool _t1279; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1279 = *_hp; free(_hp); }
    if (_t1279) {
        ;
        return TokenType_KwReturn();
    }
    ;
    Bool _t1280; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1280 = *_hp; free(_hp); }
    if (_t1280) {
        ;
        return TokenType_KwThrow();
    }
    ;
    Bool _t1281; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1281 = *_hp; free(_hp); }
    if (_t1281) {
        ;
        return TokenType_KwCatch();
    }
    ;
    Bool _t1282; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1282 = *_hp; free(_hp); }
    if (_t1282) {
        ;
        return TokenType_KwBreak();
    }
    ;
    Bool _t1283; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1283 = *_hp; free(_hp); }
    if (_t1283) {
        ;
        return TokenType_KwContinue();
    }
    ;
    Bool _t1284; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1284 = *_hp; free(_hp); }
    if (_t1284) {
        ;
        return TokenType_KwDefer();
    }
    ;
    Bool _t1285; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1285 = *_hp; free(_hp); }
    if (_t1285) {
        ;
        return TokenType_KwTrue();
    }
    ;
    Bool _t1286; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1286 = *_hp; free(_hp); }
    if (_t1286) {
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
    Bool _t1350; { Bool *_hp = TokenType_eq(self, TokenType_Eof()); _t1350 = *_hp; free(_hp); }
    if (_t1350) {
        Str *_t1287 = Str_lit("Eof", 3ULL);
        ;
        return _t1287;
    }
    ;
    Bool _t1351; { Bool *_hp = TokenType_eq(self, TokenType_LParen()); _t1351 = *_hp; free(_hp); }
    if (_t1351) {
        Str *_t1288 = Str_lit("LParen", 6ULL);
        ;
        return _t1288;
    }
    ;
    Bool _t1352; { Bool *_hp = TokenType_eq(self, TokenType_RParen()); _t1352 = *_hp; free(_hp); }
    if (_t1352) {
        Str *_t1289 = Str_lit("RParen", 6ULL);
        ;
        return _t1289;
    }
    ;
    Bool _t1353; { Bool *_hp = TokenType_eq(self, TokenType_LBrace()); _t1353 = *_hp; free(_hp); }
    if (_t1353) {
        Str *_t1290 = Str_lit("LBrace", 6ULL);
        ;
        return _t1290;
    }
    ;
    Bool _t1354; { Bool *_hp = TokenType_eq(self, TokenType_RBrace()); _t1354 = *_hp; free(_hp); }
    if (_t1354) {
        Str *_t1291 = Str_lit("RBrace", 6ULL);
        ;
        return _t1291;
    }
    ;
    Bool _t1355; { Bool *_hp = TokenType_eq(self, TokenType_LBracket()); _t1355 = *_hp; free(_hp); }
    if (_t1355) {
        Str *_t1292 = Str_lit("LBracket", 8ULL);
        ;
        return _t1292;
    }
    ;
    Bool _t1356; { Bool *_hp = TokenType_eq(self, TokenType_RBracket()); _t1356 = *_hp; free(_hp); }
    if (_t1356) {
        Str *_t1293 = Str_lit("RBracket", 8ULL);
        ;
        return _t1293;
    }
    ;
    Bool _t1357; { Bool *_hp = TokenType_eq(self, TokenType_Comma()); _t1357 = *_hp; free(_hp); }
    if (_t1357) {
        Str *_t1294 = Str_lit("Comma", 5ULL);
        ;
        return _t1294;
    }
    ;
    Bool _t1358; { Bool *_hp = TokenType_eq(self, TokenType_Colon()); _t1358 = *_hp; free(_hp); }
    if (_t1358) {
        Str *_t1295 = Str_lit("Colon", 5ULL);
        ;
        return _t1295;
    }
    ;
    Bool _t1359; { Bool *_hp = TokenType_eq(self, TokenType_Question()); _t1359 = *_hp; free(_hp); }
    if (_t1359) {
        Str *_t1296 = Str_lit("Question", 8ULL);
        ;
        return _t1296;
    }
    ;
    Bool _t1360; { Bool *_hp = TokenType_eq(self, TokenType_Bang()); _t1360 = *_hp; free(_hp); }
    if (_t1360) {
        Str *_t1297 = Str_lit("Bang", 4ULL);
        ;
        return _t1297;
    }
    ;
    Bool _t1361; { Bool *_hp = TokenType_eq(self, TokenType_Minus()); _t1361 = *_hp; free(_hp); }
    if (_t1361) {
        Str *_t1298 = Str_lit("Minus", 5ULL);
        ;
        return _t1298;
    }
    ;
    Bool _t1362; { Bool *_hp = TokenType_eq(self, TokenType_Plus()); _t1362 = *_hp; free(_hp); }
    if (_t1362) {
        Str *_t1299 = Str_lit("Plus", 4ULL);
        ;
        return _t1299;
    }
    ;
    Bool _t1363; { Bool *_hp = TokenType_eq(self, TokenType_Star()); _t1363 = *_hp; free(_hp); }
    if (_t1363) {
        Str *_t1300 = Str_lit("Star", 4ULL);
        ;
        return _t1300;
    }
    ;
    Bool _t1364; { Bool *_hp = TokenType_eq(self, TokenType_Slash()); _t1364 = *_hp; free(_hp); }
    if (_t1364) {
        Str *_t1301 = Str_lit("Slash", 5ULL);
        ;
        return _t1301;
    }
    ;
    Bool _t1365; { Bool *_hp = TokenType_eq(self, TokenType_Dot()); _t1365 = *_hp; free(_hp); }
    if (_t1365) {
        Str *_t1302 = Str_lit("Dot", 3ULL);
        ;
        return _t1302;
    }
    ;
    Bool _t1366; { Bool *_hp = TokenType_eq(self, TokenType_DotDot()); _t1366 = *_hp; free(_hp); }
    if (_t1366) {
        Str *_t1303 = Str_lit("DotDot", 6ULL);
        ;
        return _t1303;
    }
    ;
    Bool _t1367; { Bool *_hp = TokenType_eq(self, TokenType_Eq()); _t1367 = *_hp; free(_hp); }
    if (_t1367) {
        Str *_t1304 = Str_lit("Eq", 2ULL);
        ;
        return _t1304;
    }
    ;
    Bool _t1368; { Bool *_hp = TokenType_eq(self, TokenType_EqEq()); _t1368 = *_hp; free(_hp); }
    if (_t1368) {
        Str *_t1305 = Str_lit("EqEq", 4ULL);
        ;
        return _t1305;
    }
    ;
    Bool _t1369; { Bool *_hp = TokenType_eq(self, TokenType_Neq()); _t1369 = *_hp; free(_hp); }
    if (_t1369) {
        Str *_t1306 = Str_lit("Neq", 3ULL);
        ;
        return _t1306;
    }
    ;
    Bool _t1370; { Bool *_hp = TokenType_eq(self, TokenType_Lt()); _t1370 = *_hp; free(_hp); }
    if (_t1370) {
        Str *_t1307 = Str_lit("Lt", 2ULL);
        ;
        return _t1307;
    }
    ;
    Bool _t1371; { Bool *_hp = TokenType_eq(self, TokenType_LtEq()); _t1371 = *_hp; free(_hp); }
    if (_t1371) {
        Str *_t1308 = Str_lit("LtEq", 4ULL);
        ;
        return _t1308;
    }
    ;
    Bool _t1372; { Bool *_hp = TokenType_eq(self, TokenType_Gt()); _t1372 = *_hp; free(_hp); }
    if (_t1372) {
        Str *_t1309 = Str_lit("Gt", 2ULL);
        ;
        return _t1309;
    }
    ;
    Bool _t1373; { Bool *_hp = TokenType_eq(self, TokenType_GtEq()); _t1373 = *_hp; free(_hp); }
    if (_t1373) {
        Str *_t1310 = Str_lit("GtEq", 4ULL);
        ;
        return _t1310;
    }
    ;
    Bool _t1374; { Bool *_hp = TokenType_eq(self, TokenType_ColonEq()); _t1374 = *_hp; free(_hp); }
    if (_t1374) {
        Str *_t1311 = Str_lit("ColonEq", 7ULL);
        ;
        return _t1311;
    }
    ;
    Bool _t1375; { Bool *_hp = TokenType_eq(self, TokenType_Ident()); _t1375 = *_hp; free(_hp); }
    if (_t1375) {
        Str *_t1312 = Str_lit("Ident", 5ULL);
        ;
        return _t1312;
    }
    ;
    Bool _t1376; { Bool *_hp = TokenType_eq(self, TokenType_StringTok()); _t1376 = *_hp; free(_hp); }
    if (_t1376) {
        Str *_t1313 = Str_lit("StringTok", 9ULL);
        ;
        return _t1313;
    }
    ;
    Bool _t1377; { Bool *_hp = TokenType_eq(self, TokenType_Number()); _t1377 = *_hp; free(_hp); }
    if (_t1377) {
        Str *_t1314 = Str_lit("Number", 6ULL);
        ;
        return _t1314;
    }
    ;
    Bool _t1378; { Bool *_hp = TokenType_eq(self, TokenType_Char()); _t1378 = *_hp; free(_hp); }
    if (_t1378) {
        Str *_t1315 = Str_lit("Char", 4ULL);
        ;
        return _t1315;
    }
    ;
    Bool _t1379; { Bool *_hp = TokenType_eq(self, TokenType_KwMode()); _t1379 = *_hp; free(_hp); }
    if (_t1379) {
        Str *_t1316 = Str_lit("KwMode", 6ULL);
        ;
        return _t1316;
    }
    ;
    Bool _t1380; { Bool *_hp = TokenType_eq(self, TokenType_KwMut()); _t1380 = *_hp; free(_hp); }
    if (_t1380) {
        Str *_t1317 = Str_lit("KwMut", 5ULL);
        ;
        return _t1317;
    }
    ;
    Bool _t1381; { Bool *_hp = TokenType_eq(self, TokenType_KwOwn()); _t1381 = *_hp; free(_hp); }
    if (_t1381) {
        Str *_t1318 = Str_lit("KwOwn", 5ULL);
        ;
        return _t1318;
    }
    ;
    Bool _t1382; { Bool *_hp = TokenType_eq(self, TokenType_KwRef()); _t1382 = *_hp; free(_hp); }
    if (_t1382) {
        Str *_t1319 = Str_lit("KwRef", 5ULL);
        ;
        return _t1319;
    }
    ;
    Bool _t1383; { Bool *_hp = TokenType_eq(self, TokenType_KwStruct()); _t1383 = *_hp; free(_hp); }
    if (_t1383) {
        Str *_t1320 = Str_lit("KwStruct", 8ULL);
        ;
        return _t1320;
    }
    ;
    Bool _t1384; { Bool *_hp = TokenType_eq(self, TokenType_KwExtStruct()); _t1384 = *_hp; free(_hp); }
    if (_t1384) {
        Str *_t1321 = Str_lit("KwExtStruct", 11ULL);
        ;
        return _t1321;
    }
    ;
    Bool _t1385; { Bool *_hp = TokenType_eq(self, TokenType_KwEnum()); _t1385 = *_hp; free(_hp); }
    if (_t1385) {
        Str *_t1322 = Str_lit("KwEnum", 6ULL);
        ;
        return _t1322;
    }
    ;
    Bool _t1386; { Bool *_hp = TokenType_eq(self, TokenType_KwNamespace()); _t1386 = *_hp; free(_hp); }
    if (_t1386) {
        Str *_t1323 = Str_lit("KwNamespace", 11ULL);
        ;
        return _t1323;
    }
    ;
    Bool _t1387; { Bool *_hp = TokenType_eq(self, TokenType_KwFunc()); _t1387 = *_hp; free(_hp); }
    if (_t1387) {
        Str *_t1324 = Str_lit("KwFunc", 6ULL);
        ;
        return _t1324;
    }
    ;
    Bool _t1388; { Bool *_hp = TokenType_eq(self, TokenType_KwProc()); _t1388 = *_hp; free(_hp); }
    if (_t1388) {
        Str *_t1325 = Str_lit("KwProc", 6ULL);
        ;
        return _t1325;
    }
    ;
    Bool _t1389; { Bool *_hp = TokenType_eq(self, TokenType_KwTest()); _t1389 = *_hp; free(_hp); }
    if (_t1389) {
        Str *_t1326 = Str_lit("KwTest", 6ULL);
        ;
        return _t1326;
    }
    ;
    Bool _t1390; { Bool *_hp = TokenType_eq(self, TokenType_KwMacro()); _t1390 = *_hp; free(_hp); }
    if (_t1390) {
        Str *_t1327 = Str_lit("KwMacro", 7ULL);
        ;
        return _t1327;
    }
    ;
    Bool _t1391; { Bool *_hp = TokenType_eq(self, TokenType_KwExtFunc()); _t1391 = *_hp; free(_hp); }
    if (_t1391) {
        Str *_t1328 = Str_lit("KwExtFunc", 9ULL);
        ;
        return _t1328;
    }
    ;
    Bool _t1392; { Bool *_hp = TokenType_eq(self, TokenType_KwExtProc()); _t1392 = *_hp; free(_hp); }
    if (_t1392) {
        Str *_t1329 = Str_lit("KwExtProc", 9ULL);
        ;
        return _t1329;
    }
    ;
    Bool _t1393; { Bool *_hp = TokenType_eq(self, TokenType_KwReturns()); _t1393 = *_hp; free(_hp); }
    if (_t1393) {
        Str *_t1330 = Str_lit("KwReturns", 9ULL);
        ;
        return _t1330;
    }
    ;
    Bool _t1394; { Bool *_hp = TokenType_eq(self, TokenType_KwThrows()); _t1394 = *_hp; free(_hp); }
    if (_t1394) {
        Str *_t1331 = Str_lit("KwThrows", 8ULL);
        ;
        return _t1331;
    }
    ;
    Bool _t1395; { Bool *_hp = TokenType_eq(self, TokenType_KwIf()); _t1395 = *_hp; free(_hp); }
    if (_t1395) {
        Str *_t1332 = Str_lit("KwIf", 4ULL);
        ;
        return _t1332;
    }
    ;
    Bool _t1396; { Bool *_hp = TokenType_eq(self, TokenType_KwElse()); _t1396 = *_hp; free(_hp); }
    if (_t1396) {
        Str *_t1333 = Str_lit("KwElse", 6ULL);
        ;
        return _t1333;
    }
    ;
    Bool _t1397; { Bool *_hp = TokenType_eq(self, TokenType_KwWhile()); _t1397 = *_hp; free(_hp); }
    if (_t1397) {
        Str *_t1334 = Str_lit("KwWhile", 7ULL);
        ;
        return _t1334;
    }
    ;
    Bool _t1398; { Bool *_hp = TokenType_eq(self, TokenType_KwFor()); _t1398 = *_hp; free(_hp); }
    if (_t1398) {
        Str *_t1335 = Str_lit("KwFor", 5ULL);
        ;
        return _t1335;
    }
    ;
    Bool _t1399; { Bool *_hp = TokenType_eq(self, TokenType_KwIn()); _t1399 = *_hp; free(_hp); }
    if (_t1399) {
        Str *_t1336 = Str_lit("KwIn", 4ULL);
        ;
        return _t1336;
    }
    ;
    Bool _t1400; { Bool *_hp = TokenType_eq(self, TokenType_KwSwitch()); _t1400 = *_hp; free(_hp); }
    if (_t1400) {
        Str *_t1337 = Str_lit("KwSwitch", 8ULL);
        ;
        return _t1337;
    }
    ;
    Bool _t1401; { Bool *_hp = TokenType_eq(self, TokenType_KwMatch()); _t1401 = *_hp; free(_hp); }
    if (_t1401) {
        Str *_t1338 = Str_lit("KwMatch", 7ULL);
        ;
        return _t1338;
    }
    ;
    Bool _t1402; { Bool *_hp = TokenType_eq(self, TokenType_KwCase()); _t1402 = *_hp; free(_hp); }
    if (_t1402) {
        Str *_t1339 = Str_lit("KwCase", 6ULL);
        ;
        return _t1339;
    }
    ;
    Bool _t1403; { Bool *_hp = TokenType_eq(self, TokenType_KwDefault()); _t1403 = *_hp; free(_hp); }
    if (_t1403) {
        Str *_t1340 = Str_lit("KwDefault", 9ULL);
        ;
        return _t1340;
    }
    ;
    Bool _t1404; { Bool *_hp = TokenType_eq(self, TokenType_KwReturn()); _t1404 = *_hp; free(_hp); }
    if (_t1404) {
        Str *_t1341 = Str_lit("KwReturn", 8ULL);
        ;
        return _t1341;
    }
    ;
    Bool _t1405; { Bool *_hp = TokenType_eq(self, TokenType_KwThrow()); _t1405 = *_hp; free(_hp); }
    if (_t1405) {
        Str *_t1342 = Str_lit("KwThrow", 7ULL);
        ;
        return _t1342;
    }
    ;
    Bool _t1406; { Bool *_hp = TokenType_eq(self, TokenType_KwCatch()); _t1406 = *_hp; free(_hp); }
    if (_t1406) {
        Str *_t1343 = Str_lit("KwCatch", 7ULL);
        ;
        return _t1343;
    }
    ;
    Bool _t1407; { Bool *_hp = TokenType_eq(self, TokenType_KwBreak()); _t1407 = *_hp; free(_hp); }
    if (_t1407) {
        Str *_t1344 = Str_lit("KwBreak", 7ULL);
        ;
        return _t1344;
    }
    ;
    Bool _t1408; { Bool *_hp = TokenType_eq(self, TokenType_KwContinue()); _t1408 = *_hp; free(_hp); }
    if (_t1408) {
        Str *_t1345 = Str_lit("KwContinue", 10ULL);
        ;
        return _t1345;
    }
    ;
    Bool _t1409; { Bool *_hp = TokenType_eq(self, TokenType_KwDefer()); _t1409 = *_hp; free(_hp); }
    if (_t1409) {
        Str *_t1346 = Str_lit("KwDefer", 7ULL);
        ;
        return _t1346;
    }
    ;
    Bool _t1410; { Bool *_hp = TokenType_eq(self, TokenType_KwTrue()); _t1410 = *_hp; free(_hp); }
    if (_t1410) {
        Str *_t1347 = Str_lit("KwTrue", 6ULL);
        ;
        return _t1347;
    }
    ;
    Bool _t1411; { Bool *_hp = TokenType_eq(self, TokenType_KwFalse()); _t1411 = *_hp; free(_hp); }
    if (_t1411) {
        Str *_t1348 = Str_lit("KwFalse", 7ULL);
        ;
        return _t1348;
    }
    ;
    Bool _t1412; { Bool *_hp = TokenType_eq(self, TokenType_Error()); _t1412 = *_hp; free(_hp); }
    if (_t1412) {
        Str *_t1349 = Str_lit("Error", 5ULL);
        ;
        return _t1349;
    }
    ;
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
    I64 _t1415 = I64_clone(&self->line);
    I64 _t1416 = I64_clone(&self->col);
    Token *_t1417 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(&self->type); _t1417->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->text); _t1417->text = *_ca; free(_ca); }
    _t1417->line = _t1415;
    _t1417->col = _t1416;
    ;
    ;
    return _t1417;
}

void Token_delete(Token * self, Bool * call_free) {
    (void)self;
    Bool _t1418 = 0;
    TokenType_delete(&self->type, &(Bool){_t1418});
    ;
    Bool _t1419 = 0;
    Str_delete(&self->text, &(Bool){_t1419});
    ;
    Bool _t1420 = 0;
    I64_delete(&self->line, &(Bool){_t1420});
    ;
    Bool _t1421 = 0;
    I64_delete(&self->col, &(Bool){_t1421});
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
    U8 _t1423 = 48;
    U8 _t1424 = 57;
    Bool _t1425; { Bool *_hp = U8_gte(c, &(U8){_t1423}); _t1425 = *_hp; free(_hp); }
    ;
    Bool _t1426; { Bool *_hp = U8_lte(c, &(U8){_t1424}); _t1426 = *_hp; free(_hp); }
    ;
    Bool _t1427 = Bool_and(_t1425, _t1426);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1427; return _r; }
}

Bool * is_alpha(U8 * c) {
    U8 _t1428 = 97;
    U8 _t1429 = 122;
    Bool _t1430; { Bool *_hp = U8_gte(c, &(U8){_t1428}); _t1430 = *_hp; free(_hp); }
    ;
    Bool _t1431; { Bool *_hp = U8_lte(c, &(U8){_t1429}); _t1431 = *_hp; free(_hp); }
    ;
    U8 _t1432 = 65;
    U8 _t1433 = 90;
    Bool _t1434; { Bool *_hp = U8_gte(c, &(U8){_t1432}); _t1434 = *_hp; free(_hp); }
    ;
    Bool _t1435; { Bool *_hp = U8_lte(c, &(U8){_t1433}); _t1435 = *_hp; free(_hp); }
    ;
    Bool _t1436 = Bool_and(_t1430, _t1431);
    ;
    ;
    Bool _t1437 = Bool_and(_t1434, _t1435);
    ;
    ;
    U8 _t1438 = 95;
    Bool _t1439 = Bool_or(_t1436, _t1437);
    ;
    ;
    Bool _t1440 = U8_eq(DEREF(c), _t1438);
    ;
    Bool _t1441 = Bool_or(_t1439, _t1440);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1441; return _r; }
}

Bool * is_alnum(U8 * c) {
    Bool _t1442; { Bool *_hp = is_alpha(c); _t1442 = *_hp; free(_hp); }
    Bool _t1443; { Bool *_hp = is_digit(c); _t1443 = *_hp; free(_hp); }
    Bool _t1444 = Bool_or(_t1442, _t1443);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1444; return _r; }
}

Str * tok_name(TokenType * type) {
    {
        TokenType *_sw1445 = TokenType_clone(type);
        Bool _t1572; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Eof()); _t1572 = *_hp; free(_hp); }
        if (_t1572) {
            Str *_t1446 = Str_lit("eof", 3ULL);
            TokenType_delete(_sw1445, &(Bool){1});
            ;
            return _t1446;
        } else {
            Bool _t1571; { Bool *_hp = TokenType_eq(_sw1445, TokenType_LParen()); _t1571 = *_hp; free(_hp); }
            if (_t1571) {
                Str *_t1447 = Str_lit("(", 1ULL);
                ;
                TokenType_delete(_sw1445, &(Bool){1});
                ;
                return _t1447;
            } else {
                Bool _t1570; { Bool *_hp = TokenType_eq(_sw1445, TokenType_RParen()); _t1570 = *_hp; free(_hp); }
                if (_t1570) {
                    Str *_t1448 = Str_lit(")", 1ULL);
                    ;
                    ;
                    TokenType_delete(_sw1445, &(Bool){1});
                    ;
                    return _t1448;
                } else {
                    Bool _t1569; { Bool *_hp = TokenType_eq(_sw1445, TokenType_LBrace()); _t1569 = *_hp; free(_hp); }
                    if (_t1569) {
                        Str *_t1449 = Str_lit("{", 1ULL);
                        ;
                        ;
                        ;
                        TokenType_delete(_sw1445, &(Bool){1});
                        ;
                        return _t1449;
                    } else {
                        Bool _t1568; { Bool *_hp = TokenType_eq(_sw1445, TokenType_RBrace()); _t1568 = *_hp; free(_hp); }
                        if (_t1568) {
                            Str *_t1450 = Str_lit("}", 1ULL);
                            ;
                            ;
                            ;
                            ;
                            TokenType_delete(_sw1445, &(Bool){1});
                            ;
                            return _t1450;
                        } else {
                            Bool _t1567; { Bool *_hp = TokenType_eq(_sw1445, TokenType_LBracket()); _t1567 = *_hp; free(_hp); }
                            if (_t1567) {
                                Str *_t1451 = Str_lit("[", 1ULL);
                                ;
                                ;
                                ;
                                ;
                                ;
                                TokenType_delete(_sw1445, &(Bool){1});
                                ;
                                return _t1451;
                            } else {
                                Bool _t1566; { Bool *_hp = TokenType_eq(_sw1445, TokenType_RBracket()); _t1566 = *_hp; free(_hp); }
                                if (_t1566) {
                                    Str *_t1452 = Str_lit("]", 1ULL);
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    TokenType_delete(_sw1445, &(Bool){1});
                                    ;
                                    return _t1452;
                                } else {
                                    Bool _t1565; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Comma()); _t1565 = *_hp; free(_hp); }
                                    if (_t1565) {
                                        Str *_t1453 = Str_lit(",", 1ULL);
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        TokenType_delete(_sw1445, &(Bool){1});
                                        ;
                                        return _t1453;
                                    } else {
                                        Bool _t1564; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Colon()); _t1564 = *_hp; free(_hp); }
                                        if (_t1564) {
                                            Str *_t1454 = Str_lit(":", 1ULL);
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            ;
                                            TokenType_delete(_sw1445, &(Bool){1});
                                            ;
                                            return _t1454;
                                        } else {
                                            Bool _t1563; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Question()); _t1563 = *_hp; free(_hp); }
                                            if (_t1563) {
                                                Str *_t1455 = Str_lit("?", 1ULL);
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                ;
                                                TokenType_delete(_sw1445, &(Bool){1});
                                                ;
                                                return _t1455;
                                            } else {
                                                Bool _t1562; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Bang()); _t1562 = *_hp; free(_hp); }
                                                if (_t1562) {
                                                    Str *_t1456 = Str_lit("!", 1ULL);
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    ;
                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                    ;
                                                    return _t1456;
                                                } else {
                                                    Bool _t1561; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Minus()); _t1561 = *_hp; free(_hp); }
                                                    if (_t1561) {
                                                        Str *_t1457 = Str_lit("-", 1ULL);
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        ;
                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                        ;
                                                        return _t1457;
                                                    } else {
                                                        Bool _t1560; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Plus()); _t1560 = *_hp; free(_hp); }
                                                        if (_t1560) {
                                                            Str *_t1458 = Str_lit("+", 1ULL);
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            ;
                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                            ;
                                                            return _t1458;
                                                        } else {
                                                            Bool _t1559; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Star()); _t1559 = *_hp; free(_hp); }
                                                            if (_t1559) {
                                                                Str *_t1459 = Str_lit("*", 1ULL);
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                ;
                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                ;
                                                                return _t1459;
                                                            } else {
                                                                Bool _t1558; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Slash()); _t1558 = *_hp; free(_hp); }
                                                                if (_t1558) {
                                                                    Str *_t1460 = Str_lit("/", 1ULL);
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    ;
                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                    ;
                                                                    return _t1460;
                                                                } else {
                                                                    Bool _t1557; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Dot()); _t1557 = *_hp; free(_hp); }
                                                                    if (_t1557) {
                                                                        Str *_t1461 = Str_lit(".", 1ULL);
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        ;
                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                        ;
                                                                        return _t1461;
                                                                    } else {
                                                                        Bool _t1556; { Bool *_hp = TokenType_eq(_sw1445, TokenType_DotDot()); _t1556 = *_hp; free(_hp); }
                                                                        if (_t1556) {
                                                                            Str *_t1462 = Str_lit("..", 2ULL);
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            ;
                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                            ;
                                                                            return _t1462;
                                                                        } else {
                                                                            Bool _t1555; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Eq()); _t1555 = *_hp; free(_hp); }
                                                                            if (_t1555) {
                                                                                Str *_t1463 = Str_lit("=", 1ULL);
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                ;
                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                ;
                                                                                return _t1463;
                                                                            } else {
                                                                                Bool _t1554; { Bool *_hp = TokenType_eq(_sw1445, TokenType_EqEq()); _t1554 = *_hp; free(_hp); }
                                                                                if (_t1554) {
                                                                                    Str *_t1464 = Str_lit("==", 2ULL);
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    ;
                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                    ;
                                                                                    return _t1464;
                                                                                } else {
                                                                                    Bool _t1553; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Neq()); _t1553 = *_hp; free(_hp); }
                                                                                    if (_t1553) {
                                                                                        Str *_t1465 = Str_lit("!=", 2ULL);
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        ;
                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                        ;
                                                                                        return _t1465;
                                                                                    } else {
                                                                                        Bool _t1552; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Lt()); _t1552 = *_hp; free(_hp); }
                                                                                        if (_t1552) {
                                                                                            Str *_t1466 = Str_lit("<", 1ULL);
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            ;
                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                            ;
                                                                                            return _t1466;
                                                                                        } else {
                                                                                            Bool _t1551; { Bool *_hp = TokenType_eq(_sw1445, TokenType_LtEq()); _t1551 = *_hp; free(_hp); }
                                                                                            if (_t1551) {
                                                                                                Str *_t1467 = Str_lit("<=", 2ULL);
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                ;
                                                                                                return _t1467;
                                                                                            } else {
                                                                                                Bool _t1550; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Gt()); _t1550 = *_hp; free(_hp); }
                                                                                                if (_t1550) {
                                                                                                    Str *_t1468 = Str_lit(">", 1ULL);
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                    ;
                                                                                                    return _t1468;
                                                                                                } else {
                                                                                                    Bool _t1549; { Bool *_hp = TokenType_eq(_sw1445, TokenType_GtEq()); _t1549 = *_hp; free(_hp); }
                                                                                                    if (_t1549) {
                                                                                                        Str *_t1469 = Str_lit(">=", 2ULL);
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                        ;
                                                                                                        return _t1469;
                                                                                                    } else {
                                                                                                        Bool _t1548; { Bool *_hp = TokenType_eq(_sw1445, TokenType_ColonEq()); _t1548 = *_hp; free(_hp); }
                                                                                                        if (_t1548) {
                                                                                                            Str *_t1470 = Str_lit(":=", 2ULL);
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                            ;
                                                                                                            return _t1470;
                                                                                                        } else {
                                                                                                            Bool _t1547; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Ident()); _t1547 = *_hp; free(_hp); }
                                                                                                            if (_t1547) {
                                                                                                                Str *_t1471 = Str_lit("identifier", 10ULL);
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                ;
                                                                                                                return _t1471;
                                                                                                            } else {
                                                                                                                Bool _t1546; { Bool *_hp = TokenType_eq(_sw1445, TokenType_StringTok()); _t1546 = *_hp; free(_hp); }
                                                                                                                if (_t1546) {
                                                                                                                    Str *_t1472 = Str_lit("string", 6ULL);
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return _t1472;
                                                                                                                } else {
                                                                                                                    Bool _t1545; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Number()); _t1545 = *_hp; free(_hp); }
                                                                                                                    if (_t1545) {
                                                                                                                        Str *_t1473 = Str_lit("number", 6ULL);
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return _t1473;
                                                                                                                    } else {
                                                                                                                        Bool _t1544; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Char()); _t1544 = *_hp; free(_hp); }
                                                                                                                        if (_t1544) {
                                                                                                                            Str *_t1474 = Str_lit("char", 4ULL);
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return _t1474;
                                                                                                                        } else {
                                                                                                                            Bool _t1543; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwMode()); _t1543 = *_hp; free(_hp); }
                                                                                                                            if (_t1543) {
                                                                                                                                Str *_t1475 = Str_lit("mode", 4ULL);
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return _t1475;
                                                                                                                            } else {
                                                                                                                                Bool _t1542; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwMut()); _t1542 = *_hp; free(_hp); }
                                                                                                                                if (_t1542) {
                                                                                                                                    Str *_t1476 = Str_lit("mut", 3ULL);
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return _t1476;
                                                                                                                                } else {
                                                                                                                                    Bool _t1541; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwOwn()); _t1541 = *_hp; free(_hp); }
                                                                                                                                    if (_t1541) {
                                                                                                                                        Str *_t1477 = Str_lit("own", 3ULL);
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return _t1477;
                                                                                                                                    } else {
                                                                                                                                        Bool _t1540; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwRef()); _t1540 = *_hp; free(_hp); }
                                                                                                                                        if (_t1540) {
                                                                                                                                            Str *_t1478 = Str_lit("ref", 3ULL);
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                            ;
                                                                                                                                            return _t1478;
                                                                                                                                        } else {
                                                                                                                                            Bool _t1539; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwStruct()); _t1539 = *_hp; free(_hp); }
                                                                                                                                            if (_t1539) {
                                                                                                                                                Str *_t1479 = Str_lit("struct", 6ULL);
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                ;
                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                ;
                                                                                                                                                return _t1479;
                                                                                                                                            } else {
                                                                                                                                                Bool _t1538; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwExtStruct()); _t1538 = *_hp; free(_hp); }
                                                                                                                                                if (_t1538) {
                                                                                                                                                    Str *_t1480 = Str_lit("ext_struct", 10ULL);
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    ;
                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                    ;
                                                                                                                                                    return _t1480;
                                                                                                                                                } else {
                                                                                                                                                    Bool _t1537; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwEnum()); _t1537 = *_hp; free(_hp); }
                                                                                                                                                    if (_t1537) {
                                                                                                                                                        Str *_t1481 = Str_lit("enum", 4ULL);
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        ;
                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                        ;
                                                                                                                                                        return _t1481;
                                                                                                                                                    } else {
                                                                                                                                                        Bool _t1536; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwNamespace()); _t1536 = *_hp; free(_hp); }
                                                                                                                                                        if (_t1536) {
                                                                                                                                                            Str *_t1482 = Str_lit("namespace", 9ULL);
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            ;
                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                            ;
                                                                                                                                                            return _t1482;
                                                                                                                                                        } else {
                                                                                                                                                            Bool _t1535; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwFunc()); _t1535 = *_hp; free(_hp); }
                                                                                                                                                            if (_t1535) {
                                                                                                                                                                Str *_t1483 = Str_lit("func", 4ULL);
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                ;
                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                ;
                                                                                                                                                                return _t1483;
                                                                                                                                                            } else {
                                                                                                                                                                Bool _t1534; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwProc()); _t1534 = *_hp; free(_hp); }
                                                                                                                                                                if (_t1534) {
                                                                                                                                                                    Str *_t1484 = Str_lit("proc", 4ULL);
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    ;
                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                    ;
                                                                                                                                                                    return _t1484;
                                                                                                                                                                } else {
                                                                                                                                                                    Bool _t1533; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwTest()); _t1533 = *_hp; free(_hp); }
                                                                                                                                                                    if (_t1533) {
                                                                                                                                                                        Str *_t1485 = Str_lit("test", 4ULL);
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        ;
                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                        ;
                                                                                                                                                                        return _t1485;
                                                                                                                                                                    } else {
                                                                                                                                                                        Bool _t1532; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwMacro()); _t1532 = *_hp; free(_hp); }
                                                                                                                                                                        if (_t1532) {
                                                                                                                                                                            Str *_t1486 = Str_lit("macro", 5ULL);
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            ;
                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                            ;
                                                                                                                                                                            return _t1486;
                                                                                                                                                                        } else {
                                                                                                                                                                            Bool _t1531; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwExtFunc()); _t1531 = *_hp; free(_hp); }
                                                                                                                                                                            if (_t1531) {
                                                                                                                                                                                Str *_t1487 = Str_lit("ext_func", 8ULL);
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                ;
                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                ;
                                                                                                                                                                                return _t1487;
                                                                                                                                                                            } else {
                                                                                                                                                                                Bool _t1530; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwExtProc()); _t1530 = *_hp; free(_hp); }
                                                                                                                                                                                if (_t1530) {
                                                                                                                                                                                    Str *_t1488 = Str_lit("ext_proc", 8ULL);
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    ;
                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                    ;
                                                                                                                                                                                    return _t1488;
                                                                                                                                                                                } else {
                                                                                                                                                                                    Bool _t1529; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwReturns()); _t1529 = *_hp; free(_hp); }
                                                                                                                                                                                    if (_t1529) {
                                                                                                                                                                                        Str *_t1489 = Str_lit("returns", 7ULL);
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        ;
                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                        ;
                                                                                                                                                                                        return _t1489;
                                                                                                                                                                                    } else {
                                                                                                                                                                                        Bool _t1528; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwThrows()); _t1528 = *_hp; free(_hp); }
                                                                                                                                                                                        if (_t1528) {
                                                                                                                                                                                            Str *_t1490 = Str_lit("throws", 6ULL);
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            ;
                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                            ;
                                                                                                                                                                                            return _t1490;
                                                                                                                                                                                        } else {
                                                                                                                                                                                            Bool _t1527; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwIf()); _t1527 = *_hp; free(_hp); }
                                                                                                                                                                                            if (_t1527) {
                                                                                                                                                                                                Str *_t1491 = Str_lit("if", 2ULL);
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                ;
                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                ;
                                                                                                                                                                                                return _t1491;
                                                                                                                                                                                            } else {
                                                                                                                                                                                                Bool _t1526; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwElse()); _t1526 = *_hp; free(_hp); }
                                                                                                                                                                                                if (_t1526) {
                                                                                                                                                                                                    Str *_t1492 = Str_lit("else", 4ULL);
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                    ;
                                                                                                                                                                                                    return _t1492;
                                                                                                                                                                                                } else {
                                                                                                                                                                                                    Bool _t1525; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwWhile()); _t1525 = *_hp; free(_hp); }
                                                                                                                                                                                                    if (_t1525) {
                                                                                                                                                                                                        Str *_t1493 = Str_lit("while", 5ULL);
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                        ;
                                                                                                                                                                                                        return _t1493;
                                                                                                                                                                                                    } else {
                                                                                                                                                                                                        Bool _t1524; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwFor()); _t1524 = *_hp; free(_hp); }
                                                                                                                                                                                                        if (_t1524) {
                                                                                                                                                                                                            Str *_t1494 = Str_lit("for", 3ULL);
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                            ;
                                                                                                                                                                                                            return _t1494;
                                                                                                                                                                                                        } else {
                                                                                                                                                                                                            Bool _t1523; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwIn()); _t1523 = *_hp; free(_hp); }
                                                                                                                                                                                                            if (_t1523) {
                                                                                                                                                                                                                Str *_t1495 = Str_lit("in", 2ULL);
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                ;
                                                                                                                                                                                                                return _t1495;
                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                Bool _t1522; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwSwitch()); _t1522 = *_hp; free(_hp); }
                                                                                                                                                                                                                if (_t1522) {
                                                                                                                                                                                                                    Str *_t1496 = Str_lit("switch", 6ULL);
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                    return _t1496;
                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                    Bool _t1521; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwMatch()); _t1521 = *_hp; free(_hp); }
                                                                                                                                                                                                                    if (_t1521) {
                                                                                                                                                                                                                        Str *_t1497 = Str_lit("match", 5ULL);
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                        return _t1497;
                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                        Bool _t1520; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwCase()); _t1520 = *_hp; free(_hp); }
                                                                                                                                                                                                                        if (_t1520) {
                                                                                                                                                                                                                            Str *_t1498 = Str_lit("case", 4ULL);
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                            return _t1498;
                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                            Bool _t1519; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwDefault()); _t1519 = *_hp; free(_hp); }
                                                                                                                                                                                                                            if (_t1519) {
                                                                                                                                                                                                                                Str *_t1499 = Str_lit("default", 7ULL);
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                return _t1499;
                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                Bool _t1518; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwReturn()); _t1518 = *_hp; free(_hp); }
                                                                                                                                                                                                                                if (_t1518) {
                                                                                                                                                                                                                                    Str *_t1500 = Str_lit("return", 6ULL);
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                    return _t1500;
                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                    Bool _t1517; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwThrow()); _t1517 = *_hp; free(_hp); }
                                                                                                                                                                                                                                    if (_t1517) {
                                                                                                                                                                                                                                        Str *_t1501 = Str_lit("throw", 5ULL);
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                        return _t1501;
                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                        Bool _t1516; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwCatch()); _t1516 = *_hp; free(_hp); }
                                                                                                                                                                                                                                        if (_t1516) {
                                                                                                                                                                                                                                            Str *_t1502 = Str_lit("catch", 5ULL);
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                            return _t1502;
                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                            Bool _t1515; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwBreak()); _t1515 = *_hp; free(_hp); }
                                                                                                                                                                                                                                            if (_t1515) {
                                                                                                                                                                                                                                                Str *_t1503 = Str_lit("break", 5ULL);
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                return _t1503;
                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                Bool _t1514; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwContinue()); _t1514 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                if (_t1514) {
                                                                                                                                                                                                                                                    Str *_t1504 = Str_lit("continue", 8ULL);
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                    return _t1504;
                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                    Bool _t1513; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwDefer()); _t1513 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                    if (_t1513) {
                                                                                                                                                                                                                                                        Str *_t1505 = Str_lit("defer", 5ULL);
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                        return _t1505;
                                                                                                                                                                                                                                                    } else {
                                                                                                                                                                                                                                                        Bool _t1512; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwTrue()); _t1512 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                        if (_t1512) {
                                                                                                                                                                                                                                                            Str *_t1506 = Str_lit("true", 4ULL);
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                            return _t1506;
                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                            Bool _t1511; { Bool *_hp = TokenType_eq(_sw1445, TokenType_KwFalse()); _t1511 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                            if (_t1511) {
                                                                                                                                                                                                                                                                Str *_t1507 = Str_lit("false", 5ULL);
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                                return _t1507;
                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                Bool _t1510; { Bool *_hp = TokenType_eq(_sw1445, TokenType_Error()); _t1510 = *_hp; free(_hp); }
                                                                                                                                                                                                                                                                if (_t1510) {
                                                                                                                                                                                                                                                                    Str *_t1508 = Str_lit("error", 5ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1508;
                                                                                                                                                                                                                                                                } else {
                                                                                                                                                                                                                                                                    Str *_t1509 = Str_lit("?", 1ULL);
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    TokenType_delete(_sw1445, &(Bool){1});
                                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                                    return _t1509;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                ;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                            ;
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                        ;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    ;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                ;
                                                                                                                                                                                                            }
                                                                                                                                                                                                            ;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        ;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    ;
                                                                                                                                                                                                }
                                                                                                                                                                                                ;
                                                                                                                                                                                            }
                                                                                                                                                                                            ;
                                                                                                                                                                                        }
                                                                                                                                                                                        ;
                                                                                                                                                                                    }
                                                                                                                                                                                    ;
                                                                                                                                                                                }
                                                                                                                                                                                ;
                                                                                                                                                                            }
                                                                                                                                                                            ;
                                                                                                                                                                        }
                                                                                                                                                                        ;
                                                                                                                                                                    }
                                                                                                                                                                    ;
                                                                                                                                                                }
                                                                                                                                                                ;
                                                                                                                                                            }
                                                                                                                                                            ;
                                                                                                                                                        }
                                                                                                                                                        ;
                                                                                                                                                    }
                                                                                                                                                    ;
                                                                                                                                                }
                                                                                                                                                ;
                                                                                                                                            }
                                                                                                                                            ;
                                                                                                                                        }
                                                                                                                                        ;
                                                                                                                                    }
                                                                                                                                    ;
                                                                                                                                }
                                                                                                                                ;
                                                                                                                            }
                                                                                                                            ;
                                                                                                                        }
                                                                                                                        ;
                                                                                                                    }
                                                                                                                    ;
                                                                                                                }
                                                                                                                ;
                                                                                                            }
                                                                                                            ;
                                                                                                        }
                                                                                                        ;
                                                                                                    }
                                                                                                    ;
                                                                                                }
                                                                                                ;
                                                                                            }
                                                                                            ;
                                                                                        }
                                                                                        ;
                                                                                    }
                                                                                    ;
                                                                                }
                                                                                ;
                                                                            }
                                                                            ;
                                                                        }
                                                                        ;
                                                                    }
                                                                    ;
                                                                }
                                                                ;
                                                            }
                                                            ;
                                                        }
                                                        ;
                                                    }
                                                    ;
                                                }
                                                ;
                                            }
                                            ;
                                        }
                                        ;
                                    }
                                    ;
                                }
                                ;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                }
                ;
            }
            ;
        }
        TokenType_delete(_sw1445, &(Bool){1});
        ;
    }
}

TokenType * lookup_keyword(Str * word) {
    {
        Str *_sw1573 = Str_clone(word);
        Str *_t1638 = Str_lit("mode", 4ULL);
        Bool _t1639; { Bool *_hp = Str_eq(_sw1573, _t1638); _t1639 = *_hp; free(_hp); }
        Str_delete(_t1638, &(Bool){1});
        if (_t1639) {
            Str_delete(_sw1573, &(Bool){1});
            ;
            return TokenType_KwMode();
        } else {
            Str *_t1636 = Str_lit("mut", 3ULL);
            Bool _t1637; { Bool *_hp = Str_eq(_sw1573, _t1636); _t1637 = *_hp; free(_hp); }
            Str_delete(_t1636, &(Bool){1});
            if (_t1637) {
                ;
                Str_delete(_sw1573, &(Bool){1});
                ;
                return TokenType_KwMut();
            } else {
                Str *_t1634 = Str_lit("own", 3ULL);
                Bool _t1635; { Bool *_hp = Str_eq(_sw1573, _t1634); _t1635 = *_hp; free(_hp); }
                Str_delete(_t1634, &(Bool){1});
                if (_t1635) {
                    ;
                    ;
                    Str_delete(_sw1573, &(Bool){1});
                    ;
                    return TokenType_KwOwn();
                } else {
                    Str *_t1632 = Str_lit("ref", 3ULL);
                    Bool _t1633; { Bool *_hp = Str_eq(_sw1573, _t1632); _t1633 = *_hp; free(_hp); }
                    Str_delete(_t1632, &(Bool){1});
                    if (_t1633) {
                        ;
                        ;
                        ;
                        Str_delete(_sw1573, &(Bool){1});
                        ;
                        return TokenType_KwRef();
                    } else {
                        Str *_t1630 = Str_lit("struct", 6ULL);
                        Bool _t1631; { Bool *_hp = Str_eq(_sw1573, _t1630); _t1631 = *_hp; free(_hp); }
                        Str_delete(_t1630, &(Bool){1});
                        if (_t1631) {
                            ;
                            ;
                            ;
                            ;
                            Str_delete(_sw1573, &(Bool){1});
                            ;
                            return TokenType_KwStruct();
                        } else {
                            Str *_t1628 = Str_lit("ext_struct", 10ULL);
                            Bool _t1629; { Bool *_hp = Str_eq(_sw1573, _t1628); _t1629 = *_hp; free(_hp); }
                            Str_delete(_t1628, &(Bool){1});
                            if (_t1629) {
                                ;
                                ;
                                ;
                                ;
                                ;
                                Str_delete(_sw1573, &(Bool){1});
                                ;
                                return TokenType_KwExtStruct();
                            } else {
                                Str *_t1626 = Str_lit("enum", 4ULL);
                                Bool _t1627; { Bool *_hp = Str_eq(_sw1573, _t1626); _t1627 = *_hp; free(_hp); }
                                Str_delete(_t1626, &(Bool){1});
                                if (_t1627) {
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    ;
                                    Str_delete(_sw1573, &(Bool){1});
                                    ;
                                    return TokenType_KwEnum();
                                } else {
                                    Str *_t1624 = Str_lit("namespace", 9ULL);
                                    Bool _t1625; { Bool *_hp = Str_eq(_sw1573, _t1624); _t1625 = *_hp; free(_hp); }
                                    Str_delete(_t1624, &(Bool){1});
                                    if (_t1625) {
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        ;
                                        Str_delete(_sw1573, &(Bool){1});
                                        ;
                                        return TokenType_KwNamespace();
                                    } else {
                                        Str *_t1622 = Str_lit("func", 4ULL);
                                        Bool _t1623; { Bool *_hp = Str_eq(_sw1573, _t1622); _t1623 = *_hp; free(_hp); }
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
                                            Str_delete(_sw1573, &(Bool){1});
                                            ;
                                            return TokenType_KwFunc();
                                        } else {
                                            Str *_t1620 = Str_lit("proc", 4ULL);
                                            Bool _t1621; { Bool *_hp = Str_eq(_sw1573, _t1620); _t1621 = *_hp; free(_hp); }
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
                                                Str_delete(_sw1573, &(Bool){1});
                                                ;
                                                return TokenType_KwProc();
                                            } else {
                                                Str *_t1618 = Str_lit("test", 4ULL);
                                                Bool _t1619; { Bool *_hp = Str_eq(_sw1573, _t1618); _t1619 = *_hp; free(_hp); }
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
                                                    Str_delete(_sw1573, &(Bool){1});
                                                    ;
                                                    return TokenType_KwTest();
                                                } else {
                                                    Str *_t1616 = Str_lit("macro", 5ULL);
                                                    Bool _t1617; { Bool *_hp = Str_eq(_sw1573, _t1616); _t1617 = *_hp; free(_hp); }
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
                                                        Str_delete(_sw1573, &(Bool){1});
                                                        ;
                                                        return TokenType_KwMacro();
                                                    } else {
                                                        Str *_t1614 = Str_lit("ext_func", 8ULL);
                                                        Bool _t1615; { Bool *_hp = Str_eq(_sw1573, _t1614); _t1615 = *_hp; free(_hp); }
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
                                                            Str_delete(_sw1573, &(Bool){1});
                                                            ;
                                                            return TokenType_KwExtFunc();
                                                        } else {
                                                            Str *_t1612 = Str_lit("ext_proc", 8ULL);
                                                            Bool _t1613; { Bool *_hp = Str_eq(_sw1573, _t1612); _t1613 = *_hp; free(_hp); }
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
                                                                Str_delete(_sw1573, &(Bool){1});
                                                                ;
                                                                return TokenType_KwExtProc();
                                                            } else {
                                                                Str *_t1610 = Str_lit("returns", 7ULL);
                                                                Bool _t1611; { Bool *_hp = Str_eq(_sw1573, _t1610); _t1611 = *_hp; free(_hp); }
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
                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                    ;
                                                                    return TokenType_KwReturns();
                                                                } else {
                                                                    Str *_t1608 = Str_lit("throws", 6ULL);
                                                                    Bool _t1609; { Bool *_hp = Str_eq(_sw1573, _t1608); _t1609 = *_hp; free(_hp); }
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
                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                        ;
                                                                        return TokenType_KwThrows();
                                                                    } else {
                                                                        Str *_t1606 = Str_lit("if", 2ULL);
                                                                        Bool _t1607; { Bool *_hp = Str_eq(_sw1573, _t1606); _t1607 = *_hp; free(_hp); }
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
                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                            ;
                                                                            return TokenType_KwIf();
                                                                        } else {
                                                                            Str *_t1604 = Str_lit("else", 4ULL);
                                                                            Bool _t1605; { Bool *_hp = Str_eq(_sw1573, _t1604); _t1605 = *_hp; free(_hp); }
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
                                                                                Str_delete(_sw1573, &(Bool){1});
                                                                                ;
                                                                                return TokenType_KwElse();
                                                                            } else {
                                                                                Str *_t1602 = Str_lit("while", 5ULL);
                                                                                Bool _t1603; { Bool *_hp = Str_eq(_sw1573, _t1602); _t1603 = *_hp; free(_hp); }
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
                                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                                    ;
                                                                                    return TokenType_KwWhile();
                                                                                } else {
                                                                                    Str *_t1600 = Str_lit("for", 3ULL);
                                                                                    Bool _t1601; { Bool *_hp = Str_eq(_sw1573, _t1600); _t1601 = *_hp; free(_hp); }
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
                                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                                        ;
                                                                                        return TokenType_KwFor();
                                                                                    } else {
                                                                                        Str *_t1598 = Str_lit("in", 2ULL);
                                                                                        Bool _t1599; { Bool *_hp = Str_eq(_sw1573, _t1598); _t1599 = *_hp; free(_hp); }
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
                                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                                            ;
                                                                                            return TokenType_KwIn();
                                                                                        } else {
                                                                                            Str *_t1596 = Str_lit("switch", 6ULL);
                                                                                            Bool _t1597; { Bool *_hp = Str_eq(_sw1573, _t1596); _t1597 = *_hp; free(_hp); }
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
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                ;
                                                                                                Str_delete(_sw1573, &(Bool){1});
                                                                                                ;
                                                                                                return TokenType_KwSwitch();
                                                                                            } else {
                                                                                                Str *_t1594 = Str_lit("match", 5ULL);
                                                                                                Bool _t1595; { Bool *_hp = Str_eq(_sw1573, _t1594); _t1595 = *_hp; free(_hp); }
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
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    ;
                                                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                                                    ;
                                                                                                    return TokenType_KwMatch();
                                                                                                } else {
                                                                                                    Str *_t1592 = Str_lit("case", 4ULL);
                                                                                                    Bool _t1593; { Bool *_hp = Str_eq(_sw1573, _t1592); _t1593 = *_hp; free(_hp); }
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
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        ;
                                                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                                                        ;
                                                                                                        return TokenType_KwCase();
                                                                                                    } else {
                                                                                                        Str *_t1590 = Str_lit("default", 7ULL);
                                                                                                        Bool _t1591; { Bool *_hp = Str_eq(_sw1573, _t1590); _t1591 = *_hp; free(_hp); }
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
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            ;
                                                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                                                            ;
                                                                                                            return TokenType_KwDefault();
                                                                                                        } else {
                                                                                                            Str *_t1588 = Str_lit("return", 6ULL);
                                                                                                            Bool _t1589; { Bool *_hp = Str_eq(_sw1573, _t1588); _t1589 = *_hp; free(_hp); }
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
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                ;
                                                                                                                Str_delete(_sw1573, &(Bool){1});
                                                                                                                ;
                                                                                                                return TokenType_KwReturn();
                                                                                                            } else {
                                                                                                                Str *_t1586 = Str_lit("throw", 5ULL);
                                                                                                                Bool _t1587; { Bool *_hp = Str_eq(_sw1573, _t1586); _t1587 = *_hp; free(_hp); }
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
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    ;
                                                                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                                                                    ;
                                                                                                                    return TokenType_KwThrow();
                                                                                                                } else {
                                                                                                                    Str *_t1584 = Str_lit("catch", 5ULL);
                                                                                                                    Bool _t1585; { Bool *_hp = Str_eq(_sw1573, _t1584); _t1585 = *_hp; free(_hp); }
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
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        ;
                                                                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                                                                        ;
                                                                                                                        return TokenType_KwCatch();
                                                                                                                    } else {
                                                                                                                        Str *_t1582 = Str_lit("break", 5ULL);
                                                                                                                        Bool _t1583; { Bool *_hp = Str_eq(_sw1573, _t1582); _t1583 = *_hp; free(_hp); }
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
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            ;
                                                                                                                            Str_delete(_sw1573, &(Bool){1});
                                                                                                                            ;
                                                                                                                            return TokenType_KwBreak();
                                                                                                                        } else {
                                                                                                                            Str *_t1580 = Str_lit("continue", 8ULL);
                                                                                                                            Bool _t1581; { Bool *_hp = Str_eq(_sw1573, _t1580); _t1581 = *_hp; free(_hp); }
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
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                ;
                                                                                                                                Str_delete(_sw1573, &(Bool){1});
                                                                                                                                ;
                                                                                                                                return TokenType_KwContinue();
                                                                                                                            } else {
                                                                                                                                Str *_t1578 = Str_lit("defer", 5ULL);
                                                                                                                                Bool _t1579; { Bool *_hp = Str_eq(_sw1573, _t1578); _t1579 = *_hp; free(_hp); }
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
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    ;
                                                                                                                                    Str_delete(_sw1573, &(Bool){1});
                                                                                                                                    ;
                                                                                                                                    return TokenType_KwDefer();
                                                                                                                                } else {
                                                                                                                                    Str *_t1576 = Str_lit("true", 4ULL);
                                                                                                                                    Bool _t1577; { Bool *_hp = Str_eq(_sw1573, _t1576); _t1577 = *_hp; free(_hp); }
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
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        ;
                                                                                                                                        Str_delete(_sw1573, &(Bool){1});
                                                                                                                                        ;
                                                                                                                                        return TokenType_KwTrue();
                                                                                                                                    } else {
                                                                                                                                        Str *_t1574 = Str_lit("false", 5ULL);
                                                                                                                                        Bool _t1575; { Bool *_hp = Str_eq(_sw1573, _t1574); _t1575 = *_hp; free(_hp); }
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
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            ;
                                                                                                                                            Str_delete(_sw1573, &(Bool){1});
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
                                                                                                                                            Str_delete(_sw1573, &(Bool){1});
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
        Str_delete(_sw1573, &(Bool){1});
        ;
    }
}

Vec * tokenize(Str * source, Str * path) {
    Str *_t1995 = Str_lit("Token", 5ULL);
    U64 _t1996; { U64 *_hp = Token_size(); _t1996 = *_hp; free(_hp); }
    Vec *tokens = Vec_new(_t1995, &(U64){_t1996});
    Str_delete(_t1995, &(Bool){1});
    ;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    I64 line = 1;
    U64 line_start = 0;
    U64 src_len; { U64 *_hp = Str_len(source); src_len = *_hp; free(_hp); }
    while (1) {
        Bool _wcond1640; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1640 = *_hp; free(_hp); }
        if (_wcond1640) {
        } else {
            ;
            break;
        }
        ;
        U8 *c = Str_get(source, pos);
        U8 _t1940 = 32;
        U8 _t1941 = 9;
        Bool _t1942 = U8_eq(DEREF(c), _t1940);
        ;
        Bool _t1943 = U8_eq(DEREF(c), _t1941);
        ;
        U8 _t1944 = 13;
        Bool _t1945 = Bool_or(_t1942, _t1943);
        ;
        ;
        Bool _t1946 = U8_eq(DEREF(c), _t1944);
        ;
        U8 _t1947 = 59;
        Bool _t1948 = Bool_or(_t1945, _t1946);
        ;
        ;
        Bool _t1949 = U8_eq(DEREF(c), _t1947);
        ;
        Bool _t1950 = Bool_or(_t1948, _t1949);
        ;
        ;
        if (_t1950) {
            U64 _t1641 = 1;
            U64 _t1642 = U64_add(DEREF(pos), _t1641);
            ;
            *pos = _t1642;
            ;
            ;
            continue;
        }
        ;
        U8 _t1951 = 10;
        Bool _t1952 = U8_eq(DEREF(c), _t1951);
        ;
        if (_t1952) {
            U64 _t1643 = 1;
            U64 _t1644 = U64_add(DEREF(pos), _t1643);
            ;
            *pos = _t1644;
            ;
            I64 _t1645 = 1;
            I64 _t1646 = I64_add(line, _t1645);
            ;
            line = _t1646;
            ;
            U64 _t1647 = U64_clone(pos);
            line_start = _t1647;
            ;
            ;
            continue;
        }
        ;
        U64 _t1953 = U64_sub(DEREF(pos), line_start);
        U64 _t1954 = 1;
        U64 _t1955 = U64_add(_t1953, _t1954);
        ;
        ;
        I64 col = U64_to_i64(_t1955);
        ;
        U64 start = U64_clone(pos);
        U8 _t1956 = 35;
        Bool _t1957 = U8_eq(DEREF(c), _t1956);
        ;
        if (_t1957) {
            while (1) {
                Bool _wcond1648; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1648 = *_hp; free(_hp); }
                if (_wcond1648) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1649 = Str_get(source, pos);
                U8 _t1650 = 10;
                Bool _t1651 = U8_eq(DEREF(_t1649), _t1650);
                ;
                if (_t1651) {
                    ;
                    break;
                }
                ;
                U64 _t1652 = 1;
                U64 _t1653 = U64_add(DEREF(pos), _t1652);
                ;
                *pos = _t1653;
                ;
            }
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1958 = 47;
        U64 _t1959 = 1;
        U64 _t1960 = U64_add(DEREF(pos), _t1959);
        ;
        Bool _t1961 = U8_eq(DEREF(c), _t1958);
        ;
        Bool _t1962; { Bool *_hp = U64_lt(&(U64){_t1960}, &(U64){src_len}); _t1962 = *_hp; free(_hp); }
        ;
        Bool _t1963 = Bool_and(_t1961, _t1962);
        ;
        ;
        if (_t1963) {
            U64 _t1714 = 1;
            U64 *_t1715 = malloc(sizeof(U64)); *_t1715 = U64_add(DEREF(pos), _t1714);
            ;
            U8 *c2 = Str_get(source, _t1715);
            U8 _t1716 = 47;
            Bool _t1717 = U8_eq(DEREF(c2), _t1716);
            ;
            if (_t1717) {
                while (1) {
                    Bool _wcond1654; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1654 = *_hp; free(_hp); }
                    if (_wcond1654) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U8 *_t1655 = Str_get(source, pos);
                    U8 _t1656 = 10;
                    Bool _t1657 = U8_eq(DEREF(_t1655), _t1656);
                    ;
                    if (_t1657) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1658 = 1;
                    U64 _t1659 = U64_add(DEREF(pos), _t1658);
                    ;
                    *pos = _t1659;
                    ;
                }
                U64_delete(_t1715, &(Bool){1});
                ;
                ;
                ;
                ;
                continue;
            }
            ;
            U8 _t1718 = 42;
            Bool _t1719 = U8_eq(DEREF(c2), _t1718);
            U64_delete(_t1715, &(Bool){1});
            ;
            if (_t1719) {
                U64 _t1710 = 2;
                U64 _t1711 = U64_add(DEREF(pos), _t1710);
                ;
                *pos = _t1711;
                ;
                I64 depth = 1;
                while (1) {
                    Bool _wcond1660; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1660 = *_hp; free(_hp); }
                    if (_wcond1660) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    I64 _t1685 = 0;
                    Bool _t1686; { Bool *_hp = I64_lte(&(I64){depth}, &(I64){_t1685}); _t1686 = *_hp; free(_hp); }
                    ;
                    if (_t1686) {
                        ;
                        break;
                    }
                    ;
                    U64 _t1687 = 1;
                    U64 _t1688 = U64_add(DEREF(pos), _t1687);
                    ;
                    Bool _t1689; { Bool *_hp = U64_lt(&(U64){_t1688}, &(U64){src_len}); _t1689 = *_hp; free(_hp); }
                    ;
                    if (_t1689) {
                        U8 *b1 = Str_get(source, pos);
                        U64 _t1669 = 1;
                        U64 *_t1670 = malloc(sizeof(U64)); *_t1670 = U64_add(DEREF(pos), _t1669);
                        ;
                        U8 *b2 = Str_get(source, _t1670);
                        U8 _t1671 = 47;
                        U8 _t1672 = 42;
                        Bool _t1673 = U8_eq(DEREF(b1), _t1671);
                        ;
                        Bool _t1674 = U8_eq(DEREF(b2), _t1672);
                        ;
                        Bool _t1675 = Bool_and(_t1673, _t1674);
                        ;
                        ;
                        if (_t1675) {
                            I64 _t1661 = 1;
                            I64 _t1662 = I64_add(depth, _t1661);
                            ;
                            depth = _t1662;
                            ;
                            U64 _t1663 = 2;
                            U64 _t1664 = U64_add(DEREF(pos), _t1663);
                            ;
                            *pos = _t1664;
                            ;
                            U64_delete(_t1670, &(Bool){1});
                            ;
                            ;
                            continue;
                        }
                        ;
                        U8 _t1676 = 42;
                        U8 _t1677 = 47;
                        Bool _t1678 = U8_eq(DEREF(b1), _t1676);
                        ;
                        Bool _t1679 = U8_eq(DEREF(b2), _t1677);
                        U64_delete(_t1670, &(Bool){1});
                        ;
                        Bool _t1680 = Bool_and(_t1678, _t1679);
                        ;
                        ;
                        if (_t1680) {
                            I64 _t1665 = 1;
                            I64 _t1666 = I64_sub(depth, _t1665);
                            ;
                            depth = _t1666;
                            ;
                            U64 _t1667 = 2;
                            U64 _t1668 = U64_add(DEREF(pos), _t1667);
                            ;
                            *pos = _t1668;
                            ;
                            ;
                            ;
                            continue;
                        }
                        ;
                    }
                    ;
                    U8 *_t1690 = Str_get(source, pos);
                    U8 _t1691 = 10;
                    Bool _t1692 = U8_eq(DEREF(_t1690), _t1691);
                    ;
                    if (_t1692) {
                        I64 _t1681 = 1;
                        I64 _t1682 = I64_add(line, _t1681);
                        ;
                        line = _t1682;
                        ;
                        U64 _t1683 = 1;
                        U64 _t1684 = U64_add(DEREF(pos), _t1683);
                        ;
                        line_start = _t1684;
                        ;
                    }
                    ;
                    U64 _t1693 = 1;
                    U64 _t1694 = U64_add(DEREF(pos), _t1693);
                    ;
                    *pos = _t1694;
                    ;
                }
                I64 _t1712 = 0;
                Bool _t1713; { Bool *_hp = I64_gt(&(I64){depth}, &(I64){_t1712}); _t1713 = *_hp; free(_hp); }
                ;
                ;
                if (_t1713) {
                    Str *_t1695 = Str_lit("Str", 3ULL);
                    U64 _t1696; { U64 *_hp = Str_size(); _t1696 = *_hp; free(_hp); }
                    U64 _t1697 = 6;
                    Array *_va23 = Array_new(_t1695, &(U64){_t1696}, &(U64){_t1697});
                    Str_delete(_t1695, &(Bool){1});
                    ;
                    ;
                    U64 _t1698 = 0;
                    Str *_t1699 = Str_clone(path);
                    Array_set(_va23, &(U64){_t1698}, _t1699);
                    ;
                    U64 _t1700 = 1;
                    Str *_t1701 = Str_lit(":", 1ULL);
                    Array_set(_va23, &(U64){_t1700}, _t1701);
                    ;
                    U64 _t1702 = 2;
                    Str *_t1703 = I64_to_str(&(I64){line});
                    Array_set(_va23, &(U64){_t1702}, _t1703);
                    ;
                    U64 _t1704 = 3;
                    Str *_t1705 = Str_lit(":", 1ULL);
                    Array_set(_va23, &(U64){_t1704}, _t1705);
                    ;
                    U64 _t1706 = 4;
                    Str *_t1707 = I64_to_str(&(I64){col});
                    Array_set(_va23, &(U64){_t1706}, _t1707);
                    ;
                    U64 _t1708 = 5;
                    Str *_t1709 = Str_lit(": error: unterminated comment", 29ULL);
                    Array_set(_va23, &(U64){_t1708}, _t1709);
                    ;
                    println(_va23);
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
        Bool _t1964; { Bool *_hp = is_digit(c); _t1964 = *_hp; free(_hp); }
        if (_t1964) {
            while (1) {
                Bool _wcond1720; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1720 = *_hp; free(_hp); }
                if (_wcond1720) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1721 = Str_get(source, pos);
                Bool _t1722; { Bool *_hp = is_digit(_t1721); _t1722 = *_hp; free(_hp); }
                Bool _t1723 = Bool_not(_t1722);
                ;
                if (_t1723) {
                    ;
                    break;
                }
                ;
                U64 _t1724 = 1;
                U64 _t1725 = U64_add(DEREF(pos), _t1724);
                ;
                *pos = _t1725;
                ;
            }
            U64 _t1742 = 1;
            U64 _t1743 = U64_add(DEREF(pos), _t1742);
            ;
            Bool _t1744; { Bool *_hp = U64_lt(&(U64){_t1743}, &(U64){src_len}); _t1744 = *_hp; free(_hp); }
            ;
            if (_t1744) {
                U8 *_t1734 = Str_get(source, pos);
                U8 _t1735 = 46;
                U64 _t1736 = 1;
                U64 *_t1737 = malloc(sizeof(U64)); *_t1737 = U64_add(DEREF(pos), _t1736);
                ;
                U8 *_t1738 = Str_get(source, _t1737);
                Bool _t1739 = U8_eq(DEREF(_t1734), _t1735);
                ;
                Bool _t1740; { Bool *_hp = is_digit(_t1738); _t1740 = *_hp; free(_hp); }
                U64_delete(_t1737, &(Bool){1});
                Bool _t1741 = Bool_and(_t1739, _t1740);
                ;
                ;
                if (_t1741) {
                    U64 _t1732 = 1;
                    U64 _t1733 = U64_add(DEREF(pos), _t1732);
                    ;
                    *pos = _t1733;
                    ;
                    while (1) {
                        Bool _wcond1726; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1726 = *_hp; free(_hp); }
                        if (_wcond1726) {
                        } else {
                            ;
                            break;
                        }
                        ;
                        U8 *_t1727 = Str_get(source, pos);
                        Bool _t1728; { Bool *_hp = is_digit(_t1727); _t1728 = *_hp; free(_hp); }
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
                }
                ;
            }
            ;
            U64 _t1745 = U64_sub(DEREF(pos), start);
            I64 _t1746 = I64_clone(&(I64){col});
            Token *_t1747 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(TokenType_Number()); _t1747->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1745}); _t1747->text = *_ca; free(_ca); }
            _t1747->line = I64_clone(&(I64){line});
            _t1747->col = _t1746;
            ;
            ;
            Vec_push(tokens, _t1747);
            ;
            ;
            ;
            continue;
        }
        ;
        Bool _t1965; { Bool *_hp = is_alpha(c); _t1965 = *_hp; free(_hp); }
        if (_t1965) {
            while (1) {
                Bool _wcond1748; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1748 = *_hp; free(_hp); }
                if (_wcond1748) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1749 = Str_get(source, pos);
                Bool _t1750; { Bool *_hp = is_alnum(_t1749); _t1750 = *_hp; free(_hp); }
                Bool _t1751 = Bool_not(_t1750);
                ;
                if (_t1751) {
                    ;
                    break;
                }
                ;
                U64 _t1752 = 1;
                U64 _t1753 = U64_add(DEREF(pos), _t1752);
                ;
                *pos = _t1753;
                ;
            }
            U64 _t1754 = U64_sub(DEREF(pos), start);
            Str *word = Str_substr(source, &(U64){start}, &(U64){_t1754});
            ;
            TokenType *type = lookup_keyword(word);
            I64 _t1755 = I64_clone(&(I64){line});
            I64 _t1756 = I64_clone(&(I64){col});
            Token *_t1757 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(type); _t1757->type = *_ca; free(_ca); }
            { Str *_ca = Str_clone(word); _t1757->text = *_ca; free(_ca); }
            _t1757->line = _t1755;
            _t1757->col = _t1756;
            ;
            ;
            TokenType_delete(type, &(Bool){1});
            Str_delete(word, &(Bool){1});
            Vec_push(tokens, _t1757);
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1966 = 34;
        Bool _t1967 = U8_eq(DEREF(c), _t1966);
        ;
        if (_t1967) {
            U64 _t1807 = 1;
            U64 _t1808 = U64_add(DEREF(pos), _t1807);
            ;
            *pos = _t1808;
            ;
            while (1) {
                Bool _wcond1758; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _wcond1758 = *_hp; free(_hp); }
                if (_wcond1758) {
                } else {
                    ;
                    break;
                }
                ;
                U8 *_t1765 = Str_get(source, pos);
                U8 _t1766 = 34;
                Bool _t1767 = U8_eq(DEREF(_t1765), _t1766);
                ;
                if (_t1767) {
                    ;
                    break;
                }
                ;
                U8 *_t1768 = Str_get(source, pos);
                U8 _t1769 = 92;
                U64 _t1770 = 1;
                U64 _t1771 = U64_add(DEREF(pos), _t1770);
                ;
                Bool _t1772 = U8_eq(DEREF(_t1768), _t1769);
                ;
                Bool _t1773; { Bool *_hp = U64_lt(&(U64){_t1771}, &(U64){src_len}); _t1773 = *_hp; free(_hp); }
                ;
                Bool _t1774 = Bool_and(_t1772, _t1773);
                ;
                ;
                if (_t1774) {
                    U64 _t1759 = 1;
                    U64 _t1760 = U64_add(DEREF(pos), _t1759);
                    ;
                    *pos = _t1760;
                    ;
                }
                ;
                U8 *_t1775 = Str_get(source, pos);
                U8 _t1776 = 10;
                Bool _t1777 = U8_eq(DEREF(_t1775), _t1776);
                ;
                if (_t1777) {
                    I64 _t1761 = 1;
                    I64 _t1762 = I64_add(line, _t1761);
                    ;
                    line = _t1762;
                    ;
                    U64 _t1763 = 1;
                    U64 _t1764 = U64_add(DEREF(pos), _t1763);
                    ;
                    line_start = _t1764;
                    ;
                }
                ;
                U64 _t1778 = 1;
                U64 _t1779 = U64_add(DEREF(pos), _t1778);
                ;
                *pos = _t1779;
                ;
            }
            U8 *_t1809 = Str_get(source, pos);
            U8 _t1810 = 34;
            Bool _t1811; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1811 = *_hp; free(_hp); }
            Bool _t1812 = U8_eq(DEREF(_t1809), _t1810);
            ;
            Bool _t1813 = Bool_and(_t1811, _t1812);
            ;
            ;
            if (_t1813) {
                U64 _t1780 = 1;
                U64 _t1781 = U64_add(DEREF(pos), _t1780);
                ;
                *pos = _t1781;
                ;
                U64 _t1782 = 1;
                U64 _t1783 = U64_sub(DEREF(pos), start);
                U64 _t1784 = 2;
                U64 _t1785 = U64_add(start, _t1782);
                ;
                U64 _t1786 = U64_sub(_t1783, _t1784);
                ;
                ;
                I64 _t1787 = I64_clone(&(I64){col});
                Token *_t1788 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_StringTok()); _t1788->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){_t1785}, &(U64){_t1786}); _t1788->text = *_ca; free(_ca); }
                _t1788->line = I64_clone(&(I64){line});
                _t1788->col = _t1787;
                ;
                ;
                ;
                Vec_push(tokens, _t1788);
            } else {
                Str *_t1789 = Str_lit("Str", 3ULL);
                U64 _t1790; { U64 *_hp = Str_size(); _t1790 = *_hp; free(_hp); }
                U64 _t1791 = 6;
                Array *_va24 = Array_new(_t1789, &(U64){_t1790}, &(U64){_t1791});
                Str_delete(_t1789, &(Bool){1});
                ;
                ;
                U64 _t1792 = 0;
                Str *_t1793 = Str_clone(path);
                Array_set(_va24, &(U64){_t1792}, _t1793);
                ;
                U64 _t1794 = 1;
                Str *_t1795 = Str_lit(":", 1ULL);
                Array_set(_va24, &(U64){_t1794}, _t1795);
                ;
                U64 _t1796 = 2;
                Str *_t1797 = I64_to_str(&(I64){line});
                Array_set(_va24, &(U64){_t1796}, _t1797);
                ;
                U64 _t1798 = 3;
                Str *_t1799 = Str_lit(":", 1ULL);
                Array_set(_va24, &(U64){_t1798}, _t1799);
                ;
                U64 _t1800 = 4;
                Str *_t1801 = I64_to_str(&(I64){col});
                Array_set(_va24, &(U64){_t1800}, _t1801);
                ;
                U64 _t1802 = 5;
                Str *_t1803 = Str_lit(": error: unterminated string", 28ULL);
                Array_set(_va24, &(U64){_t1802}, _t1803);
                ;
                println(_va24);
                U64 _t1804 = U64_sub(DEREF(pos), start);
                I64 _t1805 = I64_clone(&(I64){col});
                Token *_t1806 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1806->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1804}); _t1806->text = *_ca; free(_ca); }
                _t1806->line = I64_clone(&(I64){line});
                _t1806->col = _t1805;
                ;
                ;
                Vec_push(tokens, _t1806);
            }
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U8 _t1968 = 39;
        Bool _t1969 = U8_eq(DEREF(c), _t1968);
        ;
        if (_t1969) {
            U64 _t1839 = 1;
            U64 _t1840 = U64_add(DEREF(pos), _t1839);
            ;
            *pos = _t1840;
            ;
            U64 ch_start = U64_clone(pos);
            U8 *_t1841 = Str_get(source, pos);
            U8 _t1842 = 92;
            U64 _t1843 = 1;
            U64 _t1844 = U64_add(DEREF(pos), _t1843);
            ;
            Bool _t1845 = U8_eq(DEREF(_t1841), _t1842);
            ;
            Bool _t1846; { Bool *_hp = U64_lt(&(U64){_t1844}, &(U64){src_len}); _t1846 = *_hp; free(_hp); }
            ;
            Bool _t1847; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1847 = *_hp; free(_hp); }
            Bool _t1848 = Bool_and(_t1845, _t1846);
            ;
            ;
            Bool _t1849 = Bool_and(_t1847, _t1848);
            ;
            ;
            if (_t1849) {
                U64 _t1814 = 1;
                U64 _t1815 = U64_add(DEREF(pos), _t1814);
                ;
                *pos = _t1815;
                ;
            }
            ;
            U64 _t1850 = 1;
            U64 _t1851 = U64_add(DEREF(pos), _t1850);
            ;
            *pos = _t1851;
            ;
            U8 *_t1852 = Str_get(source, pos);
            U8 _t1853 = 39;
            Bool _t1854; { Bool *_hp = U64_lt(pos, &(U64){src_len}); _t1854 = *_hp; free(_hp); }
            Bool _t1855 = U8_eq(DEREF(_t1852), _t1853);
            ;
            Bool _t1856 = Bool_and(_t1854, _t1855);
            ;
            ;
            if (_t1856) {
                U64 _t1816 = U64_sub(DEREF(pos), ch_start);
                I64 _t1817 = I64_clone(&(I64){col});
                Token *_t1818 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Char()); _t1818->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){ch_start}, &(U64){_t1816}); _t1818->text = *_ca; free(_ca); }
                _t1818->line = I64_clone(&(I64){line});
                _t1818->col = _t1817;
                ;
                ;
                Vec_push(tokens, _t1818);
                U64 _t1819 = 1;
                U64 _t1820 = U64_add(DEREF(pos), _t1819);
                ;
                *pos = _t1820;
                ;
            } else {
                Str *_t1821 = Str_lit("Str", 3ULL);
                U64 _t1822; { U64 *_hp = Str_size(); _t1822 = *_hp; free(_hp); }
                U64 _t1823 = 6;
                Array *_va25 = Array_new(_t1821, &(U64){_t1822}, &(U64){_t1823});
                Str_delete(_t1821, &(Bool){1});
                ;
                ;
                U64 _t1824 = 0;
                Str *_t1825 = Str_clone(path);
                Array_set(_va25, &(U64){_t1824}, _t1825);
                ;
                U64 _t1826 = 1;
                Str *_t1827 = Str_lit(":", 1ULL);
                Array_set(_va25, &(U64){_t1826}, _t1827);
                ;
                U64 _t1828 = 2;
                Str *_t1829 = I64_to_str(&(I64){line});
                Array_set(_va25, &(U64){_t1828}, _t1829);
                ;
                U64 _t1830 = 3;
                Str *_t1831 = Str_lit(":", 1ULL);
                Array_set(_va25, &(U64){_t1830}, _t1831);
                ;
                U64 _t1832 = 4;
                Str *_t1833 = I64_to_str(&(I64){col});
                Array_set(_va25, &(U64){_t1832}, _t1833);
                ;
                U64 _t1834 = 5;
                Str *_t1835 = Str_lit(": error: unterminated character literal", 39ULL);
                Array_set(_va25, &(U64){_t1834}, _t1835);
                ;
                println(_va25);
                U64 _t1836 = U64_sub(DEREF(pos), start);
                I64 _t1837 = I64_clone(&(I64){col});
                Token *_t1838 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1838->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1836}); _t1838->text = *_ca; free(_ca); }
                _t1838->line = I64_clone(&(I64){line});
                _t1838->col = _t1837;
                ;
                ;
                Vec_push(tokens, _t1838);
            }
            ;
            ;
            ;
            ;
            ;
            continue;
        }
        ;
        U64 _t1970 = 1;
        U64 _t1971 = U64_add(DEREF(pos), _t1970);
        ;
        Bool _t1972; { Bool *_hp = U64_lt(&(U64){_t1971}, &(U64){src_len}); _t1972 = *_hp; free(_hp); }
        ;
        if (_t1972) {
            U64 _t1863 = 1;
            U64 *_t1864 = malloc(sizeof(U64)); *_t1864 = U64_add(DEREF(pos), _t1863);
            ;
            U8 *c2 = Str_get(source, _t1864);
            TokenType *two = TokenType_clone(TokenType_Eof());
            U8 _t1865 = 58;
            U8 _t1866 = 61;
            Bool _t1867 = U8_eq(DEREF(c), _t1865);
            ;
            Bool _t1868 = U8_eq(DEREF(c2), _t1866);
            ;
            Bool _t1869 = Bool_and(_t1867, _t1868);
            ;
            ;
            if (_t1869) {
                two = TokenType_clone(TokenType_ColonEq());
            }
            ;
            U8 _t1870 = 61;
            U8 _t1871 = 61;
            Bool _t1872 = U8_eq(DEREF(c), _t1870);
            ;
            Bool _t1873 = U8_eq(DEREF(c2), _t1871);
            ;
            Bool _t1874 = Bool_and(_t1872, _t1873);
            ;
            ;
            if (_t1874) {
                two = TokenType_clone(TokenType_EqEq());
            }
            ;
            U8 _t1875 = 33;
            U8 _t1876 = 61;
            Bool _t1877 = U8_eq(DEREF(c), _t1875);
            ;
            Bool _t1878 = U8_eq(DEREF(c2), _t1876);
            ;
            Bool _t1879 = Bool_and(_t1877, _t1878);
            ;
            ;
            if (_t1879) {
                two = TokenType_clone(TokenType_Neq());
            }
            ;
            U8 _t1880 = 60;
            U8 _t1881 = 61;
            Bool _t1882 = U8_eq(DEREF(c), _t1880);
            ;
            Bool _t1883 = U8_eq(DEREF(c2), _t1881);
            ;
            Bool _t1884 = Bool_and(_t1882, _t1883);
            ;
            ;
            if (_t1884) {
                two = TokenType_clone(TokenType_LtEq());
            }
            ;
            U8 _t1885 = 62;
            U8 _t1886 = 61;
            Bool _t1887 = U8_eq(DEREF(c), _t1885);
            ;
            Bool _t1888 = U8_eq(DEREF(c2), _t1886);
            ;
            Bool _t1889 = Bool_and(_t1887, _t1888);
            ;
            ;
            if (_t1889) {
                two = TokenType_clone(TokenType_GtEq());
            }
            ;
            U8 _t1890 = 46;
            U8 _t1891 = 46;
            Bool _t1892 = U8_eq(DEREF(c), _t1890);
            ;
            Bool _t1893 = U8_eq(DEREF(c2), _t1891);
            U64_delete(_t1864, &(Bool){1});
            ;
            Bool _t1894 = Bool_and(_t1892, _t1893);
            ;
            ;
            if (_t1894) {
                two = TokenType_clone(TokenType_DotDot());
            }
            ;
            Bool _t1895; { Bool *_hp = TokenType_eq(two, TokenType_Eof()); _t1895 = *_hp; free(_hp); }
            Bool _t1896 = Bool_not(_t1895);
            ;
            if (_t1896) {
                U64 _t1857 = 2;
                I64 _t1858 = I64_clone(&(I64){line});
                I64 _t1859 = I64_clone(&(I64){col});
                Token *_t1860 = malloc(sizeof(Token));
                { TokenType *_ca = TokenType_clone(two); _t1860->type = *_ca; free(_ca); }
                { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1857}); _t1860->text = *_ca; free(_ca); }
                _t1860->line = _t1858;
                _t1860->col = _t1859;
                ;
                ;
                ;
                Vec_push(tokens, _t1860);
                U64 _t1861 = 2;
                U64 _t1862 = U64_add(DEREF(pos), _t1861);
                ;
                *pos = _t1862;
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
            U8 _sw1897 = U8_clone(c);
            U8 _t1932 = 40;
            Bool _t1933 = U8_eq(_sw1897, _t1932);
            ;
            if (_t1933) {
                single = TokenType_clone(TokenType_LParen());
            } else {
                U8 _t1930 = 41;
                Bool _t1931 = U8_eq(_sw1897, _t1930);
                ;
                if (_t1931) {
                    single = TokenType_clone(TokenType_RParen());
                } else {
                    U8 _t1928 = 123;
                    Bool _t1929 = U8_eq(_sw1897, _t1928);
                    ;
                    if (_t1929) {
                        single = TokenType_clone(TokenType_LBrace());
                    } else {
                        U8 _t1926 = 125;
                        Bool _t1927 = U8_eq(_sw1897, _t1926);
                        ;
                        if (_t1927) {
                            single = TokenType_clone(TokenType_RBrace());
                        } else {
                            U8 _t1924 = 91;
                            Bool _t1925 = U8_eq(_sw1897, _t1924);
                            ;
                            if (_t1925) {
                                single = TokenType_clone(TokenType_LBracket());
                            } else {
                                U8 _t1922 = 93;
                                Bool _t1923 = U8_eq(_sw1897, _t1922);
                                ;
                                if (_t1923) {
                                    single = TokenType_clone(TokenType_RBracket());
                                } else {
                                    U8 _t1920 = 44;
                                    Bool _t1921 = U8_eq(_sw1897, _t1920);
                                    ;
                                    if (_t1921) {
                                        single = TokenType_clone(TokenType_Comma());
                                    } else {
                                        U8 _t1918 = 58;
                                        Bool _t1919 = U8_eq(_sw1897, _t1918);
                                        ;
                                        if (_t1919) {
                                            single = TokenType_clone(TokenType_Colon());
                                        } else {
                                            U8 _t1916 = 46;
                                            Bool _t1917 = U8_eq(_sw1897, _t1916);
                                            ;
                                            if (_t1917) {
                                                single = TokenType_clone(TokenType_Dot());
                                            } else {
                                                U8 _t1914 = 63;
                                                Bool _t1915 = U8_eq(_sw1897, _t1914);
                                                ;
                                                if (_t1915) {
                                                    single = TokenType_clone(TokenType_Question());
                                                } else {
                                                    U8 _t1912 = 33;
                                                    Bool _t1913 = U8_eq(_sw1897, _t1912);
                                                    ;
                                                    if (_t1913) {
                                                        single = TokenType_clone(TokenType_Bang());
                                                    } else {
                                                        U8 _t1910 = 43;
                                                        Bool _t1911 = U8_eq(_sw1897, _t1910);
                                                        ;
                                                        if (_t1911) {
                                                            single = TokenType_clone(TokenType_Plus());
                                                        } else {
                                                            U8 _t1908 = 45;
                                                            Bool _t1909 = U8_eq(_sw1897, _t1908);
                                                            ;
                                                            if (_t1909) {
                                                                single = TokenType_clone(TokenType_Minus());
                                                            } else {
                                                                U8 _t1906 = 42;
                                                                Bool _t1907 = U8_eq(_sw1897, _t1906);
                                                                ;
                                                                if (_t1907) {
                                                                    single = TokenType_clone(TokenType_Star());
                                                                } else {
                                                                    U8 _t1904 = 47;
                                                                    Bool _t1905 = U8_eq(_sw1897, _t1904);
                                                                    ;
                                                                    if (_t1905) {
                                                                        single = TokenType_clone(TokenType_Slash());
                                                                    } else {
                                                                        U8 _t1902 = 61;
                                                                        Bool _t1903 = U8_eq(_sw1897, _t1902);
                                                                        ;
                                                                        if (_t1903) {
                                                                            single = TokenType_clone(TokenType_Eq());
                                                                        } else {
                                                                            U8 _t1900 = 60;
                                                                            Bool _t1901 = U8_eq(_sw1897, _t1900);
                                                                            ;
                                                                            if (_t1901) {
                                                                                single = TokenType_clone(TokenType_Lt());
                                                                            } else {
                                                                                U8 _t1898 = 62;
                                                                                Bool _t1899 = U8_eq(_sw1897, _t1898);
                                                                                ;
                                                                                if (_t1899) {
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
        Bool _t1973; { Bool *_hp = TokenType_eq(single, TokenType_Eof()); _t1973 = *_hp; free(_hp); }
        Bool _t1974 = Bool_not(_t1973);
        ;
        if (_t1974) {
            U64 _t1934 = 1;
            I64 _t1935 = I64_clone(&(I64){line});
            I64 _t1936 = I64_clone(&(I64){col});
            Token *_t1937 = malloc(sizeof(Token));
            { TokenType *_ca = TokenType_clone(single); _t1937->type = *_ca; free(_ca); }
            { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1934}); _t1937->text = *_ca; free(_ca); }
            _t1937->line = _t1935;
            _t1937->col = _t1936;
            ;
            ;
            ;
            Vec_push(tokens, _t1937);
            U64 _t1938 = 1;
            U64 _t1939 = U64_add(DEREF(pos), _t1938);
            ;
            *pos = _t1939;
            ;
            ;
            ;
            TokenType_delete(single, &(Bool){1});
            ;
            continue;
        }
        ;
        TokenType_delete(single, &(Bool){1});
        Str *_t1975 = Str_lit("Str", 3ULL);
        U64 _t1976; { U64 *_hp = Str_size(); _t1976 = *_hp; free(_hp); }
        U64 _t1977 = 6;
        Array *_va26 = Array_new(_t1975, &(U64){_t1976}, &(U64){_t1977});
        Str_delete(_t1975, &(Bool){1});
        ;
        ;
        U64 _t1978 = 0;
        Str *_t1979 = Str_clone(path);
        Array_set(_va26, &(U64){_t1978}, _t1979);
        ;
        U64 _t1980 = 1;
        Str *_t1981 = Str_lit(":", 1ULL);
        Array_set(_va26, &(U64){_t1980}, _t1981);
        ;
        U64 _t1982 = 2;
        Str *_t1983 = I64_to_str(&(I64){line});
        Array_set(_va26, &(U64){_t1982}, _t1983);
        ;
        U64 _t1984 = 3;
        Str *_t1985 = Str_lit(":", 1ULL);
        Array_set(_va26, &(U64){_t1984}, _t1985);
        ;
        U64 _t1986 = 4;
        Str *_t1987 = I64_to_str(&(I64){col});
        Array_set(_va26, &(U64){_t1986}, _t1987);
        ;
        U64 _t1988 = 5;
        Str *_t1989 = Str_lit(": error: unexpected character", 29ULL);
        Array_set(_va26, &(U64){_t1988}, _t1989);
        ;
        println(_va26);
        U64 _t1990 = 1;
        I64 _t1991 = I64_clone(&(I64){col});
        ;
        Token *_t1992 = malloc(sizeof(Token));
        { TokenType *_ca = TokenType_clone(TokenType_Error()); _t1992->type = *_ca; free(_ca); }
        { Str *_ca = Str_substr(source, &(U64){start}, &(U64){_t1990}); _t1992->text = *_ca; free(_ca); }
        _t1992->line = I64_clone(&(I64){line});
        _t1992->col = _t1991;
        ;
        ;
        ;
        Vec_push(tokens, _t1992);
        U64 _t1993 = 1;
        U64 _t1994 = U64_add(DEREF(pos), _t1993);
        ;
        *pos = _t1994;
        ;
    }
    ;
    U64 _t1997 = U64_sub(DEREF(pos), line_start);
    ;
    U64_delete(pos, &(Bool){1});
    U64 _t1998 = 1;
    U64 _t1999 = U64_add(_t1997, _t1998);
    ;
    ;
    I64 col = U64_to_i64(_t1999);
    ;
    I64 _t2000 = I64_clone(&(I64){col});
    ;
    Token *_t2001 = malloc(sizeof(Token));
    { TokenType *_ca = TokenType_clone(TokenType_Eof()); _t2001->type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(Str_lit("", 0ULL)); _t2001->text = *_ca; free(_ca); }
    _t2001->line = I64_clone(&(I64){line});
    _t2001->col = _t2000;
    ;
    ;
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

